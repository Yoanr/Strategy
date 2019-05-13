#include "Square.hpp"

Square::Square(Type typeGiven) : t(typeGiven)
{
}

Square::~Square()
{
}

Square::Type Square::getType(){
    return t;
}