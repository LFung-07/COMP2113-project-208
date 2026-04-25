// fileio.h
// Purpose: Declares file input/output utility functions for Hangmna game.
// These functions handle loading word lists from text files and generating random words for gameplay.

#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include <string>

// Loads words from a text file into a vector of strings.
// What it does: It opens a file, reads one word on each line, and stores them into a vector.
// Input: filename - Path to the word list text file.
// Output: A vector of all loaded words.

vector<string> loadWords(const string& filename);


// Selects a random word from a word list.
// What it does: It picks a random item from the vector.
// Input: word_list - A vector of strings to choose from.
// Output: A randomly selected word.

string getRandomWord(const vector<string>& word_list);


// Saves a game record to the history file.
// What it does: It appends a game result line to game_history.txt, after formatting it.
// Inputs:
//   - filename: Path to the history file.
//   - game_no: The sequential game number.
//   - difficulty: "Easy", "Normal", or "Hard".
//   - won: true if player won, false if lost.
//   - answer: The secret word.
//   - atps_left: Number of remaining wrong guesses.
//   - max_atps: Maximum wrong guesses allowed.
// Output: None (writes to the history file).

void saveGameHistory(const string& filename, int game_no,
                     const string& difficulty, bool won,
                     const string& answer, int atps_left,
                     int max_atps);


// Loads and displays the entire game history from file.
// What it does: It reads all lines from the history file and prints them.
// Input: filename - Path to the history file.
// Output: None (prints game history to console).

void displayHistory(const string& filename);


// Counts the number of games already played (for game numbering).
// What it does: Counts number of lines in the history file.
// Input: filename - Path to the history file.
// Output: Number of played games.

int countPreviousGames(const string& filename);
