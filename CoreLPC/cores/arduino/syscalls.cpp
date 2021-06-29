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

/**
  * \file syscalls.cpp
  *
  * Implementation of newlib syscall.
  *
  */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/


#include "syscalls.h"
#include "Core.h"
#include <stdio.h>
#include <stdarg.h>
#if defined (  __GNUC__  ) /* GCC CS3 */
  #include <sys/types.h>
  #include <sys/stat.h>
#endif

// Helper macro to mark unused parameters and prevent compiler warnings.
// Appends _UNUSED to the variable name to prevent accidentally using them.
#undef UNUSED
#ifdef __GNUC__
#  define UNUSED(x) x ## _UNUSED __attribute__((__unused__))
#else
#  define UNUSED(x) x ## _UNUSED
#endif
#include <errno.h>
/*----------------------------------------------------------------------------
 *        Exported variables
 *----------------------------------------------------------------------------*/

#undef errno
int errno = 0;
const char * const sysStackLimit = &_estack - SystemStackSize;
const char *heapLimit = (char*)&_estack - SystemStackSize;
/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void OutOfMemoryHandler() noexcept;

char *heapTop = (char *)&_end;


/**
 * \brief Replacement of C library of _sbrk
 */
extern "C" caddr_t _sbrk(ptrdiff_t incr) noexcept
{
	char *newHeap = heapTop + incr;
	if (newHeap <= heapLimit)
	{
		void *prev_heap = heapTop;
		heapTop = newHeap;
		return (caddr_t) prev_heap;
	}

	OutOfMemoryHandler();

	// The out of memory handle usually terminates, but in case it doesn't, try to return failure. Unfortunately, this doesn't seem to work with newlib.
	errno = ENOMEM;
	return (caddr_t)(-1);
}

extern "C" int link( UNUSED(char *cOld), UNUSED(char *cNew) )
{
    return -1 ;
}

extern "C" int _close( UNUSED(int file) )
{
    return -1 ;
}

extern "C" int _fstat( UNUSED(int file), struct stat *st )
{
    st->st_mode = S_IFCHR ;
    return 0 ;
}

extern "C" int _isatty( UNUSED(int file) )
{
    return 1 ;
}

extern "C" int _lseek( UNUSED(int file), UNUSED(int ptr), UNUSED(int dir) )
{
    return 0 ;
}

extern "C" int _read(UNUSED(int file), UNUSED(char *ptr), UNUSED(int len) )
{
    return 0 ;
}

extern "C" int _write( UNUSED(int file), char *ptr, int len )
{
	return len;
}

extern "C" void _exit( int status )
{
	for ( ; ; ) ;
}

extern "C" void _kill( UNUSED(int pid), UNUSED(int sig) )
{
    return ;
}

extern "C" int _getpid ( void )
{
    return -1 ;
}

// End
