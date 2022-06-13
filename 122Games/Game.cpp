#include "Game.h"

Game::Game()
	: _ui(nullptr)
{

}


void Game::SetUi(Ui* ui)
{
	_ui = ui;
}