#include "Box.h"
#include "Game.h"
#include "Demo.h"

using namespace std;

Box::Box()
	: _games(&_ui)
{
}


void Box::setup()
{
	GetGames()->Init();
	_ui.Initialize();
}


void Box::loop()
{
	// TODO Implement Arduino Loop
}


Games* Box::GetGames()
{
	return &_games;
}


Ui* Box::GetUi()
{
	return &_ui;
}
