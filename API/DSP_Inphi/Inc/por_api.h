/** @file por.h
 ****************************************************************************
 *
 * @brief
 *     This module describes the high level API methods provided
 *     by the Porrima(PG3) API.
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
#ifndef __POR_H__
#define __POR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "inphi_rtos.h"
#include "spica_registers.h"
#include "por_rules.h"

/**
 * @h2 Misc defines
 * =======================================================
 *
 * @brief
 * Max debug buffer length for query_dump, primarily based on the maximum size in the MCU FW.
 */
#define POR_MCU_DEBUG_BUFFER_MAX_LENGTH 2048+1

/**
 * Default number of MS to poll for MCU status
 * 
 * @private
 */
#define POR_MCU_POLL_DELAY_MS 50

/**
 * Top bits of the MCU DRAM address space
 *
 * @private
 */
#define POR_MCU_DRAM_ADDR_MSW 0x5ff8

#define POR_FEC_STATS_MAX_TIME 14000


/**
 * @h2 Package and Channel Utilities
 * =======================================================
 * These methods are used for accessing/looping over multiple instances
 * of a particular interface. The number of channels a device has
 * is based on the package type; the bare die has multiple instances
 * that may not be bumped out to a package pin.
 * Iterator will be called "channel".
 *
 * @brief
 * "for" loop replacement that duplicates this:
 *
 * @{pre,
 * for(uint32_t channel = <start channel>; channel <= <end channel>; channel += <channel spacing>)
 * }
 *
 * Which makes it easy to write package-independent code.
 *
 * @example
 * POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
 * {
 *      printf("ch %d\n", channel);
 * }
 */
#define POR_FOR_CHANNEL_IN_CHANNELS(die, intf) \
    for(const por_channels_t *_chs=por_channels(die, intf);_chs;_chs=NULL) \
    for(uint32_t _i=0; _i<_chs->num;_i++) \
    for(uint32_t _do=1, channel=_chs->ch[_i]; _do; _do=0)

/**
 * To broadcast a register write to all channels use this macro instead of a channel number.
 * 
 * Does not work for register reads!
 * 
 * Do not use in API methods, just in direct register accesses.
 */
#define POR_BROADCAST_CHANNEL 0xff

/**
 * This method is used to extract the encoded package type
 * from the lower bits of the die parameter where it is cached
 * to avoid having to lookup the package type to handle
 * channel re-mapping
 *
 * This is useful in combination with the POR_FOR_CHANNEL_IN_CHANNELS macro above.
 */
#define POR_PACKAGE_FROM_DIE(die) por_package_get_type(die)

/**
 * This macro is used to encode the package type within the
 * lower bits of the die parameter for caching purposes. This
 * is used to avoid having to lookup the package type to
 * handle channel re-mapping.
 *
 * You don't need to use this, this is more of an internal method.
 *
 * @private
 */
#define POR_PACKAGE_SET_IN_DIE(die, package) por_package_type_set_in_die(die, package)

/**
 * The maximum number of devices that the API can support in the same
 * system. This is used to manage caching the package type associated
 * with a particular die to handle mapping of API channel numbers to the external
 * pins of the ASIC.
 */
#ifndef POR_MAX_NUM_DEVICES
#define POR_MAX_NUM_DEVICES 8
#endif

/**
 * Struct for saving the channel iterators
 *
 * @private
 */
typedef struct
{
    uint32_t num;
    uint32_t ch[16];
} por_channels_t;

/**
 * Returns a pointer to a list of channels and how many there are based on the interface and package.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param intf    [I] - The desired interface
 *
 * @return Pointer to a list of channels
 */
const por_channels_t* por_channels(
        uint32_t die,
        e_por_intf intf);

/**
 * This method returns the package type based on either:
 *  - the package bits saved in the die parameter
 *  - the cached package type info saved internally to the API
 *  - queried from the connected device EFUSE
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return
 * The ASIC package type defined in the MMD30_CHIP_ID
 * register.
 *
 * @since 0.1
 */
e_por_package_type por_package_get_type(
    uint32_t die);

/**
 * This method is used to encode the package type
 * in the die parameter so that it can be used by the
 * API to lookup the channel mapping.
 *
 * This is an internal method, you don't need to use this.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param package [I] - The package type to force.
 *
 * @private
 *
 * @since 0.1
 */
uint32_t por_package_type_set_in_die(
    uint32_t die,
    e_por_package_type package);

/**
 * Although this method isn't required to operate the device (the
 * API will cache the package info automatically) it is still
 * useful for forcing the die parameter in your scripts to contain
 * the package bits, which will prevent the API from having to
 * perform a package cache lookup on each register access.
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return
 * The die number with the package type encoded in
 * the lower bits.
 *
 * @since 0.1
 *
 * @see POR_PACKAGE_FROM_DIE to get the package enum from the return value, or por_package_get_type directly.
 */
uint32_t por_package_discover_type(
    uint32_t die);

/**
 * This method is used to query the package type from the efuse
 *
 * @since 0.1
 *
 * @private
 */
e_por_package_type por_package_query_efuse(
    uint32_t die);

/**
 * This method is used to determine the number of dies
 * inside the package.
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return The number of dies in the package.
 *
 * @since 0.1
 */
uint32_t por_package_get_num_dies(
    uint32_t die);

/**
 * This method is called to get the base die inside
 * the package. This is used for iterating through multiple
 * in an ASIC package that has multiple dies.
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return The base die number in the package.
 *
 * @since 0.1
 */
uint32_t por_package_get_base_die(
    uint32_t die);


/**
 * Similar to por_channels, this method provides the min and max channels used for a particular interface.
 * In Porrima the channel ranges used through the API are continuous (1, 2, 3, ...) so there is no
 * risk in using this method over the por_channels one.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param intf    [I] - The interface
 * @param min     [O] - Pointer to the minumum channel number
 * @param max     [O] - Pointer to the maximum channel number
 *
 * @return The number of dies in the package.
 *
 * @since 0.1
 *
 * @see por_channels which does something similar
 */
void por_package_get_channels(
    uint32_t die,
    e_por_intf intf,
    uint32_t* min,
    uint32_t* max);

#if 0
/**
 * This method is called to clear the cache used to map a particular
 * die parameter to the associated ASIC package type. The package type
 * is important so that the API knows how to map channels to the external
 * pins of the ASIC.
 *
 * @since 0.1
 */
void por_package_cache_clear(void);
#endif

/**
 * This method is called to dump the cache used to map a particular
 * die parameter to the associated ASIC package type. The package type
 * is important so that the API knows how to map channels to the external
 * pins of the ASIC.
 *
 * @since 0.1
 */
void por_package_cache_dump(void);


/**
 * @h2 Register Access Methods
 * =======================================================
 * The following methods must be defined by the customer
 * to provide access to the underlying register interface
 * of the ASIC depending on the customer platform.
 *
 * @h3 Low Level Interface Methods
 * ================================
 * The spica_reg_get/spica_reg_set methods provide access to
 * he ASIC registers. They must be implemented outside the
 * API in the customers software as the interface may be
 * different for each user. The API provides the following
 * protoypes for these methods.
 *
 * @brief
 * Lowest level register get function, must be implemented
 * by the end user for 16bit-only accesses.
 *
 * NOTE: Do not use spica_reg_get directly in your code, use
 * spica_reg_read instead.
 *
 * @param die  [I] - The ASIC die being accessed.
 * @param addr [I] - The address of the register being accessed.
 * @param data [O] - The data read from the register.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_reg_get(
    uint32_t  die,
    uint32_t  addr,
    uint32_t* data);

/**
 * @brief
 * Lowest level register set function, must be implemented
 * by the end user for 16bit-only accesses.
 *
 * NOTE: Do not use spica_reg_set directly in your code, use
 * spica_reg_write instead.
 *
 * @param die  [I] - The ASIC die being accessed.
 * @param addr [I] - The address of the register being
 *                   accessed.
 * @param data [I] - The data to write to the register.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_reg_set(
    uint32_t die,
    uint32_t addr,
    uint32_t data);

#if 0
/**
 * This method is called to manage re-mapping the channel based on
 * the interface being accessed.
 *
 * @param die     [I/O] - The die being accessed. This may be modified depending
 *                        on which channel in a multi-die package is being
 *                        accessed.
 * @param channel [I/O] - The channel through the device being accessed. This
 *                        may be re-mapped based on the package type.
 *
 * @param intf    [I/O] - The interface of the register being accessed. This
 *                        may be re-mapped based on the package type and channel.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 */
inphi_status_t por_rebase_channel_by_intf(uint32_t* die, uint32_t* channel, uint32_t intf);
#endif

typedef inphi_status_t (*por_callback_lock)(uint32_t die);
typedef inphi_status_t (*por_callback_unlock)(uint32_t die);

/**
 * @h2 Hardware Locking Methods
 * =======================================================
 * The following methods provide support for multi-threading.
 * Because this is optional they are implemented as callback
 * methods that the user may choose to register.
 *
 * @note
 * The locking methods must be implemented as recursive/counting locks
 * or reentrant mutex as the API will attempt to obtain the
 * same lock multiple times in child function calls:
 *   https://en.wikipedia.org/wiki/Reentrant_mutex
 *
 * @brief
 * Setup a callback method to support h/w locking. Setting up hardware
 * locking/multi-threading is optional. It will be disabled
 * by default.
 *
 * @param callback [I] - Pointer to the callback function to
 *                       call to lock access to the h/w.
 *
 * @return None
 *
 * @since 0.1
 *
 * @private
 */
void por_set_callback_for_lock(
    por_callback_lock callback);

/**
 * Setup a callback method to support h/w unlocking. Setting up
 * hardware locking is optional. It will be disabled by default.
 *
 * @param callback [I] - Pointer to the callback function to
 *                       call to lock access to the h/w.
 *
 * @return None
 *
 * @since 0.1
 *
 * @private
 */
void por_set_callback_for_unlock(
    por_callback_unlock callback);

#if 0 //not ready just yet
#define POR_LOCK(die) {if(por_lock(die) != INPHI_OK) return INPHI_ERROR;}
#define POR_UNLOCK(die) {if(por_unlock(die) != INPHI_OK) return INPHI_ERROR;}
#else
#define POR_LOCK(die) ((void)die)
#define POR_UNLOCK(die) ((void)die)
#endif

/**
 * Lock the hardware for exclusive access. If hardware locking
 * has not been enabled then these methods silently return.
 *
 * @{note, Failure to obtain lock (via timeout or some other method)
 * should return INPHI_ERROR, otherwise the API will proceed without
 * obtaining lock}
 *
 * @{note, The locking feature has not been tested}
 *
 * @param die [I] - The die of the ASIC to access.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @see por_set_callback_for_lock, por_set_callback_for_unlock
 *
 * @since 0.1
 *
 * @private
 */
inphi_status_t por_lock(
    uint32_t die);

/**
 * Unlock the hardware for exclusive access. If hardware locking
 * has not been enabled then these methods silently return.
 *
 * @{note, The locking feature has not been tested}
*
 * @param die [I] - The die of the ASIC to access.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @see por_set_callback_for_lock, por_set_callback_for_unlock
 *
 * @since 0.1
 *
 * @private
 */
inphi_status_t por_unlock(
    uint32_t die);


/**
 * @h2 Firmware Management
 * =======================================================
 * Methods for interacting with the FW running in the POR
 * device.
 *
 * @h3 Firmware Mode Enumerations
 * =======================================================
 *
 * @brief
 * The following enumeration defines the modes of
 * operation of the firmware.
 */
typedef enum
{
    /** Unknown bootloader mode */
    POR_FW_MODE_UNKNOWN           = 0,
    /** Application mode */
    POR_FW_MODE_APPLICATION       = 1,
    /** Boot Upgrade mode */
    POR_FW_MODE_BOOT_UPGRADE      = 2,
    /** Bootloader mode */
    POR_FW_MODE_BOOT_FROM_EEPROM  = 3,

} e_por_fw_mode;


/**
 * @h3 Switching Firmware Modes
 * =======================================================
 * The following methods may be used to switch between different
 * firmware modes.
 *
 * @brief
 * This method is called to reset the firmware into application mode. It
 * resets the MCU and switches to the application bank (assuming it
 * has been previously programmed in the IRAM/DRAM). If the
 * @{b,wait_till_started} flag is set it waits for the MCU_FW_MODE register to report
 * 0xACC0 to indicate that the application image has started up.
 *
 * This method does not load the firmware from EEPROM. It assumes that the
 * firmware has been previously downloaded to the IRAM/DRAM.
 *
 * @{note,
 * To avoid blocking forever in the case of a failure or where the
 * firmware image is not yet programmed this method will timeout after five
 * seconds and return INPHI_ERROR.}
 *
 * @{note,
 * This method is multi-die aware on packages that have
 * multiple dies}
 *
 * @param die               [I] - The ASIC die to target.
 * @param wait_till_started [I] - Wait until the application firmware is started.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_mcu_reset_into_application(
    uint32_t die,
    bool wait_till_started);


/**
 * Reset the firmware into boot upgrade mode. This mode provides
 * an alternative mechanism for upgrading the firmware either
 * directly to the IRAM/DRAM or to the external EEPROM memory.
 *
 * It resets the MCU and switches into the boot upgrade bank. If the
 * @{b,wait_till_started} flag is set it waits for the MCU_FW_MODE register to report
 * 0xBCDD to indicate the bootloader has started in upgrade mode.
 *
 * @{note,
 * To avoid blocking forever in the case of a failure this method will
 * timeout after five seconds and return INPHI_ERROR.}
 *
 * @{note,
 * This method is multi-die aware on packages that have
 * multiple dies}
 *
 * @param die               [I] - The ASIC die to target.
 * @param wait_till_started [I] - Wait until the bootloader firmware is started.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_mcu_reset_into_boot_upgrade(
    uint32_t die,
    bool wait_till_started);


/**
 * Reset the firmware into boot from EEPROM mode. This mode may be
 * used to boot the application firmware from an external EEPROM
 * image if present.
 *
 * It resets the MCU into boot from EEPROM mode. If the @{b,wait_till_started} flag
 * is set it waits for the MCU_FW_MODE register to report 0xBCEE to indicate the
 * bootloader has started booting from EEPROM. To wait for the application
 * image to start call the por_mcu_block_application_mode() method
 * immediately after this call.
 *
 * @{note,
 * To avoid blocking forever in the case of a failure this method will
 * timeout after five seconds and return INPHI_ERROR.}
 *
 * @{note,
 * This method is multi-die aware on packages that have
 * multiple dies}
 *
 * @param die               [I] - The ASIC die to target.
 * @param wait_till_started [I] - True to wait until the application FW has started before returning
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @example
 * uint32_t die = 0;
 *
 * // Measure the start time
 * uint64_t start = clock();
 *
 * // Jump to boot from EEPROM
 * por_mcu_reset_into_boot_from_eeprom(die, true);
 *
 * // Wait for the application f/w to start after
 * // it has been programmed.
 * por_mcu_block_application_mode(die, 2000);
 *
 * // Measure the end time
 * uint64_t end = clock();
 *
 * // Print the amount of time it took to boot from EEPROM
 * INPHI_NOTE("Boot from EEPROM took %lld ms\n", end - start);
 */
