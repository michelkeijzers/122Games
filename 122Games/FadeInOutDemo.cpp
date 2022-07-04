#include <stdlib.h>

#include "FadeInOutDemo.h"
#include "MainUi.h"
#include "Ui.h"
#include "LedMatrix.h"
#include "FourDigitsLed.h"
#include "Sound.h"
#include "LcdDisplay.h"


static const uint16_t MILLIS_INTERVAL = 10;


FadeInOutDemo::FadeInOutDemo()
	: Game(),
	_light(0),
	_iteration(0),
	_nextPlayMillis(0)
{
}


/* virtual */ void FadeInOutDemo::Start()
{
	Game::Start();
	_nextPlayMillis = millis() + MILLIS_INTERVAL;

	GetLcdDisplay()->DisplayCenteredTexts("FADE IN/OUT", "DEMO");
}


/* virtual */ void FadeInOutDemo::Play()
{
	_light = (_light + 1) % 256;

	for (int x = 0; x < MainUi::MAX_X; x++)
	{
		for (int y = 0; y < MainUi::MAX_Y; y++)
		{
			GetLedMatrix()->SetLed(x, y, _light, _light, _light);
		}
	}

	_iteration = (_iteration + 1) % 10000;
	if (_iteration % 1000 == 100)
	{
		GetSound()->Play(500);
	}
	else if (_iteration % 1000 == 500)
	{
		GetSound()->Stop();
	}

	GetFourDigitsLed()->DisplayNumber(_iteration);
}
