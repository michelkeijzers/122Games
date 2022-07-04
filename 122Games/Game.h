#pragma once

#include "Ui.h"

class Joystick;
class Sound;
class FourDigitsLed;
class LcdDisplay;


class Game
{
public:
	Game();

	void Initialize(Ui* ui);
	Ui* GetUi();
	Joystick* GetJoystick();
	LedMatrix* GetLedMatrix();
	Sound* GetSound();
	FourDigitsLed* GetFourDigitsLed();
	LcdDisplay* GetLcdDisplay();

	virtual void Start() = 0;
	virtual void Play() = 0;

#ifdef WIN32
	virtual void HandleButton(bool pressed);
	virtual void HandleDirection(Joystick::EDirection direction);
#endif // WIN32
	
private:
	Ui* _ui;
	LedMatrix* _ledMatrix;
	Joystick* _joystick;
	Sound* _sound;
	FourDigitsLed* _fourDigitsLed;
	LcdDisplay* _lcdDisplay;
};

