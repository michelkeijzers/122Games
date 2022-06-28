#pragma once
#include "Game.h"

class Demo :
    public Game
{
public:
    Demo();

    /* virtual */ void Start();
    /* virtual */ void Play();

private:
    bool _light = false;
};

