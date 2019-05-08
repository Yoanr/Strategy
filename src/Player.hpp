#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>

class Player
{
public:
    Player();
    ~Player();

private:
    std::string name;
    int id;
};

#endif