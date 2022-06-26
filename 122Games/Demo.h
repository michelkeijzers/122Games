#pragma once
#include "Game.h"

class Demo :
    public Game
{
public:
    Demo();

    /* virtual */ void Start();
    /* virtual */ void Play();

    /* virtual */ void HandleButton(Game::EButton button);

    /* virtual */ void HandleDirection(JoyStick::EDirection direction);

private:
    bool _light = false;
};

