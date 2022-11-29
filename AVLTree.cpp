#include "AVLTree.h"


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