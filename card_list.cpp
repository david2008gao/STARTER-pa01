// card_list.cpp
// Author: David Gao
// Implementation of the classes defined in card_list.h
// The ordering least to greatest is: clubs, diamonds, spades, hearts


#include "card_list.h"

#include <iostream>
using namespace std;

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

bool Card_List::contains(const Card& card) const{
    return recursiveContains(card, root);
}
bool Card_List::recursiveContains(const Card& card, const Node* n) const{
    if (!n) return false;
    if (card == n->card) return true;
    if (card > n->card) return recursiveContains(card, n->right);
    if (card < n->card) return recursiveContains(card, n->left);
    return false;
}

Card_List::Node* Card_List::find(const Card& card) const{
    return recursiveFind(card, root);
}
Card_List::Node* Card_List::recursiveFind(const Card& card, Node* n) const{
    if (!n) return nullptr;
    if (card == n->card) return n;
    if (card > n->card) return recursiveFind(card, n->right);
    if (card < n->card) return recursiveFind(card, n->left);
    return nullptr;
}

void Card_List::print(std::ostream& os) const{
    for (Iterator it = begin(); it != end(); ++it){
        os << *it << endl;
    }
}

bool Card_List::remove(const Card& card){
    Node* curr = find(card);
    if (!curr) return false;
    if (curr == root){
        Node* leftNode = curr->left;
        Node* rightNode = curr->right;
        delete curr;
        if (!leftNode){
            root = rightNode;
            if (rightNode) rightNode -> parent = NULL;
            return true;
        }
        root = leftNode;
        leftNode -> parent = NULL;
        if (rightNode){
            while(leftNode->right){
                leftNode = leftNode->right;
            }
            leftNode->right = rightNode;
            rightNode->parent = leftNode;
        }
        return true;
    }
    Node* prev = curr->parent;
    if (prev && prev->left && prev->left == curr){
        if (curr -> left && curr -> right){
            Node* rightNode = curr->right;
            Node* temp = curr;
            curr = curr->left;
            delete temp;
            prev->left = curr;
            curr->parent = prev;
            while (curr -> right){
                curr = curr -> right;
            }
            curr -> right = rightNode;
            rightNode -> parent = curr;
            return true;
        }
        if (curr -> left){
            Node* temp = curr->left;
            prev->left = temp;
            temp->parent = prev;
            delete curr;
            return true;
        }
        if (curr -> right){
            Node* temp = curr->right;
            prev->left = temp;
            temp->parent = prev;
            delete curr;
            return true;
        }
        prev->left = NULL;
        delete curr;
        return true;
    }
    if (prev && prev->right && prev->right == curr){
        if (curr -> left && curr -> right){
            Node* rightNode = curr->right;
            Node* temp = curr;
            curr = curr->left;
            delete temp;
            prev->right = curr;
            curr->parent = prev;
            while (curr -> right){
                curr = curr -> right;
            }
            curr -> right = rightNode;
            rightNode -> parent = curr;
            return true;
        }
        if (curr -> left){
            Node* temp = curr->left;
            prev->right = temp;
            temp->parent = prev;
            delete curr;
            return true;
        }
        if (curr -> right){
            Node* temp = curr->right;
            prev->right = temp;
            temp->parent = prev;
            delete curr;
            return true;
        }
        prev -> right = NULL;
        delete curr;
        return true;
    }
    return false;
}
Card_List::Node* Card_List::leftmost(Node* n){
    if (!n || !n->left) return n;
    return leftmost(n->left);
}
Card_List::Node* Card_List::rightmost(Node* n){
    if (!n || !n->right) return n;
    return rightmost(n->right);
}
Card_List::Node* Card_List::predecessor(Node* n){
    Node* curr = n;
    if (!curr) return nullptr;
    if (curr->left){
        curr = curr->left;
        while (curr->right){
            curr = curr -> right;
        }
        return curr;
    }
    curr = n;
    Node* prev = curr->parent;
    while(prev){
        if (prev->right == curr) return prev;
        curr = prev;
        prev = prev->parent;
    }
    return nullptr;
}
Card_List::Node* Card_List::successor(Node* n){
    Node* curr = n;
    if (!curr) return nullptr;
    if (curr->right){
        curr = curr->right;
        while (curr->left){
            curr = curr -> left;
        }
        return curr;
    }
    curr = n;
    Node* prev = curr->parent;
    while(prev){
        if (prev->left == curr) return prev;
        curr = prev;
        prev = prev->parent;
    }
    return nullptr;
}
Card_List::Iterator& Card_List::Iterator::operator++(){
    if (curr) curr = successor(curr);
    return *this;
}
Card_List::Iterator& Card_List::Iterator::operator--(){
    if (curr) curr = predecessor(curr);
    return *this;
}
Card_List::Iterator Card_List::begin() const{
    return Iterator(leftmost(root));
}
Card_List::Iterator Card_List::end() const{
    return nullptr;
}
Card_List::Iterator Card_List::rbegin() const{
    return Iterator(rightmost(root));
}
Card_List::Iterator Card_List::rend() const{
    return nullptr;
}
void playGame(Card_List& alice, Card_List& bob){
    bool found = true;
    while (found){
        found = false;
        for (auto it = alice.begin(); it != alice.end(); ++it){
            Card c = *it;
            if (bob.contains(c)){
                cout << "Alice picked matching card " << c << endl;
                alice.remove(c);
                bob.remove(c);
                found = true;
                break;
            }
        }
        
        if (!found){
        break;
        }
        found = false;

        for (auto it = bob.rbegin(); it != bob.rend(); --it){
            if (alice.contains(*it)){
                Card c = *it;
                cout << "Bob picked matching card " << c << endl;
                alice.remove(c);
                bob.remove(c);
                found = true;
                break;
            }
        }
    }

    cout << endl << "Alice's cards:" << endl;
    for (auto it = alice.begin(); it != alice.end(); ++it){
        cout << *it << endl;
    }
    cout << endl << "Bob's cards:" << endl;
    for (auto it = bob.begin(); it != bob.end(); ++it){
        cout << *it << endl;
  }
}
