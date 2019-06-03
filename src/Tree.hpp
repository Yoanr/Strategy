#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "Noeud.hpp"
#include <vector>
#include "Config.hpp"

using namespace std;

class Tree
{
public:
    Tree();

private:
    bool verifyPlay(pair<int, int> position);
    GameEngine gameEngine;
    Noeud root{gameEngine,0};
    vector<pair<int, int>> getOldPosition(GameEngine gameEngine);
    vector<pair<int, int>> getNewPosition(pair<int, int> pair);
    void performTree(GameEngine gameEngine, Noeud& noeud);
};

#endif