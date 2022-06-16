#include "Ui.h"


void Ui::Initialize()
{
	_mainUi.Initialize();
}


MainUi* Ui::GetMainUi()
{
	return &_mainUi;
}


PlayerUi* Ui::GetPlayerUi(uint8_t player)
{
	return (player == 0) ? &_playerUi1 : &_playerUi2;
}
