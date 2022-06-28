#pragma once

#include "Canvas.h"
#include "Ui.h"
#include "Joystick.h"


class Game
{
public:
	Game();

	void Initialize(Ui* ui);
	
	enum class EButton
	{
		Up,
		Right,
		Down,
		Left,
		Select
	};

	Ui* GetUi();

	virtual void Start() = 0;
	virtual void Play() = 0;

	virtual void HandleButton(Game::EButton button, bool pressed) = 0;

	virtual void HandleDirection(JoyStick::EDirection direction) = 0;
	
protected:
	Ui* _ui;
};

