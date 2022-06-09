#ifdef WIN32

#include "ArduinoStringStub.h"

ArduinoStringStub::ArduinoStringStub()
{
}


ArduinoStringStub::ArduinoStringStub(const char* str)
{
	(void)str;
}


void ArduinoStringStub::toCharArray(const char* buffer, int length)
{
	(void)buffer;
	(void)length;
}


int ArduinoStringStub::toInt()
{
	return 0;
}

#endif // WIN32
