#include "Button.h"



Button::Button()
  : _pinNumber(),
	_pinResistorMode(INPUT_PULLUP),
    lastDebounceTime(0),
    debounceDelay(0),
    _isInvalidated(true),
    buttonState(false),
    lastButtonState(false)
{
}


void Button::Initialize(uint8_t pinNumber, uint8_t pinResistorMode, uint16_t debouncePeriod)
{	
    _pinNumber = pinNumber;
    _pinResistorMode = pinResistorMode;
    lastDebounceTime = 0;
    debounceDelay = debouncePeriod;
    pinMode(_pinNumber, _pinResistorMode);
    buttonState = false;
    lastButtonState = false;
#ifdef WIN32
    InjectDigitalValue(pinNumber, true, true); // Depress (HIGH)
#endif
}


uint8_t Button::GetPinNumber()
{
    return _pinNumber;
}


// See https://docs.arduino.cc/built-in-examples/digital/Debounce
bool Button::Read()
{
    // read the state of the switch into a local variable:
    bool reading = digitalRead(_pinNumber) == LOW ? true : false; // LOW = pressed

    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading != lastButtonState) {
        // reset the debouncing timer
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        // whatever the reading is at, it's been there for longer than the debounce
        // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != buttonState) {
            buttonState = reading;
            _isInvalidated = true;
        }
    }

    // save the reading. Next time through the loop, it'll be the lastButtonState:
    lastButtonState = reading;
    return buttonState;
}


bool Button::IsInvalidated()
{
    return _isInvalidated;
}


void Button::ResetInvalidation()
{
    _isInvalidated = false;
}