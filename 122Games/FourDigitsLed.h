#pragma once

// See https://en.wikipedia.org/wiki/Seven-segment_display


#ifdef WIN32
#include <cstdint>
#else
#include <stdint.h>
#endif // WIN32

#include "ClassNames.h"
#include HEADER_FILE(TM1637_DISPLAY_CLASS)


class FourDigitsLed
{
public:
	static const int NR_OF_DIGITS = 4;

	enum class ESpecialChar
	{
		Underscore = 0, // Low dash, Low line
		Dash = 1, // Hypen-minus, Minus, Negative, Hypen
		Overline = 2, // Overscore, Overbar, Macron
		Equals = 3, // Double hypen
		SuperScriptEquals = 4,
		TripleBar = 5, // Hamburger button, Identical To
		Degree = 6, // Superscript zero
		TwoVerticalLines = 7
		// Should not be a printable character, see implentation of GetCharacterSegments
	};

	FourDigitsLed();
	void Initialize(uint8_t pinClk, uint8_t pinDio, unsigned int bitDelay = 100);

	void DisplaySegments(const uint8_t segments[], uint8_t length, uint8_t position);
	uint8_t GetSegments(uint8_t position);
	void DisplayNumber(int16_t number);
	void DisplayDigit(uint8_t digit, uint8_t position);
	void DisplayText(const char* text);
	void DisplaySpecialChar(ESpecialChar specialChar, uint8_t pos);
	void DisplayChar(char character, uint8_t pos);
	void Clear();

	void ShowDisplay(bool on);
	void ShowColon(bool on);
	void SetBrightness(uint8_t brightness);
	uint8_t GetBrightness(uint8_t brightness);

	void Blink(uint16_t blinkSpeedInMs);
	void BlinkRefresh();

	TM1637_DISPLAY_CLASS* GetDisplay();

private:
	uint8_t GetCharacterSegments(char character);

	uint16_t _blinkSpeed;
	uint8_t _segments[NR_OF_DIGITS];
	bool _blinkStatusOn;
	int16_t _value;
	uint8_t _brightness;
	TM1637_DISPLAY_CLASS* _tm1637Display;
};

