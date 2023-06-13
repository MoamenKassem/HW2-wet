//
// Created by MKassem360 on 6/12/2023.
//

#ifndef HW2_WET_REVERSEDTREE_H
#define HW2_WET_REVERSEDTREE_H
#include "Customer.h"
#include "ArrayO1.h"
class reversedTree {
    ArrayO1<int> TreeSize;
    ArrayO1<int> parentIndex;
    ArrayO1<Record*> data;
    int size;

public:
    reversedTree(int size);
    ~reversedTree()=default;
    int getSize(){return size;};
    int find(int index);
    void makeset(int index,Record* value);
    void groupUnion(int group1, int group2);
    ArrayO1<Record*> getData()const{return data;};
};


#endif //HW2_WET_REVERSEDTREE_H
