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
    Node* second = new Node(b);
    Node* third = new Node(c);
    Node* fourth = new Node(d);

     //Set up the circular linked list
     first->next = second;
    second->next = third;
    third->next = fourth;
    fourth->next = first;
}

Tour::~Tour()
{
    // TODO: write this member
}

void Tour::show() {
    if (first != nullptr) {
        Node* temp = first;

        do {
            cout << temp->point.toString()  << endl;
            temp = temp->next;
        } while(temp != first);
    }
}

void Tour::draw(QGraphicsScene *scene) {
    if (first != nullptr) {
        Node* temp = first;

        do {
            temp->point.drawTo(temp->next->point, scene);
            temp = temp->next;
        } while(temp != first);
    }
}

int Tour::size() {
    int size = 0;

    if (first != nullptr) {
        Node* temp = first;
        do {
            size += 1;
            temp = temp->next;
        } while(temp != first);
    }

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
    return distance;
}

void Tour::insertNearest(Point p) {

    if (first != nullptr) {
        int shortestDistance = qInf();
        Node* closestNode = first;

        Node* temp = first;
        do {
            if (temp->point.distanceTo(p) < shortestDistance) {
                closestNode = temp;
            }
            temp = temp->next;
        } while(temp != first);

        Node* newNode = new Node(p, closestNode->next);
        closestNode->next = newNode;
    }
    // If no nodes exist
    else {
        cout << "Error" << endl;
    }
}

void Tour::insertSmallest(Point p) {

    if (first != nullptr) {
        double shortestTourDistance = qInf();

        Node* bestNode = first;
        Node* temp = first;
        Node* newNode = new Node(p);

        do {
            newNode->next = temp->next;
            temp->next = newNode;

            if(shortestTourDistance > this->distance()){
                bestNode = temp;
                shortestTourDistance = this->distance();
            }

            temp->next = newNode->next;
            temp = temp->next;
            newNode->next = nullptr;

        } while(temp != first);

        newNode->next = bestNode->next;
        bestNode->next = newNode;
    }
    // If no nodes exist
    else {
        cout << "Error" << endl;
    }
}
