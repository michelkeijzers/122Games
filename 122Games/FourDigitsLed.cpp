#include "FourDigitsLed.h"
#include "AssertUtils.h"

FourDigitsLed::FourDigitsLed()
	: _blinkSpeed(0),
	  _blinkStatusOn(false),
	  _brightness(0),
	  _segments(),
	  _value(0)
{
}


void FourDigitsLed::Initialize(uint8_t pinClk, uint8_t pinDio, unsigned int bitDelay /* = 100 */ )
{
	if (_tm1637Display != nullptr)
	{
		delete _tm1637Display;
	}

	_tm1637Display = new TM1637DisplayStub(pinClk, pinDio, bitDelay);
} 


void FourDigitsLed::SetSegments(const uint8_t segments[], uint8_t length, uint8_t pos)
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


void FourDigitsLed::DisplayNumber(int16_t number)
{
	_tm1637Display->showNumberDec(number, false, 4, 0);
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


void FourDigitsLed::BlinkRefresh()
{
	// TODO
}


TM1637_DISPLAY_CLASS* FourDigitsLed::GetDisplay()
{
	return _tm1637Display;
}
