// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    MyPriorityQueue();

    ~MyPriorityQueue();

    void push(const T& t);

    T top()const;

    void pop();

    bool empty()const;

    unsigned size() const;



private:
    // Other private members?
    void heapifyUp(int index);
    void heapifyDown(int index);
};

template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
}

template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){
    //lägg till
    vector_array.push_back(t);

    //återskap heapstrukt
    heapifyUp(vector_array.size()-1);
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

        // ta bort högst prio
        vector_array[0] = vector_array.back();
        vector_array.pop_back();

        // återskapa heap-struktur
        if (!vector_array.empty()) {
            heapifyDown(0);
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
void MyPriorityQueue<T, C>::heapifyUp(int index) {
    int parent;
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
void MyPriorityQueue<T, C>::heapifyDown(int index) {
    int size = vector_array.size();
    while (true) {
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int smallest = index;

        if (left_child < size && strictly_larger_operator(vector_array[smallest], vector_array[left_child])) {
            smallest = left_child;
        }
        if (right_child < size && strictly_larger_operator(vector_array[smallest], vector_array[right_child])) {
            smallest = right_child;
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
