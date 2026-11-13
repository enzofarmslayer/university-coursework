/**
 * The priority queue that implements our vector implementation.
 *
 * Developers: kevma271, enzcu445
 */

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"
#include <iostream>

template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    /**
     * @brief MyPriorityQueue is the constructor
     */
    MyPriorityQueue();

    /**
     * @brief ~MyPriorityQueue is the destructor
     */
    ~MyPriorityQueue();

    /**
     * @brief push inserts an elemnt in the right position.
     *        We utilize the push_back method of our vector.
     * @param t element to be inserted.
     */
    void push(const T& t);

    /**
     * @brief top returns the top element
     */
    T top()const;

    /**
     * @brief pop removes the last element
     */
    void pop();

    /**
     * @brief empty returns whether pq is empty
     * @return boolean
     */
    bool empty()const;

    /**
     * @brief size counts the amount of elements
     */
    unsigned size() const;


private:
    // Other private members?
    void heapifyFromBottom();
    void heapifyFromTop();
};


template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
}


template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
}


template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    vector_array.push_back(t);

    heapifyFromBottom();
}


template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    if (!vector_array.empty()){
        return vector_array[0];
    }
}


template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    if(!vector_array.empty()){

        // Remove highest priority
        vector_array[0] = vector_array[vector_array.size()-1];
        vector_array.pop_back();

        // Re-create the heap structure
        if (!vector_array.empty()) {
            heapifyFromTop();
        }
    }
}


template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}


template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}


template <typename T, typename C>
void MyPriorityQueue<T, C>::heapifyFromBottom() {
    int parent;
    int index = vector_array.size()-1;

    while (index > 0) {
        if (index % 2 == 0){
            parent = (index - 2) / 2;
        }
        else if (index % 2 == 1){
            parent = (index - 1) / 2;
        }

        if (strictly_larger_operator(vector_array[parent], vector_array[index])) {
            //swap
            T temp = vector_array[parent];
            vector_array[parent] = vector_array[index];
            vector_array[index] = temp;

            index = parent;
            }
        else {
            break;
        }
    }
}


template <typename T, typename C>
void MyPriorityQueue<T, C>::heapifyFromTop() {
    int size = vector_array.size();
    int index = 0;

    while (true) {
        int leftChildIndex = (2 * index) + 1;
        int rightChildIndex = (2 * index) + 2;
        int smallest = index;

        if (leftChildIndex < size && strictly_larger_operator(vector_array[smallest], vector_array[leftChildIndex])) {
            smallest = leftChildIndex;
        }
        if (rightChildIndex < size && strictly_larger_operator(vector_array[smallest], vector_array[rightChildIndex])) {
            smallest = rightChildIndex;
        }

        if (smallest != index) {
            // swap
            T temp = vector_array[index];
            vector_array[index] = vector_array[smallest];
            vector_array[smallest] = temp;

            index = smallest;
        } else {
            break;
        }
    }
}

#endif // MY_PRIORITY_QUEUE_H
