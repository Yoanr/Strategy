#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Square.hpp"
#include "Player.hpp"
#include <map>
using namespace std;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();
    void idle();
    pair<int, int> getPossibleArmy(pair<int, int> position);
    Square &getSquare(pair<int, int> position);
    void setSelectedSquare(pair<int, int>);
    pair<int,int> getSelectedSquare();
    void resetSelectedSquare();
    bool armyPresent(pair<int, int>);
    void switchCurrentPlayer();
    int getCurrentIdPlayer();
    int getCurrentRound();

private:
    int generateNumber0into100();
    map<pair<int, int>, Square> board;
    const int PROBABOMB{20};
    const int GRIDSIZE = 12;
    const pair<int, int> SPAWNP1{5, 0};
    const pair<int, int> SPAWNP2{5, 10};

    const pair<int, int> TOWER1{1, 5};
    const pair<int, int> TOWER2{5, 5};
    const pair<int, int> TOWER3{9, 5};

    int numberOfRound{0};
    void round(Player player, const pair<int, int> SPAWN);
    pair<int, int> selectedSquareIndexes{-1, -1};
    Player player1{1};
    Player player2{2};
    Player currentPlayer{player1};
    int currentRound{1};
};

#endif