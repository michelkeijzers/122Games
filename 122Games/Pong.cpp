#include <stdlib.h>

#include "Pong.h"
#include "MainUi.h"
#include "Ui.h"
#include "LedMatrix.h"
#include "Joystick.h"
#include "LcdDisplay.h"
#include "FourDigitsLed.h"


static const uint16_t MILLIS_INTERVAL = 10;
static const uint16_t COUNT_DOWN_INTERVAL = 500;

Pong::Pong()
	: Game(),
	_nextPlayMillis(0),
	_ballLocationX(0),
	_ballLocationY(0),
	_ballSpeedX(0),
	_ballSpeedY(0),
	_paddleTop(0),
	_paddleLength(0),
	_score(0),
	_countDown(0),
	_settingBallServeSpeed(EBallServeSpeed::Normal),
	_settingScoreToWin(EScoreToWin::Score10)
{
}


/* virtual */ void Pong::Start()
{
	Game::Start();
	GetLcdDisplay()->DisplayCenteredTexts("PONG", "Get Ready ...");
	_countDown = 3;
	_nextPlayMillis = millis() + COUNT_DOWN_INTERVAL;
	GetFourDigitsLed()->DisplayNumber(_countDown);
}


/* virtual */ void Pong::Play()
{
	if ((_countDown > 0) && (millis() >= _nextPlayMillis))
	{
		_countDown--;
		GetFourDigitsLed()->DisplayNumber(_countDown);
		_nextPlayMillis = millis() + COUNT_DOWN_INTERVAL;

		if (_countDown == 0)
		{
			_nextPlayMillis = millis() + MILLIS_INTERVAL;
		}
	}
	else
	{
		if (millis() >= _nextPlayMillis)
		{
			MovePaddle();
			MoveBall();
			//GetLedMatrix()->SetLed(x, y, rand() % 255, rand() % 255, rand() % 255);
			_nextPlayMillis = millis() + MILLIS_INTERVAL;
		}
	}
}


void Pong::MovePaddle()
{

}


void Pong::MoveBall()
{

}

