//
// Created by MKassem360 on 6/8/2023.
//

#include "hashTable.h"

hashTable::hashTable():max_size(10),current_size(0)
{
    AVL_Tree<Node<Customer*>>* arr = new AVL_Tree<Node<Customer*>>();
    array = arr;
}

void hashTable::check_full()
{
    if (current_size < max_size)
        return;
    AVL_Tree<Node<Customer*>>* expandedArr = new AVL_Tree<Node<Customer*>>[max_size*2];
    AVL_Tree<Node<Customer*>>* tempArr = new AVL_Tree<Node<Customer*>>[max_size];
    for(int i=0;i<max_size;i++)
    {
        tempArr[i] = array[i];
    }
    for(int i=0;i<max_size;i++)
    {
        deleteTree(array[i].getRoot());
    }
    delete array;
    this->array = expandedArr;
    this->max_size *= 2;
    for(int i=0;i<max_size/2;i++)
    {
        InsertTree(tempArr[i]);
    }
    for(int i=0;i<max_size;i++)
    {
        deleteTree(tempArr[i].getRoot());
    }
    delete[] tempArr;
}

void hashTable::check_quarter_full() {
    if (current_size >= max_size/4)
        return;

    AVL_Tree<Node<Customer*>>* shortenedArr = new AVL_Tree<Node<Customer*>>[max_size/2];
    AVL_Tree<Node<Customer*>>* tempArr = new AVL_Tree<Node<Customer*>>[max_size];
    for(int i=0;i<max_size;i++)
    {
        tempArr[i] = array[i];
    }
    for(int i=0;i<max_size;i++)
    {
        deleteTree(array[i].getRoot());
    }
    delete array;
    this->array = shortenedArr;
    this->max_size /= 2;
    for(int i=0;i<max_size*2;i++)
    {
        if(tempArr[i].getRoot() == nullptr)
            continue;
        InsertTree(tempArr[i]);
    }
    for(int i=0;i<max_size;i++)
    {
        deleteTree(tempArr[i].getRoot());
    }
    delete[] tempArr;
}

int hashTable::hashFunction(int value)
{
    return (value % max_size);
}

StatusType_t hashTable::Insert(Customer* customer)
{
    Node<Customer*>* node = new Node<Customer*>(customer->getID(),&customer, nullptr);
    if (array[hashFunction(customer->getID())].getRoot() == nullptr)
        current_size++;
    StatusType status =array[hashFunction(customer->getID())].searchAndAdd(node);
    if(status == ALREADY_EXISTS)
    {
        delete node;
        return status;
    }

    check_full();
    return status;
}

void hashTable::InsertTree(AVL_Tree<Node<Customer*>> tree)
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
    this->Insert(*node->content);
}

void hashTable::Delete(int key) // c_id for the customer
{
    array[hashFunction(key)].searchAndDelete(key);
    if(array[hashFunction(key)].getRoot() == nullptr)
        current_size--;
    check_quarter_full();
}

Customer* hashTable::Search(int key)
{
    Node<Customer*>* node = array[hashFunction(key)].search(key);
    if(node->content == nullptr)
    {
        delete node;
        return nullptr;
    }
    return *node->content;
}
