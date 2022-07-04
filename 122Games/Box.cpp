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
	MainUi* mainUi = _ui.GetMainUi();
	mainUi->GetSelectButton()->ResetInvalidation();
	mainUi->GetBackButton()->ResetInvalidation();
	mainUi->GetLeftButton()->ResetInvalidation();
	mainUi->GetRightButton()->ResetInvalidation();
	Menu* menu = mainUi->GetMenu();

	mainUi->Refresh();
	mainUi->ProcessButtons();
	
	
	if (menu->IsInvalidated())
	{
		Game* activeGame = GetGames()->GetActiveGame();

		switch (menu->GetState())
		{
		case Menu::EState::Startup: // Fall through
			// No action needed
			break;

		case Menu::EState::SelectGame:
			if (activeGame != nullptr)
			{
				_games.DeleteActiveGame();
				mainUi->Clear(false);
			}
			break;

		case Menu::EState::PlayingGame:
			_games.SetActiveGameByIndex(menu->GetMenuValue());
			_games.GetActiveGame()->Start();
		}
	}
	
	Game* activeGame = GetGames()->GetActiveGame();
	if (activeGame != nullptr)
    {
        activeGame->Play();
    }

	menu->ResetInvalidation();

}


Games* Box::GetGames()
{
	return &_games;
}


Ui* Box::GetUi()
{
	return &_ui;
}
