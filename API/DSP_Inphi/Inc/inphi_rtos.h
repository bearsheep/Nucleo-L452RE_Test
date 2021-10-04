/** @file inphi_rtos.h
 ****************************************************************************
 *
 * @brief
 *    This contains all the RTOS(like system calls) and environment      *
 *    related macro's and stub utilities which should be modified or     *
 *    filled in as suited to the customer environment. It is important   *
 *    that this customization or porting of the driver is done BEFORE    *
 *    making any attempt to compile or use the driver.                   *
 *
 ****************************************************************************
 * @author
 *    This file contains information that is proprietary and confidential to
 *    Inphi Corporation.
 *
 *    This file can be used under the terms of the Inphi Software License
 *    Agreement. You should have received a copy of the license with this file,
 *    if not please contact your Inphi support staff.
 *
 *    Copyright (C) 2006-2021 Inphi Corporation, Inc. All rights reserved.
 *
 *    API Version Number: 1.2.0.929
 ****************************************************************************/
#ifndef __INPHI_RTOS_H__
#define __INPHI_RTOS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "inphi_types.h"
#include "inphi_config.h"

#if (defined(_MSC_VER) || defined(__TINYC__)) && !defined(_WINDOWS)
   //We use _WINDOWS to signify tcc or msvc compilers
#  define _WINDOWS
#endif

#if defined(_WINDOWS)
#  include <windows.h>
#endif

// rarely we intentionally want fall-throughs in switch statements
// in C++17 they added a fancy [[fallthrough]] statement which you can use,
// or the non-standard __attribute__((fallthrough)) in gcc/clang
//#define INPHI_FALLTHROUGH __attribute__((fallthrough))
//#define INPHI_FALLTHROUGH [[fallthrough]];
#define INPHI_FALLTHROUGH

/**********************************************************
 *         Input/Output Routines                          *
 **********************************************************/
#ifdef INPHI_DONT_USE_STDLIB
// You can either replace these with non-stdlib versions or remove them entirely
#  define INPHI_FPRINTF(...)
#  define INPHI_FLUSH()
#  define INPHI_FFLUSH(x)
#  define INPHI_PRINTF(...)
#  define INPHI_SNPRINTF(...)
#  define INPHI_STRNCAT(...)
#  define INPHI_NOTE(...)
#  define INPHI_WARN(...)
#  define INPHI_CRIT(...)
#  define INPHI_FN_START(...)
#  define INPHI_RETURN(...) return __VA_ARGS__
#else
/* Include any necessary library files when building the driver */
#  include <stdlib.h>        /* for malloc(), free(), abs() */
#  include <string.h>        /* for memcpy()                */
#  include <stdarg.h>        /* for variable args           */
#  include <stdio.h>         /* for printf variants         */
#  include <time.h>          // For nanosleep
#  include <stddef.h>        // for offsetof
#  if defined(INPHI_HAS_MATH_DOT_H)
#    include <math.h>        // for abs, pow
#  endif// defined(INPHI_HAS_MATH_DOT_H)
#  if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
#   include <float.h>
#  endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
#    define INPHI_PRINTF(...)  printf(__VA_ARGS__); fflush(stdout);
#    define INPHI_FPRINTF(...) fprintf(__VA_ARGS__)
#  define INPHI_FLUSH()   fflush(stdout)
#  define INPHI_FFLUSH(x) fflush(x)
#  define INPHI_STRNCAT(...) strncat(__VA_ARGS__)
#  if !defined(__APPLE__) && !defined(_MSC_VER)
     int snprintf(char* s, size_t n, const char* format, ...);
#  endif /* __APPLE__ */
#  if defined(_MSC_VER)
     //MSVC does things differently...
#    define INPHI_SNPRINTF(...) _snprintf(__VA_ARGS__)
#  else
#    define INPHI_SNPRINTF(...) snprintf(__VA_ARGS__)
#  endif

   //logging functions, based on http://stackoverflow.com/a/1644898
   //To print out a 'note' message
#  define INPHI_NOTE(...) \
      do { if(INPHI_HAS_LOG_NOTE) { \
          INPHI_FPRINTF(stderr, __VA_ARGS__); \
          INPHI_FFLUSH(stderr); \
          } \
      } while(0)
   //To print out a 'warning' message