inphi_status_t por_mcu_reset_into_boot_from_eeprom(
    uint32_t die,
    bool wait_till_started);


#if defined(INPHI_HAS_DIRECT_DOWNLOAD) && (INPHI_HAS_DIRECT_DOWNLOAD==1)
#if defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW==1)
/**
 * @h3 Firmware Programming APIs
 * =======================================================
 * There are two ways of programming the embedded application
 * firmware:
 *
 * @table
 * - Method           | Description | Methods
 * - Direct Download  | The firmware image is programmed directly
 *                      to the on-board IRAM/DRAM and the MCU is
 *                      brought out of reset. This download needs
 *                      to happen on every reset. | por_mcu_download_firmware,
 *                      por_mcu_download_firmware_from_external_memory,
 *                      por_mcu_download_firmware_from_file
 * - Boot from EEPROM | Load the application firmware from an
 *                      external EEPROM device via SPI. | por_mcu_download_eeprom_from_file,
 *                      por_mcu_eeprom_verify_with_checksum
 *
 * @brief
 * This method is called to download the firmware inlined
 * with the API directly to the MCUs RAM memory instead
 * of booting from EEPROM.
 *
 * It will program the microcode on all dies in the package,
 * jump to the new application image and verify it is
 * running properly.
 *
 * @{note,
 * This method is multi-die aware on packages that have
 * multiple dies}
 *
 * @param die    [I] - The die used to identify which ASIC
 *                     is being accessed.
 * @param verify [I] - Optionally read back the programmed values
 *                     to verify the results. This is typically
 *                     not required and will slow down the programming
 *                     but is provided for users who want an
 *                     extra integrity check.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must have direct download support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 * - INPHI_HAS_INLINE_APP_FW
 *
 * @since 0.1
 */
inphi_status_t por_mcu_download_firmware(
    uint32_t die,
    bool verify);
#endif //defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW==1)

/**
 * This method is called to download the firmware directly
 * to the MCUs RAM memory instead of booting from EEPROM.
 * This method may be used in the event that the firmware
 * is stored separately from the API, perhaps in an
 * external Flash memory.
 *
 * It will program the microcode on all dies in the package,
 * jump to the new application image and verify it is
 * running properly.
 *
 * @param die         [I] - The die used to identify which ASIC
 *                          is being accessed.
 * @param fw_get_word [I] - This is a callback used to fetch
 *                          the firmware a 32 bit word at a time in
 *                          the event it is stored separately
 *                          from the API.
 * @param fw_length   [I] - The length of the firmware image
 *                          in 32 bit words.
 * @param verify      [I] - Optionally read back the programmed values
 *                          to verify the results. This is typically
 *                          not required and will slow down the
 *                          programming but is provided for users that
 *                          want an extra integrity check.
 * @param user_data   [I] - An optional parameter to pass back to
 *                          the fw_get_word callback to transfer
 *                          state. If you don't need this then set
 *                          it to NULL.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_mcu_download_firmware_from_external_memory(
    uint32_t die,
    uint32_t (*fw_get_word)(uint32_t offset, void* user_data),
    uint32_t fw_length,
    bool     verify,
    void*    user_data);

/**
 * This method is called to download the firmware directly
 * to the MCUs RAM memory instead of booting from EEPROM.
 * It will program the microcode on all dies in the package,
 * jump to the new application image and verify it is
 * running properly.
 *
 * @param die    [I] - The die used to identify which ASIC
 *                     is being accessed.
 * @param path   [I] - The path to the application firmware
 *                     to program.
 * @param verify [I] - Optionally read back the programmed values
 *                     to verify the results. This is typically
 *                     not required and will slow down the
 *                     programming but is provided for users that
 *                     want an extra integrity check.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must have file system support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 * - INPHI_HAS_FILESYSTEM
 *
 * @since 0.1
 */
inphi_status_t por_mcu_download_firmware_from_file(
    uint32_t die,
    const char* path,
    bool verify);

#endif //INPHI_HAS_DIRECT_DOWNLOAD


#if defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)
/**
 * @h2 Downloading EEPROM from a File
 * This section describes the process of programming the EEPROM
 * from an external file. In order to call this you must
 * define INPHI_HAS_EEPROM_ACCESS and have access
 * to the file system (INPHI_HAS_FILESYSTEM)
 *
 * @c
 * uint32_t die = 0;
 * uint32_t checksum_calculated = 0;
 * uint32_t checksum_expected = 0;
 * inphi_status_t status = INPHI_OK;
 *
 * // Set SELF_INIT pin to 0 to enable bootloader upgrade mode
 * // to allow re-programming the EEPROM.
 * customer_hardware_set_self_init_pin(0);
 *
 * // Reset the MCU into bootloader upgrade mode
 * status |= por_mcu_reset_into_boot_upgrade(die, true);
 *
 * // Re-program the EEPROM image
 * status |= por_mcu_download_eeprom_from_file(die, "/path/to/eeprom/image.txt");
 *
 * // Verify the EEPROM image
 * status |= por_mcu_eeprom_verify_with_checksum(die, 0, checksum_calculated, checksum_expected);
 * printf("Checksum (Calculated): %x\n", checksum_calculated);
 * printf("Checksum (Expected):   %x\n", checksum_expected);
 *
 * if(status != INPHI_OK)
 * {
 *     printf("An error occurred re-programming the EEPROM\n");
 * }
 *
 *
 * @brief
 * This method is called to program the EEPROM from an
 * image file.
 *
 * @param die    [I] - The die used to identify which ASIC is being
 *                     accessed.
 * @param path   [I] - The path to the EEPROM image to program.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must have file system support. It must be compiled
 * with the following flags set to 1:
 * - INPHI_HAS_FILESYSTEM
 * - INPHI_HAS_EEPROM_ACCESS
 *
 * @since 0.1
 */
inphi_status_t por_mcu_download_eeprom_from_file(
    uint32_t die,
    const char* path);


/**
 * This method is called to verify that the EEPROM contains valid data
 * by calculating the checksum of the EEPROM and comparing it to what
 * it should be. The calculated and stored checksum are returned so
 * that they may be displayed in the end user system.
 *
 * @{note, This method will automatically switch the f/w to boot
 *         upgrade mode to verify the EEPROM contents}.
 *
 * @param die                 [I] - The die of the device being accessed.
 * @param eeprom_address      [I] - The address in EEPROM to read from.
 * @param checksum_calculated [O] - If this pointer is not NULL then
 *                                  the EEPROM checksum calculated by
 *                                  the MCU will be stored in it.
 * @param checksum_expected   [O] - If this pointer is not NULL then
 *                                  the EEPROM checksum expected by the
 *                                  MCU will be stored in it.
 *
 * @example
 *   uint32_t die = 0;
 *   uint32_t calc = 0;
 *   inphi_status_t status = INPHI_OK;
 *
 *   status |= pam_mcu_eeprom_verify_with_checksum(die, 0, &calc, &exp);
 *   printf("calculated checksum: %x\n", calc);
 *   printf("expected checksum:   %x\n", exp);
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @requires
 * The API must have EEPROM access support. It must be compiled
 * with the following flags set to 1:
 * - INPHI_HAS_EEPROM_ACCESS
 */
inphi_status_t por_mcu_eeprom_verify_with_checksum(
    uint32_t  die,
    uint32_t  eeprom_address,
    uint32_t* checksum_calculated,
    uint32_t* checksum_expected);

/**
 * This method is called to read the metadata from the EEPROM
 * image. The user should allocate an array of 256 bytes to
 * store the metadata image.
 *
 * @{note, In python this method accepts two arguments only (die, metadata_size) and
 * returns (status, metadata)}
 *
 * @param die             [I]   - The die of the device being accessed.
 * @param metadata        [I/O] - The buffer allocated to store the
 *                                EEPROM metadata.
 * @param metadata_size   [I]   - The number of allocated bytes in
 *                                the metadata buffer.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @requires
 * The API must have EEPROM access support. It must be compiled
 * with the following flags:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
inphi_status_t por_mcu_eeprom_read_metadata(
    uint32_t die,
    char*    metadata,
    uint32_t metadata_size);


#if defined(INPHI_HAS_SHARED_EEPROM) && (INPHI_HAS_SHARED_EEPROM==1)
/**
 * @h2 Booting from a Shared EEPROM
 * This section describes the process of sharing an EEPROM between one
 * or more devices. The Porrima device acts as an SPI master so only one
 * device can be active at any one time, the others must be setup as
 * SPI slaves (i.e. MCU32_MCTL.SPIRST=1). Externally the SPI pins must
 * be wired together (i.e. the four SCK pins should be wired together).
 * To use the chip this way the SELF_INIT pin should be pulled low so that
 * when the ASIC is reset it automatically comes up as an SPI slave and
 * waits for the host to trigger the download from EEPROM.
 *
 * - Set SELF_INIT == 0 on all devices. This will bring the device up
 *   in bootloader upgrade mode and the host software must kick off
 *   the download from EEPROM. This is desired to ensure that each
 *   device acts as an SPI slave out of reset.
 * - Bring all devices out of reset
 * - Call por_mcu_boot_from_shared_eeprom to control the boot process.
 *   The method will block until the boot is complete on all dies in
 *   the input array. As each device is booted into application mode
 *   the method will assert MCU32_MCTL.SPIRST = 1 to ensure that the
 *   device is set back into SPI slave mode to avoid multiple dies/devices
 *   driving the SPI bus at the same time.
 *
 * @c
 * inphi_status_t status = INPHI_OK;
 *
 * // Boot the Porrima device from a shared EEPROM passing
 * // in the array of dies associated with the device. This example
 * // assumes the dies are identified as 0,1,2,3.
 * uint32_t dies[4] = {0x0, 0x1, 0x2, 0x3};
 * status |= por_mcu_boot_from_shared_eeprom(dies, 4);
 *
 *
 * @brief
 * This method is called to share a single EEPROM between one or more
 * Porrima devices such that only a single die is active on the shared SPI bus at one
 * time. In this application the SPI signals from each die/device will be wired
 * together and only one die will be active at once. The other devices will
 * be setup so that they are SPI slaves to avoid contention on the SPI bus.
 * This controlled bringup is required due to a limitation in the design
 * of the SPI logic which does not support multi-master detection.
 *
 * @param dies     [I] - The array of dies to monitor. This is setup as an array
 *                       to allow multiple devices to share the same EEPROM device.
 * @param num_dies [I] - The length of the input dies array to walk through
 *                       booting up the firmware from EEPROM serially.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @see por_mcu_boot_from_shared_eeprom_with_callback
 *
 * @requires
 *     INPHI_HAS_SHARED_EEPROM must be defined when compiling or in inphi_config.h
 *
 * @since 0.1.410
 */
inphi_status_t por_mcu_boot_from_shared_eeprom(
    uint32_t* dies,
    uint32_t  num_dies);

/**
 * This method is setup as a callback method to allow the user to not
 * completely block while the bootloader is busy loading the firmware from
 * the EEPROM for each die on the device. Only one die can be SPI
 * master at any one time so the boot procedure needs to be controlled to
 * avoid damage to the SPI pins.
 *
 * This method will be called multiple times until the application image
 * starts or the user aborts the polling operation.
 *
 * @param die           [I] - The ASIC die to poll for completion on
 * @param user_data     [I] - Optional user data passed to the callback for
 *                            state tracking purposes in case the user wants
 *                            to do other things while waiting for the boot
 *                            to complete.
 * @param complete      [O] - true if the boot has completed, false if it
 *                            is still in progress.
 * @param abort_polling [O] - true if the polling should be aborted
 *                            because it is taking too long or false if
 *                            it should continue.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 *     INPHI_HAS_SHARED_EEPROM must be defined when compiling or in inphi_config.h
 *
 * @since 0.1.410
 */
inphi_status_t por_mcu_check_boot_from_eeprom_complete(
    uint32_t die,
    void*    user_data,
    bool*    complete,
    bool*    abort_polling);

#endif // defined(INPHI_HAS_SHARED_EEPROM) && (INPHI_HAS_SHARED_EEPROM==1)

#endif // defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)




/**
 * @h2 Device Configuration
 * =======================================================
 *
 * @brief
 * This method sets up the default rules for the desired operating
 * mode to simplify the implementation for the user.
 *
 * @{note,This method initializes the rules data-structure, it does
 * not write to any registers.}
 *
 * @param die           [I] - The die of the ASIC being configured by this
 *                              instance of the rules structure.
 * @param op_mode       [I] - The main operational mode of the ASIC.
 * @param protocol_mode [I] - The desired protocol modes which will describe the rate,
 *                              number of channels on each interface, and indirectly the signalling.
 * @param fec_mode      [I] - The FEC output mode to use.
 * @param rules         [O] - The default rules for the application.
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @since 0.1
 */
inphi_status_t por_rules_set_default(
    uint32_t               die,
    e_por_operational_mode op_mode,
    e_por_protocol_mode    protocol_mode,
    e_por_fec_mode         fec_mode,
    por_rules_t*           rules);

