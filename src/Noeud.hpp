#ifndef NOEUD_H
#define NOEUD_H

#include <iostream>
#include "GameEngine.hpp"
#include <list>

using namespace std;

class Noeud
{
public:
    Noeud(GameEngine gameEngineGiven, int scoreGiven);
    Noeud& addChild(GameEngine gameEngine, int Score);

    private:
        int score{0};
        GameEngine gameEngine;
        list<Noeud *> fils;
};

#endif