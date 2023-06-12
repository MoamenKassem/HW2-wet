//
// Created by MKassem360 on 6/8/2023.
//

#include "hashTable.h"

/*DynamicArray::DynamicArray():max_size(100),current_size(0)
{
    arr = new int[max_size];
    for (int i = 0; i < max_size; i++)
        arr[i] = 0;
}*/

void hashTable::check_full(){
    if (current_size >= max_size){
        max_size*=2;
        AVL_Tree<Node<Customer>>* expandedArr = new AVL_Tree<Node<Customer>>[max_size];
        for (int i = 0; i < current_size; ++i) {
            expandedArr [i] = array[i];
        }
    }

}

void hashTable::check_quarter_full() {
    if (current_size < max_size/4)
    {
        max_size /= 2;
        AVL_Tree<Node<Customer>>* shortenedArr = new AVL_Tree<Node<Customer>>[max_size];
        for(int i=0;i<current_size;i++)
            return;
    }
}

int hashTable::hashFunction(int value)
{
    return (value % max_size);
}




void hashTable::Insert(Customer customer)
{
    Node<Customer>* node = new Node<Customer>(customer.getID(),&customer, nullptr);
    if (array[hashFunction(customer.getID())].getRoot() == nullptr)
        current_size++;
    StatusType status =array[hashFunction(customer.getID())].searchAndAdd(node);
    if(status == FAILURE)
        delete node;
}

void hashTable::Delete(int key) // c_id for the customer
{
    array[hashFunction(key)].searchAndDelete(key);
    if(array[hashFunction(key)].getRoot() == nullptr)
        current_size--;
}

Customer* hashTable::Search(int key)
{
    Node<Customer>* node = array[hashFunction(key)].search(key);
    if(node->content == nullptr)
    {
        delete node;
        return nullptr;
    }
    return node->content;
}