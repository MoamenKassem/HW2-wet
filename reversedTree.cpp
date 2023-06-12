//
// Created by MKassem360 on 6/12/2023.
//

#include "reversedTree.h"

reversedTree::reversedTree(int size): TreeSize(size,-1), parentIndex(size,-1), data(size,Record()){}

int reversedTree::find(int index)
{
    int temp = index;
    while(parentIndex[index] != -1)
    {
        index = parentIndex[index];
    }
    parentIndex.store(temp,index);
    return index;
}

void reversedTree::makeset(int index,Record value)
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




