#pragma once
#include "Screen.h"
#include "LedMatrix.h"
#include "MainUi.h"


class Ui;

class CppScreen
{
public:
    CppScreen();

    void Draw(Ui* canvas, HDC hdc, HWND hwnd);


private:
    RECT _backgroundPixelsRectangle;
    HBRUSH _backgroundPixelsColor;
    RECT _pixelsBorderRectangle;
    HBRUSH _pixelsBorderColor;

    // LED Matrix
    RECT _rectangles[MainUi::MAX_X][MainUi::MAX_Y];
   // HBRUSH _brushes[LedMatrix::MAX_X][LedMatrix::MAX_Y]; TODO: Use HBrushes

    RECT GetPixelRect(int x, int y);
    RECT GetLedSegmentRect(int player, int digit, int segment);

    // Player 1 Led Segments
    RECT _ledSegments[2][8][8]; // 8 ->4 digits, 8 segments

    bool _firstDraw;
};
