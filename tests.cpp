// tests.cpp
// Simple tests for Card_List, its Iterator, and playGame.
// Memory check: valgrind --leak-check=full ./tests

#include <iostream>
#include <sstream>
#include <string>
#include "card.h"
#include "card_list.h"

using namespace std;

int total = 0;
int passed = 0;

// Records each test result
void check(bool success, string name) {
    total++;
    if (success) {
        passed++;
    } else {
        cout << "FAIL: " << name << endl;
    }
}

// Whole list as text, smallest to largest
string forward(const Card_List& list) {
    string result = "";
    for (Card_List::Iterator it = list.begin(); it != list.end(); ++it) {
        if (result != "") result += ",";
        ostringstream out;
        out << *it;
        result += out.str();
    }
    return result;
}

// Whole list as text, largest to smallest
string backward(const Card_List& list) {
    string result = "";
    for (Card_List::Iterator it = list.rbegin(); it != list.rend(); --it) {
        if (result != "") result += ",";
        ostringstream out;
        out << *it;
        result += out.str();
    }
    return result;
}

// Gets what print() writes as a string
string printToString(const Card_List& list) {
    ostringstream out;
    list.print(out);
    return out.str();
}

int main() {

    // .insert

    // 1. insert into empty tree
    Card_List list_insert1;
    check(list_insert1.insert(Card('c', 'a')) == true, "insert 1: returns true");
    check(forward(list_insert1) == "c a", "insert 1: card is in the tree");

    // 2. duplicate is rejected
    Card_List list_insert2;
    list_insert2.insert(Card('d', '3'));
    check(list_insert2.insert(Card('d', '3')) == false, "insert 2: duplicate returns false");
    check(forward(list_insert2) == "d 3", "insert 2: only one copy");

    // 3. random order ends up sorted
    Card_List list_insert3;
    list_insert3.insert(Card('h', '9'));
    list_insert3.insert(Card('c', 'k'));
    list_insert3.insert(Card('s', '3'));
    list_insert3.insert(Card('c', 'a'));
    check(forward(list_insert3) == "c a,c k,s 3,h 9", "insert 3: sorted order");

    // 4. inserting in increasing order
    Card_List list_insert4;
    list_insert4.insert(Card('c', 'a'));
    list_insert4.insert(Card('c', '2'));
    list_insert4.insert(Card('d', '3'));
    check(forward(list_insert4) == "c a,c 2,d 3", "insert 4: increasing order");

    // 5. inserting in decreasing order, including a 10
    Card_List list_insert5;
    list_insert5.insert(Card('h', 'k'));
    list_insert5.insert(Card('h', 10));
    list_insert5.insert(Card('h', '9'));
    check(forward(list_insert5) == "h 9,h 10,h k", "insert 5: decreasing order with 10");


    // .remove

    // 1. remove from empty tree
    Card_List list_remove1;
    check(list_remove1.remove(Card('c', 'a')) == false, "remove 1: empty tree returns false");

    // 2. remove the only node
    Card_List list_remove2;
    list_remove2.insert(Card('s', '5'));
    check(list_remove2.remove(Card('s', '5')) == true, "remove 2: returns true");
    check(list_remove2.begin() == list_remove2.end(), "remove 2: tree is empty");

    // 3. remove a leaf (also a card that is not in the tree)
    Card_List list_remove3;
    list_remove3.insert(Card('d', '5'));
    list_remove3.insert(Card('c', '3'));
    list_remove3.insert(Card('s', '2'));
    check(list_remove3.remove(Card('h', 'k')) == false, "remove 3: missing card returns false");
    check(list_remove3.remove(Card('s', '2')) == true, "remove 3: leaf removed");
    check(forward(list_remove3) == "c 3,d 5", "remove 3: rest is unchanged");

    // 4. remove a node with one child
    Card_List list_remove4;
    list_remove4.insert(Card('d', '5'));
    list_remove4.insert(Card('c', '3'));
    list_remove4.insert(Card('c', '4'));
    list_remove4.remove(Card('c', '3'));
    check(forward(list_remove4) == "c 4,d 5", "remove 4: forward order");
    check(backward(list_remove4) == "d 5,c 4", "remove 4: backward order");

    // 5. remove a node with two children (here the root)
    Card_List list_remove5;
    list_remove5.insert(Card('d', '5'));
    list_remove5.insert(Card('c', '3'));
    list_remove5.insert(Card('s', '9'));
    list_remove5.remove(Card('d', '5'));
    check(forward(list_remove5) == "c 3,s 9", "remove 5: forward order");
    check(backward(list_remove5) == "s 9,c 3", "remove 5: backward order");

    // .contains

    // 1. empty tree
    Card_List list_contains1;
    check(list_contains1.contains(Card('c', 'a')) == false, "contains 1: empty tree");

    // 2. single node
    Card_List list_contains2;
    list_contains2.insert(Card('h', 10));
    check(list_contains2.contains(Card('h', 10)) == true, "contains 2: card is there");

    // 3. several nodes
    Card_List list_contains3;
    list_contains3.insert(Card('d', '5'));
    list_contains3.insert(Card('c', 'k'));
    list_contains3.insert(Card('s', 'a'));
    check(list_contains3.contains(Card('d', '5')), "contains 3: d 5");
    check(list_contains3.contains(Card('c', 'k')), "contains 3: c k");
    check(list_contains3.contains(Card('s', 'a')), "contains 3: s a");

    // 4. same number, different suit
    Card_List list_contains4;
    list_contains4.insert(Card('c', '3'));
    check(list_contains4.contains(Card('d', '3')) == false, "contains 4: other suit is not found");

    // 5. after removing
    Card_List list_contains5;
    list_contains5.insert(Card('c', '3'));
    list_contains5.insert(Card('d', '3'));
    list_contains5.remove(Card('c', '3'));
    check(list_contains5.contains(Card('c', '3')) == false, "contains 5: removed card is gone");
    check(list_contains5.contains(Card('d', '3')) == true, "contains 5: other card remains");

    // .print

    // 1. empty tree prints nothing
    Card_List list_print1;
    check(printToString(list_print1) == "", "print 1: empty");

    // 2. one card
    Card_List list_print2;
    list_print2.insert(Card('c', 'a'));
    check(printToString(list_print2) == "c a\n", "print 2: one card");

    // 3. several cards in order
    Card_List list_print3;
    list_print3.insert(Card('h', '3'));
    list_print3.insert(Card('s', '5'));
    list_print3.insert(Card('c', 'a'));
    check(printToString(list_print3) == "c a\ns 5\nh 3\n", "print 3: several cards");

    // 4. after a removal
    Card_List list_print4;
    list_print4.insert(Card('c', 'a'));
    list_print4.insert(Card('d', 'j'));
    list_print4.insert(Card('h', '2'));
    list_print4.remove(Card('d', 'j'));
    check(printToString(list_print4) == "c a\nh 2\n", "print 4: after remove");

    // 5. the value 10 prints as two characters
    Card_List list_print5;
    list_print5.insert(Card('h', 10));
    list_print5.insert(Card('h', '9'));
    check(printToString(list_print5) == "h 9\nh 10\n", "print 5: ten");

    // Iterator

    // 1. empty tree
    Card_List list_iter1;
    check(list_iter1.begin() == list_iter1.end(), "iterator 1: begin == end");
    check(list_iter1.rbegin() == list_iter1.rend(), "iterator 1: rbegin == rend");

    // 2. single node
    Card_List list_iter2;
    list_iter2.insert(Card('s', '7'));
    Card_List::Iterator it2 = list_iter2.begin();
    check(*it2 == Card('s', '7'), "iterator 2: begin is the card");
    ++it2;
    check(it2 == list_iter2.end(), "iterator 2: ++ reaches end");
    Card_List::Iterator rit2 = list_iter2.rbegin();
    check(*rit2 == Card('s', '7'), "iterator 2: rbegin is the card");
    --rit2;
    check(rit2 == list_iter2.rend(), "iterator 2: -- reaches rend");

    // 3. several nodes, both directions
    Card_List list_iter3;
    list_iter3.insert(Card('d', '5'));
    list_iter3.insert(Card('c', 'k'));
    list_iter3.insert(Card('h', '2'));
    list_iter3.insert(Card('c', 'a'));
    check(forward(list_iter3) == "c a,c k,d 5,h 2", "iterator 3: forward");
    check(backward(list_iter3) == "h 2,d 5,c k,c a", "iterator 3: backward");

    // 4. going past the ends is safe
    Card_List list_iter4;
    list_iter4.insert(Card('c', 'a'));
    Card_List::Iterator it4 = list_iter4.begin();
    ++it4;
    ++it4;
    ++it4;
    check(it4 == list_iter4.end(), "iterator 4: ++ past end stays at end");
    Card_List::Iterator rit4 = list_iter4.rbegin();
    --rit4;
    --rit4;
    --rit4;
    check(rit4 == list_iter4.rend(), "iterator 4: -- past rend stays at rend");

    // 5. comparing iterators
    Card_List list_iter5;
    list_iter5.insert(Card('c', 'a'));
    list_iter5.insert(Card('d', '2'));
    Card_List::Iterator a5 = list_iter5.begin();
    Card_List::Iterator b5 = list_iter5.begin();
    check(a5 == b5, "iterator 5: same position is ==");
    check(!(a5 != b5), "iterator 5: same position is not !=");
    ++b5;
    check(a5 != b5, "iterator 5: different position is !=");
    check(!(a5 == b5), "iterator 5: different position is not ==");

    // playGame
    // only checking results of playGame

    // 1. both players have common cards
    Card_List alice_game1;
    Card_List bob_game1;
    alice_game1.insert(Card('c', 'a'));
    alice_game1.insert(Card('c', '3'));
    alice_game1.insert(Card('h', '2'));
    bob_game1.insert(Card('c', '3'));
    bob_game1.insert(Card('h', '2'));
    bob_game1.insert(Card('s', '4'));
    playGame(alice_game1, bob_game1);
    check(forward(alice_game1) == "c a", "playGame 1: alice's hand");
    check(forward(bob_game1) == "s 4", "playGame 1: bob's hand");

    // 2. one empty hand
    Card_List alice_game2;
    Card_List bob_game2;
    bob_game2.insert(Card('c', 'a'));
    bob_game2.insert(Card('h', 'k'));
    playGame(alice_game2, bob_game2);
    check(alice_game2.begin() == alice_game2.end(), "playGame 2: alice still empty");
    check(forward(bob_game2) == "c a,h k", "playGame 2: bob unchanged");

    // 3. no common cards
    Card_List alice_game3;
    Card_List bob_game3;
    alice_game3.insert(Card('c', 'a'));
    alice_game3.insert(Card('d', '2'));
    bob_game3.insert(Card('s', '3'));
    bob_game3.insert(Card('h', '4'));
    playGame(alice_game3, bob_game3);
    check(forward(alice_game3) == "c a,d 2", "playGame 3: alice unchanged");
    check(forward(bob_game3) == "s 3,h 4", "playGame 3: bob unchanged");

    cout << passed << " of " << total << " checks passed" << endl;
    return 0;
}