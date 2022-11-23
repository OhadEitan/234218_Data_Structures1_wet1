//
// Created by eitan on 21/11/2022.
//

#ifndef WET1_NODE_H
#define WET1_NODE_H


template<typename T>
class Node
{
    T* key_value; // the actual Node
    int height; // will be very helpful as we use in AVL
    Node<T>* left_child;
    Node<T>* right_child;

private:
    void insert(T key, Node<T>* leaf);
    Node<T>* search(T key, Node<T>* leaf);
    void destroy_tree(Node<T> *leaf);
    int calc_height(Node<T>* Node);
    T max(T a, T b);

};



#endif //WET1_NODE_H
