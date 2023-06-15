//
// Created by MKassem360 on 6/12/2023.
//

#ifndef HW2_WET_REVERSEDTREE_H
#define HW2_WET_REVERSEDTREE_H
#include "Customer.h"
#include "utilesWet2.h"
class reversedTree {
    int* TreeSize;
    int* parentIndex;
    Record** data;
    int* nodeColumn;
    int* heightExtra;
    int size;

public:
    reversedTree(int size);
    ~reversedTree()=default;
    int getSize() const{return size;};
    int find(int index);
    void makeset(int index,Record* value);
    StatusType groupUnion(int Top, int Bottom);
    Record** getData()const{return data;};
    void initialize(int size);
    int calcHeight(int index);
    void printArr() const;
    int getColumn(int index);
};


#endif //HW2_WET_REVERSEDTREE_H
