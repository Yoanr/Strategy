
#include "Interaction.hpp"
#include "GameEngine.hpp"

int main()
{
   GameEngine gameEngine;
   Interaction interaction(gameEngine);

   interaction.init();
   interaction.start();

   //gameEngine.idle();

    return 0;
}
