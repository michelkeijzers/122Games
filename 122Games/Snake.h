#pragma once
#include "Game.h"

class Snake :
	public Game
{
public:
	Snake();

	/* virtual */ void Start();
	/* virtual */ void Play();

private:
	void DrawCursors();
	void MakeSurroundingLedsGreen();
	void MakeLedGreen(uint8_t x, uint8_t y);

	uint8_t _playerX;
	uint8_t _playerY;
	uint32_t _nextPlayMillis;
	uint32_t _rounds;
};

