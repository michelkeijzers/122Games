// ClassNames.h

#pragma once

// Used to include variable class names
#define stringify(x) #x
#define HEADER_FILE(a) stringify(a.h)

// Class names
#ifdef WIN32

#define ARDUINO_CLASS				ArduinoStub
#define ASYNC_TCP_CLASS             AsyncTcpStub
#define DALLAS_TEMPERATURE_CLASS    DallasTemperatureStub
#define ESP_ASYNC_WEB_SERVER_CLASS  EspAsyncWebServerStub
#define ONE_WIRE_CLASS              OneWireStub
#define SERIAL_CLASS				SerialStub
#define WEB_SERVER_CLASS            WebServerStub
#define WIFI_CLASS                  WiFiStub

#else // NON _WINDOWS

#define GPIO_INPUT                  INPUT
#define STRING String

#define strcpy_s(d,d_sz,s)			strcpy(d, s);
#define strcpy_s(d, s)				strcpy(d, s)
#define sprintf_s                   sprintf

#define ABS							abs
#define MIN(a,b)					(((a)<(b))?(a):(b))
#define MAX(a,b)					(((a)>(b))?(a):(b))
#define FastLedCRGB					CRGB

#define ARDUINO_CLASS				Arduino
#define ASYNC_TCP_CLASS             AsyncTCP
#define DALLAS_TEMPERATURE_CLASS    DallasTemperature
#define ESP_ASYNC_WEB_SERVER_CLASS  ESPAsyncWebServer
#define ONE_WIRE_CLASS              OneWire
#define SERIAL_CLASS				Arduino
#define WEB_SERVER_CLASS            WebServer
#define WIFI_CLASS                  WiFi

#endif // _WINDOWS
