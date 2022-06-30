#pragma once

// https://github.com/JemRF/max7219/blob/master/Examples/HelloWorld/HelloWorld.ino


#ifdef WIN32
#include <cstdint>
#else
#include <stdint.h>
#endif // WIN32

#include "ClassNames.h"
class MAX_7219_CLASS;


class LedSegments
{
public:
	LedSegments();
	~LedSegments();

	void Initialize();

#ifdef WIN32
	int GetValue();
#endif //WIN32

	void SetValue(int score);

	MAX_7219_CLASS* GetMax7219();

private:
	MAX_7219_CLASS* _max7219;
};

