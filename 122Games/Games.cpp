#include "Games.h"
#include "Demo.h"
#include "Worms.h"


void Games::Init()
{
	SetActiveGameByIndex(0);
	GetActiveGame()->Start();
}

Games::Games(Ui* ui)
	: _activeGame(nullptr)
{
	_ui = ui;
}

Game* Games::GetActiveGame()
{
	return _activeGame;
}


Game* Games::SetActiveGameByIndex(int gameIndex)
{
	if (_activeGame != nullptr)
	{
		delete _activeGame;
	}
		
	switch ((EGameId) gameIndex)
	{
	case GAME_DEMO:
		_activeGame = new Demo();
		break;

	case GAME_WORMS:
		_activeGame = new Worms();
		break;

	default:
		throw "Illegal case";
		break;
	}

	GetActiveGame()->SetUi(_ui);

	return _activeGame;
}