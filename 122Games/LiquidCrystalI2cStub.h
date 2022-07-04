#ifdef WIN32

#pragma once

// I2C version
// See https://github.com/johnrickman/LiquidCrystal_I2C/blob/master/LiquidCrystal_I2C.h


#include "Print.h"


class LiquidCrystalI2cStub : public Print
{
public:
	enum ECharSize
	{
		LCD_5x8DOTS
	};

	LiquidCrystalI2cStub(uint8_t i2cAddress, uint8_t lcd_columns, uint8_t lcd_rows);
	~LiquidCrystalI2cStub();

	void begin(uint8_t columns, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
	
	void clear();
	void home();
	void noDisplay();
	void display();
	void noBlink();
	void blink();
	void noCursor();
	void cursor();
	void scrollDisplayLeft();
	void scrollDisplayRight();
	void printLeft();
	void printRight();
	void leftToRight();
	void rightToLeft();
	void shiftIncrement();
	void shiftDecrement();
	void noBacklight();
	void backlight();
	void autoscroll();
	void noAutoscroll();
	void createChar(uint8_t, uint8_t[]);
	void createChar(uint8_t location, const char* charmap);
	void setCursor(uint8_t column, uint8_t row);
	size_t write(uint8_t);
	void command(uint8_t);
	void init();
	void oled_init();

	////compatibility API function aliases
	void blink_on();						// alias for blink()
	void blink_off();       					// alias for noBlink()
	void cursor_on();      	 					// alias for cursor()
	void cursor_off();      					// alias for noCursor()
	void setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()
	void load_custom_character(uint8_t char_num, uint8_t* rows);	// alias for createChar()

	// See official library for some unsupported methods
};

#endif // WIN32