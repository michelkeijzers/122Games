#pragma once
#include "Game.h"

class Worms :
	public Game
{
public:
	Worms();

	/* virtual */ void Start();
	/* virtual */ void Play();

	/* virtual */ void HandleButton(int player, Game::EButton button);

private:
	void DrawCursors();

	int _player1x;
	int _player1y;
	int _player2x;
	int _player2y;
};

