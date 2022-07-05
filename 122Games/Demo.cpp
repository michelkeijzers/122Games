#include <stdlib.h>

#include "Demo.h"
#include "MainUi.h"
#include "Ui.h"
#include "LedMatrix.h"
#include "Joystick.h"
#include "LcdDisplay.h"


static const uint16_t MILLIS_INTERVAL = 10;


Demo::Demo()
	: Game(),
	_nextPlayMillis(0)
{
}


/* virtual */ void Demo::Start()
{
	Game::Start();
	_nextPlayMillis = millis() + MILLIS_INTERVAL;
	GetLcdDisplay()->DisplayCenteredTexts("GRAPHIC DEMO", "Use Joystick");
}


/* virtual */ void Demo::Play()
{
	int intensity = _light ? 255 : 20;

	for (int i = 0; i < 200; i++)
	{
		int x = rand() % MainUi::MAX_X;
		int y = rand() % MainUi::MAX_Y;

		GetLedMatrix()->SetLed(x, y, rand() % 255, rand() % 255, rand() % 255);
	}

	_light = !_light;
}
