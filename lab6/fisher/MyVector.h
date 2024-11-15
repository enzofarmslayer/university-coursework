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
    void expandCapacity();
    T* storage;
};

template<typename T>
MyVector<T>::MyVector() : capacity(1), numberOfElements(0) {
     storage = new T[capacity];
}

template<typename T>
MyVector<T>::~MyVector(){
    delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other) : capacity(other.capacity), numberOfElements(other.numberOfElements) {
    storage = new T[capacity];

    for (unsigned i = 0; i < other.numberOfElements; i++) {
        storage[i] = other.storage[i];
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){

    if(this != other){
        delete[] storage;
        capacity = other.capacity;
        numberOfElements = other.numberOfElements;

        for (unsigned i = 0; i < other.numberOfElements; i++) {
            storage[i] = other.storage[i];
        }
    }
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& e){
    if (capacity == numberOfElements) {
        expandCapacity();
        T* big = new T[capacity];
        big = storage;
        delete[] storage;
        storage = big;
    }
    storage[numberOfElements++] = e;

}

template<typename T>
void MyVector<T>::pop_back(){
    if (numberOfElements > 0){
        delete storage[numberOfElements-1];
        numberOfElements--;
    }

    // göra något mer?
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}


template<typename T>
T& MyVector<T>::operator[](unsigned i){

    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
bool MyVector<T>::empty()const{
    return (numberOfElements == 0)
    // TODO: replace the code below with your code for this member
    //MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::clear(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T* MyVector<T>::begin(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
T* MyVector<T>::end(){
    // TODO: replace the code below with your code for this member
    MYEXCEPTION("unimplemented method");
}

template<typename T>
void MyVector<T>::expandCapacity(){
    capacity *= 2;
}

#endif // MY_VECTOR_H
