#ifndef BOT_H
#define BOT_H

#include <iostream>
#include "GameEngine.hpp"
#include "Config.hpp"
#include <vector>
#include <set>

using namespace std;

class Bot
{
public:
    pair<pair<int, int>, pair<int, int>> getNextmove(Config::eval evGiven);
    Bot(GameEngine& gameEngine);

private:
    GameEngine& gameEngine;
    Config::eval ev;
    set<pair<int, int>> bombHitted_player1;
    set<pair<int, int>> bombHitted_player2;
    bool verifyPlay(pair<int, int> position);
    pair<int, int> getRandomOldPosition();
    pair<int, int> getRandomNewPosition(pair<int, int> oldPosition);
    double minMax(GameEngine& gameEngine, bool isMax, int depth);
    vector<pair<int, int>> getOldPosition(GameEngine gameEngine);
    vector<pair<int, int>> getNewPosition(pair<int, int> pair, GameEngine gameEngine);
    pair<pair<int, int>, pair<int, int>> decisionMax(GameEngine& gameEngine);

    double getDistanceFromNearestTower(GameEngine &gameEngine, pair<int, int> position, Player &player);
    double getDistanceFromFocusedTower(GameEngine &gameEngine, pair<int, int> position, Player &player);

    double evalFctFocusedTower(GameEngine &gameEngine);
    double evalFctNearbyTower(GameEngine &gameEngine);

    double alphabeta(GameEngine &gameEngine, bool isMax, int depth, double A, double B);
};

#endif