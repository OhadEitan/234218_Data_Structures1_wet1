#include "AVLTree.h"

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
    if (bf == 2)
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
    if (bf == -2)
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
int AVLTree<ptr_type, condition>::get_tree_height()
{
    return root->height;
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
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::insert2(AVLNode<ptr_type>*& r, ptr_type* data, AVLNode<ptr_type>*& r_new_junction)
{
    if (r == nullptr)
    {
        r = new AVLNode<ptr_type>(data);
        r_new_junction = r;
        return r;
    }
    else
    {
        condition cond;
        if (cond(data, r->data))
        {
            r->left = insert2(r->left, data, r_new_junction);
        }
        else
        {
            r->right = insert2(r->right, data, r_new_junction);
        }
        update_height(r);
        return balance_tree(r);
    }
}


template <class ptr_type, class condition>
AVLNode<ptr_type>* AVLTree<ptr_type, condition>::insert(ptr_type* data)
{
    AVLNode<ptr_type>* r_new_junction = nullptr;
    root = insert2(root, data, r_new_junction);
    return r_new_junction;
}


template <class ptr_type, class condition>
void AVLTree<ptr_type, condition>::remove(int key)
{
    remove2(root, key);
}


template <class ptr_type, class condition>
void AVLTree<ptr_type, condition>::remove2(AVLNode<ptr_type>*& r, int key)
{
    if (r == nullptr)
    {
        r = new AVLNode<ptr_type>(data);
        return r;
    }
    else {
        condition cond;
        if (cond(data, r->data)) {
            r->left = insert2(r->left, data);
        } else {
            r->right = insert2(r->right, data);
        }
        update_height(r);
        return balance_tree(r);
    }
}
