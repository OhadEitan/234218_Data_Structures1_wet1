#ifndef AVLTREE_CPP_LINKEDLIST_H
#define AVLTREE_CPP_LINKEDLIST_H




// node class to be used in linked list
template<class ptr_type>
class LLNode
{
public:
    ptr_type* data;
    LLNode* previous;
    LLNode* next;
    LLNode(ptr_type* data_to_copy) : data(data_to_copy), previous(nullptr), next(nullptr) {}
    ~LLNode() = default;
};


// Linked list class
template<class ptr_type>
class LinkedList {
private:
    LLNode<ptr_type>* head;
    int num_of_nodes;

public:
    // Default constructor
    LinkedList() : head (nullptr), num_of_nodes(0) {}

    /** inserts first node in list as head
     * returns pointer to node created
     * returns nullptr - if head already exists or arguments given are nullptr
    */
    LLNode<ptr_type>* insert_head(ptr_type* data);

    /** inserts a new node to the list after an existing node
    * receives &address of new object created and node to insert after
    * returns pointer to node created
    * returns nullptr - if node already exists or arguments given are nullptr
    */
    LLNode<ptr_type>* insert_after(ptr_type* data, LLNode<ptr_type>* node_to_insert_after);

    /** removes the node that points to 'data'
     * returns true - if node is found and removed
     * returns false - if node doesn't exist or linked list is empty
     * remove doesn't erase data in any way!
     */
    bool remove(LLNode<ptr_type>* node_to_delete);

    // returns how many nodes the list consists
    int get_num_of_nodes();

    /**
     * returns true - if list is empty
     * returns false - if list is not empty
     */
    bool is_list_empty();

    // destructor - removes all nodes without erasing their data
    ~LinkedList();

};


template<class ptr_type>
LLNode<ptr_type>* LinkedList<ptr_type>::insert_head(ptr_type* data)
{
    if (data == nullptr && head != nullptr)
    {
        return nullptr;
    }
    if (head != nullptr)
    {
        LLNode<ptr_type>* newNode = new LLNode<ptr_type>(data);
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
        num_of_nodes++;
        return head;
    }
    LLNode<ptr_type>* newNode = new LLNode<ptr_type>(data);
    head = newNode;
    num_of_nodes++;
    return head;
}


template<class ptr_type>
LLNode<ptr_type>* LinkedList<ptr_type>::insert_after(ptr_type* data, LLNode<ptr_type>* node_to_insert_after)
{
    if (data == nullptr || node_to_insert_after == nullptr)
    {
        return nullptr;
    }
    if (node_to_insert_after->next != nullptr)
    {
        if (node_to_insert_after->next->data == data)
        {
            return nullptr;
        }
    }
    LLNode<ptr_type>* newNode = new LLNode<ptr_type>(data);
    newNode->next = node_to_insert_after->next;
    newNode->previous = node_to_insert_after;
    node_to_insert_after->next = newNode;
    if (newNode->next != nullptr)
    {
        newNode->next->previous = newNode;
    }
    num_of_nodes++;
    return newNode;
}


template<class ptr_type>
bool LinkedList<ptr_type>::remove(LLNode<ptr_type>* node_to_delete)
{
    if (node_to_delete == nullptr || num_of_nodes == 0)
    {
        return false;
    }
    if (node_to_delete->previous != nullptr)
    {
        node_to_delete->previous->next = node_to_delete->next;
    }
    else
    {
        head = node_to_delete->next;
    }
    if (node_to_delete->next != nullptr)
    {
        node_to_delete->next->previous = node_to_delete->previous;
    }
    delete node_to_delete;
    num_of_nodes--;
    return true;
}


template<class ptr_type>
int LinkedList<ptr_type>::get_num_of_nodes()
{
    return num_of_nodes;
}


template<class ptr_type>
bool LinkedList<ptr_type>::is_list_empty()
{
    return (num_of_nodes == 0);
}


template<class ptr_type>
LinkedList<ptr_type>::~LinkedList()
{
    LLNode<ptr_type>* node = head;
    while (node != nullptr)
    {
        LLNode<ptr_type>* temp = node->next;
        delete node;
        node = temp;
    }
}

#endif //AVLTREE_CPP_LINKEDLIST_H
