#include "Draw.hpp"
#include "simple2d.h"
#include <iostream>

void Draw::line(int l1x, int l1y, int l2x, int l2y, int lineWidth, color::Color color)
{
    S2D_DrawLine(l1x, l1y, l2x, l2y,
                 lineWidth,
                 color.r, color.g, color.b, 1,
                 color.r, color.g, color.b, 1,
                 color.r, color.g, color.b, 1,
                 color.r, color.g, color.b, 1);
}

void Draw::D4Lines(pair<int, int> position, int lineWidth, int squareSize, color::Color color)
{
    int l1x = position.first * squareSize;
    int l1y = position.second * squareSize;
    int l2x = l1x + squareSize;
    int l3y = l1y + squareSize;

    line(l1x, l1y, l2x, l1y, lineWidth, color);
    line(l2x, l1y, l2x, l3y, lineWidth, color);
    line(l2x, l3y, l1x, l3y, lineWidth, color);
    line(l1x, l3y, l1x, l1y, lineWidth, color);
}

void Draw::D2Lines(pair<int, int> position, int lineWidth, int squareSize, color::Color color)
{
    int l1x = position.first * squareSize;
    int l1y = position.second * squareSize;
    int l2x = l1x + squareSize;
    int l3y = l1y + squareSize;

    //drawLine(l1x, l1y, l2x, l1y, lineWidth, r, g, b);
    line(l2x, l1y, l2x, l3y, lineWidth, color);
    line(l2x, l3y, l1x, l3y, lineWidth, color);
    //drawLine(l1x, l3y, l1x, l1y, lineWidth, r, g, b);
}

void Draw::square(pair<int, int> position, int squareSize, int lineWidth, Square square)
{
    int x1 = position.first * squareSize + lineWidth;
    int y1 = position.second * squareSize + lineWidth;
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
            D4Lines(position, lineWidth, squareSize, color::Color{1,0,0,1});
            break;

        case Square::Type::spawn2:
            D4Lines(position, lineWidth, squareSize, color::Color{0, 0, 1, 1});
            break;

        default:
            break;
    }
}

void Draw::armyPower(pair<int, int> position, int squareSize, int lineWidth, int armyPower)
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
        txt->x = position.first * squareSize - (lineWidth) + txtSize/2;
        txt->y = position.second * squareSize - (lineWidth) + txtSize/3;
        S2D_DrawText(txt);
    }
    else
    {
        std::cout << "fonts error" << std::endl;
    }
    S2D_FreeText(txt);
}