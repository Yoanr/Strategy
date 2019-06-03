#include "Noeud.hpp"

Noeud::Noeud(GameEngine gameEngineGiven, int scoreGiven) : score(scoreGiven), gameEngine(gameEngineGiven){
}


Noeud& Noeud::addChild(GameEngine gameEngine, int score){
    Noeud* refnoeud = new Noeud(gameEngine,score);
    fils.push_back(refnoeud);
    return *refnoeud;
}