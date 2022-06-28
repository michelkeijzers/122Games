#pragma once

#include "Joystick.h"


class PlayerUi
{
public:
	PlayerUi();

	void Initialize();
	
	Joystick* GetJoystick();

private:
	Joystick* _joyStick;
};