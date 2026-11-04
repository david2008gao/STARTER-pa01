// card.cpp
// Author: David Gao
// Implementation of the classes defined in card.h
// The ordering least to greatest is: clubs, diamonds, spades, hearts


#include "card.h"

#include <iostream>
#include <string>
using namespace std;

Card::Card(int s, int n) : suit(0), num(0){
    if (s == 'c' || s == 'C'){
        suit = 0;
    }
    if (s == 'd' || s == 'D'){
        suit = 1;
    }
    if (s == 's' || s == 'S'){
        suit = 2;
    }
    if (s == 'h' || s == 'H'){
        suit = 3;
    }

    num = n-'1';
    if (n == 'a' || n == 'A'){
        num = 0;
    }
    if (n == 10){
        num = 9;
    }
    if (n == 'j' || n == 'J'){
        num = 10;
    }
    if (n == 'q' || n == 'Q'){
        num = 11;
    }
    if (n == 'k' || n == 'K'){
        num = 12;
    }
}
int Card::getSuit() const{
    return suit;
}
int Card::getNum() const{
    return num;
}
bool Card::operator<(const Card& rhs) const{
    if (suit == rhs.suit) return num < rhs.num;
    return suit < rhs.suit;
}
bool Card::operator>(const Card& rhs) const{
    return rhs < *this;
}
bool Card::operator==(const Card& rhs) const{
    return (suit == rhs.suit && num == rhs.num);
}
std::ostream& operator<<(std::ostream& os, const Card& c){
    string suits[] = {"c", "d", "s", "h"};
    string nums[] = {"a", "2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k"};

    return os << suits[c.getSuit()] << " " << nums[c.getNum()];
}