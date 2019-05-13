#include "Interaction.hpp"
#include <iostream>
#include "Lambda.hpp"
#include "GameEngine.hpp"

void drawLine(int l1x, int l1y, int l2x, int l2y, int lineWidth, float r, float g, float b)
{
    S2D_DrawLine(l1x, l1y, l2x, l2y,
                 lineWidth,
                 r, g,b, 1,
                 r, g,b, 1,
                 r, g,b, 1,
                 r, g,b, 1);
}

void draw4Lines(int i, int j, int lineWidth, int squareSize, float r, float g, float b)
{
    int l1x = i * squareSize;
    int l1y = j * squareSize;
    int l2x = l1x + squareSize;
    int l3y = l1y + squareSize;

    drawLine(l1x, l1y, l2x, l1y, lineWidth, r, g, b);
    drawLine(l2x, l1y, l2x, l3y, lineWidth, r, g, b);
    drawLine(l2x, l3y, l1x, l3y, lineWidth, r, g, b);
    drawLine(l1x, l3y, l1x, l1y, lineWidth, r, g, b);
}


void draw2Lines(int i, int j, int lineWidth, int squareSize, float r, float g, float b)
{
    int l1x = i * squareSize;
    int l1y = j * squareSize;
    int l2x = l1x + squareSize;
    int l3y = l1y + squareSize;

    //drawLine(l1x, l1y, l2x, l1y, lineWidth, r, g, b);
    drawLine(l2x, l1y, l2x, l3y, lineWidth, r, g, b);
    drawLine(l2x, l3y, l1x, l3y, lineWidth, r, g, b);
    //drawLine(l1x, l3y, l1x, l1y, lineWidth, r, g, b);
}

void drawSquare(int i, int j, int squareSize, int lineWidth, Square::Type squareType)
{
    int x1 = i * squareSize + lineWidth;
    int y1 = j * squareSize + lineWidth;
    int x2 = x1 + squareSize - lineWidth;
    int y2 = y1 + lineWidth;
    int x3 = x2  - lineWidth;
    int y3 = y2 + squareSize - lineWidth;
    int x4 = x1 + lineWidth;
    int y4 = y3 - lineWidth;

    switch (squareType){
        case Square::Type::tower:
            S2D_DrawQuad(x1, y1, 0, 1, 0, 1,
                         x2, y2, 0, 1, 0, 1,
                         x3, y3, 0, 1, 0, 1,
                         x4, y4, 0, 1, 0, 1);
            break;

        case Square::Type::spawn1:
            S2D_DrawQuad(x1, y1, 1, 1, 1, 1,
                         x2, y2, 1, 1, 1, 1,
                         x3, y3, 1, 1, 1, 1,
                         x4, y4, 1, 1, 1, 1);

            draw4Lines(i, j, lineWidth, squareSize, 1, 0, 0);
            break;

        case Square::Type::spawn2:
            S2D_DrawQuad(x1, y1, 1, 1, 1, 1,
                         x2, y2, 1, 1, 1, 1,
                         x3, y3, 1, 1, 1, 1,
                         x4, y4, 1, 1, 1, 1);

            draw4Lines(i, j, lineWidth, squareSize, 0, 0, 1);
            break;

        default:
            S2D_DrawQuad(x1, y1, 1, 1, 1, 1,
                         x2, y2, 1, 1, 1, 1,
                         x3, y3, 1, 1, 1, 1,
                         x4, y4, 1, 1, 1, 1);
    }
}


void Interaction::render()
{
    int gridSize = 11;
    int lineWidth = 2;
    int squareSize = 50;

    for (int i = 0; i <  gridSize; i++)
    {
        for (int j = 0; j <  gridSize; j++)
        {
            draw2Lines(i, j, lineWidth, squareSize, 0, 0, 0); //Black color
            drawSquare(i, j, squareSize, lineWidth, gameEngine.getSquare(i, j).getType());
        }
    }
}


void Interaction::onMouse(S2D_Event e)
{
    switch (e.type)
    {
        case S2D_MOUSE_DOWN:
            // Mouse button was pressed
            std::cout << "down" << e.x << std::endl;
            // Use `e.button` to see what button was clicked
            // Check `e.dblclick` to see if was a double click
            break;

        case S2D_MOUSE_UP:
            // Mouse button was released
            std::cout << "up" << e.x << std::endl;
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