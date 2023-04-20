#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 50

int main() {
    printf("Welkom bij Galgje! Voer een aantal woorden in om te beginnen!\n\n");

    char words[MAX_WORD_LENGTH][MAX_WORD_LENGTH];
    char chosenWord[MAX_WORD_LENGTH];
    char currentTry[MAX_WORD_LENGTH];
    char letters[MAX_WORD_LENGTH];
    int lives = 5;
    int wordCount = 0;

    while(1) {
        printf("Voer een woord in. gebruik 'stop' om te stoppen $> ");
        char word[MAX_WORD_LENGTH];
        scanf("%s", word);

        if(strcmp(word, "stop") == 0) {
            break;
        }

        strcpy(words[wordCount], word);
        wordCount++;
    }

    system("clear");

    printf("De computer heeft een woord gekozen. Hieronder staan het aantal vakken. Daaronder komen het aantal geraden letters.\n");

    if(wordCount == 0) {
        printf("Je hebt geen woord ingevuld!");
        return 0;
    }

    srand(time(NULL));
    int randomIndex = rand() % wordCount;
    strcpy(chosenWord, words[randomIndex]);
    words[randomIndex][strlen(chosenWord)-1] = '\0';

    for(int i = 0; i < strlen(chosenWord); i++) {
        currentTry[i] = '_';
    }
    currentTry[strlen(chosenWord)] = '\0';

    while(1) {

        printf("%s\n\n", currentTry);
        char letter;
        printf("Voer een letter in: ");
        scanf(" %c", &letter);
        int letterCount = 0;
        int gotLetter = 0;

        for(int i = 0; i < strlen(chosenWord); i++) {
            if(letter == chosenWord[i]) {
                gotLetter = 1;
                currentTry[i] = letter;
            }
        }

        if(!gotLetter) {
            lives--;
            letters[letterCount] = letter;
            letterCount++;
            printf("Helaas, die staat er niet in..\n\n");
            printf("Levens over: %d\n", lives);
        }

        if(letterCount > 0) {
            printf("De volgende letters heb je al geraden:\n");
            for(int i = 0; i < letterCount; i++) {
                printf("%c\n", letters[i]);
            }
        }

        if(lives == 0) {
            printf("Game over!");
            break;
        }

        if(strcmp(currentTry, chosenWord) == 0) {
            printf("%s\n", chosenWord);
            printf("Je hebt het woord geraden!");
            break;
        }
    }

    return 0;
}
