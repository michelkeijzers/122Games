#ifdef WIN32


#include "ToneStub.h"


void ToneStub::begin(uint8_t tonePin)
{
}


bool ToneStub::isPlaying()
{
	return false;
}


void ToneStub::play(uint16_t frequency, uint32_t duration /* = 0 */)
{
}


void ToneStub::stop()
{
}

#endif //WIN32