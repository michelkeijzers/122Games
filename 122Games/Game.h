#pragma once

#include "Canvas.h"
#include "Ui.h"


class Game
{
public:
	Game();

	enum class EButton
	{
		Up,
		Right,
		Down,
		Left,
		Select
	};

	Ui* GetUi();
	void SetUi(Ui* ui);

	virtual void Start() = 0;
	virtual void Play() = 0;

	virtual void HandleButton(int player, EButton button) = 0;
	
protected:
	Ui* _ui;
};

