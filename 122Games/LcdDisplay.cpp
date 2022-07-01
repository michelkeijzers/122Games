#include "AssertUtils.h"
#include "LcdDisplay.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(LIQUID_CRYSTAL_I2C_CLASS)


LcdDisplay::LcdDisplay(uint32_t i2cAddress, uint8_t nrOfRows, uint8_t nrOfColumns)
  : _i2cAddress(i2cAddress),
	_nrOfColumns(nrOfColumns),
	_nrOfRows(nrOfRows),
	_cursorRow(0),
	_cursorColumn(0),
	_displayOn(false),
	_backLightOn(false),
	_cursorOn(false),
	_cursorBlinking(false),
	_content{},
	_liquidCrystalI2c(nullptr)
{
	AssertUtils::MyAssert(nrOfRows <= MAX_ROWS);
	AssertUtils::MyAssert(nrOfColumns <= MAX_COLUMNS);

	_liquidCrystalI2c = new LIQUID_CRYSTAL_I2C_CLASS(i2cAddress, nrOfColumns, nrOfRows);
}


void LcdDisplay::Initialize()
{
	_liquidCrystalI2c->init();
}


void LcdDisplay::DisplayOn(bool on /* = true */)
{
	if (on)
	{
		_liquidCrystalI2c->display();
	}
	else
	{
		_liquidCrystalI2c->noDisplay();
	}

	_displayOn = on;
}


void LcdDisplay::Clear()
{
	_liquidCrystalI2c->clear();

	for (uint8_t row = 0; row < _nrOfRows; row++)
	{
		for (uint8_t column = 0; column < _nrOfColumns; column++)
		{
			_content[row][column] = ' ';
		}
	}
}

void LcdDisplay::SetCursor(uint8_t row, uint8_t column)
{
	VerifyRowAndColumn(row, column);
	_liquidCrystalI2c->setCursor(column, row);
	_cursorColumn = column;
	_cursorRow = row;
}


void LcdDisplay::Home()
{
	_liquidCrystalI2c->home();

	_cursorRow = 0;
	_cursorColumn = 0;
}


void LcdDisplay::CursorOn(bool on /* = true */)
{
	if (on)
	{
		_liquidCrystalI2c->cursor();
	}
	else
	{
		_liquidCrystalI2c->noCursor();
	}

	_cursorOn = on;
}


void LcdDisplay::CursorBlinking(bool on /* = true */)
{
	if (on)
	{
		_liquidCrystalI2c->blink();
	}
	else
	{
		_liquidCrystalI2c->noBlink();
	}
	_cursorBlinking = on;
}


void LcdDisplay::Refresh()
{

}


void LcdDisplay::DisplayText(uint8_t row, uint8_t startColumn, const char* text)
{
	VerifyRowAndColumn(row, startColumn);
	_liquidCrystalI2c->print(text);
	
	for (uint8_t textIndex = 0; textIndex < MathUtils::Min(startColumn + strlen(text), _nrOfColumns - 1); textIndex++)
	{
		_content[row][startColumn + textIndex] = text[textIndex];
	}
}


uint8_t LcdDisplay::GetNrOfRows()
{
	return _nrOfRows;
}


uint8_t LcdDisplay::GetNrOfColumns()
{
	return _nrOfColumns;
}


char LcdDisplay::GetContentCharacter(uint8_t row, uint8_t column)
{
	VerifyRowAndColumn(row, column);
	return _content[row][column];
}


size_t LcdDisplay::write(uint8_t character)
{
	_liquidCrystalI2c->write(character);

	VerifyRowAndColumn(_cursorRow, _cursorColumn);
	_content[_cursorRow][_cursorColumn] = character;
	_cursorColumn++;

	return 1;
}


void LcdDisplay::VerifyRowAndColumn(uint8_t row, uint8_t column)
{
	AssertUtils::MyAssert(column < _nrOfColumns);
	AssertUtils::MyAssert(row < _nrOfRows);
}