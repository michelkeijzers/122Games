#pragma once
class Game;

class Games
{
public:
	enum EGameId
	{
		GAME_DEMO,
		GAME_WORMS
	};

	Games();

	static const int NR_OF_GAMES = 1;

	void SelectGameByIndex(int index, Game** activeGame);

};

