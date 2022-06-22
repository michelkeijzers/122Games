#include "Sound.h"

#include "ClassNames.h"
#include HEADER_FILE(TONE_CLASS)
#include HEADER_FILE(ARDUINO_CLASS)

Sound::Sound()
   : _tone(nullptr),
	 _dataPin(0),
	_isPlaying(false),
	_frequency(0),
	_stopAtMillis(0)
{
}


Sound::~Sound()
{
	if (_tone != nullptr)
	{
		delete _tone;
	}
}


void Sound::Initialize(uint8_t dataPin)
{
	if (_tone != nullptr)
	{
		delete _tone;
	}
	
	_dataPin = dataPin;
	_tone = new TONE_CLASS();
	_tone->begin(dataPin);
}


bool Sound::IsPlaying()
{
	return _isPlaying;
}


void Sound::Play(uint16_t frequency, uint16_t duration /* = 0 */)
{
	_tone->play(frequency, duration == 0 ? UINT16_MAX : duration);

	_isPlaying = true;
	_frequency = frequency;
	_stopAtMillis = duration == 0 ? UINT16_MAX : millis() + duration;
}


void Sound::Stop()
{
	_tone->stop();

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
