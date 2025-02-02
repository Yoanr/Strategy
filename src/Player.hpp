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

    void moveOrMergeArmy(const pair<int, int> position, int powerArmy);
    void moveArmy(const pair<int, int> oldPosition, const pair<int, int> newPosition);
    void mergeArmy(const pair<int, int> oldPosition, const pair<int, int> newPosition);
    void deleteArmy(pair<int, int> position);
    void changeArmy(const pair<int, int> position, int powerArmy);

    bool isArmy(const pair<int, int> position);
    int getArmyPower(const pair<int, int> position);
    int getArmySize();
    map<pair<int, int>, int>& getArmy();
    int getNumberOfTowerCaptured();
    void numberOfTowerCapturedIncremented();
    void numberOfTowerCapturedDecremented();
    int getTotalPowerArmy();

    void numberOfBombHitedIncremented();
    int getNumberofBombHitted();

    pair<int,int> getPositionByIndex(int index);

private:
    int id;
    float r;
    float g;
    float b;
    float a;
    map<pair<int, int>, int> army;
    int numberOfTowerCaptured{0};
    int numberOfBombHited{0};
};

#endif