//
// Created by MKassem360 on 6/8/2023.
//

#include "hashTable.h"

int hashTable::hashFunction(int value)
{
    return (value % size);
}




void hashTable::Insert(const Customer& customer)
{
    Node<Customer>* node = new Node<Customer>(customer.getID(),customer,nullptr);
    StatusType status =array[hashFunction(customer.getID())].searchAndAdd(node);
    if(status == FAILURE)
        delete node;
}

void hashTable::Delete(int key) // c_id for the customer
{
    array[hashFunction(key)].searchAndDelete(key);
}
Customer& hashTable::Search(int key)
{
    return array[hashFunction(key)].search(key);
}