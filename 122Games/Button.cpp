#include "Button.h"



Button::Button()
  : _pinNumber(),
	_pinResistorMode(INPUT_PULLUP),
	_debouncePeriod(0),
	_debouncePollingTime(0)
{
}


void Button::Initialize(uint8_t pinNumber, uint8_t pinResistorMode, uint16_t debouncePeriod)
{	
    _pinNumber = pinNumber;
    _pinResistorMode = pinResistorMode;
    _debouncePeriod = debouncePeriod;
    _debouncePollingTime = 0;

    pinMode(_pinNumber, _pinResistorMode);
    InjectDigitalValue(pinNumber, true, true); // Depress (HIGH)
}


uint8_t Button::GetPinNumber()
{
    return _pinNumber;
}


bool Button::Read()
{
    if (millis() - _debouncePollingTime < _debouncePeriod) 
    {
        return false;
    }

    if (digitalRead(_pinNumber) == LOW) 
    {
        if (millis() - _debouncePollingTime > _debouncePeriod) 
        {
            _debouncePollingTime = millis();
            return true;
        }
        else 
        {
            return false;
        }
    }

    return false;
}