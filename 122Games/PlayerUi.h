#pragma once

#include "Joystick.h"


class PlayerUi
{
public:
	PlayerUi();

	void Initialize();
	
	Joystick* GetJoyStick();

private:
	Joystick* _joyStick;
};