#include "Sound.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


Sound::Sound()
  : _dataPin(0),
 	_isPlaying(false),
	_frequency(0),
	_stopAtMillis(0),
	_isFrequencyInvalidated(true),
    _isDurationInvalidated(true)
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


void Sound::Play(uint16_t frequency, uint32_t duration /* = 0 */)
{
	ledcWriteTone(_dataPin, frequency);

	if (IsPlaying())
	{
		_stopAtMillis = duration == 0 ? UINT16_MAX : millis() + duration;
		_isDurationInvalidated = true;
		if (_frequency != frequency)
		{
			_frequency = frequency;
			_isFrequencyInvalidated = true;
		}
	}
	else
	{
		_isPlaying = true;
		_stopAtMillis = duration == 0 ? UINT16_MAX : millis() + duration;
		_isDurationInvalidated = true;
		_frequency = frequency;
		_isFrequencyInvalidated = true;
	}
}


void Sound::Stop()
{
	ledcWrite(_dataPin, 0);

	if (IsPlaying())
	{
		_isPlaying = false;
		_stopAtMillis = 0;
		_isDurationInvalidated = true;
		_frequency = 0;
		_isFrequencyInvalidated = true;
	}
}


void Sound::Refresh()
{
	if (millis() >= _stopAtMillis)
	{
		Stop();
	}
}


bool Sound::IsInvalidated()
{
	return _isFrequencyInvalidated || _isDurationInvalidated;
}


bool Sound::IsFrequencyInvalidated()
{
	return _isFrequencyInvalidated;
}


bool Sound::IsDurationInvalidated()
{
	return _isDurationInvalidated;
}


void Sound::ResetInvalidation()
{
	_isFrequencyInvalidated = false;
	_isDurationInvalidated = false;
}


uint16_t Sound::GetFrequency()
{
	return _frequency;
}


uint16_t Sound::GetDuration()
{
	return (_stopAtMillis == 0 ? 0 : _stopAtMillis - millis());
}
