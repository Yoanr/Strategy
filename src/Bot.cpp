#include "Bot.hpp"
#include <unistd.h>
#include <math.h>
#include <algorithm>

#include <chrono>

void print(std::vector<pair<int,int>> input)
{
    for (unsigned int i = 0; i < input.size(); i++)
    {
     //   std::cout << input.at(i).first << " " << input.at(i).second << std::endl;
    }
}

void printd(std::vector<double> input)
{
    for (unsigned int i = 0; i < input.size(); i++)
    {
     //   std::cout << input.at(i) <<std::endl;
    }
}

Bot::Bot(GameEngine &gameEngineGiven) : gameEngine(gameEngineGiven)
{
    srand(time(NULL));
}

pair<pair<int, int>, pair<int, int>> Bot::getNextmove(Config::eval evGiven)
{
    ev = evGiven;
    if(evGiven == Config::eval::randomStrategy){
        auto oldPosition = getRandomOldPosition();
        return pair<pair<int, int>, pair<int, int>>(oldPosition, getRandomNewPosition(oldPosition));
    }
    /*auto start = chrono::steady_clock::now();
    auto decision = decisionMax(gameEngine);
    auto end = chrono::steady_clock::now();

    cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;

         return decision;*/
    return decisionMax(gameEngine);
}

