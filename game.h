#ifndef GAME_H
#define GAME_H
#include <set>
#include <string>
using namespace std;

class Hangman {
private:
  string answer;            // this is the word that the player guesses
  string display;           // this is to display the current progress
  set<char> guessed_char;   // this is to store all characters guessed by the player
  set<char> wrong_char;     // this is to store all wrong charcters
  int wrong;                // this is to count the number of wrong guesses
  int attempts;             // this is to store the maximum number of wrong guesses the player can make
  bool game_end;            // this is to see whether the game has ended
  bool win;                 // this is to see whether the player wins
  char vowels[5];           // this is store an array of vowels

public:
  Hangman(const string& answer, int attempts);
  bool guessLetter(char letter);
  bool isGameOver() const;
  bool isWin() const;
  string getDisplayedWord() const;
  string getGuessedLetters() const;
  string getSecretWord() const;
  int getRemainingGuesses() const;
  int getMaxGuesses() const;
  int getUnguessedVowelCount() const;
  char defuseWrongLetter();
};
#endif
