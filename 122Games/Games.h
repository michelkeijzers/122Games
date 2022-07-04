#pragma once

class Game;
class Ui;

class Games
{
public:
	enum class EGameId
	{
		DEMO,
		FADE_IN_OUT_DEMO,

		WORMS,
		LAST_GAME_INDEX
	};

	void Initialize();

	Games(Ui* ui);

	static const int NR_OF_GAMES = 1;

	Game* GetActiveGame();

	Game* SetActiveGameByIndex(int index);

private:
	Game* _activeGame;

	Ui* _ui;
};

