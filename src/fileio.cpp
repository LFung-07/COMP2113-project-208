#include "fileio.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

// Function objective: Opens a file, reads one word per line, and stores them in a vector. >>> Only include words with a length we want (4-12 letters)
vector<string> loadWords(const string& filename) {
    // ^Input filename - Path to the word list text file.
    
    vector<string> words;
    ifstream file(filename);
    string word;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return words;
    }

    while (getline(file, word)) {
        if (!word.empty() && word.back() == '\r') {
            word.pop_back();
        }

        if (word.length() >= 4 && word.length() <= 12) {
            string lowerWord;
            for (char c : word) {
                lowerWord += tolower(c);
            }
            words.push_back(lowerWord);
        }
    }

    file.close();
    return words;
    // ^Output a vector of all loaded words.
}


// Function objective: Picks a random item from the vector.
string getRandomWord(const vector<string>& wordList) {
    // ^Input word_list - A vector of strings to choose from.
    
    if (wordList.empty()) {
        return "";
    }

    int randomIndex = rand() % wordList.size();
    return wordList[randomIndex];
    // ^Output a randomly selected word.
}

// Function objective: appends a game result line to game_history.txt, after formatting it.
void saveGameHistory(const string& filename, int gameNumber,
                     const string& difficulty, bool won,
                     const string& answer, int attemptsLeft,
                     int maxAttempts) {
    // ^Input filename, game_no, difficulty, won, answer, atps_left, max_atps
    
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << "Game " << gameNumber << " || "
             << difficulty << " || "
             << (won ? "Win" : "Loss") << " || "
             << answer << " || "
             << attemptsLeft << "/" << maxAttempts << endl;
        file.close();
    } else {
        cerr << "Error: Could not save game history." << endl;
    }
    // ^Output nothing (writes to the history file).
}

// Function objective: Reads all lines from the history file and prints them.
void displayHistory(const string& filename) {
    // ^Input filename - Path to the history file.
    
    ifstream file(filename);
    string line;

    cout << "\n========== GAME HISTORY ==========" << endl;
    if (file.is_open()) {
        bool hasContent = false;
        while (getline(file, line)) {
            if (!line.empty()) {
                cout << line << endl;
                hasContent = true;
            }
        }
        if (!hasContent) {
            cout << "No games played yet." << endl;
        }
        file.close();
    }
    cout << "===================================\n" << endl;
    // ^Output nothing (prints game history to console).
}

// Function objective: Counts non-empty lines in the history file to determine the next game number.
int countPreviousGames(const string& filename) {
    // ^Input filename - Path to the history file.
    
    ifstream file(filename);
    string line;
    int count = 0;


    if (file.is_open()) {
        while (getline(file, line)) {
            if (!line.empty()) {
                count++;
            }
        }
        file.close();
    }
    return count;
    // ^Output Number of previously played games
}
