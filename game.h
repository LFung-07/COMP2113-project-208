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
  Hangman(const string& word, int maxWrong);  // this is to run a new game
  bool guessLetter(char letter);                // this is to check if the guessed character is in the answer
  bool isGameOver() const;                      // this is to return if the game has ended
  bool isWin() const;                           // this is to return if a player wins 
  string getDisplayedWord() const;              // this is to return the display of current progress
  string getGuessedLetters() const;             // this is to return all guessed characters
  string getSecretWord() const;                 // this is to return the answer after the game
  int getRemainingGuesses() const;              // this is to return the number of attempts left
  int getMaxGuesses() const;                    // this is to return the maximum attempts the player has
  int getUnguessedVowelCount() const;           // this is to show the number of unguessed vowels in the word [random event]
  char defuseWrongLetter();                     // this is to eliminate one wrong and unguessed letter [random event]
};
#endif
