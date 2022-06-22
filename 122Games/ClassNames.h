// ClassNames.h

#pragma once

// Used to include variable class names
#define stringify(x) #x
#define HEADER_FILE(a) stringify(a.h)

// Class names
#ifdef _WINDOWS

#define ARDUINO_CLASS				ArduinoStub
#define ASYNC_TCP_CLASS             AsyncTcpStub
#define DALLAS_TEMPERATURE_CLASS    DallasTemperatureStub
#define ESP_ASYNC_WEB_SERVER_CLASS  EspAsyncWebServerStub
#define FAST_LED_CLASS              FastLedStub
#define MAX_7219_CLASS              MAX7219Stub
#define ONE_WIRE_CLASS              OneWireStub
#define SERIAL_CLASS				SerialStub
#define TM1637_DISPLAY_CLASS        TM1637DisplayStub
#define TONE_CLASS                  ToneStub
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
#define FAST_LED_CLASS              FastLed
#define MAX_7219_CLASS              MAX7219
#define ONE_WIRE_CLASS              OneWire
#define SERIAL_CLASS				Arduino
#define TM1637_DISPLAY_CLASS        TM1637Display
#define TONE_CLASS                  Tone
#define WEB_SERVER_CLASS            WebServer
#define WIFI_CLASS                  WiFi

#endif // _WINDOWS
