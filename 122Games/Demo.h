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
    uint32_t _nextPlayMillis;
};

