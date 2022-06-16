#pragma once

#include "Button.h"
#include "LedSegments.h"

class PlayerUi
{
public:
	int GetScore();
	void SetScore(int score);

	LedSegments* GetLedSegments();

private:
	Button _buttonUp;
	Button _buttonRight;
	Button _buttonDown;
	Button _buttonLeft;
	Button _buttonSelect;
	LedSegments _ledSegments;
};