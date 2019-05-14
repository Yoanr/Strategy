#include "Interaction.hpp"
#include <iostream>
#include "Lambda.hpp"
#include "GameEngine.hpp"
#include "Draw.hpp"




void Interaction::render()
{
    //Draw::buttons();
    for (int i = 0; i < NUMBEROFSQUARE; i++)
    {
        for (int j = 0; j < NUMBEROFSQUARE; j++)
        {
            drawField(pair<int,int>(i,j));
            drawPossibleArmy(pair<int, int>(i,j));
        }
    }
}

void Interaction::drawField(pair<int, int> position)
{
    Draw::D2Lines(position.first, position.second, LINEWIDTH, SQUARESIZE, 0, 0, 0); //Black color
    Draw::square(position.first, position.second, SQUARESIZE, LINEWIDTH, gameEngine.getSquare(position));
}

void Interaction::drawPossibleArmy(pair<int, int> position)
{
    pair<int, int> p = gameEngine.getPossibleArmy(position); // <,>

    if (p.second != 0) {
        setColorSquareByPlayer(position, p.first);
        Draw::armyPower(position.first, position.second, SQUARESIZE, LINEWIDTH, p.second);
    }
}

void Interaction::setColorSquareByPlayer(pair<int, int> position, int idPlayer)
{
    switch (idPlayer) {
        case 1:
            gameEngine.getSquare(position).setColor(1, 0, 0);
            break;

        case 2:
            gameEngine.getSquare(position).setColor(0, 0, 1);
            break;
    }
}

pair<int, int> Interaction::getIndexByMousePosition(pair<int,int> position){
    return pair<int,int>(position.first/SQUARESIZE,position.second/SQUARESIZE);
}

bool Interaction::checkFirstClick(pair<int, int> position)
{
    if (position.first > GRIDSIZE || position.second > GRIDSIZE){ // Positions ?
        return false;
    }

    pair<int, int> indexes = getIndexByMousePosition(position);
    pair<int, int> res = gameEngine.getPossibleArmy(indexes);
    if (res.first != gameEngine.getCurrentIdPlayer()) // Army ?
    {
        return false;
    }

    return true;
}

bool Interaction::checkSecondClick(pair<int,int>  position)
{
    if (position.first > GRIDSIZE || position.second > GRIDSIZE)
    { // Positions ?
        return false;
    }
    pair<int, int> oldIndexes = getIndexByMousePosition(gameEngine.getSelectedSquare());
    pair<int, int> newIndexes = getIndexByMousePosition(position);
    if (oldIndexes == newIndexes) // Army ?
    {
        return false;
    }

    //Check the move
    if ( (newIndexes.first != oldIndexes.first + 1 && newIndexes.first != oldIndexes.first - 1 && newIndexes.first != oldIndexes.first)  ||
         (newIndexes.second != oldIndexes.second + 1 && newIndexes.second != oldIndexes.second - 1 && newIndexes.second != oldIndexes.second)) {
        return false;
    }

    return true;
}

void Interaction::setSelectedSquare(pair<int, int> position, bool isSelected)
{
    gameEngine.getSquare(position).setA(isSelected ? 0.8 : 1);
}

//TODO Not finished
void Interaction::moveSquare(pair<int, int> oldIndexes, pair<int, int> newIndexes){
    gameEngine.getSquare(oldIndexes).setColor(0, 1, 0); //not working

    setColorSquareByPlayer(newIndexes, gameEngine.getCurrentIdPlayer());
}

void Interaction::onMouse(S2D_Event e)
{
    pair<int,int> position(e.x, e.y);
    switch (e.type)
    {
        case S2D_MOUSE_DOWN:
            if(alreadyClicked){

                if(checkSecondClick(position)){
                    pair<int, int> oldIndexes = getIndexByMousePosition(gameEngine.getSelectedSquare());
                    pair<int, int> newIndexes = getIndexByMousePosition(position);

                    gameEngine.resetSelectedSquare();
                    setSelectedSquare(oldIndexes, false);

                    alreadyClicked = false;

                    moveSquare(oldIndexes, newIndexes); //TODO not always a move action

                    gameEngine.switchCurrentPlayer();
                }

            }else{
                if (checkFirstClick(position))
                {
                    gameEngine.setSelectedSquare(position);
                    setSelectedSquare(getIndexByMousePosition(position), true);

                    alreadyClicked = true;
                }
            }

            break;

        case S2D_MOUSE_UP:
            // Mouse button was released
            // Use `e.button` to see what button was clicked
            // Check `e.dblclick` to see if was a double click
            break;

        case S2D_MOUSE_SCROLL:
            // Mouse was scrolled
            // Check `e.direction` for direction being scrolled, normal or inverted:
            //   S2D_MOUSE_SCROLL_NORMAL
            //   S2D_MOUSE_SCROLL_INVERTED
            // Check `e.delta_x` and `e.delta_y` for the difference in x and y position
            break;

        case S2D_MOUSE_MOVE:
            // Mouse was moved
            // Check `e.delta_x` and `e.delta_y` for the difference in x and y position
            break;
    }
}

void Interaction::init()
{
    S2D_Window *windowGiven = S2D_CreateWindow(
            "Game", 1000, 700, nullptr, nullptr, 0);
    window = windowGiven;

    window->on_mouse = Lambda::make_function_ptr([this](S2D_Event event) { onMouse(event); });
    window->render = Lambda::make_function_ptr([this]() { render(); });

    S2D_Show(window);
}

Interaction::Interaction(GameEngine gameEngineGiven) : gameEngine(gameEngineGiven)
{
}
Interaction::~Interaction()
{
    S2D_FreeWindow(window);
}

void Interaction::start()
{


    /* window->background.r = 0.5;
     window->background.g = 0.5;
     window->background.b = 0.5;
     window->background.a = 1.0;

     window->width = 1000;
     window->height = 700;
     window->title = "Strategy";
     window->update = &update;
     window->render = &render;*/

}

void Interaction::stop()
{
    S2D_Close(window);
}