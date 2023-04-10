#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Card {
    char name[8];
    int value;
} Card;

typedef struct Hand {
    int score;
    char name[15];
    int cardAmount;
    struct Card cards[21];
} Hand;

typedef struct Game {
    struct Card stack[52];
    int isAlive;
    int cardsInStack;
    struct Hand playerHand;
    struct Hand dealerHand;
    void (*end)(struct Game* game);
    void (*createPlayers)(struct Game *game, char name[15]);
    void (*shuffle)(struct Game *game);
    void (*play)(struct Game *game, char name[15]);
    void (*hit)(struct Game* game, struct Hand* hand);

} Game;

void createPlayers(Game *game, char name[15]) {

    strcpy(game->playerHand.name, name);
    strcpy(game->dealerHand.name, "Dealer");

    game->playerHand.cards[0] = game->stack[51];
    game->playerHand.cards[1] = game->stack[50];

    game->playerHand.cardAmount = 2;

    game->playerHand.score += game->stack[51].value;
    game->playerHand.score += game->stack[50].value;

    game->dealerHand.cards[0] = game->stack[49];
    game->dealerHand.score += game->stack[49].value;

    printf("De dealer heeft %s %i. Zijn score is %i\n\n", game->dealerHand.cards[0].name, game->dealerHand.cards[0].value, game->dealerHand.score);

    game->dealerHand.cardAmount = 1;

    game->cardsInStack = 49;

    if(game->playerHand.score == 21) {
        printf("21! De speler heeft gewonnen!");
        game->isAlive = 0;
    }

}

void shuffle(Game *game) {

    int deckLength = 0;
    char types[4][8] = {"Klaver", "Harten", "Ruiten", "Schoppen"};

    for(int i = 1; i < 12; i++) {
        struct Card c;
        strcpy(c.name, types[rand() % 3]);
        c.value = i;

        game->stack[deckLength] = c;

        deckLength++;

        if(i == 11) i = 0;
        if (deckLength == 52) break;

    }

    for (size_t i = 0; i < 52 - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (52 - i) + 1);
        Card temp = game->stack[j];
        game->stack[j] = game->stack[i];
        game->stack[i] = temp;
    }

    game->cardsInStack = deckLength;

    printf("De stapel is gehusseld..\n\n");

}

void play(Game *game, char name[15]) {
    game->shuffle(game);
    game->createPlayers(game, name);

    char choice[5];

    while(game->isAlive) {

        printf("Op dit moment heb je de volgende kaarten in je hand:\n");

        for(int i = 0; i < game->playerHand.cardAmount; i++) {
            printf(
                "- %s %i\n",
                game->playerHand.cards[i].name, game->playerHand.cards[i].value
            );
        }

        printf("Je score is %i\n\nWat doe je? (hit of hold)\n\n", game->playerHand.score);

        printf(">");

        scanf("%s", choice);

        if (strcmp(choice, "hold") == 0) {
            game->end(game);
        }

        if (strcmp(choice, "hit") == 0) {
            game->hit(game, &game->playerHand);
        }

    }

}

void hit(Game* game, Hand* p) {

    p->cards[p->cardAmount] = game->stack[game->cardsInStack-1];
    p->score = p->score + p->cards[p->cardAmount].value;

    printf(
        "Speler %s heeft kaart %s %i ontvangen. Zijn score is nu: %i\n\n",
        p->name,
        p->cards[p->cardAmount].name,
        p->cards[p->cardAmount].value,
        p->score
    );

    if(p->score == 21) {
        printf("Blackjack! Einde van het spel. Speler %s heeft gewonnen\n", p->name);
        game->isAlive = 0;
    }

    if(p->score > 21) {
        printf("Bust! Einde van het spel. Speler %s heeft verloren\n", p->name);
        game->isAlive = 0;
    }

    p->cardAmount++;
    game->cardsInStack--;
}

void end(Game* game) {

    game->hit(game, &game->dealerHand);

    if(game->dealerHand.score < 17) {
        end(game);
    } else {

        if (game->dealerHand.score < 21 && game->dealerHand.score > game->playerHand.score) {
            printf("De dealer scoorde hoger dan de speler. Speler %s heeft verloren\n", game->playerHand.name);
        }

        if (game->playerHand.score < 21 && game->dealerHand.score < game->playerHand.score) {
            printf("De dealer scoorde lager dan de speler. Speler %s heeft gewonnen!\n", game->playerHand.name);
        }

        game->isAlive = 0;
    }

}

int main() {
    srand(time(NULL));

    printf("Welkom bij Blackjack in C!\n");

    Game g = {
        .end = end,
        .createPlayers = createPlayers,
        .shuffle = shuffle,
        .play = play,
        .hit = hit,
        .isAlive = 1
    };

    char name[15];
    printf("Wat is je naam?> ");
    scanf("%s", name);

    play(&g, name);

    return 0;
}
