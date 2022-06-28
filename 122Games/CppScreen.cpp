#ifdef WIN32

#include <list>
#include <string>
//#include <chrono>

#include "framework.h"
#include "CppScreen.h"
#include "LedMatrix.h"
#include "MainUi.h"
#include "Ui.h"
#include "FourDigitsLed.h"
#include "AssertUtils.h"
#include "Sound.h"


static const int LEFT_MARGIN = 20;
static const int PIXEL_WIDTH = 20;
static const int RIGHT_MARGIN = 20;

static const int TOP_MARGIN = 20;
static const int PIXEL_HEIGHT = 20;
static const int BOTTOM_MARGIN = 20;

static const int PIXELS_PLUS_MARGIN_WIDTH = LEFT_MARGIN + MainUi::MAX_X * PIXEL_WIDTH + RIGHT_MARGIN;
static const int PIXELS_PLUS_MARGIN_HEIGHT = TOP_MARGIN + MainUi::MAX_Y * PIXEL_HEIGHT + BOTTOM_MARGIN;

static const int JOYSTICK_AREA_TOP = 250;
static const int JOYSTICK_AREA_LEFT = 400;
static const int JOYSTICK_AREA_WIDTH = 50;
static const int JOYSTICK_AREA_HEIGHT = 50;
static const int JOYSTICK_LOCATION_WIDTH = 5;
static const int JOYSTICK_MARGIN = 10;
static const int JOYSTICK_TEXT_WIDTH = 100;
static const int JOYSTICK_TEXT_HEIGHT = 20;


