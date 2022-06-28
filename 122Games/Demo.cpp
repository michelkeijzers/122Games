#include <stdlib.h>

#include "Demo.h"
#include "Canvas.h"
#include "MainUi.h"
#include "Ui.h"
#include "LedMatrix.h"
#include "Joystick.h"


Demo::Demo()
	: Game()
{
}


/* virtual */ void Demo::Start()
{
}


/* virtual */ void Demo::Play()
{
	int intensity = _light ? 255 : 20;

	for (int i = 0; i < 200; i++)
	{
		int x = rand() % MainUi::MAX_X;
		int y = rand() % MainUi::MAX_Y;

		//for (int x = 0; x < Canvas::MAX_X; x++)
		//{
		//	for (int y = 0; y < Canvas::MAX_Y; y++)
		//	{
		_ui->GetMainUi()->GetLedMatrix()->SetLed(x, y, rand() % 255, rand() % 255, rand() % 255);
	//	}
	//}
	}

	_light = !_light;
}


/* virtual */ void Demo::HandleButton(Game::EButton button, bool pressed)
{
}


/* virtual */ void Demo::HandleDirection(JoyStick::EDirection direction)
{
}