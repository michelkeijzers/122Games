#pragma once

#include "LedStrip.h"
#include "Rgb.h"


class LedMatrix
{
public:
	LedMatrix();

	void Initialize(uint8_t nrOfColumns, uint8_t nrOfRows);
	
	uint8_t GetNrOfColumns();
	uint8_t GetNrOfRows();

	uint8_t GetDataPin();

	FastLedCRGB* GetLed(int x, int y);
	void SetLed(int x, int y, int red, int green, int blue);
	void Clear();

	int ToLedIndex(int x, int y);

	bool IsLedInvalidated(int x, int y);
	void ResetInvalidatedLeds();

	void Refresh();

private:
	static const int MAX_LEDS = 60 * 5; // 5 meters of 60 leds/m

	uint8_t _nrOfColumns;
	uint8_t _nrOfRows;

	LedStrip _ledStrip;

	uint8_t _invalidateBits[MAX_LEDS / 8];
};

