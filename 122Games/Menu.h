#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


class Button;
class LcdDisplay;


class Menu
{
public:
	enum class ECommand
	{
		Select,
		Back,
		Left,
		Right
	};

	Menu();

	void Initialize(LcdDisplay* lcdDisplay);
	
	enum class EState
	{
		Startup,
		SelectGame,
		PlayingGame
	};

	EState GetState();
	uint8_t GetMenuValue();

	void Refresh();
	void ProcessCommand(Button* button, ECommand command);
	void ProcessSelectGame(Button* button, ECommand command);
	void ProcessPlayingGame(Button* button, ECommand command);

	bool IsInvalidated();
	void ResetInvalidation();

private:
	void UpdateLcd();

	EState _state;
	uint8_t _menuValue;
	uint32_t _lastTransitionTime;

	LcdDisplay* _lcdDisplay;

	bool _isInvalidated;
};

