#pragma once

#include "Joystick.h"


class PlayerUi
{
public:
	PlayerUi();

	void Initialize();
	
	JoyStick* GetJoyStick();

private:
	JoyStick* _joyStick;
};