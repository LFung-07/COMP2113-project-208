#include "fileio.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace

vector<string> loadWords(const string& filename) {
    
    // What it does: It opens a file, reads one word on each line, and stores them into a vector.
                    // Only include words with length we want (4-12 letter)
    // Input: filename - Path to the word list text file.
    // Output: A vector of all loaded words.
     
    vector<string> words;
    ifstream file(filename);
    string word;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return words;
    }

    while (getline(file, word)) {
        // Remove carriage return if present (Windows-formatted files)
        if (!word.empty() && word.back() == '\r') {
            word.pop_back();
        }

        // Check length of words as well.
        if (word.length() >= 4 && word.length() <= 12) {
            // Convert to lowercase for consistency
            string lowerWord;
            for (char c : word) {
                lowerWord += tolower(c);
            }
            words.push_back(lowerWord);
        }
    }

    file.close();
    return words;
}

string getRandomWord(const vector<string>& word_list) {
    
    // What it does: It picks a random item from the vector.
    // Input: word_list - A vector of strings to choose from.
    // Output: A randomly selected word.
    
    if (word_list.empty()) {
        return "";
    }

    int randomIndex = rand() % word_list.size();
    return word_list[randomIndex];
}

void saveGameHistory(const string& filename, int game_no,
                     const string& difficulty, bool won,
                     const string& answer, int atps_left,
                     int max_atps) {
    
    // What it does: It appends a game result line to game_history.txt, after formatting it.
    // Inputs: filename, game_no, difficulty, won, answer, atps_left, max_atps
    // Output: None (writes to the history file).
    
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << "Game " << game_no << " || "
             << difficulty << " || "
             << (won ? "Win" : "Loss") << " || "
             << answer << " || "
             << atps_left << "/" << max_atps << endl;
        file.close();
    } else {
        cerr << "Error: Could not save game history." << endl;
    }
}

void displayHistory(const string& filename) {
    
    // What it does: It reads all lines from the history file and prints them.
    // Input: filename - Path to the history file.
    // Output: None (prints game history to console).
    
    ifstream file(filename);
    string line;

    cout << "\n========== GAME HISTORY ==========" << endl;
    if (file.is_open()) {
        bool hvrec = false;
        while (getline(file, line)) {
            if (!line.empty()) {
                cout << line << endl;
                hvrec = true;
            }
        }
        if (!hvrec) {
            cout << "No games played yet." << endl;
        }
        file.close();
    }
    cout << "===================================\n" << endl;
}

int countPreviousGames(const string& filename) {
    
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
}
