#pragma once

#include <cstdint>
#include "MainUi.h"

class HardwareProperties
{
public:
	static const uint8_t LED_STRIP_DATA_PIN = 8; // TODO
	static const uint8_t LED_STRIP_NR_OF_COLUMNS = MainUi::MAX_X; 
	static const uint8_t LED_STRIP_NR_OF_ROWS = MainUi::MAX_Y;

	static const uint8_t FOUR_DIGITS_LED_DATA_PIN = 4; // TODO
	static const uint8_t FOUR_DIGITS_LED_CLOCK_PIN = 5; // TODO

	static const uint8_t SPEAKER_PIN = 11; //TODO
};
