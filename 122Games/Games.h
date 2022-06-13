#pragma once

class Game;
class Ui;

class Games
{
public:
	enum EGameId
	{
		GAME_DEMO,
		GAME_WORMS
	};

	void Init();

	Games(Ui* ui);

	static const int NR_OF_GAMES = 1;

	Game* GetActiveGame();

	Game* SetActiveGameByIndex(int index);

private:
	Game* _activeGame;

	Ui* _ui;
};

