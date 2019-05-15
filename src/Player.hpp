#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <map>

using namespace std;

class Player
{
public:
    Player(int id);
    ~Player();
    int getId();
    void addArmy(const pair<int, int> position, int powerArmy);
    void moveArmy(const pair<int, int> oldPosition, const pair<int, int> newPosition);
    bool isArmy(const pair<int, int> position);
    int getArmyPower(const pair<int, int> position);
    int getArmySize();

private:
    int id;
    float r;
    float g;
    float b;
    float a;
    map<pair<int, int>, int> army;
};

#endif