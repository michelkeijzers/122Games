#include "Box.h"
#include "Game.h"
#include "LcdDisplay.h"
#include "Demo.h"


using namespace std;


Box::Box()
	: _games(&_ui)
{
}


void Box::setup()
{
	_ui.Initialize();
	GetGames()->Initialize();
}


void Box::loop()
{
	_ui.GetMainUi()->Refresh();
	_ui.GetMainUi()->ProcessButtons();
	
    Game* activeGame = GetGames()->GetActiveGame();
    if (activeGame != nullptr)
    {
        activeGame->Play();
    }
}


Games* Box::GetGames()
{
	return &_games;
}


Ui* Box::GetUi()
{
	return &_ui;
}
