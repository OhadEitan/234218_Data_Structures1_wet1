#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H


enum class Comparison
{
    GREATER_THAN,
    EQUAL,
    LESS_THAN
};


// enum class for tree condition
//enum class Comparison
//{
//    GREATER_THAN,
//    EQUAL,
//    LESS_THAN
//};


//class ConPlayerId
//{
//public:
//    Comparison operator()(Player& a, Player& b)
//    {
//        if (a.)
//        if ( < b->p_id)
//        {
//            return Comparison::LESS_THAN;
//        }
//        if (a->p_id > b->p_id)
//        {
//            return Comparison::GREATER_THAN;
//        }
//        return Comparison::EQUAL;
//    }
//};


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
    AVLNode() :  data(nullptr), height(0), left(nullptr), right(nullptr) {} ;
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




/******************************************************* tree details functions *******************************************************/


template <class ptr_type, class condition>
int AVLTree<ptr_type, condition>::get_tree_height()
{
    if (root->right == nullptr && root->left == nullptr)
    {
        return EMPTY_TREE;
    }
    return root->height;
}

template <class ptr_type, class condition>
int AVLTree<ptr_type, condition>::get_num_of_nodes()
{
    return num_of_nodes;
}

template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::get_max_node()
{
    return get_max_node_by_root(root);
}

