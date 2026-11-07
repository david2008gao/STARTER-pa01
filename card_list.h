// card_list.h
// Author: David Gao
// All class declarations related to defining a BST that represents a player's hand
// The ordering least to greatest is: clubs, diamonds, spades, hearts

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"

class Card_List {

 private:
    struct Node {
        Card card;
        Node *left, *right, *parent;
        // useful constructor:
        Node (const Card& c) : card(c), left(0), right(0), parent(0) { }
    };
    Node* root;
    void clear(Node* n); // help destructor
    bool recursiveInsert(const Card& card, Node* cur); // help insert
    bool recursiveContains(const Card& card, const Node* n) const;
    Node* find(const Card& card) const;
    Node* recursiveFind(const Card& card, Node* n) const;
    static Node* leftmost(Node* n);
    static Node* rightmost(Node* n);
    static Node* predecessor(Node* n);
    static Node* successor(Node* n);

 public:
    Card_List();                   // constructor
    ~Card_List();                  // destructor
    class Iterator {
        private:
            Node* curr;
        public:
            Iterator(Node* n = nullptr) : curr(n) {}
            const Card& operator*() const { return curr->card; }
            const Card* operator->() const { return &(curr->card); }
            Iterator& operator++();
            Iterator& operator--();
            bool operator==(const Iterator& other) const { return curr == other.curr; }
            bool operator!=(const Iterator& other) const { return curr != other.curr; }
    };
    
    bool insert(const Card& card);     // insert value; return false if duplicate
    bool remove(const Card& card);
    bool contains(const Card& card) const;
    void print(std::ostream& os = std::cout) const;
    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};
void playGame(Card_List& a, Card_List& b);

#endif