#ifndef DRAW_HPP
#define DRAw_HPP

#include "Square.hpp"
#include "color.hpp"
#include <iostream>
using namespace std;


class Draw
{
public:
    static void line(int l1x, int l1y, int l2x, int l2y, color::Color color);
    static void D2Lines(pair<int,int> position, color::Color color);
    static void D4Lines(pair<int, int> position, color::Color color);
    static void square(pair<int, int> position, Square square);
    static void armyPower(pair<int, int> position, int armyPower);
};

#endif