/**
 * This method is used to setup the default Tx rules
 *
 * @param tx_rules   [O] - The default Tx rules for the application.
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @since 0.1
 */
inphi_status_t por_tx_rules_set_default(
    por_tx_rules_t*  tx_rules);

/**
 * This method is used to check the rules for possible errors in configuration.
 *
 * This gets called automatically by por_init.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param rules   [I] - The default rules for the application.
 *
 * @private
 *
 * @since 0.1
 */
inphi_status_t por_check_rules(
    uint32_t     die,
    por_rules_t* rules);

/**
 * This method is used to check the TX FIR rules for errors in configuration.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param intf    [I] - The ASIC interface being accessed.
 * @param rules   [I] - The default rules for the application.
 *
 * @private
 *
 * @since 0.7
 */

inphi_status_t por_tx_check_rules(
    uint32_t     die,
    uint32_t     channel,
    e_por_intf   intf,
    por_tx_rules_t* tx_rules);

/**
 * This is an option soft reset that asserts the MMD08_PMA_CONTROL.RESET
 * bit. The user should normally assert the reset pin instead of hitting
 * the soft reset.
 *
 * @{note,
 * This method is multi-die aware on packages that have
 * multiple dies}
 *
 * @param die [I] - The die of the ASIC being soft reset.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_soft_reset(
    uint32_t die);

/**
 * Reset the device to have it/them ready for any user config,
 * and then call por_enter_operational_state.
 *
 * This method can be called after de-asserting the reset pin;
 * it will wait for the bootloader to load an EEPROM and the
 * application firmware to be loaded. You can configure the
 * maximum time to wait in rules.fw_dwld_timeout (default 500ms).
 *
 * @{note,
 * This method is multi-die aware on packages that have
 * multiple dies}
 *
 * @param die   [I] - The physical ASIC die being accessed.
 * @param rules [I] - The device initialization rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_init(
    uint32_t die,
    por_rules_t* rules);


/**
 * This method is used to put the Porrima device into operational
 * state. This method MUST be preceded by a call to por_init.
 *
 * @{note,
 * This method is multi-die aware on packages that have
 * multiple dies}
 *
 * @param die   [I] - The physical ASIC die being accessed.
 * @param rules [I] - The device initialization rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_enter_operational_state(
    uint32_t die,
    por_rules_t* rules);


#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/**
 * This is a debug method used to dump the configuration rules.
 *
 * @param die   [I] - The physical ASIC die being accessed.
 * @param rules [I] - The rules structure to dump.
 *
 * @since 0.1
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
void por_dbg_dump_rules(
    uint32_t die,
    por_rules_t* rules);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)


/**
 * @h2 TX FIR Management
 *
 * @brief
 * This method may be called to query the current configuration of the
 * transmitters from the ASIC.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The channel through the device to query.
 * @param intf    [I] - The TX interface to query (POR_INTF_LTX or POR_INTF_HTX).
 * @param rules   [O] - The configuration for the transmitter read back from the hardware.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_tx_fir_query(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_tx_rules_t* rules);


/**
 * Update the TX FIR configuration for a particular channel.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The channel through the device to change.
 * @param intf    [I] - The TX interface to configure (POR_INTF_LTX or POR_INTF_HTX)
 * @param rules   [I] - The rules to apply to re-configure the channel.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_tx_fir_set(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_tx_rules_t* rules);


#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/**
 * Query then dump the TX FIR configuration.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The channel through the device to change.
 * @param intf    [I] - The TX interface to configure (POR_INTF_LTX or POR_INTF_HTX)
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * INPHI_HAS_DIAGNOSTIC_DUMPS=1
 *
 * @since 0.1
 */
inphi_status_t por_tx_fir_query_dump(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * This method may be called to squelch or disable the output
 * transmitter.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The channel through the device to change.
 * @param intf    [I] - The TX interface to squelch (POR_INTF_LTX or POR_INTF_HTX)
 * @param squelch [I] - true to squelch the output, false to turn
 *                      the transmit output back on.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_tx_squelch(
    uint32_t   die,
    uint32_t   channel,
    e_por_intf intf,
    bool       squelch);

/**
 * This method may be called to enable or disable the squelch lock for the
 * output transmitter
 *
 * Setting squelch_lock to true/false does not have an immediate effect on the transmitter's state.
 * This setting will only be used by the FW the next time the Transmitter is brought up to determine
 * if the Tx is brought up dark (ie. Tx squelched), or as usual (Tx unsquelched)
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The channel through the device to change.
 * @param intf    [I] - The TX interface to squelch (POR_INTF_LTX or POR_INTF_HTX)
 * @param squelch_lock  [I] - true to enable the transmit squelch lock, false to disable the
 *                      transmit squelch lock.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.10
 */
inphi_status_t por_tx_squelch_lock(
    uint32_t   die,
    uint32_t   channel,
    e_por_intf intf,
    bool       squelch_lock);

/**
 * This is a diagnostic method that is called to toggle the current invert
 * status of the TX channel after it has been configured. This is sometimes
 * useful when trying to determine the hardware inversions.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The physical channel to toggle the invert for.
 * @param intf    [I] - The interface to toggle
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.5
 */
inphi_status_t por_tx_invert_toggle(
    uint32_t          die,
    uint32_t          channel,
    e_por_intf        intf);


/**
 * This is a diagnostic method that is called to toggle the current invert
 * status of the RX channel after it has been configured. This is sometimes
 * useful when trying to determine the hardware inversions.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The physical channel to toggle the invert for.
 * @param intf    [I] - The interface to toggle
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.5
 */
inphi_status_t por_rx_invert_toggle(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf);

/**
 * This method should be used to enable/disable a bundle of traffic on the chip independently of other bundles (if any exist).
 * Bundles are groups of connected blocks, starting at a data/clock source (Rx) and ending in a sink (Tx).
 * Bundles are dynamically created based on the operating mode of the chip, the Xbar config, etc.
 *
 * For example, if the part is configured for: POR_MODE_MISSION_MODE, POR_MODE_400G_KP8_TO_KP4
 * then the device will be split into 8 independent streams (4 in egress, 4 in ingress):
 *
 * @{pre,
 * +---------+-------------------------------+
 * |         |     Egress Bundles            |
 * | INTF    |   1   |   2   |   3   |   4   |
 * +---------+-------+-------+-------+-------+
 * |HRX      |  1,2  |  3,4  |  5,6  |  7,8  |
 * |LTX_PLL  |   1   |   2   |   3   |   4   |
 * |LTX      |   1   |   2   |   3   |   4   |
 * +---------+-------+-------+-------+-------+
 * +---------+-------------------------------+
 * |         |     Ingress Bundles           |
 * | INTF    |   5   |   6   |   7   |   8   |
 * +---------+-------+-------+-------+-------+
 * |LRX      |   1   |   2   |   3   |   4   |
 * |HTX_PLL  |   1   |   2   |   3   |   4   |
 * |HTX      |  1,2  |  3,4  |  5,6  |  7,8  |
 * +---------+-------+-------+-------+-------+
 * }
 *
 * Setting enable/disable for any intf/channel pair above will disable/enable ALL other intf/channel pairs 
 * in the same bundle. ie. Calling por_bundle_enable(die, 2, POR_INTF_HTX, false) will disable ALL
 * intf/channel pairs in bundle 5.
 *
 * If you override the clk_xbar so that all Tx channels point to a common Rx clk, then all
 * channels in each egress/ingress direction become part of the same bundles (1 for egress, 1 for ingress)
 *
 * @param die       [I] - The ASIC die being accessed.
 * @param channel   [I] - Channel 
 * @param intf      [I] - Interface
 * @param enable    [I] - True to enable the bundle, false otherwise
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.0.0.0
 */
inphi_status_t por_bundle_enable(
    uint32_t die, 
    uint32_t channel, 
    e_por_intf intf, 
    bool enable);

/**
 * The following method can be used to query the temperature in degrees C 
 *
 * @param die            [I]  - The physical ASIC die being accessed.
 * @param temperature    [IO] - The temperature in deg C
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 */
inphi_status_t por_temperature_query(
    uint32_t die,
    int16_t* temperature);

/**
 * Provides full-manual control of the Tx LUT and COEFF register programming.
 *
 * Use this function when you have the FW LUT mode set to POR_TX_LUT_BYPASS in your tx_rules.
 * When doing so the FW will leave the Tx DSP registers alone, these must be setup via this function.
 *
 * @{note, Only applicable when the tx_rules.lut_mode is BYPASS!}
 *
 * Unfortunately this function cannot be called until the Tx voltage regulators are powered on. This means this
 * function must be called after por_enter_operational_state. It will poll a status register to wait for the
 * FW to turn on the channel before continuing. Because the squelch_lock is automatically turned ON for channels
 * using the LUT_BYPASS mode, you must program the LUT, disable the squelch lock, and manually unsquelch if
 * needed. See below for an example.
 *
 * The LUT indexes represent data on the datapath; 0 is 0b00/00/00/00 or [-3,-3,-3,-3] and 255 is 0b11/11/11/11
 * or [+3,+3,+3,+3]. Pre-indexes are the MSBs, post-indexes are the LSBs.
 * ie 0b00/01/10/11 would be [-3, -1, +1, +3] or [most pre, X, Y, most post] or index 27.
 * Values in the LUT are what that combo of [pre..post] should be output as a DAC code.
 * In unsigned, 0 is the most negative output voltage, 127 is the most positive output voltage.
 * In signed, -63 is the most negative output voltage, 63 is the most positive output voltage.
 * We can scale the [-3, +3] range by multiplying by 21 to get the DAC output range of [-63, 63].
 *
 * ie. Say you setup your pre/post indexes as [pre -1, main, post +1, post +2], resulting in FIR tap values of
 * say [-0.1, 0.8, 0, 0.1] (note the sum(abs(taps)) <= 1.0). The main tap can be any index, it simply alters your FIR taps.
 * If the data pattern 0b10/01/10/00 comes into the Tx DSP, you want the output of the DSP to be:
 * sum([+1*-0.1, -1*0.8, +1*0.0, -3*0.1]) = sum([-0.1, -0.8, 0.0, -0.3]) = -1.2, or slightly lower than the -1 level.
 * Convert to the signed DAC range via -1.2 * 21 = -25.2, rounding to -25.
 * The LUT index for this data pattern is 0b10011000 or 152, therefore
 * lut[152] = -25 if the LUT is signed, or unsigned you just add 64 to get a value of 39.
 *
 * The COEFF indexes and values are represented in the following table:
 * @{pre,
 *  Index    pre                    post
 *  0~6    -3*c[0], -3*c[1], ..., -3*c[6]
 *  7~13   -1*c[0], -1*c[1], ..., -1*c[6]
 *  14~20  +1*c[0], +1*c[1], ..., +1*c[6]
 *  21~27  +3*c[0], +3*c[1], ..., +3*c[6]}
 * The value to program will be the symbol (-3, -1, +1, +3) multiplied by the coefficient (-1.0, 1.0) multiplied
 * by the scalar 21 to get a range (-63.0, +63.0). The register has 10 bits, 3 bits for fractional, so taking
 * a float/double value and multiplying by 1<<3=8, then rounding to the nearest int, will give you the value
 * to program in the LUT.
 * Maximum value will be 3*21*1*8=504, however care must be taken that the sum of absolutes of all the maximum values in
 * each column is less than 504. ie sum(abs(lut[21:28])) <= 504 (21-27 because this the +3 row and therefore the
 * largest values). This is usually done by ensuring the sum(abs(taps)) <= 1.0.
 * Unlike the LUT values, the COEFF values MUST be signed!
 *
 * @param die        [I] - The physical ASIC die being accessed.
 * @param channel    [I] - The channel through the device to change.
 * @param intf       [I] - The TX interface to configure (POR_INTF_LTX or POR_INTF_HTX)
 * @param lut_mode   [I] - The actual HW mode to use as defined in TXD_DSP_CFG__MODE
 * @param is_lut_unsigned [I] - Whether the lut entries are -64 to +63 (false) or 0 to 127 (true)
 * @param toggle_squelch  [I] - If the Tx is currently locked and passing traffic, setting this to true
 *                              will squelch, set the LUT, then unsquelch. If Tx is unlocked it does nothing.
 * @param lut        [I] - The Tx LUT to program, must be 256 entries. 7bit values.
 * @param coef       [I] - The Tx 7tap COEFF to program (only applicable to 7tap mode). 10bit values.
 *                         Can be NULL if not using a 7tap mode.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 * @example
 * //configure
 * status |= por_init(die, rules);
 * status |= por_enter_operational_state(die, rules);
 * //configure the Txs
 * POR_FOR_CHANNEL_IN_CHANNELS(POR_PACKAGE_FROM_DIE(die), POR_INTF_LTX) {
 *     //only configure bypass channels
 *     if(rules.ltx[channel].lut_mode != POR_LUT_BYPASS) continue;
 *     
 *     status |= por_tx_man_config(die, channel, POR_INTF_LTX, POR_TX_LUT_4TAP,
 *                 is_lut_unsigned, true, lut, coef);
 *     //turn off squelch lock now that the Tx has been configured
 *     status |= por_tx_squelch_lock(die, channel, POR_INTF_LTX, false);
 *     //now check the FW lock; if it was locked prior to us configuring the Tx we need to unsquelch manually
 *     //since the FW was not in control of the squelch
 *     if(SPICA_OTX_FW_STATUS__LOCKED__READ(die, channel)) {
 *         status |= por_tx_squelch(die, channel, POR_INTF_LTX, false);
 *     } 
 * }
 */
inphi_status_t por_tx_man_config(
    uint32_t            die,
    uint32_t            channel,
    e_por_intf          intf,
    e_por_lut_mode      lut_mode,
    bool                is_lut_unsigned,
    bool                toggle_squelch,
    int8_t              lut[256],
    int16_t             coef[28]);


/**
 * @h2 Firmware Debug
 * =======================================================
 *
 * @brief
 * This structure is used to gather status information from the MCU
 * for debugging purposes.
 */
typedef struct
{
    /** The firmware mode of operation */
    e_por_fw_mode  fw_mode;
    /** The firmware mode (human readable string) */
    const char*    fw_mode_str;
    /** Is the firmware stalled? */
    bool           runstall;
    /** An array of program counter values */
    uint32_t       pc_trace[10];
    /** An array of main loop counter values */
    uint32_t       loop_count[2];
    /** The delta between loop counters read once per second */
    int            loop_delta;
    /** A rough estimate of the duration of the main loop in micro seconds */
    uint32_t       loop_duration;
    /** Any MDIO address errors that may have been flagged */
    uint32_t       mdio_addr_err;
    
    /** The application firmware version code */
    uint32_t       app_version;
    /** The application firmware major version */
    uint8_t        app_version_major;
    /** The application firmware minor version */
    uint8_t        app_version_minor;
    /** The application firmware patch revision number */
    uint8_t        app_version_revision;
    /** The application firmware build id */
    uint16_t       app_version_build;
    
    /** The API version code (if programmed) */
    uint32_t       api_version;
    /** The API major version (if programmed) */
    uint8_t        api_version_major;
    /** The API minor version (if programmed) */
    uint8_t        api_version_minor;
    /** The API patch revision number (if programmed) */
    uint8_t        api_version_revision;
    /** The API build ID (if programmed) */
    uint16_t       api_version_build;
}por_mcu_status_t;

/**
 * This method is used to query status information from the on-board
 * MCU for debug purposes
 *
 * @param die        [I] - The ASIC die being accessed.
 * @param mcu_status [I] - The MCU status queried from the hardware.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t por_mcu_status_query(
    uint32_t            die,
    por_mcu_status_t* mcu_status);


#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/**
 * This method is used to query and display status information from the on-board
 * MCU for debug purposes
 *
 * @param die        [I] - The ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be compiled with INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
inphi_status_t por_mcu_status_query_print(
    uint32_t die);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * This method returns the mode that the FW is currently in.
 *
 * @param die         [I]  - The physical ASIC being accessed.
 * @param mode        [IO] - The mode that the FW is currently in
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @see e_por_fw_mode for the modes the FW can be in.
 *
 * @since 0.1
 */
inphi_status_t por_mcu_fw_mode_query(
    uint32_t die,
    e_por_fw_mode *mode);

/**
 * This method fetches a trace of the program counter for debug
 * purposes.
 *
 * @param die         [I] - The physical ASIC being accessed.
 * @param entries     [O] - The allocated buffer to write PC entries to.
 * @param num_entries [I] - The number of entries to fetc.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_mcu_pc_log_query(
    uint32_t die,
    uint32_t* entries,
    uint32_t num_entries);


#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/**
 * This method is used to dump a trace of the program counter from
 * the MCU for debug purposes.
 *
 * @param die         [I] - The physical ASIC being accessed.
 * @param num_entries [I] - The number of entries to dump.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must be compiled with INPHI_HAS_DIAGNOSTIC_DUMPS flag
 *
 * @since 0.1
 */
inphi_status_t por_mcu_pc_log_query_dump(
    uint32_t die,
    uint32_t num_entries);


/**
 * This method is used to dump the firmware trace log
 * for debug purposes.
 *
 * @param die         [I] - The physical ASIC being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must be compiled with INPHI_HAS_DIAGNOSTIC_DUMPS flag
 *
 * @since 0.1
 */
inphi_status_t por_mcu_debug_log_query_dump(
    uint32_t die);

/**
 * This method is used to dump the firmware trace log into a buffer,
 * for debug purposes.
 *
 * buff_size can be any length you want, the recommended size is
 * available via POR_MCU_DEBUG_BUFFER_MAX_LENGTH. However if a smaller size
 * is required this method will capture the latest characters in the buffer
 * so the output saved to buff will be the latest text in the queue.
 *
 * @{note, In python this method accepts two arguments only (die, buff_size) and
 * returns (status, buff)}
 *
 * @param die         [I] - The physical ASIC being accessed.
 * @param buff        [O] - A pointer to a char buffer.
 * @param buff_size   [I] - The size of the char buffer.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must be compiled with INPHI_HAS_DIAGNOSTIC_DUMPS flag
 *
 * @since 0.1
 */
inphi_status_t por_mcu_debug_log_query(
    uint32_t die,
    char* buff,
    uint32_t buff_size);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)


