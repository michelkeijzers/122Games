#include "Worms.h"
#include "MathUtils.h"
#include "MainUi.h"
#include "LedMatrix.h"
#include "Ui.h"
#include "PlayerUi.h"
#include "Joystick.h"
#include "ClassNames.h"
#include "HardwareProperties.h"
#include "FourDigitsLed.h"
#include HEADER_FILE(ARDUINO_CLASS)


static const uint16_t MILLIS_INTERVAL = 300; // 1 second

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
	DrawCursors();
	_nextPlayMillis = millis() + MILLIS_INTERVAL;
}


/* virtual */ void Worms::Play()
{
	if (millis() >= _nextPlayMillis)
	{
		_nextPlayMillis = millis() + MILLIS_INTERVAL;

		_rounds++;
		GetUi()->GetMainUi()->GetFourDigitsLed()->DisplayNumber(_rounds);
	
		if (GetUi()->IsInitialized())
		{
			if (GetUi()->GetPlayerUi()->GetJoyStick()->ReadButton())
			{
				ClearScreen();
			}

			switch (GetUi()->GetPlayerUi()->GetJoyStick()->GetDirection())
			{
			case JoyStick::EDirection::Up:
				_playerY = MathUtils::Trim(_playerY - 1, 0, MainUi::MAX_Y - 1);
				break;

			case JoyStick::EDirection::RightUp: // Fall through
			case JoyStick::EDirection::Right: // Fall through
			case JoyStick::EDirection::RightDown:
				_playerX = MathUtils::Trim(_playerX + 1, 0, MainUi::MAX_X - 1);
				break;

			case JoyStick::EDirection::Down:
				_playerY = MathUtils::Trim(_playerY + 1, 0, MainUi::MAX_Y - 1);
				break;

			case JoyStick::EDirection::LeftUp: // Fall through
			case JoyStick::EDirection::Left: // Fall through
			case JoyStick::EDirection::LeftDown:
				_playerX = MathUtils::Trim(_playerX - 1, 0, MainUi::MAX_X - 1);
				break;

			case JoyStick::EDirection::Center:
				// Do nothing
				break;

			default:
				throw "Illegal case";
				break;
			}

			DrawCursors();
		}
	}
}


void Worms::DrawCursors()
{
	MakeSurroundingLedsGreen();
	LedMatrix* ledMatrix = GetUi()->GetMainUi()->GetLedMatrix();
	ledMatrix->SetLed(_playerX, _playerY, 255, 0, 0);
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
		LedMatrix* ledMatrix = GetUi()->GetMainUi()->GetLedMatrix();
		uint8_t red = ledMatrix->GetLed(x, y)->red;
		if (red == 255)
		{
			ledMatrix->SetLed(x, y, 0, red, 0); // Move red to green
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


/* virtual */ void Worms::HandleDirection(JoyStick::EDirection direction)
{
	switch (direction)
	{
	case JoyStick::EDirection::Up:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 2048);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 0);
		break;

	case JoyStick::EDirection::RightUp:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 4095);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 0);
		break;

	case JoyStick::EDirection::Right:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 4095);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 2048);
		break;
	
	case JoyStick::EDirection::RightDown:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 4095);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 4095);
		break;

	case JoyStick::EDirection::Down:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 2048);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 4095);
		break;

	case JoyStick::EDirection::LeftDown:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 0);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 4095);
		break;

	case JoyStick::EDirection::Left:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 0);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 2048);
		break;

	case JoyStick::EDirection::LeftUp:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 0);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 0);
		break;

	case JoyStick::EDirection::Center:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 2048);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 2048);
		break;

	default:
		throw "Illegal case";
		break;
	}
}


/* virtual */ void Worms::HandleButton(Game::EButton button, bool pressed)
{
	InjectDigitalValue(HardwareProperties::JOYSTICK_BUTTON_PIN, true, !pressed);
}
