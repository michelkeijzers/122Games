#include "Joystick.h"
#include "MathUtils.h"
#include "ClassNames.h"
#include "Button.h"
#include HEADER_FILE(ARDUINO_CLASS)


const uint16_t MAX_POT_VALUE = 4095;
const uint16_t HALF_POT_RANGE = (MAX_POT_VALUE + 1) / 2;


Joystick::Joystick()
	: _button(nullptr),
	  _xAxisPotPin(0),
	  _yAxisPotPin(0),
	  _xCenterValue(0),
      _yCenterValue(0),
	  _centerPercentage(0),
	  _directionIsInvalidated(true),
	  _currentHorizontalDirection(EHorizontalDirection::Center),
	  _currentVerticalDirection(EVerticalDirection::Center),
	  _currentNonDiagonalDirection(ENonDiagonalDirection::Center),
	  _currentDirection(EDirection::Center)
{
}


void Joystick::Initialize(
	uint8_t switchPin, uint8_t xAxisPotPin, uint8_t yAxisPotPin, uint8_t centerPercentage)
{
	_xAxisPotPin = xAxisPotPin;
	_yAxisPotPin = yAxisPotPin;
	_centerPercentage = centerPercentage;

	if (_button != nullptr)
	{
		delete _button;
	}
	_button = new Button();
	_button->Initialize(switchPin, INPUT_PULLUP, 20);
	CalibrateCenter();
}


int16_t Joystick::ReadRawX()
{
	return analogRead(_xAxisPotPin);
}


int16_t Joystick::ReadRawY()
{
	return analogRead(_yAxisPotPin);
}


int16_t Joystick::ReadX()
{
	return RangeAndMap(MathUtils::Trim(ReadRawX() + (2048 - _xCenterValue), 0, 4095));
}


int16_t Joystick::ReadY()
{
	return -RangeAndMap(MathUtils::Trim(ReadRawY() + (2048 - _yCenterValue), 0, 4095));
}


bool Joystick::ReadButton()
{
	return _button->Read();
}


// Use https://www.desmos.com/calculator
Joystick::EDirection Joystick::GetDirection()
{
	EDirection newDirection = EDirection::Center;

	int16_t x = ReadX();
	int16_t y = ReadY();

	if (x * x + y * y >= _centerPercentage * _centerPercentage)
	{
		newDirection =
			x <= 0 ? (y <= 0 ? (2 * x <  y ? (x / 2 >  y ? EDirection::LeftDown 
				                                         : EDirection::Left)
				                           : (x / 2 >  y ? EDirection::Down     
											             : EDirection::Center))
				             : (2 * x < -y ? (x / 2 > -y ? EDirection::LeftUp   
								                         : EDirection::Left)
				                           : (x / 2 > -y ? EDirection::Up       
											             : EDirection::Center)))
				   : (y <= 0 ? (2 * x < -y ? (x / 2 > -y ? EDirection::Center   
					                                     : EDirection::Down)
				                           : (x / 2 > -y ? EDirection::Right  
											             : EDirection::RightDown))
				             : (2 * x <  y ? (x / 2 >  y ? EDirection::Center 
								                         : EDirection::Up)
				                           : (x / 2 >  y ? EDirection::Right
											             : EDirection::RightUp)));
	}
	
	if (_currentDirection != newDirection)
	{
		_currentDirection = newDirection;
		_directionIsInvalidated = true;
	}

	return newDirection;
}


// Use https://www.desmos.com/calculator
Joystick::ENonDiagonalDirection Joystick::GetNonDiagonalDirection()
{
	ENonDiagonalDirection newDirection = ENonDiagonalDirection::Center;

	int16_t x = ReadX();
	int16_t y = ReadY();

	if (x * x + y * y >= _centerPercentage * _centerPercentage)
	{
		newDirection =
			x <= 0 ? (y <= 0 ? (x <  y ? ENonDiagonalDirection::Left 
									   : ENonDiagonalDirection::Down)
				             : (x < -y ? ENonDiagonalDirection::Left 
								       : ENonDiagonalDirection::Up))
			       : (y <= 0 ? (x < -y ? ENonDiagonalDirection::Down 
					                   : ENonDiagonalDirection::Right)
				             : (x <  y ? ENonDiagonalDirection::Up   
								       : ENonDiagonalDirection::Right));
	}


	if (_currentNonDiagonalDirection != newDirection)
	{
		_currentNonDiagonalDirection = newDirection;
		_directionIsInvalidated = true;
	}

	return newDirection;
}


Joystick::EHorizontalDirection Joystick::GetHorizontalDirection()
{
	EHorizontalDirection newDirection = EHorizontalDirection::Center;

	switch (GetDirection())
	{
	case EDirection::Left: // fall through
	case EDirection::LeftUp: // fall through
	case EDirection::LeftDown:
		newDirection = EHorizontalDirection::Left;
		break;

	case EDirection::Right: // fall through
	case EDirection::RightUp: // fall through
	case EDirection::RightDown:
		newDirection = EHorizontalDirection::Right;
		break;

	default:
		// Ignore (Center)
		break;
	}

	if (_currentHorizontalDirection != newDirection)
	{
		_currentHorizontalDirection = newDirection;
		_directionIsInvalidated = true;
	}

	return newDirection;
}


Joystick::EVerticalDirection Joystick::GetVerticalDirection()
{
	EVerticalDirection newDirection = EVerticalDirection::Center;

	switch (GetDirection())
	{
	case EDirection::LeftUp: // fall through
	case EDirection::Up: // fall through
	case EDirection::RightUp:
		newDirection = EVerticalDirection::Up;
		break;

	case EDirection::LeftDown: // fall through
	case EDirection::Down: // fall through
	case EDirection::RightDown:
		newDirection = EVerticalDirection::Down;
		break;

	default:
		// Ignore (Center)
		break;
	}

	if (_currentVerticalDirection != newDirection)
	{
		_currentVerticalDirection = newDirection;
		_directionIsInvalidated = true;
	}

	return newDirection;
}


void Joystick::CalibrateCenter()
{
	_xCenterValue = ReadRawX();
	_yCenterValue = ReadRawY();
}


int16_t Joystick::RangeAndMap(int16_t calibratedValue)
{
	int16_t rangedValue = MathUtils::Trim(calibratedValue, -HALF_POT_RANGE, HALF_POT_RANGE - 1);
	return MathUtils::Map(calibratedValue, 0, 4096 - 1, -1000, 1000);

}


bool Joystick::IsDirectionInvalidated()
{
	return _directionIsInvalidated;
}


bool Joystick::IsButtonInvalidated()
{
	return _button->IsInvalidated();
}


void Joystick::ResetInvalidation()
{
	_directionIsInvalidated = false;
	_button->ResetInvalidation();
}