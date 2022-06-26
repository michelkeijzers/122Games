#include "Joystick.h"
#include "MathUtils.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


const uint16_t MAX_POT_VALUE = 4095;
const uint16_t HALF_POT_RANGE = (MAX_POT_VALUE + 1) / 2;


JoyStick::JoyStick()
	: _switchPin(0),
	  _xAxisPotPin(0),
	  _yAxisPotPin(0),
	  _xCenterValue(0),
      _yCenterValue(0),
	  _centerPercentage(0)
{
}


void JoyStick::Initialize(uint8_t switchPin, uint8_t xAxisPotPin, uint8_t yAxisPotPin, uint8_t centerPercentage)
{
	_switchPin = switchPin;
	_xAxisPotPin = xAxisPotPin;
	_yAxisPotPin = yAxisPotPin;
	_centerPercentage = centerPercentage;

	CalibrateCenter();
}


int16_t JoyStick::ReadRawX()
{
	return analogRead(_xAxisPotPin);
}


int16_t JoyStick::ReadRawY()
{
	return analogRead(_yAxisPotPin);
}


int8_t JoyStick::ReadX()
{
	return RangeAndMap(MathUtils::Trim(ReadRawX() + (2048 - _xCenterValue), 0, 4095));
}


int8_t JoyStick::ReadY()
{
	return RangeAndMap(MathUtils::Trim(ReadRawY() + (2048 - _yCenterValue), 0, 4095));
}


JoyStick::EDirection JoyStick::GetDirection()
{
	int8_t x = ReadX();
	int8_t y = ReadY();

	EDirection direction = EDirection::Center;

	if (x <= -_centerPercentage)
	{
		if (y <= -_centerPercentage)
		{
			direction = EDirection::LeftUp;
		}
		else if (y >= _centerPercentage)
		{
			direction = EDirection::LeftDown;
		}
		else
		{
			direction = EDirection::Left;
		}
	}
	else if (x >= _centerPercentage)
	{
		if (y <= -_centerPercentage)
		{
			direction = EDirection::RightUp;
		}
		else if (y >= _centerPercentage)
		{
			direction = EDirection::RightDown;
		}
		else
		{
			direction = EDirection::Right;
		}
	}
	else
	{
		if (y <= -_centerPercentage)
		{
			direction = EDirection::Up;
		}
		else if (y >= _centerPercentage)
		{
			direction = EDirection::Down;
		}
	}

	return direction;
}


JoyStick::EHorizontalDirection JoyStick::GetHorizontalDirection()
{
	EHorizontalDirection direction = EHorizontalDirection::Center;

	switch (GetDirection())
	{
	case EDirection::Left: // fall through
	case EDirection::LeftUp: // fall through
	case EDirection::LeftDown:
		direction = EHorizontalDirection::Left;
		break;

	case EDirection::Right: // fall through
	case EDirection::RightUp: // fall through
	case EDirection::RightDown:
		direction = EHorizontalDirection::Right;
		break;

	default:
		// Ignore (Center)
		break;
	}

	return direction;
}


JoyStick::EVerticalDirection JoyStick::GetVerticalDirection()
{
	EVerticalDirection direction = EVerticalDirection::Center;

	switch (GetDirection())
	{
	case EDirection::LeftUp: // fall through
	case EDirection::Up: // fall through
	case EDirection::RightUp:
		direction = EVerticalDirection::Up;
		break;

	case EDirection::LeftDown: // fall through
	case EDirection::Down: // fall through
	case EDirection::RightDown:
		direction = EVerticalDirection::Down;
		break;

	default:
		// Ignore (Center)
		break;
	}

	return direction;
}


void JoyStick::CalibrateCenter()
{
	_xCenterValue = ReadRawX();
	_yCenterValue = ReadRawY();
}


int8_t JoyStick::RangeAndMap(uint16_t calibratedValue)
{
	uint16_t rangedValue = MathUtils::Trim(calibratedValue, -HALF_POT_RANGE, HALF_POT_RANGE - 1);
	return MathUtils::Map(calibratedValue, 0, 4096 - 1, -100, 100);

}
