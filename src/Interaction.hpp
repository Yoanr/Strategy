#ifndef Interaction_H
#define Interaction_H

#include <simple2d.h>
#include "GameEngine.hpp"

class Interaction
{
public:
    Interaction(GameEngine gameEngineGiven);
    ~Interaction();
    void init();
    void start();
    void stop();

private:
    S2D_Window *window;
    void onMouse(S2D_Event e);
    void render();
    void drawField(int i, int j, int lineWidth, int squareSize);
    void drawPossibleArmy(int i, int j, int lineWidth, int squareSize);
    GameEngine gameEngine;
};

#endif

// http://gamecodeschool.com/sfml/building-a-simple-game-engine-in-c-plus-plus/