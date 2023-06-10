//
// Created by MKassem360 on 6/10/2023.
//

#include "DynamicArray.h"
DynamicArray::DynamicArray():max_size(100),current_size(0)
{
    arr = new int[max_size];
    for (int i = 0; i < max_size; i++)
        arr[i] = 0;
}

void DynamicArray::check_full(){
    if (current_size >= max_size){
        max_size*=2;
        int* expandedArr = new int[max_size];
        for (int i = 0; i < current_size; ++i) {
            expandedArr [i] = arr[i];
        }
    }

}

void DynamicArray::check_quarter_full() {
    if (current_size < max_size/4)
    {
        max_size /= 2;
        int* shortenedArr = new int[max_size/2];
        for(int i=0;i<current_size;i++)
    }
}