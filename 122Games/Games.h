#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


class Game;
class Ui;


class Games
{
public:
	enum class EGameId
	{
		WORMS,
		FADE_IN_OUT_DEMO,
		GRAPHIC_DEMO,
		LAST_GAME_INDEX
	};

	const char* GAME_NAMES[(uint8_t) EGameId::LAST_GAME_INDEX] =
	{
		"WORMS",
		"FADE IN/OUT DEMO",
		"GRAPHIC DEMO"
	};

	void Initialize();

	Games(Ui* ui);

	static const int NR_OF_GAMES = 1;

	Game* GetActiveGame();

	Game* SetActiveGameByIndex(int index);
	void DeleteActiveGame();

private:
	Game* _activeGame;

	Ui* _ui;
};

