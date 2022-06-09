#include "framework.h"
#include "CppScreen.h"
#include <list>

static const int LEFT_MARGIN = 20;
static const int PIXEL_WIDTH = 20;
static const int RIGHT_MARGIN = 20;

static const int TOP_MARGIN = 20;
static const int PIXEL_HEIGHT = 20;
static const int BOTTOM_MARGIN = 20;

static const int PIXELS_PLUS_MARGIN_WIDTH = LEFT_MARGIN + Canvas::MAX_X * PIXEL_WIDTH + RIGHT_MARGIN;
static const int PIXELS_PLUS_MARGIN_HEIGHT = TOP_MARGIN + Canvas::MAX_Y * PIXEL_HEIGHT + BOTTOM_MARGIN;


CppScreen::CppScreen()
{
    SetRect(&_backgroundPixelsRectangle, 0, 0, PIXELS_PLUS_MARGIN_WIDTH, PIXELS_PLUS_MARGIN_HEIGHT);
    _backgroundPixelsColor = CreateSolidBrush(RGB(0, 0, 0));
    SetRect(&_pixelsBorderRectangle, LEFT_MARGIN - 1, TOP_MARGIN - 1,
        PIXELS_PLUS_MARGIN_WIDTH - RIGHT_MARGIN,
        PIXELS_PLUS_MARGIN_HEIGHT - BOTTOM_MARGIN);
    _pixelsBorderColor = CreateSolidBrush(RGB(255, 0, 0));

    for (int x = 0; x < Canvas::MAX_X; x++)
    {
        for (int y = 0; y < Canvas::MAX_Y; y++)
        {
            _rectangles[x][y] = GetPixelRect(x, y);
            _brushes[x][y] = CreateSolidBrush(RGB(0, 0, 0));
        }
    }
}


/* static */ RECT CppScreen::GetPixelRect(int x, int y)
{
    RECT rect;
    SetRect(&rect, 
        LEFT_MARGIN + x * PIXEL_WIDTH + 1,
        TOP_MARGIN + y * PIXEL_HEIGHT + 1,
        LEFT_MARGIN + (x + 1) * PIXEL_WIDTH - 2,
        TOP_MARGIN + (y + 1) * PIXEL_HEIGHT - 2);
    return rect;
}


/* virtual */ void CppScreen::Draw(Canvas* canvas, HDC hdc, HWND hwnd)
{
    FillRect(hdc, &_backgroundPixelsRectangle, _backgroundPixelsColor);
    FrameRect(hdc, &_pixelsBorderRectangle, _pixelsBorderColor);

    HBRUSH brush;

    for (int x = 0; x < Canvas::MAX_X; x++)
    {
        for (int y = 0; y < Canvas::MAX_Y; y++)
        {
            //DeleteObject(_brushes[x][y]);
            Rgb rgb = canvas->GetPixel(x, y);
            brush = CreateSolidBrush(RGB(rgb.GetRed(), rgb.GetGreen(), rgb.GetBlue()));
            FillRect(hdc, &(_rectangles[x][y]), brush);
            DeleteObject(brush);
        }
    }
}
