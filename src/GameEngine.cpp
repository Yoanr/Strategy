#include "GameEngine.hpp"

int GameEngine::generateNumber0into100(){
    srand(time(NULL));
    return rand() % 100 + 0;
}
GameEngine::GameEngine(){
    player1.addArmy(std::pair<int,int>(1,1),1);
    player2.addArmy(std::pair<int, int>(2, 2), 1);
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            std::pair<int, int> ij = std::pair<int, int>(i, j);
            Square::Type currentType = Square::Type::basic;

            if ((i == TOWER1.first && j == TOWER1.second) || (i == TOWER2.first && j == TOWER2.second) || (i == TOWER3.first && j == TOWER3.second))
            {
                currentType = Square::Type::tower;
            }
            else if (i == SPAWNP1.first && j == SPAWNP1.second){
                currentType = Square::Type::spawn1;
            }
            else if((i == SPAWNP2.first && j == SPAWNP2.second)){
                currentType = Square::Type::spawn2 ;
            }
            else if (generateNumber0into100() < PROBABOMB && ((i != SPAWNP1.first && j != SPAWNP1.second)))
            {
                currentType = Square::Type::bomb;
            }
            board.insert(std::pair<std::pair<int, int>, Square>(ij, Square(currentType)));
        }
    }
}

std::pair<int,int> GameEngine::getPossibleArmy(int i,int j){
    std::pair<int,int> position(i,j);
    
    if (player1.isArmy(position))
    {
        return std::pair<int, int>(1, player1.getArmyPower(position));
    }
    else if (player2.isArmy(std::pair<int, int>(i, j)))
    {
        return std::pair<int, int>(2, player2.getArmyPower(position));
    }
    return std::pair<int,int>(0,0);
}

Square& GameEngine::getSquare(int i, int j){
    std::map<std::pair<int, int>, Square>::iterator it = board.find(std::pair<int, int>(i, j));
    return it->second;
}

int GameEngine::getCurrentIdPlayer(){
    return currentPlayer.getId();
}

void GameEngine::round(Player player, const std::pair<int, int> SPAWN)
{
    player.addArmy(SPAWN,1);
}

void GameEngine::idle(){
   for(;;){

       round(player1,SPAWNP1);
       round(player2, SPAWNP2);

       numberOfRound++;
   }
}

bool GameEngine::armyPresent(std::pair<int, int> indexes)
{
    bool b = currentPlayer.isArmy(indexes);
    return b;
}

void GameEngine::setSelectedSquare(std::pair<int, int> indexes)
{
    selectedSquareIndexes = indexes;
}

void GameEngine::resetSelectedSquare()
{
    selectedSquareIndexes = std::pair<int,int>(-1,-1);
}

void GameEngine::switchCurrentPlayer(){
    if(currentPlayer.getId() == 1){
        currentPlayer = player2;
    }else {
        currentPlayer = player1;
        currentRound++;
    }
}

int GameEngine::getCurrentRound(){
    return currentRound;
}

std::pair<int, int> GameEngine::getSelectedSquare()
{
    return selectedSquareIndexes;
}

GameEngine::~GameEngine()
{
}