#pragma once
#include "Game.h"

class FadeInOutDemo :
    public Game
{
public:
    FadeInOutDemo();

    /* virtual */ void Start();
    /* virtual */ void Play();

    /* virtual */ void HandleButton(Game::EButton button);

    /* virtual */ void HandleDirection(JoyStick::EDirection direction);

private:
    int _light;

    int _iteration;
};

