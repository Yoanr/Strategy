
#include "Interaction.hpp"
#include "GameEngine.hpp"

int main(int argc, char *argv[])
{

    if (argc == 2 && strcmp(argv[1],"--dev") == 0)
    {
        GameEngine *gameEngine = new GameEngine;
        Interaction *interaction = new Interaction(*gameEngine);
        return interaction->automatize();
    }
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
