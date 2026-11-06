// card_list.cpp
// Author: David Gao
// Implementation of the classes defined in card_list.h
// The ordering least to greatest is: clubs, diamonds, spades, hearts


#include "card_list.h"

#include <iostream>
using std::cout;

Card_List(){                   // constructor
    root = nullptr;
}

~Card_List();                  // destructor


bool Card_List::insert(const Card& card){        // insert value; return false if duplicate
    if (!root){
        Node c(card);
        root = c;
        return true;
    }
    return recursiveInsert(card, root);
}
bool Card_List::recursiveInsert(const Card& card, Node* cur){
    if (card == cur){
        return false;
    }
    if (card < cur){
        if (!cur -> left){
            Node c(card);
            c -> parent = cur;
            cur -> left = c;
            return true;
        }
        return recursiveInsert(card, cur->left);
    }
    if (card > cur){
        if (!cur -> right){
            Node c(card);
            c -> parent = cur;
            cur -> right = c;
            return true;
        }
        return recursiveInsert(card, cur->right;)
    }
    return false;
}

bool Card_List::remove(const Card& card);
Iterator* begin();
Iterator* end();
Iterator* operator++();
Iterator* operator--();

void Card_List::clear(Node* n); // help destructor
static Node* leftmost(Node* n);
static Node* rightmost(Node* n);
static Node* predecessor(Node* n);
static Node* successor(Node* n);
        Iterator& operator++();
        Iterator& operator--();

bool contains(const Card& card) const;
void print() const;
Iterator begin() const;
Iterator end() const;
Iterator rbegin() const;
Iterator rend() const;
void playGame(Card_List& a, Card_List& b);

#endif