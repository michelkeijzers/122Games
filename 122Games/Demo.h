#pragma once
#include "Game.h"

class Demo :
    public Game
{
public:
    /* virtual */ void Start();
    /* virtual */ void Play();

    /* virtual */ void HandleButton(int player, Game::EButton button);

private:
    bool _light = false;
};

