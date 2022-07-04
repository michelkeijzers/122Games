#ifdef WIN32


#include "ClassNames.h"
#include "LiquidCrystalI2CStub.h"


LiquidCrystalI2cStub::LiquidCrystalI2cStub(uint8_t i2cAddress, uint8_t lcd_columns, uint8_t lcd_rows)
{
}


LiquidCrystalI2cStub::~LiquidCrystalI2cStub()
{
}


void LiquidCrystalI2cStub::begin(uint8_t columns, uint8_t rows, uint8_t charsize /* = LCD_5x8DOTS */)
{
}


void LiquidCrystalI2cStub::clear()
{

}


void LiquidCrystalI2cStub::home()
{
}


void LiquidCrystalI2cStub::noDisplay()
{
}


void LiquidCrystalI2cStub::display()
{
}


void LiquidCrystalI2cStub::noBlink()
{
}


void LiquidCrystalI2cStub::blink()
{
}


void LiquidCrystalI2cStub::noCursor()
{
}


void LiquidCrystalI2cStub::cursor()
{
}


void LiquidCrystalI2cStub::scrollDisplayLeft()
{
}


void LiquidCrystalI2cStub::scrollDisplayRight()
{
}


void LiquidCrystalI2cStub::printLeft()
{
}


void LiquidCrystalI2cStub::printRight()
{
}


void LiquidCrystalI2cStub::leftToRight()
{
}


void LiquidCrystalI2cStub::rightToLeft()
{
}


void LiquidCrystalI2cStub::shiftIncrement()
{
}


void LiquidCrystalI2cStub::shiftDecrement()
{
}


void LiquidCrystalI2cStub::noBacklight()
{
}


void LiquidCrystalI2cStub::backlight()
{
}


void LiquidCrystalI2cStub::autoscroll()
{
}


void LiquidCrystalI2cStub::noAutoscroll()
{
}


void LiquidCrystalI2cStub::createChar(uint8_t, uint8_t[])
{
}


void LiquidCrystalI2cStub::createChar(uint8_t location, const char* charmap)
{
}


void LiquidCrystalI2cStub::setCursor(uint8_t column, uint8_t row)
{
}


size_t LiquidCrystalI2cStub::write(uint8_t)
{
	return 0;
}


void LiquidCrystalI2cStub::command(uint8_t)
{
}


void LiquidCrystalI2cStub::init()
{
}


void LiquidCrystalI2cStub::oled_init()
{
}


// compatibility API function aliases

void LiquidCrystalI2cStub::blink_on()
{
}


void LiquidCrystalI2cStub::blink_off()
{
}


void LiquidCrystalI2cStub::cursor_on()
{
}


void LiquidCrystalI2cStub::cursor_off()
{
}


void LiquidCrystalI2cStub::setBacklight(uint8_t new_val)
{
}


void LiquidCrystalI2cStub::load_custom_character(uint8_t char_num, uint8_t* rows)
{
}



#endif // WIN32