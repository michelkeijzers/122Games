#include "LedMatrix.h"

LedMatrix::LedMatrix()
{
	_ledStrip.Initialize(NR_OF_LEDS);
}


FastLedCRGB* LedMatrix::GetLed(int x, int y)
{
	int ledIndex = ToLedIndex(x, y);
	return _ledStrip.GetLed(ledIndex);
}


void LedMatrix::SetLed(int x, int y, int red, int green, int blue)
{
	int ledIndex = ToLedIndex(x, y);
	FastLedCRGB* rgb = _ledStrip.GetLed(ledIndex);
	rgb->red = red;
	rgb->green = green;
	rgb->blue = blue;
}


int LedMatrix::ToLedIndex(int x, int y)
{
	return y * LedMatrix::MAX_X + x;
}