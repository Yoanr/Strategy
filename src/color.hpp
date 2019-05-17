#ifndef COLOR_HPP
#define COLOR_HPP

#include "Square.hpp"

namespace color {
    struct Color {
        float r;
        float g;
        float b;
        float a;
    };

    const Color black{0,0,0,1};
    const Color blue{0, 0, 1, 1};
    const Color red{1, 0, 0, 1};
    const Color green{0, 1, 0, 1};
    const Color white{1, 1, 1, 1};
    const Color grey{0.5, 0.5, 0.5, 1};
}

#endif