CppScreen::CppScreen()
    : _firstDraw(true)
{
    SetRect(&_backgroundPixelsRectangle, 0, 0, PIXELS_PLUS_MARGIN_WIDTH, PIXELS_PLUS_MARGIN_HEIGHT);
    _backgroundPixelsColor = CreateSolidBrush(RGB(0, 0, 0));
    SetRect(&_pixelsBorderRectangle, LEFT_MARGIN - 1, TOP_MARGIN - 1,
        PIXELS_PLUS_MARGIN_WIDTH - RIGHT_MARGIN,
        PIXELS_PLUS_MARGIN_HEIGHT - BOTTOM_MARGIN);
    _pixelsBorderColor = CreateSolidBrush(RGB(255, 0, 0));

    // 
    for (int x = 0; x < MainUi::MAX_X; x++)
    {
        for (int y = 0; y < MainUi::MAX_Y; y++)
        {
            _LedMatrixRectangles[x][y] = GetPixelRect(x, y);
        }
    }

    for (int digit = 0; digit < 4; digit++)
    {
        for (int segment = 0; segment < 8; segment++)
        {
            _ledSegmentsRectangles[digit][segment] = GetLedSegmentRect(digit, segment);
        }
    }

    // Speaker
    static const int SPEAKER_AREA_TOP = 290;
    static const int SPEAKER_AREA_LEFT = 200;
    static const int SPEAKER_AREA_WIDTH = 150;
    static const int SPEAKER_AREA_HEIGHT = 50;
    static const int SPEAKER_TEXT_LEFT_MARGIN = 10;
    static const int SPEAKER_TEXT_LINE_MARGIN = 5;

    SetRect(&_speakerTextRectangle,
        SPEAKER_AREA_LEFT, SPEAKER_AREA_TOP,
        SPEAKER_AREA_LEFT + SPEAKER_AREA_WIDTH, SPEAKER_AREA_TOP + SPEAKER_AREA_HEIGHT);
    SetRect(&_speakerDurationTextRectangle,
        SPEAKER_AREA_LEFT + SPEAKER_TEXT_LEFT_MARGIN, SPEAKER_AREA_TOP + SPEAKER_TEXT_LINE_MARGIN,
        SPEAKER_AREA_LEFT + SPEAKER_AREA_WIDTH, SPEAKER_AREA_TOP + SPEAKER_AREA_HEIGHT / 2);
    SetRect(&_speakerFrequencyTextRectangle, 
        SPEAKER_AREA_LEFT + SPEAKER_TEXT_LEFT_MARGIN, SPEAKER_AREA_TOP + SPEAKER_AREA_HEIGHT / 2,
        SPEAKER_AREA_LEFT + SPEAKER_AREA_WIDTH, SPEAKER_AREA_TOP + SPEAKER_AREA_HEIGHT);

    // Joystick
    SetRect(&_joyStickRectangle, 
        JOYSTICK_AREA_LEFT - JOYSTICK_MARGIN, JOYSTICK_AREA_TOP - JOYSTICK_MARGIN,
        JOYSTICK_AREA_LEFT + JOYSTICK_AREA_WIDTH + JOYSTICK_MARGIN, JOYSTICK_AREA_TOP + JOYSTICK_AREA_HEIGHT + JOYSTICK_MARGIN);
    SetRect(&_joyStickButtonRectangle, 
        JOYSTICK_AREA_LEFT - JOYSTICK_MARGIN, JOYSTICK_AREA_TOP + JOYSTICK_AREA_HEIGHT + JOYSTICK_MARGIN,
        JOYSTICK_AREA_LEFT + JOYSTICK_AREA_WIDTH + JOYSTICK_MARGIN, JOYSTICK_AREA_TOP + JOYSTICK_AREA_HEIGHT + JOYSTICK_MARGIN + JOYSTICK_TEXT_HEIGHT);
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


RECT CppScreen::GetFullLedSegmentAreaRect()
{
    const uint8_t MARGIN = 10;

    RECT rect;
    SetRect(&rect, 3 * LED_SEGMENT_LENGTH - MARGIN, 300 - MARGIN,
        3 * LED_SEGMENT_LENGTH * (4 + 1) + MARGIN, 300 + 2 * LED_SEGMENT_LENGTH + MARGIN);
    return rect;
}

RECT CppScreen::GetLedSegmentRect(int digit, int segment)
{
    int16_t left = 0;
    int16_t right = 0;
    int16_t top = 0;
    int16_t bottom = 0;

    switch (segment)
    {
    case 0: // Center segment
        right = LED_SEGMENT_LENGTH;
        top = LED_SEGMENT_LENGTH;
        bottom = LED_SEGMENT_LENGTH;
        break;

    case 1: // Top left segment
        bottom = LED_SEGMENT_LENGTH;
        break;

    case 2: // Bottom left segment
        top = LED_SEGMENT_LENGTH;
        bottom = 2 * LED_SEGMENT_LENGTH;
        break;

    case 3: // Bottom segment
        right = LED_SEGMENT_LENGTH;
        top = 2 * LED_SEGMENT_LENGTH;
        bottom = 2 * LED_SEGMENT_LENGTH;
        break;

    case 4: // Right bottom segment
        left = LED_SEGMENT_LENGTH;
        right = LED_SEGMENT_LENGTH;
        top = LED_SEGMENT_LENGTH;
        bottom = 2 * LED_SEGMENT_LENGTH;
        break;

    case 5: // Top right segment
        left = LED_SEGMENT_LENGTH;
        right = LED_SEGMENT_LENGTH;
        bottom = LED_SEGMENT_LENGTH;
        break;

    case 6: // Top segment
        right = LED_SEGMENT_LENGTH;
        break;

    case 7:
        // DP? 
        break;

    default:
        AssertUtils::MyAssert(false);
        break;
    }

    left += 3 * LED_SEGMENT_LENGTH * (digit + 1);
    right += 3 * LED_SEGMENT_LENGTH * (digit + 1);

    left -= LED_SEGMENT_WIDTH / 2;
    right += LED_SEGMENT_WIDTH / 2;
    top += 300 - LED_SEGMENT_WIDTH / 2;
    bottom += 300 + LED_SEGMENT_WIDTH / 2;
        
    RECT rect;
    SetRect(&rect, left, top, right, bottom);
    return rect;
}

/* virtual */ void CppScreen::Draw(Ui* ui, HDC hdc, HWND hwnd)
{
    // clock_t clock_value = clock();

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
                FillRect(hdc, &(_LedMatrixRectangles[x][y]), brush);
                DeleteObject(brush);
            }
        }
    }

    // Player Segment
    brush = CreateSolidBrush(RGB(0, 0, 0));
    RECT rect = GetFullLedSegmentAreaRect();
    FillRect(hdc, &rect, brush);
    DeleteObject(brush);

    brush = CreateSolidBrush(RGB(255, 0, 0));

    for (int digit = 0; digit < 4 ; digit++)
    {
        uint8_t segments = ui->GetMainUi()->GetFourDigitsLed()->GetSegments(digit);
        for (uint8_t segment = 0; segment < 8; segment++)
        {
            bool on = (segments & (1 << segment));
            if (on)
            {
                _ledSegmentsRectangles[digit][segment] = GetLedSegmentRect(digit, segment);
                FillRect(hdc, &(_ledSegmentsRectangles[digit][segment]), brush);
            }
        }
    }

    DeleteObject(brush);

    // Sound Texts
    brush = CreateSolidBrush(RGB(0, ui->GetMainUi()->GetSound()->IsPlaying() ? 100 : 0, 0));
    FillRect(hdc, &_speakerTextRectangle, brush);
    wchar_t isPlayingBuffer[26] = {};
    wchar_t frequencyTextBuffer[26] = {};

    Sound* sound = ui->GetMainUi()->GetSound();
    uint16_t duration = sound->GetDuration();
    wcscpy_s(isPlayingBuffer, sound->IsPlaying() ? L"Duration  : ON" : L"Duration  : Off");
    std::swprintf(frequencyTextBuffer, sizeof(frequencyTextBuffer) / sizeof(*frequencyTextBuffer),
        L"Frequency: %5d Hz", sound->GetFrequency());

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));
    
    DrawText(hdc, isPlayingBuffer, -1, &_speakerDurationTextRectangle, DT_SINGLELINE | DT_NOCLIP);
    DrawText(hdc, frequencyTextBuffer, -1, &_speakerFrequencyTextRectangle, DT_SINGLELINE | DT_NOCLIP);

    // Joystick
    brush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdc, &_joyStickRectangle, brush);

    brush = CreateSolidBrush(RGB(255, 100, 100));
    int x = (ui->GetPlayerUi()->GetJoyStick()->ReadX() + 100) * JOYSTICK_AREA_WIDTH / 200;
    int y = (ui->GetPlayerUi()->GetJoyStick()->ReadY() + 100) * JOYSTICK_AREA_HEIGHT / 200;

    SetRect(&_joyStickLocationRectangle,
        JOYSTICK_AREA_LEFT + x - JOYSTICK_LOCATION_WIDTH / 2,
        JOYSTICK_AREA_TOP + y - JOYSTICK_LOCATION_WIDTH / 2,
        JOYSTICK_AREA_LEFT + x + JOYSTICK_LOCATION_WIDTH / 2,
        JOYSTICK_AREA_TOP + y + JOYSTICK_LOCATION_WIDTH / 2);
        
    FillRect(hdc, &_joyStickLocationRectangle, brush);

    brush = CreateSolidBrush(RGB(0, 0, 0));
    FillRect(hdc, &_joyStickButtonRectangle, brush);
    if (ui->GetPlayerUi()->GetJoyStick()->ReadButton())
    {
        SetTextColor(hdc, RGB(255, 255, 255));
        DrawText(hdc, L"BUTTON", -1, &_joyStickButtonRectangle, DT_SINGLELINE | DT_NOCLIP);
    }
     
    // Reset invalidation
    ui->GetMainUi()->GetLedMatrix()->ResetInvalidatedLeds();

    // clock_t clock_end_value = clock();
    // int a = (clock_end_value - clock_value) / CLOCKS_PER_SEC;
}

#endif // WIN32