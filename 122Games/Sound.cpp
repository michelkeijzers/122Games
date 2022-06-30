#include "Sound.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


Sound::Sound()
  : _dataPin(0),
 	_isPlaying(false),
	_frequency(0),
	_stopAtMillis(0)
{
}


void Sound::Initialize(uint8_t dataPin)
{
	_dataPin = dataPin;
	ledcSetup(0, 10000, 12); // PWM frequency 10K, 12 bits
	ledcAttachPin(_dataPin, 0);
}


bool Sound::IsPlaying()
{
	return _isPlaying;
}


void Sound::Play(uint16_t frequency, uint16_t duration /* = 0 */)
{
	ledcWriteTone(_dataPin, frequency);

	_isPlaying = true;
	_frequency = frequency;
	_stopAtMillis = duration == 0 ? UINT16_MAX : millis() + duration;
}


void Sound::Stop()
{
	ledcWrite(_dataPin, 0);

	_isPlaying = false;
	_frequency = 0;
	_stopAtMillis = 0;
}


void Sound::Refresh()
{
	if (millis() >= _stopAtMillis)
	{
		Stop();
	}
}


uint16_t Sound::GetFrequency()
{
	return _frequency;
}


uint16_t Sound::GetDuration()
{
	return (_stopAtMillis == 0 ? 0 : _stopAtMillis - millis());
}
