#pragma once
#include "Screen.h"
#include "LedMatrix.h"

class Ui;

class CppScreen
{
public:
    CppScreen();

    void Draw(Ui* canvas, HDC hdc, HWND hwnd);

    static RECT GetPixelRect(int x, int y);

private:
    RECT _backgroundPixelsRectangle;
    HBRUSH _backgroundPixelsColor;
    RECT _pixelsBorderRectangle;
    HBRUSH _pixelsBorderColor;

    RECT _rectangles[LedMatrix::MAX_X][LedMatrix::MAX_Y];
    HBRUSH _brushes[LedMatrix::MAX_X][LedMatrix::MAX_Y];
};
