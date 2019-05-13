
#include "Interaction.hpp"
#include "GameEngine.hpp"

int main()
{
   /* bool quit{false};
    while(not quit){ // 

        if (click button play) {
            GameEngine.start();
        }else if (click button credit) {
            printCredit();
        } else if(click button quit){
            GameEngine.stop();
            quit = true;
            }

    }*/
   GameEngine gameEngine;
   Interaction interaction(gameEngine);

   interaction.init();
   interaction.start();

   return 0;
}
