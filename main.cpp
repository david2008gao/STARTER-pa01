// This file should implement the game using a custom implementation of a BST (based on your earlier BST implementation)
#include <iostream>
#include <fstream>
#include <string>
#include "card.h"
#include "card_list.h"
//Do not include set in this file

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;
  char suit;
  char num;
  Card_List alice;
  Card_List bob;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    suit = line[0];
    num = line[2];
    if (line.size() >= 4 && line[3] == '0'){ //value is ten
      Card c(suit, 10);
      alice.insert(c);
    }
    else{
      Card c(suit, num);
      alice.insert(c);
    }
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    suit = line[0];
    num = line[2];
    if (line.size() >= 4 && line[3] == '0'){ //value is ten
      Card c(suit, 10);
      bob.insert(c);
    }
    else{
      Card c(suit, num);
      bob.insert(c);
    }
  }
  cardFile2.close();
  
  //game start
  playGame(alice, bob);
  return 0;
}
