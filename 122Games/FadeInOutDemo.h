#pragma once
#include "Game.h"

class FadeInOutDemo :
    public Game
{
public:
    /* virtual */ void Start();
    /* virtual */ void Play();

    /* virtual */ void HandleButton(int player, Game::EButton button);

private:
    int _light;

    int _iteration;
};

