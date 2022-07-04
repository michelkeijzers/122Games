#pragma once


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

	bool IsInvalidated();
	void ResetInvalidation();

private:
	uint8_t _pinNumber;
	uint8_t _pinResistorMode;
	uint32_t lastDebounceTime;
	uint32_t debounceDelay;
	bool buttonState; // Current reading from input pin;
	bool lastButtonState; // Previou reading from the input pin
	bool _isInvalidated;
};

