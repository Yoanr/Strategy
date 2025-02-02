#ifndef DRAW_HPP
#define DRAw_HPP

#include "Square.hpp"
#include "color.hpp"
#include "GameEngine.hpp"


using namespace std;

class Draw
{
public:
    static Draw& getInstance();
    void render(GameEngine &gameEngine);

private:
    Draw() = default;
    ~Draw() = default;
    Draw(const Draw &) = delete;
    Draw &operator=(const Draw &) = delete;

    pair<int, int> position{-1, -1};
    void setPosition(pair<int, int> positionGiven);

    void line(int l1x, int l1y, int l2x, int l2y, int linewidth, color::Color color);
    void rectangle(int x1, int y1, int width, int length, color::Color color);
    void square(int x1, int y1, int width,color::Color color); // draw a square easily
    void text(string str, int txtSize, color::Color c, int x, int y);
    void img(string path, int x, int y, int width, int height);
    void square4Lines(int x1, int y1, int width, int length, int linewidth, color::Color color);
    void D2Lines(color::Color color);
    void D4Lines(color::Color color);

    void square(Square square);
    void armyPower(int armyPower);

    void menuChoice();
    void field(GameEngine &gameEngine);
    void possibleArmy(GameEngine &gameEngine);
    void showInfo(GameEngine &gameEngine);
    void showFight();
    void victory(GameEngine &gameEngine);
};

#endif
