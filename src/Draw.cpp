#include "Draw.hpp"
#include "simple2d.h"

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

void Draw::square(int i, int j, int squareSize, int lineWidth, Square::Type squareType)
{
    int x1 = i * squareSize + lineWidth;
    int y1 = j * squareSize + lineWidth;
    int x2 = x1 + squareSize - lineWidth;
    int y2 = y1 + lineWidth;
    int x3 = x2 - lineWidth;
    int y3 = y2 + squareSize - lineWidth;
    int x4 = x1 + lineWidth;
    int y4 = y3 - lineWidth;

    switch (squareType)
    {
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

        D4Lines(i, j, lineWidth, squareSize, 1, 0, 0);
        break;

    case Square::Type::spawn2:
        S2D_DrawQuad(x1, y1, 1, 1, 1, 1,
                     x2, y2, 1, 1, 1, 1,
                     x3, y3, 1, 1, 1, 1,
                     x4, y4, 1, 1, 1, 1);

        D4Lines(i, j, lineWidth, squareSize, 0, 0, 1);
        break;

    default:
        S2D_DrawQuad(x1, y1, 1, 1, 1, 1,
                     x2, y2, 1, 1, 1, 1,
                     x3, y3, 1, 1, 1, 1,
                     x4, y4, 1, 1, 1, 1);
    }
}