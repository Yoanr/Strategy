#include "Bot.hpp"
#include <unistd.h>

Bot::Bot(GameEngine &gameEngineGiven) : gameEngine(gameEngineGiven)
{
    srand(time(NULL));
}

pair<pair<int, int>, pair<int, int>> Bot::getNextmove()
{
    auto oldPosition = getRandomOldPosition();

    return pair<pair<int, int>, pair<int, int>>(oldPosition, getRandomNewPosition(oldPosition));
}

bool Bot::verifyPlay(pair<int,int> position){
    if (position.first < Config::NUMBEROFSQUARE && position.first >= 0 && position.second < Config::NUMBEROFSQUARE && position.second >= 0)
    {
        return true;
    }
    return false;
}

pair<int, int> Bot::getRandomOldPosition()
{
    map<pair<int, int>, int> localArmy = gameEngine.getCurrentPlayer().getArmy();
    int armySize = gameEngine.getCurrentPlayer().getArmySize();
    int randomIndex = rand() % armySize + 0;
    return gameEngine.getCurrentPlayer().getPositionByIndex(randomIndex);
}

pair<int, int> Bot::getRandomNewPosition(pair<int, int> oldPosition)
{
    int randomNeighbours = rand() % 4 + 0;
    pair<int, int> newPosition;
    do
    {
        if (randomNeighbours == 0)
        {
            newPosition.first = oldPosition.first + 1;
            newPosition.second = oldPosition.second;
        }
        else if (randomNeighbours == 1)
        {
            newPosition.first = oldPosition.first;
            newPosition.second = oldPosition.second + 1;
        }
        else if (randomNeighbours == 2)
        {
            newPosition.first = oldPosition.first - 1;
            newPosition.second = oldPosition.second;
        }
        else if (randomNeighbours == 3)
        {
            newPosition.first = oldPosition.first;
            newPosition.second = oldPosition.second - 1;
        }
        randomNeighbours++;
        randomNeighbours = randomNeighbours % 3;
    } while (not(verifyPlay(newPosition)));
    return newPosition;
}

