#ifndef Interaction_H
#define Interaction_H

#include <simple2d.h>
#include "GameEngine.hpp"
#include "color.hpp"

using namespace std;
class Interaction {
public:
    Interaction(GameEngine gameEngineGiven);
    ~Interaction();
    void init();
    void start();
    void stop();

private:
    S2D_Window *window;
    GameEngine gameEngine;
    bool alreadyClicked{false};

    const int SQUARESIZE{50};
    const int NUMBEROFSQUARE{11};
    const int GRIDSIZE{SQUARESIZE * NUMBEROFSQUARE};
    const int LINEWIDTH{2};

    void onMouse(S2D_Event e);
    void render();
    void drawField(pair<int, int> position);
    void drawPossibleArmy(pair<int, int> position);
    void setSelectedSquare(pair<int, int> position, bool isSelected);
    void setColorSquareByPlayer(pair<int, int> position, int idPlayer);
    void moveSquare(pair<int, int> oldIndexes, pair<int, int> newIndexes);
    bool checkFirstClick(pair<int, int> position);
    bool checkSecondClick(pair<int, int> position);
    pair<int, int> getIndexByMousePosition(pair<int, int> position);

};

#endif

// http://gamecodeschool.com/sfml/building-a-simple-game-engine-in-c-plus-plus/