// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour(Point a, Point b, Point c, Point d) {
    // Dynamically allocate nodes on the heap
    first = new Node(a);
//    Node* second = new Node(b);
//    Node* third = new Node(c);
//    Node* fourth = new Node(d);
    // Set up the circular linked list
     first->next = first;
//    second->next = first;
//    third->next = fourth;
//    fourth->next = first;
}

Tour::~Tour()
{
    // TODO: write this member
}

void Tour::show() {
    if (first) {
        Node* temp = first;

        do {
            cout << temp->point.toString()  << endl;
            temp = temp->next;
        } while(temp != first);
    }
}


void Tour::draw(QGraphicsScene *scene)
{
    // TODO: write this member
}

int Tour::size() {
    int size = 0;

    if (first) {
        Node* temp = first;
        do {
            size += 1;
            temp = temp->next;
        } while(temp != first);
    }

    cout << size << endl;
    return size;
}

double Tour::distance() {
    int distance = 0;

    if (first->next != nullptr) {
        Node* temp = first;
        do {
            distance += temp->point.distanceTo(temp->next->point);
            temp = temp->next;

        } while(temp != first);
    }
    cout << distance << endl;
    return distance;
}

void Tour::insertNearest(Point p)
{
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
