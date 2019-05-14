#include "Draw.hpp"
#include "simple2d.h"
#include <iostream>

void Draw::line(int l1x, int l1y, int l2x, int l2y, int lineWidth, float r, float g, float b)
{
    S2D_DrawLine(l1x, l1y, l2x, l2y,
                 lineWidth,
                 r, g, b, 1,
                 r, g, b, 1,
                 r, g, b, 1,
                 r, g, b, 1);
}

void Draw::D4Lines(int i, int j, int lineWidth, int squareSize, float r, float g, float b)
{
    int l1x = i * squareSize;
    int l1y = j * squareSize;
    int l2x = l1x + squareSize;
    int l3y = l1y + squareSize;

    line(l1x, l1y, l2x, l1y, lineWidth, r, g, b);
    line(l2x, l1y, l2x, l3y, lineWidth, r, g, b);
    line(l2x, l3y, l1x, l3y, lineWidth, r, g, b);
    line(l1x, l3y, l1x, l1y, lineWidth, r, g, b);
}

void Draw::D2Lines(int i, int j, int lineWidth, int squareSize, float r, float g, float b)
{
    int l1x = i * squareSize;
    int l1y = j * squareSize;
    int l2x = l1x + squareSize;
    int l3y = l1y + squareSize;

    //drawLine(l1x, l1y, l2x, l1y, lineWidth, r, g, b);
    line(l2x, l1y, l2x, l3y, lineWidth, r, g, b);
    line(l2x, l3y, l1x, l3y, lineWidth, r, g, b);
    //drawLine(l1x, l3y, l1x, l1y, lineWidth, r, g, b);
}

void Draw::square(int i, int j, int squareSize, int lineWidth, Square square)
{
    int x1 = i * squareSize + lineWidth;
    int y1 = j * squareSize + lineWidth;
    int x2 = x1 + squareSize - lineWidth;
    int y2 = y1 + lineWidth;
    int x3 = x2 - lineWidth;
    int y3 = y2 + squareSize - lineWidth;
    int x4 = x1 + lineWidth;
    int y4 = y3 - lineWidth;

    S2D_DrawQuad(x1, y1, square.getR(), square.getG(), square.getB(), square.getA(),
                 x2, y2, square.getR(), square.getG(), square.getB(), square.getA(),
                 x3, y3, square.getR(), square.getG(), square.getB(), square.getA(),
                 x4, y4, square.getR(), square.getG(), square.getB(), square.getA());

    switch (square.getType())
    {

        case Square::Type::spawn1:
            D4Lines(i, j, lineWidth, squareSize, 1, 0, 0);
            break;

        case Square::Type::spawn2:
            D4Lines(i, j, lineWidth, squareSize, 0, 0, 1);
            break;

        default:
            break;
    }
}

void Draw::buttons(){
    /*S2D_DrawQuad(700, 100, 1, 1, 1, 1,
                 800, 100, 1, 1, 1, 1,
                 x3, y3, 1, 1, 1, 1,
                 x4, y4, 1, 1, 1, 1);*/
}

void Draw::armyPower(int i, int j, int squareSize, int lineWidth, int armyPower)
{
    std::string armyPowerStr = std::to_string(armyPower);
    int txtSize = 0;
    if(armyPower > 9) {
        txtSize = 25;
    }else{
        txtSize = 30;
    }

    S2D_Text *txt = S2D_CreateText("./resources/fonts/verdana.ttf", armyPowerStr.c_str(), txtSize);
    if (txt)
    {
        txt->color.r = 1;
        txt->color.g = 1;
        txt->color.b = 1;
        txt->color.a = 1;
        txt->x = i * squareSize - (lineWidth) + txtSize/2;
        txt->y = j * squareSize - (lineWidth) + txtSize/3;
        S2D_DrawText(txt);
    }
    else
    {
        std::cout << "fonts error" << std::endl;
    }
    S2D_FreeText(txt);
}