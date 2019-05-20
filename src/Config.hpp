#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "color.hpp"

class Config
{
public:
    enum  Level   {
        easy    = 1,
        normal  = 2,
        hard    = 3,
        expert  = 4
    };

    static const int SQUARESIZE{50};
    static const int NUMBEROFSQUARE{11};
    static const int GRIDSIZE{SQUARESIZE * NUMBEROFSQUARE};
    static const int LINEWIDTH{2};
    static const Level DIFFICULTY{normal};
    static const bool SQUAREUGLY{false};
    static const bool PRINTBOMB{true};
    static const bool AI{true};
};

#endif