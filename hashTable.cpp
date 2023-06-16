//
// Created by MKassem360 on 6/8/2023.
//

#include "hashTable.h"


hashTable::hashTable():max_size(10),current_size(0)
{
    array = new AVL_Tree<Node<Customer*>>[10];
    if(array == nullptr)
        throw StatusType::ALLOCATION_ERROR;
}

hashTable::~hashTable()
{
    delete[] array;
}

void hashTable::check_full()
{
    if (current_size < max_size)
        return;
    AVL_Tree<Node<Customer*>>* expandedArr = new AVL_Tree<Node<Customer*>>[max_size*2];
    if(expandedArr == nullptr)
        throw StatusType::ALLOCATION_ERROR;
    AVL_Tree<Node<Customer*>>* tempArr = array;
    array = expandedArr;
    this->max_size *= 2;
    current_size = 0;
    for(int i=0;i<max_size/2;i++)
    {
        InsertTree(tempArr[i]);
    }
    delete[] tempArr;
    array = expandedArr;
}

int hashTable::hashFunction(int value) const
{
    return (value % max_size);
}

StatusType_t hashTable::Insert(Customer* customer)
{
    Node<Customer*>* node = new Node<Customer*>(customer->getID(),customer, nullptr);
    if(node == nullptr)
        throw StatusType::ALLOCATION_ERROR;
    int index = hashFunction(customer->getID());
    if(array[index].getRoot() == nullptr)
        current_size++;
    StatusType status =array[index].searchAndAdd(node);
    if(status == ALREADY_EXISTS)
    {
        delete node;
        return status;
    }


    check_full();
    return status;
}

void hashTable::InsertTree(AVL_Tree<Node<Customer*>>& tree)
{
    InsertNode(tree.getRoot());
}

void hashTable::InsertNode(Node<Customer*>* node)
{
    if(node == nullptr){
        return;
    }
    InsertNode(node->leftSon);
    InsertNode(node->rightSon);
    this->Insert(node->content);
}

Customer* hashTable::Search(int key)
{
    Node<Customer*>* node = array[hashFunction(key)].search(key);
    if (node->content == nullptr)
    {
        delete node;
        return nullptr;
    }
    return node->content;
}
