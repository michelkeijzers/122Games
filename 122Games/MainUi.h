#pragma once

#include "HardwareProperties.h"
#include "Menu.h"

class LcdDisplay;
class LedMatrix;
class FourDigitsLed;
class Button;
class Sound;



class MainUi
{
public:
	static const int MAX_X = HardwareProperties::NR_OF_LEDS_X;
	static const int MAX_Y = HardwareProperties::NR_OF_LEDS_Y;
	static const int NR_OF_LEDS = MAX_X * MAX_Y;

	MainUi();
	~MainUi();
	void Initialize();

	void ProcessButtons();
	void ProcessButton(Button* button, Menu::ECommand command);
	
	LcdDisplay* GetLcdDisplay();
	LedMatrix* GetLedMatrix();
	FourDigitsLed* GetFourDigitsLed();
	Button* GetSelectButton();
	Button* GetBackButton();
	Button* GetLeftButton();
	Button* GetRightButton();
	Sound* GetSound();

	void Refresh();

private:
	LcdDisplay* _lcdDisplay;
	LedMatrix *_ledMatrix;
	FourDigitsLed *_fourDigitsLed;
	Button* _selectButton;
	Button* _backButton;
	Button* _leftButton;
	Button* _rightButton;
	Sound* _sound;
	Menu _menu;
};
