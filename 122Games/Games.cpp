#include "Games.h"
#include "Demo.h"
#include "Worms.h"


Games::Games()
{
}


void Games::SelectGameByIndex(int gameIndex, Game** activeGame)
{
	if (*activeGame != nullptr)
	{
		delete *activeGame;
	}
		
	switch (gameIndex)
	{
	case GAME_DEMO:
		*activeGame = new Demo();
		break;

	case GAME_WORMS:
		*activeGame = new Worms();
		break;

	default:
		throw "Illegal case";
		break;
	}
}