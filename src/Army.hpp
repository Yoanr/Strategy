#ifndef ARMY_H
#define ARMY_H

#include "Player.hpp"

class Army
{
public:
    Army();
    ~Army();

private:
    int power;
    Player player;
};

#endif