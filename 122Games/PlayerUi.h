#pragma once

#include "Button.h"
#include "LedSegments.h"

class PlayerUi
{
private:
	Button _buttonUp;
	Button _buttonRight;
	Button _buttonDown;
	Button _buttonLeft;
	Button _buttonSelect;
	LedSegments _ledSegments;
};