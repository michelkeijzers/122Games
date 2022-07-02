#include "AssertUtils.h"
#include "Game.h"
#include "Joystick.h"
#include "HardwareProperties.h"
#include "LcdDisplay.h"

Game::Game()
  : _ui(nullptr),
	_joystick(nullptr),
	_ledMatrix(nullptr),
	_sound(nullptr),
	_fourDigitsLed(nullptr),
	_lcdDisplay(nullptr)
{
}

void Game::Initialize(Ui* ui)
{
	//_ui->Initialize();
	_ui = ui;
}


Ui* Game::GetUi()
{
	return _ui;
}


Joystick* Game::GetJoystick()
{
	return _joystick;
}


LedMatrix* Game::GetLedMatrix()
{
	return _ledMatrix;
}


Sound* Game::GetSound()
{
	return _sound;
}


FourDigitsLed* Game::GetFourDigitsLed()
{
	return _fourDigitsLed;
}


LcdDisplay* Game::GetLcdDisplay()
{
	return _lcdDisplay;
}


void Game::Start()
{
	Ui* ui = GetUi();
	MainUi* mainUi = ui->GetMainUi();
	_joystick = ui->GetPlayerUi()->GetJoystick();
	_ledMatrix = mainUi->GetLedMatrix();
	_sound = mainUi->GetSound();
	_fourDigitsLed = mainUi->GetFourDigitsLed();
	_lcdDisplay = mainUi->GetLcdDisplay();

	_lcdDisplay->Clear();
}


#ifdef WIN32

/* virtual */ void Game::HandleDirection(Joystick::EDirection direction)
{
	switch (direction)
	{
	case Joystick::EDirection::Up:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 2048);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 0);
		break;

	case Joystick::EDirection::RightUp:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 4095);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 0);
		break;

	case Joystick::EDirection::Right:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 4095);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 2048);
		break;

	case Joystick::EDirection::RightDown:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 4095);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 4095);
		break;

	case Joystick::EDirection::Down:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 2048);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 4095);
		break;

	case Joystick::EDirection::LeftDown:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 0);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 4095);
		break;

	case Joystick::EDirection::Left:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 0);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 2048);
		break;

	case Joystick::EDirection::LeftUp:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 0);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 0);
		break;

	case Joystick::EDirection::Center:
		InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 2048);
		InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 2048);
		break;

	default:
		AssertUtils::MyAssert(false);
		break;
	}
}

#endif // WIN32

#ifdef WIN32

/* virtual */ void Game::HandleButton(Game::EButton button, bool pressed)
{
	InjectDigitalValue(HardwareProperties::JOYSTICK_BUTTON_PIN, true, !pressed);
}

#endif // WIN32
