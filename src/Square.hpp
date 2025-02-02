#ifndef SQUARE_H
#define SQUARE_H

#include "color.hpp"


class Square
{
public:
    enum Type
    {
        basic = 0,
        bomb = 1,
        tower = 2,
        spawn1 = 3,
        spawn2 = 4
    };
    Square(Type t);
    ~Square();
    Type getType();
    float getR();
    float getG();
    float getB();
    float getA();
    color::Color getColor();

    void setR(float r);
    void setG(float g);
    void setB(float b);
    void setA(float a);
    void setColor(color::Color color);
    void setType(Type t);

private:
    float r;
    float g;
    float b;
    float a;
    Type t;
};

#endif