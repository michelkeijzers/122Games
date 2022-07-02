#pragma once
#include "Screen.h"
#include "LedMatrix.h"
#include "MainUi.h"


class Ui;

class CppScreen
{
public:
    CppScreen();
    ~CppScreen();

    void Draw(Ui* canvas, HDC hdc, HWND hwnd);


private:
    const static int LED_SEGMENT_LENGTH = 12;
    const static int LED_SEGMENT_WIDTH = 4;

    RECT _backgroundPixelsRectangle;
    RECT _pixelsBorderRectangle;
    HBRUSH _blackBrush;
    HBRUSH _redBrush;
    HBRUSH _darkGreenBrush;
    HBRUSH _greenBrush;

    // LED Matrix
    RECT _LedMatrixRectangles[MainUi::MAX_X][MainUi::MAX_Y];

    RECT GetPixelRect(int x, int y);
    RECT GetFullLedSegmentAreaRect();
    //RECT GetFullSpeakerTextsAreaRect();
    RECT GetLedSegmentRect(int digit, int segment);

    // Player Led Segments
    RECT _ledSegmentsRectangles[8][8]; // 8 ->4 digits, 8 segments

    // Sound show
    RECT _soundTextRectangle; 
    RECT _soundDurationTextRectangle;
    RECT _soundFrequencyTextRectangle;

    // Joystick Rectangle
    RECT _joyStickRectangle;
    RECT _joyStickLocationRectangle;
    RECT _joyStickButtonRectangle;

    // LCD Display Rectangle
    RECT _lcdDisplayBezelRectangle;
    RECT _lcdDisplayScreenRectangle;

    bool _firstDraw;
};
