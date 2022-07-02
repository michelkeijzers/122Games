#pragma once


#include "ClassNames.h"
#include "Button.h"


class Joystick
{
public:
	enum class EDirection
	{
		Center,
		Up,
		RightUp,
		Right,
		RightDown,
		Down,
		LeftDown,
		Left,
		LeftUp
	};

	enum class EHorizontalDirection
	{
		Left,
		Center,
		Right
	};

	enum class EVerticalDirection
	{
		Up,
		Center,
		Down
	};

	enum class ENonDiagonalDirection
	{
		Up,
		Right,
		Down,
		Left,
		Center
	};

	Joystick();

	void Initialize(uint8_t switchPin, uint8_t xAxisPotPin, uint8_t yAxisPotPin, uint8_t centerPercentage);
	
	int16_t ReadRawX();
	int16_t ReadRawY();
	
	bool ReadButton();

	EDirection GetDirection();
	ENonDiagonalDirection GetNonDiagonalDirection();

	EHorizontalDirection GetHorizontalDirection();
	EVerticalDirection GetVerticalDirection();

	// Calibrate with center values, range to [-100, 0 (center), 100].
	int8_t ReadX();
	int8_t ReadY();

	void CalibrateCenter();

	//TODO: Full Calibration (moving joystick to left/right/up/down and save values (in EEPROM?)

	bool IsDirectionInvalidated();
	bool IsButtonInvalidated();
	void ResetInvalidation();

private:
	int8_t RangeAndMap(uint16_t calibratedValue);

	uint8_t _xAxisPotPin;
	uint8_t _yAxisPotPin;

	uint16_t _xCenterValue;
	uint16_t _yCenterValue;

	uint8_t _centerPercentage;

	Button* _button;

	bool _directionIsInvalidated;
	EHorizontalDirection _currentHorizontalDirection;
	EVerticalDirection _currentVerticalDirection;
	ENonDiagonalDirection _currentNonDiagonalDirection;
	EDirection _currentDirection;
};

