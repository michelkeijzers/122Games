#pragma once


#include "ClassNames.h"


class HardwareProperties
{
public:
	static constexpr uint8_t NR_OF_LEDS_X = 15;
	static constexpr uint8_t NR_OF_LEDS_Y = 10;

	static constexpr uint32_t LCD_I2C_ADDRESS = 0x123456; //TODO
	static constexpr uint8_t  LCD_NR_OF_ROW = 2;
	static constexpr uint8_t  LCD_NR_OF_COLUMNS = 16;

	// ESP32:
	static const uint8_t LED_STRIP_DATA_PIN = 22; // TODO; for FastLED, cannot use all numbers (some give error for pin number, e.g. 0, 8, 9)
	// Uno
	//static const uint8_t LED_STRIP_DATA_PIN = 8;

	static const uint8_t LED_STRIP_NR_OF_COLUMNS = NR_OF_LEDS_X;
	static const uint8_t LED_STRIP_NR_OF_ROWS = NR_OF_LEDS_Y;

	static const uint8_t FOUR_DIGITS_LED_DATA_PIN = 4; // TODO
	static const uint8_t FOUR_DIGITS_LED_CLOCK_PIN = 5; // TODO

	static const uint8_t SPEAKER_PIN = 11; //TODO

	static const uint8_t JOYSTICK_HORIZONTAL_PIN = 12; // TODO
	static const uint8_t JOYSTICK_VERTICAL_PIN = 13; // TODO
	static const uint8_t JOYSTICK_BUTTON_PIN = 14; // TODO

	static const uint8_t BUTTON_SELECT = 29; //TODO
	static const uint8_t BUTTON_BACK = 28; //TODO
	static const uint8_t BUTTON_LEFT = 30; //TODO
	static const uint8_t BUTTON_RIGHT = 31; //TODO

};
