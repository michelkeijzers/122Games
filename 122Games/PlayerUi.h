#pragma once

#include "Joystick.h"


class PlayerUi
{
public:
	PlayerUi();

	void Initialize();
	
	Joystick* GetJoystick();

	void Refresh();

private:
	Joystick* _joyStick;
};