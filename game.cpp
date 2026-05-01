#include "game.h"
#include <iostream>
using namespace std;

Hangman::Hangman(const string& word, int maxWrong) {
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
  letter=tolower(letter);
  if (guessed_char.find(letter) != guessed_char.end()) {
    cout << "You have already guessed '" << letter << "'!" << endl;
    return false;
  }
  guessed_char.insert(letter);
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
  if (wrong>=maxwrong) {
    game_end=true;
    win=false;
  }
  if (display==answer) {
    game_end=true;
    win=true;
  }
  return found;
}

bool Hangman::isWin() const {
  return win;
}

bool Hangman::isgame_end() const {
  return game_end;
}

string Hangman::getdisplay() const {
  string result;
  for (size_t i=0; i<display.length();i++) {
    result+=display[i];
    if (i<display.length()-1) {
      result+=' ';
    }
  }
  return result;
}

string Hangman::getguessed_char() const {
  string result;
  for (set<char>::iterator it=guessed_char.begin(); it!=guessed_char.end(); ++it) {
    result+=*it;
    result+=' ';
  }
  return result;
}

string Hangman::getanswer() const {
  return answer;
}

int Hangman::getRemainingGuesses() const{
  return maxwrong-wrong;
}

int Hangman::getMaxGuesses() const{
  return maxwrong;
}

int Hangman::getUnguessedVowelCount() const {
  int count=0;
  for (size_t i=0; i<answer.length(); i++) {
    char c=answer[i];
    bool isVowel=false;
    for (int v=0;v<5;v++) {
      if (c==vowels[v]) {
        isVowel=true;
        break;
      }
    }
    if (isVowel==true && guessed_char.find(c)==guessed_char.end()) {
      count++;
    }
  }
  return count;
}

char Hangman::defuseWrongLetter() {
    char* candidates;
    candidates=new char[26];
    int candidateCount=0;
    for (char c='a'; c<='z'; c++) {
      bool inSecret=false;
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
    int randomIndex=rand()%candidateCount;
    defused=candidates[randomIndex];
    guessed_char.insert(defused);
    wrong_char.insert(defused);
  }
  delete[] candidates;
  return defused;
}

  
