#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "game.h"
#include "fileio.h"
#include "history.h"
using namespace std;


// What it does: Prints menu options and reads user input.
// Input: reads user imput from cin.
// Output: Integer representing menu choice (1, 2, or 3).

int displayMenu() {
    int choice;
    cout << "\n=========== HANGMAN GAME ===========" << endl;
    cout << "1. Play Game" << endl;
    cout << "2. View Game History" << endl;
    cout << "3. Quit" << endl;
    cout << "====================================" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    return choice;
}


// What it does: Shows difficulty options and gets player's choice.
// Input: reads choice from cin.
// Output: Maximum wrong guesses for the chosen difficulty. Returns 0 if it is an invalid choice.

int selectDifficulty(string& difficultyName) {
    int choice;
    cout << "\n----- Select Difficulty -----" << endl;
    cout << "1. Easy   (12 wrong attempts)" << endl;
    cout << "2. Normal (9 wrong attempts)" << endl;
    cout << "3. Hard   (6 wrong attempts)" << endl;
    cout << "----------------------------" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    switch (choice) {
        case 1: difficultyName = "Easy"; return 12;
        case 2: difficultyName = "Normal"; return 9;
        case 3: difficultyName = "Hard"; return 6;
        default:
            cout << "Invalid choice!" << endl;
            return 0;
    }
}


// What it does: Draws the hangman figure proportional to wrong guesses.
// Inputs:
//   - wrong: Current number of wrong guesses.
//   - max_no_wrong: Maximum number of allowed wrong guesses.
// Output: None (prints ASCII art to console).

void displayHangman(int wrongGuesses, int maxWrong) {
    int stage;
    if (wrongGuesses <= 0) {
        stage = 0;
    } else if (wrongGuesses >= maxWrong) {
        stage = 7;
    } else {
        stage = (wrongGuesses * 7) / maxWrong;
    }
   
    cout << "\n   +---+" << endl;
    cout << "   |   |" << endl;
   
    if (stage >= 1)
        cout << "   |   O" << endl;
    else    
        cout << "   |" << endl;
   
    if (stage == 2)
        cout << "   |   |" << endl;
    else if (stage == 3)
        cout << "   |  /|" << endl;
    else if (stage >= 4)
        cout << "   |  /|\\" << endl;
    else
        cout << "   |" << endl;
   
    if (stage >= 5)
        cout << "   |   |" << endl;
    else
        cout << "   |" << endl;
   
    if (stage == 6)
        cout << "   |  /" << endl;
    else if (stage >= 7)
        cout << "   |  / \\" << endl;
    else
        cout << "   |" << endl;
   
    cout << "   |" << endl;
    cout << "=========" << endl;
}


// What it does: Randomly selects between Lucky Hint and Bomb Defuse.
// Input: game - Reference to the Hangman game object.
// Output: None (modifies game state or prints hint to console).

void checkRandomEvent(Hangman& game) {
    int randomChance = rand() % 100;
   
    if (randomChance < 10) {
        int vowelCount = game.getUnguessedVowelCount();
        cout << "\n*** RANDOM EVENT: LUCKY HINT! ***" << endl;
        cout << "There are " << vowelCount
             << " unguessed vowels remaining in the word." << endl;
    } else if (randomChance < 20) {
        char defused = game.defuseWrongLetter();
        if (defused != '\0') {
            cout << "\n*** RANDOM EVENT: BOMB DEFUSE! ***" << endl;
            cout << "The letter '" << defused
                 << "' has been eliminated as a wrong guess!" << endl;
        }
    }
}


// What it does: Manages the full game loop from word selection to end.
// Inputs: wordsd, difficulty, max_wrong, game_count, history_file.
// Output: None (runs game, saves result to history).

void playGame(const vector<string>& words,
              const string& difficultyName,
              int maxWrong, int& gameCount,
              const string& historyFile) {
    string secretWord = getRandomWord(words);
    Hangman game(secretWord, maxWrong);
   
    gameCount++;
    cout << "\n--- Game " << gameCount << " ---" << endl;
    cout << "Difficulty: " << difficultyName << endl;
    cout << "Word length: " << secretWord.length() << " letters" << endl;

    while (!game.isGameOver()) {
        int wrongGuessesMade = game.getMaxGuesses() - game.getRemainingGuesses();
        displayHangman(wrongGuessesMade, game.getMaxGuesses());
       
        cout << "\nWord: " << game.getDisplayedWord() << endl;
        cout << "Guessed letters: " << game.getGuessedLetters() << endl;
        cout << "Remaining guesses: " << game.getRemainingGuesses()
             << "/" << game.getMaxGuesses() << endl;


        checkRandomEvent(game);

        cout << "\nEnter a letter: ";
        string input;
        cin >> input;

        if (input.length() != 1 || !isalpha(input[0])) {
            cout << "Please enter a single letter!" << endl;
            continue;
        }

        bool correct = game.guessLetter(input[0]);
        if (correct)
            cout << ">> Correct!" << endl;
        else
            cout << ">> Wrong!" << endl;
    }

    int wrongGuessesMade = game.getMaxGuesses() - game.getRemainingGuesses();
    displayHangman(wrongGuessesMade, game.getMaxGuesses());
   
    cout << "\n=============== GAME OVER ===============" << endl;
    cout << "Word: " << game.getSecretWord() << endl;

    if (game.isWin())
        cout << "=== CONGRATULATIONS! YOU WIN! ===" << endl;
    else
        cout << "=== YOU LOSE! Better luck next time! ===" << endl;

    int attemptsLeft = game.getRemainingGuesses();
    saveGameHistory(historyFile, gameCount, difficultyName,
                    game.isWin(), game.getSecretWord(),
                    attemptsLeft, game.getMaxGuesses());

    cout << "\nGame saved to history." << endl;
}


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));


    const string WORDS_FILE = "data/words.txt";
    const string HISTORY_FILE = "history/game_history.txt";


    cout << "Loading word list..." << endl;
    vector<string> words = loadWords(WORDS_FILE);


    if (words.empty()) {
        cout << "Error: No words loaded. Please check " << WORDS_FILE << endl;
        return 1;
    }
    cout << "Loaded " << words.size() << " words." << endl;


    int gameCount = countPreviousGames(HISTORY_FILE);


    bool quit = false;
    while (!quit) {
        int choice = displayMenu();


        switch (choice) {
            case 1: {
                string difficultyName;
                int maxWrong = selectDifficulty(difficultyName);
                if (maxWrong > 0)
                    playGame(words, difficultyName, maxWrong, gameCount, HISTORY_FILE);
                break;
            }
            case 2:
                displayHistory(HISTORY_FILE);
                break;
            case 3:
                cout << "\nThank you for playing Hangman! Goodbye!" << endl;
                quit = true;
                break;
            default:
                cout << "Invalid choice! Please enter 1, 2, or 3." << endl;
        }
    }


    return 0;
}
