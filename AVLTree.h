#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H

#endif //AVL_AVLTREE_H


//class for tree junctions
template <class ptr_type>
class AVLNode
{
public:
    ptr_type* data;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(ptr_type* data_to_copy) : data(data_to_copy), height(0), left(nullptr), right(nullptr) {}
    int get_bf()
    {
        return (left->height - right->height);
    }
};


//overall class for tree
template <class ptr_type, class condition>
class AVLTree
{
private:
    // - sub function for insert: adds a layer for passing root
    AVLNode<ptr_type>* insert2(AVLNode<ptr_type>*& r, ptr_type* data, AVLNode<ptr_type>*& r_new_junction);

    // - sub function for insert: balance the tree with proper rotations
    AVLNode<ptr_type>* balance_tree(AVLNode<ptr_type>*& r);

    // -- sub function for balance: makes an RR rotation
    AVLNode<ptr_type>* make_RR_rotation(AVLNode<ptr_type>*& r);

    // -- sub function for balance: makes an LL rotation
    AVLNode<ptr_type>* make_LL_rotation(AVLNode<ptr_type>*& r);

    // -- sub function for balance: makes an RL rotation
    AVLNode<ptr_type>* make_RL_rotation(AVLNode<ptr_type>*& r);

    // -- sub function for balance: makes an LR rotation
    AVLNode<ptr_type>* make_LR_rotation(AVLNode<ptr_type>*& r);

    // -- sub function for balance: calculates balance factor of junction
    int get_bf(AVLNode<ptr_type>*& r);

    // - sub function for insert: updates height of junction
    void update_height(AVLNode<ptr_type>*& r);

    // - sub function for remove: adds a layer for passing root
    void remove2(AVLNode<ptr_type>*& r, int key);

public:
    AVLNode<ptr_type>* root;

    // constructor
    AVLTree() : root(nullptr) {}

    // returns the height of the tree
    int get_tree_height();

    // returns a pointer to junction, if junction doesn't exist - returns nullptr
    AVLNode<ptr_type>* search(int value);

    // insert a new junction to the tree
    AVLNode<ptr_type>* insert(ptr_type* data);

    // removes the junction that points to data with key
    void remove(int key);

    // removes the junction that points to data and calls its destructor
    void remove_and_erase(int key);

    // calls for the destructor of the data pointed to at every junction
    void erase_data();

    // destructor for the tree - DOES NOT erase the data pointed to
    //~AVLTree();



};
