#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Square.hpp"
#include "Player.hpp"
#include <map>

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();
    void idle();
    std::pair<int,int> getPossibleArmy(int i,int j);
    Square& getSquare(int i,int j);
    void setSelectedSquare(std::pair<int, int>);
    std::pair<int,int> getSelectedSquare();
    void resetSelectedSquare();
    bool armyPresent(std::pair<int, int>);
    void switchCurrentPlayer();

private:
    int generateNumber0into100();
    std::map<std::pair<int, int>, Square> board;
    const int PROBABOMB{20};
    const int GRIDSIZE = 12;
    const std::pair<int, int> SPAWNP1{5, 0};
    const std::pair<int, int> SPAWNP2{5, 10};

    const std::pair<int, int> TOWER1{1, 5};
    const std::pair<int, int> TOWER2{5, 5};
    const std::pair<int, int> TOWER3{9, 5};

    int numberOfRound{0};
    void round(Player player, const std::pair<int, int> SPAWN);
    std::pair<int, int> selectedSquareIndexes{-1, -1};
    Player player1{1};
    Player player2{2};
    Player currentPlayer{player1};
};

#endif