//
// Created by eitan on 21/11/2022.
//

#include "AVL_Tree.h"

template<typename T>
int AVL_Tree<T>::getBalanceFactor(Node<T> *node) {
    if (node == nullptr)
        return 0;
    return  Node<T>::calc_height(node->left_child)
        - Node<T>::calc_height(node->right_child);
}

// gilgul yamin
// using names from tutorial
template<typename T>
Node<T>* AVL_Tree<T>::right_rotate(Node<T>* B) {
    Node<T>* A = B->right_child;
    Node<T>* A_l =  A->left_child; // stay as he is we wont touch him
    Node<T>* A_r =  A->right_child;
    // now the gilgul
    A->right_child = B;
    B->right_child = A_r;
    A->height = Node<T>::max(Node<T>::calc_height(A->left_child),
                             Node<T>::calc_height(A->right_child)) + 1;
    B->height = Node<T>::max(Node<T>::calc_height(B->left_child),
                             Node<T>::calc_height(B->right_child)) + 1;
    return A;
}

// gilgul 0mall
// using names from tutorial
template<typename T>
Node<T>* AVL_Tree<T>::left_rotate(Node<T>* A) {
    Node<T>* B = A->right_child;
    Node<T>* B_l = B->left_child;
    Node<T>* B_r = B->right_child;
    // now the gilgul
    B->right_child = A;
    A->right_child= B_l;
    A->height = Node<T>::max(Node<T>::calc_height(A->left_child),
                             Node<T>::calc_height(A->right_child)) + 1;
    B->height = Node<T>::max(Node<T>::calc_height(B->left_child),
                             Node<T>::calc_height(B->right_child)) + 1;
    return B;
}



