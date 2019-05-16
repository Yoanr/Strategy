#include "Interaction.hpp"
#include <iostream>
#include "Lambda.hpp"
#include "GameEngine.hpp"
#include "Draw.hpp"
#include "Config.hpp"



void Interaction::render()
{
    for (int i = 0; i < Config::NUMBEROFSQUARE; i++)
    {
        for (int j = 0; j < Config::NUMBEROFSQUARE; j++)
        {
            pair<int, int> position(i, j);
            Draw::getInstance().setPosition(position);

            drawField(position);
            drawPossibleArmy(position);
        }
    }
}

void Interaction::drawField(pair<int, int> position)
{
    Draw::getInstance().D2Lines(color::black); //Black color
    Draw::getInstance().square(gameEngine.getSquare(position));
}

void Interaction::drawPossibleArmy(pair<int, int> position)
{
    pair<int, int> p = gameEngine.getPossibleArmy(position); // <,>
    int playerId = p.first;
    int armyPower = p.second;

    if (not (armyPower == 0))
    {
        gameEngine.setColorSquareByPlayer(position,playerId);
        Draw::getInstance().armyPower(armyPower);
    }
}


pair<int, int> Interaction::getIndexByMousePosition(pair<int,int> position){
    return pair<int, int>(position.first / Config::SQUARESIZE, position.second / Config::SQUARESIZE);
}

bool Interaction::checkFirstClick(pair<int, int> position)
{
    if (position.first > Config::GRIDSIZE || position.second > Config::GRIDSIZE)
    { // Positions ?
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
    if (position.first > Config::GRIDSIZE || position.second > Config::GRIDSIZE)
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
void Interaction::onMouse(S2D_Event e)
{
    pair<int,int> position(e.x, e.y);
    pair<int, int> newIndexes = getIndexByMousePosition(position);
    switch (e.type)
    {
        case S2D_MOUSE_DOWN:
            if(alreadyClicked){
                if(checkSecondClick(position)){
                    pair<int, int> oldIndexes = getIndexByMousePosition(gameEngine.getSelectedSquare());
                    gameEngine.play(oldIndexes, newIndexes);

                    alreadyClicked = false;
                }
            }else{
                if (checkFirstClick(position))
                {
                    gameEngine.setSelectedSquare(position);
                    setSelectedSquare(newIndexes, true);

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
    Draw::getInstance();
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