// card.h
// Author: David Gao
// All class declarations related to defining a single card go here
// The ordering least to greatest is: clubs, diamonds, spades, hearts

#ifndef CARD_H
#define CARD_H
#include <iostream>

class Card {

 public:
    Card(int s, int n);
    int getSuit() const;
    int getNum() const;
    bool operator<(const Card& rhs) const;
    bool operator>(const Card& rhs) const;
    bool operator==(const Card& rhs) const;

 private:

    int suit;
	int num;
};

std::ostream& operator<<(std::ostream& os, const Card& c);

#endif