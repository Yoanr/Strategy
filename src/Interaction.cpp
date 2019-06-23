#include "Interaction.hpp"
#include <iostream>
#include "Lambda.hpp"
#include "GameEngine.hpp"
#include "Draw.hpp"
#include "Config.hpp"




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

            if (Config::getInstance().MODE == Config::mode::p1versusai && not(gameEngine.getHasWon()))
            {
                onMouseBotPlay(Config::EVAL_FCT_AIP2);
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

        if(not gameEngine.getChoice()){
            onMouseChoice(pMouse);
            return;
        }

        if(not gameEngine.getHasWon()){
            if (Config::getInstance().MODE == Config::mode::p1versusp2 || Config::getInstance().MODE == Config::mode::p1versusai)
            {
                onMousePlay(pMouse);
            }
            else if (Config::getInstance().MODE == Config::mode::aiversusaiMANUAL)
            {
                if (gameEngine.getCurrentIdPlayer() == 1)
                {
                    onMouseBotPlay(Config::EVAL_FCT_AIP1);
                }
                else
                {
                    onMouseBotPlay(Config::EVAL_FCT_AIP2);
                }
            }
            else if (Config::getInstance().MODE == Config::mode::aiversusaiAUTO)
            {
                while (not gameEngine.getHasWon())
                {
                    if(gameEngine.getCurrentIdPlayer() == 1){
                        onMouseBotPlay(Config::EVAL_FCT_AIP1);
                    }else{
                        onMouseBotPlay(Config::EVAL_FCT_AIP2);
                    }
                }
            }
        }else{
            onMouseHasWon(pMouse);
        }
            break;
    }
}

void Interaction::onMouseBotPlay(Config::eval eval)
{
    pair<pair<int, int>, pair<int, int>> pair = bot.getNextmove(eval);
    gameEngine.play(pair.first, pair.second);
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

void Interaction::onMouseChoice(pair<int, int> pMouse)
{
    if (pMouse.first > 180 && pMouse.second > 200 && pMouse.first < 330 && pMouse.second < 350)
    {
        Config::getInstance().MODE = Config::mode::p1versusp2;
        gameEngine.setChoice();
    }
    if (pMouse.first > 330 && pMouse.second > 200 && pMouse.first < 480 && pMouse.second < 350)
    {
        Config::getInstance().MODE = Config::mode::p1versusai;
        gameEngine.setChoice();
    }
    if (pMouse.first > 480 && pMouse.second > 200 && pMouse.first < 630 && pMouse.second < 350)
    {
        Config::getInstance().MODE = Config::mode::aiversusaiMANUAL;
        gameEngine.setChoice();
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
            "Strategy", 800, 555, nullptr, nullptr, 0);
    window = windowGiven;

    window->on_mouse = Lambda::make_function_ptr([this](S2D_Event event) { onMouse(event); });
    window->render = Lambda::make_function_ptr([this]() { Draw::getInstance().render(gameEngine); });

    S2D_Show(window);
}

int Interaction::automatize(){
    while (not gameEngine.getHasWon())
    {
        onMouseBotPlay(Config::EVAL_FCT_AIP1);
        if (gameEngine.getHasWon())
        {
            break;
        }
        onMouseBotPlay(Config::EVAL_FCT_AIP2);
    }
    return gameEngine.getEnnemyIdPlayer();
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