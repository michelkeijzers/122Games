#include "Game.h"

Game::Game()
	: _ui(nullptr)
{
}

void Game::Initialize(Ui* ui)
{
	//_ui->Initialize();
	_ui = ui;
}


Ui* Game::GetUi()
{
	return _ui;
}
