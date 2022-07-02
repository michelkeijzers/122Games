#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


class LIQUID_CRYSTAL_I2C_CLASS;


class LcdDisplay
{
public:
	static const uint8_t MAX_COLUMNS = 20;
	static const uint8_t MAX_ROWS = 4;

	LcdDisplay(uint32_t i2cAddress, uint8_t nrOfRows, uint8_t nrOfColumns);

	void Initialize();
	void DisplayOn(bool on = true);

	void Clear();
	
	void Home();
	void SetCursor(uint8_t row, uint8_t column);
	void CursorOn(bool on = true);
	void CursorBlinking(bool on = true);

	void Refresh();

	void DisplayText(uint8_t row, uint8_t startColumn, const char* text);
	void DisplayNumber(uint8_t row, uint8_t startColumn, int32_t number, uint8_t maxLength);
	
	uint8_t GetNrOfRows();
	uint8_t GetNrOfColumns();
	char GetContentCharacter(uint8_t row, uint8_t column);

	size_t write(uint8_t character);

	bool IsContentInvalidated(uint8_t row, uint8_t column);
	void ResetInvalidation();

private:
	void VerifyRowAndColumn(uint8_t row, uint8_t column);

	uint32_t _i2cAddress;
	uint8_t _nrOfColumns;
	uint8_t _nrOfRows;
	bool _displayOn;
	bool _backLightOn;
	uint8_t _cursorRow;
	uint8_t _cursorColumn;
	bool _cursorOn;
	bool _cursorBlinking;
	char _content[MAX_ROWS][MAX_COLUMNS];
	bool _contentIsInvalidated[MAX_ROWS][MAX_COLUMNS];
	LIQUID_CRYSTAL_I2C_CLASS* _liquidCrystalI2c;
};

