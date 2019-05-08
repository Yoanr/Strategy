#ifndef Game_H
#define Game_H

#include <map>
#include "Square.hpp"

class Game
{
public:
    Game();
    ~Game();

private:
std::map<std::pair<int,int>,Square> board;

};

#endif