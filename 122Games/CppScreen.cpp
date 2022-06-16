#include <list>

#include "framework.h"
#include "CppScreen.h"
#include "LedMatrix.h"
#include "MainUi.h"
#include "Ui.h"

#include "ClassNames.h"
#include HEADER_FILE(MAX_7219_CLASS)

static const int LEFT_MARGIN = 20;
static const int PIXEL_WIDTH = 20;
static const int RIGHT_MARGIN = 20;

static const int TOP_MARGIN = 20;
static const int PIXEL_HEIGHT = 20;
static const int BOTTOM_MARGIN = 20;

static const int PIXELS_PLUS_MARGIN_WIDTH = LEFT_MARGIN + MainUi::MAX_X * PIXEL_WIDTH + RIGHT_MARGIN;
static const int PIXELS_PLUS_MARGIN_HEIGHT = TOP_MARGIN + MainUi::MAX_Y * PIXEL_HEIGHT + BOTTOM_MARGIN;


CppScreen::CppScreen()
    : _firstDraw(true)
{
    SetRect(&_backgroundPixelsRectangle, 0, 0, PIXELS_PLUS_MARGIN_WIDTH, PIXELS_PLUS_MARGIN_HEIGHT);
    _backgroundPixelsColor = CreateSolidBrush(RGB(0, 0, 0));
    SetRect(&_pixelsBorderRectangle, LEFT_MARGIN - 1, TOP_MARGIN - 1,
        PIXELS_PLUS_MARGIN_WIDTH - RIGHT_MARGIN,
        PIXELS_PLUS_MARGIN_HEIGHT - BOTTOM_MARGIN);
    _pixelsBorderColor = CreateSolidBrush(RGB(255, 0, 0));

    for (int x = 0; x < MainUi::MAX_X; x++)
    {
        for (int y = 0; y < MainUi::MAX_Y; y++)
        {
            _rectangles[x][y] = GetPixelRect(x, y);
            // _brushes[x][y] = CreateSolidBrush(RGB(0, 0, 0));
        }
    }

    for (int player = 0; player < 2; player++)
    {
        for (int digit = 0; digit < 8; digit++)
        {
            for (int segment = 0; segment < 8; segment++)
            {
                _ledSegments[player][digit][segment] = GetLedSegmentRect(player, digit, segment);
            }
        }
    }
}


RECT CppScreen::GetPixelRect(int x, int y)
{
    RECT rect;
    SetRect(&rect, 
        LEFT_MARGIN + x * PIXEL_WIDTH + 1,
        TOP_MARGIN + y * PIXEL_HEIGHT + 1,
        LEFT_MARGIN + (x + 1) * PIXEL_WIDTH - 2,
        TOP_MARGIN + (y + 1) * PIXEL_HEIGHT - 2);
    return rect;
}


RECT CppScreen::GetLedSegmentRect(int player, int digit, int segment)
{
    RECT rect;
    SetRect(&rect,
        20 + 200 * player + digit * 10,
        300 + segment * 20,
        20 + 200 * player + digit * 10 + 7,
        300 + segment * 20 - 5);
    return rect;
}

/* virtual */ void CppScreen::Draw(Ui* ui, HDC hdc, HWND hwnd)
{
    if (_firstDraw)
    {
        FillRect(hdc, &_backgroundPixelsRectangle, _backgroundPixelsColor);
        FrameRect(hdc, &_pixelsBorderRectangle, _pixelsBorderColor);
        _firstDraw = false;
    }

    HBRUSH brush;

    // LED Matrix
    LedMatrix* ledMatrix = ui->GetMainUi()->GetLedMatrix();

    for (int x = 0; x < MainUi::MAX_X; x++)
    {
        for (int y = 0; y < MainUi::MAX_Y; y++)
        {
            if (ui->GetMainUi()->GetLedMatrix()->IsLedInvalidated(x, y))
            {
                FastLedCRGB* rgb = ledMatrix->GetLed(x, y);
                brush = CreateSolidBrush(RGB(rgb->red, rgb->green, rgb->blue));
                FillRect(hdc, &(_rectangles[x][y]), brush);
                DeleteObject(brush);
            }
        }
    }

    // Player 1 Segment


    for (int player = 0; player < 2; player++)
    {
        for (int digit = 0; digit < 8; digit++)
        {
            uint8_t segments = ui->GetPlayerUi(player)->GetLedSegments()->GetMax7219()->STUB_GetSegments(digit);
            for (int segment = 0; segment < 8; segment++)
            {
                bool on = (segments & (1 << segment));
                brush = CreateSolidBrush(RGB(on ? 255 : 0, 0, 0));
                _ledSegments[player][digit][segment] = GetLedSegmentRect(player, digit, segment);
                FillRect(hdc, &(_ledSegments[player][digit][segment]), brush);
                DeleteObject(brush);
            }
        }
    }

    
     
    // Reset invalidation

    ui->GetMainUi()->GetLedMatrix()->ResetInvalidatedLeds();
}
