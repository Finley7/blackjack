#include <iostream>
#include <random>

int main() {


    std::cout << "Welkom bij Galgje! Voer een aantal woorden in om te beginnen!\n\n";
    std::vector<std::string> words = {};
    std::string chosenWord;
    std::string currentTry;
    int currentIndex = 0;
    bool alive = true;
    int lives = 5;

    while(true) {
        std::cout << "Voer een woord in. gebruik 'stop' om te stoppen $> ";
        std::string word;
        std::cin >> word;

        if(word == "stop") {
            break;
        }

        words.push_back(word);
    }

    system("clear");

    std::cout << "De computer heeft een woord gekozen. Hieronder staan het aantal vakken. Daaronder komen het aantal geraden letters.\n";

    if(words.empty()) {
        std::cout << "Je hebt geen woord ingevuld!";
        return 0;
    }

    std::shuffle(words.begin(), words.end(), std::default_random_engine{ std::random_device{}() });

    chosenWord = words.back();
    words[currentIndex].pop_back();

    for(int i = 0; i < chosenWord.size(); i++) {
        currentTry += "_";
    }

    while(true) {

        std::cout << currentTry + "\n\n";
        char letter;
        std::cout << "Voer een letter in: ";
        std::cin >> letter;
        std::vector<char> letters;
        bool gotLetter = false;

        for(int i = 0; i < chosenWord.size(); i++) {
            if(letter == chosenWord[i]) {
                gotLetter = true;
                currentTry[i] = letter;
            }
        }

        if(!gotLetter) {
            lives--;
            letters.push_back(letter);
            std::cout << "Helaas, die staat er niet in..\n\n";
            std::cout << "Levens over: " + std::to_string(lives) << std::endl;
        }

        if(!letters.empty()) {
            std::cout << "De volgende letters heb je al geraden:\n";
            for(auto l : letters) {
                std::cout << l << std::endl;
            }
        }

        if(lives == 0) {
            std::cout << "Game over!";
            break;
        }

        if(currentTry == chosenWord) {
            std::cout << chosenWord << std::endl;
            std::cout << "Je hebt het woord geraden!";
            break;
        }


    }

    return 0;
}