bool Bot::verifyPlay(pair<int,int> position){
    return
    position.first < Config::NUMBEROFSQUARE &&
    position.first >= 0 &&
    position.second < Config::NUMBEROFSQUARE &&
    position.second >= 0;
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
pair<pair<int,int>,pair<int,int>> Bot::decisionMax(GameEngine& gameEngine){
    vector<pair<int, int>> oldIndexes = getOldPosition(gameEngine);
    // std::cout<< "ancien choix" << std::endl;
    print(oldIndexes);
    pair<pair<int,int>,pair<int,int>> bestAction;
    double valeurMin =  numeric_limits<double>::infinity();
    for (std::size_t i = 0; i < oldIndexes.size(); i++)
    {
       // std::cout << "oldPosition" << oldIndexes[i].first << ',' << oldIndexes[i].second << std::endl;
        vector<pair<int, int>> newIndexes = getNewPosition(oldIndexes[i]);
        for (std::size_t j = 0; j < newIndexes.size(); j++)
        {
            if (verifyPlay(newIndexes[j]))
            {
               // std::cout<< "newPositon " << newIndexes[j].first <<',' << newIndexes[j].second << std::endl;
                GameEngine *copy = new GameEngine();
                *copy = gameEngine;
                copy->play(oldIndexes[i], newIndexes[j]);

                //double value = minMax(*copy, true, Config::DEPTH);
                double value = alphabeta(*copy, true, Config::DEPTH, -numeric_limits<double>::infinity(), numeric_limits<double>::infinity());
                delete(copy);;

                if (value < valeurMin)
                {
                   // std::cout << "Here" << std::endl;
                    valeurMin = value;
                    bestAction = pair<pair<int, int>, pair<int, int>>(oldIndexes[i], newIndexes[j]);
                }
                // std::cout << "valueMax" << valueMax << std::endl;
                // cout<<endl;
            }

        }
    }
    // std::cout << "(" << bestAction.first.first << ","<< bestAction.first.second << ")";
    // std::cout << "(" << bestAction.second.first << "," << bestAction.second.second << ")" << std::endl;
    return bestAction;
}
//double Bot::alphabeta(){
//}
double Bot::minMax(GameEngine& gameEngine,bool isMax,int depth)
{
    /*if (gameEngine.getHasWon())
    {
        std::cout << "Win node! " << std::endl;
        return - numeric_limits<double>::infinity();

    }
    if(gameEngine.getHasLose()){
        //std::cout << "Loose node! "<< std::endl;
        return  numeric_limits<double>::infinity();
    }*/
    if(depth == 0 ||gameEngine.getHasLose() ||gameEngine.getHasWon()){
        //std::cout << " depth: " << depth << " evalFunction: " << evalFunction(gameEngine) << " player: " << gameEngine.getCurrentIdPlayer() << endl;
        if (ev == Config::eval::focusStrategy)
        {
            return evalFctFocusedTower(gameEngine, isMax);
        }
        else if (ev == Config::eval::nearbyStrategy)
        {
            return evalFctNearbyTower(gameEngine, isMax);
        }
    }
    vector<double> vals;
    vector<pair<int, int>> oldIndexes = getOldPosition(gameEngine);
    for (std::size_t i = 0; i < oldIndexes.size(); i++)
    {
        vector<pair<int, int>> newIndexes = getNewPosition(oldIndexes[i]);

        for (std::size_t j = 0; j < newIndexes.size(); j++)
        {
            if (verifyPlay(newIndexes[j]))
            {
                GameEngine *copy = new GameEngine();
                *copy = gameEngine;
                copy->play(oldIndexes[i], newIndexes[j]);
                vals.push_back(minMax(*copy,(not isMax),depth-1));
                delete(copy);
            }
        }
    }
    if(isMax){
        //std::cout  << "max" << *max_element(begin(vals), end(vals)) << std::endl;
        return *max_element(begin(vals), end(vals));
    }else{
        //std::cout << "min" << *min_element(begin(vals), end(vals)) << std::endl;
        return *min_element(begin(vals), end(vals));
    }

}

double Bot::getDistanceFromNearestTower(GameEngine& gameEngine, pair<int,int> position, Player& player){
    double yFixed = 5;

    double x = static_cast<double> (position.first);
    double y = static_cast<double> (position.second);

    double yDistance = abs(yFixed - y);
    double xTower1 = abs(gameEngine.TOWER1.first - x);
    double xTower2 = abs(gameEngine.TOWER2.first - x);
    double xTower3 = abs(gameEngine.TOWER3.first - x);

    //Check if the tower is already captured
    bool checkTower1 = gameEngine.checkTowerCapturedByPlayer(gameEngine.TOWER1, player),
         checkTower2 = gameEngine.checkTowerCapturedByPlayer(gameEngine.TOWER2, player),
         checkTower3 = gameEngine.checkTowerCapturedByPlayer(gameEngine.TOWER3, player);

    if(checkTower1){
        xTower1 =  numeric_limits<double>::infinity();
    }
    if(checkTower2){
        xTower2 =  numeric_limits<double>::infinity();
    }
    if(checkTower3){
        xTower3 =  numeric_limits<double>::infinity();
    }


    double xMin = std::min(std::min(xTower1, xTower2), xTower3);

    if(checkTower1 && checkTower2 && checkTower3){
        xMin = 0;
    }

    return xMin+yDistance+1;
}

double Bot::evalFctFocusedTower(GameEngine &gameEngine, int isMax)
{
    map<pair<int, int>, int> currentArmy = gameEngine.getCurrentPlayer().getArmy();
    map<pair<int, int>, int> ennemyArmy = gameEngine.getEnnemyPlayer().getArmy();
    double currentSum = 0, ennemySum = 0;

    for (map<pair<int, int>, int>::iterator it1 = currentArmy.begin(); it1 != currentArmy.end(); ++it1)
    {
        currentSum += gameEngine.getCurrentPlayer().getNumberOfTowerCaptured() + (static_cast<double>(it1->second) / getDistanceFromFocusedTower(gameEngine, it1->first, gameEngine.getCurrentPlayer()));
    }

    for (map<pair<int, int>, int>::iterator it2 = ennemyArmy.begin(); it2 != ennemyArmy.end(); it2++)
    {
        ennemySum += gameEngine.getEnnemyPlayer().getNumberOfTowerCaptured() + (static_cast<double>(it2->second) / getDistanceFromFocusedTower(gameEngine, it2->first, gameEngine.getEnnemyPlayer()));
    }
    if(not isMax){
        return ennemySum - currentSum;
    }
    return currentSum - ennemySum;
}

double Bot::evalFctNearbyTower(GameEngine &gameEngine, int isMax)
{

    map<pair<int, int>, int> currentArmy = gameEngine.getCurrentPlayer().getArmy();
    map<pair<int, int>, int> ennemyArmy = gameEngine.getEnnemyPlayer().getArmy();
    double currentSum = 0, ennemySum = 0;

    for (map<pair<int, int>, int>::iterator it1 = currentArmy.begin(); it1 != currentArmy.end(); ++it1)
    {
        currentSum +=gameEngine.getCurrentPlayer().getNumberOfTowerCaptured() +  (static_cast<double>(it1->second) / getDistanceFromNearestTower(gameEngine, it1->first, gameEngine.getCurrentPlayer()));
    }

    for (map<pair<int, int>, int>::iterator it2 = ennemyArmy.begin(); it2 != ennemyArmy.end(); it2++)
    {
        ennemySum += gameEngine.getEnnemyPlayer().getNumberOfTowerCaptured() + (static_cast<double>(it2->second) / getDistanceFromNearestTower(gameEngine, it2->first, gameEngine.getEnnemyPlayer()));
    }
    if (not isMax)
    {
        return ennemySum - currentSum;
    }
    return currentSum - ennemySum;
}


double Bot::getDistanceFromFocusedTower(GameEngine &gameEngine, pair<int, int> position,Player& player)
{
    pair<int,int> focusedTower = gameEngine.TOWER1;
    if (gameEngine.checkTowerCapturedByPlayer(gameEngine.TOWER1, player))
    {
        focusedTower = gameEngine.TOWER2;
    }
    if (gameEngine.checkTowerCapturedByPlayer(gameEngine.TOWER1, player) && gameEngine.checkTowerCapturedByPlayer(gameEngine.TOWER2, player))
    {
        focusedTower = gameEngine.TOWER3;
    }
    //std::cout << "focusedTower: " << focusedTower.first << " " << focusedTower.second << std::endl;

    double yFixed = 5;

    double x = static_cast<double>(position.first);
    double y = static_cast<double>(position.second);

    double yDistance = abs(yFixed - y);
    double xTower1 = abs(focusedTower.first - x);
    return xTower1 + yDistance+1;
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

double Bot::alphabeta(GameEngine& gameEngine, bool isMax, int depth,double A,double B)
{
    if (depth == 0 || gameEngine.getHasLose() || gameEngine.getHasWon())
    {
        if (ev == Config::eval::focusStrategy)
        {
            return evalFctFocusedTower(gameEngine,isMax);
        }
        else if (ev == Config::eval::nearbyStrategy)
        {
            return evalFctNearbyTower(gameEngine, isMax);
        }
    }

    if (isMax)
    {
        double value = -numeric_limits<double>::infinity();
        vector<pair<int, int>> oldIndexes = getOldPosition(gameEngine);
        for (std::size_t i = 0; i < oldIndexes.size(); i++)
        {
            vector<pair<int, int>> newIndexes = getNewPosition(oldIndexes[i]);

            for (std::size_t j = 0; j < newIndexes.size(); j++)
            {
                if (verifyPlay(newIndexes[j]))
                {
                    GameEngine *copy = new GameEngine();
                    *copy = gameEngine;
                    copy->play(oldIndexes[i], newIndexes[j]);
                    value = std::max(value, alphabeta(*copy, false, depth - 1, A, B));
                    if(value >= B){
                        return value;
                    }
                    A = std::max(A,value);
                    delete (copy);
                }
            }
        }
        return value;
    }
    else
    {
        double value = numeric_limits<double>::infinity();
        vector<pair<int, int>> oldIndexes = getOldPosition(gameEngine);
        for (std::size_t i = 0; i < oldIndexes.size(); i++)
        {
            vector<pair<int, int>> newIndexes = getNewPosition(oldIndexes[i]);

            for (std::size_t j = 0; j < newIndexes.size(); j++)
            {
                if (verifyPlay(newIndexes[j]))
                {
                    GameEngine *copy = new GameEngine();
                    *copy = gameEngine;
                    copy->play(oldIndexes[i], newIndexes[j]);
                    value = std::min(value, alphabeta(*copy, true, depth - 1, A, B));
                    if(A >= value){
                        return value;
                    }
                    B = std::min(B,value);
                    delete (copy);
                }
            }
        }
        return value;
    }
}