template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::get_max_node_by_root(AVLNode<ptr_type>* given_root)
{
    AVLNode<ptr_type>* r;
    if (given_root == nullptr)
    {
        return nullptr;
    }
    r = given_root;
    while(r->right != nullptr)
    {
        r = r->right;
    }
    return r;
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::get_min_node_by_root(AVLNode<ptr_type>* given_root)
{
    AVLNode<ptr_type>* r;
    if (given_root == nullptr)
    {
        return nullptr;
    }
    r = given_root;
    while(r->left != nullptr)
    {
        r = r->left;
    }
    return r;
}


/******************************************************* balancing functions *******************************************************/


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::make_LL_rotation(AVLNode<ptr_type>*& r)
{
    AVLNode<ptr_type>* A = r->left;
    r->left = r->left->right;
    A->right = r;
    update_height(r);
    update_height(A);
    return A;
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::make_RR_rotation(AVLNode<ptr_type>*& r)
{
    AVLNode<ptr_type>* A = r->right;
    r->right = r->right->left;
    A->left = r;
    update_height(r);
    update_height(A);
    return A;
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::make_RL_rotation(AVLNode<ptr_type>*& r)
{
    r->right = make_LL_rotation(r->right);
    update_height(r);
    return make_RR_rotation(r);
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::make_LR_rotation(AVLNode<ptr_type>*& r)
{
    r->left = make_RR_rotation(r->left);
    update_height(r);
    return make_LL_rotation(r);
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::balance_tree(AVLNode<ptr_type>*& r)
{
    int bf = get_bf(r);
    if (bf == UNBALANCED_POSITIVE_BF)
    {
        if (get_bf(r->left) >= 0)
        {
            return make_LL_rotation(r);
        }
        else
        {
            return make_LR_rotation(r);
        }
    }
    if (bf == UNBALANCED_NEGATIVE_BF)
    {
        if (get_bf(r->right) >= 0)
        {
            return make_RR_rotation(r);
        }
        else
        {
            return make_RL_rotation(r);
        }
    }
    return r;
}


template <class ptr_type, class condition>
int AVLTree<ptr_type, condition>::get_bf(AVLNode<ptr_type>*& r)
{
    if (r->left == nullptr && r->right != nullptr)
    {
        return (0 - 1 - r->right->height);
    }
    if (r->left != nullptr && r->right == nullptr)
    {
        return (r->left->height + 1);
    }
    if (r->left != nullptr && r->right != nullptr)
    {
        return (r->left->height - r->right->height);
    }
    return 0;
}


template <class ptr_type, class condition>
void AVLTree<ptr_type, condition>::update_height(AVLNode<ptr_type>*& r)
{
    if (r->left == nullptr && r->right != nullptr)
    {
        r->height = 1 + r->right->height;
    }
    if (r->left != nullptr && r->right == nullptr)
    {
        r->height = 1 + r->left->height;
    }
    if (r->left != nullptr && r->right != nullptr)
    {
        if (r->left->height > r->right->height)
        {
            r->height = r->left->height + 1;
        }
        else
        {
            r->height = r->right->height + 1;
        }
    }
    if (r->left == nullptr && r->right == nullptr)
    {
        r->height = 0;
    }
}


/******************************************************* insert functions *******************************************************/


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::insert(ptr_type* data)
{
    AVLNode<ptr_type>* r_new_junction = nullptr;
    root = insert_node(root, data, r_new_junction);
    return r_new_junction;
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::insert_node(AVLNode<ptr_type>*& r, ptr_type* data, AVLNode<ptr_type>*& r_new_junction)
{
    if (r == nullptr)
    {
        r = new AVLNode<ptr_type>(data);
        r_new_junction = r;
        num_of_nodes++;
        return r;
    }
    else
    {
        condition cond;
        Comparison result = cond(data, r->data);
        if (result == Comparison::LESS_THAN)
        {
            r->left = insert_node(r->left, data, r_new_junction);
            update_height(r);
            return balance_tree(r);
        }
        if (result == Comparison::GREATER_THAN)
        {
            r->right = insert_node(r->right, data, r_new_junction);
            update_height(r);
            return balance_tree(r);
        }
        if (result == Comparison::EQUAL)
        {
            r_new_junction = nullptr;
            return r;
        }
    }
}


/******************************************************* search functions *******************************************************/


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::search(ptr_type* data)
{
    AVLNode<ptr_type>* requested = nullptr;
    return search_node(root, data, requested);
}

template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::search_node(AVLNode<ptr_type> *&r, ptr_type* data, AVLNode<ptr_type> *&requested)
{
    if (r == nullptr)
    {
        return nullptr;
    }
    else
    {
        condition cond;
        AVLNode<ptr_type>* temp;
        Comparison result = cond(data, r->data);
        if (result == Comparison::LESS_THAN)
        {
            temp = search_node(r->left, data, requested);
            if (temp != nullptr)
            {
                return temp;
            }
            return nullptr;
        }
        if (result == Comparison::GREATER_THAN)
        {
            temp = search_node(r->right, data, requested);
            if (temp != nullptr)
            {
                return temp;
            }
            return nullptr;
        }
        if (result == Comparison::EQUAL)
        {
            requested = r;
            return r;
        }
    }
}


/******************************************************* travel functions *******************************************************/


template <class ptr_type, class condition>
void AVLTree<ptr_type, condition>::inorder()
{
    inorder_travel(root);
}


template <class ptr_type, class condition>
void AVLTree<ptr_type, condition>::inorder_travel(AVLNode<ptr_type>*& r)
{
    if (r == nullptr)
    {
        return;
    }
    inorder_travel(r->left);
    // do something with data
    inorder_travel(r->right);
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::get_closest_left(ptr_type* data)
{
    AVLNode<ptr_type>* requested = search(data);
    if (requested == nullptr)
    {
        return nullptr;
    }
    if (requested->left == nullptr)
    {
        condition cond;
        bool* result = new bool();
        *result = false;
        AVLNode<ptr_type>* father = get_father(root, data, father, result);
        while (father != nullptr)
        {
            if (cond(data, father->data) == Comparison::GREATER_THAN)
            {
                return father;
            }
            if (cond(data, father->data) == Comparison::LESS_THAN && father->left != nullptr)
            {
                return get_max_node_by_root(father->left);
            }
            *result = false;
            father = (root, data, father, result);
        }
        return nullptr;
    }
    if (requested->left != nullptr)
    {
        return get_max_node_by_root(requested->left);
    }

}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::get_father(AVLNode<ptr_type>* r, ptr_type* data, AVLNode<ptr_type>*& requested, bool*& flag)
{
    if (r == nullptr)
    {
        return nullptr;
    }
    else
    {
        condition cond;
        AVLNode<ptr_type>* temp;
        Comparison result = cond(data, r->data);
        if (result == Comparison::LESS_THAN)
        {
            temp = get_father(r->left, data, requested, flag);
            if (temp != nullptr)
            {
                if (*flag == true)
                {
                    requested = r;
                    *flag = false;
                }
                return temp;
            }
            return nullptr;
        }
        if (result == Comparison::GREATER_THAN)
        {
            temp = get_father(r->right, data, requested, flag);
            if (temp != nullptr)
            {
                if (*flag == true)
                {
                    requested = r;
                    *flag = false;
                }
                return temp;
            }
            return nullptr;
        }
        if (result == Comparison::EQUAL)
        {
            *flag = true;
            return r;
        }
    }
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::get_closest_right(ptr_type* data)
{
    AVLNode<ptr_type>* requested = search(data);
    if (requested == nullptr)
    {
        return nullptr;
    }
    if (requested->right == nullptr)
    {
        AVLNode<ptr_type>* father = nullptr;
        bool* result = new bool();
        *result = false;
        get_father(root, data, father, result);
        return father;
    }
    return get_min_node_by_root(requested->right);
}


/******************************************************* removing functions *******************************************************/


template <class ptr_type, class condition>
bool AVLTree<ptr_type, condition>::remove(ptr_type* data)
{
    bool* result = new bool();
    *result = false;
    remove_node(root, data, result, false);
    bool value = *result;
    delete result;
    if (value == true)
    {
        num_of_nodes--;
    }
    return value;
}


template <class ptr_type, class condition>
bool AVLTree<ptr_type, condition>::remove_and_erase(ptr_type* data)
{
    bool* result = new bool();
    *result = false;
    remove_node(root, data, result, true);
    bool value = *result;
    delete result;
    if (value == true)
    {
        num_of_nodes--;
    }
    return value;
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::find_successor(AVLNode<ptr_type>* b)
{
    b = b->left;
    while(b->right != nullptr)
    {
        b = b->right;
    }
    return b;
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::remove_node(AVLNode<ptr_type> *&r, ptr_type* data, bool*& result, bool erase)
{
    if (r == nullptr)
    {
        *result = *result + false;
        return nullptr;
    }
    else
    {
        condition cond;
        Comparison comp_result = cond(data, r->data);
        if (comp_result == Comparison::EQUAL)
        {
            if (r->right == nullptr && r->left == nullptr) // junction is leaf
            {
                AVLNode<ptr_type>* temp = r;
                if (erase)
                {
                    delete temp->data;
                }
                delete temp;
                r = nullptr;
                *result = true;
                return r;
            }
            if (r->right == nullptr && r->left != nullptr) // junction has only left child
            {
                AVLNode<ptr_type>* temp = r;
                r = r->left;
                if (erase)
                {
                    delete temp->data;
                }
                delete temp;
                *result = true;
                return r;
            }
            if (r->right != nullptr && r->left == nullptr) // junction has only right child
            {
                AVLNode<ptr_type>* temp = r;
                r = r->right;
                if (erase)
                {
                    delete temp->data;
                }
                delete temp;
                *result = true;
                return r;
            }
            if (r->right != nullptr && r->left != nullptr) // junction has both children
            {
                AVLNode<ptr_type>* successor = find_successor(r);
                AVLNode<ptr_type>* temp2;
                temp2 = r;
                if (erase)
                {
                    delete temp2->data;
                }
                r->data = successor->data;
                remove_node(r->left, successor->data, result, false);
                update_height(r);
                *result = true;
                return balance_tree(r);
            }
        }
        if (comp_result == Comparison::LESS_THAN)
        {
            r->left = remove_node(r->left, data, result, erase);
            update_height(r);
            return balance_tree(r);
        }
        if (comp_result == Comparison::GREATER_THAN)
        {
            r->right = remove_node(r->right, data, result, erase);
            update_height(r);
            return balance_tree(r);
        }
    }
}


template <class ptr_type, class condition>
void AVLTree<ptr_type, condition>::erase_data_in_node(AVLNode<ptr_type>*& r)
{
    if (r == nullptr)
    {
        return;
    }
    erase_data_in_node(r->left);
    erase_data_in_node(r->right);
    r->height = 0;  // for elegance
    delete r->data;
}


template <class ptr_type, class condition>
void AVLTree<ptr_type, condition>::erase_data()
{
    erase_data_in_node(root);
}


/******************************************************* destructor *******************************************************/


template <class ptr_type, class condition>
void AVLTree<ptr_type, condition>::destructor(AVLNode<ptr_type>*& r)
{
    if (r == nullptr)
    {
        return;
    }
    destructor(r->left);
    destructor(r->right);
    delete r;
}

template <class ptr_type, class condition>
AVLTree<ptr_type, condition>::~AVLTree()
{
    destructor(root);
}


#endif //AVL_AVLTREE_H
