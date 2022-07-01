#include "Box.h"
#include "Game.h"
#include "LcdDisplay.h"
#include "Demo.h"
#include "Sound.h"


using namespace std;


Box::Box()
	: _games(&_ui)
{
}


void Box::setup()
{
	_ui.Initialize();
	_ui.GetMainUi()->GetLcdDisplay()->DisplayText(0, 2, "12 Square Games");
	_ui.GetMainUi()->GetLcdDisplay()->DisplayText(1, 0, "Created");
	_ui.GetMainUi()->GetLcdDisplay()->DisplayText(2, 3, "by");
	_ui.GetMainUi()->GetLcdDisplay()->DisplayText(3, 5, "Michel Keijzers");
	GetGames()->Initialize();
}


void Box::loop()
{
	_ui.GetMainUi()->GetSound()->Refresh();
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
