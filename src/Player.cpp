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
void Player::addArmy(const std::pair<int, int> position, int powerArmy)
{
    if(isArmy(position)){
        army[position] =  getArmyPower(position) + powerArmy;
    }else{
        army.insert(std::pair<std::pair<int, int>, int>(position, powerArmy));
    }
}

bool Player::isArmy(const std::pair<int, int> position)
{
    std::map<std::pair<int, int>, int>::iterator it = army.find(position);
    bool b = (it != army.end());
    return b;
}

int Player::getArmyPower(const std::pair<int, int> position)
{
    return army.find(position)->second;
}

int Player::getId(){
    return id;
}

Player::~Player()
{
}