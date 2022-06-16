#pragma once
#include <cstdint>

#include "ClassNames.h"
class MAX_7219_CLASS;

// https://github.com/JemRF/max7219/blob/master/Examples/HelloWorld/HelloWorld.ino

class LedSegments
{
public:
	LedSegments();
	~LedSegments();

	void Initialize();

	int GetValue();
	void SetValue(int score);

	MAX_7219_CLASS* GetMax7219();

private:
	MAX_7219_CLASS* _max7219;
};

