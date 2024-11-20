// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    MyVector();

    ~MyVector();

    MyVector(const MyVector& other);

    MyVector& operator =(const MyVector& other);

    void push_back(const T&);

    void pop_back();

    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    bool empty()const;

    T* begin();

    T* end();

    void clear();

    unsigned size()const;


    unsigned capacity = 0;
    unsigned numberOfElements = 0;

private:
//    void expandCapacity();
    T* vector_array;
};

template<typename T>
MyVector<T>::MyVector() : capacity(1), numberOfElements(0) {
     vector_array = new T[capacity];
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] vector_array;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other) : capacity(other.capacity), numberOfElements(other.numberOfElements) {
    vector_array = new T[capacity];

    for (unsigned i = 0; i < other.numberOfElements; i++) {
        vector_array[i] = other.vector_array[i];
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){

    if(this != &other){
        delete[] vector_array;
        capacity = other.capacity;
        numberOfElements = other.numberOfElements;
        vector_array = new T[capacity];
        for (unsigned i = 0; i < other.numberOfElements; i++) {
            vector_array[i] = other.vector_array[i];
        }
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){

    if (capacity == numberOfElements) {
        //expandCapacity();
        T* big = new T[capacity*2];
        for (unsigned i = 0; i < numberOfElements; i++) {
               big[i] = vector_array[i];
        }
        delete[] vector_array;
        vector_array = big;
        capacity *= 2;        
    }
    vector_array[numberOfElements++] = e;

}

template<typename T>
void MyVector<T>::pop_back(){
    if (numberOfElements > 0){
        //delete storage[numberOfElements-1];
        numberOfElements--;
    }
}


template<typename T>
T& MyVector<T>::operator[](unsigned i){
    return vector_array[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    return vector_array[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return (numberOfElements == 0);
}

template<typename T>
void MyVector<T>::clear(){
//    for(int i = 0; i < numberOfElements; ++i){
//        delete storage[i];
//    }
    delete[] vector_array;
    capacity = 1;
    numberOfElements = 0;
    vector_array = new T[capacity];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    return vector_array;
}

template<typename T>
T* MyVector<T>::end(){
    return vector_array + numberOfElements;
}

//template<typename T>
//void MyVector<T>::expandCapacity(){
//    capacity *= 2;
//}

#endif // MY_VECTOR_H
