/** @file inphi_rtos.c
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
 *  * @author
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
#include "inphi_rtos.h"


#if defined(_WINDOWS)
int usleep(unsigned int usec)
{
    LARGE_INTEGER cur;    // The current timer value
    LARGE_INTEGER end;    // When we stop looping
    LARGE_INTEGER res;    // The resolution of the timer

    /* If we are sleeping in msec then use Sleep() (not as accurate but less CPU heavy).  Also if there is
       no performance timer available then fall back to this */
    if(usec>1000 || QueryPerformanceFrequency(&res)==0)
    {
        Sleep(usec/1000);
    }
    else
    {
        QueryPerformanceCounter(&cur);
        end.QuadPart=cur.QuadPart+res.QuadPart*usec/1000000;
        do
        {
            QueryPerformanceCounter(&cur);
        } while(cur.QuadPart<end.QuadPart);
    }

    return 0;
}
#else
#include <unistd.h>
int usleep(uint32_t usec);
#endif


void INPHI_UDELAY(int usecs)
{
#ifdef INPHI_DONT_USE_STDLIB
    #error "TO DO: Cannot compile without defining CS_UDELAY() for your system in platform/inphi_rtos.c"
#else
    usleep(usecs);
#endif
}

void INPHI_MDELAY(int msecs)
{
    INPHI_UDELAY(msecs * 1000);
}

char *INPHI_STRNCPY(char *dest, const char *source, int count)
{
  char *start = dest;

  while (count && (*dest++ = *source++)) count--;
  if (count) while (--count) *dest++ = '\0';
  return start;
}

/* Calc simple 32bit checksum on src data */
uint32_t inphi_checksum(const void *src, unsigned int size)
{
    const uint8_t *s_ptr = (const uint8_t*)src;
    const uint8_t *end = s_ptr + size;
    uint32_t cksum = 0;

    for(; s_ptr < end; s_ptr++) {
        cksum = (cksum >> 1) | (cksum << (32 - 1));
        cksum += *s_ptr;
    }
    return cksum;
}

void *INPHI_MEMSET(void *dest, int ch, unsigned int count)
{
#ifdef INPHI_DONT_USE_STDLIB
    unsigned char *pb = (unsigned char *)dest;
    unsigned char *pbend = pb + count;
    unsigned char val = (unsigned char)ch;
    while (pb != pbend) *pb++ = val;
    return dest;
#else
    return memset(dest, ch, count);
#endif
}

void *INPHI_MEMCPY(void *dest, const void *src, unsigned int count)
{
#ifdef INPHI_DONT_USE_STDLIB
  char *d = dest;
  const char *s = src;
  while (count--)
    *d++ = *s++;
  return dest;
#else
    return memcpy(dest, src, count);
#endif
}


unsigned int INPHI_ABS(int value)
{
#ifdef INPHI_DONT_USE_STDLIB
    return (unsigned int) (value < 0 ? -value : value);
#else
    return (unsigned int) abs(value);
#endif
}



#ifndef INPHI_DONT_USE_STDLIB
#    if !defined(_WINDOWS) && !defined(_WIN32) && !defined(_WIN64)
#        include <arpa/inet.h> /* for ntohs, htons            */
#    endif
#endif

uint32_t INPHI_NTOHL(uint32_t data)
{
#if defined(INPHI_DONT_USE_STDLIB) || defined(_WINDOWS)
    // Platform independent ntohl
    uint8_t *datap = (uint8_t*)&data;
    return ((uint32_t)datap[0] << 24) |
           ((uint32_t)datap[1] << 16) |
           ((uint32_t)datap[2] << 8)  |
           ((uint32_t)datap[3]);
#else
    return ntohl(data);
#endif
}


