#include "Draw.hpp"
#include "simple2d.h"
#include <iostream>
#include "Config.hpp"

void Draw::line(int l1x, int l1y, int l2x, int l2y, color::Color color)
{
    S2D_DrawLine(l1x, l1y, l2x, l2y,
                 Config::LINEWIDTH,
                 color.r, color.g, color.b, color.a,
                 color.r, color.g, color.b, color.a,
                 color.r, color.g, color.b, color.a,
                 color.r, color.g, color.b, color.a);
}

void Draw::D4Lines(pair<int, int> position, color::Color color)
{
    int l1x = position.first * Config::SQUARESIZE;
    int l1y = position.second * Config::SQUARESIZE;
    int l2x = l1x + Config::SQUARESIZE;
    int l3y = l1y + Config::SQUARESIZE;

    line(l1x, l1y, l2x, l1y, color);
    line(l2x, l1y, l2x, l3y, color);
    line(l2x, l3y, l1x, l3y, color);
    line(l1x, l3y, l1x, l1y, color);
}

void Draw::D2Lines(pair<int, int> position, color::Color color)
{
    int l1x = position.first * Config::SQUARESIZE;
    int l1y = position.second * Config::SQUARESIZE;
    int l2x = l1x + Config::SQUARESIZE;
    int l3y = l1y + Config::SQUARESIZE;

    //drawLine(l1x, l1y, l2x, l1y, lineWidth, r, g, b);
    line(l2x, l1y, l2x, l3y, color);
    line(l2x, l3y, l1x, l3y, color);
    //drawLine(l1x, l3y, l1x, l1y, lineWidth, r, g, b);
}

void Draw::square(pair<int, int> position, Square square)
{
    int x1 = position.first * Config::SQUARESIZE + Config::LINEWIDTH;
    int y1 = position.second * Config::SQUARESIZE + Config::LINEWIDTH;
    int x2 = x1 + Config::SQUARESIZE - Config::LINEWIDTH;
    int y2 = y1 + Config::LINEWIDTH;
    int x3 = x2 - Config::LINEWIDTH;
    int y3 = y2 + Config::SQUARESIZE - Config::LINEWIDTH;
    int x4 = x1 + Config::LINEWIDTH;
    int y4 = y3 - Config::LINEWIDTH;

    S2D_DrawQuad(x1, y1, square.getR(), square.getG(), square.getB(), square.getA(),
                 x2, y2, square.getR(), square.getG(), square.getB(), square.getA(),
                 x3, y3, square.getR(), square.getG(), square.getB(), square.getA(),
                 x4, y4, square.getR(), square.getG(), square.getB(), square.getA());

    switch (square.getType())
    {

        case Square::Type::spawn1:
            D4Lines(position, color::red);
            break;

        case Square::Type::spawn2:
            D4Lines(position, color::blue);
            break;

        default:
            break;
    }
}

void Draw::armyPower(pair<int, int> position, int armyPower)
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
        txt->x = position.first * Config::SQUARESIZE - (Config::LINEWIDTH) + txtSize / 2;
        txt->y = position.second * Config::SQUARESIZE - (Config::LINEWIDTH) + txtSize / 3;
        S2D_DrawText(txt);
    }
    else
    {
        std::cout << "fonts error" << std::endl;
    }
    S2D_FreeText(txt);
}