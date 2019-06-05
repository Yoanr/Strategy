#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "color.hpp"

using namespace std;

class Config
{
public:
    enum  Level   {
        wtf = 0,
        easy    = 1,
        normal  = 2,
        hard    = 3,
        expert  = 4
    };

    static const int SQUARESIZE{50};
    static const int NUMBEROFSQUARE{11};
    static const int GRIDSIZE{SQUARESIZE * NUMBEROFSQUARE};
    static const int LINEWIDTH{2};
    static const Level DIFFICULTY{wtf};
    static const bool SQUAREUGLY{false};
    static const bool PRINTBOMB{true};
    static const bool AI{true};
    static const int DEPTH{1};
};

#endif