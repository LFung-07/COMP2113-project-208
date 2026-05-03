#include "game.h"
#include <iostream>
using namespace std;

Hangman::Hangman(const string& word, int maxWrong) {
  // input the secret word and max wrong attempts
  // output hangman display
  answer=word;
  maxwrong=maxWrong;
  wrong=0;
  game_end=false;
  win=false;
  vowels[0]='a';
  vowels[1]='e';
  vowels[2]='i';
  vowels[3]='o';
  vowels[4]='u';
  display="";
  for (size_t i=0; i<answer.length(); i++) {
    display+="_";
  }
}
  
bool Hangman::guessLetter(char letter) {
  // input player's guess
  // output true if letter found in word, false if wrong guess
  letter=tolower(letter);
  // check if letter already being guessed
  if (guessed_char.find(letter) != guessed_char.end()) {
    cout << "You have already guessed '" << letter << "'!" << endl;
    return false;
  }
  // add to list of guessed letters
  guessed_char.insert(letter);
  // check if letter is in answer
  bool found=false;
  for (size_t i=0; i<answer.length(); i++) {
    if (answer[i]==letter) {
      display[i]=letter;
      found=true;
    }
  }
  if (found==false) {
    wrong_char.insert(letter);
    wrong++;
  }
  // lose
  if (wrong>=maxwrong) {
    game_end=true;
    win=false;
  }
  // win
  if (display==answer) {
    game_end=true;
    win=true;
  }
  return found;
}

bool Hangman::isWin() const {
  // output true if player has won
  return win;
}

bool Hangman::isGameOver() const {
  // output true if game has ended
  return game_end;
}

string Hangman::getDisplayedWord() const {
  // output display
  string result;
  for (size_t i=0; i<display.length();i++) {
    result+=display[i];
    if (i<display.length()-1) {
      result+=' ';
    }
  }
  return result;
}

string Hangman::getGuessedLetters() const {
  // output guessed letters in display
  string result;
  for (set<char>::iterator it=guessed_char.begin(); it!=guessed_char.end(); ++it) {
    result+=*it;
    result+=' ';
  }
  return result;
}

string Hangman::getSecretWord() const {
  // output the answer
  return answer;
}

int Hangman::getRemainingGuesses() const{
  // output guesses remaining
  return maxwrong-wrong;
}

int Hangman::getMaxGuesses() const{
  // output max wrong attempts allowed 
  return maxwrong;
}

int Hangman::getUnguessedVowelCount() const {
  // output number of unguessed vowels
  int count=0;
  for (size_t i=0; i<answer.length(); i++) {
    char c=answer[i];
    //check if letter is a vowel
    bool isVowel=false;
    for (int v=0;v<5;v++) {
      if (c==vowels[v]) {
        isVowel=true;
        break;
      }
    }
    // count number of ungussed vowels
    if (isVowel==true && guessed_char.find(c)==guessed_char.end()) {
      count++;
    }
  }
  return count;
}

char Hangman::defuseWrongLetter() {
    // output defused letter
    char* candidates;
    candidates=new char[26];
    int candidateCount=0;
    for (char c='a'; c<='z'; c++) {
      bool inSecret=false;
      //find unguessed and wrong letters
      for (size_t i=0; i<answer.length();i++) {
        if (answer[i]==c) {
          inSecret=true;
          break;
          }
      }
      if (inSecret==false && guessed_char.find(c)==guessed_char.end()) {
      candidates[candidateCount]=c;
      candidateCount++;
      }
  }
  char defused='\0';
  if (candidateCount>0) {
    // defuse a random letter
    int randomIndex=rand()%candidateCount;
    defused=candidates[randomIndex];
    // add that letter to the guessed list
    guessed_char.insert(defused);
    wrong_char.insert(defused);
  }
  delete[] candidates;
  return defused;
}

  
