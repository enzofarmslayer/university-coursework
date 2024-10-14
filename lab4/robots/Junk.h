/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include <QGraphicsScene>

class Junk : public Unit {
public:
    Junk(const Point& p): Unit(p){}
    virtual Junk* clone() const override;


    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;
    bool isAlive() const override;
    void doCrash() override;
    bool isToBeJunked() const override;
    void moveTowards(const Point& p) override;

};

#endif // JUNK_H
