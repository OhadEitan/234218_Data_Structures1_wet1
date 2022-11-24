#ifndef BST_H
#define BST_H

#include <iostream>
template <class item>
class BST {

public:
    // ctor, dtor, insert and one print method already done in intbst.cpp:
    BST();                   // constructor
    ~BST();                  // destructor
    bool insert(item value);     // insert value; return false if duplicate
    void printPreOrder() const; // prints tree data pre-order to cout

    // 8 METHODS YOU MUST IMPLEMENT in intbst.cpp:
    void printInOrder() const;       // print tree data in-order to cout
    void printPostOrder() const;     // print tree data post-order to cout
    int sum() const;                 // sum of all values
    int count() const;               // count of values
    bool contains(item value) const;  // true if value is in tree

    // THESE ARE HARDER! DO THESE LAST
    item getPredecessor(item value) const;       // returns the predecessor value of the given value or 0 if there is none
    item getSuccessor(item value) const;         // returns the successor value of the given value or 0 if there is none
    bool remove(item value);                    // deletes the Node containing the given value from the tree

private:

    struct Node {
        item info;
        Node *left, *right, * parent;
        // useful constructor:
        Node(item v=0) : info(v), left(0), right(0), parent(0) { }
    };

    // just one instance variable (pointer to root node):
    Node *root;

    // recursive utility functions for use by public methods above
    Node* getNodeFor(item value, Node* n) const; // IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
    void clear(Node *n); // for destructor
    bool insert(item value, Node *n); // note overloading names for simplicity
    void printPreOrder(Node *n) const;
    void printInOrder(Node *n) const;
    void printPostOrder(Node *n) const;
    int sum(Node *n) const;
    int count(Node *n) const;
    Node* max(Node* n) const;
    Node* min(Node* n) const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(item value) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(item value) const; // returns the Node containing the predecessor of the given value 
};

#include "bst.cpp"
#endif