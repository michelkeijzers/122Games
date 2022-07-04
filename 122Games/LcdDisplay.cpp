#include "AssertUtils.h"
#include "MathUtils.h"
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
	_liquidCrystalI2c(nullptr),
	_contentIsInvalidated {}
{
	AssertUtils::MyAssert(nrOfRows <= MAX_ROWS);
	AssertUtils::MyAssert(nrOfColumns <= MAX_COLUMNS);

	_liquidCrystalI2c = new LIQUID_CRYSTAL_I2C_CLASS(i2cAddress, nrOfColumns, nrOfRows);

	for (uint8_t row = 0; row < MAX_ROWS; row++)
	{
		for (uint8_t column = 0; column < MAX_COLUMNS; column++)
		{
			_contentIsInvalidated[row][column] = true;
		}
	}
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
	for (uint8_t row = 0; row < _nrOfRows; row++)
	{
		for (uint8_t column = 0; column < _nrOfColumns; column++)
		{
			SetCursor(row, column);
			write(' ');
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

	_liquidCrystalI2c->setCursor(startColumn, row);
	_liquidCrystalI2c->print(text);
	
	for (uint8_t textIndex = 0; textIndex < MathUtils::Min((int)strlen(text), _nrOfColumns - 1); textIndex++)
	{
		SetCursor(row, startColumn + textIndex);
		write(text[textIndex]);
	}
}


void LcdDisplay::DisplayCenteredText(uint8_t row, const char* text)
{
	int8_t startColumn = (int8_t) (_nrOfColumns - strlen(text)) / 2;
	AssertUtils::MyAssert(startColumn >= 0);

	VerifyRowAndColumn(row, startColumn);
	_liquidCrystalI2c->print(text);

	for (uint8_t textIndex = 0; textIndex < MathUtils::Min((int)strlen(text), _nrOfColumns - 1); textIndex++)
	{
		SetCursor(row, startColumn + textIndex);
		write(text[textIndex]);
	}
}


void LcdDisplay::DisplayNumber(uint8_t row, uint8_t startColumn, int32_t number, uint8_t maxLength)
{
	char buffer[20] = {};
	size_t size = sprintf_s(buffer, "%*lu", maxLength, number);
	AssertUtils::MyAssert(strlen(buffer) <= maxLength);
	DisplayText(row, startColumn, buffer);
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
	_contentIsInvalidated[_cursorRow][_cursorColumn] = true;
	_cursorColumn++;

	return 1;
}


bool LcdDisplay::IsContentInvalidated(uint8_t row, uint8_t column)
{
	VerifyRowAndColumn(row, column);
	return _contentIsInvalidated[row][column];
}


void LcdDisplay::ResetInvalidation()
{
	for (uint8_t row = 0; row < _nrOfRows; row++)
	{
		for (uint8_t column = 0; column < _nrOfColumns; column++)
		{
			_contentIsInvalidated[_cursorRow][_cursorColumn] = false;
		}
	}
}

	
void LcdDisplay::VerifyRowAndColumn(uint8_t row, uint8_t column)
{
	AssertUtils::MyAssert(row < _nrOfRows);
	AssertUtils::MyAssert(column < _nrOfColumns);
}

