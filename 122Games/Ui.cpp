#include "Ui.h"


Ui::Ui()
	: _isInitialized(false)
{
}

void Ui::Initialize()
{
	_mainUi.Initialize();
	_playerUi.Initialize();
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


void Ui::Refresh()
{
	_mainUi.Refresh();
	_playerUi.Refresh();
}