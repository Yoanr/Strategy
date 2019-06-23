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

    enum mode
    {
        p1versusp2 = 0,
        aiversusaiAUTO = 1,
        aiversusaiMANUAL = 2,
        p1versusai = 3

    };

    enum eval
    {
        fct1 = 1,
        fct2 = 2
    };

    static const int SQUARESIZE{50};
    static const int NUMBEROFSQUARE{11};
    static const int GRIDSIZE{SQUARESIZE * NUMBEROFSQUARE};
    static const int LINEWIDTH{2};
    static const Level DIFFICULTY{wtf};
    static const bool SQUAREUGLY{false};
    static const bool PRINTBOMB{false};
    static const mode MODE{aiversusaiMANUAL};

    static const eval EVAL_FCT_AIP1{eval::fct1};
    static const eval EVAL_FCT_AIP2{eval::fct2};
    static const int DEPTH{0};
};

#endif