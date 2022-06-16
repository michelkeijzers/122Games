#include <stdlib.h>

#include "FadeInOutDemo.h"
#include "Canvas.h"
#include "MainUi.h"
#include "Ui.h"
#include "LedMatrix.h"

/* virtual */ void FadeInOutDemo::Start()
{
	_ui->GetPlayerUi(0)->SetScore(0);
}


/* virtual */ void FadeInOutDemo::Play()
{
	_light = (_light + 1) % 256;

	for (int x = 0; x < MainUi::MAX_X; x++)
	{
		for (int y = 0; y < MainUi::MAX_Y; y++)
		{
			_ui->GetMainUi()->GetLedMatrix()->SetLed(x, y, _light, _light, _light);
		}
	}
}


/* virtual */ void FadeInOutDemo::HandleButton(int player, Game::EButton button)
{
}