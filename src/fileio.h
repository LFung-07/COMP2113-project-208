#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include <string>
using namespace std;


vector<string> loadWords(const string& filename);
// This loads words from a text file into a vector of strings.


string getRandomWord(const vector<string>& word_list);
// This selects a random word from a word list.


void saveGameHistory(const string& filename, int game_no, const string& difficulty, bool won, const string& answer, int atps_left, int max_atps);
// This saves a game record to the history file.


void displayHistory(const string& filename);
// This loads and displays the entire game history from file.


int countPreviousGames(const string& filename);
// This counts the number of games already played (for game numbering).

#endif
