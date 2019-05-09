
#include <simple2d.h>
#include "GameEngine.hpp"

void render()
{
}

void update(){
}

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

    S2D_Window *window = S2D_CreateWindow(
        "Menu", 500, 500, update, render, 0);
    
    S2D_Close(window);

    GameEngine gameEngine(*window);
    gameEngine.start();

    return 0;
}
