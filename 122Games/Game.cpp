#include "Game.h"

Game::Game()
	: _ui(nullptr)
{

}


Ui* Game::GetUi()
{
	return _ui;
}


void Game::SetUi(Ui* ui)
{
	_ui = ui;
}