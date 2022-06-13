#pragma once

#include "Games.h"
#include "Ui.h"

class Game;
class Screen;


class Box
{
public:
	Box();

	void setup();
	void loop();

	Games* GetGames();
	Ui* GetUi();

private:
	Games _games;
	Ui _ui;
};

