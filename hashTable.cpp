//
// Created by MKassem360 on 6/8/2023.
//

#include "hashTable.h"

void hashTable::printArr(AVL_Tree<Node<Customer*>>* toPrintArr,int size) const
{
    std::cout << "\n" << "Array" << ":   " << std::endl;
    for (int i = 0; i < size; ++i) {
        toPrintArr[i].printLevelOrder();
    }
    std::cout << std::endl;
}
void hashTable::printArr() const
{
    std::cout << "\n" << "Array" << ":   " << std::endl;
    for (int i = 0; i < getSize(); ++i) {
        array[i].printLevelOrder();
    }
    std::cout << std::endl;
}







hashTable::hashTable():max_size(10),current_size(0)
{
    array = new AVL_Tree<Node<Customer*>>[10];
}

void hashTable::check_full()
{
    if (current_size < max_size)
        return;
    AVL_Tree<Node<Customer*>>* expandedArr = new AVL_Tree<Node<Customer*>>[max_size*2];
    AVL_Tree<Node<Customer*>>* tempArr = array;
    array = expandedArr;
    this->max_size *= 2;
    current_size = 0;
    for(int i=0;i<max_size/2;i++)
    {
        printArr(expandedArr,max_size);
        printArr(tempArr,max_size/2);
        InsertTree(tempArr[i]);
    }
    /*for(int i=0;i<max_size;i++)
    {
        tempArr.printArr();
        deleteTree(tempArr[i].getRoot());
        tempArr[i].changeRoot(nullptr);
    }*/
    array = expandedArr;
}

void hashTable::check_quarter_full() {
    if (current_size > max_size/4)
        return;
    AVL_Tree<Node<Customer*>>* shortenedArr = new AVL_Tree<Node<Customer*>>[max_size/2];
    AVL_Tree<Node<Customer*>>* tempArr = array;
    array = shortenedArr;
    this->max_size /= 2;
    current_size = 0;
    for(int i=0;i<max_size*2;i++)
    {
        printArr(shortenedArr,max_size);
        printArr(tempArr,max_size*2);
        InsertTree(tempArr[i]);
    }
    /*for(int i=0;i<max_size;i++)
    {
        tempArr.printArr();
        deleteTree(tempArr[i].getRoot());
        tempArr[i].changeRoot(nullptr);
    }*/
    array = shortenedArr;
}

int hashTable::hashFunction(int value) const
{
    return (value % max_size);
}

StatusType_t hashTable::Insert(Customer* customer)
{
    Node<Customer*>* node = new Node<Customer*>(customer->getID(),customer, nullptr);
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
    this->Insert(node->content);
}

void hashTable::Delete(int key) // c_id for the customer
{
    int index = hashFunction(key);
    array[index].searchAndDelete(key);
    if(array[index].getRoot() == nullptr)
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
    return node->content;
}
