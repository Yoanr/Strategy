#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Square.hpp"
#include "Player.hpp"
#include "Config.hpp"
#include <map>
using namespace std;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();
    GameEngine& operator=(const GameEngine& other); // TODO

    Square &getSquare(pair<int, int> position);
    pair<int, int> getPossibleArmy(pair<int, int> position);
    pair<int,int> getSelectedSquare();
    int getCurrentIdPlayer();
    int getEnnemyIdPlayer();
    bool isNotEnnemySpawn(pair<int, int> position);
    void setSelectedSquare(pair<int, int>);
    bool getHasWon();
    bool getChoice();
    void setChoice();
    void setHasWon(bool hasWonGiven); // cheatcode
    void play(pair<int, int> oldPosition, pair<int, int> newPosition);
    void setColorSquareByPlayer(pair<int, int> position, int idPlayer);
    pair<int,int> getNbrOfBombHitted();
    pair<int,int> getTotalPowerArmy();
    int getCurrentRound();
    bool getHasLose();

    Player &getCurrentPlayer();
    Player &getEnnemyPlayer();

    const pair<int, int> SPAWNP1{5, 0};
    const pair<int, int> SPAWNP2{5, 10};

    const pair<int, int> TOWER1{1, 5};
    const pair<int, int> TOWER2{5, 5};
    const pair<int, int> TOWER3{9, 5};
    bool checkTowerCapturedByPlayer(const pair<int, int>& towerPosition,Player& player);
    bool isBomb(pair<int, int> position);

private:
    int getProbaBomb(Config::Level level);
    int hasWon{false};
    bool choice{false};
    int generateNumber0into100();
    map<pair<int, int>, Square> board;
    const int GRIDSIZE = 12;

    int numberOfRound{0};
    pair<int, int> selectedSquareIndexes{-1, -1};
    Player player1{1};
    Player player2{2};
    int currentPlayerId{1};
    int currentRound{1};

    void resetSelectedSquare();
    bool fightPlayerArmy(pair<int, int> oldPosition, pair<int, int> newPosition, Player& player);
    void moveToBomb(pair<int, int> oldPosition, pair<int, int> newPosition);
    bool armyPresent(pair<int, int>);
    void manageEndOfRound();
    void checkTowers();
};

#endif