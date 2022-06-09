#pragma once
#include "Screen.h"
#include "Canvas.h"


class CppScreen :
    public Screen
{
public:
    CppScreen();

    void Draw(Canvas* canvas, HDC hdc, HWND hwnd);

    static RECT GetPixelRect(int x, int y);

private:
    RECT _backgroundPixelsRectangle;
    HBRUSH _backgroundPixelsColor;
    RECT _pixelsBorderRectangle;
    HBRUSH _pixelsBorderColor;

    RECT _rectangles[Canvas::MAX_X][Canvas::MAX_Y];
    HBRUSH _brushes[Canvas::MAX_X][Canvas::MAX_Y];
};
