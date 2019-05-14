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
    float getR();
    float getG();
    float getB();
    float getA();

    void setR(float r);
    void setG(float g);
    void setB(float b);
    void setA(float a);

private:
    float r;
    float g;
    float b;
    float a;
    Type t;
};

#endif