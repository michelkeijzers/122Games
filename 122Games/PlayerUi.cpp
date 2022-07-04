#include "PlayerUi.h"
#include "Joystick.h"
#include "HardwareProperties.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


PlayerUi::PlayerUi()
	: _joyStick(nullptr)
{
}


void PlayerUi::Initialize()
{
	if (_joyStick != nullptr)
	{
		delete _joyStick;
	}

	_joyStick = new Joystick();

#ifdef WIN32
	InjectAnalogValue(HardwareProperties::JOYSTICK_HORIZONTAL_PIN, true, 2048);
	InjectAnalogValue(HardwareProperties::JOYSTICK_VERTICAL_PIN, true, 2048);
#endif

	_joyStick->Initialize(HardwareProperties::JOYSTICK_BUTTON_PIN, HardwareProperties::JOYSTICK_HORIZONTAL_PIN,
		HardwareProperties::JOYSTICK_VERTICAL_PIN, 40);
}


Joystick* PlayerUi::GetJoystick()
{
	return _joyStick;
}


void PlayerUi::Refresh()
{

}