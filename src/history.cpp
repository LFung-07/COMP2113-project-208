#include "history.h"
#include <sstream>

std::string formatHistoryRecord(const GameHistory& game) {
  
    std::stringstream ss;
    ss << "Game " << game.gameNumber << " || "
       << game.difficulty << " || "
       << (game.won ? "Win" : "Loss") << " || "
       << game.answer << " || "
       << game.attemptsLeft << "/" << game.maxAttempts;
  
    return ss.str();
  
}
