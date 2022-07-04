#include "AssertUtils.h"
#include "Games.h"
#include "Demo.h"
#include "FadeInOutDemo.h"
#include "Worms.h"


/* static */ const char* Games::GAME_NAMES[(uint8_t)Games::EGameId::LAST_GAME_INDEX] =
{
	"WORMS",
	"FADE DEMO",
	"GRAPHIC DEMO"
};


Games::Games(Ui* ui)
	: _activeGame(nullptr),
	_activeGameId(EGameId::LAST_GAME_INDEX)
{
	AssertUtils::MyAssert((sizeof(GAME_NAMES) / sizeof(const char*) == (uint8_t) EGameId::LAST_GAME_INDEX));
	_ui = ui;
}


void Games::Initialize()
{
	//SetActiveGameByIndex(Games::EGameId::WORMS);
	//GetActiveGame()->Start();
}



Game* Games::GetActiveGame()
{
	return _activeGame;
}


Game* Games::SetActiveGameByIndex(int gameIndex)
{
	AssertUtils::MyAssert(gameIndex < (uint8_t)EGameId::LAST_GAME_INDEX);

	_activeGameId = (EGameId) gameIndex;

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


/* static */const char* Games::GetGameName(uint8_t gameIndex)
{
	AssertUtils::MyAssert(gameIndex < (uint8_t)EGameId::LAST_GAME_INDEX);
	return GAME_NAMES[gameIndex];
}