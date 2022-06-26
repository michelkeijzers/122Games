#pragma once

class LedMatrix;
class FourDigitsLed;
class Sound;

class MainUi
{
public:
	static const int MAX_X = 12;
	static const int MAX_Y = 12;
	static const int NR_OF_LEDS = MAX_X * MAX_Y;

	MainUi();
	~MainUi();
	void Initialize();
	
	LedMatrix* GetLedMatrix();
	FourDigitsLed* GetFourDigitsLed();
	Sound* GetSound();

private:
	LedMatrix *_ledMatrix;
	FourDigitsLed *_fourDigitsLed;
	Sound* _sound;
};
