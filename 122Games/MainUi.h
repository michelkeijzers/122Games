#pragma once

#include "LedMatrix.h"
#include "PlayerUi.h"


class MainUi
{
public:
	static const int MAX_X = 12;
	static const int MAX_Y = 12;
	static const int NR_OF_LEDS = MAX_X * MAX_Y;

	MainUi();
	void Initialize();

	LedMatrix* GetLedMatrix();

private:
	LedMatrix _ledMatrix;
};

