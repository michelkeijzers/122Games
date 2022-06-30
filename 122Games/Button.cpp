#include "Button.h"



Button::Button()
  : _pinNumber(),
	_pinResistorMode(INPUT_PULLUP),
	_debouncePeriod(0),
	_debouncePollingTime(0),
    _firstPressed(false)
{
}


void Button::Initialize(uint8_t pinNumber, uint8_t pinResistorMode, uint16_t debouncePeriod)
{	
    _pinNumber = pinNumber;
    _pinResistorMode = pinResistorMode;
    _debouncePeriod = debouncePeriod;
    _debouncePollingTime = 0;
    _firstPressed = false;

    pinMode(_pinNumber, _pinResistorMode);
#ifdef WIN32
    InjectDigitalValue(pinNumber, true, true); // Depress (HIGH)
#endif
}


uint8_t Button::GetPinNumber()
{
    return _pinNumber;
}


bool Button::Read()
{
    if (_firstPressed && (millis() - _debouncePollingTime < _debouncePeriod))
    {
        return true;
    }

    if (digitalRead(_pinNumber) == LOW) 
    {
        _firstPressed = true;
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