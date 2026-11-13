/**
 * All methods for our own vector that has a better time complexity for push back.
 *
 * Developers: kevma271, enzcu445
 */

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"

template <typename T>
class MyVector
{

public:
    /**
     * @brief MyVector is the constructor
     */
    MyVector();
    /**
     * @brief ~MyVector is the destructor
     */
    ~MyVector();

    /**
     * @brief MyVector is the copy constructor
     * @param other vector instance to copy from
     */
    MyVector(const MyVector& other);

    /**
     * @brief operator = is our own assignment operator
     * @param other vector instance to instanciate
     * @return the new vector instance
     */
    MyVector& operator =(const MyVector& other);

    /**
     * @brief push_back an improved time complexity of O(n^2 logn).
     *        Which is obtained by increasing capacity of the vector
     *        with 2 when it gets full. This way we don't have to
     *        copy values to a new vector as often.
     */
    void push_back(const T&);

    /**
     * @brief pop_back removes the last element
     */
    void pop_back();

    /**
     * @brief operator [] used to index the vector
     */
    T& operator[](unsigned i);

    /**
     * @brief operator [] indexing the vector with
     *        a const parameter
     */
    const T& operator[](unsigned i)const;

    /**
     * @brief empty returns whether vector contains anything
     * @return boolean
     */
    bool empty()const;

    /**
     * @brief begin returns a pointer to the first element
     */
    T* begin();

    /**
     * @brief end returns a pointer to the last element
     */
    T* end();

    /**
     * @brief clear cleans all the elements from the vector
     */
    void clear();

    /**
     * @brief size retrievs the size of the vector
     */
    unsigned size()const;

    unsigned capacity = 0;
    unsigned numberOfElements = 0;

private:
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

#endif // MY_VECTOR_H
