/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _WIRING_MATH_
#define _WIRING_MATH_

#include <stdint.h>
//#include <compiler.h>

#ifdef __cplusplus
extern "C" uint32_t random32() noexcept;
#else
extern uint32_t random32() noexcept;
#endif

#ifdef __cplusplus

#include <cmath>

// std::min and std::max don't seem to work with this variant of gcc, so define our own ones here
// We use these only with primitive types, so pass them directly instead of by const reference
#ifdef min
# undef min
#endif

#ifdef max
# undef max
#endif

// We need to use "extern C++" here so that it compiles even if this file was #included inside an "extern C" block
extern "C++" {

	inline bool Xor(bool a, bool b) noexcept
	{
		return (a) ? !b : b;
	}

	inline bool XNor(bool a, bool b) noexcept
	{
		return (a) ? b : !b;
	}

	inline int32_t random(int32_t howbig) noexcept
	{
		return random32() % howbig;
	}

	extern int32_t random(int32_t, int32_t) noexcept;

	template<class X> inline constexpr X min(X _a, X _b) noexcept
	{
		return (_a < _b) ? _a : _b;
	}

	template<class X> inline constexpr X max(X _a, X _b) noexcept
	{
		return (_a > _b) ? _a : _b;
	}

	// Specialisations for float and double to handle NaNs properly
	template<> inline constexpr float min(float _a, float _b) noexcept
	{
		return (std::isnan(_a) || _a < _b) ? _a : _b;
	}

	template<> inline constexpr float max(float _a, float _b) noexcept
	{
		return (std::isnan(_a) || _a > _b) ? _a : _b;
	}

	template<> inline constexpr double min(double _a, double _b) noexcept
	{
		return (std::isnan(_a) || _a < _b) ? _a : _b;
	}

	template<> inline constexpr double max(double _a, double _b) noexcept
	{
		return (std::isnan(_a) || _a > _b) ? _a : _b;
	}

	// Note that constrain<float> will return NaN for a NaN input because of the way we define min<float> and max<float>
	template<class T> inline constexpr T constrain(T val, T vmin, T vmax) noexcept
	{
		return max<T>(min<T>(val, vmax), vmin);
	}

	inline constexpr float fsquare(float arg) noexcept
	{
		return arg * arg;
	}

	inline constexpr double dsquare(double arg) noexcept
	{
		return arg * arg;
	}

	inline constexpr uint64_t isquare64(int32_t arg) noexcept
	{
		return (uint64_t)((int64_t)arg * arg);
	}

	inline constexpr uint64_t isquare64(uint32_t arg) noexcept
	{
		return (uint64_t)arg * arg;
	}

	// Find the lowest set bit. Returns the lowest set bit number, undefined if no bits are set.
	// GCC provides intrinsics, but unhelpfully they are in terms of int, long and long long instead of uint32_t, uint64_t etc.
	inline unsigned int LowestSetBitNumber(unsigned int val) noexcept
	{
		return (unsigned int)__builtin_ctz(val);
	}

	inline unsigned int LowestSetBitNumber(unsigned long val) noexcept
	{
		return (unsigned int)__builtin_ctzl(val);
	}

	inline unsigned int LowestSetBitNumber(unsigned long long val) noexcept
	{
		return (unsigned int)__builtin_ctzll(val);
	}
}

#endif

// Macro to give us the number of elements in an array
#define ARRAY_SIZE(_x)	(sizeof(_x)/sizeof(_x[0]))

// Macro to give us the highest valid index into an array i.e. one less than the size
#define ARRAY_UPB(_x)	(ARRAY_SIZE(_x) - 1)

#endif /* _WIRING_MATH_ */
