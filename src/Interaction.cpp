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
    Draw::getInstance().showInfo(gameEngine.getCurrentRound(), gameEngine.getNbrOfBombHitted(),gameEngine.getTotalPowerArmy(),gameEngine.getCurrentIdPlayer());
    
    if(gameEngine.getHasWon()){
        Draw::getInstance().victory(gameEngine.getEnnemyIdPlayer());
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

    if (not armyPower == 0)
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

    if (gameEngine.isNotEnnemySpawn(newIndexes)) // Ennemy spawn ?
    {
        return false;
    }

    if (oldIndexes == newIndexes) // same square ? + reset move
    {
        alreadyClicked = false;
        setSelectedSquare(newIndexes, false);
        gameEngine.getSquare(newIndexes).setA(1);
        return false;
    }

    //Check the move
    if ( not ((newIndexes.first == oldIndexes.first + 1 && newIndexes.second == oldIndexes.second) ||
              (newIndexes.first == oldIndexes.first - 1 && newIndexes.second == oldIndexes.second) ||
              (newIndexes.first == oldIndexes.first && newIndexes.second == oldIndexes.second + 1) ||
              (newIndexes.first == oldIndexes.first && newIndexes.second == oldIndexes.second - 1)))
    {
        return false;
    }

    return true;
}

void Interaction::setSelectedSquare(pair<int, int> position, bool isSelected)
{
    gameEngine.getSquare(position).setA(isSelected ? 0.3 : 1);
}

void Interaction::onMousePlay(pair<int, int> pMouse)
{
    pair<int, int> newIndexes = getIndexByMousePosition(pMouse);
    if (alreadyClicked)
    {
        if (checkSecondClick(pMouse))
        {
            pair<int, int> oldIndexes = getIndexByMousePosition(gameEngine.getSelectedSquare());
            gameEngine.play(oldIndexes, newIndexes);

            alreadyClicked = false;

            if (Config::AI && not (gameEngine.getHasWon()))
            {
                pair<pair<int, int>, pair<int, int>> pair = bot.getNextmove();
                gameEngine.play(pair.first, pair.second);
            }

        }
    }
    else
    {
        if (checkFirstClick(pMouse))
        {
            gameEngine.setSelectedSquare(pMouse);
            setSelectedSquare(newIndexes, true);

            alreadyClicked = true;
        }
    }
}
void Interaction::onMouse(S2D_Event e)
{
    pair<int, int> pMouse(e.x, e.y);
    switch (e.type)
    {
        case S2D_MOUSE_DOWN:
        if(not gameEngine.getHasWon()){
            onMousePlay(pMouse);
        }else{
            onMouseHasWon(pMouse);
        }
            
            break;
    }
}

void Interaction::onMouseHasWon(pair<int, int> pMouse)
{
   if (pMouse.first > 160 && pMouse.second > 290 && pMouse.first < 250 && pMouse.second < 340)
   {
       wantToReplay = true;
        stop(); // Replay
   }

   if (pMouse.first > 320 && pMouse.second > 290 && pMouse.first < 410 && pMouse.second < 340)
   {
       wantToReplay = false;
       stop(); // Quit
    }
}

bool Interaction::getwantToReplay()
{
    return wantToReplay;
}

void Interaction::idle()
{
    Draw::getInstance();
    S2D_Window *windowGiven = S2D_CreateWindow(
            "Game", 800, 555, nullptr, nullptr, 0);
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

void Interaction::stop()
{
    S2D_Close(window);
}