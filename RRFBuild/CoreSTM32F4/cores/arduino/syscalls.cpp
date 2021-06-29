/**
  * \file syscalls_stm32.c
  *
  * Implementation of newlib syscall.
  *
  */

#include "stm32_def.h"
#if defined (  __GNUC__  ) /* GCC CS3 */
#include <sys/stat.h>
#endif
#include "Core.h"
#include <errno.h>
#include "syscalls.h"
#undef errno
extern int errno;

extern char _estack;
const char * const sysStackLimit = &_estack - SystemStackSize;
const char *heapLimit = (char*)&_estack - SystemStackSize;

extern size_t uart_debug_write(uint8_t *data, uint32_t size);

// Helper macro to mark unused parameters and prevent compiler warnings.
// Appends _UNUSED to the variable name to prevent accidentally using them.
#ifdef UNUSED
#undef UNUSED
#endif
#ifdef __GNUC__
#define UNUSED(x) x ## _UNUSED __attribute__((__unused__))
#else
#define UNUSED(x) x ## _UNUSED
#endif

void OutOfMemoryHandler() noexcept;

char *heapTop = (char *)&_end;

extern "C" __attribute__((weak)) caddr_t _sbrk(ptrdiff_t incr) noexcept
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

extern "C" __attribute__((weak)) int _close(UNUSED(int file))
{
  return -1;
}

extern "C" __attribute__((weak)) int _fstat(UNUSED(int file), struct stat *st)
{
  st->st_mode = S_IFCHR ;
  return 0;
}

extern "C" __attribute__((weak)) int _isatty(UNUSED(int file))
{
  return 1;
}

extern "C" __attribute__((weak)) int _lseek(UNUSED(int file), UNUSED(int ptr), UNUSED(int dir))
{
  return 0;
}

extern "C" __attribute__((weak)) int _read(UNUSED(int file), UNUSED(char *ptr), UNUSED(int len))
{
  return 0;
}

extern "C" __attribute__((weak)) int _write(UNUSED(int file), char *ptr, int len)
{
#ifdef HAL_UART_MODULE_ENABLED
  return uart_debug_write((uint8_t *)ptr, (uint32_t)len);
#else
  (void)ptr;
  return len;
#endif
}

extern "C" __attribute__((weak)) void _exit(UNUSED(int status))
{
  for (; ;) ;
}

extern "C" __attribute__((weak)) int _kill(UNUSED(int pid), UNUSED(int sig))
{
  errno = EINVAL;
  return -1;
}

extern "C" __attribute__((weak)) int _getpid(void)
{
  return 1;
}
