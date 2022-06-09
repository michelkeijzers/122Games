#pragma once

#include "Canvas.h"

class Game
{
public:
	enum class EButton
	{
		Up,
		Right,
		Down,
		Left,
		Select
	};

	virtual void Start() = 0;
	virtual void Play() = 0;

	virtual void HandleButton(int player, EButton button) = 0;

	Canvas* GetCanvas();
	
protected:
	Canvas _canvas;
};

