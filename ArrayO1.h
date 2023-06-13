//
// Created by MKassem360 on 6/12/2023.
//

#ifndef HW2_WET_ARRAYO1_H
#define HW2_WET_ARRAYO1_H

template <class T>
class ArrayO1 {
    T * array;
    int * shortcut;
    int * initializedIndex;
    int size;
    int top;
    T* initial_value;
public:
    ArrayO1()=default;
    ArrayO1(int size, T initial_value); // init
    ~ArrayO1()=default;
    bool is_assigned(int index);
    T operator[](int index); //get(V,i):
    void store(int i,T value); //store(V,I,e):
    void operator=(T other);
};


#endif //HW2_WET_ARRAYO1_H
