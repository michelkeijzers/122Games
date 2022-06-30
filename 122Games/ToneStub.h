#ifdef WIN32

#pragma once

// Based on Tone library by Brett Hagman


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

#endif // WIN32
