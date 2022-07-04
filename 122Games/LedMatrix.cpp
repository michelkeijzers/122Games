#include "LedMatrix.h"
#include "AssertUtils.h"


LedMatrix::LedMatrix()
{
	ResetInvalidatedLeds();
}


void LedMatrix::Initialize(uint8_t nrOfColumns, uint8_t nrOfRows)
{
	AssertUtils::MyAssert(nrOfColumns * nrOfRows <= MAX_LEDS);

	_nrOfColumns = nrOfColumns;
	_nrOfRows = nrOfRows;
	_ledStrip.Initialize(nrOfColumns * nrOfRows);
}


uint8_t LedMatrix::GetDataPin()
{
	return _ledStrip.GetDataPin();
}


uint8_t LedMatrix::GetNrOfColumns()
{
	return _nrOfColumns;
}


uint8_t LedMatrix::GetNrOfRows()
{
	return _nrOfRows;
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
	
	_invalidateBits[ledIndex / 8] |= (1 << ledIndex % 8);
}


void LedMatrix::Clear()
{
	for (uint8_t y = 0; y < _nrOfRows; y++)
	{
		for (uint8_t x = 0; x < _nrOfColumns; x++)
		{
			SetLed(x, y, 0, 0, 0);
		}
	}
}


int LedMatrix::ToLedIndex(int x, int y)
{
	return y * _nrOfColumns + x;
}


bool LedMatrix::IsLedInvalidated(int x, int y)
{
	int ledIndex = ToLedIndex(x, y);
	return (_invalidateBits[ledIndex / 8]) & (1 << ledIndex % 8) ? true : false;
}


void LedMatrix::ResetInvalidatedLeds()
{
	for (int index = 0; index < (_nrOfColumns * _nrOfRows + 7) / 8; index++)
	{
		_invalidateBits[index] = 0;
	}
}


void LedMatrix::Refresh()
{
}