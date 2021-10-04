/** @file inphi_types.h
 ****************************************************************************
 *
 * @brief
 *    This module contains common data types and defines used by
 *    the driver.
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
#ifndef __INPHI_TYPES_H__
#define __INPHI_TYPES_H__

#ifdef __cplusplus
//for the PRIu64 macros in g++
#define __STDC_FORMAT_MACROS
#endif //__cplusplus
#include <inttypes.h>
#include <stdint.h>

#if defined(_MSC_VER)
   //be careful when using these, as if(int == true) will not work if int > 1
#  define false   0
#  define true    1
#  define bool int
#else
#  include <stdbool.h>
#endif

/*
 * Basic data types
 */
typedef int32_t inphi_status_t;


#ifndef __LINE__
#   define __LINE__ 0
#endif
#ifndef __FILE__
#   define __FILE__ "<unknown>"
#endif

#ifdef _MSC_VER
   //MSVC doesn't support __func__
#  define __func__ __FUNCTION__
#endif

/*
 * Other defines
 */
#define INPHI_OK           0
#define INPHI_ERROR        -1

#ifndef NULL
#  define NULL            0
#endif

#endif /* __INPHI_TYPES_H__ */

