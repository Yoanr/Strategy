#include "Draw.hpp"
#include "../inc/simple2d.h"
#include <iostream>
#include "Config.hpp"


Draw& Draw::getInstance(){
    static Draw instance;
    return instance;
}

void Draw::render(GameEngine &gameEngine)
{
    if(not gameEngine.getChoice()){
        menuChoice();
        return;
    }
    for (int i = 0; i < Config::NUMBEROFSQUARE; i++)
    {
        for (int j = 0; j < Config::NUMBEROFSQUARE; j++)
        {
            pair<int, int> position(i, j);
            setPosition(position);

            field(position, gameEngine);
        }
    }
    showInfo(gameEngine.getCurrentRound(), gameEngine.getNbrOfBombHitted(), gameEngine.getTotalPowerArmy(), gameEngine.getCurrentIdPlayer());

    if (gameEngine.getHasWon())
    {
        victory(gameEngine.getEnnemyIdPlayer());
    }
}




void Draw::setPosition(pair<int,int> positionGiven){
position = positionGiven;
}
void Draw::line(int l1x, int l1y, int l2x, int l2y,int linewidth, color::Color color)
{
    S2D_DrawLine(l1x, l1y, l2x, l2y,
                 linewidth,
                 color.r, color.g, color.b, color.a,
                 color.r, color.g, color.b, color.a,
                 color.r, color.g, color.b, color.a,
                 color.r, color.g, color.b, color.a);
}

void Draw::D4Lines(color::Color color)
{
    int l1x = position.first * Config::SQUARESIZE;
    int l1y = position.second * Config::SQUARESIZE;
    int l2x = l1x + Config::SQUARESIZE;
    int l3y = l1y + Config::SQUARESIZE;

    line(l1x, l1y, l2x, l1y, Config::LINEWIDTH, color);
    line(l2x, l1y, l2x, l3y, Config::LINEWIDTH, color);
    line(l2x, l3y, l1x, l3y, Config::LINEWIDTH, color);
    line(l1x, l3y, l1x, l1y, Config::LINEWIDTH, color);
}

void Draw::D2Lines(color::Color color)
{
    int l1x = position.first * Config::SQUARESIZE;
    int l1y = position.second * Config::SQUARESIZE;
    int l2x = l1x + Config::SQUARESIZE;
    int l3y = l1y + Config::SQUARESIZE;

    line(l2x, l1y, l2x, l3y, Config::LINEWIDTH, color);
    line(l2x, l3y, l1x, l3y, Config::LINEWIDTH, color);
}

void Draw::square(Square squareGiven)
{
    if(Config::SQUAREUGLY){
        int x1 = position.first * Config::SQUARESIZE + Config::LINEWIDTH;
        int y1 = position.second * Config::SQUARESIZE + Config::LINEWIDTH;
         int x2 = x1 + Config::SQUARESIZE - Config::LINEWIDTH;
        int y2 = y1 + Config::LINEWIDTH;
        int x3 = x2 - Config::LINEWIDTH;
        int y3 = y2 + Config::SQUARESIZE - Config::LINEWIDTH;
        int x4 = x1 + Config::LINEWIDTH;
        int y4 = y3 - Config::LINEWIDTH;

        S2D_DrawQuad(x1, y1, squareGiven.getR(), squareGiven.getG(), squareGiven.getB(), squareGiven.getA(),
                     x2, y2, squareGiven.getR(), squareGiven.getG(), squareGiven.getB(), squareGiven.getA(),
                     x3, y3, squareGiven.getR(), squareGiven.getG(), squareGiven.getB(), squareGiven.getA(),
                     x4, y4, squareGiven.getR(), squareGiven.getG(), squareGiven.getB(), squareGiven.getA());
    }else {
        int x1 = position.first * Config::SQUARESIZE + Config::LINEWIDTH;
        int y1 = position.second * Config::SQUARESIZE + Config::LINEWIDTH;

        square(x1, y1, Config::SQUARESIZE - Config::LINEWIDTH, squareGiven.getColor());
    }
   
    switch (squareGiven.getType())
    {

        case Square::Type::spawn1:
            D4Lines(color::red);
            break;

        case Square::Type::spawn2:
            D4Lines(color::blue);
            break;
        case Square::Type::tower:
            D4Lines(color::green);

        default:
            break;
    }
}

void Draw::armyPower(int armyPower)
{
    string armyPowerStr = to_string(armyPower);
    int txtSize = 0;
    if(armyPower > 9) {
        txtSize = 25;
    }else{
        txtSize = 30;
    }
    int x = position.first * Config::SQUARESIZE - (Config::LINEWIDTH) + txtSize / 2;
    int y = position.second * Config::SQUARESIZE - (Config::LINEWIDTH) + txtSize / 3;

    text(armyPowerStr, txtSize, color::white, x, y);
}

