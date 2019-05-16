#include "Square.hpp"

Square::Square(Type typeGiven) : t(typeGiven)
{
    switch (typeGiven)
    {
        case Square::Type::tower:
            r = 0;
            g = 1;
            b = 0;
            a = 1;
            break;
        //TODO remove color on bomb square
        case Square::Type::bomb:
            r = 1;
            g = 1;
            b = 0;
            a = 1;
            break;

        default:
            r = 1;
            g = 1;
            b = 1;
            a = 1;
    }
}

float Square::getR(){
    return r;
}
float Square::getG(){
    return g;
}
float Square::getB(){
    return b;
}
float Square::getA(){
    return a;
}

void Square::setR(float rGiven){
    r = rGiven;
}
void Square::setG(float gGiven)
{
    g = gGiven;
}
void Square::setB(float bGiven)
{
    b = bGiven;
}
void Square::setA(float aGiven){
    a = aGiven;
}

void Square::setType(Type tGiven){
    t = tGiven;
}

void Square::setColor(color::Color color){
    r=color.r;
    g=color.g;
    b=color.b;
}


Square::~Square()
{
}

Square::Type Square::getType(){
    return t;
}