/**
 * @h2 Version Information
 * =======================================================
 *
 * @brief
 * This method is used to retreive the version string describing
 * the version of the API in use. The user must allocate
 * a buffer of at least 256 bytes to retrieve the version information.
 *
 * @{note, In python this method accepts one argument only (buffer_len) and
 * returns (status, buffer)}
 *
 * @param buffer     [O] - The output buffer where the version string will
 *                         be stored.
 * @param buffer_len [I] - The length of the allocated buffer.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure
 *
 * @since 0.1
 */
inphi_status_t por_version(
    char*    buffer,
    uint32_t buffer_len);

/**
 * @brief
 * This method is used to retreive the version string describing
 * the version of the firmware in use. The user must allocate
 * a buffer of at least 256 bytes to retrieve the version information.
 *
 * @{note, In python this method accepts two arguments only (die, buffer_len) and
 * returns (status, buffer)}
 *
 * @param die        [I] - The ASIC die being accessed to fetch
 *                         the firmware verison information.
 * @param buffer     [O] - The output buffer where the version string will
 *                         be stored.
 * @param buffer_len [I] - The length of the allocated buffer.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure
 *
 * @since 0.1
 */
inphi_status_t por_version_firmware(
    uint32_t die,
    char*    buffer,
    uint32_t buffer_len);


/**
 * @h2 Link Status
 *
 * @brief
 * This method is used to wait for all channels in the package
 * to be in the receive ready state where they are ready to receive
 * traffic. This is state information is polled from the on-board
 * firmware.
 *
 * @{note,
 *   The timeout may be longer than the input specified as the
 *   overhead of accessing registers will increase the time}
 *
 * @{note,
 * This method is multi-die aware on packages that have
 * multiple dies so it will check the status across all dies inside
 * the package}
 *
 * @param die              [I] - The physical ASIC die being accessed.
 * @param timeout_in_usecs [I] - The amount of time to wait for all
 *                               channels to be ready in micro-seconds.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_wait_for_link_ready(
    uint32_t die,
    uint32_t timeout_in_usecs);


/**
* This method is called to determine whether particular interfaces or all
* interfaces of a channel link is up.
*
* @param die             [I] - The ASIC die being accessed.
* @param channel         [I] - The channel.
* @param intf            [I] - One or more interfaces to check. Note the intf
*                              identifiers can be OR'd together.
*
* @return true if the link is up, false if the link is down.
*
*/
bool por_channel_is_link_ready(
    uint32_t        die,
    uint32_t        channel,
    e_por_intf      intf);

/**
* This method is called to wait for link ready from a particular
* channel. This method checks the 1 to 4 channel interfaces to ensure the
* link is up.
*
* @param die             [I] - The ASIC die being accessed.
* @param channel         [I] - The channel to poll for link up.
* @param intf            [I] - One or more interfaces to check. Note the intf
*                              identifiers can be OR'd together.
* @param timeout_in_usecs [I] - The timeout in microseconds to wait for the channel.
*
* @return INPHI_OK if the link is ready, INPHI_ERROR if the link is not ready.
*
*/
inphi_status_t por_channel_wait_for_link_ready(
    uint32_t   die,
    uint32_t   channel,
    e_por_intf intf,
    uint32_t   timeout_in_usecs);


/**
 * Link status
 */
typedef struct
{
    // Top Level
    /** FW Lock
    * - true if all enabled interfaces/channels locked
    * - false otherwise
    */
    bool fw_lock;

    // HRX
    /** Signal detect status
     * - true if there is a signal present on the Rx
     * - false otherwise.
     *
     * The FW will not attempt to acquire lock unless this is true.
     */
    bool hrx_sdt[POR_MAX_HRX_CHANNELS+1];
    /** VCO tuning complete
     * - true if using a local refclk and the RTL tuning FSM has been completed.
     * - false only if there is some kind of HW fault preventing the correct VCO freq from being determined.
     *
     * VCO tuning is only done after the refclk and desired data rate has been sent to the FW by the API.
     * If this is false the FW will not be able to configure the channel: you should check the power supplies
     * and refclk stability.
     *
     * VCO tuning is not run when using refless. In that case the FW will find the correct VCO freq by
     * looking at the data directly and this status can be ignored.
     */
    bool hrx_vco_lock[POR_MAX_HRX_CHANNELS+1];
    /** Debounced analog CDR lock detect
     * - true if the analog circuitry has switched from local reference to data lock and is locked to that data.
     * - false when the analog is attempting to lock.
     *
     * This should only be used as a debug step; the CDR state will be reset periodically while the FW is
     * attempting to acquire lock.
     *
     * This should be ignored in refless mode, in that mode there is no reference to determine if the CDR is
     * locked or not.
     */
    bool hrx_cdr_lock[POR_MAX_HRX_CHANNELS+1];
    /** FW has determined that the channel is locked and ready to pass traffic.
     * - true if FW is in data/mission mode.
     * - false otherwise
     *
     * The FW will only set this when all the above status signals are true (SDT, VCO lock, CDR lock) and when
     * data/mission mode adaptation has stabilized. This status will be valid in all modes and configurations,
     * including refless where the VCO/CDR lock aren't used.
     */
    bool hrx_fw_lock[POR_MAX_HRX_CHANNELS+1];

    /** PLL lock
     *
     * This is similar to the hrx_vco_lock, however unlike the Tx PLLs the clock is either based off a refclk
     * (in local clock mode) or off of the MRX recovered clock (in refless clock mode). This is the lower
     * level HW lock indicator and should be used for debugging only.
     *
     */
    bool hrx_pll_lock[POR_MAX_HRX_CHANNELS+1];

    /** PLL FSM state
     *
     * This is the current state of the HRX PLL FSM.
     *
     */
    uint8_t hrx_pll_fsm_state[POR_MAX_HRX_CHANNELS+1];

    /** FSM state
     *
     * This is current state of the HRX FSM state machine. This is a lower
     * level HW indicator and should be used for debugging only.
     *
     */
    uint8_t hrx_fsm_state[POR_MAX_HRX_CHANNELS+1];

    /** Number of times this channel has had to re-acquire lock.
     *
     * This is only incremented when FW has achieved lock but was interrupted for some reason (HW/FW faults,
     * loss of lock, loss of SDT, etc.). This will not continue to increment unless there is a signal present
     * on the interface.
     */
    uint8_t  hrx_reset_cnt[POR_MAX_HRX_CHANNELS+1];

    // HTX
    /** FW has determined that the channel is locked and ready to pass traffic.
     * - true if FW is in data/mission mode.
     * - false otherwise
     *
     * The FW will only set this when the Tx DSP is ready and when the upstream traffic source (LRX, HRX,
     * PRBS generator) are ready as well.
     */
    bool htx_fw_lock[POR_MAX_HTX_CHANNELS+1];
    /** PLL lock
     *
     * This is similar to the hrx_vco_lock; the upstream traffic source will send a clock to the Tx which the
     * PLL will lock to. This is the lower level HW lock indicator and should be used for debugging only.
     *
     * Technically there is one PLL per channel pair, so internal instances 0 & 1 will share a PLL. This
     * only matters for packages with all instances brought out to package channels, like the gearbox part.
     * The lock status is replicated for convenience to fill out the array.
     */
    bool htx_pll_lock[POR_MAX_HTX_CHANNELS+1];

    /** PLL FSM state
     *
     * This is the current state of the HTX PLL FSM.
     *
     */
    uint8_t htx_pll_fsm_state[POR_MAX_HTX_CHANNELS+1];

    /** FSM state
     *
     * This is current state of the HTX FSM state machine. This is a lower
     * level HW indicator and should be used for debugging only.
     *
     */
    uint8_t htx_fsm_state[POR_MAX_HTX_CHANNELS+1];


    /** Number of times this channel has had to re-acquire lock.
     *
     * This is only incremented when FW has achieved lock but was interrupted for some reason (HW/FW faults,
     * loss of lock, loss of SDT, etc.). This will not continue to increment unless there is a signal present
     * on the interface.
     */
    uint8_t  htx_reset_cnt[POR_MAX_HTX_CHANNELS+1];

    // LTX
    /** FW has determined that the channel is locked and ready to pass traffic.
     * - true if FW is in data/mission mode.
     * - false otherwise
     *
     * The FW will only set this when the Tx DSP is ready and when the upstream traffic source (LRX, HRX,
     * PRBS generator) are ready as well.
     */
    bool ltx_fw_lock[POR_MAX_LTX_CHANNELS+1];
    /** PLL lock
     *
     * This is similar to the hrx_vco_lock; the upstream traffic source will send a clock to the Tx which the
     * PLL will lock to. This is the lower level HW lock indicator and should be used for debugging only.
     *
     */
    bool ltx_pll_lock[POR_MAX_LTX_CHANNELS+1];

    /** PLL FSM state
     *
     * This is the current state of the LTX PLL FSM.
     *
     */
    uint8_t ltx_pll_fsm_state[POR_MAX_LTX_CHANNELS+1];

    /** FSM state
     *
     * This is current state of the LTX FSM state machine. This is a lower
     * level HW indicator and should be used for debugging only.
     *
     */
    uint8_t ltx_fsm_state[POR_MAX_LTX_CHANNELS+1];

    /** Number of times this channel has had to re-acquire lock.
     *
     * This is only incremented when FW has achieved lock but was interrupted for some reason (HW/FW faults,
     * loss of lock, loss of SDT, etc.). This will not continue to increment unless there is a signal present
     * on the interface.
     */
    uint8_t  ltx_reset_cnt[POR_MAX_LTX_CHANNELS+1];

    // LRX
    /** Signal detect status
     * - true if there is a signal present on the Rx
     * - false otherwise.
     *
     * The FW will not attempt to acquire lock unless this is true.
     */
    bool lrx_sdt[POR_MAX_LRX_CHANNELS+1];
    /** DSP status
     * - true if the DSP is locked and running adaptation
     * - false if the DSP is attempting to lock or is unable to maintain lock
     *
     * Unlike the HRx, the LRx has a HW FSM DSP that runs continuously in the background. This will be set
     * when the HW is locked to the incoming signal and is running the continuous adaptation FSMs.
     * Only use this for debugging, see lrx_fw_lock below.
     */
    bool lrx_dsp_ready[POR_MAX_LRX_CHANNELS+1];
    /** FW has determined that the channel is locked and ready to pass traffic.
     * - true if FW is in data/mission mode.
     * - false otherwise
     *
     * The FW will only set this when all the above status signals are true (SDT, DSP ready) and when
     * data/mission mode adaptation has stabilized. This status will be valid in all modes and configurations,
     * including refless where the LRx relies on a clock from the HRx.
     */
    bool lrx_fw_lock[POR_MAX_LRX_CHANNELS+1];
    /** PLL lock
     *
     * This is similar to the hrx_vco_lock, however unlike the Tx PLLs the clock is either based off a refclk
     * (in local clock mode) or off of the HRx recovered clock (in refless clock mode). This is the lower
     * level HW lock indicator and should be used for debugging only.
     *
     */
    bool lrx_pll_lock[POR_MAX_LRX_CHANNELS+1];

    /** PLL FSM state
     *
     * This is the current state of the LRX PLL FSM.
     *
     */
    uint8_t lrx_pll_fsm_state[POR_MAX_LRX_CHANNELS+1];

    /** FSM state
     *
     * This is current state of the LRX FSM state machine. This is a lower
     * level HW indicator and should be used for debugging only.
     *
     */
    uint8_t lrx_fsm_state[POR_MAX_LRX_CHANNELS+1];

    /** Number of times this channel has had to re-acquire lock.
     *
     * This is only incremented when FW has achieved lock but was interrupted for some reason (HW/FW faults,
     * loss of lock, loss of SDT, etc.). This will not continue to increment unless there is a signal present
     * on the interface.
     */
    uint8_t  lrx_reset_cnt[POR_MAX_LRX_CHANNELS+1];

    /**
     * Set when the FEC IG PCS/AM/FEC is locked and ready to pass traffic
     */
    bool ig_fw_lock;

    /**
     * Number of times the IG FEC interface has had to reacquire lock
     */
    uint8_t ig_fw_reset_count;

    /**
     * Set when the FEC EG PCS/AM/FEC is locked and ready to pass traffic
     */
    bool eg_fw_lock;

    /**
     * Number of times the EG FEC interface has had to reacquire lock
     */
    uint8_t eg_fw_reset_count;

} por_link_status_t;