#  define INPHI_WARN(...) \
      do { if(INPHI_HAS_LOG_WARN) { \
          INPHI_FPRINTF(stderr, "[WARNING]  %s: ", __func__); \
          INPHI_FPRINTF(stderr, __VA_ARGS__); \
          INPHI_FFLUSH(stderr); \
          } \
      } while(0)
          
   //To print out a 'critical' message
#  define INPHI_CRIT(...) \
      do { if(INPHI_HAS_LOG_CRIT) { \
          INPHI_FPRINTF(stderr, "[CRITICAL] %s: ", __func__); \
          INPHI_FPRINTF(stderr, __VA_ARGS__); \
          INPHI_FFLUSH(stderr); \
          } \
      } while(0)

#  if defined(INPHI_HAS_MATH_DOT_H)
//   Must have math.h support to use pow; we don't provide a homebrew version
#    define INPHI_POW(...)  pow(__VA_ARGS__)
#  else
#    define INPHI_POW(...) (0)
#  endif     

#endif /* INPHI_DONT_USE_STDLIB */


/**********************************************************
 *         Timer delay utilities                          *
 **********************************************************/
void INPHI_UDELAY(int usecs);
void INPHI_MDELAY(int msecs);

/**********************************************************
 *         Memory Handling                                *
 **********************************************************/
char *INPHI_STRNCPY(char *dest, const char *source, int count);
void *INPHI_MEMSET(void *dest, int ch, unsigned int count);
void *INPHI_MEMCPY(void *dest, const void *src, unsigned int count);

/**********************************************************
 *         Byte Swapping
 **********************************************************/
uint32_t INPHI_NTOHL(uint32_t data);

/**********************************************************
 *         Other utilities                                *
 **********************************************************/
unsigned int INPHI_ABS(int value);

/**
 * Calculates checksum on src data of given length
 *
 * Checksum is just a simple add and rotate
 *
 * @param src    [I] - Pointer to the source data
 * @param length [I] - Length of source data
 *
 * @return 32bit checksum
 */
uint32_t inphi_checksum(const void *src, unsigned int length);

/* bit masks */
#define INBIT0  0x00000001
#define INBIT1  0x00000002
#define INBIT2  0x00000004
#define INBIT3  0x00000008
#define INBIT4  0x00000010
#define INBIT5  0x00000020
#define INBIT6  0x00000040
#define INBIT7  0x00000080

#define INBIT8  0x00000100
#define INBIT9  0x00000200
#define INBIT10 0x00000400
#define INBIT11 0x00000800
#define INBIT12 0x00001000
#define INBIT13 0x00002000
#define INBIT14 0x00004000
#define INBIT15 0x00008000

#define INBIT16 0x00010000 
#define INBIT17 0x00020000
#define INBIT18 0x00040000
#define INBIT19 0x00080000
#define INBIT20 0x00100000
#define INBIT21 0x00200000
#define INBIT22 0x00400000
#define INBIT23 0x00800000

#define INBIT24 0x01000000
#define INBIT25 0x02000000
#define INBIT26 0x04000000
#define INBIT27 0x08000000
#define INBIT28 0x10000000
#define INBIT29 0x20000000
#define INBIT30 0x40000000
#define INBIT31 0x80000000

/** Use this macro when assigning to a inphi_boolean, 
 * since the inph_boolean is really an unsigned char
 * 
 * @example
 * valid == TRUE iff bit3 OR bit5 is set in reg_val:
 * cs_boolean valid = INPHI_IF_SET(reg_val,INBIT3|INBIT5);
 */
#define INPHI_IF_SET(val,mask) ( ((val) & (mask)) != 0 )

/** True iff all bits in mask are set */
#define INPHI_IF_ALL_SET(val,mask) ( ((val) & (mask)) == mask )

/** True iff all bits in mask are cleared */
#define INPHI_IF_CLR(val,mask) ( ((val) & (mask)) == 0 )

/** Set mask bits in val */
#define INPHI_SET(val,mask) ( ((val) | (mask)) )

/** Clear mask bits in val */
#define INPHI_CLR(val,mask) ( ((val) & ~(mask)) )

/** Toggle mask bits in val */
#define INPHI_TOGGLE(val,mask) ( ((val) ^ (mask)) )


/** Simple define to help stringify enums for translation */
#define INPHI_TRANS_ENUM(value) case value: return #value;

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif /* __INPHI_RTOS_H__ */

