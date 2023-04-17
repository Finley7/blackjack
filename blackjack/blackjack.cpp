// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <thread>

struct Game {

    const std::vector<int> count = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10};

    const std::string cards[4] = { "Spades", "Clover", "Hearts", "Diamond" };
    const std::string names[4] = {"Jack", "Queen", "King", "Ace"};

    std::vector<std::pair<std::string, int>> deck = {};
    std::vector<std::pair<std::string, int>> playerHands, dealerHands;
    bool alive = true;

    int playerScore = 0, dealerScore = 0;

    void shuffle() {
        
        for (int i = 0; i < count.size(); i++) {
            
            for (const auto & card : cards) {
                deck.emplace_back(card, count[i]);
            }

            if (i == 12) i = 0;
            if (deck.size() == 52) {
                break;
            }

        }
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine{ std::random_device{}() });
        sleep(1);
        std::cout << "De stapel is gehusseld" << "\n\n";
    }

    void sleep(int seconds) {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }

    void assignCards() {
        // Dealt two cards to player
        std::pair card = deck.back(); // get last card in deck
        playerHands.push_back(card);
        deck.pop_back(); // remove the card from deck

        card = deck.back();
        playerHands.push_back(card);
        deck.pop_back();

        // Dealt two cards to dealer
        card = deck.back();
        dealerHands.push_back(card);
        deck.pop_back();
    }

    void countScores() {
        playerScore = 0;
        dealerScore = 0;

        for(auto & playerHand : playerHands) {
            playerScore = playerScore + playerHand.second;
        }

        for(auto & dealerHand : dealerHands) {
            dealerScore = dealerScore + dealerHand.second;
        }

        if(playerScore > 21) {
            std::cout << "Score: " << playerScore << "\n\n";
            std::cout << "You lost.. Try again?" << "\n\n";
            alive = false;
        }

        if(playerScore == 21) {
            std::cout << "You won! Play again?" << "\n\n";
            alive = false;
        }

        std::cout << "The dealer has a score of " << dealerScore << "\n";
        std::cout << "The player has a score of " << playerScore << "\n";
        sleep(1);
    }

    void hit(const std::string& player) {

        std::vector<std::pair<std::string, int>> *correctHand;

        correctHand = &(player == "player" ? playerHands : dealerHands);

        std::pair<std::string, int> card = deck.back(); // get last card in deck
        correctHand->push_back(card);
        sleep(1);
        std::cout << "Handed out " << card.second << " of " << card.first << " to " << player << "\n\n";

        deck.pop_back(); // remove the card from deck
        countScores();
    }

    void finish() {
        if(dealerScore < 17) {
            hit("dealer");
            finish();
        }
    }

    void stand() {

        finish();

        if(dealerScore > 21) {
            std::cout << "The dealer is BUST! You've won! Play again?" << "\n\n";
            alive = false;
        }

        if(dealerScore == 21) {
            std::cout << "The dealer has won! Try again?" << "\n\n";
            alive = false;
        }

        if(dealerScore > playerScore && dealerScore <= 21) {
            std::cout << "The dealer has won! Try again?" << "\n\n";
            alive = false;
        }

        if(playerScore > dealerScore && playerScore <= 21) {
            std::cout << "You've won! Congratulations" << "\n\n";
            alive = false;
        }

    }

    void play() {

        std::pair<std::string, int> dealerCard = dealerHands.back();
        std::cout << "The dealer has a " << dealerCard.first << " of " << dealerCard.second << "\n\n";

        for (auto & playerHand : playerHands) {
            std::cout << "The player has a " << playerHand.first << " of " << playerHand.second << "\n\n";
        }
        
        countScores();

        std::string choice;

        while (alive) {
            std::cout << "What will you do? (hit or stand)" << "\n\n";
            std::cin >> choice;

            if (choice == "stand" || choice == "hit") {
                
                if (choice == "hit") {
                    hit("player");
                } else {
                    stand();
                }

            }
            else {
                std::cout << "Invalid command, please try again." << "\n\n";
            }
        }

    }


    void start() {
        std::cout << "De game is gestart" << "\n\n";
        shuffle();
        assignCards();
        play();
    }

    void reset() {
        alive = true;
    }
};

int main()
{
    std::string keyword;
    Game *game = nullptr;

    while (true) {
        std::cout << "Welkom bij BlackJack\n";
        std::cout << "Type 'start' om te starten, 'help' voor hulp of 'exit' om af te sluiten" << "\n\n";
        std::cin >> keyword;

        if (keyword == "help") {
            std::cout << "------" << "\n\n";
            std::cout << "Blackjack is een populair kaartspel dat meestal wordt gespeeld in casino's, maar ook vaak in huiselijke kring. Het doel van het spel is om een hand te krijgen met een hogere waarde dan de hand van de dealer, zonder de waarde van 21 te overschrijden.Het spel wordt gespeeld met een standaard dek van 52 kaarten.Elke kaart heeft een puntwaarde die overeenkomt met het nummer op de kaart, behalve de plaatjeskaarten(boer, vrouw, koning) die elk 10 punten waard zijn, en de aas die 1 of 11 punten waard kan zijn, afhankelijk van wat beter uitkomt voor de speler.Aan het begin van het spel krijgt elke speler, inclusief de dealer, twee kaarten.De speler kan ervoor kiezen om extra kaarten te vragen(hit) om zo dichter bij de 21 te komen, of hij kan passen en hopen dat zijn hand al sterk genoeg is om de dealer te verslaan.Als de speler 21 punten bereikt met zijn eerste twee kaarten(een aas en een kaart met een puntwaarde van 10), wordt dit een blackjack genoemd en wint de speler automatisch, tenzij de dealer ook een blackjack heeft.Als alle spelers hebben gehandeld, is het de beurt aan de dealer om zijn hand te spelen.De dealer moet kaarten blijven trekken totdat hij minimaal 17 punten heeft bereikt.Als de dealer meer dan 21 punten heeft(bust), wint elke speler die nog in het spel is.Als de speler een hogere hand heeft dan de dealer zonder de 21 te overschrijden, wint de speler.Als de dealer een hogere hand heeft, verliest de speler.Als de speler en de dealer dezelfde hand hebben, eindigt het spel in een gelijkspel." << "\n\n";
            std::cout << "------" << "\n\n";
        }

        if (keyword == "start") {

            if(game != nullptr) {
                delete game;
            }

            game = new Game();
            game->start();
        }

        if (keyword == "exit") {
            break;
        }
    }

    return 0;
}
