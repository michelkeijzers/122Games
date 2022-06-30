#ifdef WIN32

#pragma once

#include "ClassNames.h"
#include "ArduinoStub.h"
#include "ArduinoStringStub.h"

#include "Print.h"

class SerialClass : public Print
{
public:
	SerialClass();

	void begin(int baudrate);

	/* override */ size_t write(uint8_t character);

	/*
	size_t println();
	size_t println(const char* str);
	size_t println(ArduinoStringStub str);
	size_t println(char value);
	size_t println(unsigned int value);
	size_t println(int value);
	size_t println(int value, int mode);
	size_t println(float value);

	size_t print();
	size_t print(const char* str);
	size_t print(ArduinoStringStub str);
	size_t print(char value);
	size_t print(unsigned int value);
	size_t print(int value);
	size_t print(int value, int mode);
	size_t print(float value);
	*/

	size_t printf(ArduinoStringStub str, int arg1 = NULL, const char* arg2 = NULL);
	static void flush();

private:
	wchar_t _message[256];
	wchar_t _string[256];
};


class SerialPort
{
public:
	SerialPort() {};
};

extern SerialClass Serial;
extern SerialClass Serial1;
extern SerialClass Serial2;
//extern SerialClass Serial3;

extern SerialPort SoftwareSerial;
extern SerialPort HardwareSerial;

#endif // WINDOWS