/**
 * This method may be called to query the current link status
 * of the interfaces of the device.
 *
 * @param die         [I] - The ASIC die being accessed.
 * @param link_status [O] - Pointer to the link status. Elements are indexed by package channel.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_link_status_query(
    uint32_t die,
    por_link_status_t* link_status);

/**
 * This method may be called to verify that the FW status
 * is ok. If not, a dump of the FW status is performed.
 *
 * To determine if the FW is ok, the following is checked:
 *
 * - Check that it's in application mode (ACC0)
 * - Check that there is no exception
 * - Check that the HL_STATE (FW high-level state) reg is not 0xffff (stuck in startup)
 * - Check that the loop counter is incrementing
 * - Read, wait 10ms, read loop counter again
*
 * @param die         [I] - The ASIC die being accessed.
 *
 * @return true when FW ok, false on FW not ok.
 *
 * @since 0.1
 */
bool por_is_fw_running_ok(
    uint32_t die);

/**
 * This method is called to block waiting for the f/w to be
 * running in application mode. This is useful when switching
 * f/w modes or when programming the application firmware image.
 *
 * @param die           [I] - The ASIC die being accessed.
 * @param timeout_in_ms [I] - The maximum timeout in milli-seconds
 *                            to block waiting for the application image to
 *                            startup.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_mcu_block_application_mode(
    uint32_t die,
    uint32_t timeout_in_ms);


#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1
/**
 * This method may be called to print the current link status
 * of the interfaces of the device.
 *
 * @param die         [I] - The ASIC die being accessed.
 * @param link_status [I] - Pointer to the link status. Note that the link_status elements are
 *                          all 0-based regardless of the package type.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 *
 * @since 0.1
 *
 */
inphi_status_t por_link_status_print(
    uint32_t die,
    por_link_status_t* link_status);

/**
 * This method may be called to query then print the current link status
 * of the interfaces of the device.
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 *
 * @since 0.1
 *
 */
inphi_status_t por_link_status_query_dump(
    uint32_t die);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)


/**
 * @h2 PRBS Generator/checker
 * =======================================================
 *
 * @brief
 * PRBS synthetic pattern types.
 *
 * @{note,
 * The value of these PRBS polynomial types are abstracted from the hardware because
 * the line side (LRX) checker config is different from the host side (HRX) checker and
 * host and line side generators (HTX, LTX) config. For this reason we use a common
 * enum decoupled from the hardware (ie synthetic) to enumerate the pattern types.}
 */
typedef enum
{

    /** PRBS x^31+x^28+1 */
    POR_PAT_PRBS31                = 0,
    /** PRBS x^7+x^6+1 */
    POR_PAT_PRBS7                 = 1,
    /** PRBS x^9+x^5+1 */
    POR_PAT_PRBS9_5               = 2,
    /** PRBS x^9+x^4+1 */
    POR_PAT_PRBS9_4               = 3,
    /** PRBS x^11+x^9+1 */
    POR_PAT_PRBS11                = 4,
    /** PRBS x^13+x^12+x^2+x+1 */
    POR_PAT_PRBS13                = 5,
    /** PRBS x^15+x^4+1 */
    POR_PAT_PRBS15                = 6,
    /** PRBS x^23+x^18+1 */
    POR_PAT_PRBS23                = 7,
    /** PRBS x^58+x^39+1*/
    POR_PAT_PRBS58                = 8,
    /** PRBS x^16+x^5+x^3+x^2+1 */
    POR_PAT_PRBS16                = 9,
    /** Invalid PRBS pattern */ 
    POR_PAT_NONE                  = 10

} e_por_prbs_pat;

/**
 * Tx PRBS pattern modes
 */
typedef enum
{
    /** PRBS pattern modes */
    POR_PRBS_PATTERN_PRBS   = 0,
    /** Programmable fixed pattern mode */
    POR_PRBS_PATTERN_FIXED  = 1,
    /** JP03B test pattern. IEEE 802.3bs Clause 120.5.10.2.2*/
    POR_PRBS_PATTERN_JP083B = 2,
    /** Transmitter linearity test pattern. IEEE 802.3bs Clause 120.5.10.2.4 */
    POR_PRBS_PATTERN_LIN    = 3,
    /** CID jitter tolerance test pattern. OIF-CEI-3.1 Sections 2.1.1.1 and 2.5.1.1 */
    POR_PRBS_PATTERN_CJT    = 4,
    /** SSPRQ pattern, IEEE 802.3bs Clause 120.5.11.2.3 */
    POR_PRBS_PATTERN_SSPRQ  = 5,

} e_por_prbs_pat_mode;

/**
 * Line Rx PRBS checker modes
 */
typedef enum
{
    /** PRBS mode for individual MSB/LSB bit streams in a PAM-4 symbol */
    POR_PRBS_MODE_MSB_LSB   = 0,
    /** PRBS mode for a combined PAM-4 symbol */
    POR_PRBS_MODE_COMBINED  = 1

} e_por_rx_prbs_mode;

/**
 * Tx error injection patterns
 */
typedef enum
{
    /** Bit 0 (one MSB). 0x0000_0000_0000_0001 */
    POR_ERRINJ_PAT_BIT0  = 0,
    /** Bit 1 (one LSB). 0x0000_0000_0000_0002 */
    POR_ERRINJ_PAT_BIT1  = 1,
    /** Bits 0 and 1 (one PAM4 symbol). 0x0000_0000_0000_0003 */
    POR_ERRINJ_PAT_BIT01 = 2,
    /** All MSBs. 0x5555_5555_5555_5555 */
    POR_ERRINJ_PAT_MSBS  = 3,
    /** All LSBs. 0xAAAA_AAAA_AAAA_AAAA */
    POR_ERRINJ_PAT_LSBS  = 4,
    /** All bits. 0xFFFF_FFFF_FFFF_FFFF */
    POR_ERRINJ_PAT_ALL   = 5,
    /** One bit per word. The position shifts right each time an error is injected */
    POR_ERRINJ_PAT_WALK  = 6,
    /** One 2-bit PAM4 symbol per word. The position shift right two bits each time an error is injected */
    POR_ERRINJ_PAT_WALK3 = 7

} e_por_tx_err_inj_pat;

/**
 * This structure is used to configure one
 * of the pattern generators on the device.
 */
typedef struct
{
    /**
     * In combined mode this enables
     * the PRBS generator.
     *
     * In MSB/LSB mode this enables the LSB/MSB pattern
     * generation.
     */
    bool en;

    /**
     * If operating in MSB/LSB mode this enables
     * the MSB/LSB pattern. These will generally
     * be enabled at the same time but can be controlled
     * independently if required.
     */
    bool gen_en_lsb;

    /**
     * Setup the pattern generator to operate in
     * either MSB/LSB or Combined mode:
     */
    e_por_rx_prbs_mode prbs_mode;

    /** The LSB PRBS pattern to transmit */
    e_por_prbs_pat prbs_pattern_lsb;

    /** The PRBS pattern to transmit */
    e_por_prbs_pat prbs_pattern;

    /** * Selects the type of test pattern that is generated. */
    e_por_prbs_pat_mode pattern_mode;

    /** Specifies the fixed pattern word value that the fixed pattern checker attempts to lock to.
     *  Bit 63 is expected to be received first. The default corresponds to the JP03A pattern described
     *  in IEEE 802.3bs Clause 120.5.10.2.1. */
    uint16_t fixed0_pat0;
    uint16_t fixed0_pat1;
    uint16_t fixed0_pat2;
    uint16_t fixed0_pat3;
    uint16_t fixed1_pat0;
    uint16_t fixed1_pat1;
    uint16_t fixed1_pat2;
    uint16_t fixed1_pat3;

    /** Number of times to repeat the fixed0_pat pattern */
    uint8_t fixed0_pat_repeat;

    /** Number of times to repeat the fixed1_pat pattern */
    uint8_t fixed1_pat_repeat;

} por_tx_prbs_gen_rules_t;

/**
 * Host Rx PRBS checker auto-polarity thresholds
 */
typedef enum
{
    /** More than 9 consecutive 64 bit words with one or more errors each */
    POR_PRBS_AUTO_POLARITY_9   = 0,
    /** More than 17 consecutive 64 bit words with one or more errors each */
    POR_PRBS_AUTO_POLARITY_17  = 1,
    /** More than 33  consecutive 64 bit words with one or more errors each */
    POR_PRBS_AUTO_POLARITY_33  = 2,
    /** More than 65 consecutive 64 bit words with one or more errors each */
    POR_PRBS_AUTO_POLARITY_65  = 3,

} e_por_hrx_prbs_auto_pol_thresh;


/**
 * rules specific to the host rx checker
 */
typedef struct
{

    /** Enables the auto polarity detection feature of the PRBS checker. After a consecutive number of
      * errors (programmable by auto_polarity_thresh) the polarity is inverted. */
    bool auto_polarity_en;

    /** When out of sync this controls the threshold for toggling the receive data polarity in auto
     *  polarity mode. Every 64 bits (a "word") is checked for an error and if a certain number of
     *  consecutive words contain errors then the polarity is toggled. In NRZ mode a word is 64 bits
     *  and in PAM4 mode a word is 32 symbols, i.e. 64 bits too. Caution: the alignment of serial bits
     *  to words is effectively random so, for example, two errors 10 bits apart may look like one
     *  word with two errors or two consecutive words with one error each.
     */
    e_por_hrx_prbs_auto_pol_thresh auto_polarity_thresh;

    /** Selects the type of test pattern that is generated. */
    e_por_prbs_pat_mode pattern_mode;

    /** Specifies the fixed pattern word value that the fixed pattern checker attempts to lock to.
     *  Bit 63 is expected to be received first. The default corresponds to the JP03A pattern described
     *  in IEEE 802.3bs Clause 120.5.10.2.1. */
    uint16_t fixed_pat0;
    uint16_t fixed_pat1;
    uint16_t fixed_pat2;
    uint16_t fixed_pat3;

    /** Controls the number of bit errors in one parallel data bus sample that cause a transition to the
     * out of sync state. If more errors are found in one cycle than this value the transition occurs.
     * Applies to the PRBS and fixed pattern checker state machines. Note that the alignment of the
     * received data to the 64-bit word boundaries is not predictable. So, for example, two adjacent
     * errors in the incoming serial stream may show up in one 64-bit word (which will declare two mismatches
     * in that word) or may show up in two consecutive 64-bit words (each of which will declare just one mismatch). */
    uint8_t oos_thresh;

} por_hrx_prbs_chk_advanced_rules_t;

/**
 * rules specific to the line rx checker
 */
typedef struct
{

    /** Error threshold of PRBS interrupt */
    uint8_t prbs_err_th_irq;

    /** enable PRBS auto lock mode */
    bool prbs_auto_lock;

    /** Threshold of number of errors for PRBS lock Note: Must be non-zero values */
    uint8_t prbs_err_th_lock;

    /** Threshold of number of cycles for PRBS lock */
    uint8_t prbs_cyc_th_lock;

} por_lrx_prbs_chk_advanced_rules_t;


/**
 * Rx PRBS checker rules
 */
