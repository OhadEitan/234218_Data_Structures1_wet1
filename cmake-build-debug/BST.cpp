//
// Created by eitan on 21/11/2022.
//

#include "BST.h"

template<typename T>
BST<T>::BST() : root(nullptr){}


template<typename T>
BST<T>::~BST()
{
    destroy_tree();
}

template<typename T>
void BST<T>::insert(T key) {
    if(root!= nullptr)
        // if our tree contains at least one node and not empty
        insert(key, root);
    else{
        // tree is empty we have only null ptr to root
        root=new Node<T>;
        root->key_value=key;
        root->left_child=nullptr;
        root->right_child=nullptr;
       // root->height =0; // maybe should be 1
    }
}

template<typename T>
Node<T>* BST<T>::search(T key) {
    return Node<T>::search(key, root);
}

template<typename T>
void BST<T>::destroy_tree() {
    Node<T>::destroy_tree(root);
}
