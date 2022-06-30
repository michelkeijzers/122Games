#ifdef WIN32

#include "MAX7219Stub.h"
#include "AssertUtils.h"
#include <string.h>
#include <stdlib.h>


// See https ://github.com/JemRF/max7219
//   a  --
//   f |  |   b
//   g  --
//   e |  |   c
//   d  -- o  dp
class MAX7219_Font
{
public:
	static uint8_t GetSegments(char character)
	{
		uint8_t segments = 0;

		switch (character)
		{
		case 'A': segments = 0b1110111; break;
		case 'B': segments = 0b1111111; break;
		case 'C': segments = 0b1001110; break;
		case 'D': segments = 0b1111110; break;
		case 'E': segments = 0b1001111; break;
		case 'F': segments = 0b1000111; break;
		case 'G': segments = 0b1011110; break;
		case 'H': segments = 0b0110111; break;
		case 'I': segments = 0b0110000; break;
		case 'J': segments = 0b0111100; break;
		case 'L': segments = 0b0001110; break;
		case 'N': segments = 0b1110110; break;
		case 'O': segments = 0b1111110; break;
		case 'P': segments = 0b1100111; break;
		case 'R': segments = 0b0000101; break;
		case 'S': segments = 0b1011011; break;
		case 'T': segments = 0b0001111; break;
		case 'U': segments = 0b0111110; break;
		case 'Y': segments = 0b0100111; break;
		case '[': segments = 0b1001110; break;
		case ']': segments = 0b1111000; break;
		case '_': segments = 0b0001000; break;
		case 'a': segments = 0b1110111; break;
		case 'b': segments = 0b0011111; break;
		case 'c': segments = 0b0001101; break;
		case 'd': segments = 0b0111101; break;
		case 'e': segments = 0b1001111; break;
		case 'f': segments = 0b1000111; break;
		case 'g': segments = 0b1011110; break;
		case 'h': segments = 0b0010111; break;
		case 'i': segments = 0b0010000; break;
		case 'j': segments = 0b0111100; break;
		case 'l': segments = 0b0001110; break;
		case 'n': segments = 0b0010101; break;
		case 'o': segments = 0b1111110; break;
		case 'p': segments = 0b1100111; break;
		case 'r': segments = 0b0000101; break;
		case 's': segments = 0b1011011; break;
		case 't': segments = 0b0001111; break;
		case 'u': segments = 0b0011100; break;
		case 'y': segments = 0b0100111; break;
		case '-': segments = 0b0000001; break;
		case ' ': segments = 0b0000000; break;
		case '0': segments = 0b1111110; break;
		case '1': segments = 0b0110000; break;
		case '2': segments = 0b1101101; break;
		case '3': segments = 0b1111001; break;
		case '4': segments = 0b0110011; break;
		case '5': segments = 0b1011011; break;
		case '6': segments = 0b1011111; break;
		case '7': segments = 0b1110000; break;
		case '8': segments = 0b1111111; break;
		case '9': segments = 0b1111011; break;
		case   0: segments = 0b0000000; break;
		default: AssertUtils::MyAssert(false);
		}

		return segments;
	}
};


MAX7219Stub::MAX7219Stub()
	: _segments(),
	  _characters(),
	  _dps(),
	  _brightness(0)
{
}


void MAX7219Stub::Begin(void)
{
}


void MAX7219Stub::DisplayChar(uint8_t digit, char character, unsigned int dp)
{
	_segments[digit] = MAX7219_Font::GetSegments(character);
	_characters[digit] = character;
	_dps[digit] = dp;
}


void MAX7219Stub::DisplayText(char* text, bool rightJustify)
{
	AssertUtils::MyAssert(strlen(text) <= MAX_DIGITS);

	uint8_t textLength = (uint8_t) strlen(text);

	for (uint8_t segmentIndex = 0; segmentIndex < MAX_DIGITS; segmentIndex++)
	{
		char character = segmentIndex >= textLength ? ' ' : text[segmentIndex];
		DisplayChar(rightJustify ? MAX_DIGITS - 1 - segmentIndex : segmentIndex, character, false);
	}
}


char MAX7219Stub::STUB_GetDisplayedChar(uint8_t digit)
{
	AssertUtils::MyAssert(digit < MAX_DIGITS);
#pragma warning(push)
// Reading invalid data from this->_characters: the readable size is 8 bytes, but digit bytes may be read
#pragma warning(disable:6385) 
	return _characters[digit];
#pragma warning(pop)
}

char* MAX7219Stub::STUB_GetDisplayedText()
{
	return _characters;
}


uint32_t MAX7219Stub::STUB_GetDisplayedValue()
{
	char buffer[MAX_DIGITS + 1];
	strncpy_s(buffer, _characters, MAX_DIGITS);
	buffer[MAX_DIGITS] = '\0';
	return atol(buffer);
}


//void MAX7219Stub::MAX7219_Write(volatile byte opcode, volatile byte data);

//void MAX7219Stub::clearDisplay();

void MAX7219Stub::Clear(void)
{
	DisplayText((char*)"", false);
}

void MAX7219Stub::MAX7219_ShutdownStart(void)
{

}


void MAX7219Stub::MAX7219_ShutdownStop(void)
{

}


//void MAX7219Stub::MAX7219_DisplayTestStart(void);
//void MAX7219Stub::MAX7219_DisplayTestStop(void);

//unsigned char MAX7219Stub::MAX7219_LookupCode(char character, unsigned int dp);

void MAX7219Stub::MAX7219_SetBrightness(uint8_t brightness)
{
	_brightness = brightness;
}


uint8_t MAX7219Stub::STUB_MAX7219_GetBrightness()
{
	return _brightness;
}


uint8_t MAX7219Stub::STUB_GetSegments(uint8_t digit)
{
	AssertUtils::MyAssert(digit < MAX_DIGITS);

	
#pragma warning(push)
	// Reading invalid data from this->_characters: the readable size is 8 bytes, but digit bytes may be read
#pragma warning(disable:6385) 
	return _segments[digit];
#pragma warning(pop)

}

#endif // WIN32
