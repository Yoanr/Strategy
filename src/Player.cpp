#include "Player.hpp"

Player::Player(int idGiven) : id(idGiven){
}
void Player::addArmy(const std::pair<int, int> position, int powerArmy)
{
    if(isArmy(position)){
        army[position] =  getArmyPower(position) + powerArmy;
    }else{
        std::cout << position.first << " " << position.second << std::endl;
        army.insert(std::pair<std::pair<int, int>, int>(position, powerArmy));
    }
}

bool Player::isArmy(const std::pair<int, int> position)
{
    std::map<std::pair<int, int>, int>::iterator it = army.find(position);
    bool b = (it != army.end());
    std::cout << "bool " << b << std::endl;
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