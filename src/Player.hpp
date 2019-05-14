#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <map>

class Player
{
public:
    Player(int id);
    ~Player();
    int getId();
    void addArmy(const std::pair<int, int> position, int powerArmy);
    bool isArmy(const std::pair<int, int> position);
    int getArmyPower(const std::pair<int, int> position);

private:
    int id;
    float r;
    float g;
    float b;
    float a;
    std::map<std::pair<int, int>, int> army;
};

#endif