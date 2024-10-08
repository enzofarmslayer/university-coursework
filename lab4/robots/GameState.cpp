/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 * Updated for TDDD86, 2021.
 */

#include "GameState.h"
#include "utilities.h"
#include "constants.h"
#include <iostream>


GameState::GameState(int numberOfRobots) {
   for (int i = 0; i < numberOfRobots; i++) {
        Robot robot;
        while(!isEmpty(robot)){
            robot = Robot();
        }
        units.push_back(robot);
    }
    teleportHero();
}

void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);
    for (const Robot& robot: robots)
        robot.draw(scene);
    for (const Junk& junk: junks)
        junk.draw(scene);
}

void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}

void GameState::moveRobots() {
    for(Robot& robot: robots)
        robot.moveTowards(hero.asPoint());
}


void GameState::updateCrashes() {
    for(unsigned i=0; i < units.size(); ++i){
        for(unsigned j=i+1; j < units.size(); ++j) {
            if(units[i].at(units[j])) {
                units[i].doCrash();
                units[j].doCrash();
            }
        }
    }
}


int GameState::countToBeJunked()const{
    int numberDestroyed =0;

    for(unsigned i=0; i < units.size(); ++i)
        if(units[i].isToBeJunked())
            numberDestroyed++;

//    for(unsigned i=0; i < robots.size(); ++i)
//        if(robots[i].isToBeJunked())
//            numberDestroyed++;
    return numberDestroyed;
}


void GameState::junkTheCrashed(){
    for(unsigned i=0; i < units.size(); ++i){
        if (units[i].isToBeJunked()) {
            units.push_back(Junk(units[i].asPoint()));
            units[i] = units[units.size()-1];
            units.pop_back();
        }
    }
}


bool GameState::someRobotsAlive() const {
    for(unsigned i=0; i < units.size(); ++i) {
        if(units[i].isAlive()) {
            return true;
        }
    }
    return false;
}


bool GameState::heroDead() const {
    for (const Unit& unit: units)
    {
        if (hero.at(unit)){
            return true;
        }
    }

//    for(const Robot& robot: robots){
//        if(hero.at(robot)){
//            return true;
//        }
//    }
//    for(const Junk& junk: junks){
//        if(hero.at(junk)){
//            return true;
//        }
//    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}

Point GameState::getHeroAsPoint() const {return hero.asPoint();}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit1) const {
    for (const Unit& unit2: units)
    {
        if (unit1.at(unit2)){
            return false;
        }
    }

//    for(const Robot& robot: robots)
//        if(robot.at(unit))
//            return false;
//    for(const Junk& junk: junks)
//        if(junk.at(unit))
//            return false;
    return true;
}