typedef struct
{
    /** Enables the PRBS checker. */
    bool en;

    /** Enables separate PRBS generation on MSB and LSB bits (PAM4 MSB and LSB). When 0, a single
      * PRBS stream is generated. */
    e_por_rx_prbs_mode prbs_mode;

    /** Inverts the receive bit pattern ahead of the PRBS checker if auto polarity is not enabled. */
    bool prbs_inv;

    /** Selects the PRBS polynomial for LSB bits (PAM4 symbol LSB) when dual PRBS mode is enabled. */
    e_por_prbs_pat prbs_pattern_lsb;

    /** Selects the PRBS polynomial when not in dual PRBS mode or for MSB bits when in dual PRBS mode
      * (PAM4 symbol MSB) */
    e_por_prbs_pat prbs_pattern;

    /** rules specific to the line rx checker */
    por_lrx_prbs_chk_advanced_rules_t lrx_advanced;

    /** rules specific to the host rx checker */
    por_hrx_prbs_chk_advanced_rules_t hrx_advanced;

} por_rx_prbs_chk_rules_t;


/**
 * Host and line Rx PRBS checker status
 */
typedef struct
{
    /** PRBS mode for individual MSB/LSB or combined bit streams */
    e_por_rx_prbs_mode prbs_mode;

    /** PRBS lock status */
    bool prbs_lock;

    /** PRBS lock status (LSB) */
    bool prbs_lock_lsb;

    /** Fixed pattern sync */
    uint8_t prbs_fixed_pat_sync;

    /** Received PRBS pattern */
    e_por_prbs_pat prbs_pattern;

    /** Received PRBS pattern (LSB) */
    e_por_prbs_pat prbs_pattern_lsb;

    /** Flag to indicate if the prbs total bit counter has saturated */
    bool prbs_total_bit_count_saturated;

    /** PRBS bit error counter */
    uint32_t prbs_error_bit_count;

    /** PRBS errored bit counter (LSB) */
    uint32_t prbs_error_bit_count_lsb;

    /** PRBS total bit counter */
    uint64_t prbs_total_bit_count;

    /** Received PRBS invert status */
    uint8_t prbs_inv;

    /** Received PRBS invert status (LSB) */
    uint8_t prbs_inv_lsb;

} por_rx_prbs_chk_status_t;


/**
 * This method is used to set the PRBS generator rules to their default values.
 *
 * @param rules [I/O] - The PRBS generator rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_tx_prbs_rules_set_default(
    por_tx_prbs_gen_rules_t* rules);

/**
 * This method is used to configure the PRBS generator.
 *
 * @{note,
 * You may want to squelch the transmitter before disabling the PRBS generator.
 * This will prevent the transmitter from emitting garbage to a downstream device}
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The channel number, range 0..3.
 * @param intf    [I] - The line or host interface, see e_por_intf enum.
 * @param rules   [I] - The generator rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_tx_prbs_gen_config(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_tx_prbs_gen_rules_t* rules);

/**
 * This method is called to inject errors into the TX datapath.
 *
 * @param die      [I] - The die of the ASIC being accessed.
 * @param channel  [I] - The channel to inject errors on
 * @param intf     [I] - The direction to inject errors on (POR_INTF_LTX or POR_INTF_HTX)
 * @param enable   [I] - Turn the injector on/off
 * @param pattern  [I] - The pattern to inject
 * @param gap      [I] - Number of 64-bit words without errors to insert between words with errors
 * @param duration [I] - Number of 64-bit words to inject errors on
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure
 *
 * @since 0.1
 */
inphi_status_t por_tx_error_inject(
    uint32_t             die,
    uint32_t             channel,
    e_por_intf           intf,
    bool                 enable,
    e_por_tx_err_inj_pat pattern,
    uint8_t              gap,
    uint8_t              duration);

/**
 * This method is used to set the PRBS checker rules to their default values.
 *
 * @param rx_rules [I/O] - The PRBS checker rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_rx_prbs_rules_set_default(
    por_rx_prbs_chk_rules_t* rx_rules);

/**
 * This method is used to configure the PRBS checker.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The channel number
 * @param intf    [I] - The line or host interface, see e_por_intf enum.
 * @param rules   [I] - The checker rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_rx_prbs_chk_config(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_rx_prbs_chk_rules_t* rules);

/**
 * This method is used to get the PRBS checker status.
 *
 * @param die        [I] - The physical ASIC die being accessed.
 * @param channel    [I] - The channel number, range 0..3.
 * @param intf       [I] - The line or host interface, see e_por_intf enum.
 * @param chk_status [O] - The checker status.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_rx_prbs_chk_status(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_rx_prbs_chk_status_t* chk_status);

/**
 * This method is used to Auto detect the HRX PRBS pattern, if any
 *
 * @param die        [I] - The physical ASIC die being accessed.
 * @param channel    [I] - The channel number, range 0..3.
 * @param is_lsb     [I] - MSB (combined) or LSB (odd)
 *
 * @return prbs_pattern, see e_por_prbs_pat prbs_pattern enum
 *
 * @since 0.1
 */
e_por_prbs_pat por_hrx_prbs_pat_auto_detect(
    uint32_t die,
    uint32_t channel,
    bool is_lsb);


#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
/**
 * This method figures out the BER based on the PRBS checker status.
 *
 * @param chk_status    [I] - The checker status.
 * @param ber           [O] - The BER (MSB or combined)
 * @param ber_lsb       [O] - The BER (LSB)
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @requires
 * The API must be have floating point support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_FLOATING_POINT=1
 */
inphi_status_t por_rx_prbs_ber(
    por_rx_prbs_chk_status_t *chk_status,
    double *ber,
    double *ber_lsb);
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/**
 * This method is used to dump the PRBS checker status.
 *
 * @param die           [I] - The physical ASIC die being accessed.
 * @param channel       [I] - The channel number, range 0..3.
 * @param intf          [I] - The line or host interface, see e_por_intf enum.
 * @param chk_status    [I] - The checker status.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
inphi_status_t por_rx_prbs_chk_status_print(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_rx_prbs_chk_status_t* chk_status);

/**
 * This method is used to query and dump the PRBS checker status for all channels.
 *
 * @param die           [I] - The physical ASIC die being accessed.
 * @param intf          [I] - The line or host interface, see e_por_intf enum.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
inphi_status_t por_rx_prbs_chk_status_query_all_print(
    uint32_t die,
    e_por_intf intf);


/**
 * This method is used to polls and clears the checker then dump the PRBS checker status.
 *
 * @param die           [I] - The physical ASIC die being accessed.
 * @param channel       [I] - The channel number, range 0..3.
 * @param intf          [I] - The line or host interface, see e_por_intf enum.
 * @param chk_rules     [I] - The checker rules.
 * @param gate_time_sec [I] - A delay (seconds) between status collection.
 * @param n_times       [I] - Number of time to collect status.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
inphi_status_t por_rx_prbs_chk_status_dump(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_rx_prbs_chk_rules_t* chk_rules,
    uint16_t gate_time_sec,
    uint16_t n_times);


/**
 * This is a diagnostic method used to summarize the checker statistics
 * and display them to the user for analysis.
 *
 * @param die        [I] - The physical ASIC die being accessed.
 * @param intf       [I] - The line or host interface to dump the PRBS stats for.
 * @param chk_status [I] - The array of PRBS stats structure to analyze.
 * @param start      [I] - The channel number to start dumping from.
 * @param end        [I] - The channel number to end dumping at.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
inphi_status_t por_rx_prbs_chk_summary_dump(
    uint32_t                  die,
    e_por_intf                intf,
    por_rx_prbs_chk_status_t* chk_status,
    uint32_t                  start,
    uint32_t                  end);


/**
 * @h2 Debug/diagnostic methods
 * =======================================================
 *
 * @brief
 * This is a diagnostic method to print all of the accessible registers within the device.
 *
 * @param die  [I] - The physical ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
inphi_status_t por_diags_register_dump(
    uint32_t die);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * @h2 MCU Diagnostics
 * =======================================================
 * @note
 * Many of the MCU messaging methods are only available while
 * the device is in bootloader upgrade mode. The messaging interface
 * is limited when operating in application mode.
 *
 * Use por_mcu_fw_mode_query to determine the current FW mode.
 *
 * @brief
 * Struct mimicing the one from the FW, which contains important
 * addresses for PIF accesses.
 *
 * @since 0.1
 *
 * @private
 */
typedef struct
{
    /** The address of the firmwares debug log */
    uint32_t debug_buffer_address;

    /** Address of the info buf */
    uint32_t info_buf_address;
}por_fw_info_t;

/**
 * Reads the fw_info struct from the FW.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param fw_info [O] - FW info struct read from the FW.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @private
 */
inphi_status_t por_mcu_fw_info_query(
    uint32_t       die,
    por_fw_info_t *fw_info);

#if defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)

/**
 * @h2 SPI Interface
 * =======================================================
 *
 * @brief
 * This defines the SPI clock divide ratio which controls
 * the SPI clock used to talk to an optional external EEPROM
 * to store the embedded firmware. This divides down the internal
 * MCU clock to bring it down to a rate that the external
 * EEPROM can support. Typically this will be POR_SPI_CLK_DIV_64.
 *
 * @since 1.1.0.0 
 * 
 * @requires
 * The API must be have EEPROM access support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
typedef enum
{
    /** Divide by 16 */
    POR_SPI_CLK_DIV_16 = 3,
    /** Divide by 32 */
    POR_SPI_CLK_DIV_32 = 4,
    /** Divide by 64 */
    POR_SPI_CLK_DIV_64 = 5,
    /** Divide by 128 */
    POR_SPI_CLK_DIV_128 = 6,
    /** Divide by 256 */
    POR_SPI_CLK_DIV_256 = 7
} e_por_spi_clk_div;

/**
 * This method is used to read an block of data from the
 * external EEPROM (if it is present).
 *
 * @param die         [I] - The physical ASIC die being accessed.
 * @param eeprom_addr [I] - The EEPROM address to access.
 * @param words       [I] - The buffer to read the SPI
 *                          data into.
 * @param num_words   [I] - The number of 32 bit words to read
 *                          from EEPROM.
 * @param clkdiv      [I] - The SPI clock divide ratio.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.1.0.0
 * 
 * @requires
 * The API must have EEPROM access support. It must be compiled
 * with the following flags:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
inphi_status_t por_spi_read_data_block(
    uint32_t          die,
    uint32_t          eeprom_addr,
    uint32_t          *words,
    uint32_t          num_words,
    e_por_spi_clk_div clkdiv);

/**
 * This method is used to write a block of data into the
 * external EEPROM (if it is present)
 *
 * @param die         [I] - The physical ASIC die being accessed.
 * @param eeprom_addr [I] - The EEPROM address to access.
 * @param words       [I] - The array of 32 bit words to write
 *                          to the EEPROM.
 * @param num_words   [I] - The number of 32 bit words to write
 *                          to the EEPROM.
 * @param clkdiv      [I] - The SPI clock divide ratio.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.1.0.0
 *
 * @requires
 * The API must be have EEPROM access support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
inphi_status_t por_spi_write_data_block(
    uint32_t          die,
    uint32_t          eeprom_addr,
    uint32_t          *words,
    uint32_t          num_words,
    e_por_spi_clk_div clkdiv);


/**
 * This method is called to erase the EEPROM
 *
 * @param die         [I] - The physical ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
inphi_status_t por_spi_eeprom_erase(
    uint32_t die);

#endif // defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)

/**
 * @h2 DSP diagnostics
 * =======================================================
 *
 * @brief
 * This defines the DSP methods used for diagnostics.
 * 
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */

//# constants for indexing results structures
#define POR_RX_DSP_SLICES           16
#define POR_RX_DSP_NUM_FFE_TAPS     10
//# quantity of ISI taps to collect, max 48 if first = 0
#define POR_RX_DSP_QTY              48

// encoding for CP_SNR_RUN_CFG.duration
#define POR_RX_DSP_DURATION_16      0  // duration = 2^16
#define POR_RX_DSP_DURATION_15      1  // duration = 2^15
#define POR_RX_DSP_DURATION_14      2  // duration = 2^14
#define POR_RX_DSP_DURATION_13      3  // duration = 2^13
#define POR_RX_DSP_DURATION_12      4  // duration = 2^12
#define POR_RX_DSP_DURATION_11      5  // duration = 2^11
#define POR_RX_DSP_DURATION_10      6  // duration = 2^10
#define POR_RX_DSP_DURATION_9       7  // duration = 2^9


/**
 * This method is called to read the SNR monitor value from the hardware
 * and translate it to a decimal (fixed-point) dB value.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The LRX channel through the device to query.
 *
 * @return The (fixed-point) SNR value in dB
 *
 * @since 1.1.0.0
 */
uint32_t por_lrx_dsp_snr_read_db_fixp(
    uint32_t die,
    uint32_t channel);

/**
 * This method is called to read the SNR monitor value from the hardware
 * and translate it to a decimal (fixed-point) dB value.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel through the device to query.
 * @param intf    [I] - The interface (POR_INTF_LRX only for now)
 *
 * @return The (fixed-point) SNR value in dB
 *
 * @since 1.1.0.0
 */
uint32_t por_rx_dsp_snr_read_db_fixp(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf);


#if defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)
#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)
/**
 * Convert fixed-point 16.8 LTP value to a floating point double in dB.
 *
 * @param ltp [I] - LTP in 16.8 format
 *
 * @return LTP as a double in dB, INFINITY if ltp=0xffff.
 *
 * @see
 * por_rx_dsp_ltp_read_fixp to read the fixed-point ltp value.
 *
 * @requires
 * The API must be compiled with INPHI_HAS_MATH_DOT_H and INPHI_HAS_FLOATING_POINT flags.
 * This will pull in the <math.h> library which will increase the size of
 * the generated image.
 *
 * @since 1.1.0.0
 */
double por_rx_dsp_ltp_format(uint16_t ltp);
#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)
#endif // defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)


#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)
/**
 * This method is called to read the SNR monitor value from the hardware
 * and translate it to a decimal dB value.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The LRX channel through the device to query.
 *
 * @return The SNR value in dB
 *
 * @requires
 * The API must be compiled with INPHI_HAS_MATH_DOT_H and INPHI_HAS_FLOATING_POINT flags.
 * This will pull in the <math.h> library which will increase the size of
 * the generated image.
 *
 * @since 1.1.0.0
 */
