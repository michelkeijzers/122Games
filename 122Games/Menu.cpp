#include "Menu.h"
#include "AssertUtils.h"
#include "MathUtils.h"
#include "Button.h"
#include "Games.h"
#include "LcdDisplay.h"


Menu::Menu()
: _state(Menu::EState::Startup),
  _currentMenuValue(0),
  _maxMenuValue(0),
  _lastTransitionTime(0),
  _lcdDisplay(nullptr),
  _isInvalidated(false)
{
}


void Menu::Initialize(LcdDisplay* lcdDisplay)
{
	SetState(EState::Startup);
	_lcdDisplay = lcdDisplay;
	_lastTransitionTime = millis();
}


Menu::EState Menu::GetState()
{
	return _state;
}


uint8_t Menu::GetMenuValue()
{
	return _currentMenuValue;
}


// For timed transitions
void Menu::Refresh()
{
	switch (_state)
	{
	case EState::Startup:
		if (millis() - _lastTransitionTime >= 1000)
		{
			if (_currentMenuValue < _maxMenuValue)
			{
				IncreaseCurrentMenuValue();
				UpdateLcd();
				_lastTransitionTime = millis();
			}
			else
			{
				SetState(EState::SelectGame);
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
	switch (command)
	{
	case ECommand::Left:
		DecreaseCurrentMenuValue();
		break;

	case ECommand::Right:
		IncreaseCurrentMenuValue();
		break;

	case ECommand::Select:
		SetState(EState::PlayingGame);
		break;

	default:
		// Ignore others
		break;
	}

	if (_isInvalidated)
	{
		UpdateLcd();
	}
}


void Menu::ProcessPlayingGame(Button* button, ECommand command)
{
	switch (command)
	{
	case ECommand::Back:
		SetState(EState::SelectGame);
		UpdateLcd();
		break;

	default:
		// Ignore others
		break;
	}
}


void Menu::DecreaseCurrentMenuValue()
{
	if (_currentMenuValue > 0)
	{
		_currentMenuValue--;
		_isInvalidated = true;
	}
}


void Menu::IncreaseCurrentMenuValue()
{
	if (_currentMenuValue < _maxMenuValue)
	{
		_currentMenuValue++;
		_isInvalidated = true;
	}
}


void Menu::SetState(EState state)
{
	if (_state != state)
	{
		_state = state;
		_isInvalidated = true;

		switch (_state)
		{
		case EState::Startup:
			_maxMenuValue = 1; // Two screens
			break;

		case EState::SelectGame:
			_maxMenuValue = (uint8_t)Games::EGameId::LAST_GAME_INDEX - 1;
			break;

		case EState::PlayingGame:
			// No menu values
			break;

		default:
			AssertUtils::MyAssert(false);
		}
	}
}


void Menu::DisplaySideSymbols(bool show /* = true */)
{
	char leftSymbol  = show ? (_currentMenuValue == 0 ? ' ' : '<') : ' ';
	char rightSymbol = show ? (_currentMenuValue == _maxMenuValue ? ' ' : '>') : ' ';
	_lcdDisplay->DisplayCharacter(1, 0, leftSymbol);
	_lcdDisplay->DisplayCharacter(1, _lcdDisplay->GetNrOfColumns() - 1, rightSymbol);
}


void Menu::UpdateLcd()
{
	switch (_state)
	{
	case EState::Startup:
		switch (_currentMenuValue)
		{
		case 0: 
			// Initialization, no LCD update
			break;

		case 1:
			_lcdDisplay->Clear();
			// IMPR: Left/Right justify
			_lcdDisplay->DisplayCenteredTexts("LED MATRIX GAMES", "0.1     (c) 2022"); 
			break;

		case 2:
			_lcdDisplay->Clear();
			_lcdDisplay->DisplayCenteredTexts("Developed by", "Michel Keijzers");
			break;
		}
		break;

	case EState::SelectGame:
		UpdateLcdForSelectingOrPlayingGame("Select Game");
		break;

	case EState::PlayingGame:
		UpdateLcdForSelectingOrPlayingGame("Playing Game");
		break;

	default:
		AssertUtils::MyAssert(false);
	}
}


void Menu::UpdateLcdForSelectingOrPlayingGame(const char* text)
{
	_lcdDisplay->Clear();
	_lcdDisplay->DisplayCenteredTexts(
		"Select Game", Games::GetGameName(_currentMenuValue), _lcdDisplay->GetNrOfColumns() - 2);
	DisplaySideSymbols();
}


bool Menu::IsInvalidated()
{
	return _isInvalidated;
}


void Menu::ResetInvalidation()
{
	_isInvalidated = false;
}
