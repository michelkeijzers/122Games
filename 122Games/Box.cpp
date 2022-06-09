#include "Box.h"
#include "Game.h"
#include "Demo.h"

using namespace std;

Box::Box()
	: _screen(nullptr),
	  _activeGame(nullptr)
{
}


void Box::setup()
{
	// TODO Implement Arduino Setup
}


void Box::loop()
{
	// TODO Implement Arduino Loop
}


void Box::SetScreen(Screen* screen)
{
	_screen = screen;
}


void Box::SetActiveGame(int gameIndex)
{
	if (_activeGame != nullptr)
	{
		delete _activeGame;
	}

	_games.SelectGameByIndex(gameIndex, &_activeGame);
}


Game* Box::ActiveGame()
{
	return _activeGame;
}


void Box::StartGame()
{
	_activeGame->Start();
}