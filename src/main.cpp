#include <simple2d.h>

void render()
{
    S2D_DrawTriangle(
        320, 50, 1, 0, 0, 1,
        540, 430, 0, 1, 0, 1,
        100, 430, 0, 0, 1, 1);
}

void update(){
}

int main()
{

    S2D_Window *window = S2D_CreateWindow(
        "WarY", 500, 500, update, render, 0);

    S2D_Show(window);
    S2D_FreeWindow(window);
    return 0;
}
