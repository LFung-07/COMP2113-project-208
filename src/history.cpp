#include "history.h"
#include <sstream>

std::string formatHistoryRecord(const GameHistory& game) {
    /*
     * What it does: Creates a formatted string from a GameHistory record.
     * Input: game - A GameHistory struct with game details.
     * Output: String in format: "Game X || Difficulty || Win/Loss || Answer || L/T"
     */
    std::stringstream ss;
    ss << "Game " << game.gameNumber << " || "
       << game.difficulty << " || "
       << (game.won ? "Win" : "Loss") << " || "
       << game.answer << " || "
       << game.attemptsLeft << "/" << game.maxAttempts;
  
    return ss.str();
}
