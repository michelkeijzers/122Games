#ifdef WIN32

#pragma once

#include <string>

class ArduinoStringStub : public std::string
{
public:
	ArduinoStringStub();

	ArduinoStringStub(const char* str);

	void toCharArray(const char* buffer, int length);

	int toInt();
};

#endif
