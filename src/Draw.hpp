#ifndef DRAW_HPP
#define DRAw_HPP

#include "Square.hpp"
#include "color.hpp"
#include <iostream>
using namespace std;


class Draw
{
public:
    static Draw& getInstance();
    void setPosition(pair<int, int> positionGiven);

    void D2Lines(color::Color color);
    void D4Lines(color::Color color);
    void square(Square square);
    void armyPower(int armyPower);


private:
    Draw() = default;
    ~Draw() = default;
    Draw(const Draw &) = delete;
    Draw &operator=(const Draw &) = delete;

    pair<int,int> position{-1,-1};
    void line(int l1x, int l1y, int l2x, int l2y, color::Color color);
};

#endif