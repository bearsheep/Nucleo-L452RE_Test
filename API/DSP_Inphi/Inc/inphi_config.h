/** @file inphi_config.h
 ****************************************************************************
 *
 * @brief
 *     This module allows individual features in the API to be compiled
 *     in or out to manage code space.
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
 ***************************************************************************/
#ifndef __INPHI_CONFIG_H__
#define __INPHI_CONFIG_H__

#undef INPHI_HAS_FLOATING_POINT

// Set to 1 if to bundle the application firmware with
// the API for programming via vega_mcu_download_firmware()
#define INPHI_HAS_INLINE_APP_FW        1
#define INPHI_HAS_INLINE_BOOTLOADER_FW 1       

// Set to 1 if you want to include support for downloading
// the firmware directly to the IRAM/DRAM 
#define INPHI_HAS_DIRECT_DOWNLOAD      1

// Set to 1 if you want to reduce the code size by removing
// support for the PMR interface
// Note that only one of INPHI_REMOVE_PMR or INPHI_REMOVE_PSR flags
// can be defined at one time.
// #define INPHI_REMOVE_PMR           1

// Set to 1 if you want to reduce the code size by removing
// support for the PSR interface
// Note that only one of INPHI_REMOVE_PMR or INPHI_REMOVE_PSR flags
// can be defined at one time.
// #define INPHI_REMOVE_PSR           1

#if defined(INPHI_REMOVE_PMR) && defined(INPHI_REMOVE_PSR)
    // Throw a fatal compile error here...
    #error "Compile flags INPHI_REMOVE_PMR and INPHI_REMOVE_PSR cannot both be defined"
#endif

// Set to 1 to include support for displaying diagnostic dumps
// This would only be useful on systems with some sort of console
// access.
#define INPHI_HAS_DIAGNOSTIC_DUMPS     1

// Set to 1 to include support for math.h
#define INPHI_HAS_MATH_DOT_H           1

// Set to 1 to include floating point math support
#define INPHI_HAS_FLOATING_POINT       1

// Turn on/off MCU diagnostic methods
#define INPHI_HAS_MCU_DIAGNOSTICS      1

// Turn on/off the eye monitor methods
#define INPHI_HAS_EYEMON               1

// Turn on/off the methods for accessing the EEPROM
#define INPHI_HAS_EEPROM_ACCESS        1
// Used for booting two devices from the same EEPROM
#define INPHI_HAS_SHARED_EEPROM        1

// Turn on/off conservative Inbound PIF reads.
// To speed up verifying the f/w image this
// can be set to 0.
#define INPHI_HAS_INBPIF_READ_POLLING  1

#define INPHI_HAS_LOG_NOTE 1
#define INPHI_HAS_LOG_WARN 1
#define INPHI_HAS_LOG_CRIT 1

#if !defined(INPHI_DONT_USE_STDLIB)
#    if !defined(INPHI_HAS_FILESYSTEM)
#        define INPHI_HAS_FILESYSTEM 1
#    endif
#endif

#if defined(INPHI_DONT_USE_STDLIB)
#    undef INPHI_HAS_FILESYSTEM
#    undef INPHI_HAS_MATH_DOT_H
#    undef INPHI_HAS_DIAGNOSTIC_DUMPS
#    define INPHI_HAS_FILESYSTEM       0
#    define INPHI_HAS_MATH_DOT_H       0
#    define INPHI_HAS_DIAGNOSTIC_DUMPS 0
#endif

#endif /* __INPHI_CONFIG_H__ */
