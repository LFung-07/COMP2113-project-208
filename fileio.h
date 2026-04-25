
/*
 * fileio.h
 * Purpose: Declares file input/output utility functions for the Hangman game.
 * These functions handle loading word lists from text files and generating
 * random words for gameplay.
 */

#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include <string>

/**
 * Loads words from a text file into a vector of strings.
 * What it does: Opens a file, reads each line (one word per line),
 *               and stores valid words (4-12 letters) into a vector.
 * Input: filename - Path to the word list text file.
 * Output: A vector of strings containing all loaded words.
 */
std::vector<std::string> loadWords(const std::string& filename);

/**
 * Selects a random word from a word list.
 * What it does: Uses rand() to pick a random index from the vector.
 * Input: wordList - A vector of strings to choose from.
 * Output: A single randomly selected word string.
 */
std::string getRandomWord(const std::vector<std::string>& wordList);

/**
 * Saves a game record to the history file.
 * What it does: Appends a formatted game result line to game_history.txt.
 * Inputs:
 *   - filename: Path to the history file.
 *   - gameNumber: The sequential game number.
 *   - difficulty: "Easy", "Normal", or "Hard".
 *   - won: true if player won, false if lost.
 *   - answer: The secret word.
 *   - attemptsLeft: Number of remaining wrong guesses.
 *   - maxAttempts: Maximum wrong guesses allowed.
 * Output: None (writes to file as side effect).
 */
void saveGameHistory(const std::string& filename, int gameNumber,
                     const std::string& difficulty, bool won,
                     const std::string& answer, int attemptsLeft,
                     int maxAttempts);

/**
 * Loads and displays the entire game history from file.
 * What it does: Reads all lines from the history file and prints them.
 * Input: filename - Path to the history file.
 * Output: None (prints to console as side effect).
 */
void displayHistory(const std::string& filename);

/**
 * Counts the number of games already played (for game numbering).
 * What it does: Counts non-empty lines in the history file.
 * Input: filename - Path to the history file.
 * Output: Integer count of previous games.
 */
int countPreviousGames(const std::string& filename);

#endif
