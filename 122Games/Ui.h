#pragma once

#include "MainUi.h"
#include "PlayerUi.h"

class LedMatrix;

class Ui
{
public:
	void Initialize();

	MainUi* GetMainUi();
	PlayerUi* GetPlayerUi(uint8_t player);

private:
	MainUi _mainUi;
	PlayerUi _playerUi1;
	PlayerUi _playerUi2;
};

