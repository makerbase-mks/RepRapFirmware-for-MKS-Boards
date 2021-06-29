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

#ifndef Print_h
#define Print_h

#include <inttypes.h>
#include <stdio.h> // for size_t
#include <string.h>

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

class Print
{
private:
	int write_error;
	size_t printNumber(unsigned long, uint8_t) noexcept;
	size_t printFloat(double, uint8_t) noexcept;

protected:
	void setWriteError(int err = 1) noexcept { write_error = err; }

public:
    Print() noexcept : write_error(0) {}
    virtual ~Print() {}

    int getWriteError() noexcept { return write_error; }
    void clearWriteError() noexcept { setWriteError(0); }

    virtual size_t write(uint8_t) noexcept = 0;

    size_t write(const char *str) noexcept
    {
    	return (str == NULL) ? 0 : write((const uint8_t *)str, strlen(str));
    }

    virtual size_t write(const uint8_t *buffer, size_t size) noexcept;

    size_t write(const char *buffer, size_t size) noexcept
    {
    	return write((const uint8_t *)buffer, size);
    }

    size_t print(const char[]) noexcept;
    size_t print(char) noexcept;
    size_t print(unsigned char, int = DEC) noexcept;
    size_t print(int, int = DEC) noexcept;
    size_t print(unsigned int, int = DEC) noexcept;
    size_t print(long, int = DEC) noexcept;
    size_t print(unsigned long, int = DEC) noexcept;
    size_t print(double, int = 2) noexcept;

    size_t println(const char[]) noexcept;
    size_t println(char) noexcept;
    size_t println(unsigned char, int = DEC) noexcept;
    size_t println(int, int = DEC) noexcept;
    size_t println(unsigned int, int = DEC) noexcept;
    size_t println(long, int = DEC) noexcept;
    size_t println(unsigned long, int = DEC) noexcept;
    size_t println(double, int = 2) noexcept;
    size_t println(void) noexcept;
};

#endif
