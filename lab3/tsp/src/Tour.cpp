// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour(Point a, Point b, Point c, Point d):first(Node(a)) {

    // Dynamically allocate nodes on the heap
    Node* second = new Node(b);
    Node* third = new Node(c);
    Node* fourth = new Node(d);

    // Set up the circular linked list
    first.next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = &first;
}

Tour::~Tour()
{
    // TODO: write this member
}

void Tour::show() {
    cout << first.point.toString()  << endl;
    cout << first.next->point.toString()  << endl;
    cout << first.next->next->point.toString()  << endl;
    cout << first.next->next->next->point.toString()  << endl;
}


void Tour::draw(QGraphicsScene *scene)
{
    // TODO: write this member
}

int Tour::size()
{
    // TODO: write this member
}

double Tour::distance()
{
    // TODO: write this member
}

void Tour::insertNearest(Point p)
{
    // TODO: write this member
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
