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
void Player::addArmy(const pair<int, int> position, int powerArmy)
{
    if(isArmy(position)){
        army[position] =  getArmyPower(position) + powerArmy;
    }else{
        army.insert(pair<pair<int, int>, int>(position, powerArmy));
    }
}

void Player::moveArmy(const pair<int, int> oldPosition, const pair<int, int> newPosition){
    if(army.find(oldPosition) != army.end()) {
        int armyPower = army[oldPosition];
        army.erase(oldPosition);
        addArmy(newPosition, armyPower);
    }
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
    return army.find(position)->second;
}

int Player::getId(){
    return id;
}

Player::~Player()
{
}