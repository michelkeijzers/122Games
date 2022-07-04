#include "FourDigitsLed.h"
#include "AssertUtils.h"

FourDigitsLed::FourDigitsLed()
	: _blinkSpeed(0),
	  _blinkStatusOn(false),
	  _brightness(0),
	  _value(0),
	  _tm1637Display(nullptr)
{
	for (uint8_t digit = 0; digit < NR_OF_DIGITS; digit++)
	{
		_segments[digit] = 0;
	}
}


void FourDigitsLed::Initialize(uint8_t pinClk, uint8_t pinDio, unsigned int bitDelay /* = 100 */ )
{
	if (_tm1637Display != nullptr)
	{
		delete _tm1637Display;
	}

	_tm1637Display = new TM1637_DISPLAY_CLASS(pinClk, pinDio, bitDelay);
} 


void FourDigitsLed::DisplaySegments(const uint8_t segments[], uint8_t length, uint8_t pos)
{
	AssertUtils::MyAssert(length > 0);
	AssertUtils::MyAssert(length <= 4);
	AssertUtils::MyAssert(pos >= 0);
	AssertUtils::MyAssert(pos < 4);
	AssertUtils::MyAssert(length + pos <= 4);

	_tm1637Display->setSegments(segments, length, pos);

	for (uint8_t digit = pos; digit < pos + length; digit++)
	{
		_segments[digit] = segments[digit - pos];
	}
}


uint8_t FourDigitsLed::GetSegments(uint8_t position)
{
	AssertUtils::MyAssert(position < NR_OF_DIGITS);

	return _segments[position];
}


/// <summary>
/// Right justify, only 0..9999 implemented
/// </summary>
/// <param name="number"></param>
void FourDigitsLed::DisplayNumber(int16_t number)
{
	AssertUtils::MyAssert(number >= 0); // Not implemented yet
	AssertUtils::MyAssert(number < 10000);

	Clear();
	DisplayDigit(number % 10, 3);
	number /= 10;

	if (number > 0)
	{
		DisplayDigit(number % 10, 2);
	}
	number /= 10;

	if (number > 0)
	{
		DisplayDigit(number % 10, 1);
	}
	number /= 10;

	if (number > 0)
	{
		DisplayDigit((uint8_t) number, 0);
	}

	//_tm1637Display->showNumberDec(number, false, 4, 0);
}


void FourDigitsLed::DisplayDigit(uint8_t digit, uint8_t position)
{
	AssertUtils::MyAssert(digit < 10);
	uint8_t segments = GetCharacterSegments((char)((uint8_t)('0') + digit));
	DisplaySegments(&segments, 1, position);

}


void FourDigitsLed::DisplayText(const char* text) // TODO: Justify ?
{
	//TODO
}

void FourDigitsLed::DisplaySpecialChar(ESpecialChar specialChar, uint8_t pos)
{
	//TODO
}

void FourDigitsLed::DisplayChar(char character, uint8_t pos)
{
	//TODO
}

void FourDigitsLed::Clear()
{
	for (int position = 0; position < NR_OF_DIGITS; position++)
	{
		_segments[position] = 0;
	}

	_tm1637Display->clear();
}


void FourDigitsLed::ShowDisplay(bool on)
{
	_tm1637Display->setBrightness(_brightness, on);
}


void FourDigitsLed::ShowColon(bool on)
{
	// TODO _tm1637Display->showDots(1)
}


void FourDigitsLed::SetBrightness(uint8_t brightness)
{
	_tm1637Display->setBrightness(_brightness, true);
}


uint8_t FourDigitsLed::GetBrightness(uint8_t brightness)
{
	return _brightness;
}


void FourDigitsLed::Blink(uint16_t blinkSpeedInMs)
{
	// TODO
}


void FourDigitsLed::Refresh()
{
	// TODO
}


TM1637_DISPLAY_CLASS* FourDigitsLed::GetDisplay()
{
	return _tm1637Display;
}


// See http://www.uize.com/examples/seven-segment-display.html and wikipedia
uint8_t FourDigitsLed::GetCharacterSegments(char character)
{
	uint8_t segments = 0;

	switch (character)
	{
	case '0': segments = 0x7E; break;
	case '1': segments = 0x30; break;
	case '2': segments = 0x6D; break;
	case '3': segments = 0x79; break;
	case '4': segments = 0x33; break;
	case '5': segments = 0x5B; break;
	case '6': segments = 0x5F; break;
	case '7': segments = 0x70; break;
	case '8': segments = 0x7F; break;
	case '9': segments = 0x7B; break;
	case 'A': segments = 0x77; break;
	case 'b': segments = 0x1F; break;
	case 'C': segments = 0x4E; break;
	case 'c': segments = 0x0D; break;
	case 'd': segments = 0x3D; break;
	case 'E': segments = 0x4F; break;
	case 'F': segments = 0x47; break;
	case 'G': segments = 0x5E; break;
	case 'H': segments = 0x37; break;
	case 'h': segments = 0x17; break;
	case 'I': segments = 0x06; break;
	case 'i': segments = 0x04; break;
	case 'j': segments = 0x18; break;
	case 'J': segments = 0x3C; break;
	case 'L': segments = 0x0E; break;
	case 'l': segments = 0x30; break;
	case 'N': segments = 0x76; break;
	case 'n': segments = 0x15; break;
	case 'O': segments = 0x7E; break;
	case 'o': segments = 0x1D; break;
	case 'P': segments = 0x67; break;
	case 'q': segments = 0x73; break;
	case 'r': segments = 0x05; break;
	case 't': segments = 0x0F; break;
	case 'S': segments = 0x5B; break;
	case 'U': segments = 0x3E; break;
	case 'u': segments = 0x1C; break;
	case 'y': segments = 0x3B; break;
	case 'Z': segments = 0x6D; break;
	case ' ': segments = 0x00; break;
	case '(': segments = 0x3E; break;
	case '{': segments = 0x3E; break;
	case ')': segments = 0x78; break;
	case '}': segments = 0x78; break;
	case '/': segments = 0x25; break;
	case '\\': segments = 0x13; break;
	case (char)ESpecialChar::Underscore: segments = 0x08; break;
	case (char)ESpecialChar::Dash: segments = 0x01; break;
	case (char)ESpecialChar::Overline: segments = 0x40; break;
	case (char)ESpecialChar::Equals: segments = 0x09; break;
	case (char)ESpecialChar::SuperScriptEquals: segments = 0x41; break;
	case (char)ESpecialChar::TripleBar: segments = 0x49; break;
	case (char)ESpecialChar::Degree: segments = 0x63; break;
	case (char)ESpecialChar::TwoVerticalLines: segments = 0x36; break;
	default: break;
	}

	return segments;
}