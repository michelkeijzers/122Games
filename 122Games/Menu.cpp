#include "framework.h"
#include "Menu.h"
#include "AssertUtils.h"
#include "MathUtils.h"
#include "Button.h"
#include "Games.h"
#include "LcdDisplay.h"


Menu::Menu()
: _state(Menu::EState::Startup),
  _menuValue(0),
  _lastTransitionTime(0),
  _lcdDisplay(nullptr)
{
}


void Menu::Initialize(LcdDisplay* lcdDisplay)
{
	_lcdDisplay = lcdDisplay;
	_lastTransitionTime = millis();
}


Menu::EState Menu::GetState()
{
	return _state;
}


// For timed transitions
void Menu::Refresh()
{
	switch (_state)
	{
	case EState::Startup:
		if (millis() - _lastTransitionTime >= 1000)
		{
			if (_menuValue < 2)
			{
				_menuValue++;
				UpdateLcd();
				_lastTransitionTime = millis();
			}
			else
			{
				_state = EState::SelectGame;
				_menuValue = 0;
				UpdateLcd();
				_lastTransitionTime = millis();
			}
		}
		break;

	default:
		// Ignore others
		break;
	}
}


void Menu::ProcessCommand(Button* button, ECommand command)
{
	switch (_state)
	{
	case EState::Startup:
		// Only timed transitions
		break;

	case EState::SelectGame:
		ProcessSelectGame(button, command);
		break;

	case EState::PlayingGame:
		ProcessPlayingGame(button, command);
		break;

	default:
		AssertUtils::MyAssert(false);
	}
}


void Menu::ProcessSelectGame(Button* button, ECommand command)
{
	OutputDebugString(L"SG ");
	switch (command)
	{
	case ECommand::Left:
		_menuValue = MathUtils::Max(0, _menuValue - 1);
		UpdateLcd();
		break;

	case ECommand::Right:
		_menuValue = MathUtils::Min((uint8_t) Games::EGameId::LAST_GAME_INDEX, _menuValue + 1);
		UpdateLcd();
		break;

	case ECommand::Select:
		_state = EState::PlayingGame;
		UpdateLcd();
		break;

	default:
		// Ignore others
		break;
	}
}


void Menu::ProcessPlayingGame(Button* button, ECommand command)
{
	switch (command)
	{
	case ECommand::Back:
		_state = EState::SelectGame;
		UpdateLcd();
		break;

	default:
		// Ignore others
		break;
	}
}


void Menu::UpdateLcd()
{
	OutputDebugString(L"Upd ");
	switch (_state)
	{
	case EState::Startup:
		switch (_menuValue)
		{
		case 0: 
			// Initialization, no LCD update
			break;

		case 1:
			OutputDebugString(L"a ");
			_lcdDisplay->Clear();
			_lcdDisplay->DisplayCenteredText(0, "LED MATRIX GAMES");
			_lcdDisplay->DisplayCenteredText(1, "0.1     (c) 2022"); // IMPR: Left/Right justify
			break;

		case 2:
			OutputDebugString(L"b ");
			_lcdDisplay->Clear();
			_lcdDisplay->DisplayCenteredText(0, "Developed by");
			_lcdDisplay->DisplayCenteredText(1, "Michel Keijzers");
			break;
		}
		break;

	case EState::SelectGame:
		OutputDebugString(L"c ");
		_lcdDisplay->Clear();
		_lcdDisplay->DisplayCenteredText(0, "Select Game");
		_lcdDisplay->DisplayCenteredText(1, "| GAME NAME >"); // TODO
		break;

	case EState::PlayingGame:
		OutputDebugString(L"d ");
		_lcdDisplay->Clear();
		_lcdDisplay->DisplayText(0, 0, "Playing Game");
		_lcdDisplay->DisplayText(1, 0, "GAME NAME"); //TODO
		break;

	default:
		AssertUtils::MyAssert(false);
	}
}