#include "AssertUtils.h"
#include "Worms.h"
#include "MathUtils.h"
#include "PlayerUi.h"
#include "ClassNames.h"
#include "HardwareProperties.h"
#include "Game.h"
#include "LedMatrix.h"
#include "FourDigitsLed.h"
#include "LcdDisplay.h"
#include "Sound.h"
#include HEADER_FILE(ARDUINO_CLASS)


static const uint16_t MILLIS_INTERVAL = 10;
static const uint16_t CURSOR_DELAY = 5; // Every x rounds


Worms::Worms()
  : Game(),
	_playerX(6),
	_playerY(6),
	_nextPlayMillis(0),
	_rounds(0)
{
}


/* virtual */ void Worms::Start()
{
	_nextPlayMillis = millis() + MILLIS_INTERVAL;
	Game::Start();
	DrawCursors();

	LcdDisplay* lcdDisplay = GetLcdDisplay();
	lcdDisplay->Clear();

	lcdDisplay->DisplayText(0, 2, "WORMS GAME");
	lcdDisplay->DisplayText(1, 0, "Created");
	lcdDisplay->DisplayText(2, 3, "by");
	lcdDisplay->DisplayText(3, 4, "Michel Keijzers");
}


bool _prevState = false;


/* virtual */ void Worms::Play()
{
	if (millis() >= _nextPlayMillis)
	{
		_nextPlayMillis = millis() + MILLIS_INTERVAL;

		_rounds++;

		Sound* sound = GetSound();
		if (millis() % 1000 < 300)
		{
			if (!sound->IsPlaying())
			{
				sound->Play(440);
			}
		}
		else
		{
			if (sound->IsPlaying())
			{
				sound->Stop();
			}
		}

		GetFourDigitsLed()->DisplayNumber(_rounds % 10000);
		GetLcdDisplay()->DisplayNumber(1, 10, _rounds % 10000, 4);
	
		if (GetUi()->IsInitialized())
		{
			bool buttonPressed = GetJoystick()->ReadButton();
			
			if (_prevState != buttonPressed)
			{
				_prevState = buttonPressed;
				Serial.print(buttonPressed);
			}

			if (buttonPressed)
			{
				ClearScreen();
			}

			if (_rounds % CURSOR_DELAY == 0)
			{
				switch (GetJoystick()->GetNonDiagonalDirection())
				{
				case Joystick::ENonDiagonalDirection::Up:
					_playerY = MathUtils::Trim(_playerY - 1, 0, MainUi::MAX_Y - 1);
					break;

				case Joystick::ENonDiagonalDirection::Right:
					_playerX = MathUtils::Trim(_playerX + 1, 0, MainUi::MAX_X - 1);
					break;

				case Joystick::ENonDiagonalDirection::Down:
					_playerY = MathUtils::Trim(_playerY + 1, 0, MainUi::MAX_Y - 1);
					break;

				case Joystick::ENonDiagonalDirection::Left:
					_playerX = MathUtils::Trim(_playerX - 1, 0, MainUi::MAX_X - 1);
					break;

				case Joystick::ENonDiagonalDirection::Center:
					// Do nothing
					break;

				default:
					AssertUtils::MyAssert(false);
					break;
				}

				DrawCursors();
			}
		}
	}
}


void Worms::DrawCursors()
{
	MakeSurroundingLedsGreen();
	GetLedMatrix()->SetLed(_playerX, _playerY, 255, 0, 0);
}


void Worms::MakeSurroundingLedsGreen()
{
	MakeLedGreen(_playerX - 1, _playerY);
	MakeLedGreen(_playerX + 1, _playerY);
	MakeLedGreen(_playerX, _playerY - 1);
	MakeLedGreen(_playerX, _playerY + 1);
}


void Worms::MakeLedGreen(uint8_t x, uint8_t y)
{
	if ((x >= 0) && (x < MainUi::MAX_X) && (y >= 0) && (y < MainUi::MAX_Y))
	{
		uint8_t red = GetLedMatrix()->GetLed(x, y)->red;
		if (red == 255)
		{
			GetLedMatrix()->SetLed(x, y, 0, red, 0); // Move red to green
		}
	}
}


void Worms::ClearScreen()
{
	LedMatrix* ledMatrix = GetUi()->GetMainUi()->GetLedMatrix();
	for (uint8_t x = 0; x < MainUi::MAX_X; x++)
	{
		for (uint8_t y = 0; y < MainUi::MAX_Y; y++)
		{
			ledMatrix->SetLed(x, y, 0, 0, 0);
		}
	}
}
