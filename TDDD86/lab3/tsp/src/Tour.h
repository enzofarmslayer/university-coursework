/*
 * This file contains the declaration of the Tour structure.
 * See Tour.cpp for implementation of each member.
 */

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
    /*
     * Destructor for tour. Loops thorugh the tour and delete all nodes when called
     */
    ~Tour();

    /*
     * Shows all points in terminal
     */
    void show();

    /*
     * Draws the tour by looping through all nodes and drawing the distance between them with QGraphics
     */
    void draw(QGraphicsScene* scene);

    /*
     * Returns the size of the tour, the amount of nodes
     */
    int size();

    /*
     * Returns the total distance of the tour
     */
    double distance();

    /*
     * A heurestic that adds a point next to a already existing node that is the closest to it
     */
    void insertNearest(Point p);

    /*
     * This heurestic adds the new node in all positions in that way that adds the least to the distance of the tour
     */
    void insertSmallest(Point p);

private: 
    // First node
   Node* first = nullptr;
};

#endif // TOUR_H
