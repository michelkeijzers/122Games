#pragma once

#include "Games.h"

class Game;
class Screen;


class Box
{
public:
	Box();

	void setup();
	void loop();

	void SetScreen(Screen* screen);
	void SetActiveGame(int gameIndex);
	Game* ActiveGame();
	void StartGame();

private:
	Screen* _screen;
	Games _games;
    Game* _activeGame;
};

