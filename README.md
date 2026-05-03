# Hangman Game - COMP2113 Course Project

## Team Members
- Shiwoo Ahn - 3036516873
- Leung Fung - 3036600181
- Ng Cheuk Hang - 3036588204

## Game Description
A text-based Hangman game with multiple difficulty levels, random events,
and game history tracking. Players guess letters to uncover a hidden word
before running out of attempts.

## Features

### 1. Multiple Difficulty Levels
- **Easy**: 12 wrong attempts
- **Normal**: 9 wrong attempts
- **Hard**: 6 wrong attempts
All words are 4-12 letters long across all difficulties.

### 2. Random Events (20% chance each turn)
- **Lucky Hint (10%)**: Reveals how many unguessed vowels remain.
- **Bomb Defuse (10%)**: Automatically eliminates one wrong letter.

### 3. Game History
Records all games with format:
`Game [number] || [difficulty] || [Win/Loss] || [answer] || [attempts left/total]`

## Coding Requirement Elements

| Requirement | Implementation |
|-------------|---------------|
| Random Events | `rand()` for word selection, random event triggers |
| Data Structures | `struct GameHistory`, `std::vector`, `std::set`, `std::string` |
| Dynamic Memory | `char*` array in `defuseWrongLetter()` function |
| File I/O | Load words from `data/words.txt`, save/load `history/game_history.txt` |
| Multiple Files | `main.cpp`, `game.cpp/h`, `fileio.cpp/h`, `history.cpp/h` |

## Non-Standard Libraries
None. Only standard C++ libraries used.

## Word List Source
Filtered from Google 10,000 most common English words dataset.

## Compilation & Execution

### Using Makefile:
\`\`\`bash
make
./hangman
\`\`\`

### Direct Compilation (without make):
\`\`\`bash
g++ -std=c++11 -o hangman src/main.cpp src/game.cpp src/fileio.cpp src/history.cpp
./hangman
\`\`\`

### Clean:
\`\`\`bash
make clean
make cleanall
\`\`\`
