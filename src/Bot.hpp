#ifndef BOT_H
#define BOT_H

#include <iostream>
#include "GameEngine.hpp"
#include "Config.hpp"
#include <vector>

using namespace std;

class Bot
{
public:
    Bot(GameEngine &gameEngine);
    pair<pair<int, int>, pair<int, int>> getNextmove(Config::eval evGiven);
private:
    GameEngine& gameEngine;
    Config::eval ev;
    vector<pair<int, int>> bombHitted;

    pair<int, int> getRandomOldPosition();
    bool verifyPlay(pair<int, int> position);
    pair<int, int> getRandomNewPosition(pair<int, int> oldPosition);

    // AI algorith
    pair<pair<int, int>, pair<int, int>> decisionMax(GameEngine &gameEngine);
    double alphabeta(GameEngine &gameEngine, bool isMax, int depth, double A, double B);

    vector<pair<int, int>> getOldPosition(GameEngine gameEngine);
    vector<pair<int, int>> getNewPosition(pair<int, int> pair);

    // evaluation function
    double evalFctFocusedTower(GameEngine &gameEngine, int isMax);
    double evalFctNearbyTower(GameEngine &gameEngine, int isMax);

    // intermediary function
    double getDistanceFromNearestTower(GameEngine &gameEngine, pair<int, int> position, Player &player);
    double getDistanceFromFocusedTower(GameEngine &gameEngine, pair<int, int> position, Player &player);

};

#endif