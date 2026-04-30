#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "game.h"
#include "fileio.h"
#include "history.h"
using namespace std;

int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Load files form path
    const string WORDS_FILE = "data/words.txt";
    const string HISTORY_FILE = "history/game_history.txt";

    // Load words
    cout << "Loading word list..." << endl;
    vector<string> words = loadWords(WORDS_FILE);

    if (words.empty()) {
        cout << "Error: No words loaded. Please check " << WORDS_FILE << endl;
        return 1;
    }
    cout << "Loaded " << words.size() << " words." << endl;

    // Initialize game counter from existing history
    int gameCount = countPreviousGames(HISTORY_FILE);
    
    return 0;
}
