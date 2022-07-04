#pragma once

#include "MainUi.h"
#include "PlayerUi.h"

class LedMatrix;

class Ui
{
public:
	Ui();

	void Initialize();
	bool IsInitialized();

	MainUi* GetMainUi();
	PlayerUi* GetPlayerUi();

	void Refresh();

private:
	MainUi _mainUi;
	PlayerUi _playerUi;
	bool _isInitialized;
};

