#pragma once

#include "LedStrip.h"
#include "Rgb.h"


class LedMatrix
{
public:
	LedMatrix();

	static const int MAX_X = 12;
	static const int MAX_Y = 12;
	static const int NR_OF_LEDS = MAX_X * MAX_Y;

	FastLedCRGB* GetLed(int x, int y);
	void SetLed(int x, int y, int red, int green, int blue);

	int ToLedIndex(int x, int y);

private:
	LedStrip _ledStrip;
};

