#pragma once

#include <cstdint>

#include "ClassNames.h"

class ToneStub
{
public:
    void begin(uint8_t tonePin);
    bool isPlaying();
    void play(uint16_t frequency, uint32_t duration = 0);
    void stop();
};

