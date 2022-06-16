#include "Games.h"
#include "Demo.h"
#include "FadeInOutDemo.h"
#include "Worms.h"

void Games::Init()
{
	SetActiveGameByIndex(Games::EGameId::FADE_IN_OUT_DEMO);
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
	case DEMO:
		_activeGame = new Demo();
		break;

	case FADE_IN_OUT_DEMO:
		_activeGame = new FadeInOutDemo();
		break;

	case WORMS:
		_activeGame = new Worms();
		break;

	default:
		throw "Illegal case";
		break;
	}

	GetActiveGame()->SetUi(_ui);

	return _activeGame;
}