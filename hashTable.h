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
    AVL_Tree<Node<Customer*>>* array;
    int max_size;
    int current_size;
public:
    hashTable();
    // array functions
    void check_full();
    void check_quarter_full();
    AVL_Tree<Node<Customer*>>& operator[](int index){return array[index];}; // get
    // hash functions
    int hashFunction(int value) const; // mod
    int getSize() const{return max_size;};
    StatusType_t Insert(Customer* customer);
    void Delete(int key);
    Customer* Search(int value);
    void InsertTree(AVL_Tree<Node<Customer*>> tree);
    void InsertNode(Node<Customer*>* node);
};

/*
 m - size of hashtable
 n - num of items in hashtable

 */
#endif //HW2_WET_HASHTABLE_H
