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
