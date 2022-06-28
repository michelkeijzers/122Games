#include "Game.h"
#include "Joystick.h"
#include "HardwareProperties.h"


Game::Game()
  : _ui(nullptr),
	_joystick(nullptr),
	_ledMatrix(nullptr),
	_sound(nullptr),
	_fourDigitsLed(nullptr)
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


void Game::Start()
{
	_ledMatrix = GetUi()->GetMainUi()->GetLedMatrix();
	_joystick = GetUi()->GetPlayerUi()->GetJoystick();
	_sound = GetUi()->GetMainUi()->GetSound();
	_fourDigitsLed = GetUi()->GetMainUi()->GetFourDigitsLed();
}


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
		throw "Illegal case";
		break;
	}
}


/* virtual */ void Game::HandleButton(Game::EButton button, bool pressed)
{
	InjectDigitalValue(HardwareProperties::JOYSTICK_BUTTON_PIN, true, !pressed);
}
