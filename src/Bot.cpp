#include "Bot.hpp"
#include <unistd.h>
#include <math.h>
#include <algorithm>

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

/*
function minimax(node, depth, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, depth − 1, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, depth − 1, TRUE))
        return value
*/
pair<pair<int,int>,pair<int,int>> Bot::decisionMax(GameEngine gameEngine){
    vector<pair<pair<int,int>,pair<int,int>>> coups;
    vector<pair<int, int>> oldIndexes = getOldPosition(gameEngine);
    pair<pair<int,int>,pair<int,int>> bestAction;
    double valueMax = - numeric_limits<double>::infinity();
    for (std::size_t i = 0; i < oldIndexes.size(); i++)
    {
        vector<pair<int, int>> newIndexes = getNewPosition(oldIndexes[i]);

        for (std::size_t j = 0; j < newIndexes.size(); j++)
        {
            if (verifyPlay(newIndexes[j]))
            {
                GameEngine *copy = new GameEngine();
                *copy = gameEngine;
                double value = minMax(copy, false, Config::DEPTH);

                if (value > valueMax)
                {
                    valueMax = value;
                    bestAction = pair<pair<int, int>, pair<int, int>>(oldIndexes[i], newIndexes[i]);
                }
            }
        }
    }
    return bestAction;
}

double Bot::minMax(GameEngine* gameEngine,bool isMax,int depth)
{
    if (gameEngine->getHasWon() || depth == 0)
    {
        return evalFunction(*gameEngine);

    }
    vector<double> vals;
    vector<pair<int, int>> oldIndexes = getOldPosition(*gameEngine);
    for (std::size_t i = 0; i < oldIndexes.size(); i++)
    {
        vector<pair<int, int>> newIndexes = getNewPosition(oldIndexes[i]);

        for (std::size_t j = 0; j < newIndexes.size(); j++)
        {
            if (verifyPlay(newIndexes[j]))
            {
                gameEngine->play(oldIndexes[i], newIndexes[j]);
                vals.push_back(minMax(gameEngine,(not isMax),depth-1));
            }
        }
    }
    if(isMax){
        return *max_element(begin(vals), end(vals));
    }else{
        return *min_element(vals.begin(), vals.end());
    }

}
double Bot::evalFunction(GameEngine gameEngine){
    map<pair<int, int>, int> currentArmy = gameEngine.getCurrentPlayer().getArmy();
    map<pair<int, int>, int> ennemyArmy = gameEngine.getEnnemyPlayer().getArmy();
    double currentSum=0,ennemySum=0;

    for (map<pair<int, int>, int>::iterator it = currentArmy.begin(); it != currentArmy.end(); ++it)
    {
        currentSum += (1 / getDistanceFromNearestTower(gameEngine,it->first)) * it->second;
    }

    for (map<pair<int, int>, int>::iterator it = ennemyArmy.begin(); it != ennemyArmy.end(); ++it)
    {
        ennemySum += (1 / getDistanceFromNearestTower(gameEngine, it->first)) * it->second;
    }
    return currentSum - ennemySum;
}

int Bot::getDistanceFromNearestTower(GameEngine gameEngine, pair<int,int> position){
    int yFixed = 5;
    int xMin = 10;

    int x = position.first;
    int y = position.second;

    int yDistance = abs(yFixed-y);
    int xTower1 = abs(gameEngine.TOWER1.first - x);
    int xTower2 = abs(gameEngine.TOWER2.first - x);
    int xTower3 = abs(gameEngine.TOWER3.first - x);
    xMin = std::min(std::min(xTower1, xTower2), xTower3);
    return xMin+yDistance;
}


vector<pair<int, int>> Bot::getOldPosition(GameEngine gameEngine)
{
    map<pair<int, int>, int> m = gameEngine.getCurrentPlayer().getArmy();
    vector<pair<int, int>> v;
    for (map<pair<int, int>, int>::iterator it = m.begin(); it != m.end(); ++it)
    {
        v.push_back(it->first);
    }
    return v; // pointer ? ref ?
}

vector<pair<int, int>> Bot::getNewPosition(pair<int, int> pair)
{
    vector<std::pair<int, int>> v;

    v.push_back(std::pair<int, int>(pair.first + 1, pair.second));
    v.push_back(std::pair<int, int>(pair.first, pair.second + 1));
    v.push_back(std::pair<int, int>(pair.first - 1, pair.second));
    v.push_back(std::pair<int, int>(pair.first, pair.second - 1));

    return v; // pointer ? ref ?
}