double por_lrx_dsp_snr_read_db(
    uint32_t die,
    uint32_t channel);

/**
 * This method is called to read the SNR monitor value from the hardware
 * and translate it to a decimal dB value.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel through the device to query.
 * @param intf    [I] - The interface (POR_INTF_LRX only for now)
 *
 * @return The SNR value in dB
 *
 * @requires
 * The API must be compiled with INPHI_HAS_FLOATING_POINT flags.
 *
 * @since 1.1.0.0
 */
double por_rx_dsp_snr_read_db(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf);

#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)

/**
 * Read the fixed-point minimum LTP (Level Transition Parameter) on an interface/channel.
 * LTP is defined in the CMIS 4-0 spec as:
 *
 * @{pre,
 * LTP = 10*log10(min(ltp0, ltp1, ltp2))
 *   where ltp(i) = (P(i+1) + P(i))/(2*V(i))
 * }
 *
 * Returned as a 16.8 value (unsigned, 8 fractional bits) in units of 1/256dB.
 *
 * Special values:
 * - 0 is an error value, or LTP unavailable
 * - 0xFFFF is +infinity, where V(i)=0
 * - 0xFFFE is a large dB value > 255.996dB
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel through the device to query.
 * @param intf    [I] - The interface (POR_INTF_LRX only for now)
 * @param ltp     [O] - Minimum LTP
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @see
 * por_rx_dsp_ltp_format to convert to a double value.
 *
 * @since 1.1.0.0 
 */
inphi_status_t por_rx_dsp_ltp_read_fixp(uint32_t die, uint32_t channel, e_por_intf intf, uint16_t *ltp);

/**
 * @h3 LRX FFE Taps
 * ========================================================
 * This section contains routines used to query the LRX FFE
 * tap values for each of the 32 FFE sub-channels
 *
 * Query the FFE taps
 *
 * To get a floating point value for the ffe_tap divide by 64.0
 *
 * @param die             [I] - The ASIC die being accessed.
 * @param channel         [I] - The channel through the device to query.
 * @param ffe_tap         [O] - The array of [16x10] taps to populate (S7.6 format)
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_lrx_dsp_ffe_taps_query(
    uint32_t die,
    uint32_t channel,
    int16_t  ffe_tap[POR_RX_DSP_SLICES*POR_RX_DSP_NUM_FFE_TAPS]);

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

/**
 * Print the FFE taps for a particulr channel and FFE sub-channel
 *
 * @param die             [I] - The ASIC die being accessed.
 * @param channel         [I] - The channel through the device to query.
 * @param ffe_taps        [I] - The array of FFE taps queried via the
 *                              por_lrx_dsp_ffe_taps_query method.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @see por_lrx_dsp_ffe_taps_query
 *
 * @requires
 * The API must be compiled with the following compilation define:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS == 1
 *
 * @since 0.1
 */
inphi_status_t por_lrx_dsp_ffe_taps_print(
    uint32_t die,
    uint32_t channel,
    int16_t  ffe_taps[POR_RX_DSP_SLICES*POR_RX_DSP_NUM_FFE_TAPS]);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

/**
 * @h3 LRX VGA Diagnostics
 * ============================================================
 * This section contains routines used to query the Line Rx VGA
 *
 * @brief
 * VGA 
 */
/**
 * This method is called to read the raw VGA1 value from
 * the hardware for the input channel. The return value is NOT in dB.
 *
 * @param die       [I] - The ASIC die being accessed.
 * @param channel   [I] - The channel through the device to query.
 * @param vga1_gain [O] - The read vga1_gain value from HW
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 */
inphi_status_t por_lrx_dsp_vga1_query(
    uint32_t die,
    uint32_t channel,
    uint16_t* vga1_gain);

/**
 * @h3 LRX Histogram
 * =======================================================
 * The following methods are used to manage capturing and
 * displaying the LRX histogram.
 *
 * @brief
 * Initialize then capture the LRX DSP histogram.
 * Note that this method captures the histogram data from the HW.
 *
 * @param die        [I] - The ASIC die being accessed.
 * @param channel    [I] - The channel through the device to query.
 * @param hist_data  [O] - Array of exactly [16x256] entries of uint32_t.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 */
inphi_status_t por_lrx_dsp_get_histogram(
    uint32_t die,
    uint32_t channel,
    uint32_t *hist_data);



/**
 * @h2 Host RX
 * =======================================================
 *
 * @h3 HRX Pulse Response
 * =======================================================
 * The pulse response interface can be used to help tune
 * the transmit taps on the host interface.
 *
 * @brief
 * This method queries the pulse response values from the FW
 * for a particular channel.
 *
 * @param die         [I]   - The physical ASIC die being accessed.
 * @param channel     [I]   - Channel that was used in the info request.
 * @param resp_values [O]   - Resulting response values, must be able to hold len elements (<=19).
 * @param len         [I/O] - Number of elements in resp_values (0<len<=19), is set to num of elements the FW sent.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 */
inphi_status_t por_hrx_pulse_resp_query(
    uint32_t die,
    uint32_t channel,
    int32_t* resp_values,
    int32_t* len);

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

/**
 * This method is called to query the pulse response for a range of
 * channels on the device and prints them.
 *
 * @param die   [I] - The physical ASIC die being accessed.
 * @param start [I] - The channel to start querying the pulse response from.
 * @param end   [I] - The channel to end querying the pulse response from.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 */
inphi_status_t por_hrx_pulse_resp_query_dump_range(
    uint32_t die,
    uint32_t start,
    uint32_t end);

/**
 * This method is called to query the pulse response for all host
 * channels and prints them.
 *
 * @param die   [I] - The physical ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 */
inphi_status_t por_hrx_pulse_resp_query_dump(
    uint32_t die);



#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

/**
 * @h2 FEC
 * =======================================================
 *
 * @h3 FW FEC stats polling (CMIS VDM)
 *
 * The following structures are used for polling stats inside the FW and pulling the min/max/accumulated/current
 * stats out of the FW and into the API.
 * 
 * @h4 Poll timing
 *
 * interval_time and accumulation_time work together to define the duty cycle of the FEC HW, that is the
 * amount of time the FEC HW is on and accumulating FEC error statistics.
 *
 * interval_time represents the amount of time the FEC will be OFF,
 * and when it expires the FEC HW will be turned back on. accumulation_time is the amount of time the FEC
 * will remain on (not including the FEC lock time) and the stats will be accumulated in the HW counters.
 * At the end of the accumulation_time, the HW counters are read by the FW and saved to the FWs internal
 * stats counters. These FW stats counters are large enough to accumulate ~1 year of stats (64bit ints).
 *
 * Here's an example of a non-zero interval_time (aka low power mode), where the FEC is dynamically turned
 * on and off by the FW. You can see that the FEC stats HW is accumulating only when the FEC is locked and the
 * accumulation_time is counting. The interval_time is kept short here for demonstration purposes, however
 * it can be set to anything from 0 to 14000ms. The ratio between the interval_timer and the accumulation_time
 * forms the duty cycle of the FEC, in this example it's ~50%.
 *
 * @note
 * interval_time can only be non-zero when your FEC output mode is set to POR_FEC_BYPASS. If you use
 * POR_FEC_REGEN (like in POR_MODE_100G_PCS4_TO_KP1) then a non-zero interval_time may cause the FEC traffic
 * to drop. A POR_FEC_REGEN mode *cannot* use low-power FEC stats monitoring.
 *
 * @text
 * Here's an example of a zero interval_time (aka high power mode), where the FEC is left on all the time.
 * The benefit of this approach is no FEC error events will be lost, as each snapshot & accumulate is atomic.
 * In this mode the FW can be left accumulating for as long as needed before a call to por_fec_stats_poller_request
 * (with clear_on_read=true) or por_fec_stats_poller_clear is needed.
 *
 * @note
 * The FW stats counter sizes allow for a considerable amount of accumulation time (~1 year), however you must
 * design your VDM system software to clear the internal FW stats at some point. Catching a stats overflow after
 * a year of operation will be difficult to debug!
 *
 * @brief
 * Rules for configuring the FEC stats polling in the FW.
 */
typedef struct
{
    /**
     * Enable FW FEC stats collection.
     *
     * Note your main configuration rules (ie the rules used for por_enter_operational_state) need
     * to have the FEC block enabled in order for stats collection to work. You do not need to be
     * in POR_FEC_REGEN mode; POR_FEC_BYPASS will work for stats monitoring. See por_fec_rules_t.
     */
    bool en;

    /**
     * Amount of time the FEC HW will be left **off**.
     * - When accumulation_time elapses, FEC HW is turned off and interval_time is started again.
     * - When interval_time elapses, FEC HW is turned on and accumulation_time is started.
     *
     * In milliseconds, must be less than 14000.
     *
     * 0 means the accumulation_time is triggered periodically and the FEC HW is left ON.
     * More than 0 means the FEC is turned off (if you are in POR_FEC_BYPASS mode) while interval_time is running.
     *
     * Values < 50 may be inaccurate. The actual amount of time the FEC HW will be left off will always be >
     * interval_time.
     */
    uint32_t interval_time;

    /**
     * Amount of time the FEC HW will be **on** and accumulating error stats.
     * - When interval_time elapses, FEC HW is turned on and accumulation_time is started.
     * - When accumulation_time elapses, FEC HW is turned off and interval_time is started again.
     *
     * In milliseconds, must be less than 14000.
     *
     * Must be greater than 0, 0 is invalid.
     *
     * Values less than 10ms will be very inaccurate and may impact FW performance, please use >= 10. The
     * actual amount of time the FEC HW will be left on and accumulating stats will always be > accumulation_time.
     */
    uint32_t accumulation_time;
} por_fec_stats_poller_rules_t;

/**        
 * Configure the internal FW FEC stats polling.
 *
 * This can be done any time after por_init. If a previous call has enabled the FEC stats polling in the FW
 * a call to this method will simply change the timer durations and trigger a new polling cycle, it will not
 * clear the already accumulated FEC stats saved by the FW.
 *
 * @{note, As soon as the FW FEC stats polling is enabled, you MUST NOT use the
 * snapshot_all or snapshot_intf methods on the FEC intf being polled by the
 * FW. Otherwise the FW may miss some FEC stats.}
 *
 * @param die         [I] - The ASIC die being accessed.
 * @param intf        [I] - The interface being accessed, must be POR_INTF_EG_FEC or POR_INTF_IG_FEC.
 * @param stats_rules [I] - The rules being used to configure the poller.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 */
inphi_status_t por_fec_stats_poller_cfg(
    uint32_t   die,
    e_por_intf intf,
    const por_fec_stats_poller_rules_t *stats_rules);

/**
 * FEC stats, pre-formatted in the correct CMIS F16 format. Can be presented to the CMIS interface directly
 * without conversion.
 *
 * F16 is a 16bit floating point format with:
 * - bits[15:11] as exponent (e), biased by o
 * - bits[10:0] as mantissa
 * 
 * Where the resulting value is defined as
 *   value = m*10^(e+o)
 * And o = -24. If e=31, m=2047 then the value is +infinity. If e=31, m=0 then the value is NaN.
 *
 * There is an example conversion function (float_2_cmis_f16) in por_api.c included in this API package, as well
 * as the inverse function (cmis_f16_to_float) used for por_fec_stats_poller_calc_ber.
 *
 * This structure is defined in the order it is retrieved from FW memory.
 */
typedef struct {

    //preamble
    /** Poll count, gets incremented every time the poller snapshots the FEC HW registers
     * and cleared along with the rest of the saved/accumulated FEC stats.
     */
    uint32_t poll_count;

    //block 0
    /** Average Bit Error Rate */
    uint16_t ber_avg;
    /** Average number of errored Frames (FERC) */
    uint16_t ferc_avg;

    //block 1
    /** Current Bit Error Rate */
    uint16_t ber_curr;
    /** Current number of errored Frames (FERC) */
    uint16_t ferc_curr;

    //block 2
    /** Max Bit Error Rate */
    uint16_t ber_max;
    /** Max number of errored Frames (FERC) */
    uint16_t ferc_max;

    //block 3
    /** Min Bit Error Rate */
    uint16_t ber_min;
    /** Min number of errored Frames (FERC) */
    uint16_t ferc_min;

    //block 4
    /** Corrected CW rate for N number of bits */
    uint16_t corr_cw_hist_15_curr;
    uint16_t corr_cw_hist_15_avg;
    uint16_t corr_cw_hist_15_max;
    uint16_t corr_cw_hist_14_curr;
    uint16_t corr_cw_hist_14_avg;
    uint16_t corr_cw_hist_14_max;
    uint16_t corr_cw_hist_13_curr;
    uint16_t corr_cw_hist_13_avg;
    uint16_t corr_cw_hist_13_max;
    uint16_t corr_cw_hist_12_curr;
    uint16_t corr_cw_hist_12_avg;
    uint16_t corr_cw_hist_12_max;

    //block 5
    uint16_t corr_cw_hist_11_curr;
    uint16_t corr_cw_hist_11_avg;
    uint16_t corr_cw_hist_11_max;
    uint16_t corr_cw_hist_10_curr;
    uint16_t corr_cw_hist_10_avg;
    uint16_t corr_cw_hist_10_max;
    uint16_t corr_cw_hist_9_curr;
    uint16_t corr_cw_hist_9_avg;
    uint16_t corr_cw_hist_9_max;
    uint16_t corr_cw_hist_8_curr;
    uint16_t corr_cw_hist_8_avg;
    uint16_t corr_cw_hist_8_max;
    uint16_t corr_cw_hist_7_curr;
    uint16_t corr_cw_hist_7_avg;
    uint16_t corr_cw_hist_7_max;
    /** Current Symbol Error Rate */
    uint16_t ser_curr;
    /** Average Symbol Error Rate */
    uint16_t ser_avg;
    /** Max Symbol Error Rate */
    uint16_t ser_max;

    //block 6
    /** Corrected CW rate for N number of bits */
    uint16_t corr_cw_hist_6_curr;
    uint16_t corr_cw_hist_6_avg;
    uint16_t corr_cw_hist_6_max;
    uint16_t corr_cw_hist_5_curr;
    uint16_t corr_cw_hist_5_avg;
    uint16_t corr_cw_hist_5_max;
    uint16_t corr_cw_hist_4_curr;
    uint16_t corr_cw_hist_4_avg;
    uint16_t corr_cw_hist_4_max;
    uint16_t corr_cw_hist_3_curr;
    uint16_t corr_cw_hist_3_avg;
    uint16_t corr_cw_hist_3_max;
    uint16_t corr_cw_hist_2_curr;
    uint16_t corr_cw_hist_2_avg;
    uint16_t corr_cw_hist_2_max;
    uint16_t corr_cw_hist_1_curr;
    uint16_t corr_cw_hist_1_avg;
    uint16_t corr_cw_hist_1_max;

    //block 7
    /** Min Symbol Error Rate */
    uint16_t ser_min;
    /** Corrected CW rate for N number of bits */
    uint16_t corr_cw_hist_15_min;
    uint16_t corr_cw_hist_14_min;
    uint16_t corr_cw_hist_13_min;
    uint16_t corr_cw_hist_12_min;
    uint16_t corr_cw_hist_11_min;
    uint16_t corr_cw_hist_10_min;
    uint16_t corr_cw_hist_9_min;
    uint16_t corr_cw_hist_8_min;
    uint16_t corr_cw_hist_7_min;
    uint16_t corr_cw_hist_6_min;
    uint16_t corr_cw_hist_5_min;
    uint16_t corr_cw_hist_4_min;
    uint16_t corr_cw_hist_3_min;
    uint16_t corr_cw_hist_2_min;
    uint16_t corr_cw_hist_1_min;

    /** Housekeeping state, let's us easily grab blocks out of sequence.
     * Please do NOT modify this.
     */
    uint32_t _state;
} por_fec_stats_cp_block_t;

