// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"


// Constructor
Tour::Tour() {
    //first = nullptr;
}

// Destructor
Tour::~Tour() {
    // Check if a node exists
    if (first != nullptr) {
        Node* temp;

        // Link the first node with the second next and remove the next
        // Loop until there is no second node
        do {
            temp = first->next;
            first->next = temp->next;
            delete temp;

        } while(first->next != first);

        delete first;
    }
}


// Shows all points
void Tour::show() {
    // Check if a node exists
    if (first != nullptr) {
        Node* temp = first;

        // Loop through all points and print them to the console
        do {
            cout << temp->point.toString()  << endl;
            temp = temp->next;
        } while(temp != first);
    }
}


// Draws the points with QGraphics
void Tour::draw(QGraphicsScene *scene) {
    // Check if a node exists
    if (first == nullptr) {
        return;
    }
    else if (first->next == first){
        first->point.draw(scene);
    }
    else
    {
        Node* temp = first;

        // Loop through all points and draw them out
        do {
            temp->point.drawTo(temp->next->point, scene);
            temp = temp->next;
        } while(temp != first);
    }
}


// Returns the amount of points
int Tour::size() {
    int size = 0;

    // Check if a node exists
    if (first != nullptr) {
        Node* temp = first;

        // Loop through all points and count them
        do {
            size += 1;
            temp = temp->next;
        } while(temp != first);
    }

    return size;
}


// Returns the distance of the tour
double Tour::distance() {
    double distance = 0;

    // Check if a node exists
    if (first != nullptr && first->next != first) {
        Node* temp = first;

        do {
            // Loop through all points and add to the distance
            distance += temp->point.distanceTo(temp->next->point);
            temp = temp->next;

        } while(temp != first);
    }

    return distance;
}


// Inserts a new point after the one its nearest
void Tour::insertNearest(Point p) {

    // Check if a node exists
    if (first != nullptr) {
        Node* closestNode = first;
        Node* temp = first;
        int shortestDistance = first->point.distanceTo(p);

        // Loop through the nodes and if the current node is the closest we save it
        do {
            if (temp->point.distanceTo(p) < shortestDistance) {
                shortestDistance = temp->point.distanceTo(p);
                closestNode = temp;
            }
            temp = temp->next;
        } while(temp != first);

        Node* newNode = new Node(p, closestNode->next);
        closestNode->next = newNode;
    }

    // If no nodes exist create the first one
    else {
        first = new Node(p);
        first->next = first;
    }
}


// Adds a point in a way that makes minimal change in the tour distance
void Tour::insertSmallest(Point p) {
    // Check if a node exists
    if (first != nullptr) {

        Node* bestNode = first;
        Node* temp = first;
        Node* newNode = new Node(p);

        // Initialize shortestTourDistance to the current tour distance + new node
        newNode->next = first->next;
        first->next = newNode;

        double shortestTourDistance = this->distance();

        // reset the list without the node
        first->next = newNode->next;
        newNode->next = nullptr;

        // Add the new point in all possible positions and save the one that adds the least to the distance
        do {
            newNode->next = temp->next;
            temp->next = newNode;

            // Check if the new tour distance is smaller
            double currentTourDistance = this->distance();
            if(shortestTourDistance > currentTourDistance){
                bestNode = temp;
                shortestTourDistance = currentTourDistance;
            }

            // Undo the insertion to try the next position
            temp->next = newNode->next;
            temp = temp->next;
            newNode->next = nullptr;

        } while(temp != first);

        // Finalize the best insertion
        newNode->next = bestNode->next;
        bestNode->next = newNode;
    }

    // If no nodes exist create the first one
    else {
        first = new Node(p);
        first->next = first;
    }

}
