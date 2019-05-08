#include <simple2d.h>
void drawBlackLine(int l1x, int l1y, int l2x, int l2y, int lineWidth)
{
    S2D_DrawLine(l1x, l1y, l2x, l2y,
                 lineWidth,
                 0, 0, 0, 1,
                 0, 0, 0, 1,
                 0, 0, 0, 1,
                 0, 0, 0, 1);
}

void draw4Lines(int i,int j,int lineWidth,int squareSize){
    int l1x = i * squareSize;
    int l1y = j * squareSize;
    int l2x = l1x + squareSize;
    int l3y = l1y + squareSize;

    drawBlackLine(l1x,l1y,l2x,l1y,lineWidth);
    drawBlackLine(l2x, l1y, l2x, l3y, lineWidth);
    drawBlackLine(l2x, l3y, l1x, l3y, lineWidth);
    drawBlackLine(l1x, l3y, l1x, l1y, lineWidth);
}

void drawSquare(int i,int j/*, int lineWidth*/, int squareSize){
    int x1 = i * squareSize /*+ lineWidth*/;
    int y1 = j * squareSize /*+ lineWidth*/;
    int x2 = x1 + squareSize;
    int y2 = y1;
    int x3 = x2;
    int y3 = y2 + squareSize;
    int x4 = x1;
    int y4 = y3;

    if ((i == 2 && j == 6) || (i == 6 && j == 6) || (i == 10 && j == 6))
    {
        S2D_DrawQuad(x1, y1, 0, 1, 0, 1,
                     x2, y2, 0, 1, 0, 1,
                     x3, y3, 0, 1, 0, 1,
                     x4, y4, 0, 1, 0, 1);
    }
    else if (i == 6 && j == 11)
    {
        S2D_DrawQuad(x1, y1, 0, 0, 1, 1,
                     x2, y2, 0, 0, 1, 1,
                     x3, y3, 0, 0, 1, 1,
                     x4, y4, 0, 0, 1, 1);
    }else if(i == 6 && j == 1)
    {
        S2D_DrawQuad(x1, y1, 1, 0, 0, 1,
                     x2, y2, 1, 0, 0, 1,
                     x3, y3, 1, 0, 0, 1,
                     x4, y4, 1, 0, 0, 1);
    }
    else{
        S2D_DrawQuad(x1, y1, 1, 1, 1, 1,
                     x2, y2, 1, 1, 1, 1,
                     x3, y3, 1, 1, 1, 1,
                     x4, y4, 1, 1, 1, 1);
    }

    
}
void render()
{

    int gridSize = 11;
    int lineWidth = 2;
    int squareSize = 50;
    int initX = 1;
    int initY = 1;

    for(int i = initX; i < initX + gridSize; i++){
        for (int j = initY; j < initY + gridSize; j++)
        {
            draw4Lines(i,j,lineWidth,squareSize);
            drawSquare(i,j,squareSize);
        }
    }
}

void update(){
}

int main()
{

    S2D_Window *window = S2D_CreateWindow(
        "WarY", 1000, 700, update, render, 0);
    window->background.r = 0.5;
    window->background.g = 0.5;
    window->background.b = 0.5;
    window->background.a = 1.0;

    S2D_Show(window);
    S2D_FreeWindow(window);
    return 0;
}
