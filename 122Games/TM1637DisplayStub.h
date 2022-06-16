#pragma once

#include <cstdint>

class TM1637DisplayStub
{
public:
	TM1637DisplayStub(uint8_t pinClk, uint8_t pinDIO, unsigned int bitDelay);
	void setBrightness(uint8_t brightness, bool on);
	void setSegments(const uint8_t segments[], uint8_t length, uint8_t pos);
	void clear();
	void showNumberDec(int num, bool leading_zero, uint8_t length, uint8_t pos);
	void showNumberDecExt(int num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos);
	void showNumberHexEx(uint16_t num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos);
	void showNumberBaseEx(int8_t base, uint16_t num, uint8_t dots, bool leading_zero, uint8_t length, uint8_t pos);
	void bitDelay();
	void start();
	void stop();
	void writeByte(uint8_t b);
	void showDots(uint8_t dots, uint8_t* digits);
	void encodeDigit(uint8_t digit);
};

