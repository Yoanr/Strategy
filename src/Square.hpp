#ifndef SQUARE_H
#define SQUARE_H

#include "Army.hpp"

class Square
{
public:
    Square();
    ~Square();

private:
    Army army;
    int r;
    int g;
    int b;
    int a;

};

#endif