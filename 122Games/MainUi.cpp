#include "MainUi.h"
#include "LcdDisplay.h"
#include "FourDigitsLed.h"
#include "LedMatrix.h"
#include "Button.h"
#include "Sound.h"
#include "HardwareProperties.h"


MainUi::MainUi()
	: _lcdDisplay(nullptr),
	_fourDigitsLed(nullptr),
	_ledMatrix(nullptr),
	_startStopButton(nullptr),
	_selectButton(nullptr),
	_leftButton(nullptr),
	_rightButton(nullptr),
	_sound(nullptr)
{
}


MainUi::~MainUi()
{
	if (_lcdDisplay != nullptr)
	{
		delete _lcdDisplay;
	}
	if (_fourDigitsLed != nullptr)
	{
		delete _fourDigitsLed;
	}

	if (_ledMatrix != nullptr)
	{
		delete _ledMatrix;
	}

	if (_startStopButton != nullptr)
	{
		delete _startStopButton;
	}

	if (_selectButton != nullptr)
	{
		delete _selectButton;
	}

	if (_leftButton != nullptr)
	{
		delete _leftButton;
	}

	if (_rightButton != nullptr)
	{
		delete _rightButton;
	}

	if (_sound != nullptr)
	{
		delete _sound;
	}
}


void MainUi::Initialize()
{
	if (_lcdDisplay == nullptr)
	{
		_lcdDisplay = new LcdDisplay(
			HardwareProperties::LCD_I2C_ADDRESS,
			HardwareProperties::LCD_NR_OF_ROW,
			HardwareProperties::LCD_NR_OF_COLUMNS);
	}

	_lcdDisplay->Initialize();

	if (_fourDigitsLed == nullptr)
	{
		_fourDigitsLed = new FourDigitsLed();
	}

	_fourDigitsLed->Initialize(
		HardwareProperties::FOUR_DIGITS_LED_CLOCK_PIN,
		HardwareProperties::FOUR_DIGITS_LED_DATA_PIN);

	if (_ledMatrix == nullptr)
	{
		_ledMatrix = new LedMatrix();
	}

	_ledMatrix->Initialize(
		HardwareProperties::LED_STRIP_NR_OF_COLUMNS,
		HardwareProperties::LED_STRIP_NR_OF_ROWS);

	if (_startStopButton == nullptr)
	{
		_startStopButton = new Button();
	}

	_startStopButton->Initialize(HardwareProperties::BUTTON_START_STOP, INPUT_PULLUP, 50);

	if (_selectButton == nullptr)
	{
		_selectButton = new Button();
	}

	_selectButton->Initialize(HardwareProperties::BUTTON_SELECT, INPUT_PULLUP, 50);

	if (_leftButton == nullptr)
	{
		_leftButton = new Button();
	}

	_leftButton->Initialize(HardwareProperties::BUTTON_LEFT, INPUT_PULLUP, 50);

	if (_rightButton == nullptr)
	{
		_rightButton = new Button();
	}

	_rightButton->Initialize(HardwareProperties::BUTTON_RIGHT, INPUT_PULLUP, 50);


	if (_sound == nullptr)
	{
		_sound = new Sound();
	}

	_sound->Initialize(HardwareProperties::SPEAKER_PIN);
}


LcdDisplay* MainUi::GetLcdDisplay()
{
	return _lcdDisplay;
}


FourDigitsLed* MainUi::GetFourDigitsLed()
{
	return _fourDigitsLed;
}


LedMatrix* MainUi::GetLedMatrix()
{
	return _ledMatrix;
}


Button* MainUi::GetStartStopButton()
{
	return _startStopButton;
}


Button* MainUi::GetSelectButton()
{
	return _selectButton;
}


Button* MainUi::GetLeftButton()
{
	return _leftButton;
}


Button* MainUi::GetRightButton()
{
	return _rightButton;
}


Sound* MainUi::GetSound()
{ 
	return _sound;
}


void MainUi::ProcessButtons()
{

}