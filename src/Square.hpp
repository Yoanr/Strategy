#ifndef SQUARE_H
#define SQUARE_H

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

private:
    int r;
    int g;
    int b;
    int a;
    Type t;

};

#endif