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

	Games(Ui* ui);

	void Initialize();

	static const int NR_OF_GAMES = 1;

	Game* GetActiveGame();

	Game* SetActiveGameByIndex(int gameIndex);
	void DeleteActiveGame();

	static const char* GetGameName(uint8_t gameIndex);

private:
	Game* _activeGame;
	EGameId _activeGameId;
	static const char* GAME_NAMES[(uint8_t)EGameId::LAST_GAME_INDEX];

	Ui* _ui;
};

