//
// Created by eitan on 21/11/2022.
//

#include "Node.h"

template<typename T>
void Node<T>::insert(T key, Node<T> *leaf) {
    if(key< leaf->key_value)
    {
        if(leaf->left_child!= nullptr)
            insert(key, leaf->left_child); // recursive going to left tree
        else
        {
            //found a place as someone left child
            leaf->left_child=new Node<T>;
            leaf->left_child->key_value=key;
            leaf->left_child->left_child=nullptr;    // left child of the node we inserted is null ptr
            leaf->left_child->right_child=nullptr;   //right child of the node we inserted is null ptr

        }
    }
    else if(key>leaf->key_value)
    {
        if(leaf->right_child!=nullptr)
            insert(key, leaf->right_child); // recursive going to right tree
        else
        {
            //found a place as someone right child
            leaf->right_child=new Node<T>;
            leaf->right_child->key_value=key;
            leaf->right_child->left_child=nullptr;  //Sets the left child of the child node to null
            leaf->right_child->right_child=nullptr; //Sets the right child of the child node to null
            leaf->right_child->height=0;
        }
    }
}

template<typename T>
Node<T> *Node<T>::search(T key, Node<T> *leaf) {
    if(leaf!= nullptr)
    {
        if(key==leaf->key_value)
            return leaf;
        if(key<leaf->key_value)
            return search(key, leaf->left_child);
        else
            return search(key, leaf->right_child);
    }
        // if we are here key isn't in tree
    return nullptr;
}

template<typename T>
void Node<T>::destroy_tree(Node<T> *leaf) {
    if(leaf!= nullptr)
    {
        destroy_tree(leaf->left);
        destroy_tree(leaf->right);
        delete leaf->key_value; // is that the right way?
        delete leaf;
    }
}

template<typename T>
int Node<T>::calc_height(Node<T> *Node) {
    if (Node == nullptr)
        return 0;
    return Node->height;
}

template<typename T>
T Node<T>::max(T a, T b) {
    return (a > b) ? a : b;
}




