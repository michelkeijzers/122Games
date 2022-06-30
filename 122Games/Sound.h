#pragma once


#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


class TONE_CLASS;


class Sound
{
public:
	Sound();

	void Initialize(uint8_t dataPin);

	bool IsPlaying();
	void Play(uint16_t frequency, uint32_t duration = 0);
	void Stop();

	uint16_t GetFrequency();
	uint16_t GetDuration();

	void Refresh();

private:
	uint8_t _dataPin;
	bool _isPlaying;
	uint16_t _frequency;
	uint32_t _stopAtMillis;
};

