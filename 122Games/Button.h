#pragma once

#include <cstdint>
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


// Debounce button, LOW = Pressed
class Button
{
public:
	Button();

	void Initialize(uint8_t pinNumber, uint8_t pinResistorMode = INPUT_PULLUP, uint16_t debouncePeriod = 50);

	uint8_t GetPinNumber();

	bool Read();

private:
	uint8_t _pinNumber;
	uint8_t _pinResistorMode;
	uint16_t _debouncePeriod;
	uint32_t _debouncePollingTime;
};

