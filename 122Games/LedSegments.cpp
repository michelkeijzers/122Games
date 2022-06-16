#include "LedSegments.h"

#include <stdlib.h>

#include "ClassNames.h"
#include HEADER_FILE(MAX_7219_CLASS)

LedSegments::LedSegments()
{
	_max7219 = new MAX_7219_CLASS();
}


LedSegments::~LedSegments()
{
	if (_max7219 != nullptr)
	{
		delete _max7219;
	}
}


void LedSegments::Initialize()
{
}


int LedSegments::GetValue()
{
	return _max7219->STUB_GetDisplayedValue();
}

void LedSegments::SetValue(int value)
{
	char buffer[5];
	_itoa_s(value, (char*) &buffer, 5, 10);
	_max7219->DisplayText((char*)buffer, true);
}


MAX_7219_CLASS* LedSegments::GetMax7219()
{
	return _max7219;
}