#pragma once

#include "MainUi.h"
#include "PlayerUi.h"

class LedMatrix;

class Ui
{
public:
	MainUi* GetMainUi();
	LedMatrix* GetLedMatrix();
	PlayerUi* GetPlayerUi(int player);

private:
	MainUi _mainUi;
	PlayerUi _player1Ui;
	PlayerUi _player2Ui;
};

