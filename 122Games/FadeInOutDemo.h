#pragma once
#include "Game.h"

class FadeInOutDemo :
    public Game
{
public:
    FadeInOutDemo();

    /* virtual */ void Start();
    /* virtual */ void Play();

private:
    int _light;

    int _iteration;
};

