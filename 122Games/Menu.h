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
	void DecreaseCurrentMenuValue();
	void IncreaseCurrentMenuValue();
	void SetState(EState state);

	void DisplaySideSymbols(bool show = true);
	void UpdateLcd();
	void UpdateLcdForSelectingOrPlayingGame(const char* text);

	EState _state;
	uint8_t _currentMenuValue;
	uint8_t _maxMenuValue;
	uint32_t _lastTransitionTime;

	LcdDisplay* _lcdDisplay;

	bool _isInvalidated;
};

