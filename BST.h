//
// Created by eitan on 21/11/2022.
//
#include "Node.h"
#ifndef WET1_BST_H
#define WET1_BST_H

// Binary search tree - shortcut will be BST
template<typename T>
class BST {

private:
    Node<T>* root; // root is the head of the tree
public:
    BST();
    ~BST();
    virtual void insert(T key);
    Node<T>* search(T key);
    void destroy_tree();
};




#endif //WET1_BST_H
