//
// Created by MKassem360 on 6/12/2023.
//

#include "reversedTree.h"

reversedTree::reversedTree(int size):size(size), TreeSize(size,-1), parentIndex(size,-1)
{
    Record* record = new Record();
    ArrayO1<Record*>* data = new ArrayO1<Record*>(size,record);
    this->data = *data;
}

int reversedTree::find(int index)
{
    int temp = index;
    while(parentIndex[index] != -1)
    {
        index = parentIndex[index];
    }
    while(parentIndex[temp] != -1)
    {
        temp = parentIndex[temp];
        parentIndex.store(temp,index);
    }
    return index;
}

void reversedTree::makeset(int index,Record* value)
{
    TreeSize.store(index,1);
    data.store(index,value);
}

void reversedTree::groupUnion(int group1, int group2)
{
    if(TreeSize[group1] == TreeSize[group2])
        return;
    if(TreeSize[group1] > TreeSize[group2]){
        parentIndex.store(group2,group1);
        TreeSize.store(group1,TreeSize[group1]+TreeSize[group2]);
        TreeSize.store(group2,-1);
        return;
    }
    parentIndex.store(group1,group2);
    TreeSize.store(group2,TreeSize[group1]+TreeSize[group2]);
    TreeSize.store(group1,-1);
}




