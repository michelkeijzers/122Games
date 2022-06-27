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

	uint8_t _playerX;
	uint8_t _playerY;
	uint32_t _nextPlayMillis;
	uint32_t _rounds;

};

