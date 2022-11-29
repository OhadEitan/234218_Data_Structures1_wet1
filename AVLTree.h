#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H

#endif //AVL_AVLTREE_H


// Player class for example - TO DELETE
class Player
{
public:
    int id;
    Player(int id) : id(id) {}
};

// enum class for tree condition
enum class Comparison
{
    GREATER_THAN,
    EQUAL,
    LESS_THAN
};


// condition for players tree
class wc_players_Condition
{
public:
    Comparison operator()(Player* a, Player* b)
    {
        if (a->id < b->id)
        {
            return Comparison::LESS_THAN;
        }
        if (a->id > b->id)
        {
            return Comparison::GREATER_THAN;
        }
        return Comparison::EQUAL;
    }
};


//class for tree nodes
template <class ptr_type>
class AVLNode
{
public:
    ptr_type* data;
    int height;
    AVLNode* left;
    AVLNode* right;
    AVLNode(ptr_type* data_to_copy) : data(data_to_copy), height(0), left(nullptr), right(nullptr) {}
};


//overall class for AVL tree
template <class ptr_type, class condition>
class AVLTree
{
private:
    // - sub function for insert: adds a layer for passing root
    AVLNode<ptr_type>* insert_node(AVLNode<ptr_type>*& r, ptr_type* data, AVLNode<ptr_type>*& r_new_junction);

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

    // -- sub function for balance: calculates balance factor of node
    int get_bf(AVLNode<ptr_type>*& r);

    // - sub function for insert: updates height of node
    void update_height(AVLNode<ptr_type>*& r);

    // - sub function for remove: adds a layer for passing root and result of operation
    AVLNode<ptr_type>* remove_node(AVLNode<ptr_type>*& r, ptr_type* data, bool*& result, bool erase);

    // - sub function for remove: finds a successor for removed node
    AVLNode<ptr_type>* find_successor(AVLNode<ptr_type>* b);

    // - sub function for search: adds a layer for passing root and result of operation
    AVLNode<ptr_type>* search_node(AVLNode<ptr_type>*& r, ptr_type* data, AVLNode<ptr_type>*& requested);

    // - sub function for search: adds a layer for passing root and result of operation
    void erase_data_in_node(AVLNode<ptr_type>*& r);

    // - sub function for destructor: frees all nodes (without freeing the data in every node)
    void destructor(AVLNode<ptr_type>*& root);

    // is there any need?
    void inorder_travel(AVLNode<ptr_type>*& r);

    // - sub function for get_closest_left: returns father of key object, returns nullptr if not
    AVLNode<ptr_type>* get_father(AVLNode<ptr_type>* r, ptr_type* data, AVLNode<ptr_type>*& requested, bool*& flag);

    // - sub function for get_max_node: returns max node for any tree that starts with a given root
    AVLNode<ptr_type>* get_max_node_by_root(AVLNode<ptr_type>* given_root);

    // - sub function for get_min_node: returns min node for any tree that starts with a given root
    AVLNode<ptr_type>* get_min_node_by_root(AVLNode<ptr_type>* given_root);

    AVLNode<ptr_type>* root;
    int num_of_nodes;

    static const int EMPTY_TREE = -1;
    static const int UNBALANCED_POSITIVE_BF = 2;
    static const int UNBALANCED_NEGATIVE_BF = -2;

public:

    // constructor
    AVLTree() : root(nullptr), num_of_nodes(0) {}

    // returns how many nodes the tree consists
    int get_num_of_nodes();

    // returns the height of the tree
    int get_tree_height();

    /** returns pointer to the tree's max node
     * returns nullptr - if tree is empty
     */
    AVLNode<ptr_type>* get_max_node();

    /** inserts a new node to the tree
     * receives &address of new object created
     * returns pointer to node created
     * returns nullptr - if node already exists
     */
    AVLNode<ptr_type>* insert(ptr_type* data);

    /** removes the node that points to 'data'
     * returns true - if node is found and removed
     * returns false - if node doesn't exist
     */
    bool remove(ptr_type* data);

    /** removes the node that points to 'data' and calls its destructor
     * returns true - if node is found and removed, and data is erased
     * returns false - if node doesn't exist
     */
    bool remove_and_erase(ptr_type* data);

    /** returns a pointer to node
     *  returns nullptr - if node doesn't exist
     */
    AVLNode<ptr_type>* search(ptr_type* data);

    /**
     * returns a pointer to the closest left neighbor node (smaller then the node)
     * returns nullptr - if doesn't exist
     */
    AVLNode<ptr_type>* get_closest_left(ptr_type* data);

    /**
    * returns a pointer to the closest left neighbor node (smaller then the node)
    * returns nullptr - if doesn't exist
    */
    AVLNode<ptr_type>* get_closest_right(ptr_type* data);

    // is there any need?
    void inorder();

    /** calls for the destructor of the data pointed to at every node
     * does not remove the node itself (that's the destructors job)
     */
    void erase_data();

    // destructor for the tree - DOES NOT erase the data pointed to
    ~AVLTree();

};
