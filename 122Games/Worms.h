#pragma once
#include "Game.h"

class Worms :
	public Game
{
public:
	Worms();

	/* virtual */ void Start();
	/* virtual */ void Play();

	/* virtual */ void HandleButton(Game::EButton button);

	/* virtual */ void HandleDirection(JoyStick::EDirection direction);

private:
	void DrawCursors();
	void MakeSurroundingLedsGreen();
	void MakeLedGreen(uint8_t x, uint8_t y);

	int _playerX;
	int _playerY;
	uint32_t _nextPlayMillis;
};

