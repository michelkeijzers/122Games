#ifdef WIN32

#include "SerialStub.h"
#include "Windows.h"
#include "stdio.h"


SerialClass Serial;
SerialPort SoftwareSerial;
SerialPort HardwareSerial;

void SerialClass::begin(int baudrate)
{
	static_cast<int>(baudrate);
}


void SerialClass::println()
{
	OutputDebugString(L"\n");
}


void SerialClass::println(const char* str)
{
	size_t sizet;
	mbstowcs_s(&sizet, _string, str, strlen(str) + 1);
	swprintf_s(_message, L"%s\n", _string);
	OutputDebugString(_message);
}


void SerialClass::println(ArduinoStringStub str)
{
	println(str.c_str());
}


void SerialClass::println(char value)
{
	swprintf_s(_message, L"%c\n", value);
	OutputDebugString(_message);
}


void SerialClass::println(int value, int mode)
{
	(void)mode;

	swprintf_s(_message, L"%d\n", value);
	OutputDebugString(_message);
}



void SerialClass::println(unsigned int value)
{
	println(value, DEC);
}


void SerialClass::println(int value)
{
	println(value, DEC);
}


void SerialClass::println(float value)
{
	swprintf_s(_message, L"%f\n", value);
	OutputDebugString(_message);
}


void SerialClass::print()
{
	swprintf_s(_message, L"");
	OutputDebugString(_message);
}


void SerialClass::print(const char* str)
{
	size_t sizet;
	mbstowcs_s(&sizet, _string, str, strlen(str) + 1);
	swprintf_s(_message, L"%s", _string);
	OutputDebugString(_message);
}


void SerialClass::print(ArduinoStringStub str)
{
	print(str.c_str());
}


void SerialClass::print(int value, int mode)
{
	(void)mode;

	swprintf_s(_message, L"%d", value);
	OutputDebugString(_message);
}


void SerialClass::print(char value)
{
	swprintf_s(_message, L"%c", value);
	OutputDebugString(_message);
}


void SerialClass::print(unsigned int value)
{
	print(value, DEC);
}


void SerialClass::print(int value)
{
	print(value, DEC);
}


void SerialClass::print(float value)
{
	swprintf_s(_message, L"%f", value);
	OutputDebugString(_message);
}


void SerialClass::printf(ArduinoStringStub str, int arg1 /* = NULL */, const char* arg2 /* = NULL */)
{
	(void) arg1;
	(void) arg2;
	print(str.c_str());
}


void SerialClass::flush()
{
}

#endif // _WINDOWS
