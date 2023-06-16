//
// Created by MKassem360 on 6/12/2023.
//

#include <iostream>
#include "reversedTree.h"
/*
void reversedTree::printArr() const
{
    std::cout << "\n" << "TreeSize" << ":   " << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << TreeSize[i] << ",";
    }
    std::cout << "\n" << "parentIndex" << ":   " << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << parentIndex[i] << ",";
    }
    std::cout << "\n" << "TopContainer" << ":   " << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << topContainer[i] << ",";
    }
    std::cout << "\n" << "Extra" << ":   " << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << heightExtra[i] << ",";
    }
    std::cout << std::endl;
}
*/

reversedTree::~reversedTree()
{
    delete[] TreeSize;
    delete[] parentIndex;
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
    delete[] heightExtra;
    delete[] nodeColumn;
    delete[] topContainer;
}

int reversedTree::getColumn(int index)
{
    return nodeColumn[find(index)];
}

int reversedTree::calcHeight(int index)
{
    if(parentIndex[index] == -1)
        return heightExtra[index];

    int sumR=0,toSubtract=0,previousExtra=0,returnIndex=index,oldParent =-1;
    int inputIndex = index;
    while(parentIndex[index] != -1)
    {
        sumR += heightExtra[index];
        index = parentIndex[index];
    }

    while(parentIndex[inputIndex] != -1)
    {
        previousExtra = heightExtra[inputIndex];
        oldParent = parentIndex[inputIndex];

        heightExtra[inputIndex] = sumR - toSubtract;
        parentIndex[inputIndex] = index;
        inputIndex = oldParent;
        toSubtract += previousExtra;
    }
    return heightExtra[returnIndex] + heightExtra[index];
}

void reversedTree::initialize(int arrSize)
{
    for (int i = 0; i < arrSize; ++i) {
        parentIndex[i] = -1;
        TreeSize[i] = 0;
        heightExtra[i] = 0;
        nodeColumn[i] = i;
        topContainer[i] = -1;
    }
}

reversedTree::reversedTree(int size):size(size)
{
    TreeSize = new int[size];
    parentIndex = new int [size];
    data = new Record*[size];
    heightExtra = new int[size];
    nodeColumn = new int [size];
    topContainer = new int [size];
}

int reversedTree::find(int index)
{
    calcHeight(index);
    int temp = index;
    while(parentIndex[index] != -1)
    {
        index = parentIndex[index];
    }
    while(parentIndex[temp] != -1)
    {
        parentIndex[temp] = index;
        temp = parentIndex[temp];
    }
    return index;
}

void reversedTree::makeset(int index,Record* value)
{
    TreeSize[index] = 1;
    data[index] = value;
    topContainer[index] = index;
}

StatusType reversedTree::groupUnion(int Top, int Bottom)
{
    int head1 = find(Top);
    int head2 = find(Bottom);
    if(head1 == head2) {
        return FAILURE;
    }
    nodeColumn[head1] = nodeColumn[head2];

    if(TreeSize[head1] > TreeSize[head2]){

        heightExtra[head1]+=calcHeight(topContainer[head2]) + data[topContainer[head2]]->RecordsAmount;
        heightExtra[head2]-=heightExtra[head1];

        parentIndex[head2] = head1;
        TreeSize[head1] = TreeSize[head1]+TreeSize[head2];

        return SUCCESS;
    }

    TreeSize[head2] = TreeSize[head1]+TreeSize[head2];

    heightExtra[head1]+=calcHeight(topContainer[head2])-heightExtra[head2] + data[topContainer[head2]]->RecordsAmount;

    parentIndex[head1] = head2;
    topContainer[head2] = topContainer[head1];
    return SUCCESS;
}