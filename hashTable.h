//
// Created by MKassem360 on 6/8/2023.
//

#ifndef HW2_WET_HASHTABLE_H
#define HW2_WET_HASHTABLE_H
#include "AVL_Tree.h"
#include "Node.h"
#include "Customer.h"
#include "utilesWet2.h"
//made by chain hashing
class hashTable {
AVL_Tree<Node>* array;
int size; // size of hashtable
public:
    int hashFunction(int value); // mod
    void Insert(const Customer& customer);
    void Delete(int key);
    void Search(int value);
};

/*
 m - size of hashtable
 n - num of items in hashtable

 */
#endif //HW2_WET_HASHTABLE_H
