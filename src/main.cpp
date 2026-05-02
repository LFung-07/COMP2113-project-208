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

int selectDifficulty(string& difficulty) {
    int choice;
    cout << "\n----- Select Difficulty -----" << endl;
    cout << "1. Easy   (12 wrong attempts)" << endl;
    cout << "2. Normal (9 wrong attempts)" << endl;
    cout << "3. Hard   (6 wrong attempts)" << endl;
    cout << "----------------------------" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;

    switch (choice) {
        case 1:
            difficulty = "Easy";
            return 12;
        case 2:
            difficulty = "Normal";
            return 9;
        case 3:
            difficulty = "Hard";
            return 6;
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

void displayHangman(int wrong, int max_no_wrong) {
    cout << "\n   +---+" << endl;
    cout << "   |   |" << endl;
    
    // Head
    if (wrong >= 1)
        cout << "   |   O" << endl;
    else
        cout << "   |" << endl;
    
    // Body and arms
    if (wrong == 2)
        cout << "   |   |" << endl;
    else if (wrong == 3)
        cout << "   |  /|" << endl;
    else if (wrong >= 4)
        cout << "   |  /|\\" << endl;
    else
        cout << "   |" << endl;
    
    // Waist
    if (wrong >= 5)
        cout << "   |   |" << endl;
    else
        cout << "   |" << endl;
    
    // Legs
    if (wrong == 6)
        cout << "   |  /" << endl;
    else if (wrong >= 7)
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
    int chance = rand() % 100;  // 0-99
    
    if (chance < 10) {
        // 10% chance: Lucky Hint - show unguessed vowel count
        int no_of_vowel = game.getUnguessedVowelCount();
        cout << "\n🌟 RANDOM EVENT: LUCKY HINT! 🌟" << endl;
        cout << "There are " << no_of_vowel << " unguessed vowels remaining in the word." << endl;
    } else if (chance < 20) {
        // 10% chance: Bomb Defuse - eliminate a wrong letter
        char defused = game.defuseWrongLetter();
        if (defused != '\0') {
            cout << "\n💣 RANDOM EVENT: BOMB DEFUSE! 💣" << endl;
            cout << "The letter '" << defused
                      << "' has been eliminated as a wrong guess!" << endl;
        }
    }
}


// What it does: Manages the full game loop from word selection to end.
// Inputs: wordsd, difficulty, max_wrong, game_count, history_file.
// Output: None (runs game, saves result to history).

void playGame(const vector<string>& words,
              const string& difficulty_name,
              int max_wrong, 
              int& game_count,
              const string& history_file) {
    // Select random word
    string secret_word = getRandomWord(words);
    
    // Create game object
    Hangman game(secret_word, max_wrong);
    
    // Increment game count
    game_count++;
    cout << "\n--- Game " << game_count << " ---" << endl;
    cout << "Difficulty: " << difficulty << endl;
    cout << "Word length: " << secret_word.length() << " letters" << endl;

    // Main game loop
    while (!game.isGameOver()) {
        displayHangman(game.getRemainingGuesses(), game.getMaxGuesses());
        cout << "\nWord: " << game.getDisplayedWord() << endl;
        cout << "Guessed letters: " << game.getGuessedLetters() << endl;
        cout << "Remaining guesses: " << game.getRemainingGuesses()
                  << "/" << game.getMaxGuesses() << endl;

        // Check for random event before each guess
        checkRandomEvent(game);

        // Get player's guess
        cout << "\nEnter a letter: ";
        string input;
        cin >> input;

        // Validate input
        if (input.length() != 1 || !isalpha(input[0])) {
            cout << "Please enter a single letter!" << endl;
            continue;
        }

        bool correct = game.guessLetter(input[0]);
        if (correct) {
            cout << "✅ Correct!" << endl;
        } else {
            cout << "❌ Wrong!" << endl;
        }
    }

    // Game over - display final result
    displayHangman(game.getRemainingGuesses(), game.getMaxGuesses());
    cout << "\n=============== GAME OVER ===============" << endl;
    cout << "Word: " << game.getSecretWord() << endl;

    if (game.isWin()) {
        cout << "🎉 CONGRATULATIONS! YOU WIN! 🎉" << endl;
    } else {
        cout << "💀 YOU LOSE! Better luck next time! 💀" << endl;
    }

    // Save to history
    int atps_left = game.getRemainingGuesses();
    saveGameHistory(history_file, game_count, difficulty,
                    game.isWin(), game.getSecretWord(),
                    atps_left, game.getMaxGuesses());

    cout << "\nGame saved to history." << endl;
}





int main() {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(NULL)));

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
    int game_count = countPreviousGames(HISTORY_FILE);

    bool quit = false;
    while (!quit) {
        int choice = displayMenu();

        switch (choice) {
            case 1: {
                // Play Game
                string difficulty;
                int max_no_wrong = selectDifficulty(difficulty);
                
                if (maxWrong > 0) {
                    playGame(words, difficulty, max_no_wrong, game_count, HISTORY_FILE);
                }
                break;
            }
            case 2:
                // View History
                // PLS RMB ADD AFTER HISTORY PART IS DONEEE
                break;
            case 3:
                // Quit
                cout << "\nThank you for playing Hangman! Goodbye!" << endl;
                quit = true;
                break;
            default:
                cout << "Invalid choice! Please enter 1, 2, or 3." << endl;
        }
    }
    
    return 0;
}
