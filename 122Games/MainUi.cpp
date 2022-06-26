#include "MainUi.h"
#include "FourDigitsLed.h"
#include "LedMatrix.h"
#include "HardwareProperties.h"
#include "Sound.h"


MainUi::MainUi()
  : _fourDigitsLed(nullptr),
	_ledMatrix(nullptr),
	_sound(nullptr)
{
}


MainUi::~MainUi()
{
	if (_fourDigitsLed != nullptr)
	{
		delete _fourDigitsLed;
	}

	if (_ledMatrix != nullptr)
	{
		delete _ledMatrix;
	}

	if (_sound != nullptr)
	{
		delete _sound;
	}
}


void MainUi::Initialize()
{
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

	if (_sound == nullptr)
	{
		_sound = new Sound();
	}

	_sound->Initialize(HardwareProperties::SPEAKER_PIN);
}


FourDigitsLed* MainUi::GetFourDigitsLed()
{
	return _fourDigitsLed;
}


LedMatrix* MainUi::GetLedMatrix()
{
	return _ledMatrix;
}


Sound* MainUi::GetSound()
{
	return _sound;
}

