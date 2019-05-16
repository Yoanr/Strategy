#include "GameEngine.hpp"
#include <unistd.h>

int GameEngine::generateNumber0into100(){
    srand(time(NULL));
    return rand() % 100 + 0;
}
GameEngine::GameEngine(){
    player1.moveOrMergeArmy(SPAWNP1, 1);
    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            pair<int, int> ij = pair<int, int>(i, j);
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
            board.insert(pair<pair<int, int>, Square>(ij, Square(currentType)));
        }
    }
}

pair<int, int> GameEngine::getPossibleArmy(pair<int, int> position)
{
    if (player1.isArmy(position))
    {
        return pair<int, int>(1, player1.getArmyPower(position));
    }
    else if (player2.isArmy(position))
    {
        return pair<int, int>(2, player2.getArmyPower(position));
    }
    return pair<int,int>(0,0);
}

Square &GameEngine::getSquare(pair<int, int> position)
{
    map<pair<int, int>, Square>::iterator it = board.find(position);
    return it->second;
}

int GameEngine::getCurrentIdPlayer(){
    return currentPlayerId;
}

int GameEngine::getEnnemyIdPlayer()
{
    return getEnnemyPlayer().getId();
}

bool GameEngine::armyPresent(pair<int, int> indexes)
{
    bool b = getCurrentPlayer().isArmy(indexes);
    return b;
}

void GameEngine::setSelectedSquare(pair<int, int> indexes)
{
    selectedSquareIndexes = indexes;
}

void GameEngine::resetSelectedSquare()
{
    selectedSquareIndexes = pair<int,int>(-1,-1);
}

void GameEngine::switchCurrentPlayerId(){
    if(currentPlayerId == 1){
        currentPlayerId = 2;
        player2.moveOrMergeArmy(SPAWNP2, 1);
    }else {
        currentPlayerId = 1;
        player1.moveOrMergeArmy(SPAWNP1, 1);
        currentRound++;
    }
}

Player& GameEngine::getCurrentPlayer(){
    if (currentPlayerId == 1) {
        return player1;
    } else {
        return player2;
    }
}

Player& GameEngine::getEnnemyPlayer()
{
    if (currentPlayerId == 1)
    {
        return player2;
    }
    else
    {
        return player1;
    }
}

void GameEngine::fightPlayerArmy(pair<int, int> oldPosition, pair<int, int> newPosition){
    
    int armyPowerCurrentPlayer = getCurrentPlayer().getArmyPower(oldPosition);
    getCurrentPlayer().deleteArmy(oldPosition);

    int armyPowerEnnemyPlayer = getEnnemyPlayer().getArmyPower(newPosition);

    while (armyPowerCurrentPlayer > 0 && armyPowerEnnemyPlayer > 0){
        int proportion = 100 / (armyPowerCurrentPlayer + armyPowerEnnemyPlayer);
        sleep(1);
        int rand = generateNumber0into100();
        std::cout << "rand: " << rand << std::endl;
        if ( rand < proportion * armyPowerCurrentPlayer){
            armyPowerEnnemyPlayer--;
            std::cout << "fight won current" << std::endl;
        }else{
            armyPowerCurrentPlayer--;
            std::cout << "fight won ennemy" << std::endl;
        }
        std::cout << "resume fight: pcurrent" << armyPowerCurrentPlayer << ", pennemy" << armyPowerEnnemyPlayer << std::endl;
    }
    
    if (armyPowerCurrentPlayer>0){
        getCurrentPlayer().moveArmy(oldPosition,newPosition);
        getEnnemyPlayer().deleteArmy(newPosition);
    }else{
        getEnnemyPlayer().changeArmy(newPosition,armyPowerEnnemyPlayer);
    }
}

int GameEngine::getCurrentRound(){
    return currentRound;
}

void GameEngine::play(pair<int, int> oldPosition, pair<int, int> newPosition){
    resetSelectedSquare();
    getSquare(oldPosition).setA(1);

    pair<int, int> possibleArmy = getPossibleArmy(newPosition);
    int idPossiblePlayerArmy = possibleArmy.first;

    getSquare(oldPosition).setColor(color::white);
    setColorSquareByPlayer(newPosition, getCurrentIdPlayer());

    if (idPossiblePlayerArmy == Square::Type::basic)
    {
        getCurrentPlayer().moveArmy(oldPosition, newPosition);
    }
    else if (idPossiblePlayerArmy == getCurrentIdPlayer())
    {
        getCurrentPlayer().mergeArmy(oldPosition, newPosition);
    }
    else if (idPossiblePlayerArmy == getEnnemyIdPlayer())
    {
        fightPlayerArmy(oldPosition, newPosition);
    }

    switchCurrentPlayerId();
}

void GameEngine::setColorSquareByPlayer(pair<int, int> position, int idPlayer)
{
    switch (idPlayer)
    {
    case 1:
        getSquare(position).setColor(color::red);
        break;

    case 2:
        getSquare(position).setColor(color::blue);
        break;
    }
}

pair<int, int> GameEngine::getSelectedSquare()
{
    return selectedSquareIndexes;
}

GameEngine::~GameEngine()
{
}