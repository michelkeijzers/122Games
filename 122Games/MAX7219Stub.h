#ifdef WIN32

// Based on max7219, Jonathan Evans
// Changes:
//   in max7219.cpp, change:
//     static void MAX7219::MAX7219_ShutdownStop (void)
//   into
//     /* static */ void MAX7219::MAX7219_ShutdownStop (void)

#pragma once

#include <cstdint>

#include "LedSegments.h"

class MAX7219Stub
{
public:
	MAX7219Stub();

	void Begin(void);

	// Between 35..44 => converted to 48..57 + dp 
	// (dot, see https://github.com/JemRF/max7219/blob/master/max7219.cpp, line 100-102)
	void DisplayChar(uint8_t digit, char character, unsigned int dp);
	//void DisplayChar(uint8_t digit, uint8_t asciiValue, bool dp);
	void DisplayText(char* text, bool rightJustify);

	char STUB_GetDisplayedChar(uint8_t digit);
	char* STUB_GetDisplayedText();
	uint32_t STUB_GetDisplayedValue();

	// void MAX7219_Write(volatile uint8_t opcode, volatile uint8_t data);

	// void clearDisplay();
	void Clear(void);

	void MAX7219_ShutdownStart(void);
	void MAX7219_ShutdownStop(void);
 
	// void MAX7219_DisplayTestStart(void);
	// void MAX7219_DisplayTestStop(void);

	// unsigned char MAX7219_LookupCode(char character, unsigned int dp);

	void MAX7219_SetBrightness(uint8_t brightness);
	uint8_t STUB_MAX7219_GetBrightness();

	uint8_t STUB_GetSegments(uint8_t digit);

private:
	static const int MAX_DIGITS = 8;

	uint8_t _segments[MAX_DIGITS];
	char _characters[MAX_DIGITS];
	bool _dps[MAX_DIGITS];
	uint8_t _brightness;
};


#endif // WIN32
