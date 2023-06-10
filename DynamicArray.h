//
// Created by MKassem360 on 6/10/2023.
//


#ifndef HW2_WET_DYNAMICARRAY_H
#define HW2_WET_DYNAMICARRAY_H


class DynamicArray {
int* arr;
int max_size;
int current_size;
public:
    DynamicArray();
    ~DynamicArray()=default;
    void check_full();
    void check_quarter_full();
    int operator[](int index){return arr[index];}; // get
    void setValue(int index, int value){arr[index] = value;}; //set
};






#endif //HW2_WET_DYNAMICARRAY_H
