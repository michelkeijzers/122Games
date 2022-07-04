#ifdef WIN32

#include <list>
#include <string>

#include "framework.h"
#include "CppScreen.h"
#include "LedMatrix.h"
#include "MainUi.h"
#include "Ui.h"
#include "LcdDisplay.h"
#include "Joystick.h"
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

static const int LCD_AREA_TOP = 250;
static const int LCD_AREA_LEFT = 600;
static const int LCD_CHARACTER_WIDTH = 16;
static const int LCD_CHARACTER_HEIGHT = 20;
static const int LCD_AREA_WIDTH = LCD_CHARACTER_WIDTH * HardwareProperties::LCD_NR_OF_COLUMNS;
static const int LCD_AREA_HEIGHT = LCD_CHARACTER_HEIGHT * HardwareProperties::LCD_NR_OF_ROW;
static const int LCD_MARGIN = 10;

CppScreen::CppScreen()
    : _firstDraw(true)
{
    _blackBrush = CreateSolidBrush(RGB(0, 0, 0));
    _redBrush = CreateSolidBrush(RGB(255, 0, 0));
    _darkGreenBrush = CreateSolidBrush(RGB(30, 230, 30));
    _greenBrush = CreateSolidBrush(RGB(100, 255, 100));
    
    SetRect(&_backgroundPixelsRectangle, 0, 0, PIXELS_PLUS_MARGIN_WIDTH, PIXELS_PLUS_MARGIN_HEIGHT);
    SetRect(&_pixelsBorderRectangle, LEFT_MARGIN - 1, TOP_MARGIN - 1,
        PIXELS_PLUS_MARGIN_WIDTH - RIGHT_MARGIN,
        PIXELS_PLUS_MARGIN_HEIGHT - BOTTOM_MARGIN);

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
    static const int SOUND_AREA_TOP = 290;
    static const int SOUND_AREA_LEFT = 200;
    static const int SOUND_AREA_WIDTH = 150;
    static const int SOUND_AREA_HEIGHT = 50;
    static const int SOUND_TEXT_LEFT_MARGIN = 10;
    static const int SOUND_TEXT_LINE_MARGIN = 5;

    SetRect(&_soundTextRectangle,
        SOUND_AREA_LEFT, SOUND_AREA_TOP,
        SOUND_AREA_LEFT + SOUND_AREA_WIDTH, SOUND_AREA_TOP + SOUND_AREA_HEIGHT);
    SetRect(&_soundDurationTextRectangle,
        SOUND_AREA_LEFT + SOUND_TEXT_LEFT_MARGIN, SOUND_AREA_TOP + SOUND_TEXT_LINE_MARGIN,
        SOUND_AREA_LEFT + SOUND_AREA_WIDTH - SOUND_TEXT_LEFT_MARGIN, SOUND_AREA_TOP + SOUND_AREA_HEIGHT / 2 - SOUND_TEXT_LINE_MARGIN);
    SetRect(&_soundFrequencyTextRectangle, 
        SOUND_AREA_LEFT + SOUND_TEXT_LEFT_MARGIN, SOUND_AREA_TOP + SOUND_AREA_HEIGHT / 2,
        SOUND_AREA_LEFT + SOUND_AREA_WIDTH - SOUND_TEXT_LEFT_MARGIN, SOUND_AREA_TOP + SOUND_AREA_HEIGHT - SOUND_TEXT_LINE_MARGIN);

    // Joystick
    SetRect(&_joyStickRectangle, 
        JOYSTICK_AREA_LEFT - JOYSTICK_MARGIN, JOYSTICK_AREA_TOP - JOYSTICK_MARGIN,
        JOYSTICK_AREA_LEFT + JOYSTICK_AREA_WIDTH + JOYSTICK_MARGIN, JOYSTICK_AREA_TOP + JOYSTICK_AREA_HEIGHT + JOYSTICK_MARGIN);
    SetRect(&_joyStickButtonRectangle, 
        JOYSTICK_AREA_LEFT - JOYSTICK_MARGIN, JOYSTICK_AREA_TOP + JOYSTICK_AREA_HEIGHT + JOYSTICK_MARGIN,
        JOYSTICK_AREA_LEFT + JOYSTICK_AREA_WIDTH + JOYSTICK_MARGIN, JOYSTICK_AREA_TOP + JOYSTICK_AREA_HEIGHT + JOYSTICK_MARGIN + JOYSTICK_TEXT_HEIGHT);

    // LCD Display
    SetRect(&_lcdDisplayBezelRectangle, LCD_AREA_LEFT - LCD_MARGIN, LCD_AREA_TOP - LCD_MARGIN,
        LCD_AREA_LEFT + LCD_AREA_WIDTH + LCD_MARGIN, LCD_AREA_TOP + LCD_AREA_HEIGHT + LCD_MARGIN);
    SetRect(&_lcdDisplayScreenRectangle, LCD_AREA_LEFT - LCD_MARGIN / 2, LCD_AREA_TOP - LCD_MARGIN / 2,
        LCD_AREA_LEFT + LCD_AREA_WIDTH + LCD_MARGIN / 2, LCD_AREA_TOP + LCD_AREA_HEIGHT + LCD_MARGIN / 2);
}


