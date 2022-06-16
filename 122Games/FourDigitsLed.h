#pragma once

#include <cstdint>

#include "ClassNames.h"
#include HEADER_FILE(TM1637_DISPLAY_CLASS)


class FourDigitsLed
{
	
	enum ESpecialChar
	{
		// See wikipedia 7 segments
	};

	FourDigitsLed();
	void Initialize(uint8_t pinClk, uint8_t pinDio, unsigned int bitDelay = 100);


	void SetSegments(const uint8_t segments[], uint8_t length, uint8_t pos);
	void DisplayNumber(int16_t number);
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
	uint16_t _blinkSpeed;
	uint8_t _segments[4];
	bool _blinkStatusOn;
	int16_t _value;
	uint8_t _brightness;
	TM1637_DISPLAY_CLASS* _tm1637Display;
};

