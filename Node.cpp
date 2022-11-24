////
//// Created by eitan on 21/11/2022.
////
//
//#include "Node.h"
//
//template<class T, class K>
//void Node<T,K>::insert(T key, K value, Node<T,K> *leaf) {
//    if(key< leaf->key)
//    {
//        if(leaf->left_child!= nullptr)
//            insert(key, value, leaf->left_child); // recursive going to left tree
//        else
//        {
//            //found a place as someone left child
//            leaf->left_child=new Node<T,K>;
//            leaf->left_child->value=value;
//            leaf->left_child->key=key;
//            leaf->left_child->left_child=nullptr;    // left child of the node we inserted is null ptr
//            leaf->left_child->right_child=nullptr;   //right child of the node we inserted is null ptr
//
//        }
//    }
//    else if(key>leaf->key_value)
//    {
//        if(leaf->right_child!=nullptr)
//            insert(key, value, leaf->right_child); // recursive going to right tree
//        else
//        {
//            //found a place as someone right child
//            leaf->right_child=new Node<T,K>;
//            leaf->right_child->value=value;
//            leaf->right_child->key=key;
//            leaf->right_child->left_child=nullptr;  //Sets the left child of the child node to null
//            leaf->right_child->right_child=nullptr; //Sets the right child of the child node to null
//            leaf->right_child->height=0;
//        }
//    }
//}
//
//template<class T, class K>
//Node<T,K> *Node<T,K>::search(K key, Node<T,K> *leaf) {
//    if(leaf!= nullptr)
//    {
//        if(key==leaf->key_value)
//            return leaf;
//        if(key<leaf->key_value)
//            return search(key, leaf->left_child);
//        else
//            return search(key, leaf->right_child);
//    }
//        // if we are here key isn't in tree
//    return nullptr;
//}
//
//template<class T, class K>
//void Node<T,K>::destroy_tree(Node<T,K> *leaf) {
//    if(leaf!= nullptr)
//    {
//        destroy_tree(leaf->left);
//        destroy_tree(leaf->right);
//        delete leaf->key_value; // is that the right way?
//        delete leaf;
//    }
//}
//
//template<class T, class K>
//int Node<T,K>::calc_height(Node<T,K> *Node) {
//    if (Node == nullptr)
//        return 0;
//    return Node->height;
//}
//
//template<class T, class K>
//K Node<T,K>::max(K a, K b) {
//    return (a > b) ? a : b;
//}
//
//
//
//
