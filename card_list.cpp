// card_list.cpp
// Author: David Gao
// Implementation of the classes defined in card_list.h
// The ordering least to greatest is: clubs, diamonds, spades, hearts


#include "card_list.h"

#include <iostream>
using std::cout;

Card_List::Card_List(){                   // constructor
    root = nullptr;
}

Card_List::~Card_List(){                  // destructor
    if (root) clear(root);
}
void Card_List::clear(Node* n){ // help destructor
    if (n->left) clear(n->left);
    if (n->right) clear(n->right);
    delete n;
}


bool Card_List::insert(const Card& card){        // insert value; return false if duplicate
    if (!root){
        Node* c = new Node(card);
        root = c;
        return true;
    }
    return recursiveInsert(card, root);
}
bool Card_List::recursiveInsert(const Card& card, Node* cur){
    if (card == cur->card){
        return false;
    }
    if (card < cur->card){
        if (!cur -> left){
            Node* c = new Node(card);
            c -> parent = cur;
            cur -> left = c;
            return true;
        }
        return recursiveInsert(card, cur->left);
    }
    if (card > cur->card){
        if (!cur -> right){
            Node* c = new Node(card);
            c -> parent = cur;
            cur -> right = c;
            return true;
        }
        return recursiveInsert(card, cur->right);
    }
    return false;
}

bool Card_List::remove(const Card& card);
Card_List::Node* Card_List::leftmost(Node* n);
Card_List::Node* Card_List::rightmost(Node* n);
Card_List::Node* Card_List::predecessor(Node* n);
Card_List::Node* Card_List::successor(Node* n);
Card_List::Iterator& Card_List::Iterator::operator++();
Card_List::Iterator& Card_List::Iterator::operator--();

bool Card_List::contains(const Card& card) const;
void Card_List::print() const;
Card_List::Iterator Card_List::begin() const;
Card_List::Iterator Card_List::end() const;
Card_List::Iterator Card_List::rbegin() const;
Card_List::Iterator Card_List::rend() const;
void playGame(Card_List& a, Card_List& b);
