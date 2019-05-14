#ifndef Interaction_H
#define Interaction_H

#include <simple2d.h>
#include "GameEngine.hpp"

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

    void onMouse(S2D_Event e);
    void render();
    void drawField(int i, int j, int lineWidth, int squareSize);
    void drawPossibleArmy(int i, int j, int squareSize, int lineWidth);
    void setSelectedSquare(int i, int j, bool isSelected);
    void setColorSquareByPlayer(int i, int j, int idPlayer);
    void moveSquare(std::pair<int, int> oldIndexes, std::pair<int, int> newIndexes);
    bool checkFirstClick(std::pair<int, int> position);
    bool checkSecondClick(std::pair<int, int> position);
    std::pair<int, int> getIndexByMousePosition(std::pair<int, int> position);

};

#endif

// http://gamecodeschool.com/sfml/building-a-simple-game-engine-in-c-plus-plus/