
// ArduinoStub.h
// Stub for Arduino function on Windows.
// Only for Windows

#ifdef WIN32

#pragma once

#include <cstdint>
#include "MathUtils.h"
#include "SerialStub.h"
#include <string>
#include <cstring>
#include <cstdio>
#include <iostream>
#include "ArduinoStringStub.h"

#define F
#define PROGMEM

typedef ArduinoStringStub STRING;

constexpr auto LED_BUILTIN = 10;

constexpr auto GPIO_INPUT = 0;
constexpr auto INPUT_PULLUP = 1;
constexpr auto OUTPUT = 100;

constexpr auto LOW = false;
constexpr auto HIGH = true;

const uint8_t A0 = 100;
const uint8_t A1 = 101;
const uint8_t A2 = 102;
const uint8_t A3 = 103;
const uint8_t A4 = 104;
const uint8_t A5 = 105;
const uint8_t A6 = 106;
const uint8_t A7 = 107;
const uint8_t A8 = 108;


// Digital I/O

extern void pinMode(uint8_t pin, int state);
extern bool digitalRead(uint8_t pin);
extern void digitalWrite(uint8_t pin, bool state);


// Analog I/O

extern uint16_t analogRead(uint8_t pin);

// Zero, Due & MKR Family

// Advanced I/O

// Time

extern void delay(uint32_t milliSeconds);

extern uint32_t millis();

// Math

#define ABS(x) MathUtils::Abs(x)

extern int constrain(int x, int lower, int upper);

extern int map(int value, int fromLower, int fromUpper, int toLower, int toUpper);

#define MIN(x, y) MathUtils::Min(x, y)

#define MAX(x, y) MathUtils::Max(x, y)


// Trigonometry

// Characters

// Random Numbers

extern uint32_t random(uint32_t number);

extern void randomSeed(uint16_t seed);

// Bits and Bytes

// External Interrupts

// Interrupts

// Communication

// USB

// ESP32 

void ledcSetup(int ledChannel, int frequency, int resolution);
void ledcAttachPin(int pin, int ledChannel);
void ledcWriteTone(int ledCHannel, float frequency);

#endif // _WINDOWS
