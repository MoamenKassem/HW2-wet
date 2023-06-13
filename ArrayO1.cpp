//
// Created by MKassem360 on 6/12/2023.
//

#include "ArrayO1.h"

template <class T>
ArrayO1<T>::ArrayO1(int size, T initial_value):size(size),top(0),initial_value(initial_value)
{
    this->array = new T[size];
    this->shortcut = new int[size];
    this->initializedIndex = new int[size];
} // init

template <class T>
bool ArrayO1<T>::is_assigned(int index)
{
    return (shortcut[index]< top && shortcut[index]>=0 && initializedIndex[shortcut[index]]==index);
}

template <class T>
T ArrayO1<T>::operator[](int index)
{
    if (is_assigned(index))
        return array[index];
    else return;
} //get(V,i):

template <class T>
void ArrayO1<T>::store(int i,T value)
{
    if (!is_assigned(i)) {
        initializedIndex[top] = i ;
        shortcut[i] = top ;
        top = top +1;}
    array[i]= value;
}

template <class T>
void ArrayO1<T>::operator=(T other){
    other.array = this->array;
    other.shortcut = this->shortcut;
    other.initializedIndex = this->initializedIndex;
    other.top = this->top;
    other.initial_value = this->initial_value;
    other.size = this->size;
}