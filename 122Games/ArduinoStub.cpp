// ArduinoStub.cpp
// Stub for Arduino function on Windows.
// Only for Windows

#ifdef WIN32


#include <sys/timeb.h>
#include <cstdint>
#include <time.h>
#include <stdlib.h>
#include "ArduinoStub.h"


timeb* _startupTime = nullptr;

std::map<uint8_t, bool> _injectedDigitalValues;
std::map<uint8_t, uint16_t> _injectedAnalogValues;


// Digital I/O

extern void pinMode(uint8_t pin, int state)
{
	(void)pin;
	(void)state;
}


extern bool digitalRead(uint8_t pin)
{
	auto it = _injectedDigitalValues.find(pin);
	if (it == _injectedDigitalValues.end())
	{
		return rand() % 2 == 0 ? false : true;
	}
	else
	{
		return it->second; // Value
	}
}


extern void digitalWrite(uint8_t pin, bool state)
{
	(void)pin;
	(void)state;
}


// Analog I/O

extern uint16_t analogRead(uint8_t pin)
{
	auto it = _injectedAnalogValues.find(pin);
	if (it == _injectedAnalogValues.end())
	{
		return rand() % 4096;
	}
	else
	{
		return it->second; // Value
	}
}

// Injection functions

#ifdef WIN32

extern void InjectDigitalValue(uint8_t pin, bool set, bool injectionValue)
{
	_injectedDigitalValues.erase(pin);
	if (set)
	{
		_injectedDigitalValues.insert({ pin, injectionValue });
	}
}

#endif // WIN32

#ifdef WIN32

extern void InjectAnalogValue(uint8_t pin, bool set, uint16_t injectionValue)
{
	_injectedAnalogValues.erase(pin);
	if (set)
	{
		_injectedAnalogValues.insert({ pin, injectionValue });
	}
}

#endif // WIN32

// Zero, Due & MKR Family

// Advanced I/O

// Time

extern void delay(uint32_t delay)
{
	timeb startTime;
	ftime(&startTime);

	uint64_t endTime = startTime.time * 1000 + startTime.millitm + delay;
	timeb runningTime;

	do
	{
		ftime(&runningTime);
	} while ((uint64_t)(runningTime.time * 1000 + runningTime.millitm) < endTime);
}


extern uint32_t millis()
{
	if (_startupTime == nullptr)
	{
		_startupTime = new timeb;
		ftime(_startupTime);
	}

	timeb now;

	ftime(&now);
	return uint32_t(now.time * 1000 + now.millitm -
		_startupTime->time * 1000 - _startupTime->millitm);
}


// Math

extern _Check_return_ int __cdecl abs(_In_ int a)
{
	return a < 0 ? -a : a;
}


extern int constrain(int x, int lower, int upper)
{
	return (x < lower ? lower : (x > upper ? upper : x));
}


// Manual test: map(5, 1, 10, 100, 200) = 10
extern int map(int value, int fromLower, int fromUpper, int toLower, int toUpper)
{
	return toLower + ((toUpper - toLower) / (fromUpper - fromLower)) * (value - fromLower);
}


extern int Min(int a, int b)
{
	return a < b ? a : b;
}


extern int Max(int a, int b)
{
	return a > b ? a : b;
}


// Trigonometry

// Characters

// Random Numbers

extern uint32_t random(uint32_t number)
{
	return rand() % number;
}


extern void randomSeed(uint16_t seed)
{
	(void)seed;
	srand((unsigned int)time(nullptr));
}


// Bits and Bytes

// External Interrupts

// Interrupts

// Communication

// USB

// ESP32

void ledcSetup(int ledChannel, int frequency, int resolution)
{
	(void)ledChannel;
	(void)frequency;
	(void)resolution;
}


void ledcAttachPin(int pin, int ledChannel)
{
	(void)pin;
	(void)ledChannel;
}


void ledcWriteTone(int ledChannel, float frequency)
{
	(void)ledChannel;
	(void)frequency;
}


#endif // WIN32