void Draw::rectangle(int x1, int y1, int width, int length, color::Color c){
    S2D_DrawQuad(x1, y1, c.r, c.g, c.b, c.a,
                 x1 + width, y1, c.r, c.g, c.b, c.a,
                 x1 + width, y1 + length, c.r, c.g, c.b, c.a,
                 x1, y1 + length, c.r, c.g, c.b, c.a);
}
void Draw::square(int x1, int y1, int width, color::Color color){
    rectangle(x1,y1,width,width,color);
}
void Draw::menuChoice()
{
    img(std::string("./resources/img/background.png"),0,0,800,555);
    text(std::string("Menu"), 70, color::white, 320, 100);
    rectangle(180, 200, 450, 150, color::grey);
    line(330,200,330,350,Config::LINEWIDTH,color::black);
    line(480, 200, 480, 350, Config::LINEWIDTH, color::black);
    text(std::string("P1 vs P2"), 20, color::white, 210, 260);
    text(std::string("P1 vs AI"), 20, color::white, 360, 260);
    text(std::string("AI vs AI"), 20, color::white, 510, 260);
}

void Draw::victory(int idPlayer)
{
    rectangle(50,200,450,150,color::grey);
    square4Lines(50,200,450,150,3,color::black);
    rectangle(320, 290, 90, 50, color::black);
    rectangle(160, 290, 90, 50, color::black);

    int txtSize = 30;
    string const str1("Player ");
    string const str2 = to_string(idPlayer);
    string const str3(" has won the party!");

    string const strMsg(str1+str2+str3);

    text(strMsg,txtSize,color::black,65,220);
    text(std::string("Replay"), 20, color::white, 170, 300);
    text(std::string("Quit"), 20, color::white, 342, 300);
}
void Draw::text(string str,int txtSize,color::Color c,int x,int y){
    S2D_Text *txt = S2D_CreateText("./resources/fonts/verdana.ttf", str.c_str(), txtSize);
    if (txt)
    {
        txt->color.r = c.r;
        txt->color.g = c.g;
        txt->color.b = c.b;
        txt->color.a = c.a;
        txt->x = x;
        txt->y = y;
        S2D_DrawText(txt);
    }
    else
    {
        cout << "fonts error" << endl;
    }
    S2D_FreeText(txt);
}

void Draw::img(string path, int x, int y, int width, int height)
{
    S2D_Image *img = S2D_CreateImage(path.c_str());
    if (img)
    {
        img->x = x;
        img->y = y;
        img->width = width;
        img->height = height;
    }
    else
    {
        cout << "img error" << endl;
    }
    S2D_DrawImage(img);
}

void Draw::square4Lines(int x1,int y1, int width, int length ,int linewidth,color::Color color)
{
    int x1w = x1+width;
    int y1l = y1 + length;
    
    line(x1, y1, x1w, y1,linewidth, color);
    line(x1w, y1, x1w, y1l, linewidth, color);
    line(x1w, y1l, x1, y1l, linewidth, color);
    line(x1, y1l, x1, y1, linewidth, color);
}

void Draw::showInfo(int round, pair<int, int> bombHit, pair<int, int> armyPowerTotal,int currentPlayerId)
{
    if(Config::getInstance().MODE == Config::mode::p1versusp2){
        text(std::string("P1"), 80, color::red, 620, 100);
        text(std::string("P2"), 80, color::blue, 620, 350);
    }
    else if (Config::getInstance().MODE == Config::mode::p1versusai)
    {
        text(std::string("P1"), 80, color::red, 620, 100);
        text(std::string("AI"), 80, color::blue, 620, 350);
    }
    else if (Config::getInstance().MODE == Config::mode::aiversusaiMANUAL)
    {
        text(std::string("AI"), 80, color::red, 620, 100);
        text(std::string("AI"), 80, color::blue, 620, 350);
    }
    line(550, 250, 800, 250, Config::LINEWIDTH, color::white);
    line(550, 300, 800, 300, Config::LINEWIDTH, color::white);


    if(currentPlayerId == 1){
        line(630,200,710,200,Config::LINEWIDTH,color::red);
    }else{
        line(630, 450, 710, 450, Config::LINEWIDTH, color::blue);
    }
    string const strRound(string("Round ") + to_string(round));
    text(strRound, 20, color::white, 630, 265);

    string const strInfoP1(string("ArmyPower:") + to_string(armyPowerTotal.first)+string(" , BombHitted:")+to_string(bombHit.first));
    text(strInfoP1, 10, color::white, 560, 10);

    string const strInfoP2(string("ArmyPower:") + to_string(armyPowerTotal.second) + string(" , BombHitted:") + to_string(bombHit.second));
    text(strInfoP2, 10, color::white, 560, 500);
}

void Draw::field(pair<int, int> position, GameEngine& gameEngine)
{
    D2Lines(color::black); //Black color
    square(gameEngine.getSquare(position));
    possibleArmy(position, gameEngine);
}

void Draw::possibleArmy(pair<int, int> position, GameEngine& gameEngine)
{
    pair<int, int> p = gameEngine.getPossibleArmy(position); // <,>
    int playerId = p.first;
    int armyLocalPower = p.second;

    if (not armyLocalPower == 0)
    {
        gameEngine.setColorSquareByPlayer(position, playerId);
        armyPower(armyLocalPower);
    }
}