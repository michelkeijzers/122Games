#ifdef WIN32

#include "SerialStub.h"
#include "Windows.h"
#include "stdio.h"


SerialClass Serial;
SerialPort SoftwareSerial;
SerialPort HardwareSerial;

SerialClass::SerialClass()
  : _message{},
	_string{}
{
}

void SerialClass::begin(int baudrate)
{
	static_cast<int>(baudrate);
}


/* override */ size_t SerialClass::write(uint8_t character)
{
	size_t size;
	char text[] = { (char) character, '\0' };
	wchar_t wtext[2];
	mbstowcs_s(&size, wtext, text, 2);
	OutputDebugString(wtext);
	return 1;
}


/*
size_t SerialClass::println()
{
	OutputDebugString(L"\n");
	return 0;
}


size_t SerialClass::println(const char* str)
{
	size_t sizet;
	mbstowcs_s(&sizet, _string, str, strlen(str) + 1);
	swprintf_s(_message, L"%s\n", _string);
	OutputDebugString(_message);
	return strlen(str);
}


size_t SerialClass::println(ArduinoStringStub str)
{
	println(str.c_str());
	return str.length();
}


size_t SerialClass::println(char value)
{
	swprintf_s(_message, L"%c\n", value);
	OutputDebugString(_message);
	return lstrlen(_message);
}


size_t SerialClass::println(int value, int mode)
{
	(void)mode;

	swprintf_s(_message, L"%d\n", value);
	OutputDebugString(_message);
	return lstrlen(_message);
}



size_t SerialClass::println(unsigned int value)
{
	return println(value, DEC);
}


size_t SerialClass::println(int value)
{
	return println(value, DEC);
}


size_t SerialClass::println(float value)
{
	swprintf_s(_message, L"%f\n", value);
	OutputDebugString(_message);
	return lstrlen(_message);
}


size_t SerialClass::print()
{
	swprintf_s(_message, L"");
	OutputDebugString(_message);
	return lstrlen(_message);
}


size_t SerialClass::print(const char* str)
{
	size_t sizet;
	mbstowcs_s(&sizet, _string, str, strlen(str) + 1);
	swprintf_s(_message, L"%s", _string);
	OutputDebugString(_message);
	return lstrlen(_message);
}


size_t SerialClass::print(ArduinoStringStub str)
{
	return print(str.c_str());
}


size_t SerialClass::print(int value, int mode)
{
	(void)mode;

	swprintf_s(_message, L"%d", value);
	OutputDebugString(_message);
	return lstrlen(_message);
}


size_t SerialClass::print(char value)
{
	swprintf_s(_message, L"%c", value);
	OutputDebugString(_message);
	return lstrlen(_message);
}


size_t SerialClass::print(unsigned int value)
{
	return print(value, DEC);
}


size_t SerialClass::print(int value)
{
	return print(value, DEC);
}


size_t SerialClass::print(float value)
{
	swprintf_s(_message, L"%f", value);
	OutputDebugString(_message);
	return lstrlen(_message);
}
*/

size_t SerialClass::printf(
	ArduinoStringStub str, int arg1 /* = NULL */, const char* arg2 /* = NULL */)
{
	(void) arg1;
	(void) arg2;
	return print(str.c_str());
}


void SerialClass::flush()
{
}

#endif // WIN32
