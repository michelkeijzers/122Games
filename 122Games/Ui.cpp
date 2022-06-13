#include "Ui.h"


MainUi* Ui::GetMainUi()
{
	return &_mainUi;
}


PlayerUi* Ui::GetPlayerUi(int player)
{
	return (player == 0) ? &_player1Ui : &_player2Ui;
}


LedMatrix* Ui::GetLedMatrix()
{
	return _mainUi.GetLedMatrix();
}