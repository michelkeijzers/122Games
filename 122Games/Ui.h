#pragma once

#include "MainUi.h"
#include "PlayerUi.h"

class LedMatrix;

class Ui
{
public:
	void Initialize();
	bool IsInitialized();

	MainUi* GetMainUi();
	PlayerUi* GetPlayerUi();

private:
	MainUi _mainUi;
	PlayerUi _playerUi;
	bool _isInitialized;
};

