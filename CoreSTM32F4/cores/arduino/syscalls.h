#pragma once

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef SystemStackSize
# define SystemStackSize	(1024)
#endif

extern char _end;									// defined by the linker script
extern char _estack;

extern const char * const sysStackLimit;

extern char *heapTop;
extern const char *heapLimit;

extern void OutOfMemoryHandler() noexcept;					// this must be provided by the client application

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

extern caddr_t _sbrk( int incr ) ;

extern int link( char *cOld, char *cNew ) ;

extern int _close( int file ) ;

extern int _fstat( int file, struct stat *st ) ;

extern int _isatty( int file ) ;

extern int _lseek( int file, int ptr, int dir ) ;

extern int _read(int file, char *ptr, int len) ;

extern int _write( int file, char *ptr, int len ) ;

#ifdef __cplusplus
}
#endif

