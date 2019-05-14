#ifndef DRAW_HPP
#define DRAw_HPP

#include "Square.hpp"

class Draw
{
public:
    static void line(int l1x, int l1y, int l2x, int l2y, int lineWidth, float r, float g, float b);
    static void D2Lines(int i, int j, int lineWidth, int squareSize, float r, float g, float b);
    static void D4Lines(int i, int j, int lineWidth, int squareSize, float r, float g, float b);
    static void square(int i, int j, int squareSize, int lineWidth, Square square);
    static void army(int i, int j, int squareSize, int lineWidth, int idPLayer);
    static void buttons();
    static void armyPower(int i, int j, int squareSize, int lineWidth, int armyPower);
};

#endif