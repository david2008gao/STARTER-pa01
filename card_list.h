// card_list.h
// Author: David Gao
// All class declarations related to defining a BST that represents a player's hand
// The ordering least to greatest is: clubs, diamonds, spades, hearts

#ifndef CARD_LIST_H
#define CARD_LIST_H

class Card_List {

 public:
    Card_List();                   // constructor
    ~Card_List();                  // destructor
    bool insert(Card card);     // insert value; return false if duplicate
    bool remove(Card card);
    Card* begin();
    Card* end();
    Card* operator++();
    Card* operator--();

 private:

    struct Node {
    Card card;
	Node *left, *right, * parent;
	// useful constructor:
    Card (Card c = 0) : card(c), left(0), right(0), parent(0) { }
    
};

#endif