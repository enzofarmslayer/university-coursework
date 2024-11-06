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
        Unit* robot = new Robot();
        while(!isEmpty(*robot)){
            delete robot;
            robot = new Robot;
        }
        units.push_back(robot);

    }

    teleportHero();
}


GameState::GameState(const GameState& that){
   hero = that.hero;
   for (const Unit* unit : that.units) {
       units.push_back(unit->clone());
   }
}


GameState::GameState(GameState&& that) : units(that.units), hero(that.hero) {
    for (auto a = units.begin(); a!=units.end(); a++) {
        *a=nullptr;
    }
}

GameState& GameState::operator=(GameState&& that)  {
    units = that.units;
    hero = that.hero;
    for (auto a = units.begin(); a!=units.end(); a++) {
        *a=nullptr;
    }
}

GameState& GameState::operator=(const GameState& that)  {
   if (this != &that) {
       hero = that.hero;

       deleteUnits();

       for (const Unit* unit : that.units) {
           units.push_back(unit->clone());
       }
   }
   return *this;
}


GameState::~GameState() {
   deleteUnits();
}


void GameState::deleteUnits() {
   for (Unit* unit : units) {
       delete unit;
   }
   units.clear();
}


void GameState::draw(QGraphicsScene *scene) const {
    scene->clear();
    hero.draw(scene);

    for (const Unit* unit: units)
            unit->draw(scene);
}


void GameState::teleportHero() {
    do hero.teleport();
    while (!isEmpty(hero));
}


void GameState::moveRobots() {
    for(Unit* unit: units)
        unit->moveTowards(hero.asPoint());

}


void GameState::updateCrashes() {
    for(unsigned i=0; i < units.size(); ++i){
        for(unsigned j=i+1; j < units.size(); ++j) {
            if(units[i]->at(units[j])) {
                units[i]->doCrash();
                units[j]->doCrash();
            }
        }
    }
}


int GameState::countToBeJunked()const{
    int numberDestroyed =0;

    for(unsigned i=0; i < units.size(); ++i) {
        if(units[i]->isToBeJunked())
            numberDestroyed++;
    }
    return numberDestroyed;
}


void GameState::junkTheCrashed(){
    for(unsigned i=0; i < units.size(); ++i){
        if (units[i]->isToBeJunked()) {
            units.push_back(new Junk(units[i]->asPoint()));
            delete units[i];
            units[i] = units[units.size()-1];
            units.pop_back();
        }
    }
}


bool GameState::someRobotsAlive() const {

    for(unsigned i=0; i < units.size(); ++i) {
        if(units[i]->isAlive()) {
            return true;
        }
    }
    return false;
}


bool GameState::heroDead() const {
    for (const Unit* unit: units)
    {
        if (hero.at(unit)){
            return true;
        }
    }
    return false;
}


void GameState::moveHeroTowards(const Point& dir) {
    hero.moveTowards(dir);
}


Point GameState::getHeroAsPoint() const {
    return hero.asPoint();
}

/*
 * Free of robots and junk
 */
bool GameState::isEmpty(const Unit& unit1) const {
    for (const Unit* unit2: units) {
        if (unit1.at(unit2)){
            return false;
        }
    }
    return true;
}

