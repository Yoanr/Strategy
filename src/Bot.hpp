#ifndef BOT_H
#define BOT_H

#include <iostream>
#include "GameEngine.hpp"
#include "Config.hpp"

using namespace std;

class Bot
{
public:
    pair<pair<int, int>, pair<int, int>> getNextmove();
    Bot(GameEngine& gameEngine);

private:
    GameEngine& gameEngine;
    bool verifyPlay(pair<int, int> position);
    pair<int, int> getRandomOldPosition();
    pair<int, int> getRandomNewPosition(pair<int, int> oldPosition);
};

#endif