#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <simple2d.h>

class GameEngine
{
public:
    GameEngine(S2D_Window &windowGiven);
    ~GameEngine();
    void start();
    void stop();

private:
    S2D_Window& window;
};

#endif

// http://gamecodeschool.com/sfml/building-a-simple-game-engine-in-c-plus-plus/