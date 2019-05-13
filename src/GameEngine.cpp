#include "GameEngine.hpp"

int GameEngine::generateNumber0into100(){
    srand(time(NULL));
    return rand() % 100 + 0;
}
GameEngine::GameEngine(){

    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            std::pair<int, int> ij = std::pair<int, int>(i, j);
            if ((i == TOWER1.first && j == TOWER1.second) || (i == TOWER2.first && j == TOWER2.second) || (i == TOWER3.first && j == TOWER3.second))
            {
                board.insert(std::pair<std::pair<int, int>, Square>(ij,Square(Square::Type::tower)));
            }
            else if (generateNumber0into100() < PROBABOMB && ((i != SPAWNP1.first && j != SPAWNP1.second) && (i != SPAWNP2.first || j != SPAWNP2.second)))
            {
                board.insert(std::pair<std::pair<int, int>, Square>(ij, Square(Square::Type::bomb)));
            }else{
                board.insert(std::pair<std::pair<int, int>, Square>(ij, Square(Square::Type::basic)));
            }
        }
    }
}

Square& GameEngine::getSquare(int i, int j){
    std::map<std::pair<int, int>, Square>::iterator it = board.find(std::pair<int, int>(i, j));
        return it->second;
}

GameEngine::~GameEngine()
{
}