/*
 * SafeVsnprintf.h
 *
 *  Created on: 8 Apr 2018
 *      Author: David
 */

#ifndef SRC_LIBRARIES_GENERAL_SAFEVSNPRINTF_H_
#define SRC_LIBRARIES_GENERAL_SAFEVSNPRINTF_H_

#include <cstdarg>
#include <cstddef>
#include <functional>

// These functions are like vprintf and printf but each character to print is sent through a function
// The putc function must behave as follows:
// If the character passed is not zero: if possible, send or store the character and return true; else store a terminator if necessary and return false to terminate the vuprintf call.
// If the character passed is zero, this signals the last character being printed at this time, so store a terminator if necessary. The return value is unimportant.
// NOTE: whenever a format specifier of exactly "%.s" is encountered, the string argument is JSON-escaped.
int vuprintf(std::function<bool(char) /*noexcept*/ > putc, const char *format, va_list args) noexcept;
int uprintf(std::function<bool(char) /*noexcept*/ > putc, const char *format, ...) noexcept __attribute__ ((format (printf, 2, 3)));

int SafeVsnprintf(char *buffer, size_t maxLen, const char *format, va_list args) noexcept;
int SafeSnprintf(char* buffer, size_t maxLen, const char* format, ...) noexcept __attribute__ ((format (printf, 3, 4)));

// We must define these after including <functional> because that file refers to vsnprintf
#define vsnprintf(b, m, f, a) static_assert(false, "Do not use vsnprintf, use SafeVsnprintf instead")
#define snprintf(b, m, f, ...) static_assert(false, "Do not use snprintf, use SafeSnprintf instead")

#endif /* SRC_LIBRARIES_GENERAL_SAFEVSNPRINTF_H_ */
