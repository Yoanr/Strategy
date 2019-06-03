#include "Tree.hpp"

Tree::Tree(){
    performTree(gameEngine,root);
}

void Tree::performTree(GameEngine gameEngine,Noeud& noeud){
    if(gameEngine.getHasWon()){
        return;
    }
    vector<pair<int, int>> oldIndexes = getOldPosition(gameEngine);
    for (std::size_t i = 0; i < oldIndexes.size(); i++)
    {
        vector<pair<int, int>> newIndexes = getNewPosition(oldIndexes[i]);

        for (std::size_t j = 0; j < newIndexes.size(); j++)
        {
            if (verifyPlay(newIndexes[i]))
            {
                GameEngine *copy = new GameEngine();
                *copy = gameEngine;

                copy->play(oldIndexes[i] /*CHOOSE OLD POSITION CORRECTLY*/, newIndexes[j]);
                Noeud &refnoeud = noeud.addChild(*copy, 1);
                performTree(gameEngine, refnoeud);
            }
        }
    }
}

 vector<pair<int, int>> Tree::getOldPosition(GameEngine gameEngine){
     map<pair<int, int>,int> m = gameEngine.getCurrentPlayer().getArmy();
     vector<pair<int, int>> v;
     for (map<pair<int, int>, int>::iterator it = m.begin(); it != m.end(); ++it)
     {
         v.push_back(it->first);
     }
     return v; // pointer ? ref ?
}

vector<pair<int, int>> Tree::getNewPosition(pair<int, int> pair)
{
    vector<std::pair<int, int>> v;

    v.push_back(std::pair<int, int>(pair.first + 1, pair.second));
    v.push_back(std::pair<int, int>(pair.first, pair.second + 1));
    v.push_back(std::pair<int, int>(pair.first - 1, pair.second));
    v.push_back(std::pair<int, int>(pair.first, pair.second - 1));

    return v; // pointer ? ref ?
}


bool Tree::verifyPlay(pair<int, int> position)
{
    if (position.first < Config::NUMBEROFSQUARE && position.first >= 0 && position.second < Config::NUMBEROFSQUARE && position.second >= 0)
    {
        return true;
    }
    return false;
}