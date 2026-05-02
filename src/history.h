#ifndef HISTORY_H
#define HISTORY_H

#include <string>

struct GameHistory {
    int gameNumber;
    std::string difficulty;
    bool won;
    std::string answer;
    int attemptsLeft;
    int maxAttempts;
};

std::string formatHistoryRecord(const GameHistory& game);

#endif
