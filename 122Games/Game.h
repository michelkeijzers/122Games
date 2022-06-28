#pragma once

#include "Canvas.h"
#include "Ui.h"
#include "Joystick.h"
#include "Sound.h"
#include "FourDigitsLed.h"

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
	Joystick* GetJoystick();
	LedMatrix* GetLedMatrix();
	Sound* GetSound();
	FourDigitsLed* GetFourDigitsLed();

	virtual void Start() = 0;
	virtual void Play() = 0;

	virtual void HandleButton(Game::EButton button, bool pressed);
	virtual void HandleDirection(Joystick::EDirection direction);
	
private:
	Ui* _ui;
	LedMatrix* _ledMatrix;
	Joystick* _joystick;
	Sound* _sound;
	FourDigitsLed* _fourDigitsLed;
};