CppScreen::~CppScreen()
{
    if (_blackBrush != nullptr)
    {
        DeleteObject(&_blackBrush);
    }

    if (_redBrush != nullptr)
    {
        DeleteObject(&_redBrush);
    }

    if (_darkGreenBrush != nullptr)
    {
        DeleteObject(&_darkGreenBrush);
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
        RECT rect = GetFullLedSegmentAreaRect();
        FillRect(hdc, &rect, _blackBrush);

        FillRect(hdc, &_soundTextRectangle, _blackBrush);
        FillRect(hdc, &_backgroundPixelsRectangle, _blackBrush);
        FrameRect(hdc, &_pixelsBorderRectangle, _redBrush);
        FillRect(hdc, &_joyStickRectangle, _blackBrush);
        FillRect(hdc, &_lcdDisplayBezelRectangle, _blackBrush);
        FillRect(hdc, &_lcdDisplayScreenRectangle, _greenBrush);
        
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
    RECT rect = GetFullLedSegmentAreaRect();
    FillRect(hdc, &rect, _blackBrush);

    for (int digit = 0; digit < 4 ; digit++)
    {
        uint8_t segments = ui->GetMainUi()->GetFourDigitsLed()->GetSegments(digit);
        for (uint8_t segment = 0; segment < 8; segment++)
        {
            bool on = (segments & (1 << segment));
            if (on)
            {
                _ledSegmentsRectangles[digit][segment] = GetLedSegmentRect(digit, segment);
                FillRect(hdc, &(_ledSegmentsRectangles[digit][segment]), _redBrush);
            }
        }
    }

    // Sound Texts
    Sound* sound = ui->GetMainUi()->GetSound();
    if (sound->IsInvalidated())
    {
        if (sound->IsDurationInvalidated())
        {
            FillRect(hdc, &_soundDurationTextRectangle, sound->IsPlaying() ? _redBrush : _blackBrush);

            wchar_t isPlayingBuffer[26] = {};
            uint16_t duration = sound->GetDuration();
            wcscpy_s(isPlayingBuffer, sound->IsPlaying() ? L"Duration  : ON" : L"Duration  : Off");

            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            DrawText(hdc, isPlayingBuffer, -1, &_soundDurationTextRectangle, DT_SINGLELINE | DT_NOCLIP);
        }

        if (sound->IsFrequencyInvalidated())
        {
            FillRect(hdc, &_soundFrequencyTextRectangle, sound->IsPlaying() ? _redBrush : _blackBrush);

            wchar_t frequencyTextBuffer[26] = {};
            std::swprintf(frequencyTextBuffer, sizeof(frequencyTextBuffer) / sizeof(*frequencyTextBuffer),
                L"Frequency: %5d Hz", sound->GetFrequency());

            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 255, 255));
            DrawText(hdc, frequencyTextBuffer, -1, &_soundFrequencyTextRectangle, DT_SINGLELINE | DT_NOCLIP);
        }
    }

    // Joystick
    Joystick* joystick = ui->GetPlayerUi()->GetJoystick();
    if (joystick->IsDirectionInvalidated())
    {
        FillRect(hdc, &_joyStickLocationRectangle, _blackBrush);
        int x = (joystick->ReadX() + 100) * JOYSTICK_AREA_WIDTH / 200;
        int y = (joystick->ReadY() + 100) * JOYSTICK_AREA_HEIGHT / 200;

        SetRect(&_joyStickLocationRectangle,
            JOYSTICK_AREA_LEFT + x - JOYSTICK_LOCATION_WIDTH / 2,
            JOYSTICK_AREA_TOP + y - JOYSTICK_LOCATION_WIDTH / 2,
            JOYSTICK_AREA_LEFT + x + JOYSTICK_LOCATION_WIDTH / 2,
            JOYSTICK_AREA_TOP + y + JOYSTICK_LOCATION_WIDTH / 2);

        FillRect(hdc, &_joyStickLocationRectangle, _redBrush);
    }

    if (joystick->IsButtonInvalidated())
    {
        FillRect(hdc, &_joyStickButtonRectangle, joystick->ReadButton() ? _greenBrush : _blackBrush);
        SetBkMode(hdc, TRANSPARENT);
        SetTextColor(hdc, RGB(255, 255, 255));
        DrawText(hdc, L"BUTTON", -1, &_joyStickButtonRectangle, DT_SINGLELINE | DT_NOCLIP);
    }
    
    // LCD Display
    LcdDisplay* lcdDisplay = ui->GetMainUi()->GetLcdDisplay();

    for (uint8_t row = 0; row < lcdDisplay->GetNrOfRows(); row++)
    {
        for (uint8_t column = 0; column < lcdDisplay->GetNrOfColumns(); column++)
        {
            if (lcdDisplay->IsContentInvalidated(row, column))
            {
                OutputDebugString(L"_");
                size_t size;
                char text[] = { lcdDisplay->GetContentCharacter(row, column), '\0' };
                wchar_t wtext[2];
                mbstowcs_s(&size, wtext, text, 2);

                RECT charRectangle;
                SetRect(&charRectangle,
                    _lcdDisplayScreenRectangle.left + 5 + LCD_MARGIN + LCD_CHARACTER_WIDTH * column,
                    _lcdDisplayScreenRectangle.top + 5 + row * LCD_CHARACTER_HEIGHT,
                    _lcdDisplayScreenRectangle.left + 5 + LCD_MARGIN + LCD_CHARACTER_WIDTH * column + LCD_CHARACTER_WIDTH - 4,
                    _lcdDisplayScreenRectangle.top + 5 + row * LCD_CHARACTER_HEIGHT + LCD_CHARACTER_HEIGHT - 4);
                FillRect(hdc, &charRectangle, _darkGreenBrush);
                charRectangle.left = charRectangle.left + 1;
                charRectangle.top = charRectangle.top + 1;
                SetBkMode(hdc, TRANSPARENT);
                SetTextColor(hdc, RGB(0, 0, 0));
                DrawText(hdc, wtext, -1, &charRectangle, DT_SINGLELINE | DT_NOCLIP);
            }
        }
    }
    // Reset invalidation
    sound->ResetInvalidation();
    ledMatrix->ResetInvalidatedLeds();
    joystick->ResetInvalidation();
    lcdDisplay->ResetInvalidation();


    // clock_t clock_end_value = clock();
    // int a = (clock_end_value - clock_value) / CLOCKS_PER_SEC;
}

#endif // WIN32