/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef HERO_H
#define HERO_H

#include "Unit.h"
#include <QGraphicsScene>

class Hero : public Unit {
    bool toBeJunked = false;

public:

    /*
     * did not crash yet
     */
    bool isAlive() const;

    /*
     * Crashes and remembers it
     */
    void doCrash();

    /*
     * Return whether the hero crashed
     */
    bool isToBeJunked() const;


    /*
    * Draws this hero onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;

};

#endif // HERO_H
