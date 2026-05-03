#ifndef HISTORY_H
#define HISTORY_H

#include <string>

/*
 * GameHistory struct - Stores information about a single game session.
 */
struct GameHistory {
    int gameNumber;         // Game number
    std::string difficulty; // Difficulty level (Easy/Normal/Hard)
    bool won;               // Whether the player won
    std::string answer;     // The secret word
    int attemptsLeft;       // Remaining wrong guesses
    int maxAttempts;        // Maximum wrong guesses allowed
};

/*
 * Formats a GameHistory record into a readable string.
 * What it does: Converts game data into formatted string for display and storage.
 * Input: game - A GameHistory struct containing game details.
 * Output: A string in format "Game X || Difficulty || Win/Loss || Answer || L/T"
 */
std::string formatHistoryRecord(const GameHistory& game);

#endif
