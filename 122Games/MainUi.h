#pragma once

#include "HardwareProperties.h"

class LcdDisplay;
class LedMatrix;
class FourDigitsLed;
class Sound;


class MainUi
{
public:
	static const int MAX_X = HardwareProperties::NR_OF_LEDS_X;
	static const int MAX_Y = HardwareProperties::NR_OF_LEDS_Y;
	static const int NR_OF_LEDS = MAX_X * MAX_Y;

	MainUi();
	~MainUi();
	void Initialize();
	
	LcdDisplay* GetLcdDisplay();
	LedMatrix* GetLedMatrix();
	FourDigitsLed* GetFourDigitsLed();
	Sound* GetSound();

private:
	LcdDisplay* _lcdDisplay;
	LedMatrix *_ledMatrix;
	FourDigitsLed *_fourDigitsLed;
	Sound* _sound;
};
