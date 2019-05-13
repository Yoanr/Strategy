#ifndef SQUARE_H
#define SQUARE_H

#include "Army.hpp"

class Square
{
public:
    enum Type
    {
        basic = 0,
        bomb = 1,
        tower = 2
    };
    Square(Type t);
    ~Square();

private:
    int r;
    int g;
    int b;
    int a;
    Type t;

};

#endif