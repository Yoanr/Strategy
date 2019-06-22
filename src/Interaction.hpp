#ifndef Interaction_H
#define Interaction_H

#include "../inc/simple2d.h"
#include "GameEngine.hpp"
#include "color.hpp"
#include "Bot.hpp"

using namespace std;
class Interaction {
public:
    Interaction(GameEngine gameEngineGiven);
    ~Interaction();
    void idle();
    void stop();
    bool getwantToReplay();

private:
    S2D_Window *window;
    GameEngine gameEngine;
    Bot bot{gameEngine};
    bool alreadyClicked{false};
    bool wantToReplay{false};

    void onMouse(S2D_Event e);
    void onMousePlay(pair<int, int> pMouse);
    void onMouseBotPlay();
    void onMouseHasWon(pair<int, int> pMouse);
    void setSelectedSquare(pair<int, int> position, bool isSelected);
    bool checkFirstClick(pair<int, int> positionClicked);
    bool checkSecondClick(pair<int, int> positionClicked);
    pair<int, int> getIndexByMousePosition(pair<int, int> position);
//todo clean position in all fonction
};

#endif

// http://gamecodeschool.com/sfml/building-a-simple-game-engine-in-c-plus-plus/