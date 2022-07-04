#include "AssertUtils.h"
#include "Games.h"
#include "Demo.h"
#include "FadeInOutDemo.h"
#include "Worms.h"

void Games::Initialize()
{
	//SetActiveGameByIndex(Games::EGameId::WORMS);
	//GetActiveGame()->Start();
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
	case EGameId::WORMS:
		_activeGame = new Worms();
		break;

	case EGameId::FADE_IN_OUT_DEMO:
		_activeGame = new FadeInOutDemo();
		break;

	case EGameId::GRAPHIC_DEMO:
		_activeGame = new Demo();
		break;

	default:
		AssertUtils::MyAssert(false);
		break;
	}

	GetActiveGame()->Initialize(_ui);

	return _activeGame;
}


void Games::DeleteActiveGame()
{
	if (_activeGame != nullptr)
	{
		delete _activeGame;
		_activeGame = nullptr;
	}
}
