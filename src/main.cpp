
#include "Interaction.hpp"
#include "GameEngine.hpp"

int main()
{
    bool wantToReplay{true};

    while (wantToReplay)
    {
        GameEngine *gameEngine = new GameEngine;
        Interaction *interaction = new Interaction(*gameEngine);

        interaction->idle();
        wantToReplay = interaction->getwantToReplay();
        delete (gameEngine);
        delete (interaction);
    }
    return 0;
}
