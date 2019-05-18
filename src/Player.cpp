#include "Player.hpp"

Player::Player(int idGiven) : id(idGiven){
    switch (idGiven)
    {
        case 1:
            r = 1;
            g = 0;
            b = 0;
            a = 1;
            break;

        case 2:
            r = 0;
            g = 0;
            b = 1;
            a = 1;
            break;
    }
}

void Player::changeArmy(const pair<int, int> position, int powerArmy)
{
    if (isArmy(position))
    {
        army[position] =  powerArmy;
    }
}

void Player::moveOrMergeArmy(const pair<int, int> position, int armyPower)
{
    if (isArmy(position)){
        army[position] = getArmyPower(position) + armyPower;
    }else{
        army.insert(pair<pair<int, int>, int>(position, armyPower));
    }
}

void Player::moveArmy(const pair<int, int> oldPosition, const pair<int, int> newPosition)
{
    int armyPower = getArmyPower(oldPosition);
    deleteArmy(oldPosition);
    army.insert(pair<pair<int, int>, int>(newPosition, armyPower));
}

void Player::deleteArmy(const pair<int, int> position)
{
    army.erase(position);
}

void Player::mergeArmy(const pair<int, int> oldPosition, const pair<int, int> newPosition)
{
    int armyPower = getArmyPower(oldPosition);
    deleteArmy(oldPosition);
    army[newPosition] = getArmyPower(newPosition) + armyPower;
}

int Player::getArmySize(){
    return army.size();
}

bool Player::isArmy(const pair<int, int> position)
{
    map<pair<int, int>, int>::iterator it = army.find(position);
    bool b = (it != army.end());
    return b;
}

int Player::getArmyPower(const pair<int, int> position)
{
    return army[position];
}

int Player::getId(){
    return id;
}

Player::~Player()
{
}

int Player::getNumberOfTowerCaptured(){
    return numberOfTowerCaptured;
}
void Player::numberOfTowerCapturedIncremented()
{
    numberOfTowerCaptured++;
}
void Player::numberOfTowerCapturedDecremented()
{
    numberOfTowerCaptured--;
}

void Player::numberOfBombHitedIncremented(){
    numberOfBombHited++;
}
int Player::getNumberofBombHitted(){
    return numberOfBombHited;
}

int Player::getTotalPowerArmy(){
    int totalPowerArmy{0};
    for (map<pair<int, int>, int>::iterator it = army.begin(); it != army.end();++it){
        totalPowerArmy=+it->second;
    }
    return totalPowerArmy;
}