/*
 WCharacter.h - Character utility functions for Wiring & Arduino
 Copyright (c) 2010 Hernando Barragan.  All right reserved.

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

#ifndef Character_h
#define Character_h

#include <ctype.h>

#ifdef __cplusplus
extern "C" {
#endif

// WCharacter.h prototypes
#if defined (  __GNUC__  )
inline boolean isAlphaNumeric(int c) noexcept __attribute__((always_inline));
inline boolean isAlpha(int c) noexcept __attribute__((always_inline));
inline boolean isAscii(int c) noexcept __attribute__((always_inline));
inline boolean isWhitespace(int c) noexcept __attribute__((always_inline));
inline boolean isControl(int c) noexcept __attribute__((always_inline));
inline boolean isDigit(int c) noexcept __attribute__((always_inline));
inline boolean isGraph(int c) noexcept __attribute__((always_inline));
inline boolean isLowerCase(int c) noexcept __attribute__((always_inline));
inline boolean isPrintable(int c) noexcept __attribute__((always_inline));
inline boolean isPunct(int c) noexcept __attribute__((always_inline));
inline boolean isSpace(int c) noexcept __attribute__((always_inline));
inline boolean isUpperCase(int c) noexcept __attribute__((always_inline));
inline boolean isHexadecimalDigit(int c) noexcept __attribute__((always_inline));
inline int toAscii(int c) noexcept __attribute__((always_inline));
inline int toLowerCase(int c) noexcept __attribute__((always_inline));
inline int toUpperCase(int c) noexcept __attribute__((always_inline));
#elif defined ( __ICCARM__ )
#endif

// Checks for an alphanumeric character.
// It is equivalent to (isalpha(c) || isdigit(c)).
inline boolean isAlphaNumeric(int c) noexcept
{
  return ( isalnum(c) == 0 ? false : true);
}


// Checks for an alphabetic character.
// It is equivalent to (isupper(c) || islower(c)).
inline boolean isAlpha(int c) noexcept
{
  return ( isalpha(c) == 0 ? false : true);
}


// Checks whether c is a 7-bit unsigned char value
// that fits into the ASCII character set.
inline boolean isAscii(int c) noexcept
{
/*  return ( isascii(c) == 0 ? false : true); */
  return ( (c & ~0x7f) != 0 ? false : true);
}


// Checks for a blank character, that is, a space or a tab.
inline boolean isWhitespace(int c) noexcept
{
  return ( isblank (c) == 0 ? false : true);
}


// Checks for a control character.
inline boolean isControl(int c) noexcept
{
  return ( iscntrl (c) == 0 ? false : true);
}


// Checks for a digit (0 through 9).
inline boolean isDigit(int c) noexcept
{
  return ( isdigit (c) == 0 ? false : true);
}


// Checks for any printable character except space.
inline boolean isGraph(int c) noexcept
{
  return ( isgraph (c) == 0 ? false : true);
}


// Checks for a lower-case character.
inline boolean isLowerCase(int c) noexcept
{
  return (islower (c) == 0 ? false : true);
}


// Checks for any printable character including space.
inline boolean isPrintable(int c) noexcept
{
  return ( isprint (c) == 0 ? false : true);
}


// Checks for any printable character which is not a space
// or an alphanumeric character.
inline boolean isPunct(int c) noexcept
{
  return ( ispunct (c) == 0 ? false : true);
}


// Checks for white-space characters. For the avr-libc library,
// these are: space, formfeed ('\f'), newline ('\n'), carriage
// return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
inline boolean isSpace(int c) noexcept
{
  return ( isspace (c) == 0 ? false : true);
}


// Checks for an uppercase letter.
inline boolean isUpperCase(int c) noexcept
{
  return ( isupper (c) == 0 ? false : true);
}


// Checks for a hexadecimal digits, i.e. one of 0 1 2 3 4 5 6 7
// 8 9 a b c d e f A B C D E F.
inline boolean isHexadecimalDigit(int c) noexcept
{
  return ( isxdigit (c) == 0 ? false : true);
}


// Converts c to a 7-bit unsigned char value that fits into the
// ASCII character set, by clearing the high-order bits.
inline int toAscii(int c) noexcept
{
/*  return toascii (c); */
  return (c & 0x7f);
}


// Warning:
// Many people will be unhappy if you use this function.
// This function will convert accented letters into random
// characters.

// Converts the letter c to lower case, if possible.
inline int toLowerCase(int c) noexcept
{
  return tolower (c);
}


// Converts the letter c to upper case, if possible.
inline int toUpperCase(int c) noexcept
{
  return toupper (c);
}

#ifdef __cplusplus
}
#endif

#endif