/** Number of read blocks in por_fec_stats_cp_block_t */
#define POR_FEC_STATS_CP_BLOCKS 8

/**
 * Request that the FW populate the FEC stats copy buffer. This function is non-blocking and will not wait for the FW.
 *
 * The counters used by the FW are large enough to accumulate FEC stats for many days (~1yr), the interval they
 * are polled/cleared should not matter.
 *
 * Optionally stats can be cleared atomically after they are copied by the FW. If polling continuously
 * (ie interval_time=0) then no stats/events will be lost during the clear.
 *
 * stats structure will be initialized when calling this function. All values are initialized to the F16 equivalent of
 * NaN (see por_fec_stats_cp_block_t).
 *
 * @{note, This request call must be followed by a call to fec_stats_poller_get. A call to any other API method
 * which uses the messaging path will cause the FEC stats copy buffer to be cleared, losing the FEC stats requested
 * by this method.}
 *
 * @param die           [I] - The ASIC die being accessed.
 * @param intf          [I] - The interface being accessed, must be POR_INTF_EG_FEC or POR_INTF_IG_FEC.
 * @param clear_on_read [I] - True to clear all stats counters in the FW after reading. Atomic.
 * @param stats        [IO] - The stats structure that will later be used by por_fec_stats_poller_get
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 */
inphi_status_t por_fec_stats_poller_request(
    uint32_t   die,
    e_por_intf intf,
    bool clear_on_read,
    por_fec_stats_cp_block_t *stats);

/** Return type for por_fec_stats_poller_get.
 * Communicates whether we're waiting for the FW to perform some operation or not.
 */
typedef enum {
    /** Returned successfully, not waiting for the FW, same as INPHI_OK */
    POR_POLLER_OK = 0,
    /** Timed out waiting for the FW to complete the request. Keep calling the same method */
    POR_POLLER_WAITING = 1,
    /** API hit an error, you must re-request the stats from the FW. Same as INPHI_ERROR.
     * Note the documentation has a bug, this should be negative 1 (-1). */
    POR_POLLER_ERROR = -1,
} e_por_poller_status;

/**
 * Read FW stats copy buffer and populate the provided stats structure. This can be done all at once or in
 * blocks of somewhat-related stats.
 * Blocks are defined/mentioned in the por_fec_stats_cp_block_t definition, set each bit of blocks_to_read
 * that you wish to copy from the FW. Ex set bit n (1<<n) to populate block n.
 *
 * You must call por_fec_stats_poller_request prior to this function. This function will not block waiting
 * for the FW to populate the copy buffer, instead it will return POR_POLLER_WAITING while waiting for the
 * FW. Simply call this method again (with the same arguments) until the return status is POR_POLLER_OK.
 *
 * The stats structure used for por_fec_stats_poller_request MUST be the same structure used for this call!
 *
 * If this method returns POR_POLLER_ERROR, then the stats are either invalid (poll_count = 0) or an API
 * method was unable to copy the data from the copy buffer (register read error, etc.) In either case another
 * call MUST be made to por_fec_stats_poller_request prior to calling this method again.
 *
 * @param die            [I] - The ASIC die being accessed.
 * @param intf           [I] - The interface being accessed, must be POR_INTF_EG_FEC or POR_INTF_IG_FEC.
 * @param blocks_to_read [I] - Bitmask of each block to read. ie. set Bit 0 = 1 to read the first block.
 * @param stats          [O] - The stats structure copied from the FW.
 *
 * @return POR_POLLER_OK (success), POR_POLLER_WAITING (waiting on FW), POR_POLLER_ERROR (error/failure).
 *
 * @since 1.2.0.0
 *
 *
 * @example

        // Note that this is just an example of how to design a non-blocking FSM. If you're using 25MHz MDIO
        // or 1MHz I2C then the IO won't be a bottleneck and a complicated FSM is not required.

        // make sure the same stats data is used for BOTH the request and the get
        static por_fec_stats_cp_block_t stats;
        // incrementally grab each block
        static int block = 0;
        // track our VDM state
        static e_vdm_state state = VDM_START;

        // ... whatever other stuff ...

        switch(state) {
            case VDM_START:
                INPHI_NOTE("VDM request\n");
                // request stats from the FW, clearing right afterwards
                status |= por_fec_stats_poller_request(die, intf, fec, true, &stats);
                // non-blocking, exit right away
                state += 1;
                // reset our block too
                block = 0;
                break;
                
            case VDM_POLL:
                // see if the FW has copied the stats, don't copy the buffer yet
                poll_status = por_fec_stats_poller_get(die, intf, fec, 0, &stats);
                if(poll_status == POR_POLLER_ERROR) {
                    //some error, go back and try again
                    state = VDM_START;
                }
                else if(poll_status == POR_POLLER_WAITING) {
                    //stay here, FW isn't ready yet
                }
                else {
                    //FW has copied, move on
                    INPHI_NOTE("VDM captured\n");
                    state += 1;
                }
                break;
                
            case VDM_GET:
                // FW has finished copying the stats, now pull them out of the FW copy buffer one-by-one
                INPHI_NOTE("VDM get block %d\n", block);
                poll_status = por_fec_stats_poller_get(die, intf, fec, 1<<block, &stats);
                if(poll_status == POR_POLLER_ERROR) {
                    //some error, go back and try again
                    state = VDM_START;
                }
                else if(poll_status == POR_POLLER_WAITING) {
                    //stay here, FW isn't ready yet
                    // (technically this can't happen as of 1.10)
                }
                else {
                    //block was grabbed, proceed to the next one
                    block += 1;
                    if(block >= POR_FEC_STATS_CP_BLOCKS) {
                        //done all the blocks, reset
                        block = 0;
                        state += 1;
                    }
                }
                break;
                
            case VDM_POST:
                // Normally you will want to populate the CMIS register space with the captured VDM
                // stats. In this example we're just going to print to the console log.
                // NOTE: There is no need to call por_fec_stats_poller_calc_ber in module FW; this is for debug only!
                {
                    por_fec_stats_poller_t avg_rates;
                    por_fec_stats_poller_t min_rates;
                    por_fec_stats_poller_t max_rates;
                    por_fec_stats_poller_t cur_rates;
                    status |= por_fec_stats_poller_calc_ber(die, intf, fec, &stats, &avg_rates, &min_rates, &max_rates, &cur_rates);
                    
                    INPHI_PRINTF("===> Average <========\n");
                    INPHI_PRINTF( "  ber  : %7.2e\n", avg_rates.ber);
                    INPHI_PRINTF( "  ser  : %7.2e\n", avg_rates.ser);
                    INPHI_PRINTF( "  ferc : %7.2e\n", avg_rates.ferc);  
                    INPHI_PRINTF( "  hist : ");
                    for (uint16_t i=0; i<15; i++)
                        INPHI_PRINTF( "%d-%7.2e  ", i+1, avg_rates.corrected_ratio_hist[i]);
                    INPHI_PRINTF("\n"); 
                    INPHI_PRINTF("===> Min. <========\n");
                    INPHI_PRINTF( "  ber  : %7.2e\n", min_rates.ber);
                    INPHI_PRINTF( "  ser  : %7.2e\n", min_rates.ser);
                    INPHI_PRINTF( "  ferc : %7.2e\n", min_rates.ferc);
                    INPHI_PRINTF( "  hist : ");
                    for (uint16_t i=0; i<15; i++)
                        INPHI_PRINTF( "%d-%7.2e  ", i+1, min_rates.corrected_ratio_hist[i]);
                    INPHI_PRINTF("\n"); 
                    INPHI_PRINTF("===> Max. <========\n");
                    INPHI_PRINTF( "  ber  : %7.2e\n", max_rates.ber);
                    INPHI_PRINTF( "  ser  : %7.2e\n", max_rates.ser);
                    INPHI_PRINTF( "  ferc : %7.2e\n", max_rates.ferc);
                    INPHI_PRINTF( "  hist : ");
                    for (uint16_t i=0; i<15; i++)
                        INPHI_PRINTF( "%d-%7.2e  ", i+1, max_rates.corrected_ratio_hist[i]);
                    INPHI_PRINTF("\n");
                    INPHI_PRINTF("===> Current <========\n");
                    INPHI_PRINTF( "  ber  : %7.2e\n", cur_rates.ber);
                    INPHI_PRINTF( "  ser  : %7.2e\n", cur_rates.ser);
                    INPHI_PRINTF( "  ferc : %7.2e\n", cur_rates.ferc);
                    INPHI_PRINTF( "  hist : ");
                    for (uint16_t i=0; i<15; i++)
                        INPHI_PRINTF( "%d-%7.2e  ", i+1, cur_rates.corrected_ratio_hist[i]);
                    INPHI_PRINTF("\n");
                    
                }  
                state += 1;
                break;

            default:
                return INPHI_ERROR;
        }
 */
e_por_poller_status por_fec_stats_poller_get(
    uint32_t   die,
    e_por_intf intf,
    uint32_t blocks_to_read,
    por_fec_stats_cp_block_t *stats);

/**
 * Clear the internal FW FEC stats counters. Clearing the FW stats counters does not
 * affect the currently accumulating HW stats counters; these will be read the next time the accumulation_time
 * expires.
 *
 * The counters used by the FW are large enough to accumulate FEC stats for many days (~1yr), the interval they
 * are polled/cleared should not matter.
 *
 * @param die  [I] - The ASIC die being accessed.
 * @param intf [I] - The interface being accessed, must be POR_INTF_EG_FEC or POR_INTF_IG_FEC.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 */
inphi_status_t por_fec_stats_poller_clear(
    uint32_t   die, 
    e_por_intf intf);

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
#if defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)


#if !defined(INPHI_HAS_POR_RATE_T)
//fallback in case someone doesn't update their inphi_config.h
typedef double por_rate_t;
#endif

/**
 * Structure to hold the accum/min/max rates.
 *
 * @{pre,10 bits / symbol
 * 544 symbols / cw (KP)
 * 528 symbols / cw (KR)}
 *
 * @{note, Use the typedef por_rate_t in inphi_config.h to change the type from double (default) to another type (like float)}
 *
 * @requires
 * INPHI_HAS_FLOATING_POINT=1 
 */
typedef struct {
    /**
     * Symbol error rate into the FEC.
     *
     * SERi = num_symbol_errors_total / (544 * code_words_processed)
     */
    por_rate_t ser;
    /**
     * Bit error rate into the FEC.
     *
     * BERi = (num_ones_to_zeroes + num_zeroes_to_ones) / (5440 * code_words_processed)
     */
    por_rate_t ber;
    /**
     * Frame error count, not rate
     */
    por_rate_t ferc;
    /**
     * Corrected codeword rate = codewords_corrected[n] / codewords_processed
     * Where n is the number of errors -1.
     * ie. codewords_corrected[3-1] is the number of CW that had 3 corrected errors, so
     * corrected_ratio_hist[3-1] is the rate for 3 corrected errors per CW.
     */
    por_rate_t corrected_ratio_hist[15];
} por_fec_stats_poller_t;


/**
 * Uses the stats returned by the FW to calculate the rates for min/max/accumulated/current. This is simply
 * converting the CMIS F16 format to an ordinary float/double.
 *
 * @param die       [I] - The ASIC die being accessed.
 * @param intf      [I] - The interface being accessed, must be POR_INTF_EG_FEC or POR_INTF_IG_FEC.
 * @param stats     [I] - The stats structure copied from the FW.
 * @param avg_rates [O] - The output average/accumulated rates. Can be NULL to ignore.
 * @param min_rates [O] - The output minimum rates. Can be NULL to ignore.
 * @param max_rates [O] - The output maximum rates. Can be NULL to ignore.
 * @param cur_rates [O] - The output current rates. Can be NULL to ignore.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 *
 * @requires
 * INPHI_HAS_FLOATING_POINT=1 
 */
inphi_status_t por_fec_stats_poller_calc_ber(
    uint32_t die,
    e_por_intf intf,
    por_fec_stats_cp_block_t *stats,
    por_fec_stats_poller_t *avg_rates,
    por_fec_stats_poller_t *min_rates,
    por_fec_stats_poller_t *max_rates,
    por_fec_stats_poller_t *cur_rates);
#endif // defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)
#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)


#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif //__POR_H__

