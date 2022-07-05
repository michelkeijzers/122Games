#pragma once

#include "Game.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


class Pong :
    public Game
{
public:
    Pong();

    /* virtual */ void Start();
    /* virtual */ void Play();

private:
    enum class EBallServeSpeed
    {
        Slow,
        Normal
    };

    enum class EScoreToWin
    {
        Score3 = 3,
        Score5 = 5,
        Score10 = 10,
        Score15 = 15,
        Score20 = 20

    };
    void MovePaddle();
    void MoveBall();

    uint32_t _nextPlayMillis;

    uint8_t _ballLocationX;
    uint8_t _ballLocationY;
    int8_t _ballSpeedX;
    int8_t _ballSpeedY;

    uint8_t _paddleTop;
    uint8_t _paddleLength;

    uint8_t _score;

    uint8_t _countDown;

    EBallServeSpeed _settingBallServeSpeed;
    EScoreToWin _settingScoreToWin;
};

