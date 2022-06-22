#include "Ui.h"


void Ui::Initialize()
{
	_mainUi.Initialize();
	_isInitialized = true;
}


bool Ui::IsInitialized()
{
	return _isInitialized;
}

MainUi* Ui::GetMainUi()
{
	return &_mainUi;
}


PlayerUi* Ui::GetPlayerUi()
{
	return &_playerUi;
}
