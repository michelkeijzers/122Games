#ifdef _WIN32

#pragma once

// Copied from https://github.com/arduino/ArduinoCore-avr/blob/master/cores/arduino/Print.cpp
// Used by LiquidCrystalI2c(Stub).

/*
  Print.h - Base class that provides print() and println()
  Copyright (c) 2008 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <inttypes.h>
#include <stdio.h> // for size_t
#include <string.h>

constexpr auto DEC = 10;
constexpr auto HEX = 16;
constexpr auto OCT = 8;
constexpr auto BIN = 8;

class Print
{
private:
    int write_error;
    size_t printNumber(unsigned long, uint8_t);
    size_t printFloat(double, uint8_t);

protected:
    void setWriteError(int err = 1) { write_error = err; }

public:
    Print()
    : write_error(0) 
    {
    }


    int getWriteError()
    {
        return write_error; 
    }
    
    
    void clearWriteError()
    {
        setWriteError(0); 
    }


    virtual size_t write(uint8_t character) = 0;
    

    size_t write(const char* str)
    {
        if (str == NULL)
        {
            return 0;
        }
        return write((const uint8_t*)str, strlen(str));
    }
    

    virtual size_t write(const uint8_t* buffer, size_t size);
    

    size_t write(const char* buffer, size_t size) 
    {
        return write((const uint8_t*)buffer, size);
    }

    // default to zero, meaning "a single write may block"
    // should be overridden by subclasses with buffering
    virtual int availableForWrite() 
    {
        return 0; 
    }


    // size_t print(const __FlashStringHelper*); // Not implemented
    // size_t print(const String&); // Not implemented
    virtual size_t print(const char[]);
    virtual size_t print(char);
    virtual size_t print(unsigned char, int = DEC);
    virtual size_t print(int, int = DEC);
    virtual size_t print(unsigned int, int = DEC);
    virtual size_t print(long, int = DEC);
    virtual size_t print(unsigned long, int = DEC);
    virtual size_t print(double, int = 2);
    // size_t print(const Printable&); // Not implemented

    // size_t println(const __FlashStringHelper*); // Not implemented
    // size_t println(const String& s); // Not implemented
    virtual size_t println(const char[]);
    virtual size_t println(char);
    virtual size_t println(unsigned char, int = DEC);
    virtual size_t println(int, int = DEC);
    virtual size_t println(unsigned int, int = DEC);
    virtual size_t println(long, int = DEC);
    virtual size_t println(unsigned long, int = DEC);
    virtual size_t println(double, int = 2);
    // size_t println(const Printable&); // Not implemented 
    virtual size_t println(void);

    virtual void flush() { /* Empty implementation for backward compatibility */ }
};

#endif // WIN32
