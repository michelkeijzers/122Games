#pragma once


#include "ClassNames.h"
#include HEADER_FILE(FAST_LED_CLASS)
#include "LedColor.h"


constexpr auto LED_STRIP_MAX_NR_OF_LEDS = 255;


class LedStrip
{
public:
	static const uint8_t MAX_CURRENT_IN_MILLI_AMP_PER_SUB_LED;
	static const uint8_t SUB_LEDS_PER_LED;                    

	LedStrip();

    void Initialize(uint8_t nrOfLeds);
	
	uint8_t GetDataPin();

	uint8_t GetNrOfLeds();

	struct FastLedCRGB* GetLeds();

	struct FastLedCRGB* GetLed(uint8_t ledIndex);

	uint16_t CalculateCurrentInMilliAmp();

	void ReduceCurrent(uint8_t percentage);

	void SetAllLeds(LedColor::EColor color, uint8_t step);
	void SetAllLeds(uint32_t color);
	void SetAllLeds(uint8_t red, uint8_t green, uint8_t blue);

	void SetLed(struct FastLedCRGB* led, LedColor::EColor color, uint8_t step);
	void SetLed(struct FastLedCRGB* led, uint32_t color);
	void SetLed(struct FastLedCRGB* led, uint8_t red, uint8_t green, uint8_t blue);

private:
	uint8_t _nrOfLeds;

	struct FastLedCRGB* _leds;

	CFastLED _fastLed;
};
