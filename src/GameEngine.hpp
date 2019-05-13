#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Square.hpp"
#include <map>

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();
    Square& getSquare(int i,int j);

private:
    int generateNumber0into100();
    std::map<std::pair<int, int>, Square> board;
    const int PROBABOMB{20};
    const int GRIDSIZE = 12;
    const std::pair<int,int> SPAWNP1{5,0};
    const std::pair<int, int> SPAWNP2{5, 10};

    const std::pair<int, int> TOWER1{1, 5};
    const std::pair<int, int> TOWER2{5, 5};
    const std::pair<int, int> TOWER3{9, 5};
};

#endif