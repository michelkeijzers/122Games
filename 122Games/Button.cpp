#include "Button.h"



Button::Button()
  : _pinNumber(),
	_pinResistorMode(INPUT_PULLUP),
	_debouncePeriod(0),
	_debouncePollingTime(0),
    _firstPressed(false),
    _isInvalidated(true),
    _currentState(false)
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
    bool newState = false;

    if (_firstPressed && (millis() - _debouncePollingTime < _debouncePeriod))
    {
        newState = true;
    }
    else if (digitalRead(_pinNumber) == LOW) 
    {
        _firstPressed = true;
        if (millis() - _debouncePollingTime > _debouncePeriod)
        {
            _debouncePollingTime = millis();
            newState = true;
        }
        else 
        {
            newState = false;
        }
    }
    else
    {
        newState = false;
    }

    if (_currentState != newState)
    {
        _currentState = newState;
        _isInvalidated = true;
    }
    return newState;
}


bool Button::IsInvalidated()
{
    return _isInvalidated;
}


void Button::ResetInvalidation()
{
    _isInvalidated = false;
}