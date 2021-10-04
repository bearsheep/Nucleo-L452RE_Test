

#ifndef __INPHI_POR_API__
#define __INPHI_POR_API__





#ifdef __cplusplus
/* don't mangle api function names (gen) */
extern "C" {
#endif

#include "inphi_rtos.h"


/** @file spica_rules.h
 ****************************************************************************
 *
 * @brief
 *     This module describes the high level configuration rules for the API.
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
#ifndef __SPICA_RULES_H__
#define __SPICA_RULES_H__

/**
 * @h2 Misc defines
 * =======================================================
 *
 * @brief
 * Default number of MS to poll for MCU status
 * 
 * @private
 */
#define SPICA_MCU_POLL_DELAY_MS 50

/**
 * @h2 ASIC Package and Channel Utilities
 * =======================================================
 *
 * @brief
 * The maximum number of dies inside the ASIC package. When only
 * working on a single die package this can be re-defined to 1 to
 * conserve memory utilization.
 */
#define SPICA_MAX_DIES_IN_PACKAGE 2

/** the maximum number of channels per die */
#define SPICA_NUM_OF_ORX_CHANNELS 4
#define SPICA_NUM_OF_OTX_CHANNELS 4
#define SPICA_NUM_OF_MRX_CHANNELS 4
#define SPICA_NUM_OF_MTX_CHANNELS 4
#define SPICA_NUM_OF_SRX_CHANNELS 8
#define SPICA_NUM_OF_STX_CHANNELS 8

/** The maximum number of line receivers in the ASIC package */
#define SPICA_MAX_ORX_CHANNELS (SPICA_NUM_OF_ORX_CHANNELS * SPICA_MAX_DIES_IN_PACKAGE)
/** The maximum number of line transmitters in the ASIC package */
#define SPICA_MAX_OTX_CHANNELS (SPICA_NUM_OF_OTX_CHANNELS * SPICA_MAX_DIES_IN_PACKAGE)
/** The maximum number of host PMR receivers in the ASIC package */
#define SPICA_MAX_MRX_CHANNELS (SPICA_NUM_OF_MRX_CHANNELS * SPICA_MAX_DIES_IN_PACKAGE)
/** The maximum number of host PMR transmitters in the ASIC package */
#define SPICA_MAX_MTX_CHANNELS (SPICA_NUM_OF_MTX_CHANNELS * SPICA_MAX_DIES_IN_PACKAGE)
/** The maximum number of host PSR receivers in the ASIC package */
#define SPICA_MAX_SRX_CHANNELS (SPICA_NUM_OF_SRX_CHANNELS * SPICA_MAX_DIES_IN_PACKAGE)
/** The maximum number of host PSR transmitters in the ASIC package */
#define SPICA_MAX_STX_CHANNELS (SPICA_NUM_OF_STX_CHANNELS * SPICA_MAX_DIES_IN_PACKAGE)

/** Maximum number of bundles */
#define SPICA_MAX_BUNDLES       8

/**
 * The Bare-die host interface type.
 */
typedef enum
{
    /** Bare-die host interface is PMR */
    SPICA_PACKAGE_HOST_INTF_PMR = 0,

    /** Bare-die host interface is PSR */
    SPICA_PACKAGE_HOST_INTF_PSR,

} e_spica_package_host_intf;

/**
 * The ASIC package type which defines the channel
 * mapping. See the user guide section API Channel Mapping for more info.
 */
typedef enum
{
    /** Un-mapped package type, channels will not be re-mapped */
    SPICA_PACKAGE_TYPE_UNMAPPED = 0,

    /** 800G EML bottom 15x14 package */
    SPICA_PACKAGE_TYPE_EML_BOT_15x14 = 1,

    /** 800G SiPho bottom 14x14 package */
    SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14 = 2,

    /** 800G EML top 15x14 package */
    SPICA_PACKAGE_TYPE_EML_TOP_15x14 = 3,

    /** 800G SiPho top 15x14 package */
    SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14 = 4,

    /** 400G EML 12x13 package (PG3) */
    SPICA_PACKAGE_TYPE_EML_12x13 = 5,

    /** 400G Std 10x13 package */
    SPICA_PACKAGE_TYPE_STD_10x13 = 6,

    /** 400G SiPho package */
    SPICA_PACKAGE_TYPE_SIPHO = 7,

    /** 400G EML 12x13 package (PG3) Rev 1 */
    SPICA_PACKAGE_TYPE_EML_12x13_REV1 = 8,

    /** Unknown package type */
    SPICA_PACKAGE_TYPE_UNKNOWN = 9,

    /** For range checking of the package type, don't use this value. */ 
    SPICA_PACKAGE_TYPE_MAX,
} e_spica_package_type;

/**
 * These are interface or definitions used by the API to
 * configure certain parts of the datapath.
 */
typedef enum
{
    /** SPICA Line RX */
    SPICA_INTF_NONE   = 0,
    /** SPICA Line RX */
    SPICA_INTF_ORX    = 1<<0,
    /** SPICA Line TX */
    SPICA_INTF_OTX    = 1<<1,
    /** PMR Host RX */
    SPICA_INTF_MRX    = 1<<2,
    /** PMR Host TX */
    SPICA_INTF_MTX    = 1<<3,
    /** PSR Host RX */
    SPICA_INTF_SRX    = 1<<4,
    /** PSR Host TX */
    SPICA_INTF_STX    = 1<<5,
    /** Egress FEC */
    SPICA_INTF_EG_FEC = 1<<6,
    /** Ingress FEC */
    SPICA_INTF_IG_FEC = 1<<7,
    /** Any FEC */
    SPICA_INTF_ANY_FEC = (SPICA_INTF_EG_FEC | SPICA_INTF_IG_FEC),
    /** The POR line side interface */
    SPICA_INTF_POR  = SPICA_INTF_ORX | SPICA_INTF_OTX,
    /** The PMR host side interface */
    SPICA_INTF_PMR  = SPICA_INTF_MRX | SPICA_INTF_MTX,
    /** The PSR host side interface */
    SPICA_INTF_PSR  = SPICA_INTF_SRX | SPICA_INTF_STX,
    /** All interfaces */
    SPICA_INTF_ALL = SPICA_INTF_POR | SPICA_INTF_PMR | SPICA_INTF_PSR

} e_spica_intf;

/**
 * The operational mode of the device
 */
typedef enum
{
    /**
     * Mission mode.
     *
     * This is the main operational mode of the Spica device. It configures
     * the ASIC to pass traffic straight through the ingress and egress channels.
     * All interfaces are setup for PAM4 signalling by default.
     * On gearbox packages half of the host channels will be disabled,
     * as those packages have twice as many host channels as line channels.
     *
     * @{pre,
     *   HOST (PAM)         LINE (PAM)
     *      +-------------------+
     *      !      +-----+      !
     *   >>----------------------->>
     *      !      !     !      !
     *      !      !     !      !
     *      !      !     !      !
     *   <<-----------------------<<
     *      !      +-----+      !
     *      +-------------------+
     * }
     */
    SPICA_MODE_MISSION_MODE = 0,

    /**
     * Line PRBS mode.
     *
     * This is a diagnostic mode that configures the device to send PRBS
     * traffic out the line transmitters, with the clock sourced from the
     * reference. This may be looped back to the
     * device via an external loopback to check PRBS on the line receiver.
     * All interfaces are setup for PAM4 signalling by default.
     *
     * @{pre,
     *   HOST               LINE (PAM)
     *      +-------------------+
     *      !      +-----+      !
     *      !      !     ! PRBS---->>
     *      !      !     !      !
     *      !      !     !      !
     *      !      !     !      !
     *      !      !     !   <<------
     *      !      +-----+      !
     *      +-------------------+
     * }
     */
    SPICA_MODE_LINE_PRBS,                   // 1

    /**
     * Host PRBS mode.
     *
     * This is a diagnostic mode that configures the device to send PRBS
     * traffic out the host interface, with the clock sourced from the
     * reference. This may be looped back to the
     * device via an external loopback to check PRBS on the host receiver.
     * On gearbox packages, host interfaces are setup for NRZ by default.
     * On non-gearbox packages, host interfaces are setup for PAM4 by default.
     *
     * @{pre,
     *   HOST (PAM/NRZ)       LINE
     *       +-------------------+
     *       !      +-----+      !
     *   ------>>   !     !      !
     *       !      !     !      !
     *       !      !     !      !
     *       !      !     !      !
     *   <<----PRBS !     !      !
     *       !      +-----+      !
     *       +-------------------+
     * }
     */
    SPICA_MODE_HOST_PRBS,                   // 2     

    /**
     * Dual PRBS mode.
     *
     * This is a diagnostic mode that configures the device to send PRBS
     * traffic out the host and line interfaces, with the clock sourced from
     * the reference. The host and line interfaces
     * may be looped back to the device via external loopbacks to check PRBS
     * on the their respective interfaces.
     * On gearbox packages, host interfaces are setup for NRZ by default.
     * On non-gearbox packages, host interfaces are setup for PAM4 by default.
     * Line interfaces are setup for PAM4 on all packages by default.
     *
     * @{pre,
     *   HOST (PAM/NRZ)       LINE (PAM)
     *       +-------------------+
     *       !      +-----+      !
     *   ------>>   !     ! PRBS---->>
     *       !      !     !      !
     *       !      !     !      !
     *       !      !     !      !
     *   <<----PRBS !     !   <<------
     *       !      +-----+      !
     *       +-------------------+
     * }
     */
    SPICA_MODE_DUAL_PRBS,                   // 3

    /**
     * Shallow line loopback.
     *
     * In this mode only the line side interface is used, the host interfaces are disabled.
     * The data received on the line side receivers is looped back in
     * the digital to the line side transmitters.
     * This mode can also be referred to as a line side shallow digital loopback.
     * NOTE: The full ingress data path can be turned on in this mode simply by
     * enabling the HTX channels.
     * All interfaces are setup for PAM4 signalling by default.
     *
     * @{pre,
     *   HOST               LINE (PAM)
     *      +-------------------+
     *      !      +-----+      !
     *      !      !     !   +----->>
     *      !      !     !   !  !
     *      !      !     !   !  !
     *      !      !     !   !  !
     *      !      !     !   +-----<<
     *      !      +-----+      !
     *      +-------------------+
     * }
     */
    SPICA_MODE_SHALLOW_LINE_LOOPBACK,       // 4

    /**
     * Shallow host loopback.
     *
     * In this mode only the host side interface is used, the line interfaces are disabled.
     * The data received on the host side receivers is looped back in
     * the digital to the host side transmitters.
     * This mode can also be referred to as a host side shallow digital loopback.
     * NOTE: The full egress data path can be turned on in this mode simply by
     * enabling the LTX channels.
     * On gearbox packages, host interfaces are setup for NRZ by default.
     * On non-gearbox packages, host interfaces are setup for PAM4 by default.
     *
     * @{pre,
     *    HOST (PAM/NRZ)     LINE
     *       +-------------------+
     *       !      +-----+      !
     *   >>------+  !     !      !
     *       !   !  !     !      !
     *       !   !  !     !      !
     *       !   !  !     !      !
     *   <<------+  !     !      !
     *       !      +-----+      !
     *       +-------------------+
     * }
     */
    SPICA_MODE_SHALLOW_HOST_LOOPBACK,       // 5

    /**
     * Ingress PRBS mode.
     *
     * This is a diagnostic mode that configures the device to send PRBS
     * traffic out the line Tx interfaces and check the PRBS traffic comming
     * into the host Rx interface, with the clock sourced from
     * the reference. 
     *
     * @{pre,
     *   HOST (PAM/NRZ)       LINE (PAM)
     *       +-------------------+
     *       !      +-----+      !
     *   --->> PRBS !     ! PRBS---->>
     *       !      !     !      !
     *       !      !     !      !
     *       !      !     !      !
     *   <<-------------------------<<
     *       !      +-----+      !
     *       +-------------------+
     * }
     */
    SPICA_MODE_INGRESS_PRBS,                // 6

    /**
     * Egress PRBS mode.
     *
     * This is a diagnostic mode that configures the device to send PRBS
     * traffic out the host Tx interfaces and check the PRBS traffic comming
     * into the line Rx interface, with the clock sourced from
     * the reference. 
     *
     * @{pre,
     *   HOST (PAM/NRZ)       LINE (PAM)
     *       +-------------------+
     *       !      +-----+      !
     *   >>------------------------->>
     *       !      !     !      !
     *       !      !     !      !
     *       !      !     !      !
     *   <<----PRBS !     ! PRBS <<---
     *       !      +-----+      !
     *       +-------------------+
     * }
     */
    SPICA_MODE_EGRESS_PRBS,                 // 7

    SPICA_MODE_OP_END,
} e_spica_operational_mode;   

/**
 * The protocol mode of the device
 */
typedef enum 
{

    /** Host 4x106.25Gbps (PAM4) to Line 4x106.25Gbps (PAM4) */
    SPICA_MODE_400G_4Px53p1_TO_4Px53p1 = 0,
    /** Host 4x25.78125 Gbps (NRZ) to Line 4x25.78125 Gbps (NRZ) */
    SPICA_MODE_100G_4Nx25p8_TO_4Nx25p8,
    /** Host 4x82.5Gbps (PAM4) to Line 4x82.5Gbps (PAM4) [Discount Rate]*/
    SPICA_MODE_300G_4Px41p3_TO_4Px41p3,
    /** Host 4x53.125 Gbps (PAM4) to Line 4x53.125 Gbps (PAM4) */
    SPICA_MODE_200G_4Px26p6_TO_4Px26p6,
    /** Host 4x25.78125 Gbps (NRZ) to Line 2x51.5625 Gbps (PAM4) */
    SPICA_MODE_100G_4Nx25p8_TO_2Px25p8,
    /** Host 8x53.125 Gbps (PAM) to Line 4x106.25 Gbps (PAM4) */
    SPICA_MODE_400G_8Px26p6_TO_4Px53p1,
    /** Host 4x53.125 Gbps (PAM) to Line 2x106.25 Gbps (PAM4) */
    SPICA_MODE_200G_4Px26p6_TO_2Px53p1,
    /** Host 2x53.125 Gbps (PAM) to Line 1x106.25 Gbps (PAM4) */
    SPICA_MODE_100G_2Px26p6_TO_1Px53p1,
    /** Host 4x26.5625 Gbps (NRZ) to Line 1x106.25 Gbps (PAM4) */
    SPICA_MODE_100G_4Nx26p6_TO_1Px53p1,
    /** Host 4x53.1Gbps (NRZ) to Line 4x53.1Gbps (NRZ) */
    SPICA_MODE_200G_4Nx53p1_TO_4Nx53p1,
    /** Host 8x26.5625Gbps (NRZ) to Line 4x53.1Gbps (PAM4) */
    SPICA_MODE_200G_8Nx26p6_TO_4Px26p6,

    SPICA_MODE_PROT_END,

} e_spica_protocol_mode;

/**
 * The Transmitter Look-Up-Table (LUT) configuration
 */
typedef enum
{
    /**
     * 4-Tap LUT mode. 
     * Requires LUT to be programmed. 
     */
    SPICA_LUT_4TAP       = 0,
    /**
     * Bypass mode.
     * One-tap LUT mode, uses rows 0-3 of the LUT.
     */
    SPICA_LUT_BYPASS     = 1,
    /**
     * 7-Tap Linear mode.
     * Does not use LUT, convolution output is used directly.
     */
    SPICA_LUT_7TAP_LIN   = 2,
    /**
     * 7-Tap LUT mode.
     * Convolution output is put through a LUT.
     * - Inner eye settings and taps 0-6 are used directly in a small 7x4-to-1 LUT + convolution.
     * - That is then fed into a 128-to-1 LUT.
     */
    SPICA_LUT_7TAP_LUT   = 3,

} e_spica_lut_mode;

/**
 * The ORX 6-Bit Mode definitions
 */
typedef enum
{
    /** 6-Bit Mode Disable */
    SPICA_6BIT_MODE_DISABLE = 0,

    /** 6-Bit Mode Enable */
    SPICA_6BIT_MODE_ENABLE  = 1,

    /** 6-Bit Mode Automatic */
    SPICA_6BIT_MODE_AUTO     = 2 

} e_spica_6bit_mode;

/**
 * The signalling mode
 */
typedef enum
{
    /** PAM signalling mode */
    SPICA_SIGNAL_MODE_PAM = 0,
    /** NRZ signalling mode */
    SPICA_SIGNAL_MODE_NRZ = 1,

} e_spica_signal_mode;

/**
 * For setting the TX swing
 */
typedef enum 
{
    /** 60 percent Tx swing */
    SPICA_TX_SWING_60p  = 0,
    /** 70 percent Tx swing */
    SPICA_TX_SWING_70p  = 1,
    /** 80 percent Tx swing */
    SPICA_TX_SWING_80p  = 2,
    /** 90 percent Tx swing */
    SPICA_TX_SWING_90p  = 3,
    /** 100 percent Tx swing */
    SPICA_TX_SWING_100p = 4,
    /** 110 percent Tx swing */
    SPICA_TX_SWING_110p = 5,
    /** 120 percent Tx swing */
    SPICA_TX_SWING_120p = 6, 
    /** Tx swing not applicable */
    SPICA_TX_SWING_NA = 7 

} e_spica_tx_swing;

/**
 * Selected baud-rate, all units are kilo Baud per second (kBd/s). 
 * Note that when the channel is configured for NRZ signalling, the data-rate equals the baud-rate.
 * When configured for PAM signalling, the data-rate is 2x the baud-rate.
 */
typedef enum
{
    /** For KR4 */
    SPICA_BAUD_RATE_25p8  = 25781250,
    /** For KP4 */
    SPICA_BAUD_RATE_26p6  = 26562500,
    /** Proprietary Rate */
    SPICA_BAUD_RATE_41p3  = 41250000,
    /** For KR SL */
    SPICA_BAUD_RATE_51p6  = 51562500,
    /** For KP SL */
    SPICA_BAUD_RATE_53p1  = 53125000,
    /** Proprietary Rate */
    SPICA_BAUD_RATE_56p3  = 56250000,
} e_spica_baud_rate;

/** 
 * FLL modes of operation
 */
typedef enum
{
    /** Counter-PD mode */
    SPICA_FLL_MODE_COUNTER_PD = 0,
    /** BB-PD mode */
    SPICA_FLL_MODE_BB_PD,
} e_spica_fll_mode;

/**
 * This structure contains the rules used to control
 * the transmitters of the device.
 */
typedef struct 
{
    /** Channel Enable, set to false to cause the FW to ignore this channel. Channels set to false
     * will be set to a low power mode. */
    bool channel_enable;

    /**
     * Lock the squelch for manual control by host software. The firmware
     * may still squelch the TX but it cannot un-squelch when this flag
     * is asserted
     */
    bool squelch_lock;

    /** Signalling type, NRZ or PAM on HTX, PAM only on LTX */
    e_spica_signal_mode signalling;

    /** Baud rate */
    uint32_t baud_rate;

    /**
     * LUT mode
     *
     * Note there are special restrictions around SPICA_LUT_BYPASS, see the e_spica_lut_mode
     * documentation for more details.
     */
    e_spica_lut_mode lut_mode;

    /**
     * IEEE Demap, sometimes called bit order. True to use the IEEE standard bit order of LSB-first,
     * false to use legacy Inphi bit order of MSB-first.
     *
     * This should always be left to true unless the other device is connected
     * to (on either host or line) is a legacy Inphi device (ie 28nm PAM B0). Even in those cases, the
     * latest APIs for legacy devices support IEEE mode, and should be enabled on those devices.
     * */
    bool ieee_demap;

    /** Gray mapping */
    bool gray_mapping;  

    /** Tx channel inversion */
    bool invert_chan;

    /** Tx swing adjustment, See e_spica_tx_swing enum
     *  NOTE: Not applicable to PSR Tx interface */
    e_spica_tx_swing swing;
    
    /** Coefficient Pre-Tap, range -1000 to 1000 where -1000 = -1, 1000 = 1 
     * Use the first N indexes for N-Tap mode */
    int16_t fir_taps[7];

    /** Scale PAM lower inner eye, range 500 to 1500 where 500 = 0.5, 1500 = 1.5 
      * NOTE: This is used for LUT modes only, default eye levels are used for linear modes */
    uint16_t inner_eye1;

    /** Scale PAM upper inner eye, range 1500 to 2500 where 1500 = 1.5, 2500 = 2.5 
      * NOTE: This is used for LUT modes only, default eye levels are used for linear modes */
    uint16_t inner_eye2;

    /** DFE pre-coder enable
     * The DFE precoder helps to transform burst errors from the DFE to error events with 
     * smaller number of bit flips in order to improve BER. The precoder should not be 
     * turned on in non-DFE modes since it can actually increase the BER.
     *
     * Note that the link partner's receive precoder must be enabled if
     * this rule is set to true.
    */
    bool dfe_precoder_en;
    
    /* 
     * FLL mode 
    */
    e_spica_fll_mode fll_mode;

} spica_tx_rules_t;

/**
 * This structure contains the rules used to control
 * the ORX/MRX receivers of the device.
 */
typedef struct
{
    /** Channel Enable, set to false to cause the FW to ignore this channel. Channels set to false
     * will be set to a low power mode. */
    bool channel_enable;

    /** Signalling type*/
    e_spica_signal_mode signalling;

    /** Baud rate */
    uint32_t baud_rate;

    /**
     * IEEE Demap, sometimes called bit order. True to use the IEEE standard bit order of LSB-first,
     * false to use legacy Inphi bit order of MSB-first.
     *
     * This should always be left to true unless the other device connected
     * to (on either host or line) is a legacy Inphi device (ie 28nm PAM B0). Even in those cases, the
     * latest APIs for legacy devices support IEEE mode, and should be enabled on those devices.
     * */
    bool ieee_demap;

    /** Gray mapping */
    bool gray_mapping;  

    /** Tx channel inversion */
    bool invert_chan;

    /** SDT DSP enable 
      * If this is set to true then the following thresholds must be manually set as well:
      * - lrx_los_dsrt_ctrl_startup;
      * Thresholds should be set to actual mV value and should not use an enum
      * @private
      * @deprecated This rule is not used
      */
    bool sdt_dsp_en;

    /** LOS DSP enable 
      * If this is set to true then the following thresholds must be manually set as well:
      * - lrx_los_asrt_ctrl_startup;
      * - lrx_los_asrt_ctrl_datamode;
      * Thresholds should be set to actual mV value and should not use an enum
      * @private
      * @deprecated This rule is not used
    */
    bool los_dsp_en;

    /** 6-Bit Mode 
     * @private
     */
    uint8_t six_bit_mode;

    /** Force into Mission Mode 
     * @private
    */
    bool force_mission_mode;

    /** FFE constant diff mode setting 
     * @private
    */
    bool ffe_const_diff_en;

    /** Selects the number of BW knobs to sweep. Range 1-3. 
     * @private
    */
    uint8_t bw_idx_max;

    /** VGA1 tracking algorithm call period in msec. Range 1-255. 
     * @private
    */
    uint8_t vga1_tracking_period;

    /** ALG1 Disable
     * @private
    */
    bool alg1_dis;

    /** ALG2 Disable 
     * @private
    */        
    bool alg2_dis;

    /** ALG3 Disable
     * @private
    */    
    bool alg3_dis;

    /** ALG4 Disable 
     * @private
    */
    bool alg4_dis;

    /** Disable restart on LOS trigger */
    bool restart_on_los_dis;

    /** Disable ALL QC algorithms */
    bool qc_all_dis;

    /** Disable QC histogram algorithms */
    bool qc_hist_dis;

    /** Disable QC slicer algorithms */
    bool qc_slc_dis;

    /** Disable QC SNR algorithms */
    bool qc_snr_dis;

} spica_ant_rx_rules_t;

/**
 * This structure contains the rules used to control
 * the host receivers of the device.
 */
typedef struct 
{
    /** Channel Enable, set to false to cause the FW to ignore this channel. Channels set to false
     * will be set to a low power mode.
     *
     * @{note,
     * HRX die instance 4 (ie package channel 3 on retimer bottom packages, different for each package)
     * must be enabled to pass a clock to the LTX. This will be fixed in a future FW release.
     * }
     */
    bool channel_enable;

    /** Signalling, whether PAM or NRZ */
    e_spica_signal_mode signalling;

    /** Baud rate */
    uint32_t baud_rate;

    // Demapping rules:

    /** Gray mapping */
    bool gray_mapping;  

    /** IEEE Demap flag */
    bool ieee_demap;

    /** Rx channel inversion */
    bool invert_chan;

    // Automatic adaptation rules:

    /** Skip adaptation all together, allowing DSP debug without the FW interfering.
     * This should definitely be left enabled.
     */
    bool skip_adapt;

    /** Disable CTLE adaptation, using our override value instead */
    bool ctle_adapt_dis;

    /**
     * The value to override HRX_RXA_AFE_CTLE_CFG with. See register description for field info.
     *
     * - CSTUNE controls the frequencies covered by the CTLE, set between 0 for low-loss to 3 for high loss. Do
     *   not set this higher than 3.
     * - RSTUNE controls the peaking applied, following the table below:
     * @{pre,
     * C |  R | dB peak
     * 3 | 13 |  0
     * 3 | 12 |  2
     * 3 | 11 |  3
     * 3 |  9 |  4
     * 3 |  8 |  5
     * 3 |  5 |  6
     * 3 |  3 |  7
     * 3 |  2 |  8
     * 3 |  1 |  9
     * 3 |  0 | 10
     * }
     */
    uint16_t ctle_override;

    /** Selectively ENABLE the C adapt, which is normally disabled */
    bool ctle_c_adapt_en;
    /** Selectively DISABLE the R adapt, which is normally enabled (and should be left enabled! */
    bool ctle_r_adapt_dis;

    /** Disable LFEQ adaptation, using our override value instead */
    bool lfeq_adapt_dis;

    /**
     * The value to override HRX_RXA_AFE_LFEQ_CFG with. See register description for field info.
     * 
     * - PEAK_ADJ is reasonably linear, so the dB peaking is simply dB = PEAK_ADJ * 0.5dB
     * - POLE_ADJ does not have usability limits like the CTLE CSTUNE, it can be any value from 0 to 15.
     */
    uint16_t lfeq_override;

    /** Disable DFE, saving a few mW/channel. Note that most channels will need DFE */
    bool dfe_adapt_dis;

    /** Disable data skew adaptation (aka sample phase correction). This should be left enabled. */
    bool data_skew_adapt_dis;

    /** Disable edge skew adaptation (aka DCD correction). This should be left enabled. */
    bool edge_skew_adapt_dis;

    /** Disable the Slicer Calibration adaptation */
    bool slc_adapt_dis;

    /** Disable the Edge DC Offset adaptation */
    bool edge_off_adapt_dis;

    /** Disable the Automatic Gain Control adaptation */
    bool agc_adapt_dis;

    /** Disable the VCO temperature offset calibration */
    bool vco_temp_cal_dis;

    /** Disable the AFE BW adapt */
    bool afe_bw_adapt_dis;

    /** Disable the DC offset adapt during mission mode */
    bool dc_off_adapt_dis;

    /** VCO mode to configure VCO temp aware calibration*/
    bool vco_mode;

    /** Rate config */
    uint32_t rates;

    /** Disable LFEQ adapt after FW lock */
    bool lfeq_adapt_dis_after_init_adapt;

} spica_sun_rx_rules_t;

/**
 * The device driver type
 */
typedef enum
{
    /** Driver type None */
    SPICA_DRIVER_TYPE_NONE = 0,
    /** Driver type EML */
    SPICA_DRIVER_TYPE_EML,
    /** Driver type SiPho */
    SPICA_DRIVER_TYPE_SIPHO,
    /** Driver type 1vPP */
    SPICA_DRIVER_TYPE_1VPP,

} e_spica_driver_type;

/**
 * LOS Assert/De-assert control
 */
typedef enum
{

    /** Input signal amplitude, 50 mv ppd  */
    SPICA_LOS_CTRL_AMP_50 = 0,
    /** Input signal amplitude, 100 mv ppd  */
    SPICA_LOS_CTRL_AMP_100 = 1,
    /** Input signal amplitude, 150 mv ppd  */
    SPICA_LOS_CTRL_AMP_150 = 2,
    /** Input signal amplitude, 200 mv ppd  */
    SPICA_LOS_CTRL_AMP_200 = 3,
    /** Input signal amplitude, 250 mv ppd  */
    SPICA_LOS_CTRL_AMP_250 = 4,
    /** Input signal amplitude, 300 mv ppd  */
    SPICA_LOS_CTRL_AMP_300 = 5,
    /** Input signal amplitude, 350 mv ppd  */
    SPICA_LOS_CTRL_AMP_350 = 6,
    
    SPICA_LOS_CTRL_AMP_MAX = 7,

}e_spica_los_ctrl_amp;

/**
 * The RX quality-check approximate SNR thresholds
 * PAM supported range: 14p5dB to 21dB
 * NRZ supported range: 10p1dB to 14dB
 */
typedef enum
{
    /** SNR Thresholds (PAM and NRZ) */
    /** SNR 10.1 (dB) */
    SPICA_RX_QC_SNR_THRESH_10p1dB   = 0x65,
    /** SNR 10.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_10p5dB   = 0x69,
    /** SNR 11 (dB) */
    SPICA_RX_QC_SNR_THRESH_11dB     = 0x6E,
    /** SNR 11.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_11p5dB   = 0x73,
    /** SNR 12 (dB) */
    SPICA_RX_QC_SNR_THRESH_12dB     = 0x78,
    /** SNR 12.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_12p5dB   = 0x7D,
    /** SNR 13 (dB) */
    SPICA_RX_QC_SNR_THRESH_13dB     = 0x82,
    /** SNR 13.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_13p5dB   = 0x87,
    /** SNR 14 (dB) */
    SPICA_RX_QC_SNR_THRESH_14dB     = 0x8C,
    /** SNR 14.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_14p5dB   = 0x91,
    /** SNR 15 (dB) */
    SPICA_RX_QC_SNR_THRESH_15dB     = 0x96,
    /** SNR 15.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_15p5dB   = 0x9B,
    /** SNR 16 (dB) */
    SPICA_RX_QC_SNR_THRESH_16dB     = 0xA0,
    /** SNR 16.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_16p5dB   = 0xA5,
    /** SNR 17 (dB) */
    SPICA_RX_QC_SNR_THRESH_17dB     = 0xAA,
    /** SNR 17.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_17p5dB   = 0xAF,
    /** SNR 18 (dB) */
    SPICA_RX_QC_SNR_THRESH_18dB     = 0xB4,
    /** SNR 18.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_18p5dB   = 0xB9,
    /** SNR 19 (dB) */
    SPICA_RX_QC_SNR_THRESH_19dB     = 0xBE,
    /** SNR 19.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_19p5dB   = 0xC3,
    /** SNR 20 (dB) */
    SPICA_RX_QC_SNR_THRESH_20dB     = 0xC8,
    /** SNR 20.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_20p5dB   = 0xCD,
    /** SNR 21 (dB) */
    SPICA_RX_QC_SNR_THRESH_21dB     = 0xD2,
    /** SNR 21.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_21p5dB   = 0xD7,
    /** SNR 22 (dB) */
    SPICA_RX_QC_SNR_THRESH_22dB     = 0xDC,
    /** SNR 22.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_22p5dB   = 0xE1,
    /** SNR 23 (dB) */
    SPICA_RX_QC_SNR_THRESH_23dB     = 0xE6,
    /** SNR 23.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_23p5dB   = 0xEB,
    /** SNR 24 (dB) */
    SPICA_RX_QC_SNR_THRESH_24dB     = 0xF0,
    /** SNR 24.5 (dB) */
    SPICA_RX_QC_SNR_THRESH_24p5dB   = 0xF5,
    /** SNR 25 (dB) */
    SPICA_RX_QC_SNR_THRESH_25dB     = 0xFA,

} e_spica_rx_qc_snr_threshold;

/**
 * This structure contains the RX quality-check rules.
 *
 */
typedef struct
{

    /** LRX QC SNR Threshold - Enter MM (default PAM:17dB, NRZ:19dB) 
    */
    e_spica_rx_qc_snr_threshold snr_threshold_mm_enter;

    /** LRX QC SNR Threshold - Exit MM (default PAM:16dB, NRZ:18dB)
    */
    e_spica_rx_qc_snr_threshold snr_threshold_mm_exit;

   /** The max allowable error percentage in the LRX DSP slicer location in order that the LRX state
      * can be deemed to be of acceptable quality.
      * 0% means the slicer has to be exactly the ideal value.
      * 100% means the slicer can deviate +/-100% from the ideal value.
      * Value is rounded down to the nearest 10% (ie 97% gets truncated to 90%) (default:50%)
      */
    uint8_t slc_err_limit;

} spica_rx_qc_rules_t;

/**
 * Advanced rules for diagnostics and debug features.
 *
 * Note: Leave these as their defaults unless instructed to by a Inphi AE
 */
typedef struct
{
    /** LRX DDLF enable */
    bool lrx_ddlf_en;

    /** HRX DDLF enable */
    bool hrx_ddlf_en;

    /** LRX low loss detection enable */
    bool lrx_low_loss_det_en;

    /** HRX low loss detection enable */
    bool hrx_low_loss_det_en;

    /** LRX double restart disable */
    bool lrx_double_restart_dis;

    /** LRX CID LOSD enable */
    bool lrx_cid_losd_det_en;

    /** HRX CID LOSD enable */
    bool hrx_cid_losd_det_en;

} spica_advanced_rules_t;

/**
 * This structure contains the rules used to control
 * the operational behavior of the device.
 */
typedef struct 
{
    /** The ASIC package type */
    e_spica_package_type package_type;

    /** If the package AND driver type are unmapped in the EFUSE, this specifies the bare die driver type */
    e_spica_driver_type driver_type_override;

    /** Firmware download time-out value, units are 100 microseconds (default 5000 or 500ms) */
    uint32_t fw_dwld_timeout;

    /** 
     * If this flag is set a warning will be generated if the firmware
     * version detected does not match the one the API was bundled with
     */
    bool fw_warn_if_mismatched;

    /** The operational mode of the device */
    e_spica_operational_mode operational_mode;

    /** The protocol mode of the device */
    e_spica_protocol_mode protocol_mode;

    /** Advanced rules */
    spica_advanced_rules_t advanced;

    /** Note the channel arrays are sized +1 because some package channels are 1-based */

    /** ORX Line receive rules */
    spica_ant_rx_rules_t orx[SPICA_MAX_ORX_CHANNELS+1];

    /** MRX Host receive rules */
    spica_ant_rx_rules_t mrx[SPICA_MAX_MRX_CHANNELS+1];

    /** SRX Host receive rules */
    spica_sun_rx_rules_t srx[SPICA_MAX_SRX_CHANNELS+1];

    /** OTX Line transmit rules */
    spica_tx_rules_t otx[SPICA_MAX_OTX_CHANNELS+1];

    /** MTX Host transmit rules */
    spica_tx_rules_t mtx[SPICA_MAX_MTX_CHANNELS+1];

    /** STX Host transmit rules */
    spica_tx_rules_t stx[SPICA_MAX_STX_CHANNELS+1];

    /**
     * OTX Data xbar has up to four Rx channel selections per single OTX channel (4:1 forward gearbox)
     */
    uint8_t otx_xbar_src_chan[SPICA_MAX_OTX_CHANNELS+1][4];

    /**
     * OTX CLK xbar provides configurability of a clock source for each OTX channel
     */
    uint8_t otx_clk_xbar[SPICA_MAX_OTX_CHANNELS+1];

    /**
     * Specifies the Rx channel and interleave index used as a source for the given MTX channel.  Each Rx channel can contain up to 4 MTX channels of data.
     * - mtx_xbar_src_chan[channel][0] - Specifies the SRC channel
     * - mtx_xbar_src_chan[channel][1] - Specifies the interleave index within the SRC channel (Valid values are 0, 1, 2, 3)
     */
    uint8_t mtx_xbar_src_chan[SPICA_MAX_MTX_CHANNELS+1][2];

    /**
     * MTX CLK xbar provides configurability of a clock source for each MTX channel
     */
    uint8_t mtx_clk_xbar[SPICA_MAX_MTX_CHANNELS+1];

    /**
     * Specifies the Rx channel and interleave index used as a source for the given STX channel.  Each Rx channel can contain up to 4 STX channels of data.
     * - stx_xbar_src_chan[channel][0] - Specifies the SRC channel
     * - stx_xbar_src_chan[channel][1] - Specifies the interleave index within the SRC channel (Valid values are 0, 1, 2, 3)
     */
    uint8_t stx_xbar_src_chan[SPICA_MAX_STX_CHANNELS+1][2];

    /**
     * STX CLK xbar provides configurability of a clock source for each STX channel
     */
    uint8_t stx_clk_xbar[SPICA_MAX_STX_CHANNELS+1];

    /**
     * LRX quality-check rules, which are common for all LRX channels
     */
    spica_rx_qc_rules_t lrx_qc;

    /**
     * HRX quality-check rules, which are common for all HRX channels
     */
    spica_rx_qc_rules_t hrx_qc;

    /** SDT (LOS De-assert) threshold (units are e_spica_los_ctrl_amp enum) */
    e_spica_los_ctrl_amp lrx_los_dsrt_ctrl_startup;

    /** LOS Assert threshold during startup (units are e_spica_los_ctrl_amp enum) */
    e_spica_los_ctrl_amp lrx_los_asrt_ctrl_startup;

    /** LOS Assert threshold during datamode (units are e_spica_los_ctrl_amp enum) */
    e_spica_los_ctrl_amp lrx_los_asrt_ctrl_datamode;

} spica_rules_t;

/**
 * Rules struct for defining a bundle
 *
 * @private
 */
typedef struct
{
    /** Enable flag */
    bool     en[SPICA_MAX_BUNDLES];

    /** Die associated with the bundle */
    uint32_t die[SPICA_MAX_BUNDLES];

    /** Line side channel map */
    uint16_t  line_ch_map[SPICA_MAX_BUNDLES];

    /** Host side channel map */
    uint16_t  host_ch_map[SPICA_MAX_BUNDLES];

} spica_bundle_rules_t;

#endif // __SPICA_RULES_H__
/** @file spica.h
 ****************************************************************************
 *
 * @brief
 *     This module describes the high level API methods provided
 *     by the Spica API.
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
#ifndef __SPICA_H__
#define __SPICA_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// MACROS - START
#define SPICA_MASK(NAME)            (NAME##__MASK << NAME##__OFFSET)
#define SPICA_OFFSET(NAME)          (NAME##__OFFSET)
#define SPICA_VAL(NAME, val)        (((val) & NAME##__MASK) << NAME##__OFFSET)
#define SPICA_ADDRESS(NAME)         (NAME##__ADDRESS)
#define SPICA_MASK_UNALIGNED(NAME)  (NAME##__MASK)
#define SPICA_ADDR_DIFF(A0, A1)     (A1##__ADDRESS - A0##__ADDRESS)
//MACROS - END

#define SPICA_MCU_IRAM_BASE_ADDR       0x5ffa0000
#define SPICA_MCU_IRAM_SIZE            0x8000 //128 kB in 32bit words
#define SPICA_MCU_DRAM_BASE_ADDR       0x5ff80000
#define SPICA_MCU_DRAM_SIZE            0x4000 //64 kB in 32bit words

/// To broadcast a register write to all channels, do not use in API methods, just in direct register accesses
#define SPICA_BROADCAST_CHANNEL 0xff

// Maximum time to wait for a ACK response from the FW, units are seconds
#define SPICA_ACK_WAIT_MAX      300 // seconds
//
// Maximum time to wait for the PLL to sync, units are seconds
#define SPICA_PLL_SYNC_WAIT_MAX 300 // seconds

/**
 * The maximum number of devices that the API can support in the same
 * system. This is used to manage caching the package type associated
 * with a particular die to handle mapping of API channel numbers to the external
 * pins of the ASIC.
 */
#ifndef SPICA_MAX_NUM_DEVICES
#define SPICA_MAX_NUM_DEVICES 8
#endif // SPICA_MAX_NUM_DEVICES

/**
 * Struct for saving the channel iterators
 *
 * @private
 */
typedef struct
{
    uint8_t num;
    uint8_t ch[16];
} spica_channels_t;

/**
 * Returns a list of valid channels on the selected interface
 *
 * @param die       [I] - The ASIC die being accessed.
 * @param intf      [I] - The interface.
 *
 * @return a pointer to a static/const spica_channels_t struct containing the channels info.
 *
 * @since 0.1.0.0
 *
 * @see spica_package_get_channels which does something similar
 */
const spica_channels_t* spica_channels(
    uint32_t      die, 
    e_spica_intf  intf);

/**
 * Returns a list of valid channels on the selected bundle of an interface
 *
 * @param die        [I] - The ASIC die being accessed.
 * @param bundle_idx [I] - The bundle number.
 * @param intf       [I] - The interface.
 *
 * @return a pointer to a static/const spica_channels_t struct containing the channels info.
 *
 * @since 0.1.0.0
 *
 * @see spica_package_get_channels which does something similar
 */
const spica_channels_t* spica_bundle_channels(
    uint32_t      die, 
    uint32_t      bundle_idx, 
    e_spica_intf  intf);

/**
 * Convenience macro for iterating through all channels on an interface.
 * Iterator will be called "channel"
 *
 * @example
 * SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_ORX)
 * {
 *      printf("ch %d\n", channel);
 * }
 */
#define SPICA_FOR_CHANNEL_IN_CHANNELS(die, intf) \
    for(const spica_channels_t *_chs=spica_channels(die, intf);_chs;_chs=NULL) \
    for(uint32_t _i=0; _i<_chs->num;_i++) \
    for(uint32_t _do=1, channel=_chs->ch[_i]; _do; _do=0)

/**
 * Convenience macro for iterating through channels of a bundle on an interface.
 * Iterator will be called "channel"
 *
 * @example
 * SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_ORX)
 * 
 *      printf("ch %d\n", channel);
 * }
 */
#define SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, intf) \
    for(const spica_channels_t *_chs=spica_bundle_channels(die, bundle_idx, intf);_chs;_chs=NULL) \
    for(uint32_t _i=0; _i<_chs->num;_i++) \
    for(uint32_t _do=1, channel=_chs->ch[_i]; _do; _do=0)

/**
 * This method will discover the package type and encode it in
 * the bits of the die parameter. This is generally the
 * first method the user should call in order to cache the package
 * type in the die parameter. This is used to avoid the overhead
 * of looking up the package type parameter on other calls.
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return
 * The die number with the package type encoded in
 * the lower bits.
 *
 * @since 0.1.0.0
 *
 * @deprecated
 * This method is no longer required. The API will query
 * the package type from the EFUSE and cache it.
 */
uint32_t spica_package_discover_type(
    uint32_t die);

/**
 * This method is used to query the package type from the efuse
 *
 * @since 0.1
 *
 * @private
 */
e_spica_package_type spica_package_query_efuse(
    uint32_t die);

/**
 * This method is used to determine the number of dies
 * inside the package.
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return The number of dies in the package.
 *
 * @since 0.1.0.0
 */
uint32_t spica_package_get_num_dies(
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
 * @since 0.1.0.0
 */
uint32_t spica_package_get_base_die(
    uint32_t die);

#if 0
/**
 * This method is called to get the bundle from the die.
 *
 * @param die    [I] - The ASIC die being accessed.
 *
 * @return The bundle associated to the die
 *
 * @since 0.1.0.0
 */
uint32_t spica_package_get_bundle_from_die(
    uint32_t die);
#endif //0

/**
 * This method is used to query the ASIC package type
 * from a given die.
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return
 * The ASIC package type defined in the MMD30_CHIP_ID
 * register.
 *
 * @private
 *
 * @since 0.1.0.0
 */
e_spica_package_type spica_package_get_type(
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
 * @since 0.1.0.0
 */
uint32_t spica_package_type_set_in_die(
    uint32_t die, 
    e_spica_package_type package);

/**
 * This is a private method that get the minumum and maximum channel 
 * numbers for the package. It's mostly used for the python wrapper.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param intf    [I] - The interface
 * @param min     [O] - Pointer to the minumum channel number
 * @param max     [O] - Pointer to the maximum channel number
 *
 * @return The number of dies in the package.
 *
 * @private
 *
 * @since 0.1.0.0
 */
void spica_package_get_channels(
    uint32_t     die, 
    e_spica_intf intf, 
    uint32_t*    min, 
    uint32_t*    max);

/**
 * This is a private method that gets the interfaces associated
 * with the die.
 *
 * @param die     [I] - The ASIC die being accessed.
 *
 * @return a bitwise or of the interface. see e_spica_intf
 *
 * @private
 *
 * @since 0.1.0.0
 */
uint32_t spica_package_get_intf(uint32_t die);

/**
 * This method is used to determine the die associated with a particular channel
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel being accessed.
 * @param intf    [I] - The interface
 *
 * @private
 *
 * @since 0.1.0.0
 */
uint32_t spica_reg_channel_to_die(
    uint32_t die, 
    uint32_t channel, 
    e_spica_intf intf);

/**
 * This method is called to dump the cache used to map a particular
 * die parameter to the associated ASIC package type. The package type
 * is important so that the API knows how to map channels to the external
 * pins of the ASIC.
 *
 * @since 0.1.0.0
 */
void spica_package_cache_dump(void);

/**
 * This method is called to clear the cache used to map a particular
 * die parameter to the associated ASIC package type. The package type
 * is important so that the API knows how to map channels to the external
 * pins of the ASIC.
 *
 * @since 0.15.0.0
 */
void spica_package_cache_clear();

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

/**
 * @h3 API Register Access Methods
 * ===============================
 * These are higher layer methods that build upon the
 * spica_reg_get/spica_reg_set methods. These should be used
 * when accessing the registers in the event that any special
 * handling needs to be implemented when accessing particular
 * registers.
 *
 * @brief
 * This method is used to write a register on the device. The
 * registers are actually only 16 bits but 32b is used for
 * internal validation purposes. The extra bits about 0xffff
 * are ignored.
 *
 * @param die  [I] - The ASIC die being accessed.
 * @param addr [I] - The address of the register being accessed.
 * @param data [I] - The data to write to the register.
 *
 * @since 0.1.0.0
 */
void spica_reg_write(
    uint32_t die, 
    uint32_t addr, 
    uint32_t data);

/**
 * This method is called to read an ASIC register.
 *
 * @param die  [I] - The ASIC die being accessed.
 * @param addr [I] - The address of the register being accessed.
 * 
 * @return The data read back from the register.
 *
 * @since 0.1.0.0
 */
uint32_t spica_reg_read(
    uint32_t die, 
    uint32_t addr);

/**
 * This method is called to perform a read/modify/write operation
 * on an ASIC register. This is used to modify bitfields within
 * a register.
 *
 * @param die  [I] - The ASIC die being accessed.
 * @param addr [I] - The address of the register being accessed.
 * @param data [I] - The data to write to the register.
 * @param mask [I] - A mask to ignore unsed bits.
 * 
 * @return The modified register value.
 *
 * @since 0.1.0.0
 */
uint32_t spica_reg_rmw(
    uint32_t die, 
    uint32_t addr, 
    uint32_t data, 
    uint32_t mask);

/**
 * @h4 Per-Channel Register Access Methods
 * =======================================
 * These methods are used to access a particular channel through the
 * ASIC. They automatically map the channel to the correct register instance
 * based on the ASIC type.
 *
 * @brief
 * This method is called to read a register for a particular channel through
 * the ASIC.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel being accessed.
 * @param addr    [I] - The address of the register being accessed.
 * 
 * @return The data read back from the register.
 *
 * @since 0.1.0.0
 */
uint32_t spica_reg_channel_read(
    uint32_t die, 
    uint32_t channel, 
    uint32_t addr);

/**
 * This method is used for writing to a register associated with a particular
 * channel. The registers are actually only 16 bits but 32b is
 * used for internal validation purposes. The extra bits about 0xffff
 * are ignored.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel being accessed.
 * @param addr    [I] - The address of the register being accessed.
 * @param data    [I] - The data to write to the register.
 *
 * @since 0.1.0.0
 */
void spica_reg_channel_write(
    uint32_t die, 
    uint32_t channel, 
    uint32_t addr, 
    uint32_t data);

/**
 * This method is called to perform a read/modify/write operation
 * on a register for a particular channel through the ASIC. This is used to
 * modify bitfields within a register.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel being accessed.
 * @param addr    [I] - The address of the register being accessed.
 * @param data    [I] - The data to write to the register.
 * @param mask    [I] - A mask to ignore unsed bits.
 * 
 * @return The modified register value.
 *
 * @since 0.1.0.0
 */
uint32_t spica_reg_channel_rmw(
    uint32_t die, 
    uint32_t channel, 
    uint32_t addr, 
    uint32_t data, 
    uint32_t mask);

/**
 * This method is used to re-map the address for particular register based
 * on the ASIC.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel being accessed.
 * @param addr    [I] - The address of the register being accessed.
 *
 * @since 0.1.0.0
 *
 * @return The corrected register channel for the target channel.
 */
uint32_t spica_reg_channel_addr(
    uint32_t die, 
    uint32_t channel,
    uint32_t addr);

/**
 * This method is called to manage re-mapping the channel based on
 * the register address being accessed.
 *
 * @param die     [I/O] - The die being accessed. This may be modified depending
 *                        on which channel in a multi-die package is being
 *                        accessed.
 * @param channel [I/O] - The channel through the device being accessed. This
 *                        may be re-mapped based on the package type.
 *
 * @param addr    [I/O] - The address of the register being accessed. This
 *                        may be re-mapped based on the pacakge type and channel.
 *
 * @since 1.0.0.0
 */
inphi_status_t spica_rebase_by_addr(
    uint32_t* die, 
    uint32_t* channel, 
    uint32_t* addr);

/**
 * This method is called to manage re-mapping the channel based on
 * the register interface being accessed.
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
 * @since 1.2.0.0
 *
 */
inphi_status_t spica_rebase_channel_by_intf(
    uint32_t* die, 
    uint32_t* channel, 
    uint32_t intf);

typedef inphi_status_t (*spica_callback_lock)(uint32_t die);
typedef inphi_status_t (*spica_callback_unlock)(uint32_t die);

/**
 * @h2 Hardware Locking Methods
 * =======================================================
 * The following methods provide supprort for multi-threading.
 * Because this is optional they are implemented as callback
 * methods that the user may chose to register.
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
 * @since 0.1.0.0
 */
void spica_set_callback_for_lock(
    spica_callback_lock callback);

/**
 * Setup a callback method to support h/w unlocking. Setting up
 * hardware locking is optional. It will be disabled by default.
 *
 * @param callback [I] - Pointer to the callback function to
 *                       call to lock access to the h/w.
 *
 * @return None
 *
 * @since 0.1.0.0
 */
void spica_set_callback_for_unlock(
    spica_callback_unlock callback);

    
#define SPICA_LOCK(die) {if(spica_lock(die) != INPHI_OK) return INPHI_ERROR;}
#define SPICA_UNLOCK(die) {if(spica_unlock(die) != INPHI_OK) return INPHI_ERROR;}

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
 * @param die [I] - The ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @see spica_set_callback_for_lock, spica_set_callback_for_unlock
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_lock(
    uint32_t die);

/**
 * Unlock the hardware for exclusive access. If hardware locking
 * has not been enabled then these methods silently return.
 *
 * @{note, The locking feature has not been tested}
* 
 * @param die [I] - The ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @see spica_set_callback_for_lock, spica_set_callback_for_unlock
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_unlock(
    uint32_t die);

/**
 * @h2 Firmware Management
 * =======================================================
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
    /** Unknown FW mode */
    SPICA_FW_MODE_UNKNOWN           = 0,
    /**  FW in pplication mode */
    SPICA_FW_MODE_APPLICATION       = 1,
    /** Boot Upgrade mode */
    SPICA_FW_MODE_BOOT_UPGRADE      = 2,
    /** Bootloader mode */
    SPICA_FW_MODE_BOOT_FROM_EEPROM  = 3,

} e_spica_fw_mode;

const char* spica_dbg_translate_fw_mode(
    e_spica_fw_mode mode);

const char* spica_dbg_translate_intf(
    e_spica_intf intf);

const char* spica_dbg_translate_package_type(
    e_spica_package_type package);

const char* spica_dbg_translate_driver_type_override(
    e_spica_driver_type driver_type_override);

const char* spica_dbg_translate_tx_swing(
    e_spica_tx_swing tx_swing);

const char* spica_dbg_translate_lut_mode(
    e_spica_lut_mode lut_mode);

const char* spica_dbg_translate_protocol_mode(
    e_spica_protocol_mode protocol_mode);

const char* spica_dbg_translate_signalling(
    e_spica_signal_mode signal_mode);

const char* spica_dbg_translate_six_bit_mode(
    uint8_t six_bit_mode);

const char* spica_dbg_translate_operational_mode(
    e_spica_operational_mode operational_mode);

const char* spica_dbg_translate_baud_rate(
    e_spica_baud_rate baud_rate);

/**
 * @h3 Switching Firmware Modes
 * =======================================================
 *
 * @brief
 * This method is called to reset the firmware into application mode. It
 * resets the MCU and switches to the application bank (assuming it
 * has been previously programmed in the IRAM/DRAM). If the
 * @{b,wait_till_started} flag is set it waits for the MCU_FW_MODE register to respicat
 * 0xACC0 to indicate that the application image has started up.
 *
 * This method assumes that the * firmware has been previously downloaded to the IRAM/DRAM.
 *
 * @{note,
 * To avoid blocking forever in the case of a failure or where the
 * firmware image is not yet programmed this method will timeout after five
 * seconds and return INPHI_ERROR.}
 *
 * @param die               [I] - The ASIC die being accessed.
 * @param wait_till_started [I] - Wait until the application firmware is started.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_reset_into_application(
    uint32_t die, 
    bool     wait_till_started);

/**
 * Query the current firmware mode
 *
 * @param die     [I]   - The physical ASIC die being accessed.
 * @param fw_mode [I/O] - The firmware mode.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_fw_mode_query(
    uint32_t         die, 
    e_spica_fw_mode* fw_mode);

/**
 * Write to MCU memory via the inbound PIF interface
 *
 * @param die       [I] - The ASIC die to target
 * @param addr      [I] - The address to write
 * @param buffer    [O] - The buffer to write from
 * @param num_words [I] - The number of 32 bit words to write from 'buffer'
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_pif_write(
    uint32_t        die,
    uint32_t        addr,
    const uint32_t* buffer,
    uint32_t        num_words);

/**
 * Read from MCU memory through the inbound PIF interface
 *
 * @param die       [I] - The ASIC die to target
 * @param addr      [I] - The address to read
 * @param buffer    [O] - The buffer to read into
 * @param num_words [I] - The number of 32 bit words to read into 'buffer'
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_pif_read(
    uint32_t  die,
    uint32_t  addr,
    uint32_t* buffer,
    uint32_t  num_words);

/**
 * Get the SRX pulse resp
 * @private
 */
inphi_status_t spica_msg_srx_pulse_resp_request(
    uint32_t die,
    uint32_t channel,
    int32_t *resp_values,
    uint32_t len);

/**
 * This is an internal method used to program the API version
 * number in one of the scratch registers so that it can be
 * identified through register dumps
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @private
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_init_api_version(uint32_t die);

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
 * @since 0.1.0.0
 */
inphi_status_t spica_wait_for_link_ready(
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
 * @since 0.1.0.0
 */
bool spica_channel_is_link_ready(
    uint32_t        die,
    uint32_t        channel,
    e_spica_intf      intf);

/**
 * This method is called to wait for link ready from a particular
 * channel. 
 *
 * @param die             [I] - The ASIC die being accessed.
 * @param channel         [I] - The channel to poll for link up.
 * @param intf            [I] - One or more interfaces to check. Note the intf
 *                              identifiers can be OR'd together.
 * @param timeout_in_usecs [I] - The timeout in microseconds to wait for the channel.
 *
 * @return INPHI_OK if the link is ready, INPHI_ERROR if the link is not ready.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_channel_wait_for_link_ready(
    uint32_t   die,
    uint32_t   channel,
    e_spica_intf intf,
    uint32_t   timeout_in_usecs);

/**
 * This method may be called to verify that the FW status
 * is ok. If not, a print of the FW status is performed.
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
 * @since 0.1.0.0
 */
bool spica_is_fw_running_ok(
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
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_block_application_mode(
    uint32_t die,
    int      timeout_in_ms);

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
 *                      to happen on every reset. | spica_mcu_download_firmware,
 *                      spica_mcu_download_firmware_from_external_memory,
 *                      spica_mcu_download_firmware_from_file
 *  
 * @brief
 * This method is called to download the firmware inlined
 * with the API directly to the MCUs RAM memory.
 *
 * It will program the microcode on all dies ,
 * jump to the new application image and verify it is
 * running properly.
 *
 * @param die    [I] - The ASIC die being accessed.
 * @param verify [I] - Optionally read back the programmed values
 *                     to verify the results. This is typically
 *                     not required and will slow down the programming
 *                     but is provided for users that want an
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
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_download_firmware(
    uint32_t die, 
    bool     verify);

/**
 * This method is called to fetch a pointer to the inlined f/w image.
 *
 * @param ptr    [O] - The pointer to the inlined firmware.
 * @param length [O] - The length of the firmware image in 32b words
 *
 * @requires
 * The API must have direct download support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 * - INPHI_HAS_INLINE_APP_FW
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_get_inline_firmware(
    const uint32_t** ptr, 
    uint32_t*        length);

/**
 * Get the inlined f/w version number.
 *
 * @return The inlined f/w version number (if present)
 *
 * @requires
 * The API must be compiled with
 * - INPHI_HAS_INLINE_APP_FW
 *
 * @since 0.1.0.0
 */
uint32_t spica_mcu_get_inline_firmware_version(void);

/**
 * This method is called to download the bootloader inlined
 * with the API directly to the MCUs RAM memory.
 *
 * It will program the bootloader microcode on all dies,
 * the bootlader will download the application image from EEPROM,
 * verify the checksum,
 * jump to the new application image
 *
 * @param die    [I] - The ASIC die being accessed.
 * @param verify [I] - Optionally read back the programmed values
 *                     to verify the results. This is typically
 *                     not required and will slow down the programming
 *                     but is provided for users that want an
 *                     extra integrity check.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must have direct download support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 * - INPHI_HAS_INLINE_BOOTLOADER_FW
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_download_bootloader(
    uint32_t die,
    bool     verify);

/**
 * This method is called to fetch a pointer to the inlined
 * bootloader image.
 *
 * @param ptr    [O] - The pointer to the inlined bootloader.
 * @param length [O] - The length of the firmware image in 32b words
 *
 * @requires
 * The API must have direct download support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 * - INPHI_HAS_INLINE_BOOTLOADER_FW
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_get_inline_bootloader(
    const uint32_t** ptr,
    uint32_t*        length);

/**
 * This method may be called to broadcast the firmware download to
 * multiple ASICs.
 *
 * @param die          [I] - The physical ASIC die being accessed.
 * @param get_firmware [I] - A callback method used to fetch the
 *                           firmware to download.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must have direct download support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 * - INPHI_HAS_INLINE_APP_FW
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_direct_download_image_bcast(
    uint32_t die,
    inphi_status_t (*get_firmware)( const uint32_t** ptr, uint32_t* length));

/**
 * This is a helper method used to broadcast the inlined firmware
 * to multiple ASICs.
 *
 * @param die  [I] - The physical ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must have direct download support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 * - INPHI_HAS_INLINE_APP_FW
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_direct_download_image_bcast_inline(
    uint32_t die);

/**
 * This is a helper method used to broadcast a particular image
 * to multiple IPs.
 *
 * @param die  [I] - The physical ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must have direct download support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_direct_download_image_bcast_buffer(
    uint32_t        die,
    const uint32_t* image_ptr,
    uint32_t        length);

#if 0
/**
 * This wrapper method may be called after programming the firmware to
 * verify the contents of the IRAM/DRAM firmware image. This is primarily
 * for testing via Python
 *
 * @{note, If the f/w is stalled then both the IRAM and DRAM images will
 *         be verified otherwise if the f/w is not stalled then only 
 *         the IRAM image will be verified.
 *
 * @param die          [I] - The ASIC die being accessed.
 *
 * @return INPHI_OK if the image is ok, INPHI_ERROR if the image
 *         is not ok.
 *
 * @requires
 * The API must have direct download support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_verify_image_wrapper(
    uint32_t        die);

/**
 * This method may be called after programming the firmware to
 * verify the contents of the IRAM/DRAM firmware image.
 *
 * @{note, If the f/w is stalled then both the IRAM and DRAM images will
 *         be verified otherwise if the f/w is not stalled then only 
 *         the IRAM image will be verified.
 *
 * @param die          [I] - The ASIC die being accessed.
 * @param image        [I] - The pointer to the firmware image to verify
 *                           against.
 * @param image_length [I] - The length of the firmware image in 32b words.
 *
 * @return INPHI_OK if the image is ok, INPHI_ERROR if the image
 *         is not ok.
 *
 * @requires
 * The API must have direct download support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_verify_image(
    uint32_t        die,
    const uint32_t* image,
    uint32_t        image_length);
#endif //0

/**
 * This method is called to download the firmware directly
 * to the MCUs RAM memory.
 * It will program the microcode on all dies,
 * jump to the new application image and verify it is
 * running properly.
 *
 * @param die    [I] - The ASIC die being accessed.
 * @param path   [I] - The path to the application firmware
 *                     to program.
 * @param verify [I] - Optionally performs a CRC-32 checksum calculation
 *                     on the programmed firmware and compares this calculated 
 *                     result with the value embedded in the file. This is 
 *                     provided for users that want an extra integrity check.
 *                     Note that for FW versions older than 0.8.468, this flag 
 *                     msut be set to false as this verify is not supported. 
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must have file system support. It must be
 * compiled with the following flags set to 1:
 * - INPHI_HAS_DIRECT_DOWNLOAD
 * - INPHI_HAS_FILESYSTEM
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_download_firmware_from_file(
    uint32_t    die, 
    const char* path, 
    bool        verify);

/**
 * This method is called to zero initialize the IRAM and DRAM memories
 * to ensure ECC bits are properly initialized
 *
 * @param die    [I] - The ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_ram_init(
    uint32_t die);

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
 * status |= spica_mcu_reset_into_boot_upgrade(die, true);
 *
 * // Re-program the EEPROM image
 * status |= spica_mcu_download_eeprom_from_file(die, "/path/to/eeprom/image.txt");
 *
 * // Verify the EEPROM image
 * status |= spica_mcu_eeprom_verify_with_checksum(die, 0, checksum_calculated, checksum_expected);
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
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_download_eeprom_from_file(
    uint32_t    die,
    const char* path);

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
 * @since 0.1.0.0
 * 
 * @requires
 * The API must have EEPROM access support. It must be compiled
 * with the following flags:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
inphi_status_t spica_mcu_eeprom_read_metadata(
    uint32_t die,
    char*    metadata,
    uint32_t metadata_size);

#endif // defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)

/**
 * @h2 DSP diagnostics
 * =======================================================
 *
 * @brief
 * This defines the DSP methods used for diagnostics.
 *
 * @since 0.13.0.0 
 * 
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */

// encoding for CP_SNR_RUN_CFG.duration
#define SPICA_RX_DSP_DURATION_16      0  // duration = 2^16
#define SPICA_RX_DSP_DURATION_15      1  // duration = 2^15
#define SPICA_RX_DSP_DURATION_14      2  // duration = 2^14
#define SPICA_RX_DSP_DURATION_13      3  // duration = 2^13
#define SPICA_RX_DSP_DURATION_12      4  // duration = 2^12
#define SPICA_RX_DSP_DURATION_11      5  // duration = 2^11
#define SPICA_RX_DSP_DURATION_10      6  // duration = 2^10
#define SPICA_RX_DSP_DURATION_9       7  // duration = 2^9

#define SPICA_RX_DSP_SETTLE_11        0  // 2^11
#define SPICA_RX_DSP_SETTLE_10        1  // 2^10
#define SPICA_RX_DSP_SETTLE_9         2  // 2^9
#define SPICA_RX_DSP_SETTLE_8         3  // 2^8
#define SPICA_RX_DSP_SETTLE_7         4  // 2^7
#define SPICA_RX_DSP_SETTLE_6         5  // 2^6
#define SPICA_RX_DSP_SETTLE_5         6  // 2^5

#define SPICA_RX_DSP_STEP_SIZE        2
#define SPICA_RX_DSP_MAX_STEP         64
#define SPICA_RX_DSP_API_REQUEST_BIT  7
#define SPICA_RX_DSP_API_ACK_BIT      8
#define SPICA_RX_DSP_ACC_REG          0x8000
#define SPICA_RX_DSP_ACC_WR           0x4000
#define SPICA_RX_DSP_FORMAT_24b       0x0000
#define SPICA_RX_DSP_FORMAT_12b       0x1000
#define SPICA_RX_DSP_FORMAT_32b       0x2000
#define SPICA_RX_DSP_FW_TIME_OUT      2000  // 2 sec timeout
#define SPICA_RX_DSP_HIST_BINS        256   // number of histogram bins
#define SPICA_RX_DSP_HIST_TH_SLICES   16    // number of histogram track and hold slices

// encoding for CP_PR_CFG.slc_id
#define SPICA_RX_DSP_CAL_SLICER       0
#define SPICA_RX_DSP_PROBE_SLICER     1

//# encoding for CP_PR_CFG.mu[3:0]
#define SPICA_RX_DSP_MU_MINUS_6       0  // mu = 7 * 2^-6
#define SPICA_RX_DSP_MU_MINUS_7       1  // mu = 7 * 2^-7
#define SPICA_RX_DSP_MU_MINUS_8       2  // mu = 7 * 2^-8
#define SPICA_RX_DSP_MU_MINUS_9       3  // mu = 7 * 2^-9
#define SPICA_RX_DSP_MU_MINUS_10      4  // mu = 7 * 2^-10
#define SPICA_RX_DSP_MU_MINUS_11      5  // mu = 7 * 2^-11
#define SPICA_RX_DSP_MU_MINUS_12      6  // mu = 7 * 2^-12
#define SPICA_RX_DSP_MU_MINUS_13      7  // mu = 7 * 2^-13
#define SPICA_RX_DSP_MU_MINUS_14      8  // mu = 7 * 2^-14
#define SPICA_RX_DSP_MU_MINUS_15      9  // mu = 7 * 2^-15

//# encoding for CP_PR_CFG.isi_d_qual[1:0] and lms1q[1:0]
#define SPICA_RX_DSP_QUAL_MINUS_3     0
#define SPICA_RX_DSP_QUAL_MINUS_1     1
#define SPICA_RX_DSP_QUAL_PLUS_1      2
#define SPICA_RX_DSP_QUAL_PLUS_3      3

//# constants for indexing results structures
#define SPICA_RX_DSP_SLICES           16
#define SPICA_RX_DSP_LO_HI            2  // LO = 0; HI = 1
#define SPICA_RX_DSP_NUM_FFE_TAPS     10
#define SPICA_RX_DSP_LO               0  
#define SPICA_RX_DSP_HI               1 

//# quantity of ISI taps to collect, max 48 if first = 0
#define SPICA_RX_DSP_QTY              48

/**
 * @h3 Histogram
 * =======================================================
 * The following methods are used to manage capturing and
 * displaying the histogram.
 *
 * @brief
 * Initialize then capture the RX DSP histogram.
 * Note that this method captures the histogram data from the HW.
 *
 * @param die        [I] - The ASIC die being accessed.
 * @param channel    [I] - The channel through the device to query.
 * @param intf       [I] - The interface
 * @param histo      [O] - Pointer to the histogram data. This must be a buffer
 *                         of exactly [16384] entries of uint32_t.
 *                
 * histo Documentation
 * 
 * 1D array containing data for 16 interleaves, 4 levels/interleave, 256 data points per level
 * Array dimension = 16 x 4 x 256 = 16,384
 *
 * The array is packed as follows:
 * 
 * Interleave |  Level M3  |  Level M1  |  Level P1  |  Level P3  |
 * -----------+------------+------------+------------+------------+
 *      0     |    0-255   |   256-511  |  513-767   |  768-1023  |
 *      ...   |    ...     |   ...      |  ...       |  ...       |
 *      15    | 15358-15615| 15616-15871| 15872-16127| 16128-16383|
 * -----------+------------+------------+------------+------------+
 *
 * Note: Each level is allocated 256 uint32_t entries in the array. However, it only fills 64 of them.
 * 256 entries represents the full DAC code range.  The data associated with the specific level (64 entries) is then saved
 * around the true DAC code level within this range. 32 data points on either side of the actual amp location.
 *
 * For example:                
 * - Interleave 0, level M3 (level centered about actual DAC code 58)
 *
 *              *
 *              ** 
 *             ****
 *             *****
 *            *******
 *           *********
 *         *************
 *        **************** 
 *      *******************
 *  +-----------------------------------------------------------------------------+
 *  0   26       58       90                                                    255
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.13.0.0
 */
inphi_status_t spica_rx_dsp_hist_get(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,   
    uint32_t*    histo);

/**
 * This method is called to read the SNR monitor value from the hardware
 * and translate it to a decimal (fixed-point) dB value.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel through the device to query.
 * @param intf    [I] - The interface
 *
 * @return The (fixed-point) SNR value
 * SNR(dB) = SNR(fixed-point) / 1600
 *
 * @since 0.13.0.0
 */
uint16_t spica_rx_dsp_snr_read_db_fixp(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf);

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)

/**
 * This method is called to read the SNR monitor value from the hardware
 * and translate it to a decimal dB value.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel through the device to query.
 * @param intf    [I] - The interface
 *
 * @return The SNR value in dB
 *
 * @see
 * spica_rx_dsp_snr_read_db_fixp() to return the raw SNR value reported
 * by the hardware that has not been converted to dB.
 *
 * @since 0.13.0.0
 */
double spica_rx_dsp_snr_read_db(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf);
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
 * @param intf    [I] - The interface (SPICA_INTF_ORX, SPICA_INTF_MRX only for now)
 * @param ltp     [O] - Minimum LTP
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @see
 * spica_rx_dsp_ltp_format to convert to a double value.
 *
 * @since 1.1.0.0
 */
inphi_status_t spica_rx_dsp_ltp_read_fixp(uint32_t die, uint32_t channel, e_spica_intf intf, uint16_t *ltp);

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
 * spica_rx_dsp_ltp_read_fixp to read the fixed-point ltp value.
 *
 * @requires
 * The API must be compiled with INPHI_HAS_MATH_DOT_H and INPHI_HAS_FLOATING_POINT flags.
 * This will pull in the <math.h> library which will increase the size of
 * the generated image.
 *
 * @since 1.1.0.0
 */
double spica_rx_dsp_ltp_format(uint16_t ltp);

#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)
#endif // defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)

/**
 * @h3 VGA Diagnostics
 * =======================================================
 * This section contains routines used to query the VGA
 *
 * @brief
 * VGA 
 */
/**
 * This method is called to read the raw VGA1 value from
 * the hardware for the input channel. The return value is NOT in dB.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel through the device to query.
 * @param intf    [I] - The interface 
 *
 * @return The raw VGA1 value read from the hardware.
 *
 * @since 0.13.0.0
 *
 */
inphi_status_t spica_rx_dsp_vga1_query(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    uint16_t* vga1_gain);

/**
 * This method is called to read the raw VGA2 values from
 * the hardware for the input channel. The return value is NOT in dB.
 *
 * @param die         [I] - The ASIC die being accessed.
 * @param channel     [I] - The channel through the device to query.
 * @param intf        [I] - The interface 
 * @param vga2_gain   [O] - The array of vga2 values to populate
 *
 * @return The raw VGA2 value read from the hardware.
 *
 * @since 0.14.0.0
 *
 */
inphi_status_t spica_rx_dsp_vga2_query(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    int16_t vga2_gain[SPICA_RX_DSP_SLICES]);

/**
 * @h3 FFE Taps
 * =======================================================
 * This section contains routines used to query the FFE
 * tap values for each of the 16 interleaves
 *
 * @brief
 * FFE Tap indices
 */
typedef enum
{
    /** pre-cursor 3 Tap index */
    SPICA_FFE_TAP_PRE_CURSOR_3  = 0,
    /** pre-cursor 2 Tap index */
    SPICA_FFE_TAP_PRE_CURSOR_2  = 1,
    /** pre-cursor 1 Tap index */
    SPICA_FFE_TAP_PRE_CURSOR_1  = 2,
    /** main cursor Tap index */
    SPICA_FFE_TAP_MAIN_CURSOR   = 3,
    /** post-cursor 1 Tap index */
    SPICA_FFE_TAP_POST_CURSOR_1 = 4,
    /** post-cursor 2 Tap index */
    SPICA_FFE_TAP_POST_CURSOR_2 = 5,
    /** post-cursor 3 Tap index */
    SPICA_FFE_TAP_POST_CURSOR_3 = 6,
    /** post-cursor 4 Tap index */
    SPICA_FFE_TAP_POST_CURSOR_4 = 7,
    /** post-cursor 5 Tap index */
    SPICA_FFE_TAP_POST_CURSOR_5 = 8,
    /** post-cursor 6 Tap index */
    SPICA_FFE_TAP_POST_CURSOR_6 = 9,
}e_spica_ffe_taps;

/**
 * Query the FFE taps
 *
 * To get a floating point value for the ffe_tap divide by 64.0
 *
 * @param die             [I] - The ASIC die being accessed.
 * @param channel         [I] - The channel through the device to query.
 * @param intf            [I] - The interface
 * @param ffe_taps        [O] - The array of taps to populate (S7.6 format)
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.13.0.0
 */
inphi_status_t spica_rx_dsp_ffe_taps_query(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    int16_t ffe_taps[SPICA_RX_DSP_SLICES*SPICA_RX_DSP_NUM_FFE_TAPS]);

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1
/**
 * This is a debug method used to translate the FFE taps index into a human
 * readable string for diagnostic dumps
 *
 * @param tap_index [I] - The tap index to translate to a string
 *
 * @return The human readable version of the FFE tap.
 *
 * @requires
 * The API must be compiled with the following compilation define:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS == 1
 *
 * @since 0.13.0.0
 */
const char* spica_rx_dsp_dbg_translate_ffe_tap_index(
    e_spica_ffe_taps tap_index);

/**
 * Print the FFE taps for a particulr channel and FFE sub-channel
 *
 * @param die             [I] - The ASIC die being accessed.
 * @param channel         [I] - The channel through the device to query.
 * @param intf            [I] - The interface
 * @param ffe_sub_channel [I] - The FFE sub-channel to print the
 *                              tap values for.
 * @param ffe_taps        [I] - The array of FFE taps queried via the
 *                              spica_rx_dsp_ffe_taps_query method.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @see spica_rx_dsp_ffe_taps_query
 *
 * @requires
 * The API must be compiled with the following compilation define:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS == 1
 * - INPHI_HAS_FLOATING_POINT==1
 *
 * @since 0.13.0.0
 */
inphi_status_t spica_rx_dsp_ffe_taps_print(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    int16_t ffe_taps[SPICA_RX_DSP_SLICES*SPICA_RX_DSP_NUM_FFE_TAPS]);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

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
 * EEPROM can support. Typically this will be SPICA_SPI_CLK_DIV_64.
 *
 * @since 0.1.0.0 
 * 
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
typedef enum
{
    /** Divide by 16 */
    SPICA_SPI_CLK_DIV_16 = 3,
    /** Divide by 32 */
    SPICA_SPI_CLK_DIV_32 = 4,
    /** Divide by 64 */
    SPICA_SPI_CLK_DIV_64 = 5,
    /** Divide by 128 */
    SPICA_SPI_CLK_DIV_128 = 6,
    /** Divide by 256 */
    SPICA_SPI_CLK_DIV_256 = 7
} e_spica_spi_clk_div;

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
 * @since 0.1.0.0
 * 
 * @requires
 * The API must have EEPROM access support. It must be compiled
 * with the following flags:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
inphi_status_t spica_spi_read_data_block(
    uint32_t            die,
    uint32_t            eeprom_addr,
    uint32_t            *words,
    uint32_t            num_words,
    e_spica_spi_clk_div clkdiv);

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
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
inphi_status_t spica_spi_write_data_block(
    uint32_t            die,
    uint32_t            eeprom_addr,
    uint32_t            *words,
    uint32_t            num_words,
    e_spica_spi_clk_div clkdiv);

/**
 * This method is called to erase the EEPROM
 *
 * @param die         [I] - The physical ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_EEPROM_ACCESS=1
 */
inphi_status_t spica_spi_eeprom_erase(
    uint32_t die);

#endif // defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)

/**
 * @h3 Bootloader Status Information
 * @brief
 * The current bootloader error status
 */
typedef enum
{
    /** EEPROM content successfully downloaded to RAMs and CRC passed */
    SPICA_BOOT_DOWNLOAD_OK = 1,
    /** Error in total size (IRAM+DRAM) read from EEPROM Header */
    SPICA_BOOT_ERR_SPI_IMG_SIZE = 2,
    /** Error in IRAM size read from EEPROM Header */
    SPICA_BOOT_ERR_SPI_IRAM_SIZE = 3,
    /** Error in DRAM size read from EEPROM Header */
    SPICA_BOOT_ERR_SPI_DRAM_SIZE = 4,
    /** SPI read from EEPROM timed-out */
    SPICA_BOOT_ERR_SPI_RECEIVE_TIMEOUT = 5,
    /** CRC check on downloaded EEPROM content failed */
    SPICA_BOOT_ERR_BOOT_CRC_FAIL = 6,
    /** Download process is on-going, not yet done */
    SPICA_BOOT_BOOT_IN_PROGRESS = 7,
    /** SPI reset timed-out (FW could not confirm SPI had been properly reset) */
    SPICA_BOOT_ERR_SPI_RESET_TIMEOUT = 8,
    /** A memory protection error occurred (only in boot upgrade mode) */
    SPICA_BOOT_ERR_MEMORY_GRANT = 9,
    /** An unknown parameter was received by the bootloader (only in boot upgrade mode) */
    SPICA_BOOT_ERR_MESSAGE_UNNOWN_PARAM = 10,
    /** An invalid message was received by the bootloader (only in boot upgrade mode) */
    SPICA_BOOT_ERR_MESSAGE_INVALID_TYPE = 11,
    /** A partial message was aborted by the host (only in boot upgrade mode) */
    SPICA_BOOT_ERR_MESSAGE_ABORT = 12,

}e_spica_bootloader_error_status;

/**
 * The current bootloader status bit map
 */
typedef enum
{
    /** A boot operation complete, the EEPROM has been programmed, and the bootloader jumped to application mode */
    SPICA_BOOT_COMPLETE = 0x8000,
    /** A boot from EEPROM operation failed, the bootloader will continue retrying */
    SPICA_BOOT_FROM_EEPROM_FAILED = 0x4000,
    /** The boot from EEPROM was aborted by the EEPROM header and jumped to boot upgrade mode */
    SPICA_BOOT_FROM_EEPROM_ABORTED = 0x2000,
    /** The bootloader detected an empty EEPROM and jumped to boot upgrade mode */
    SPICA_EEPROM_EMPTY = 0x1000,
    /** A corrupted image was detected during boot */
    SPICA_BOOT_CORRUPT_IMAGE_DETECTED = 0x0800,
    /** A boot operation is currently in progress */
    SPICA_BOOT_IN_PROGRESS = 0x0100

}e_spica_bootloader_status;

/**
 * This structure contains the bootloader status information
 */
typedef struct
{
    /** bootloader status */
    uint16_t status;

    /** Number of boot retries */
    uint8_t retries;

    /** Boot status code */
    e_spica_bootloader_error_status error_status;

} spica_bootloader_status_t;

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * Print the bootloader status
 *
 * @param bootloader_status [I] - The status of the bootloader
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 */
inphi_status_t spica_bootloader_status_print(
    spica_bootloader_status_t* bootloader_status);

/**
 * This method gets then displays the bootloader status
 *
 * @param die         [I] - The physical ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 */
inphi_status_t spica_bootloader_status_query_print(
    uint32_t die);

#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * Fetch the bootloader status
 *
 * @param die               [I] - The physical ASIC die being accessed.
 * @param bootloader_status [O] - The status of the bootloader
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 */
inphi_status_t spica_bootloader_status_query(
    uint32_t die,
    spica_bootloader_status_t* bootloader_status);

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
    e_spica_fw_mode fw_mode;
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
}spica_mcu_status_t;

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
inphi_status_t spica_mcu_status_query(
    uint32_t            die,
    spica_mcu_status_t* mcu_status);

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
inphi_status_t spica_mcu_status_query_print(
    uint32_t die);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

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
 * @since 0.1.0.0 
 */
inphi_status_t spica_mcu_pc_log_query(
    uint32_t  die,
    uint32_t* entries,
    uint32_t  num_entries);

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/**
 * This method is used to print a trace of the program counter from
 * the MCU for debug purposes.
 *
 * @param die         [I] - The physical ASIC being accessed.
 * @param num_entries [I] - The number of entries to print.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must be compiled with INPHI_HAS_DIAGNOSTIC_DUMPS flag
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_pc_log_query_print(
    uint32_t die,
    uint32_t num_entries);

/**
 * This method is used to print the firmware trace log
 * for debug purposes.
 *
 * @param die         [I] - The physical ASIC being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @requires
 * The API must be compiled with INPHI_HAS_DIAGNOSTIC_DUMPS flag
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_debug_log_query_print(
    uint32_t die);

/**
 * This method is used to print the firmware trace log into a buffer,
 * for debug purposes.
 *
 * buff_size can be any length you want, the recommended size is
 * available via SPICA_MCU_DEBUG_BUFFER_MAX_LENGTH. However if a smaller size
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
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_debug_log_query(
    uint32_t die,
    char*    buff,
    uint32_t buff_size);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * This method is called to update the current setting of the f/w debug log
 * filter. The filter is used to restrict which log messages get displayed
 * in the firmware log
 *
 * @param die    [I] - The physical ASIC die being accessed.
 * @param filter [I] - The filter to use to filter log messages in the f/w log.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_debug_log_filter_set(
    uint32_t die, 
    uint32_t filter);

/**
 * @h2 MCU Diagnostics
 * =======================================================
 * @note
 *
 * Use spica_mcu_fw_mode_query to determine the current FW mode.
 *
 * @brief
 * Struct mimicing the one from the FW, which contains imspicatant
 * addresses for PIF accesses.
 *
 * @since 0.1.0.0
 *
 * @private
 */
typedef struct
{
    /** The address of the firmwares debug log */
    uint32_t debug_buffer_address;

    /** Address of the info buf */
    uint32_t info_buf_address;
}spica_fw_info_t;

/**
 * Reads the fw_info struct from the FW.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param fw_info [O] - FW info struct read from the FW.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 *
 * @private
 */
inphi_status_t spica_mcu_fw_info_query(
    uint32_t       die,
    spica_fw_info_t *fw_info);

/**
 * Top bits of the MCU DRAM address space
 * @private
 */
#define SPICA_MCU_DRAM_ADDR_MSW 0x5ff8

/**
 * Write to MCU memory via the inbound PIF interface
 *
 * @param die       [I] - The ASIC die to target
 * @param addr      [I] - The address to write
 * @param buffer    [O] - The buffer to write from
 * @param num_words [I] - The number of 32 bit words to write from 'buffer'
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_pif_write(
    uint32_t        die,
    uint32_t        addr,
    const uint32_t* buffer,
    uint32_t        num_words);

/**
 * Read from MCU memory through the inbound PIF interface
 *
 * @param die       [I] - The ASIC die to target
 * @param addr      [I] - The address to read
 * @param buffer    [O] - The buffer to read into
 * @param num_words [I] - The number of 32 bit words to read into 'buffer'
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_mcu_pif_read(
    uint32_t  die,
    uint32_t  addr,
    uint32_t* buffer,
    uint32_t  num_words);

/**
 * @h2 Version Information
 * =======================================================
 *
 * @brief
 * This method is used to retreive the API version string describing
 * the version of the API in use. The user must allocate
 * a buffer of at least 256 bytes to retrieve the version information.
 * 
 * @param buffer     [O] - The output buffer where the version string will
 *                         be stored.
 * @param buffer_len [I] - The length of the allocated buffer. Units are bytes.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure 
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_version(
    char*    buffer, 
    uint32_t buffer_len);

/**
 * @brief
 * This method is used to retreive the version string describing
 * the version of the firmware in use. The user must allocate
 * a buffer of at least 256 bytes to retrieve the version information.
 *
 * @param die        [I] - TThe ASIC die being accessed.
 * @param buffer     [O] - The output buffer where the version string will
 *                         be stored.
 * @param buffer_len [I] - The length of the allocated buffer. Units are bytes.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure 
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_version_firmware(
    uint32_t die,
    char*    buffer, 
    uint32_t buffer_len);

/**
 * @h2 PRBS Generator/checker
 * =======================================================
 *
 * @brief
 * PRBS pattern types.
 */
typedef enum
{

    /** PRBS x^31+x^28+1 */
    SPICA_PAT_PRBS31                = 0,
    /** PRBS x^7+x^6+1 */
    SPICA_PAT_PRBS7                 = 1,
    /** PRBS x^9+x^5+1 */
    SPICA_PAT_PRBS9_5               = 2,
    /** PRBS x^9+x^4+1 */
    SPICA_PAT_PRBS9_4               = 3,
    /** PRBS x^11+x^9+1 */
    SPICA_PAT_PRBS11                = 4,
    /** PRBS x^13+x^12+x^2+x+1 */
    SPICA_PAT_PRBS13                = 5,
    /** PRBS x^15+x^4+1 */
    SPICA_PAT_PRBS15                = 6,
    /** PRBS x^23+x^18+1 */
    SPICA_PAT_PRBS23                = 7,
    /** PRBS x^58+x^39+1*/
    SPICA_PAT_PRBS58                = 8,
    /** PRBS x^16+x^5+x^3+x^2+1 */
    SPICA_PAT_PRBS16                = 9,
    /** Invalid PRBS pattern */ 
    SPICA_PAT_NONE                  = 10

} e_spica_prbs_pat;

/**
 * Tx PRBS pattern modes 
 */
typedef enum
{
    /** PRBS pattern modes */
    SPICA_PRBS_PATTERN_PRBS   = 0,
    /** Programmable fixed pattern mode */
    SPICA_PRBS_PATTERN_FIXED  = 1,
    /** JP03B test pattern. IEEE 802.3bs Clause 120.5.10.2.2*/
    SPICA_PRBS_PATTERN_JP083B = 2,
    /** Transmitter linearity test pattern. IEEE 802.3bs Clause 120.5.10.2.4 */
    SPICA_PRBS_PATTERN_LIN    = 3,
    /** CID jitter tolerance test pattern. OIF-CEI-3.1 Sections 2.1.1.1 and 2.5.1.1 */
    SPICA_PRBS_PATTERN_CJT    = 4,
    /** SSPRQ pattern, IEEE 802.3bs Clause 120.5.11.2.3 */
    SPICA_PRBS_PATTERN_SSPRQ  = 5

} e_spica_prbs_pat_mode;

/**
 * Rx PRBS checker modes
 */
typedef enum
{
    /** PRBS mode for individual MSB/LSB bit streams in a PAM-4 symbol */
    SPICA_PRBS_MODE_MSB_LSB   = 0,
    /** PRBS mode for a combined PAM-4 symbol */
    SPICA_PRBS_MODE_COMBINED  = 1

} e_spica_prbs_chk_mode;

/**
 * Tx error injection patterns
 */
typedef enum
{
    /** Bit 0 (one MSB). 0x0000_0000_0000_0001 */
    SPICA_ERRINJ_PAT_BIT0  = 0,
    /** Bit 1 (one LSB). 0x0000_0000_0000_0002 */    
    SPICA_ERRINJ_PAT_BIT1  = 1,
    /** Bits 0 and 1 (one PAM4 symbol). 0x0000_0000_0000_0003 */
    SPICA_ERRINJ_PAT_BIT01 = 2,
    /** All MSBs. 0x5555_5555_5555_5555 */    
    SPICA_ERRINJ_PAT_MSBS  = 3,
    /** All LSBs. 0xAAAA_AAAA_AAAA_AAAA */    
    SPICA_ERRINJ_PAT_LSBS  = 4,
    /** All bits. 0xFFFF_FFFF_FFFF_FFFF */    
    SPICA_ERRINJ_PAT_ALL   = 5, 
    /** One bit per word. The position shifts right each time an error is injected */    
    SPICA_ERRINJ_PAT_WALK  = 6, 
    /** One 2-bit PAM4 symbol per word. The position shift right two bits each time an error is injected */
    SPICA_ERRINJ_PAT_WALK3 = 7 

} e_spica_prbs_err_inj_pat;

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
    e_spica_prbs_chk_mode prbs_mode;

    /** The LSB PRBS pattern to transmit */
    e_spica_prbs_pat prbs_pattern_lsb;

    /** The PRBS pattern to transmit */
    e_spica_prbs_pat prbs_pattern;

    /** * Selects the type of test pattern that is generated. */
    e_spica_prbs_pat_mode pattern_mode;

    /** Specifies the fixed pattern word value that the fixed pattern checker attempts to lock to. 
     *  Bit 63 is expected to be received first. The default corresponds to the JP03A pattern described 
     *  in IEEE 802.3bs Clause 120.5.10.2.1. */

    /** When set each PRBS bit is transmitted in one UI, i.e. NRZ mode.  
     *  When cleared two adjacent PRBS bits are transmitted in one UI, i.e. PAM4 mode.  
     *  Do not attempt to combine dual PRBS mode and NRZ mode. */
    bool nrz_mode;

    /** PRBS Seed (Even) Configuration:
     *  This is the seed used when re-seeding (re-seeding is an optional feature).  The bit positions used for 
     *  each PRBS polynomial order are shown below.  Ensure at least one bit of the seed being used is High.
     *  The seed itself does not come out of the generator, instead the seed represents previously generated bits.  
     *  So the first bit of generator output is based off the seed bits, but does not equal the seed bits.  
     *  The seed is LSB first, meaning the LSB of the seed represents the oldest previously generated bit and 
     *  the MSB of the seed represents the nevest previously generated bit.
     *  This even seed is applied when GEN_PRBS_SEED_CFG__reseed_evn is High in two cases:
     *  
     *  1) Rising edge of GEN_PRBS_SEED_CFG__reseed.
     *  2) GEN_CFG__prbs_mode changes and GEN_PRBS_SEED_CFG__reseed is High.
     *  
     *  PRBS order 7  use bits 57:51
     *  PRBS order 9  use bits 57:49
     *  PRBS order 11 use bits 57:47
     *  PRBS order 13 use bits 57:45
     *  PRBS order 15 use bits 57:43
     *  PRBS order 16 use bits 57:42
     *  PRBS order 23 use bits 57:35
     *  PRBS order 31 use bits 57:27
     *  PRBS order 58 use bits 57:0
     *  
     *  Fixed Pattern Value 0 Configuration:
     *  One of the fixed pattern word values. Bit 63 of this pattern is transmitted first. The fixed pattern consists 
     *  of two 64-bit words, each repeated a configurable number of times. The default fixed pattern is the 
     *  JP03A pattern described in IEEE 802.3bs Clause 120.5.10.2.1. */
    uint16_t seed_evn_0;
    uint16_t seed_evn_1;
    uint16_t seed_evn_2;
    uint16_t seed_evn_3;

    /** PRBS Seed (Odd) Configuration:
     *  This is the seed used when re-seeding (re-seeding is an optional feature).  The bit positions used for 
     *  each PRBS polynomial order are shown below.  Ensure at least one bit of the seed being used is High.
     *  The seed itself does not come out of the generator, instead the seed represents previously generated bits.  
     *  So the first bit of generator output is based off the seed bits, but does not equal the seed bits.  
     *  The seed is LSB first, meaning the LSB of the seed represents the oldest previously generated bit and 
     *  the MSB of the seed represents the nevest previously generated bit.
     *  This odd seed is applied when GEN_PRBS_SEED_CFG__reseed_odd is High in two cases:
     *  1) Rising edge of GEN_PRBS_SEED_CFG__reseed.
     *  2) GEN_CFG__prbs_mode changes and GEN_PRBS_SEED_CFG__reseed is High.
     *  PRBS order 7  use bits 57:51
     *  PRBS order 9  use bits 57:49
     *  PRBS order 11 use bits 57:47
     *  PRBS order 13 use bits 57:45
     *  PRBS order 15 use bits 57:43
     *  PRBS order 16 use bits 57:42
     *  PRBS order 23 use bits 57:35
     *  PRBS order 31 use bits 57:27
     *  PRBS order 58 use bits 57:0
     *  
     *  Fixed Pattern Value 1 Configuration:
     *  One of the fixed pattern word values. Bit 63 of this pattern is transmitted first. The fixed pattern consists 
     *  of two 64-bit words, each repeated a configurable number of times. */
    uint16_t seed_odd_0;
    uint16_t seed_odd_1;
    uint16_t seed_odd_2;
    uint16_t seed_odd_3;

} spica_prbs_gen_rules_t;

const char* spica_prbs_translate_pat(
    e_spica_prbs_pat pattern); 

/**
 * This method is used to set the PRBS generator rules to their default values.
 *
 * @param gen_rules [I/O] - The PRBS generator rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_prbs_gen_rules_default_set(
    spica_prbs_gen_rules_t* gen_rules);

/**
 * This method is used to configure the PRBS generator.
 *
 * @{note,
 * You may want to squelch the transmitter before disabling the PRBS generator.
 * This will prevent the transmitter from emitting garbage to a downstream device}
 *
 * @param die         [I] - The physical ASIC die being accessed.
 * @param channel     [I] - The channel number, range 0..1.
 * @param intf        [I] - The interface, see e_spica_intf enum.
 * @param gen_rules   [I] - The generator rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_prbs_gen_config(
    uint32_t      die, 
    uint32_t      channel, 
    e_spica_intf  intf,
    spica_prbs_gen_rules_t* gen_rules);

/**
 * This method is called to inject errors into the TX datapath.
 *
 * @param die      [I] - The die of the ASIC being accessed.
 * @param channel  [I] - The channel to inject errors on
 * @param intf     [I] - The interface, see e_spica_intf enum.
 * @param enable   [I] - Turn the injector on/off
 * @param pattern  [I] - The pattern to inject
 * @param gap      [I] - Number of 64-bit words without errors to insert between words with errors
 * @param duration [I] - Number of 64-bit words to inject errors on
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure
 *
 * @since 0.1.0.0 
 */ 
inphi_status_t spica_prbs_gen_error_inject(
    uint32_t               die,
    uint32_t               channel,
    e_spica_intf           intf,
    bool                   enable,
    e_spica_prbs_err_inj_pat pattern,
    uint8_t                gap,
    uint8_t                duration);

/**
 * PRBS checker auto-polarity thresholds
 */
typedef enum
{
    /** More than 9 consecutive 64 bit words with one or more errors each */
    SPICA_PRBS_AUTO_POLARITY_9   = 0,
    /** More than 17 consecutive 64 bit words with one or more errors each */
    SPICA_PRBS_AUTO_POLARITY_17  = 1,
    /** More than 33  consecutive 64 bit words with one or more errors each */
    SPICA_PRBS_AUTO_POLARITY_33  = 2,
    /** More than 65 consecutive 64 bit words with one or more errors each */
    SPICA_PRBS_AUTO_POLARITY_65  = 3,

} e_spica_rx_prbs_auto_pol_thresh;

/**
 * Rx PRBS checker rules
 */
typedef struct
{
    /** Enables the PRBS checker. */
    bool en;

    /** Enables separate PRBS generation on MSB and LSB bits (PAM4 MSB and LSB). When 0, a single 
      * PRBS stream is generated. */
    e_spica_prbs_chk_mode prbs_mode;

    /** Inverts the receive bit pattern ahead of the PRBS checker if auto polarity is not enabled. */
    bool prbs_inv;

    /** Selects the PRBS polynomial for LSB bits (PAM4 symbol LSB) when dual PRBS mode is enabled. */
    e_spica_prbs_pat prbs_pattern_lsb;

    /** Selects the PRBS polynomial when not in dual PRBS mode or for MSB bits when in dual PRBS mode 
      * (PAM4 symbol MSB) */
    e_spica_prbs_pat prbs_pattern;

    /** NRZ mode flag, true = NRZ */
    bool nrz_mode;

    /** Enables the auto polarity detection feature of the PRBS checker. After a consecutive number of 
      * errors (programmable by auto_polarity_thresh) the polarity is inverted. */
    bool auto_polarity_en;

    /** When out of sync this controls the threshold for toggling the receive data polarity in auto 
     *  polarity mode. Every 64 bits (a "word") is checked for an error and if a certain number of 
     *  consecutive words contain errors then the polarity is toggled. In NRZ mode a word is 64 bits
     *  and in PAM4 mode a word is 32 symbols, i.e. 64 bits too. Caution: the alignment of serial bits
     *  to words is effectively random so, for example, two errors 10 bits apart may look like one
     *  word with two errors or two consecutive words with one error each.
     *      Value     Symbol                              Description
     *      2'd0  AUTO_POLARITY_9  More than 9 consecutive 64 bit words with one or more errors each
     *      2'd1  AUTO_POLARITY_17  More than 17 consecutive 64 bit words with one or more errors each
     *      2'd2  AUTO_POLARITY_33  More than 33 consecutive 64 bit words with one or more errors each
     *      2'd3  AUTO_POLARITY_65  More than 65 consecutive 64 bit words with one or more errors each */
    e_spica_rx_prbs_auto_pol_thresh auto_polarity_thresh;

    /** Selects the type of test pattern that is generated. */
    e_spica_prbs_pat_mode pattern_mode;

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

} spica_prbs_chk_rules_t;

/**
 * Host and Rx PRBS checker status
 */
typedef struct
{
    /** PRBS mode for individual MSB/LSB or combined bit streams */
    e_spica_prbs_chk_mode prbs_mode;

    /** PRBS lock status */
    bool prbs_lock;

    /** PRBS lock status (LSB) */
    bool prbs_lock_lsb;

    /** Fixed pattern sync */
    uint8_t prbs_fixed_pat_sync;

    /** Received PRBS pattern */
    e_spica_prbs_pat prbs_pattern;

    /** Received PRBS pattern (LSB) */
    e_spica_prbs_pat prbs_pattern_lsb;

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

} spica_prbs_chk_status_t;
 

/**
 * This method is used to set the PRBS checker rules to their default values.
 *
 * @param chk_rules [I/O] - The PRBS checker rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_prbs_chk_rules_default_set(
    spica_prbs_chk_rules_t* chk_rules);

/**
 * This method is used to configure the PRBS checker.
 *
 * @param die       [I] - The physical ASIC die being accessed.
 * @param channel   [I] - The channel number
 * @param intf      [I] - The interface, see e_spica_intf enum.
 * @param chk_rules [I] - The checker rules.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_prbs_chk_config(
    uint32_t      die, 
    uint32_t      channel, 
    e_spica_intf  intf,
    spica_prbs_chk_rules_t*  chk_rules);

/**
 * This method is used to determine whether the PRBS checker is already
 * enabled.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The physical channel number (0-1)
 * @param intf    [I] - The interface, see e_spica_intf enum.
 *
 * @return true if the checker is enabled, false if it's not
 *
 * @since 0.1.0.0 
 */
bool spica_prbs_chk_is_enabled(
    uint32_t      die, 
    uint32_t      channel,
    e_spica_intf  intf);

/**
 * This method is used to get the PRBS checker status.
 *
 * @param die        [I] - The physical ASIC die being accessed.
 * @param channel    [I] - The channel number (0-1)
 * @param intf       [I] - The interface, see e_spica_intf enum.
 * @param chk_status [O] - The checker status.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_prbs_chk_status(
    uint32_t      die, 
    uint32_t      channel, 
    e_spica_intf  intf,
    spica_prbs_chk_status_t*  chk_status);

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
 * @since 0.1.0.0 
 *
 * @requires
 * The API must be have floating point support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_FLOATING_POINT=1
 */
inphi_status_t spica_prbs_chk_ber(
    spica_prbs_chk_status_t *chk_status,
    double  *ber,
    double  *ber_lsb);
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

inphi_status_t spica_prbs_chk_status_print(
    uint32_t                 die, 
    uint32_t                 channel,
    e_spica_intf             intf,
    spica_prbs_chk_status_t* chk_status);

/**
 * This method is used to print the PRBS checker status.
 *
 * @param die           [I] - The physical ASIC die being accessed.
 * @param channel       [I] - The channel number, range 0..1.
 * @param intf          [I] - The interface, see e_spica_intf enum.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
inphi_status_t spica_prbs_chk_status_query_print(
    uint32_t     die, 
    uint32_t     channel,
    e_spica_intf intf);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/**
 * This is a debug method used to print the configuration rules for a bundle.
 *
 * @param die        [I] - The physical ASIC die being accessed.
 * @param bundle_idx [I] - The bundle number.
 * @param rules      [I] - The rules structure to print.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
void spica_dbg_print_rules_per_bundle(
    uint32_t       die,
    uint32_t       bundle_idx,
    spica_rules_t* rules);

/**
 * This is a debug method used to print the configuration rules.
 *
 * @param die   [I] - The physical ASIC die being accessed.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
void spica_dbg_print_rules(
    uint32_t       die, 
    spica_rules_t* rules);

/**
 * This is a debug method used to query then print the configuration rules.
 *
 * @param die        [I] - The physical ASIC die being accessed.
 * @param bundle_idx [I] - The bundle number.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
void spica_dbg_query_print_rules_per_bundle(
    uint32_t die, 
    uint32_t bundle_idx);

/**
 * This is a debug method used to query then print the configuration rules.
 *
 * @param die    [I] - The physical ASIC die being accessed.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
void spica_dbg_query_print_rules(
    uint32_t die);

/**
 * This is a debug method used to print the bundle rules.
 *
 * @param rules [I] - The bundle rules structure to print.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
void spica_bundle_dbg_print_rules(
    spica_bundle_rules_t* bundle_rules);

/**
 * This is a debug method used to query the bundle rules.
 *
 * @param rules [O] - The bundle rules structure to print.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
void spica_bundle_dbg_query_rules(
    spica_bundle_rules_t* bundle_rules);

/**
 * This is a debug method used to query then print the bundle rules.
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
void spica_bundle_dbg_query_print_rules(void);

/**
 * This is a debug method used to dump all the registers
 *
 * @since 0.1.0.0
 *
 * @requires
 * The API must be have diagnostic dump support. It must be
 * compiled with the following flag:
 * - INPHI_HAS_DIAGNOSTIC_DUMPS=1
 */
inphi_status_t spica_diags_register_dump(uint32_t die);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * This method is called to get the die associated to the bundle.
 *
 * @param bundle_idx [I] - The bundle number.
 *
 * @return The die associated to the bundle
 *
 * @since 0.1.0.0
 */
uint32_t spica_bundle_get_die_from_bundle(
    uint32_t bundle_idx);

/**
 * This method is called to see if the bundle is enabled.
 *
 * @param bundle_idx [I] - The bundle number.
 *
 * @return The die associated to the bundle
 *
 * @return True if enabled, False otherwise.
* 
 * @since 0.1.0.0
 */
bool spica_bundle_is_en(
    uint32_t bundle_idx);

/*
 * Send the rules to the die associated with the bundle and flip the UPDATE_ALL_RULES_REQ bit
 */
inphi_status_t spica_enter_operational_state_per_bundle(
    uint32_t       die,
    uint32_t       bundle_idx,
    spica_rules_t* rules);

/*
 * Send the rules to the die and flip the UPDATE_ALL_RULES_REQ bit
 */
inphi_status_t spica_enter_operational_state(
    uint32_t       die,
    spica_rules_t* rules);

/*
 * Reset the die (associated to the bundle) to have it ready for any user config
 */
inphi_status_t spica_init_per_bundle(
    uint32_t       bundle_idx,
    spica_rules_t* rules);

/*
 * Reset the device to have it ready for any user config
 */
inphi_status_t spica_init(
    uint32_t       die,
    spica_rules_t* rules);

/*
 * Query the TX FIR configuration.
 */
inphi_status_t spica_tx_fir_query(
    uint32_t          die,
    uint32_t          channel,
    e_spica_intf      intf,
    spica_tx_rules_t* tx_rules);

/*
 * Update the TX FIR configuration of the channel
 */
inphi_status_t spica_tx_fir_set(
    uint32_t          die,
    uint32_t          channel,
    e_spica_intf      intf,
    spica_tx_rules_t* tx_rules);

// Squelch the transmit output for the specified channel
inphi_status_t spica_tx_squelch(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,
    bool         squelch);

/**
 * Provides full-manual control of the Tx LUT and COEFF register programming.
 *
 * Use this function when you have the FW LUT mode set to SPICA_LUT_BYPASS in your tx_rules.
 * When doing so the FW will leave the Tx DSP registers alone, these must be setup via this function.
 *
 * @{note, Only applicable when the tx_rules.lut_mode is BYPASS!}
 *
 * Unfortunately this function cannot be called until the Tx voltage regulators are powered on. This means this
 * function must be called after spica_enter_operational_state. It will poll a status register to wait for the
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
 * @param intf       [I] - The TX interface to configure 
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
 * @since 0.1.0.0
 *
 * @example
 * //configure
 * status |= spica_init(die, rules);
 * status |= spica_enter_operational_state(die, rules);
 * //configure the Txs
 * SPICA_FOR_CHANNEL_IN_CHANNELS(SPICA_PACKAGE_FROM_DIE(die), SPICA_INTF_OTX) {
 *     //only configure bypass channels
 *     if(rules.otx[channel].lut_mode != SPICA_LUT_BYPASS) continue;
 *     
 *     status |= spica_tx_man_config(die, channel, SPICA_INTF_OTX, SPICA_TX_HW_MODE_TAP4,
 *                 is_lut_unsigned, true, lut, coef);
 *     //turn off squelch lock now that the Tx has been configured
 *     status |= spica_tx_squelch_lock(die, channel, SPICA_INTF_OTX, false);
 *     //now check the FW lock; if it was locked prior to us configuring the Tx we need to unsquelch manually
 *     //since the FW was not in control of the squelch
 *     if(SPICA_OTX_FW_STATUS__LOCKED__READ(die, channel)) {
 *         status |= spica_tx_squelch(die, channel, SPICA_INTF_OTX, false);
 *     } 
 * }
 */
inphi_status_t spica_tx_man_config(
    uint32_t            die,
    uint32_t            channel,
    e_spica_intf        intf,
    e_spica_lut_mode    lut_mode,
    bool                is_lut_unsigned,
    bool                toggle_squelch,
    int8_t              lut[256],
    int16_t             coef[28]);

/**
 * @h2 Device Configuration
 * =======================================================
 *
 * @brief
 * This method sets up the default rules for all the 
 * enabled bundles to the desired operating
 * mode to simplify the implementation for the user.
 *
 * @{note,This method initializes the rules data-structure, it does
 * not write to any registers.}
 *
 * @param die           [I] - The die of the ASIC being configured by this
 *                              instance of the rules structure.
 * @param bundle_idx    [I] - The bundle number.
 * @param op_mode       [I] - The main operational mode of the ASIC.
 * @param protocol_mode [I] - The desired protocol modes which will describe the rate,
 *                              number of channels on each interface, and indirectly the signalling.
 * @param rules         [O] - The default rules for the application.
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_rules_default_set_per_bundle(
    uint32_t                 die,
    uint32_t                 bundle_idx,
    e_spica_operational_mode op_mode,
    e_spica_protocol_mode    protocol_mode,
    spica_rules_t*           rules);

/** This method sets up the default rules for all the enabled bundles 
 * to the desired operating mode to simplify the implementation for the user.
 *
 * @{note,This method initializes the rules data-structure, it does
 * not write to any registers.}
 *
 * @param die           [I] - The die of the ASIC being configured by this
 *                              instance of the rules structure.
 * @param op_mode       [I] - The main operational mode of the ASIC.
 * @param protocol_mode [I] - The desired protocol modes which will describe the rate,
 *                              number of channels on each interface, and indirectly the signalling.
 * @param rules         [O] - The default rules for the application.
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_rules_default_set(
    uint32_t                 die,
    e_spica_operational_mode op_mode,
    e_spica_protocol_mode    protocol_mode,
    spica_rules_t*           rules);

/**
 * This method is used to setup the default Tx rules
 *
 * @param die              [I] - The die of the ASIC.
 * @param intf             [I] - The interface.
 * @param driver_type_ovrd [I] - The driver type override, see enum e_spica_driver_type.
 * @param tx_rules         [O] - The default Tx rules for the application.
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_tx_rules_default_set(
    uint32_t            die,
    e_spica_intf        intf,
    e_spica_driver_type driver_type_ovrd,
    spica_tx_rules_t*   tx_rules);

/**
 * This method is used to configure the bundles
 *
 * @param bundle_rules  [I/O] - Pointer to the bundle rules structure
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_bundle_cfg(
    spica_bundle_rules_t* bundle_rules);

/**
 * This method is used to setup the bundles rukles to their default
 * configureations based on the package type.
 *
 * @param die          [I]   - The die of the ASIC.
 * @param bundle_rules [I/O] - Pointer to the bundle rules structure
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @since 0.1.0.0
 */
inphi_status_t spica_bundle_default_set(
    uint32_t die, 
    spica_bundle_rules_t* bundle_rules);

/**
 * This method is used Update the top, rx and tx rules structure.
 *
 * @param die        [I]   - The die of the ASIC.
 * @param bundle_idx [I]   - The bundle number.
 * @param rules      [I/O] - Pointer to the rules structure
 *
 * @return INPHI_OK on success, INPHI_ERROR otherwise
 *
 * @since 0.14.0.0
 */
inphi_status_t spica_cp_overlays_to_rules(
    uint32_t       die,
    uint32_t       bundle_idx,
    spica_rules_t* rules);

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
* @param channel          [I] - The channel.
* @param intf             [I] - One or more interfaces to check. Note the intf
*                               identifiers can be OR'd together.
* @param timeout_in_usecs [I] - The amount of time to wait for all
*                               channels to be ready in micro-seconds.
*
* @return INPHI_OK on success, INPHI_ERROR on failure.
*
* @since 0.1
*/
inphi_status_t spica_channel_wait_for_link_ready(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,
    uint32_t     timeout_in_usecs);

/**
* This method is called to determine whether particular interfaces or all
* interfaces of a channel link is up.
*
* @param die      [I] - The ASIC die being accessed.
* @param channel  [I] - The channel.
* @param intf     [I] - One or more interfaces to check. Note the intf
*                       identifiers can be OR'd together.
*
* @return true if the link is up, false if the link is down.
*
*/
bool spica_channel_is_link_ready(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf);

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

    // MRX and SRX combined
    /** Signal detect status
     * - true if there is a signal present on the Rx
     * - false otherwise.
     *
     * The FW will not attempt to acquire lock unless this is true.
     */
    bool hrx_sdt[SPICA_MAX_SRX_CHANNELS+1];

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
    bool hrx_vco_lock[SPICA_MAX_SRX_CHANNELS+1];

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
    bool hrx_cdr_lock[SPICA_MAX_SRX_CHANNELS+1];

    /** DSP status
     * - true if the DSP is locked and running adaptation
     * - false if the DSP is attempting to lock or is unable to maintain lock
     *
     * Like the ORX, the MRX has a HW FSM DSP that runs continuously in the background. This will be set
     * when the HW is locked to the incoming signal and is running the continuous adaptation FSMs.
     * Only use this for debugging, see hrx_fw_lock below.
     */
    bool hrx_dsp_ready[SPICA_MAX_SRX_CHANNELS+1];

    /** FW has determined that the channel is locked and ready to pass traffic.
     * - true if FW is in data/mission mode.
     * - false otherwise
     *
     * The FW will only set this when all the above status signals are true (SDT, VCO lock, CDR lock) and when
     * data/mission mode adaptation has stabilized. This status will be valid in all modes and configurations,
     * including refless where the VCO/CDR lock aren't used.
     */
    bool hrx_fw_lock[SPICA_MAX_SRX_CHANNELS+1];

    /** PLL lock
     *
     * This is similar to the mrx_vco_lock, however unlike the Tx PLLs the clock is either based off a refclk
     * (in local clock mode) or off of the MRX recovered clock (in refless clock mode). This is the lower
     * level HW lock indicator and should be used for debugging only.
     *
     */
    bool hrx_pll_lock[SPICA_MAX_SRX_CHANNELS+1];

    /** PLL FSM state
     *
     * This is the current state of the SMRX PLL FSM.
     *
     */
    uint8_t hrx_pll_fsm_state[SPICA_MAX_SRX_CHANNELS+1];

    /** FSM state
     *
     * This is current state of the MRX or SRX FSM state machine. This is a lower
     * level HW indicator and should be used for debugging only.
     *
     */
    uint8_t hrx_fsm_state[SPICA_MAX_SRX_CHANNELS+1];

    /** Number of times this channel has had to re-acquire lock.
     *
     * This is only incremented when FW has achieved lock but was interrupted for some reason (HW/FW faults,
     * loss of lock, loss of SDT, etc.). This will not continue to increment unless there is a signal present
     * on the interface.
     */
    uint8_t hrx_reset_cnt[SPICA_MAX_SRX_CHANNELS+1];

    // MTX and STX combined
    /** FW has determined that the channel is locked and ready to pass traffic.
     * - true if FW is in data/mission mode.
     * - false otherwise
     *
     * The FW will only set this when the Tx DSP is ready and when the upstream traffic source (ORX, MRX,
     * PRBS generator) are ready as well.
     */
    bool htx_fw_lock[SPICA_MAX_STX_CHANNELS+1];
    /** PLL lock
     *
     * This is similar to the mrx_vco_lock; the upstream traffic source will send a clock to the Tx which the
     * PLL will lock to. This is the lower level HW lock indicator and should be used for debugging only.
     *
     * Technically there is one PLL per channel pair, so internal instances 0 & 1 will share a PLL. This
     * only matters for packages with all instances brought out to package channels, like the gearbox part.
     * The lock status is replicated for convenience to fill out the array.
     */
    bool htx_pll_lock[SPICA_MAX_STX_CHANNELS+1];

    /** PLL FSM state
     *
     * This is the current state of the SMTX PLL FSM.
     *
     */
    uint8_t htx_pll_fsm_state[SPICA_MAX_STX_CHANNELS+1];

    /** FSM state
     *
     * This is current state of the MTX or STX FSM state machine. This is a lower
     * level HW indicator and should be used for debugging only.
     *
     */
    uint8_t htx_fsm_state[SPICA_MAX_STX_CHANNELS+1];

    /** Number of times this channel has had to re-acquire lock.
     *
     * This is only incremented when FW has achieved lock but was interrupted for some reason (HW/FW faults,
     * loss of lock, loss of SDT, etc.). This will not continue to increment unless there is a signal present
     * on the interface.
     */
    uint8_t  htx_reset_cnt[SPICA_MAX_STX_CHANNELS+1];

    // OTX
    /** FW has determined that the channel is locked and ready to pass traffic.
     * - true if FW is in data/mission mode.
     * - false otherwise
     *
     * The FW will only set this when the Tx DSP is ready and when the upstream traffic source (ORX, MRX,
     * PRBS generator) are ready as well.
     */
    bool otx_fw_lock[SPICA_MAX_OTX_CHANNELS+1];

    /** PLL lock
     *
     * This is similar to the mrx_vco_lock; the upstream traffic source will send a clock to the Tx which the
     * PLL will lock to. This is the lower level HW lock indicator and should be used for debugging only.
     *
     */
    bool otx_pll_lock[SPICA_MAX_OTX_CHANNELS+1];

    /** PLL FSM state
     *
     * This is the current state of the OTX PLL FSM.
     *
     */
    uint8_t otx_pll_fsm_state[SPICA_MAX_OTX_CHANNELS+1];

    /** FSM state
     *
     * This is current state of the OTX FSM state machine. This is a lower
     * level HW indicator and should be used for debugging only.
     *
     */
    uint8_t otx_fsm_state[SPICA_MAX_OTX_CHANNELS+1];

    /** Number of times this channel has had to re-acquire lock.
     *
     * This is only incremented when FW has achieved lock but was interrupted for some reason (HW/FW faults,
     * loss of lock, loss of SDT, etc.). This will not continue to increment unless there is a signal present
     * on the interface.
     */
    uint8_t  otx_reset_cnt[SPICA_MAX_OTX_CHANNELS+1];

    // ORX
    /** Signal detect status
     * - true if there is a signal present on the Rx
     * - false otherwise.
     *
     * The FW will not attempt to acquire lock unless this is true.
     */
    bool orx_sdt[SPICA_MAX_ORX_CHANNELS+1];

    /** DSP status
     * - true if the DSP is locked and running adaptation
     * - false if the DSP is attempting to lock or is unable to maintain lock
     *
     * Unlike the MRX, the ORX has a HW FSM DSP that runs continuously in the background. This will be set
     * when the HW is locked to the incoming signal and is running the continuous adaptation FSMs.
     * Only use this for debugging, see orx_fw_lock below.
     */
    bool orx_dsp_ready[SPICA_MAX_ORX_CHANNELS+1];

    /** FW has determined that the channel is locked and ready to pass traffic.
     * - true if FW is in data/mission mode.
     * - false otherwise
     *
     * The FW will only set this when all the above status signals are true (SDT, DSP ready) and when
     * data/mission mode adaptation has stabilized. This status will be valid in all modes and configurations,
     * including refless where the ORX relies on a clock from the MRX.
     */
    bool orx_fw_lock[SPICA_MAX_ORX_CHANNELS+1];

    /** PLL lock
     *
     * This is similar to the mrx_vco_lock, however unlike the Tx PLLs the clock is either based off a refclk
     * (in local clock mode) or off of the MRX recovered clock (in refless clock mode). This is the lower
     * level HW lock indicator and should be used for debugging only.
     *
     */
    bool orx_pll_lock[SPICA_MAX_ORX_CHANNELS+1];

    /** PLL FSM state
     *
     * This is the current state of the ORX PLL FSM.
     *
     */
    uint8_t orx_pll_fsm_state[SPICA_MAX_ORX_CHANNELS+1];

    /** FSM state
     *
     * This is current state of the ORX FSM state machine. This is a lower
     * level HW indicator and should be used for debugging only.
     *
     */
    uint8_t orx_fsm_state[SPICA_MAX_ORX_CHANNELS+1];

    /** Number of times this channel has had to re-acquire lock.
     *
     * This is only incremented when FW has achieved lock but was interrupted for some reason (HW/FW faults,
     * loss of lock, loss of SDT, etc.). This will not continue to increment unless there is a signal present
     * on the interface.
     */
    uint8_t  orx_reset_cnt[SPICA_MAX_ORX_CHANNELS+1];

} spica_link_status_t;

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
inphi_status_t spica_link_status_query(
    uint32_t die,
    spica_link_status_t* link_status);

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
inphi_status_t spica_link_status_print(
    uint32_t die,
    spica_link_status_t* link_status);

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
inphi_status_t spica_link_status_query_print(
    uint32_t die);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * This method may be called to return the die/instance of
 * the selected package channel. This may be called from the line_status_method
 * or the GUIs dashboard tab.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param channel [I] - The channel.
 * @param intf    [I] - The interface.
 *
 * @return MSB16=die and LSB16=instance
 *
 * @since 0.9.0.0
 *
 */
uint32_t spica_get_die_inst_from_pkg_ch(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf);

/**
 * This method may be called to check if the package contains the PSR IP 
 *
 * @param die  [I] - The ASIC die being accessed.
 *
 * @since 0.13.0.0
 *
 */
bool spica_package_has_psr(
    uint32_t die);

/**
 * This method may be called to check if the package contains the PMR IP 
 *
 * @param die  [I] - The ASIC die being accessed.
 *
 * @since 0.13.0.0
 *
 */
bool spica_package_has_pmr(
    uint32_t die);

/**
 * This method may be called to get the Driver Type of the package
 *
 * @param die  [I] - The ASIC die being accessed.
 *
 * @return e_spica_driver_type
* 
 * @since 1.2.0.0
 *
 */
e_spica_driver_type spica_package_get_driver_type(
    uint32_t die);

/**
 * @h2 Host RX
 * =======================================================
 *
 * @h3 SRX Pulse Response
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
inphi_status_t spica_srx_pulse_resp_query(
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
inphi_status_t spica_srx_pulse_resp_query_dump_range(
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
inphi_status_t spica_srx_pulse_resp_query_dump(
    uint32_t die);

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS == 1)
// #endif // defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)

/**
 * This method should be used to enable/disable a clock group (bundle of traffic) on the chip independently of other clock groups (if any exist).
 * Clock groups are groups of connected blocks, starting at a data/clock source (Rx) and ending in a sink (Tx).
 * Clock groups are dynamically created based on the operating mode of the chip, the Xbar config, etc.
 *
 * For example, if the part is configured for: SPICA_MODE_MISSION_MODE, SPICA_MODE_400G_8P_26p6_TO_4P_53p1
 * and the clk_xbar is left at default values, then the device will be split into 8 independent streams (4 in egress, 4 in ingress):
 *
 * @{pre,
 * +---------+-------------------------------+
 * |         |     Egress Clock Groups       |
 * | INTF    |   1   |   2   |   3   |   4   |
 * +---------+-------+-------+-------+-------+
 * |SRX      |  1,2  |  3,4  |  5,6  |  7,8  |
 * |OTX_PLL  |   1   |   2   |   3   |   4   |
 * |OTX      |   1   |   2   |   3   |   4   |
 * +---------+-------+-------+-------+-------+
 * +---------+-------------------------------+
 * |         |     Ingress Clock Groups      |
 * | INTF    |   5   |   6   |   7   |   8   |
 * +---------+-------+-------+-------+-------+
 * |ORX      |   1   |   2   |   3   |   4   |
 * |SMTX_PLL |   1   |   2   |   3   |   4   |
 * |STX      |  1,2  |  3,4  |  5,6  |  7,8  |
 * +---------+-------+-------+-------+-------+
 * }
 *
 * Setting enable/disable for any intf/channel pair above will disable/enable ALL other intf/channel pairs 
 * in the same clock group. ie. Calling spica_clock_group_enable(die, 2, SPICA_INTF_STX, false) will disable ALL
 * intf/channel pairs in clock group 5.
 *
 * If you override the clk_xbar so that all Tx channels point to a common Rx clk, then all
 * channels in each egress/ingress direction become part of the same clock groups (1 for egress, 1 for ingress)
 *
 * @param die       [I] - The ASIC die being accessed.
 * @param channel   [I] - Channel 
 * @param intf      [I] - Interface
 * @param enable    [I] - True to enable the clock group, false otherwise
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.0.0.0
 */
inphi_status_t spica_clock_group_enable(
    uint32_t die, 
    uint32_t channel, 
    e_spica_intf intf, 
    bool enable);

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
 * @param intf    [I] - The TX interface to squelch (SPICA_INTF_OTX, SPICA_INTF_MTX, or SPICA_INTF_STX)
 * @param squelch_lock  [I] - true to enable the transmit squelch lock, false to disable the
 *                      transmit squelch lock.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.0.0.0
 */
inphi_status_t spica_tx_squelch_lock(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,
    bool         squelch_lock);

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
 * @since 1.0.0.0
 */
inphi_status_t spica_tx_invert_toggle(
    uint32_t          die,
    uint32_t          channel,
    e_spica_intf      intf);

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
 * @since 1.0.0.0
 */
inphi_status_t spica_rx_invert_toggle(
    uint32_t          die,
    uint32_t          channel,
    e_spica_intf      intf);

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
inphi_status_t spica_temperature_query(
    uint32_t die,
    int16_t* temperature);

#if !defined(INPHI_REMOVE_MESSAGING)

/**
 * @h2 MCU Messaging
 * =======================================================
 * The following methods must are used to send/receive
 * messages to/from the MCU.
 */

/* The number of RX mailbox entries in the mailbox - 8 4 byte entries */
#define SPICA_MCU_RXMBOX_MAX_ENTRIES 8
#define SPICA_MCU_MBOX_ITER_DELAY    5    /* mailbox iteration delay 5 milliseconds */
#define SPICA_MCU_MBOX_MAX_TIMEOUT   8000 /* max mailbox timeout of 8 sec in case f/w is busy doing long operation */

/**
 * The number of bytes allocated for the transfer buffer used
 * to manage reading and writing from the external EEPROM. When
 * running against the DV environment the buffer must be small
 * to avoid timeouts accessing the EEPROM.
 */
#define SPICA_MCU_MSG_TRANSFER_BUFFER_SIZE 256

/* Buffer types managed by the host */
#define SPICA_MCU_BUFFER_TYPE_TRANSFER  0
#define SPICA_MCU_BUFFER_TYPE_DEBUG_LOG 1

#define SPICA_FEC_STATS_MAX_TIME 14000

/**
 * This enumeration defines the list of messages that the MCU is 
 * capable of processing 
 * NOTE: This enumeratod type must match the one in the 
 * FW file inc/messaging.h.
 */
typedef enum
{
    /** A memory write request */
    SPICA_MCU_MSG_WRITE_MEMORY_REQUEST         = 0,
    /** A memory write response */
    SPICA_MCU_MSG_WRITE_MEMORY_RESPONSE        = 1,
    /** A memory read request */
    SPICA_MCU_MSG_READ_MEMORY_REQUEST          = 2,
    /** A memory write response */
    SPICA_MCU_MSG_READ_MEMORY_RESPONSE         = 3,
    /** AN EEPROM write request */
    SPICA_MCU_MSG_WRITE_EEPROM_REQUEST         = 4,
    /** An EEPROM write response */
    SPICA_MCU_MSG_WRITE_EEPROM_RESPONSE        = 5,
    /** An EEPROM read request */
    SPICA_MCU_MSG_READ_EEPROM_REQUEST          = 6,
    /** An EEPROM read response */
    SPICA_MCU_MSG_READ_EEPROM_RESPONSE         = 7,
    /** Get the address of a buffer from the MCU */
    SPICA_MCU_MSG_GET_BUFFER_REQUEST           = 8,
    /** The response to the buffer request */
    SPICA_MCU_MSG_GET_BUFFER_RESPONSE          = 9,
    /** Verify the contents of the EEPROM */
    SPICA_MCU_MSG_VERIFY_EEPROM_REQUEST        = 10,
    /** The response to the verify request */
    SPICA_MCU_MSG_VERIFY_EEPROM_RESPONSE       = 11,
    /** Request access to protected memory */
    SPICA_MCU_MSG_GRANT_MEMORY_REQUEST         = 13,
    /** The response to the grant access */
    SPICA_MCU_MSG_GRANT_MEMORY_RESPONSE        = 14,
    /** Release the fetched buffer */
    SPICA_MCU_MSG_RELEASE_BUFFER_REQUEST       = 15,
    /** The response to the release request */
    SPICA_MCU_MSG_RELEASE_BUFFER_RESPONSE      = 16,
    /** Set the request of a firmware parameter*/
    SPICA_MCU_MSG_PARAM_SET_REQUEST            = 17,
    /** Set the response to the firmware paramater */
    SPICA_MCU_MSG_PARAM_SET_RESPONSE           = 18,
    /** Get the request of a firmware parameter*/
    SPICA_MCU_MSG_PARAM_GET_REQUEST            = 19,
    /** Get the response to the firmware paramater */
    SPICA_MCU_MSG_PARAM_GET_RESPONSE           = 20,
    /** Error response from the MCU */
    SPICA_MCU_MSG_ERROR_RESPONSE               = 21,

    SPICA_MCU_MSG_SET_TX_REQUEST               = 26,
    SPICA_MCU_MSG_SET_TX_RESPONSE              = 27,

    SPICA_MCU_MSG_SPICA_INIT_REQUEST             = 30,
    SPICA_MCU_MSG_SPICA_INIT_RESPONSE            = 31,
    SPICA_MCU_MSG_SPICA_ENTER_OPERATIONAL_STATE_REQUEST  = 32,
    SPICA_MCU_MSG_SPICA_ENTER_OPERATIONAL_STATE_RESPONSE = 33,

    SPICA_MCU_MSG_INFO_REQUEST = 34,
    SPICA_MCU_MSG_INFO_RESPONSE = 35,

    /** 7-Tap coefficient request */
    SPICA_MCU_MSG_SET_7TAP_COEFFS_REQUEST = 38,
    /** 7-Tap coefficient response */
    SPICA_MCU_MSG_SET_7TAP_COEFFS_RESPONSE = 39,

    /** Get the histograms */
    SPICA_MCU_MSG_HIST_REQUEST = 40,
    SPICA_MCU_MSG_HIST_RESPONSE = 41,

    /** Get the SRX pulse resp */
    SPICA_MCU_MSG_SRX_PULSE_REQUEST = 42,
    SPICA_MCU_MSG_SRX_PULSE_RESPONSE = 43,

    /** Tx/Rx Inversion request */
    SPICA_MCU_MSG_SET_LANE_INV_REQUEST = 46,
    SPICA_MCU_MSG_SET_LANE_INV_RESPONSE = 47,

    /** Enable/Disable bundle */
    SPICA_MCU_MSG_SET_BUNDLE_ENABLE_REQUEST  = 48,
    SPICA_MCU_MSG_SET_BUNDLE_ENABLE_RESPONSE = 49,

    SPICA_MCU_MSG_FEC_STATS_CFG = 50, //no response
    SPICA_MCU_MSG_FEC_STATS_GET_AND_CLEAR = 51,
    SPICA_MCU_MSG_FEC_STATS_GET = 52,
    SPICA_MCU_MSG_FEC_STATS_CLEAR = 53, //no response
    SPICA_MCU_MSG_FEC_STATS_RET = 54, //the returned stats

    SPICA_MCU_MSG_FEAT_EN = 56, //no response

    SPICA_MCU_MSG_END //must be last

}e_spica_mcu_msg_type;

#pragma pack(push,4)

//Message Header
typedef union {
    struct
    {
        uint32_t msg_len  :16;
        uint32_t msg_type : 8;
        uint32_t msg_id   : 8;
    }get;
    uint32_t raw;
}msg_hdr_t;

//DSP Info Payload
typedef union {
    struct
    {
        uint32_t info_id : 8;
        uint32_t channel : 8;
        uint32_t ip_block: 8;
        uint32_t opt_arg : 8; //optional arg such as errgen_id
    }get;
    uint32_t raw;
}fw_info_payload_t;

//DSP Info Message
typedef struct {
    msg_hdr_t         hdr;
    fw_info_payload_t payload;
}fw_info_msg_t;

#pragma pack(pop)

inphi_status_t spica_mcu_reset_into_application(
    uint32_t die, 
    bool wait_till_started);

uint8_t spica_mcu_msg_id(void);

uint32_t spica_mcu_msg_type(
    uint32_t msg_type,
    uint8_t  msg_id,
    uint8_t  msg_len);

inphi_status_t spica_msg_send(
    uint32_t        die,
    const uint32_t* header,
    uint16_t        header_size,
    const uint32_t* payload,
    uint16_t        payload_size);

inphi_status_t spica_msg_recv(
    uint32_t   die,
    uint32_t*  payload_buffer,
    uint16_t   max_payload,
    msg_hdr_t* resp_hdr,
    uint32_t*  resp_rc,
    uint32_t   timeout);

e_spica_fw_mode spica_mcu_decode_bootver(
    uint32_t bootver);

inphi_status_t spica_mcu_fw_mode_query(
    uint32_t       die,
    e_spica_fw_mode* mode);

/**
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
 * interval_time can only be non-zero when your FEC output mode is set to SPICA_FEC_BYPASS. If you use
 * SPICA_FEC_REGEN (like in SPICA_MODE_100G_PCS4_TO_KP1) then a non-zero interval_time may cause the FEC traffic
 * to drop. A SPICA_FEC_REGEN mode *cannot* use low-power FEC stats monitoring.
 *
 * @text
 * Here's an example of a zero interval_time (aka high power mode), where the FEC is left on all the time.
 * The benefit of this approach is no FEC error events will be lost, as each snapshot & accumulate is atomic.
 * In this mode the FW can be left accumulating for as long as needed before a call to spica_fec_stats_poller_request
 * (with clear_on_read=true) or spica_fec_stats_poller_clear is needed.
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
     * Note your main configuration rules (ie the rules used for spica_enter_operational_state) need
     * to have the FEC block enabled in order for stats collection to work. You do not need to be
     * in SPICA_FEC_REGEN mode; SPICA_FEC_BYPASS will work for stats monitoring. See spica_fec_rules_t.
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
     * More than 0 means the FEC is turned off (if you are in SPICA_FEC_BYPASS mode) while interval_time is running.
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
} spica_fec_stats_poller_rules_t;

/**
 * Configure the internal FW FEC stats polling.
 *
 * This can be done any time after spica_init. If a previous call has enabled the FEC stats polling in the FW
 * a call to this method will simply change the timer durations and trigger a new polling cycle, it will not
 * clear the already accumulated FEC stats saved by the FW.
 *
 * @{note, As soon as the FW FEC stats polling is enabled, you MUST NOT use the
 * snapshot_all or snapshot_intf methods on the FEC intf being polled by the
 * FW. Otherwise the FW may miss some FEC stats.}
 *
 * @param die         [I] - The ASIC die being accessed.
 * @param intf        [I] - The interface being accessed, must be SPICA_INTF_EG_FEC or SPICA_INTF_IG_FEC.
 * @param stats_rules [I] - The rules being used to configure the poller.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 */
inphi_status_t spica_fec_stats_poller_cfg(
    uint32_t   die,
    e_spica_intf intf,
    const spica_fec_stats_poller_rules_t *stats_rules
    );

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
 * There is an example conversion function (float_2_cmis_f16) in spica_api.c included in this API package, as well
 * as the inverse function (cmis_f16_to_float) used for spica_fec_stats_poller_calc_ber.
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
} spica_fec_stats_cp_block_t;

/** Number of read blocks in spica_fec_stats_cp_block_t */
#define SPICA_FEC_STATS_CP_BLOCKS 8

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
 * NaN (see spica_fec_stats_cp_block_t).
 *
 * @{note, This request call must be followed by a call to fec_stats_poller_get. A call to any other API method
 * which uses the messaging path will cause the FEC stats copy buffer to be cleared, losing the FEC stats requested
 * by this method.}
 *
 * @param die           [I] - The ASIC die being accessed.
 * @param intf          [I] - The interface being accessed, must be SPICA_INTF_EG_FEC or SPICA_INTF_IG_FEC.
 * @param clear_on_read [I] - True to clear all stats counters in the FW after reading. Atomic.
 * @param stats        [IO] - The stats structure that will later be used by spica_fec_stats_poller_get
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 * 
 */
inphi_status_t spica_fec_stats_poller_request(
    uint32_t   die,
    e_spica_intf intf,
    bool clear_on_read,
    spica_fec_stats_cp_block_t *stats
    );

/** Return type for spica_fec_stats_poller_get.
 * Communicates whether we're waiting for the FW to perform some operation or not.
 */
typedef enum {
    /** Returned successfully, not waiting for the FW, same as INPHI_OK */
    SPICA_POLLER_OK = 0,
    /** Timed out waiting for the FW to complete the request. Keep calling the same method */
    SPICA_POLLER_WAITING = 1,
    /** API hit an error, you must re-request the stats from the FW. Same as INPHI_ERROR.
     * Note the documentation has a bug, this should be negative 1 (-1). */
    SPICA_POLLER_ERROR = -1,
} e_spica_poller_status;

/**
 * Read FW stats copy buffer and populate the provided stats structure. This can be done all at once or in
 * blocks of somewhat-related stats.
 * Blocks are defined/mentioned in the spica_fec_stats_cp_block_t definition, set each bit of blocks_to_read
 * that you wish to copy from the FW. Ex set bit n (1<<n) to populate block n.
 *
 * You must call spica_fec_stats_poller_request prior to this function. This function will not block waiting
 * for the FW to populate the copy buffer, instead it will return SPICA_POLLER_WAITING while waiting for the
 * FW. Simply call this method again (with the same arguments) until the return status is SPICA_POLLER_OK.
 *
 * The stats structure used for spica_fec_stats_poller_request MUST be the same structure used for this call!
 *
 * If this method returns SPICA_POLLER_ERROR, then the stats are either invalid (poll_count = 0) or an API
 * method was unable to copy the data from the copy buffer (register read error, etc.) In either case another
 * call MUST be made to spica_fec_stats_poller_request prior to calling this method again.
 *
 * @param die            [I] - The ASIC die being accessed.
 * @param intf           [I] - The interface being accessed, must be SPICA_INTF_EG_FEC or SPICA_INTF_IG_FEC.
 * @param blocks_to_read [I] - Bitmask of each block to read. ie. set Bit 0 = 1 to read the first block.
 * @param stats          [O] - The stats structure copied from the FW.
 *
 * @return SPICA_POLLER_OK (success), SPICA_POLLER_WAITING (waiting on FW), SPICA_POLLER_ERROR (error/failure).
 *
 * @since 1.2.0.0
 *
 * @requires
 * stdlib for offsetof
 *
 * @example

        // Note that this is just an example of how to design a non-blocking FSM. If you're using 25MHz MDIO
        // or 1MHz I2C then the IO won't be a bottleneck and a complicated FSM is not required.

        // make sure the same stats data is used for BOTH the request and the get
        static spica_fec_stats_cp_block_t stats;
        // incrementally grab each block
        static int block = 0;
        // track our VDM state
        static e_vdm_state state = VDM_START;

        // ... whatever other stuff ...

        switch(state) {
            case VDM_START:
                INPHI_NOTE("VDM request\n");
                // request stats from the FW, clearing right afterwards
                status |= spica_fec_stats_poller_request(die, intf, fec, true, &stats);
                // non-blocking, exit right away
                state += 1;
                // reset our block too
                block = 0;
                break;

            case VDM_POLL:
                // see if the FW has copied the stats, don't copy the buffer yet
                poll_status = spica_fec_stats_poller_get(die, intf, fec, 0, &stats);
                if(poll_status == SPICA_POLLER_ERROR) {
                    //some error, go back and try again
                    state = VDM_START;
                }
                else if(poll_status == SPICA_POLLER_WAITING) {
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
                poll_status = spica_fec_stats_poller_get(die, intf, fec, 1<<block, &stats);
                if(poll_status == SPICA_POLLER_ERROR) {
                    //some error, go back and try again
                    state = VDM_START;
                }
                else if(poll_status == SPICA_POLLER_WAITING) {
                    //stay here, FW isn't ready yet
                    // (technically this can't happen as of 1.10)
                }
                else {
                    //block was grabbed, proceed to the next one
                    block += 1;
                    if(block >= SPICA_FEC_STATS_CP_BLOCKS) {
                        //done all the blocks, reset
                        block = 0;
                        state += 1;
                    }
                }
                break;

            case VDM_POST:
                // Normally you will want to populate the CMIS register space with the captured VDM
                // stats. In this example we're just going to print to the console log.
                // NOTE: There is no need to call spica_fec_stats_poller_calc_ber in module FW; this is for debug only!
                {
                    spica_fec_stats_poller_t avg_rates;
                    spica_fec_stats_poller_t min_rates;
                    spica_fec_stats_poller_t max_rates;
                    spica_fec_stats_poller_t cur_rates;
                    status |= spica_fec_stats_poller_calc_ber(die, intf, fec, &stats, &avg_rates, &min_rates, &max_rates, &cur_rates);

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
e_spica_poller_status spica_fec_stats_poller_get(
    uint32_t   die,
    e_spica_intf intf,
    uint32_t blocks_to_read,
    spica_fec_stats_cp_block_t *stats
    );

/**
 * Clear the internal FW FEC stats counters. Clearing the FW stats counters does not
 * affect the currently accumulating HW stats counters; these will be read the next time the accumulation_time
 * expires.
 *
 * The counters used by the FW are large enough to accumulate FEC stats for many days (~1yr), the interval they
 * are polled/cleared should not matter.
 *
 * @param die  [I] - The ASIC die being accessed.
 * @param intf [I] - The interface being accessed, must be SPICA_INTF_EG_FEC or SPICA_INTF_IG_FEC.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 1.2.0.0
 *
 */
inphi_status_t spica_fec_stats_poller_clear(
    uint32_t   die,
    e_spica_intf intf
    );

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
#if defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)

#if !defined(INPHI_HAS_SPICA_RATE_T)
//fallback in case someone doesn't update their inphi_config.h
typedef double spica_rate_t;
#endif

/**
 * Structure to hold the accum/min/max rates.
 *
 * @{pre,10 bits / symbol
 * 544 symbols / cw (KP)
 * 528 symbols / cw (KR)}
 *
 * @{note, Use the typedef spica_rate_t in inphi_config.h to change the type from double (default) to another type (like float)}
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
    spica_rate_t ser;
    /**
     * Bit error rate into the FEC.
     *
     * BERi = (num_ones_to_zeroes + num_zeroes_to_ones) / (5440 * code_words_processed)
     */
    spica_rate_t ber;
    /**
     * Frame error count, not rate
     */
    spica_rate_t ferc;
    /**
     * Corrected codeword rate = codewords_corrected[n] / codewords_processed
     * Where n is the number of errors -1.
     * ie. codewords_corrected[3-1] is the number of CW that had 3 corrected errors, so
     * corrected_ratio_hist[3-1] is the rate for 3 corrected errors per CW.
     */
    spica_rate_t corrected_ratio_hist[15];
} spica_fec_stats_poller_t;

/**
 * Uses the stats returned by the FW to calculate the rates for min/max/accumulated/current. This is simply
 * converting the CMIS F16 format to an ordinary float/double.
 *
 * @param die       [I] - The ASIC die being accessed.
 * @param intf      [I] - The interface being accessed, must be SPICA_INTF_EG_FEC or SPICA_INTF_IG_FEC.
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
inphi_status_t spica_fec_stats_poller_calc_ber(
    uint32_t die,
    e_spica_intf intf,
    spica_fec_stats_cp_block_t *stats,
    spica_fec_stats_poller_t *avg_rates,
    spica_fec_stats_poller_t *min_rates,
    spica_fec_stats_poller_t *max_rates,
    spica_fec_stats_poller_t *cur_rates
    );
#endif // defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)
#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

/*
 * MCU FEC stats poller methods
 */
inphi_status_t spica_mcu_fec_stats_poller_cfg(
    uint32_t   die,
    e_spica_intf intf,
    const spica_fec_stats_poller_rules_t *stats_rules);

inphi_status_t spica_mcu_fec_stats_poller_request(
    uint32_t   die,
    e_spica_intf intf,
    bool clear_on_read);

#ifndef INPHI_DONT_USE_STDLIB
e_spica_poller_status spica_mcu_fec_stats_poller_get(
    uint32_t   die,
    e_spica_intf intf,
    uint32_t blocks_to_read,
    spica_fec_stats_cp_block_t *stats);
#endif //ifndef INPHI_DONT_USE_STDLIB

inphi_status_t spica_mcu_fec_stats_poller_clear(
    uint32_t   die,  
    e_spica_intf intf);

#endif // defined(INPHI_REMOVE_MESSAGING)

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif

#endif //__SPICA_H__

// This is an automatically generated header file that is constructed
// as part of the build process. Do not modify it manually
#ifndef __SPICA_API_VERSION_H__
#define __SPICA_API_VERSION_H__

#define SPICA_API_VERSION          "1.2.0.929"
#define SPICA_API_BUILD_DATE       "12 May 2021 at 09:06:50 -0700"

// Major/Minor Release Number
#define SPICA_API_VERSION_MAJOR    1
#define SPICA_API_VERSION_MINOR    2

// Patch Release Number
#define SPICA_API_VERSION_REVISION 0
#define SPICA_API_VERSION_PATCH    0

// Continuous Integration Build ID
#define SPICA_API_VERSION_UPDATE   929
#define SPICA_API_VERSION_BUILD    929

#endif // __SPICA_API_VERSION_H__

/** @file spica_bootloader_image.h
 ******************************************************************************
 *
 * @brief
 *     This module contains the bootloader microcode image for downloading
 *     directly to the MCU.
 *
 ******************************************************************************
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
 *******************************************************************************/
#include <stdint.h>

#ifndef __SPICA_BOOTLOADER_IMAGE__
#define __SPICA_BOOTLOADER_IMAGE__

#ifdef __cplusplus
extern "C" {
#endif

// Inphi Spica DD-Bootloader Image for API Development
//   Version:      1.7.04
//   Build Date:  25 Aug 2020 at 07:33
//   Description: 

// If you're moving this image somewhere (i.e. flash), then get rid
// of this #if/#endif. You don't want to have the inlined image and this
// one included in your code.

#if defined(INPHI_HAS_INLINE_BOOTLOADER_FW) && (INPHI_HAS_INLINE_BOOTLOADER_FW==1)
const uint32_t spica_bootloader_image[] = {
    // Programming 12x32 bit words at 5ff80000
    0x5ff80000, 0x0000000c,
        0x5ffdea58,
        0x5ffde908,
        0x5ffdea58,
        0x5ffdea58,
        0x5ffde989,
        0x5ffa0010,
        0x5ff80030,
        0x5ff80570,
        0x60000000,
        0x60000000,
        0x00000000,
        0x00000000,
    // Programming 91x32 bit words at 5ffa0000
    0x5ffa0000, 0x0000005b,
        0x1049c500,
        0xe52049d5,
        0x49f53049,
        0x00003400,
        0x51384128,
        0xc1126148,
        0x13d10060,
        0xf0034800,
        0xe6204080,
        0x34382003,
        0x46303340,
        0x00000008,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x1009c500,
        0xe52009d5,
        0x09f53009,
        0x00003500,
        0x8003d140,
        0x22301133,
        0x13e62030,
        0xf7002010,
        0x80f0dd74,
        0x5778e740,
        0x464080f0,
        0x00000034,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x0049c900,
        0xd91009d1,
        0x49e92049,
        0x4049f930,
        0x90504980,
        0x49a06049,
        0x0049b070,
        0x00000034,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x1009c900,
        0xe92009d9,
        0x09d17009,
        0x4009f930,
        0x97500987,
        0x09a76009,
        0x0009b770,
        0x00000035,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x0049cd00,
        0xdd1009d1,
        0x49ed2049,
        0x4049fd30,
        0x50504940,
        0x49606049,
        0x80497070,
        0x90904980,
        0x49a0a049,
        0x0049b0b0,
        0x00000034,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x1009cd00,
        0xed2009dd,
        0x09d1b009,
        0x4009fd30,
        0x5b50094b,
        0x096b6009,
        0x80097b70,
        0x9b90098b,
        0x09aba009,
        0x0009bbb0,
        0x00000035,
    // Programming 2x32 bit words at 5ffa017c
    0x5ffa017c, 0x00000002,
        0x06004120,
        0x0000ffff,
    // Programming 2x32 bit words at 5ffa01a0
    0x5ffa01a0, 0x00000002,
        0x06004120,
        0x0000ffff,
    // Programming 2x32 bit words at 5ffa01e0
    0x5ffa01e0, 0x00000002,
        0x06004120,
        0x0000ffff,
    // Programming 2x32 bit words at 5ffa0220
    0x5ffa0220, 0x00000002,
        0x06004120,
        0x0000ffff,
    // Programming 3x32 bit words at 5ffa0260
    0x5ffa0260, 0x00000003,
        0x7c13d620,
        0x00510082,
        0x00ffff06,
    // Programming 1x32 bit words at 5ffa02a0
    0x5ffa02a0, 0x00000001,
        0x00003710,
    // Programming 2x32 bit words at 5ffa02dc
    0x5ffa02dc, 0x00000002,
        0x46004100,
        0x0000fffe,
    // Programming 8x32 bit words at 5ffa02f8
    0x5ffa02f8, 0x00000008,
        0x5ff80000,
        0x29a0c112,
        0x05613241,
        0x3103e820,
        0x62f6fffc,
        0xa0323002,
        0x61490338,
        0x000003a0,
    // Programming 2x32 bit words at 5ffa031c
    0x5ffa031c, 0x00000002,
        0x46004140,
        0x0000fffe,
    // Programming 57x32 bit words at 5ffa0740
    0x5ffa0740, 0x00000039,
        0x00000c06,
        0x00000000,
        0x5ffa0000,
        0x2222112f,
        0xe0000000,
        0x5ffa07c4,
        0x00000000,
        0x00000000,
        0x00000000,
        0x5ff80028,
        0x00000000,
        0x5ff8002c,
        0x00000000,
        0xe400000c,
        0xfff22113,
        0x3003eb30,
        0x228c7430,
        0x020903cc,
        0x20fff021,
        0x531c13e7,
        0x20136330,
        0xed210061,
        0xffed51ff,
        0x0cffee61,
        0x50027d03,
        0x06861066,
        0x00000000,
        0x00000000,
        0x00506340,
        0xf03d0020,
        0x500020f0,
        0xb3b6c033,
        0x41747014,
        0x67344070,
        0x6340e513,
        0xc0335050,
        0x00edb3f6,
        0xde510020,
        0x7d030cff,
        0x34407002,
        0x5050e340,
        0x7470c033,
        0xf0b3f641,
        0x0c002030,
        0x13491011,
        0x10134800,
        0x000c0020,
        0x40ffd741,
        0xd64113d2,
        0x13d340ff,
        0x40ffd641,
        0xd55113d4,
        0x410549ff,
        0xd540ffd5,
        0xffd45113,
        0x8f450549,
        0x0000003d,
    // Programming 676x32 bit words at 5ffde000
    0x5ffde000, 0x000002a4,
        0x5ff81800,
        0x00040020,
        0x5ff80030,
        0x5ff80570,
        0x633dc002,
        0x00001000,
        0x633dc000,
        0x633dc0a8,
        0x00008000,
        0x00004000,
        0x00002000,
        0x00000800,
        0x633dc064,
        0x633dc062,
        0x633dc0c4,
        0x5ff80458,
        0x633dc0a4,
        0x633dc0a6,
        0x633dc0ac,
        0x633dc0ae,
        0x633dc0b0,
        0x633dc0b2,
        0x0000bfff,
        0x633c0802,
        0x633c0800,
        0x0000ff0d,
        0x633dc100,
        0x0001c000,
        0x00010000,
        0x0000c000,
        0x5ff9ffff,
        0x5ffdffff,
        0x5ff8ffff,
        0x0000ffff,
        0x5ff7ffff,
        0x5ff80040,
        0x04c11db7,
        0x5ff80030,
        0x633dc0b4,
        0x633dc0b6,
        0x633dc0b8,
        0x633dc0ba,
        0x5ff80440,
        0x00001964,
        0x0000cafe,
        0x00001704,
        0x633dc0c0,
        0x633dc0c2,
        0x0000bcee,
        0x5ff8044c,
        0x633df004,
        0x5ff8045c,
        0x633df020,
        0x633df01c,
        0x11111111,
        0x633df000,
        0x633df014,
        0x633df028,
        0x633df02c,
        0x5ff80454,
        0x633df018,
        0x03000000,
        0x633dc0c6,
        0x00020000,
        0x5ff80444,
        0x00050023,
        0x80000007,
        0x00000005,
        0x5ffdea58,
        0xba11000c,
        0xffba31ff,
        0xe630f03d,
        0x00201013,
        0x71ffb961,
        0xb677ffb9,
        0x4b060906,
        0xf8367766,
        0x0c005455,
        0x00510012,
        0x060041f0,
        0x0000fffd,
        0xa1004136,
        0xb2b1ffb2,
        0xffb1c1ff,
        0xa1006025,
        0x1b0cffb1,
        0x5fa51c0c,
        0x00f01d00,
        0xa1010136,
        0x0b0cffae,
        0xa5ffaec1,
        0xaba1005e,
        0x00a1b2ff,
        0xe500a1c2,
        0xa8a1005d,
        0x0c7b0cff,
        0x005d25fc,
        0x0139030c,
        0x21391139,
        0x41393139,
        0x61395139,
        0x65004aa5,
        0x1a560071,
        0xe50a0c05,
        0x71390068,
        0x0c20c152,
        0x82811904,
        0xc19214c1,
        0x8ba1cb10,
        0xc9c14bb1,
        0xa9a1b991,
        0x89c199b1,
        0x1cc1a2d1,
        0x2d0061a5,
        0xa89aec0a,
        0x0040a571,
        0x1b003965,
        0xf871e844,
        0xe9554b05,
        0xe064660f,
        0x014822dc,
        0x04261128,
        0x00424602,
        0x0c003206,
        0x00004602,
        0x9256620c,
        0xff88a105,
        0x89c10b0c,
        0x005525ff,
        0x0cff86a1,
        0xff87c10b,
        0xa1005465,
        0x0b0cff83,
        0xe5ff86c1,
        0x80a10053,
        0xc10b0cff,
        0x5325ff7d,
        0xff7da100,
        0xfc0c1b0c,
        0xa1005265,
        0x7bb1ff7b,
        0xff7ac1ff,
        0xa10051a5,
        0x0b0cff78,
        0x2500a1c2,
        0x74a10051,
        0x0c4b0cff,
        0x0050654c,
        0x200015c6,
        0x71a1f4b0,
        0xa5fc0cff,
        0x6fa1004f,
        0xff70b1ff,
        0xe5ff70c1,
        0x6ca1004e,
        0x004d25ff,
        0xc234b4a0,
        0x69a1f0a0,
        0xc0bb1bff,
        0xb0b011bb,
        0x004d25f4,
        0x0cff6ba1,
        0xa51c0c0b,
        0x69a1004c,
        0x0c1b0cff,
        0x004be51c,
        0x65ff68a1,
        0xea97004a,
        0xff66a107,
        0x4da50aa8,
        0xa1f27c00,
        0x0b0cff5c,
        0x2500a1c2,
        0xf01d004a,
        0xb83a0266,
        0x350b6621,
        0x0c6631c8,
        0xff5ca130,
        0xc7004765,
        0x5aa116ea,
        0xff53b1ff,
        0xe5ff53c1,
        0x57a10047,
        0xc10b0cff,
        0x4725ff51,
        0xff4da100,
        0xc1ff4bb1,
        0x4665ff4a,
        0xc6e20c00,
        0x52a1ffbf,
        0xf4b040ff,
        0x400042e5,
        0x50a1f5b0,
        0x004265ff,
        0x4fa14148,
        0xf55040ff,
        0x41a505bd,
        0xff4da100,
        0xbdf44040,
        0x0040e504,
        0x4ba15178,
        0xf56070ff,
        0x402506bd,
        0xff49a100,
        0xbdf47070,
        0x003f6507,
        0xa12e6207,
        0x4025ff3f,
        0xff45b100,
        0xb0ff37c1,
        0x3ba110ba,
        0xe4b0b0ff,
        0xb020bbc0,
        0x3d65f4b0,
        0xff30a100,
        0xc1ff33b1,
        0x3f25ff32,
        0xc6d20c00,
        0x6162ffa2,
        0x17720714,
        0xb2ff32a1,
        0xa4c200a4,
        0x003da500,
        0xb1ff38a1,
        0x27c1ff28,
        0x003ce5ff,
        0xa1177217,
        0x27b1ff2b,
        0xff26c1ff,
        0xa1003be5,
        0x22b1ff32,
        0xff21c1ff,
        0x47003b25,
        0x24a13062,
        0x003965ff,
        0xb1f0a0d2,
        0xc820ff2d,
        0x11ccc041,
        0xd010bab0,
        0x1ea110cc,
        0x20bbc0ff,
        0xbbc02c0c,
        0xf4b0b020,
        0xe50035e5,
        0x8a1c004d,
        0xa1004565,
        0xb020ff24,
        0x0034e5f4,
        0xa1097247,
        0x8b0cff15,
        0x36a58c0c,
        0xff1fc100,
        0x7a1421d2,
        0xf0d5da64,
        0xd6d011dd,
        0x04bcd7c0,
        0x7c06220c,
        0xff1ae1ff,
        0xf011f5f0,
        0xaef7c0f4,
        0xc6320c04,
        0x2192ff77,
        0xff168114,
        0x901199f0,
        0xa897c097,
        0xc6420c04,
        0x1321ff72,
        0xff1341ff,
        0x71ff1451,
        0x6132ff14,
        0x11613210,
        0xc1a2030c,
        0x0039e540,
        0xa2041a56,
        0x18e51021,
        0x0011a500,
        0xe544c1a2,
        0x61a20038,
        0xa29afc13,
        0x17a51121,
        0x00106500,
        0xc71121c2,
        0x244602b7,
        0x1021b200,
        0x1bcc332b,
        0xad0b8c16,
        0x35b2b70b,
        0xba3234b7,
        0x3b34d7dc,
        0x0e06190c,
        0x460a2d00,
        0x0a2d0000,
        0x06d62256,
        0x0a2d0001,
        0xa2fffd06,
        0x0b0c18c1,
        0x14250c0c,
        0x560a2d00,
        0x6188d4ba,
        0x06d44856,
        0xf5e1ff4f,
        0x07beb7fe,
        0xba0435b7,
        0xc3b5f7fc,
        0xb916090c,
        0xf75c1605,
        0x61b20b0c,
        0x1661a215,
        0xa23c3637,
        0x30a548c1,
        0xfb1a5600,
        0xa51221a2,
        0x0865000f,
        0x92331b00,
        0x21b21221,
        0x1621a215,
        0x0a99bb1b,
        0x4b112182,
        0xcd3b87aa,
        0xa1ffcf86,
        0xcab1fec7,
        0xfec9c1fe,
        0x0c0024a5,
        0xffdfc6f2,
        0xb1fec3a1,
        0xc5c1fec6,
        0x0023a5fe,
        0xdb86021c,
        0xfebea1ff,
        0xc1fec2b1,
        0x22a5fec1,
        0xfff68600,
        0x46132122,
        0x0000ffd6,
        0x71004136,
        0x050cfed4,
        0x0cfed461,
        0x01358082,
        0xa276551b,
        0x1143f00f,
        0x600053d6,
        0x00463034,
        0x3d043d00,
        0x0c0739f0,
        0x66774b82,
        0xf01ddef5,
        0x51004136,
        0x0598feca,
        0x26059916,
        0x29661419,
        0x2c35a80f,
        0x0041250b,
        0x8a80f87c,
        0x1d258930,
        0x38f01df0,
        0x0c156835,
        0x72821c04,
        0x1200ffa0,
        0x008b0c40,
        0x0200a1a7,
        0x10a6a040,
        0xa591a0a0,
        0xc222003e,
        0xc1448bf8,
        0xb830feb7,
        0x30bab075,
        0xc074b0b0,
        0x0bb8a0bb,
        0x30113380,
        0xc466303b,
        0x1d3539cc,
        0x0cf37cf0,
        0x8605c91c,
        0x0000fffc,
        0x31004136,
        0x1329feae,
        0x0000f01d,
        0xad006136,
        0x89080c01,
        0x25028901,
        0x0a5d001f,
        0x68042a56,
        0xfea67101,
        0x0799290c,
        0xa1fff665,
        0xb060fea5,
        0x001225f4,
        0x60fea4a1,
        0x11a5f5b0,
        0xfea2a100,
        0x250417b2,
        0x27b80011,
        0xb0fea1a1,
        0x1065f5b0,
        0x8c27a800,
        0x8c046904,
        0xa703a903,
        0x1c0c0316,
        0x052d02c9,
        0x0000f01d,
        0x65004136,
        0x9391ffef,
        0x89080cfe,
        0x89298919,
        0x65098939,
        0x90a1fff1,
        0x250b0cfe,
        0x8fa1000d,
        0xa50b0cfe,
        0x8ea1000c,
        0xfe86b1fe,
        0xa1000be5,
        0x84b1fe8d,
        0x000b65fe,
        0x0000f01d,
        0xb1004136,
        0x1a0cfe8b,
        0x82c8a0c2,
        0x8791faa0,
        0xd90d0cfe,
        0x8959d949,
        0xc919c939,
        0xb929a969,
        0xfe5ea109,
        0x4c0c4b0c,
        0xa1000ae5,
        0x81b1fe5d,
        0x0007e5fe,
        0xe5fe62a1,
        0x0a2d0008,
        0xa1fe7fb1,
        0x06e5fe7f,
        0xfe56a100,
        0xa0c20b0c,
        0x0008a5f0,
        0xa10b62a7,
        0x53b1fe63,
        0xfe52c1fe,
        0xb70007a5,
        0x60a10b62,
        0xfe50b1fe,
        0xe5fe50c1,
        0x74a10006,
        0xfe74b1fe,
        0xe50003a5,
        0x1accffa6,
        0x0cffa4a5,
        0x00f01d02,
        0x61004136,
        0x1400fe60,
        0x80f87c40,
        0x95003083,
        0x109390a1,
        0x0c049367,
        0x00008607,
        0x80001272,
        0x88901087,
        0x00528220,
        0x0000f01d,
        0xdd004136,
        0xb102ad03,
        0x0c0cfe54,
        0x1dfffc65,
        0x000000f0,
        0xad004136,
        0xfe4fb102,
        0x27a50c0c,
        0x1d0a2d00,
        0x000000f0,
        0xad004136,
        0xfe4ab102,
        0x26650c0c,
        0xfe48b100,
        0xf97c0c0c,
        0x90108340,
        0x99a03094,
        0x9002ad10,
        0x20802088,
        0x6502ddf4,
        0xf01dfff8,
        0x31004136,
        0x0338fe50,
        0xe5823320,
        0x0a2d002d,
        0x20002d65,
        0x3837c08a,
        0x00f01df6,
        0x32004136,
        0x140ce8a3,
        0xa5fe49a1,
        0x330b0027,
        0x6a47c3ac,
        0xfe4631f2,
        0xd8cc2388,
        0x65fe46a1,
        0x23490026,
        0x0299090c,
        0xa10001c6,
        0x2565fe42,
        0xa102a900,
        0x41b1fe41,
        0x0023a5fe,
        0xf01d020c,
        0xf01d520c,
        0x3d006136,
        0xfe394102,
        0x1488090c,
        0x78cc0199,
        0xfaa501ad,
        0xcc0a2dff,
        0x2501ad7a,
        0x0a2dfffa,
        0xf01d0a8c,
        0x01b814a8,
        0x04b903b9,
        0x14a9aa1b,
        0x0000f01d,
        0xa1004136,
        0xf265fe08,
        0x046a17ff,
        0x1d3424a0,
        0x1d720cf0,
        0x000000f0,
        0x65004136,
        0x0a3dfffe,
        0xa5fe2aa1,
        0xfab1001e,
        0xd08d3cfd,
        0xccd011c3,
        0x20bab010,
        0xa1c7afd2,
        0xbbd0fe24,
        0x20bbc010,
        0xc0c1a0c2,
        0x1b6520bb,
        0xfe20a100,
        0x1c0c1b0c,
        0xa1001ca5,
        0x1b65fe18,
        0x036a1700,
        0xf01d121c,
        0x0cfe1ca1,
        0x0019654b,
        0x0cfe1ba1,
        0x0018e51b,
        0xa1fe1ab1,
        0x0bb8fe1a,
        0xb1001825,
        0x10a1fe19,
        0x20b2b0fe,
        0xc1001765,
        0x020cfe0c,
        0x1c290c29,
        0x3c292c29,
        0x0000f01d,
        0xa1004136,
        0x4b0cfdda,
        0xe9e54c0c,
        0xfdd7a1ff,
        0x4c0c0b0c,
        0xa1ffe925,
        0xe7a5fe0d,
        0x3480a0ff,
        0xa1e8a322,
        0x1800fe03,
        0xa1220040,
        0x31001465,
        0x1a37fe08,
        0x9c220b0c,
        0xfdfda1c2,
        0x37001365,
        0x020cf29a,
        0xe5fdd2a1,
        0xea27ffe4,
        0xfe01a107,
        0xe8250aa8,
        0x0cf01dff,
        0xfff9c682,
        0x2003b130,
        0x333b0301,
        0x200c9237,
        0x628c0302,
        0x0220220b,
        0x03003013,
        0xb1304128,
        0x56513813,
        0x61320562,
        0x12614211,
        0x31136152,
        0xe620fdf4,
        0x13e63003,
        0x1203b130,
        0x201060c1,
        0x36040c00,
        0x01f50081,
        0xfdeee100,
        0xf01d0cea,
        0x0c13e620,
        0x10a54802,
        0xb1300020,
        0x58953813,
        0x003000b5,
        0xc1006136,
        0xc0cafde8,
        0xcd006136,
        0x00613600,
        0x213600cd,
        0x1d0bbd00,
        0x12f27cf0,
        0x300060c1,
        0xfde13100,
        0x000003a0,
        0xac004136,
        0x62170c53,
        0xa05200a0,
        0x18937600,
        0x500d6207,
        0x880bc083,
        0x00401800,
        0x6640a147,
        0x41212020,
        0x5050551b,
        0x00004674,
        0x062d060c,
        0x0000f01d,
        0x22004136,
        0x04000012,
        0x10232040,
        0x20b12020,
        0xf01df420,
        0x28004136,
        0x40040002,
        0x20102320,
        0xf01d9120,
        0x00004136,
        0xf87c4014,
        0x00308380,
        0x6360a165,
        0x04036610,
        0x0046070c,
        0x80027800,
        0x66801087,
        0x1d026920,
        0x000000f0,
        0xdd004136,
        0x7c02ad03,
        0xe50c0cfb,
        0xf01dfffc,
        0xad004136,
        0x0cfb7c02,
        0xfffae50c,
        0xf01d0a2d,
        0xad004136,
        0x0cfb7c02,
        0xfff9e50c,
        0xfb7c0c0c,
        0xb0103340,
        0x8a803084,
        0x8002ad10,
        0x03dd2033,
        0x2dfff965,
        0x00f01d03,
        0x51384128,
        0x1060c112,
        0x30000041,
        0x00000000,
        0x20002136,
        0xf01d03ea,
        0x56002136,
        0xf0300052,
        0x00200013,
        0x0000f01d,
        0xcc002136,
        0x03f02032,
        0x020cf01d,
        0x0000f01d,
};
// The length of the bootloader image
const uint32_t spica_bootloader_image_length = sizeof(spica_bootloader_image)/sizeof(spica_bootloader_image[0]);

#endif // defined(INPHI_HAS_INLINE_BOOTLOADER_FW) && (INPHI_HAS_INLINE_BOOTLOADER_FW==1)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __SPICA_BOOTLOADER_IMAGE__
// This is an automatically generated header file that is constructed
// as part of the build process. Do not modify it manually
#ifndef __POR_API_VERSION_H__
#define __POR_API_VERSION_H__

#define POR_API_VERSION          "1.2.0.929"
#define POR_API_BUILD_DATE       "12 May 2021 at 09:06:50 -0700"

// Major/Minor Release Number
#define POR_API_VERSION_MAJOR    1
#define POR_API_VERSION_MINOR    2

// Patch Release Number
#define POR_API_VERSION_REVISION 0
#define POR_API_VERSION_PATCH    0

// Continuous Integration Build ID
#define POR_API_VERSION_UPDATE   929
#define POR_API_VERSION_BUILD    929

#endif // __POR_API_VERSION_H__
#ifndef __SPICA_APP_VERSION_H__
#define __SPICA_APP_VERSION_H__
// This file is auto-generated, do not change
#define SPICA_APP_VERSION_MAJOR 1
#define SPICA_APP_VERSION_MINOR 2
#define SPICA_APP_VERSION_REVISION 0
#define SPICA_APP_VERSION_BUILD 963
#define SPICA_APP_VERSION_NUMBER 0x102003c3 
// Application version description
#define SPICA_APP_VERSION_DESC  "Test firmware version"
#endif // __SPICA_APP_VERSION_H__

/** @file porrima_gen3_app_fw_image.h
 ******************************************************************************
 *
 * @brief
 *     This module contains the application microcode image for downloading
 *     directly to the MCU.
 *
 ******************************************************************************
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
 *******************************************************************************/
#include <stdint.h>

#ifndef __SPICA_APP_FW_IMAGE__
#define __SPICA_APP_FW_IMAGE__

#ifdef __cplusplus
extern "C" {
#endif

// Inphi porrima_gen3 Firmware Image for API Development
//   Version:      1.2.0.963
//   Build Date:  12 May 2021 at 11:47 -0400
//   Description: Test firmware version

// If you're moving this image somewhere (i.e. flash), then get rid
// of this #if/#endif. You don't want to have the inlined image and this
// one included in your code.

#if defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW==1)
const uint32_t spica_app_fw_image[] = {
    // Programming 6322x32 bit words at 5ff81800
    // Remove dsp firmware image in por_api.c because didn't use INLINE_APP_FW, Lance 20211004.
 };
// The length of the firmware image
const uint32_t spica_app_fw_image_length = sizeof(spica_app_fw_image)/sizeof(spica_app_fw_image[0]);

#endif // defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW==1)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __SPICA_APP_FW_IMAGE__


#ifdef __cplusplus
} /* closing brace for extern "C" (gen) */
#endif




#endif /* __$INPHI_$POR_API__ */





#include "por_api.h"

/** @file spica_package.c
 *****************************************************************************
 *
 * @brief
 * This module contains the implementation of the packagement management
 * methods used to cache access to the ASIC registers and map API
 * channel numbers to the approriate ASIC pins.
 * 
 *****************************************************************************
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

void spica_package_cache_clear();

static e_spica_package_type g_spica_package_cache_package = SPICA_PACKAGE_TYPE_UNKNOWN;
static bool g_spica_package_cache_initialized = false;

/**
 * This is an internal method that is used to determine whether the
 * EFUSE has been loaded.
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return true if the EFUSE is programmed and false if it is
 *         still powered down.
 */
static bool spica_efuse_is_programmed(uint32_t die)
{
    return (0x1 == (SPICA_EFUSE_EF__DATA__READ(die) & 0x1));
}

/**
 * This is an internal method used to fetch the
 * contents of the EFUSE in order to discover the
 * package type.
 */
static inphi_status_t spica_efuse_fetch(uint32_t die)
{
    inphi_status_t status = INPHI_OK;

    // If the EFUSE was not accessible then return immediately
    // to avoid the API constantly polling the EFUSE in a
    // scenario where it doesn't exist. This is to avoid the
    // API blocking the GUI when operating offline or in chipsim
    // modes.
    if(0xFF == SPICA_EFUSE_GENERAL0_CFG__WORD_ADDRESS__READ(die))
    {
        return INPHI_ERROR;
    }

    SPICA_EFUSE_GENERAL1_CFG__POWER_UP__RMW(die, 1);
    SPICA_EFUSE_GENERAL0_CFG__FETCH__RMW(die, 0);
    SPICA_EFUSE_GENERAL0_CFG__FETCH__RMW(die, 1);

    //wait a small fixed amount of time for the efuse to power up
    INPHI_UDELAY(200);

#if 0 //not needed
    if(max_attempts == 0)
    {
        // If the EFUSE fetch failed then 0xFF in the word
        // address field. This is an indication to the API not to
        // attempt to re-read the EFUSE
        SPICA_EFUSE_GENERAL0_CFG__WORD_ADDRESS__RMW(die, 0xff);
        INPHI_CRIT("EFUSE was not accessible, package type is unknown\n");
        status = INPHI_ERROR;
    }
#endif

    // Power down the EFUSE
    SPICA_EFUSE_GENERAL1_CFG__POWER_UP__RMW(die, 0);

    return status;
}

//! This method is used to cache the package type
//! within the die parameter to avoid having to step through
//! an array to lookup the package type.
//!
//! @param die [I] - The ASIC die being accessed.
//!
//! @return
//!   The die parameter with the package
//!   type encoded.
e_spica_package_type spica_package_type_from_die(uint32_t* die)
{
    e_spica_package_type package = (e_spica_package_type)((*die >> 4) & 0xF);

    // If the package type has not been cached then look
    // it up and cache it in the parameter.
    if(package == SPICA_PACKAGE_TYPE_UNMAPPED)
    {
        // Read the package type from the EFUSE and
        // cache it in the die parameter.
        if(!spica_efuse_is_programmed(*die))
        {
            spica_efuse_fetch(*die);
        }

        // Read the package type from the EFUSE
        uint16_t chip_id = SPICA_MMD30_CHIP_ID__READ(*die);

        // If the valid bit is not set then force the 15x14 package
        if(0x100 != (chip_id & 0x100))
        {
            package = SPICA_PACKAGE_TYPE_UNMAPPED;
        }
        else
        {
            uint32_t tmp = (chip_id & 0x3f) + 1;
            if(tmp >= SPICA_PACKAGE_TYPE_MAX)
            {
                package = SPICA_PACKAGE_TYPE_UNKNOWN;
            }
            else
            {
                package = (e_spica_package_type)tmp;
            }
        }

        // Cache package type in the lower bits of the EFUSE
        // to avoid looking it up on every access.
        *die = spica_package_type_set_in_die(*die, package);
    }

    return package;
}

// Override the package type, this will be saved in bits [7:5] of the die
uint32_t spica_package_type_set_in_die(uint32_t die, e_spica_package_type package)
{
    // Clear out the old package type
    die &= ~0xF0;
    // OR in the new package type
    die |= (((uint32_t)package & 0xF) << 4);
    
    return die;
}

uint32_t spica_package_discover_type(uint32_t die)
{
    e_spica_package_type package = spica_package_get_type(die);

    // Cache package type in the lower bits of the EFUSE
    // to avoid looking it up on every access.
    return spica_package_type_set_in_die(die, package);
}

e_spica_package_type spica_package_query_efuse(uint32_t die)
{
    if(!spica_efuse_is_programmed(die))
    {
        spica_efuse_fetch(die);
    }

    e_spica_package_type package;
    // Read the package type from the EFUSE
    uint16_t chip_id = SPICA_MMD30_CHIP_ID__READ(die);

    // If the valid bit is not set then force to UNMAPPED 
    if(0x100 != (chip_id & 0x100))
    {
        INPHI_WARN("Chip unfused, defaulting to UNMAPPED. chip_id 0x%x\n", chip_id);
        package = SPICA_PACKAGE_TYPE_UNMAPPED;
    }
    else
    {
        uint32_t tmp = (chip_id & 0x3f);
        if(tmp >= SPICA_PACKAGE_TYPE_MAX)
        {
            INPHI_WARN("Unsupported package read from HW, CHIP_ID=0x%x\n", chip_id);
            package = SPICA_PACKAGE_TYPE_UNKNOWN;
        }
        else
        {
            package = (e_spica_package_type)tmp;
            
            if (SPICA_PACKAGE_TYPE_EML_12x13 == package)  
            {
                // if the chip revision is 1, then reassign the package
                if (1 == SPICA_EFUSE_PKG_REVISION__READ(die))
                {
                    package = SPICA_PACKAGE_TYPE_EML_12x13_REV1;
                }
            }
        }
    }

    g_spica_package_cache_package = package;

    return package;
}

uint32_t spica_package_get_num_dies(uint32_t die)
{
    e_spica_package_type package = spica_package_get_type(die);

    switch (package)
    {
        case SPICA_PACKAGE_TYPE_EML_BOT_15x14:
        case SPICA_PACKAGE_TYPE_EML_TOP_15x14:
        case SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14:
        case SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14:
            return 2;
            break;

        case SPICA_PACKAGE_TYPE_EML_12x13:
        case SPICA_PACKAGE_TYPE_EML_12x13_REV1:
        case SPICA_PACKAGE_TYPE_STD_10x13:
        case SPICA_PACKAGE_TYPE_SIPHO:
        case SPICA_PACKAGE_TYPE_UNMAPPED:
            return 1;
            break;

        default:
            return 1;
            break;

    }
}

/* This method is used to determine the die associated with a particular channel */
uint32_t spica_reg_channel_to_die(uint32_t die, uint32_t channel, e_spica_intf intf)
{
    (void)channel;
    (void)intf;

    e_spica_package_type package = spica_package_get_type(die);

    switch (package)
    {
        case SPICA_PACKAGE_TYPE_EML_BOT_15x14:
        case SPICA_PACKAGE_TYPE_EML_TOP_15x14:
        case SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14:
            if ((channel >= 1) && (channel <= 4))
            {   
                return (die | 1); // upper die
            }
            else
            {   
                return (die & ~1); // lower die
            }
            break;

        case SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14:
            if ((channel >= 1) && (channel <= 4))
            {   
                return (die & ~1); // lower die
            }
            else
            {   
                return (die | 1); // upper die
            }
            break;

        case SPICA_PACKAGE_TYPE_EML_12x13:
        case SPICA_PACKAGE_TYPE_EML_12x13_REV1:
        case SPICA_PACKAGE_TYPE_STD_10x13:
        case SPICA_PACKAGE_TYPE_SIPHO:
        case SPICA_PACKAGE_TYPE_UNMAPPED:
            return (die & ~1); // lower die
            break;

        default:
            return (die & ~1); // lower die
            break;

    }
}

uint32_t spica_package_get_base_die(uint32_t die)
{
    die &= ~0xF;

    return die;
}

// Query the ASIC package type
e_spica_package_type spica_package_get_type(uint32_t die)
{
    if(!g_spica_package_cache_initialized)
    {
        spica_package_cache_clear();
    }
    // If valid package type cached then don't re-query EFUSE 
    if (g_spica_package_cache_package != SPICA_PACKAGE_TYPE_UNKNOWN)
    {
        return g_spica_package_cache_package;
    }

    uint32_t base_die = die & ~0xFF;

    return spica_package_query_efuse(base_die);
}

void spica_package_get_channels(uint32_t die, e_spica_intf intf, uint32_t* min, uint32_t* max)
{
    const spica_channels_t* channels = spica_channels(die, intf);
    
    if(channels != NULL)
    {
        *min = channels->ch[0];
        *max = channels->ch[(channels->num)-1];
    }
    else
    {
        *min = 0;
        *max = 0;
    }
}

uint32_t spica_package_get_intf(uint32_t die)
{
    e_spica_package_type package = spica_package_get_type(die);
    
    switch (package)
    {
        // RobM: Debug, find out which intf/packages
        case SPICA_PACKAGE_TYPE_EML_BOT_15x14:
        case SPICA_PACKAGE_TYPE_EML_TOP_15x14:
        case SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14:
        case SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14:
            return (SPICA_INTF_POR | SPICA_INTF_PMR);
            break;

        case SPICA_PACKAGE_TYPE_EML_12x13:
        case SPICA_PACKAGE_TYPE_EML_12x13_REV1:
        case SPICA_PACKAGE_TYPE_STD_10x13:
            return (SPICA_INTF_POR | SPICA_INTF_PSR);
            break;
    
        case SPICA_PACKAGE_TYPE_UNMAPPED:
            if (spica_package_has_psr(die))
            {
                return (SPICA_INTF_POR | SPICA_INTF_PSR);
            }
            if (spica_package_has_pmr(die))
            {
                return (SPICA_INTF_POR | SPICA_INTF_PMR);
            }

            break;

        default: 
            break;
    }
    return SPICA_INTF_NONE;
}

/**
* This method is called to dump the cache used to map a particular
* die parameter to the associated ASIC package type. The package type
* is important so that the API knows how to map channels to the external
* pins of the ASIC.
*
* @since 0.6
*/
void spica_package_cache_dump()
{
    INPHI_NOTE("init=%s, package=%08x\n",
               g_spica_package_cache_initialized ? "True" : "False",
               g_spica_package_cache_package);
}

void spica_package_cache_clear()
{
    g_spica_package_cache_package      = SPICA_PACKAGE_TYPE_UNKNOWN;
    g_spica_package_cache_initialized  = true;
}

bool spica_package_has_psr(uint32_t die)
{
    e_spica_package_type package = spica_package_get_type(die);

    switch (package)
    {
        case SPICA_PACKAGE_TYPE_EML_12x13:
        case SPICA_PACKAGE_TYPE_EML_12x13_REV1:
        case SPICA_PACKAGE_TYPE_STD_10x13:
        case SPICA_PACKAGE_TYPE_SIPHO:
            return true;
            break;

        case SPICA_PACKAGE_TYPE_UNMAPPED:
            if (SPICA_PACKAGE_HOST_INTF_PSR == SPICA_EFUSE_DEVICE_CONTROL__HOST_INTFACE__READ(die))
            {
                return true;
            }
            break;

        default:
            break;

    }
    return false;
}

bool spica_package_has_pmr(uint32_t die)
{
    e_spica_package_type package = spica_package_get_type(die);

    switch (package)
    {
        case SPICA_PACKAGE_TYPE_EML_BOT_15x14:
        case SPICA_PACKAGE_TYPE_EML_TOP_15x14:
        case SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14:
        case SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14:
            return true;
            break;

        case SPICA_PACKAGE_TYPE_UNMAPPED:
            if (SPICA_PACKAGE_HOST_INTF_PMR == SPICA_EFUSE_DEVICE_CONTROL__HOST_INTFACE__READ(die))
            {
                return true;
            }
            break;

        default:
            break;

    }
    return false;
}

e_spica_driver_type spica_package_get_driver_type(uint32_t die)
{
    e_spica_package_type package = spica_package_get_type(die);
    e_spica_driver_type driver = SPICA_DRIVER_TYPE_NONE;

    switch (package)
    {
        case SPICA_PACKAGE_TYPE_EML_BOT_15x14:
        case SPICA_PACKAGE_TYPE_EML_TOP_15x14:
        case SPICA_PACKAGE_TYPE_EML_12x13:
        case SPICA_PACKAGE_TYPE_EML_12x13_REV1:
            return SPICA_DRIVER_TYPE_EML;
            break;
        case SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14:
        case SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14:
        case SPICA_PACKAGE_TYPE_SIPHO:
            return SPICA_DRIVER_TYPE_SIPHO;
            break;
        case SPICA_PACKAGE_TYPE_STD_10x13:
            return SPICA_DRIVER_TYPE_1VPP;
            break;
        case SPICA_PACKAGE_TYPE_UNMAPPED:
            return SPICA_EFUSE_DEVICE_CONTROL__DRV_TYPE__READ(die);
            break;
        default:
            return SPICA_DRIVER_TYPE_NONE;
            break;
    }

    return driver;
}

/** @file spica_reg_access.c
 *****************************************************************************
 *
 * @brief
 * These contain the register access functionality.
 *
 * End users must implement spica_reg_get and spica_reg_set for their comms
 * protocol (MDIO or I2C).
 * 
 *****************************************************************************
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

const spica_channels_t _spica_chs_1t8  = {8,  {1, 2, 3, 4, 5, 6, 7, 8}}; // All channels 
const spica_channels_t _spica_chs_1t4  = {4,  {1, 2, 3, 4}};             // Die 1 channels
const spica_channels_t _spica_chs_5t8  = {4,  {5, 6, 7, 8}};             // Die 0 channels

static spica_channels_t _spica_chs_line_bundle[SPICA_MAX_BUNDLES]; // stores line bundle info
static spica_channels_t _spica_chs_host_bundle[SPICA_MAX_BUNDLES]; // stores host bundle info

extern spica_bundle_rules_t  g_bundle_storage;

const spica_channels_t* spica_channels(
    uint32_t die, 
    e_spica_intf intf)
{
    e_spica_package_type package = spica_package_get_type(die);

    switch(package)
    {
        case SPICA_PACKAGE_TYPE_EML_BOT_15x14:
        case SPICA_PACKAGE_TYPE_EML_TOP_15x14:
        case SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14:
        case SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14:
            return &_spica_chs_1t8;
            break;

        case SPICA_PACKAGE_TYPE_EML_12x13:
        case SPICA_PACKAGE_TYPE_EML_12x13_REV1:
        case SPICA_PACKAGE_TYPE_STD_10x13:
            if (intf & SPICA_INTF_POR)
            {
                return &_spica_chs_1t4;
            }
            else // host side is PSR
            {
                return &_spica_chs_1t8;
            }
            break;

        case SPICA_PACKAGE_TYPE_UNMAPPED:
            if (intf & (SPICA_INTF_POR | SPICA_INTF_PMR))
            {
                return &_spica_chs_1t4;
            }
            else // host side is PSR
            {
                return &_spica_chs_1t8;
            }
            break;

        default:
            break;

    }

    //assert(false);
    return NULL;
}

const spica_channels_t* spica_bundle_channels(
    uint32_t die, 
    uint32_t bundle_idx, 
    e_spica_intf intf)
{
    if (intf & SPICA_INTF_POR)
    {
        return (&_spica_chs_line_bundle[bundle_idx]);
    }
    else // host side
    {
        return (&_spica_chs_host_bundle[bundle_idx]);
    }
}

void spica_bundle_ch_cfg(
    uint32_t bundle_idx) 
{
    uint32_t ch_cnt;
    uint32_t ch_num;

    ch_cnt = 0;
    ch_num = 0;

    // riffle thru all 16 channels in the bit map
    for (uint32_t ch_idx = 1; ch_idx <= 0x8000; ch_idx <<= 1)
    {
        if (g_bundle_storage.line_ch_map[bundle_idx] & ch_idx)
        {
            _spica_chs_line_bundle[bundle_idx].ch[ch_cnt] = ch_num;
            ch_cnt++;
        }
        ch_num++;
    }
    _spica_chs_line_bundle[bundle_idx].num = ch_cnt;

#if 0
    INPHI_NOTE("spica_bundle_ch_cfg: line, bundle_idx=%d, ch_cnt=%d, ch=", bundle_idx, ch_cnt);
    for (uint32_t i = 0; i < ch_cnt; i++)
    {
        INPHI_NOTE("%d,", _spica_chs_line_bundle[bundle_idx].ch[i]);
    }
    INPHI_NOTE("\n");
#endif
    ch_cnt = 0;
    ch_num = 0;

    for (uint32_t ch_idx = 1; ch_idx <= 0x8000; ch_idx <<= 1)
    {
        if (g_bundle_storage.host_ch_map[bundle_idx] & ch_idx)
        {
            _spica_chs_host_bundle[bundle_idx].ch[ch_cnt] = ch_num;
            ch_cnt++;
        }
        ch_num++;
    }
    _spica_chs_host_bundle[bundle_idx].num = ch_cnt;

#if 0
    INPHI_NOTE("spica_bundle_ch_cfg: host, bundle_idx=%d, ch_cnt=%d, ch=", bundle_idx, ch_cnt);
    for (uint32_t i = 0; i < ch_cnt; i++)
    {
        INPHI_NOTE("%d,", _spica_chs_host_bundle[bundle_idx].ch[i]);
    }
    INPHI_NOTE("\n");
#endif

}

/**
 * These are enumerated register block values used internally for re-mapping
 * register accessed based on the package channel numbers.
 *
 * @private
 */
typedef enum
{
    SPICA_REG_BLOCK_NO_CHANNEL,

    SPICA_REG_BLOCK_SRX,
    SPICA_REG_BLOCK_SRX_RXL,

    SPICA_REG_BLOCK_MRX,
    SPICA_REG_BLOCK_ORX,

    SPICA_REG_BLOCK_SMTX,
    SPICA_REG_BLOCK_SMTX_PSR,

    SPICA_REG_BLOCK_OTX,

    SPICA_REG_BLOCK_TOP_ERU,

    /** Last block for range checks */
    SPICA_REG_BLOCK_END,

}e_spica_reg_block;

typedef enum 
{
    D_0, D_1,
} e_die_num;

typedef enum 
{
    C_0,  C_1,  C_2,  C_3,  C_4,  C_5,  C_6,  C_7, 
    C_8,  C_9,  C_10, C_11, C_12, C_13, C_14, C_15, 
    C_16, C_17, C_18, C_19, C_20, C_21, C_22, C_23, 
    C_24, C_25
} e_ch_num;

static uint8_t reg_block_map[][SPICA_REG_BLOCK_END][9][2] = {
    [SPICA_PACKAGE_TYPE_EML_BOT_15x14] = { 
     //                                                                  PACKAGE CHANNEL 
     //                                     0          1            2           3           4           5           6           7           8
     //------------------------------------------------------------------------------------------------------------------------------------------- 
        [SPICA_REG_BLOCK_NO_CHANNEL] = {{0xf,0xf}, {D_0, C_0}, {D_0, C_1}, {D_0, C_2}, {D_0, C_3}, {D_1, C_0}, {D_1, C_1}, {D_1, C_2}, {D_1, C_3}},

        [SPICA_REG_BLOCK_MRX]        = {{0xf,0xf}, {D_1, C_3}, {D_1, C_2}, {D_1, C_1}, {D_1, C_0}, {D_0, C_3}, {D_0, C_1}, {D_0, C_2}, {D_0, C_0}},

        [SPICA_REG_BLOCK_ORX]        = {{0xf,0xf}, {D_1, C_0}, {D_1, C_1}, {D_1, C_2}, {D_1, C_3}, {D_0, C_0}, {D_0, C_1}, {D_0, C_2}, {D_0, C_3}},

        [SPICA_REG_BLOCK_SMTX]       = {{0xf,0xf}, {D_1, C_0}, {D_1, C_2}, {D_1, C_1}, {D_1, C_3}, {D_0, C_0}, {D_0, C_2}, {D_0, C_1}, {D_0, C_3}},

        [SPICA_REG_BLOCK_OTX]        = {{0xf,0xf}, {D_1, C_0}, {D_1, C_1}, {D_1, C_2}, {D_1, C_3}, {D_0, C_0}, {D_0, C_1}, {D_0, C_2}, {D_0, C_3}}, 

        [SPICA_REG_BLOCK_TOP_ERU]    = {{0xf,0xf}, {D_1, C_0}, {D_1, C_1}, {D_0, C_0}, {D_0, C_1}, {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},
    },
    [SPICA_PACKAGE_TYPE_EML_TOP_15x14] = { 
     //                                                                  PACKAGE CHANNEL 
     //                                     0          1            2           3           4           5           6           7           8
     //------------------------------------------------------------------------------------------------------------------------------------------- 
        [SPICA_REG_BLOCK_NO_CHANNEL] = {{0xf,0xf}, {D_0, C_0}, {D_0, C_1}, {D_0, C_2}, {D_0, C_3}, {D_1, C_0}, {D_1, C_1}, {D_1, C_2}, {D_1, C_3}},

        [SPICA_REG_BLOCK_MRX]        = {{0xf,0xf}, {D_1, C_0}, {D_1, C_2}, {D_1, C_1}, {D_1, C_3}, {D_0, C_1}, {D_0, C_0}, {D_0, C_3}, {D_0, C_2}},

        [SPICA_REG_BLOCK_ORX]        = {{0xf,0xf}, {D_1, C_0}, {D_1, C_1}, {D_1, C_2}, {D_1, C_3}, {D_0, C_0}, {D_0, C_1}, {D_0, C_2}, {D_0, C_3}},

        [SPICA_REG_BLOCK_SMTX]       = {{0xf,0xf}, {D_1, C_3}, {D_1, C_1}, {D_1, C_2}, {D_1, C_0}, {D_0, C_3}, {D_0, C_1}, {D_0, C_2}, {D_0, C_0}},

        [SPICA_REG_BLOCK_OTX]        = {{0xf,0xf}, {D_1, C_0}, {D_1, C_1}, {D_1, C_2}, {D_1, C_3}, {D_0, C_0}, {D_0, C_1}, {D_0, C_2}, {D_0, C_3}}, 

        [SPICA_REG_BLOCK_TOP_ERU]    = {{0xf,0xf}, {D_1, C_0}, {D_1, C_1}, {D_0, C_0}, {D_0, C_1}, {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},
    },
    [SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14] = { 
     //                                                                  PACKAGE CHANNEL 
     //                                     0          1            2           3           4           5           6           7           8
     //------------------------------------------------------------------------------------------------------------------------------------------- 
        [SPICA_REG_BLOCK_NO_CHANNEL] = {{0xf,0xf}, {D_0, C_0}, {D_0, C_1}, {D_0, C_2}, {D_0, C_3}, {D_1, C_0}, {D_1, C_1}, {D_1, C_2}, {D_1, C_3}},

        [SPICA_REG_BLOCK_MRX]        = {{0xf,0xf}, {D_0, C_3}, {D_0, C_2}, {D_0, C_1}, {D_0, C_0}, {D_1, C_3}, {D_1, C_2}, {D_1, C_1}, {D_1, C_0}},

        [SPICA_REG_BLOCK_ORX]        = {{0xf,0xf}, {D_0, C_3}, {D_0, C_2}, {D_0, C_1}, {D_0, C_0}, {D_1, C_3}, {D_1, C_2}, {D_1, C_1}, {D_1, C_0}},

        [SPICA_REG_BLOCK_SMTX]       = {{0xf,0xf}, {D_0, C_0}, {D_0, C_2}, {D_0, C_1}, {D_0, C_3}, {D_1, C_0}, {D_1, C_2}, {D_1, C_1}, {D_1, C_3}},

        [SPICA_REG_BLOCK_OTX]        = {{0xf,0xf}, {D_0, C_3}, {D_0, C_2}, {D_0, C_1}, {D_0, C_0}, {D_1, C_3}, {D_1, C_2}, {D_1, C_1}, {D_1, C_0}}, 

        [SPICA_REG_BLOCK_TOP_ERU]    = {{0xf,0xf}, {D_0, C_0}, {D_0, C_1}, {D_1, C_0}, {D_1, C_1}, {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},
    },
    [SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14] = { 
     //                                                                  PACKAGE CHANNEL 
     //                                     0          1            2           3           4           5           6           7           8
     //------------------------------------------------------------------------------------------------------------------------------------------- 
        [SPICA_REG_BLOCK_NO_CHANNEL] = {{0xf,0xf}, {D_0, C_0}, {D_0, C_1}, {D_0, C_2}, {D_0, C_3}, {D_1, C_0}, {D_1, C_1}, {D_1, C_2}, {D_1, C_3}},

        [SPICA_REG_BLOCK_MRX]        = {{0xf,0xf}, {D_1, C_0}, {D_1, C_2}, {D_1, C_1}, {D_1, C_3}, {D_0, C_1}, {D_0, C_0}, {D_0, C_3}, {D_0, C_2}},

        [SPICA_REG_BLOCK_ORX]        = {{0xf,0xf}, {D_1, C_3}, {D_1, C_2}, {D_1, C_1}, {D_1, C_0}, {D_0, C_2}, {D_0, C_3}, {D_0, C_0}, {D_0, C_1}},

        [SPICA_REG_BLOCK_SMTX]       = {{0xf,0xf}, {D_1, C_3}, {D_1, C_1}, {D_1, C_2}, {D_1, C_0}, {D_0, C_3}, {D_0, C_1}, {D_0, C_2}, {D_0, C_0}},

        [SPICA_REG_BLOCK_OTX]        = {{0xf,0xf}, {D_1, C_1}, {D_1, C_0}, {D_1, C_3}, {D_1, C_2}, {D_0, C_1}, {D_0, C_0}, {D_0, C_3}, {D_0, C_2}}, 

        [SPICA_REG_BLOCK_TOP_ERU]    = {{0xf,0xf}, {D_1, C_0}, {D_1, C_1}, {D_0, C_0}, {D_0, C_1}, {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},
    },
    [SPICA_PACKAGE_TYPE_EML_12x13] = { 
     //                                                                    PACKAGE CHANNEL 
     //                                     0           1            2            3           4          5             6           7           8
     //---------------------------------------------------------------------------------------------------------------------------------------------- 
        [SPICA_REG_BLOCK_NO_CHANNEL] = {{0xf,0xf}, {D_0, C_0},  {D_0, C_1},  {D_0, C_2}, {D_0, C_3}, {D_0, C_4},  {D_0, C_5}, {D_0, C_6}, {D_0, C_7}}, 

        [SPICA_REG_BLOCK_SRX]        = {{0xf,0xf}, {D_0, C_3},  {D_0, C_3},  {D_0, C_1}, {D_0, C_2}, {D_0, C_2},  {D_0, C_0}, {D_0, C_0}, {D_0, C_1}}, // See youtrack SPS-160
        [SPICA_REG_BLOCK_SRX_RXL]    = {{0xf,0xf}, {D_0, C_12}, {D_0, C_13}, {D_0, C_5}, {D_0, C_9}, {D_0, C_8},  {D_0, C_1}, {D_0, C_0}, {D_0, C_4}}, // See youtrack SPS-160
        //                                                 6            7            3           5           4            1           0           2    // bump-out ch

        [SPICA_REG_BLOCK_ORX]        = {{0xf,0xf}, {D_0, C_3},  {D_0, C_2},  {D_0, C_1}, {D_0, C_0}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},

        [SPICA_REG_BLOCK_SMTX]       = {{0xf,0xf}, {D_0, C_2},  {D_0, C_3},  {D_0, C_3}, {D_0, C_2}, {D_0, C_1},  {D_0, C_1}, {D_0, C_0}, {D_0, C_0}}, // See youtrack SPS-160
        [SPICA_REG_BLOCK_SMTX_PSR]   = {{0xf,0xf}, {D_0, C_16}, {D_0, C_24}, {D_0, C_25},{D_0, C_17},{D_0, C_8},  {D_0, C_9}, {D_0, C_0}, {D_0, C_1}}, // See youtrack SPS-160
        //                                                 4            6            7           5           2            3           0           1    // bump-out ch

        [SPICA_REG_BLOCK_OTX]        = {{0xf,0xf}, {D_0, C_0},  {D_0, C_1},  {D_0, C_2}, {D_0, C_3}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},

        [SPICA_REG_BLOCK_TOP_ERU]    = {{0xf,0xf}, {D_0, C_0},  {D_0, C_1},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},
    },
    [SPICA_PACKAGE_TYPE_EML_12x13_REV1] = { 
     //                                                                    PACKAGE CHANNEL 
     //                                     0           1            2            3           4          5             6           7           8
     //---------------------------------------------------------------------------------------------------------------------------------------------- 
        [SPICA_REG_BLOCK_NO_CHANNEL] = {{0xf,0xf}, {D_0, C_0},  {D_0, C_1},  {D_0, C_2}, {D_0, C_3}, {D_0, C_4},  {D_0, C_5}, {D_0, C_6}, {D_0, C_7}}, 

        [SPICA_REG_BLOCK_SRX]        = {{0xf,0xf}, {D_0, C_3},  {D_0, C_3},  {D_0, C_2}, {D_0, C_2}, {D_0, C_0},  {D_0, C_0}, {D_0, C_1}, {D_0, C_1}}, // See youtrack SPS-160
        [SPICA_REG_BLOCK_SRX_RXL]    = {{0xf,0xf}, {D_0, C_12}, {D_0, C_13}, {D_0, C_8}, {D_0, C_9}, {D_0, C_0},  {D_0, C_1}, {D_0, C_5}, {D_0, C_4}}, // See youtrack SPS-160
        //                                                 6            7            4           5           0            1           3           2    // bump-out ch
           
        [SPICA_REG_BLOCK_ORX]        = {{0xf,0xf}, {D_0, C_3},  {D_0, C_2},  {D_0, C_1}, {D_0, C_0}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},

        [SPICA_REG_BLOCK_SMTX]       = {{0xf,0xf}, {D_0, C_2},  {D_0, C_2},  {D_0, C_3}, {D_0, C_3}, {D_0, C_1},  {D_0, C_1}, {D_0, C_0}, {D_0, C_0}}, // See youtrack SPS-160
        [SPICA_REG_BLOCK_SMTX_PSR]   = {{0xf,0xf}, {D_0, C_16}, {D_0, C_17}, {D_0, C_24},{D_0, C_25},{D_0, C_8},  {D_0, C_9}, {D_0, C_0}, {D_0, C_1}}, // See youtrack SPS-160
        //                                                 4            5            6           7           2            3           0           1    // bump-out ch
           
        [SPICA_REG_BLOCK_OTX]        = {{0xf,0xf}, {D_0, C_0},  {D_0, C_1},  {D_0, C_2}, {D_0, C_3}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},

        [SPICA_REG_BLOCK_TOP_ERU]    = {{0xf,0xf}, {D_0, C_0},  {D_0, C_1},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},
    },
    [SPICA_PACKAGE_TYPE_STD_10x13] = { 
     //                                                                    PACKAGE CHANNEL 
     //                                     0           1            2            3           4          5             6           7           8
     //---------------------------------------------------------------------------------------------------------------------------------------------- 
        [SPICA_REG_BLOCK_NO_CHANNEL] = {{0xf,0xf}, {D_0, C_0},  {D_0, C_1},  {D_0, C_2}, {D_0, C_3}, {D_0, C_4},  {D_0, C_5}, {D_0, C_6}, {D_0, C_7}}, 

        [SPICA_REG_BLOCK_SRX]        = {{0xf,0xf}, {D_0, C_2},  {D_0, C_2},  {D_0, C_3}, {D_0, C_3}, {D_0, C_0},  {D_0, C_0}, {D_0, C_1}, {D_0, C_1}}, // See youtrack SPS-160
        [SPICA_REG_BLOCK_SRX_RXL]    = {{0xf,0xf}, {D_0, C_8},  {D_0, C_9}, {D_0, C_13},{D_0, C_12}, {D_0, C_0},  {D_0, C_1}, {D_0, C_4}, {D_0, C_5}}, // See youtrack SPS-160
        //                                                 6            7            4           5           0            1           3           2    // bump-out ch
           
        [SPICA_REG_BLOCK_ORX]        = {{0xf,0xf}, {D_0, C_3},  {D_0, C_2},  {D_0, C_1}, {D_0, C_0}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},

        [SPICA_REG_BLOCK_SMTX]       = {{0xf,0xf}, {D_0, C_2},  {D_0, C_2},  {D_0, C_3}, {D_0, C_3}, {D_0, C_1},  {D_0, C_1}, {D_0, C_0}, {D_0, C_0}}, // See youtrack SPS-160
        [SPICA_REG_BLOCK_SMTX_PSR]   = {{0xf,0xf}, {D_0, C_16}, {D_0, C_17}, {D_0, C_24},{D_0, C_25},{D_0, C_8},  {D_0, C_9}, {D_0, C_0}, {D_0, C_1}}, // See youtrack SPS-160
        //                                                 4            5            6           7           2            3           0           1    // bump-out ch
           
        [SPICA_REG_BLOCK_OTX]        = {{0xf,0xf}, {D_0, C_0},  {D_0, C_1},  {D_0, C_2}, {D_0, C_3}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},

        [SPICA_REG_BLOCK_TOP_ERU]    = {{0xf,0xf}, {D_0, C_0},  {D_0, C_1},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf}},
    },
    [SPICA_PACKAGE_TYPE_UNMAPPED] = {  // 0-based
     //                                                                    PACKAGE CHANNEL 
     //                                     0           1            2            3           4          5             6           7           8
     //---------------------------------------------------------------------------------------------------------------------------------------------- 
        [SPICA_REG_BLOCK_NO_CHANNEL] = {{0xf, 0xf}, {D_0, C_0}, {D_0, C_1},  {D_0, C_2},  {D_0, C_3}, {D_0, C_4}, {D_0, C_5},  {D_0, C_6}, {D_0, C_7}}, 

        [SPICA_REG_BLOCK_SRX]        = {{0xf, 0xf}, {D_0, C_0}, {D_0, C_1},  {D_0, C_2},  {D_0, C_3}, {D_0, C_4}, {D_0, C_5},  {D_0, C_6}, {D_0, C_7}}, 
        [SPICA_REG_BLOCK_SRX_RXL]    = {{0xf, 0xf}, {D_0, C_0}, {D_0, C_1},  {D_0, C_2},  {D_0, C_3}, {D_0, C_4}, {D_0, C_5},  {D_0, C_6}, {D_0, C_7}}, 
        
        [SPICA_REG_BLOCK_MRX]        = {{0xf, 0xf}, {D_0, C_0}, {D_0, C_1},  {D_0, C_2},  {D_0, C_3}, {D_0, C_4}, {D_0, C_5},  {D_0, C_6}, {D_0, C_7}}, 
        [SPICA_REG_BLOCK_ORX]        = {{0xf, 0xf}, {D_0, C_0}, {D_0, C_1},  {D_0, C_2},  {D_0, C_3}, {0xf, 0xf}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}},

        [SPICA_REG_BLOCK_SMTX]       = {{0xf, 0xf}, {D_0, C_0}, {D_0, C_1},  {D_0, C_2},  {D_0, C_3}, {D_0, C_4}, {D_0, C_5},  {D_0, C_6}, {D_0, C_7}}, 
        [SPICA_REG_BLOCK_SMTX_PSR]   = {{0xf, 0xf}, {D_0, C_0}, {D_0, C_1},  {D_0, C_2},  {D_0, C_3}, {D_0, C_4}, {D_0, C_5},  {D_0, C_6}, {D_0, C_7}}, 

        [SPICA_REG_BLOCK_OTX]        = {{0xf, 0xf}, {D_0, C_0}, {D_0, C_1},  {D_0, C_2},  {D_0, C_3}, {0xf, 0xf}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}},

        [SPICA_REG_BLOCK_TOP_ERU]    = {{0xf, 0xf}, {D_0, C_0}, {D_0, C_1},  {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}, {0xf, 0xf},  {0xf, 0xf}, {0xf, 0xf}},
    },

    //FIXME: Add additional packages when available
    
};

/**
 * This is an internal structure used to manage the properties with
 * different register blocks to help in re-mapping channel numbers to
 * particular register blocks.
 *
 * @private
 */
typedef struct
{
    /** The instance number of the broadcast register (-1 if it doesn't exist) */
    int             broadcast;
    
    /** The span betweeen instances of the register */
    uint32_t        span;
    
    /** The register block type */
    e_spica_reg_block block;

}spica_channel_info_t;

// A static lookup table containing information about different register
// blocks.
static const spica_channel_info_t spica_ch_info[] = {
    [SPICA_REG_BLOCK_NO_CHANNEL]         = {.broadcast =  0,   .span = 0x800,   .block = SPICA_REG_BLOCK_NO_CHANNEL      },

    [SPICA_REG_BLOCK_SRX]                = {.broadcast =  4,   .span = 0x800,   .block = SPICA_REG_BLOCK_SRX             },
    [SPICA_REG_BLOCK_SRX_RXL]            = {.broadcast = 14,   .span = 0x200,   .block = SPICA_REG_BLOCK_SRX_RXL         },
                                                                                                                         
    [SPICA_REG_BLOCK_MRX]                = {.broadcast =  4,   .span = 0x800,   .block = SPICA_REG_BLOCK_MRX             },
                                                                                                                         
    [SPICA_REG_BLOCK_ORX]                = {.broadcast =  4,   .span = 0x800,   .block = SPICA_REG_BLOCK_ORX             },
                                                                                                                         
    [SPICA_REG_BLOCK_SMTX]               = {.broadcast =  4,   .span = 0x800,   .block = SPICA_REG_BLOCK_SMTX            },
    [SPICA_REG_BLOCK_SMTX_PSR]           = {.broadcast = 14,   .span = 0x100,   .block = SPICA_REG_BLOCK_SMTX_PSR        },
                                                                                                                         
    [SPICA_REG_BLOCK_OTX]                = {.broadcast =  4,   .span = 0x800,   .block = SPICA_REG_BLOCK_OTX             },
                                                                                                                         
    [SPICA_REG_BLOCK_TOP_ERU]            = {.broadcast =  0,   .span = 0x300,   .block = SPICA_REG_BLOCK_TOP_ERU         },

};

/**
 * This method is called to lookup channel information for a particular
 * register address.
 *
 * @param addr [I] - The register access to lookup the channel info for.
 *
 * @return A pointer to the channel info associated with the register block.
 *
 * @private
 */
const spica_channel_info_t* spica_channel_info(
    uint32_t addr)
{
    if (addr < 0x1e1000) {return &spica_ch_info[SPICA_REG_BLOCK_NO_CHANNEL];}
    else if(addr >= 0x1e1000 && addr < 0x1e1010) {return &spica_ch_info[SPICA_REG_BLOCK_SRX];}        // SRX TOP
    else if(addr >= 0x1e1010 && addr < 0x1e1100) {return &spica_ch_info[SPICA_REG_BLOCK_SRX];}        // SRX BIAS
    else if(addr >= 0x1e1100 && addr < 0x1e3800) {return &spica_ch_info[SPICA_REG_BLOCK_SRX_RXL];}    // SRX RXL

    else if(addr >= 0x1e3800 && addr < 0x1e3d80) {return &spica_ch_info[SPICA_REG_BLOCK_MRX];}        // MRX
    else if(addr >= 0x1e3d80 && addr < 0x1e3e80) {return &spica_ch_info[SPICA_REG_BLOCK_MRX];}        // MRX PLL
    else if(addr >= 0x1e3e80 && addr < 0x1e6000) {return &spica_ch_info[SPICA_REG_BLOCK_MRX];}        // MRX BIAS
    
    else if(addr >= 0x1e6000 && addr < 0x1e6580) {return &spica_ch_info[SPICA_REG_BLOCK_ORX];}        // ORX
    else if(addr >= 0x1e6580 && addr < 0x1e6680) {return &spica_ch_info[SPICA_REG_BLOCK_ORX];}        // ORX PLL
    else if(addr >= 0x1e6680 && addr < 0x1e8800) {return &spica_ch_info[SPICA_REG_BLOCK_ORX];}        // ORX BIAS

    else if(addr >= 0x1e8800 && addr < 0x1e8840) {return &spica_ch_info[SPICA_REG_BLOCK_SMTX];}       // SMTX_TOP
    else if(addr >= 0x1e8840 && addr < 0x1e8860) {return &spica_ch_info[SPICA_REG_BLOCK_SMTX];}       // SMTX_FLL
    else if(addr >= 0x1e8860 && addr < 0x1e8880) {return &spica_ch_info[SPICA_REG_BLOCK_SMTX];}       // SMTX_PSR_TOP
    else if(addr >= 0x1e8880 && addr < 0x1e8900) {return &spica_ch_info[SPICA_REG_BLOCK_SMTX];}       // SMTX_PMR_TX_TOP
    else if(addr >= 0x1e8900 && addr < 0x1e8c00) {return &spica_ch_info[SPICA_REG_BLOCK_SMTX_PSR];}   // SMTX_PSR
    else if(addr >= 0x1e8c00 && addr < 0x1e8d00) {return &spica_ch_info[SPICA_REG_BLOCK_SMTX];}       // SMTX_PMR
    else if(addr >= 0x1e8d00 && addr < 0x1e8e00) {return &spica_ch_info[SPICA_REG_BLOCK_SMTX];}       // SMTX_BIAS
    else if(addr >= 0x1e8e00 && addr < 0x1eb000) {return &spica_ch_info[SPICA_REG_BLOCK_SMTX];}       // SMTX_PLL

    else if(addr >= 0x1eb000 && addr < 0x1eb080) {return &spica_ch_info[SPICA_REG_BLOCK_OTX];}        // OTX
    else if(addr >= 0x1eb080 && addr < 0x1eb140) {return &spica_ch_info[SPICA_REG_BLOCK_OTX];}        // OTX_TXA
    else if(addr >= 0x1eb140 && addr < 0x1eb1d0) {return &spica_ch_info[SPICA_REG_BLOCK_OTX];}        // OTX_TXD 
    else if(addr >= 0x1eb1d0 && addr < 0x1eb200) {return &spica_ch_info[SPICA_REG_BLOCK_OTX];}        // OTX_FLL
    else if(addr >= 0x1eb200 && addr < 0x1eb300) {return &spica_ch_info[SPICA_REG_BLOCK_OTX];}        // OTX_BIAS
    else if(addr >= 0x1eb300 && addr < 0x1ed800) {return &spica_ch_info[SPICA_REG_BLOCK_OTX];}        // OTX_PLL

    else if(addr >= 0x1ed800 && addr < 0x1ede00) {return &spica_ch_info[SPICA_REG_BLOCK_TOP_ERU];}    // ERU_TOP_ERU

    return &spica_ch_info[SPICA_REG_BLOCK_NO_CHANNEL];
}

void spica_channel_adjust(
    uint32_t* die, 
    uint32_t* channel, 
    uint32_t* addr, 
    const spica_channel_info_t* info)
{
    *die = spica_package_get_base_die(*die);
    e_spica_package_type pkg_type = spica_package_get_type(*die);

    if(info->block == SPICA_REG_BLOCK_NO_CHANNEL)
    {
        if(*channel != 0)
        {
            INPHI_CRIT("Non-zero channel specified on non-channel register, die 0x%08x, channel %d, addr 0x%08x\n", *die, *channel, *addr);
        }
        return;
    }

    if(*channel == SPICA_BROADCAST_CHANNEL)
    {
        *channel = info->broadcast;
    }
    else
    {
        //for now channels must be > 0, we should replace this with a is_valid call
        if(*channel == 0)
        {
            INPHI_CRIT("Channel 0 invalid, die 0x%08x, channel %d, addr 0x%08x, block %d\n", *die, *channel, *addr, info->block);
            return;
        }

        //INPHI_NOTE("Adjust channel %d for interface %d\n", *channel, info->block);
        // Channel re-mapping
        // Handle all package variants in LUT
        //INPHI_NOTE("pkg_type=%d, info->block=%d, channel=%d\n", pkg_type, info->block, *channel);

        *die    += reg_block_map[pkg_type][info->block][*channel][0]; 
        *channel = reg_block_map[pkg_type][info->block][*channel][1];
        //INPHI_NOTE("die=0x%x, channel=%d\n", *die, *channel);
    }
}

/**
 * This method is called to manage re-mapping the channel based on
 * the register address being accessed.
 *
 * @param die     [I/O] - The die being accessed. This may be modified depending
 *                        on which channel in a multi-die package is being
 *                        accessed.
 * @param channel [I/O] - The channel through the device being accessed. This
 *                        may be re-mapped based on the package type.
 *
 * @param addr    [I/O] - The address of the register being accessed. This
 *                        may be re-mapped based on the pacakge type and channel.
 *
 */
inphi_status_t spica_rebase_by_addr(
    uint32_t* die, 
    uint32_t* channel, 
    uint32_t* addr)
{
    inphi_status_t status = INPHI_OK;

    const spica_channel_info_t* info = spica_channel_info(*addr);

    spica_channel_adjust(die, channel, addr, info);
    
    *addr = *addr + (*channel * info->span);
  
    return status;

}

/**
 * This method is called to manage re-mapping the channel based on
 * the register interface being accessed.
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
 */
inphi_status_t spica_rebase_channel_by_intf(uint32_t* die, uint32_t* channel, uint32_t intf)
{
    inphi_status_t status = INPHI_OK;
    

    e_spica_package_type package_type = spica_package_get_type(*die);

    // If the die hasn't been cached save it here to avoid looking it up
    // continuously.
    *die = spica_package_type_set_in_die(*die, package_type);

    const spica_channel_info_t* info = NULL;

    switch(intf)
    {
        case SPICA_INTF_OTX:
            info = &spica_ch_info[SPICA_REG_BLOCK_OTX];
            break;
        case SPICA_INTF_ORX:
            info = &spica_ch_info[SPICA_REG_BLOCK_ORX];
            break;
        case SPICA_INTF_MTX:
            info = &spica_ch_info[SPICA_REG_BLOCK_SMTX];
            break;
        case SPICA_INTF_MRX:
            info = &spica_ch_info[SPICA_REG_BLOCK_MRX];
            break;
        case SPICA_INTF_STX:
            info = &spica_ch_info[SPICA_REG_BLOCK_SMTX_PSR];
            break;
        case SPICA_INTF_SRX:
            info = &spica_ch_info[SPICA_REG_BLOCK_SRX_RXL];
            break;
        default:
            return INPHI_ERROR;
    }
    uint32_t* addr=0;
    spica_channel_adjust(die, channel, addr, info);

    return status;

}
 
/**
 * This method is used to re-map the address for particular register based
 * on the ASIC package type.
 *
 * @param die     [I] - The physical ASIC die being accessed.
 * @param channel [I] - The channel being accessed.
 * @param addr    [I] - The address of the register being accessed.
 *
 * @return The corrected register channel for the target channel.
 */
uint32_t spica_reg_channel_addr(
    uint32_t die, 
    uint32_t channel, 
    uint32_t addr)
{
    spica_rebase_by_addr(&die, &channel, &addr);
    return addr;
};

/**
 * This method is used for writing to a register associated with a particular
 * channel in the package. The registers are actually only 16 bits but 32b is
 * used for internal validation purposes. The extra bits about 0xffff
 * are ignored.
 *
 * @param die  [I] - The physical ASIC die being accessed.
 * @param addr [I] - The address of the register being accessed.
 * @param data [I] - The data to write to the register.
 */
void spica_reg_channel_write(
    uint32_t die, 
    uint32_t channel, 
    uint32_t addr, 
    uint32_t data)
{
    spica_rebase_by_addr(&die, &channel, &addr);
    //INPHI_PRINTF("  spica_reg_channel_write: die=%x, channel=%d, addr=%x\n", die, channel, addr);
    
    spica_reg_write(die, addr, data);
}

/**
 * This method is called to read a register for a particular channel through
 * the ASIC.
 *
 * @param die  [I] - The physical ASIC die being accessed.
 * @param addr [I] - The address of the register being accessed.
 * 
 * @return The data read back from the register.
 */
uint32_t spica_reg_channel_read(
    uint32_t die, 
    uint32_t channel, 
    uint32_t addr)
{
    spica_rebase_by_addr(&die, &channel, &addr);

    //INPHI_PRINTF("  spica_reg_channel_read: die=%x, channel=%d, addr=%x\n", die, channel, addr);
    return spica_reg_read(die, addr);
}

/**
 * This method is called to perform a read/modify/write operation
 * on a register for a particular channel through the ASIC. This is used to
 * modify bitfields within a register.
 *
 * @param die  [I] - The physical ASIC die being accessed.
 * @param addr [I] - The address of the register being accessed.
 * @param data [I] - The data to write to the register.
 * @param mask [I] - A mask to ignore unsed bits.
 * 
 * @return The modified register value.
 */
uint32_t spica_reg_channel_rmw(
    uint32_t die, 
    uint32_t channel, 
    uint32_t addr, 
    uint32_t data, 
    uint32_t mask)
{
    spica_rebase_by_addr(&die, &channel, &addr);

    return spica_reg_rmw(die, addr, data, mask);
}

/*
 * Wrapper method that sets a registermodules/comms/spica_reg_access.c
 */
void spica_reg_write(
    uint32_t die, 
    uint32_t addr, 
    uint32_t data)
{
    uint32_t tmp;

    tmp = (uint32_t)(data & 0xffff);
    spica_reg_set(die, addr, tmp);
}

/*
 * Wrapper method that gets a register
 */
uint32_t spica_reg_read(
    uint32_t die, 
    uint32_t addr)
{
    uint32_t tmp;
    uint32_t data = 0;

    spica_reg_get(die, addr, &tmp);
    data = (uint16_t)(tmp & 0xffff);

    return data;
}

/* Perform a read/modify/write operation to modify a bitfield */
uint32_t spica_reg_rmw(
    uint32_t die, 
    uint32_t addr, 
    uint32_t data, 
    uint32_t mask)
{
    spica_lock(die);
    uint32_t tmp = spica_reg_read(die, addr);
    tmp &= ~mask;
    tmp |= data & mask;
    spica_reg_write(die, addr, tmp);
    spica_unlock(die);
    return tmp;
}

/*
 * This method may be called to return the die and register instance of
 * the selected package channel. This may be called from the link_status
 * method or the GUIs dashboard tab.
 */
uint32_t spica_get_die_inst_from_pkg_ch(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf)
{
    e_spica_package_type pkg_type = spica_package_get_type(die);
    uint32_t addr;
    uint32_t inst;

    switch (intf)
    {
        case SPICA_INTF_ORX:
            addr = SPICA_ORX_DDP_CHK_CFG__ADDRESS;
            break;
        case SPICA_INTF_OTX:
            addr = SPICA_OTX_TXD_CLKEN__ADDRESS;
            break;
        case SPICA_INTF_MRX:
            addr = SPICA_MRX_DDP_CHK_CFG__ADDRESS;
            break;
        case SPICA_INTF_MTX:
            addr = SPICA_SMTX_PMR_TXD_CLKEN__ADDRESS;
            break;
        case SPICA_INTF_SRX:
            addr = SPICA_SRX_RXD_CLKEN__ADDRESS;
            break;
        case SPICA_INTF_STX:
            addr = SPICA_SMTX_PSR_TXD_CLKEN__ADDRESS;
            break;
        default:
            INPHI_CRIT("Invalid interface=%d\n", intf);
            return 0;
            break;
    }

    const spica_channel_info_t* info = spica_channel_info(addr);

    // INPHI_NOTE("[pkg_type][info->block][channel]=%d,%d,%d\n", pkg_type,info->block,channel);

    die  = reg_block_map[pkg_type][info->block][channel][0]; 
    inst = reg_block_map[pkg_type][info->block][channel][1];

    if ((die == 0xf) && (inst == 0xf))
    {
        INPHI_CRIT("Invalid pkg channel, pkg type:%s, info->block:%d, channel:%d\n", 
                    spica_dbg_translate_package_type(pkg_type), info->block, channel);
        return 0;
    }
    // For PSR, the reg_block_map table contains a die and reg offset. 
    // The reg offset is different from the reg instance.

    if (intf == SPICA_INTF_SRX)
    {
        static const uint8_t srx_inst_xlate[14] = 
            // 0, 1,  2,  3, 4, 5,  6,  7, 8, 9, 10, 11, 12,13   // reg address offset
            {  0, 1,255,255, 3, 4,255,255, 6, 7,255,255,  9,10}; // reg instance
        inst = srx_inst_xlate[inst];
    }
    if (intf == SPICA_INTF_STX)
    {
        static const uint8_t stx_inst_xlate[26] = 
            // 0, 1,  2,  3,  4,  5,  6,  7, 8, 9, 10 ,11, 12, 13 ,14, 15,16,17, 18, 19, 20, 21, 22, 23,24,25   // reg address offset
            {  0, 1,255,255,255,255,255,255, 3, 4,255,255,255,255,255,255, 6, 7,255,255,255,255,255,255, 9,10}; // reg instance
        inst = stx_inst_xlate[inst];
    }

    return (((die & 1 ) << 16) | inst);
}

/** @file spica_prbs.c
 ****************************************************************************
 *
 * @brief
 *     This module contains the implementation of the PRBS interface
 *     on the Spica ASIC.
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

/*
 * Define the default PRBS generator rules 
 */
static const spica_prbs_gen_rules_t spica_prbs_gen_rules_default =
{
    // generator rules
    .en               = true,
    .gen_en_lsb       = false,
    .prbs_mode        = SPICA_PRBS_MODE_COMBINED,
    .prbs_pattern_lsb = SPICA_PAT_PRBS31,
    .prbs_pattern     = SPICA_PAT_PRBS31,
    .pattern_mode     = SPICA_PRBS_PATTERN_PRBS,
    .nrz_mode         = false,
    .seed_evn_0       = 0x3333,
    .seed_evn_1       = 0x3333,
    .seed_evn_2       = 0x3333,
    .seed_evn_3       = 0x3333,
    .seed_odd_0       = 0x3333,
    .seed_odd_1       = 0x3333,
    .seed_odd_2       = 0x3333,
    .seed_odd_3       = 0x3333
};

/*
 * Define the default PRBS checker rules 
 */
static const spica_prbs_chk_rules_t spica_prbs_chk_rules_default =
{
    // generic checker rules
    .en                   = true,
    .prbs_mode            = SPICA_PRBS_MODE_MSB_LSB,
    .prbs_inv             = false,
    .prbs_pattern_lsb     = SPICA_PAT_PRBS31,
    .prbs_pattern         = SPICA_PAT_PRBS31,
    .nrz_mode             = false,
    .auto_polarity_en     = true,
    .auto_polarity_thresh = SPICA_PRBS_AUTO_POLARITY_9,
    .pattern_mode         = SPICA_PRBS_PATTERN_PRBS,
    .fixed_pat0           = 0x3333,
    .fixed_pat1           = 0x3333,
    .fixed_pat2           = 0x3333,
    .fixed_pat3           = 0x3333,
    .oos_thresh           = 15 
};

/**
 * Returns the PRBS pattern string
 */

const char* spica_prbs_translate_pat(
    e_spica_prbs_pat pattern) 
{ 
    switch (pattern)
    {
        case SPICA_PAT_PRBS31:  return ("PRBS31");
        case SPICA_PAT_PRBS7:   return ("PRBS7");
        case SPICA_PAT_PRBS9_5: return ("PRBS9_5");
        case SPICA_PAT_PRBS9_4: return ("PRBS9_4");
        case SPICA_PAT_PRBS11:  return ("PRBS11");
        case SPICA_PAT_PRBS13:  return ("PRBS13");
        case SPICA_PAT_PRBS15:  return ("PRBS15");
        case SPICA_PAT_PRBS23:  return ("PRBS23");
        case SPICA_PAT_PRBS58:  return ("PRBS58");
        case SPICA_PAT_PRBS16:  return ("PRBS16");
        default:              return ("None");
            break;
    }
    return ("???");
}

/*
 * Converts the synthetic PRBS pattern to the HW pattern
 */ 
uint16_t spica_prbs_get_hdwr_pat(
    e_spica_prbs_pat pattern)
{
    switch(pattern)
    {
        case SPICA_PAT_PRBS31:  return 0;
        case SPICA_PAT_PRBS7:   return 1;
        case SPICA_PAT_PRBS9_5: return 2;
        case SPICA_PAT_PRBS9_4: return 3;
        case SPICA_PAT_PRBS11:  return 4;
        case SPICA_PAT_PRBS13:  return 5;
        case SPICA_PAT_PRBS15:  return 6;
        case SPICA_PAT_PRBS23:  return 7;
        case SPICA_PAT_PRBS58:  return 8;
        case SPICA_PAT_PRBS16:  return 9;
        default:              return 0;
    }
}

/*
 * Configure the default PRBS generator rules
 */ 
inphi_status_t spica_prbs_gen_rules_default_set(
    spica_prbs_gen_rules_t* gen_rules)
{
    if(!gen_rules)
    {
        INPHI_NOTE("PRBS Generator rules pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }
    
    INPHI_MEMCPY(gen_rules, &spica_prbs_gen_rules_default, sizeof(spica_prbs_gen_rules_t));

    return INPHI_OK;
}

/**
 * This method is called to inject errors into the TX datapath.
 */ 
inphi_status_t spica_prbs_gen_error_inject(
    uint32_t             die,
    uint32_t             channel,
    e_spica_intf         intf,
    bool                 enable,
    e_spica_prbs_err_inj_pat pattern,
    uint8_t              gap,
    uint8_t              duration)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data0, data1, cfg0_mask, cfg1_mask;

    SPICA_LOCK(die);

    if (enable)
    {
        // de-assert the enable
        data0 = SPICA_VAL(SPICA_OTX_TXD_ERRINJ_CFG0__ENABLE,  0   ) |
                SPICA_VAL(SPICA_OTX_TXD_ERRINJ_CFG0__PATTERN, pattern);
        cfg0_mask = SPICA_MASK(SPICA_OTX_TXD_ERRINJ_CFG0__ENABLE ) |
               SPICA_MASK(SPICA_OTX_TXD_ERRINJ_CFG0__PATTERN);

        data1 = SPICA_VAL(SPICA_OTX_TXD_ERRINJ_CFG1__GAP,  gap    ) |
                SPICA_VAL(SPICA_OTX_TXD_ERRINJ_CFG1__DURATION, duration);
        cfg1_mask = SPICA_MASK(SPICA_OTX_TXD_ERRINJ_CFG1__GAP    ) |
               SPICA_MASK(SPICA_OTX_TXD_ERRINJ_CFG1__DURATION);

        if (SPICA_INTF_OTX == intf)
        {
            // Make sure we turn on the clock first
            SPICA_OTX_TXD_CLKEN__INJ__RMW(die, channel, 1);
            spica_reg_channel_rmw(die, channel, SPICA_ADDRESS(SPICA_OTX_TXD_ERRINJ_CFG0), data0, cfg0_mask);
            spica_reg_channel_rmw(die, channel, SPICA_ADDRESS(SPICA_OTX_TXD_ERRINJ_CFG1), data1, cfg1_mask);
            //Assert / clear the enable
            SPICA_OTX_TXD_ERRINJ_CFG0__ENABLE__RMW(die, channel, enable);
        }
#if !defined(INPHI_REMOVE_PMR)
        else if (SPICA_INTF_MTX == intf)
        {
            // Make sure we turn on the clock first
            SPICA_SMTX_PMR_TXD_CLKEN__INJ__RMW(die, channel, 1);
            spica_reg_channel_rmw(die, channel, SPICA_ADDRESS(SPICA_SMTX_PMR_TXD_ERRINJ_CFG0), data0, cfg0_mask);
            spica_reg_channel_rmw(die, channel, SPICA_ADDRESS(SPICA_SMTX_PMR_TXD_ERRINJ_CFG1), data1, cfg1_mask);
            //Assert / clear the enable
            SPICA_SMTX_PMR_TXD_ERRINJ_CFG0__ENABLE__RMW(die, channel, enable);
        }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
        else if (SPICA_INTF_STX == intf)
        {
            // Make sure we turn on the clock first
            SPICA_SMTX_PSR_TXD_CLKEN__INJ__RMW(die, channel, 1);
            spica_reg_channel_rmw(die, channel, SPICA_ADDRESS(SPICA_SMTX_PSR_TXD_ERRINJ_CFG0), data0, cfg0_mask);
            spica_reg_channel_rmw(die, channel, SPICA_ADDRESS(SPICA_SMTX_PSR_TXD_ERRINJ_CFG1), data1, cfg1_mask);
            //Assert / clear the enable
            SPICA_SMTX_PSR_TXD_ERRINJ_CFG0__ENABLE__RMW(die, channel, enable);
        }
#endif // defined(INPHI_REMOVE_PSR)
        else
        {
            INPHI_NOTE("Generator interface must be one of OTX, MTX or STX!\n");
            status |= INPHI_ERROR;
        }
    }

    if (!enable)
    {
        // turn off the clock
        if (SPICA_INTF_OTX == intf)
        {
            SPICA_OTX_TXD_CLKEN__INJ__RMW(die, channel, 0);
        }
#if !defined(INPHI_REMOVE_PMR)
        else if (SPICA_INTF_MTX == intf)
        {
            SPICA_SMTX_PMR_TXD_CLKEN__INJ__RMW(die, channel, 0);
        }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
        else if (SPICA_INTF_STX == intf)
        {
            SPICA_SMTX_PSR_TXD_CLKEN__INJ__RMW(die, channel, 0);
        }
#endif // defined(INPHI_REMOVE_PSR)
        else
        {
            INPHI_NOTE("Generator interface must be one of OTX, MTX or STX!\n");
            status |= INPHI_ERROR;
        }
    }

    SPICA_UNLOCK(die);

    return status;
}

/*
 * Configure the PRBS generator
 */ 
inphi_status_t spica_prbs_gen_config(
    uint32_t      die, 
    uint32_t      channel, 
    e_spica_intf  intf,
    spica_prbs_gen_rules_t* gen_rules)
{
    inphi_status_t status = INPHI_OK;
    
    if(!gen_rules)
    {
        INPHI_NOTE("PRBS Generator gen_rules pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    uint16_t data = 0;

    SPICA_LOCK(die);

    if (SPICA_INTF_OTX == intf)
    {
        if (gen_rules->en == false)
        {
            //INPHI_NOTE("Turning OFF the %s PRBS generator for Die=%x Channel=%d\n", label, die, channel);
            SPICA_OTX_TXD_CLKEN__GEN__RMW(die, channel, 0);
            SPICA_OTX_TXD_CLKEN__INJ__RMW(die, channel, 1);
            SPICA_OTX_TXD_GEN_CFG__WRITE(die, channel, 0);
        }
        else
        {
            //INPHI_NOTE("Turning ON the %s PRBS generator for Die=%x Channel=%d\n", label, die, channel);
            SPICA_OTX_TXD_CLKEN__GEN__RMW(die, channel, 1);

            // Put the generator in reset when the configuration is being changed
            SPICA_OTX_TXD_RESET__GEN__RMW(die, channel, 1);
            
            data = SPICA_VAL(SPICA_OTX_TXD_GEN_CFG__DUAL_PRBS,     (gen_rules->prbs_mode != SPICA_PRBS_MODE_COMBINED)  ) |
                   SPICA_VAL(SPICA_OTX_TXD_GEN_CFG__GEN_EN,        gen_rules->en                                       ) |
                   SPICA_VAL(SPICA_OTX_TXD_GEN_CFG__GEN_EN_ODD,    gen_rules->gen_en_lsb                               ) |
                   SPICA_VAL(SPICA_OTX_TXD_GEN_CFG__PRBS_MODE_ODD, spica_prbs_get_hdwr_pat(gen_rules->prbs_pattern_lsb)) |
                   SPICA_VAL(SPICA_OTX_TXD_GEN_CFG__PRBS_MODE,     spica_prbs_get_hdwr_pat(gen_rules->prbs_pattern)    ) |
                   SPICA_VAL(SPICA_OTX_TXD_GEN_CFG__PATTERN_MODE,  gen_rules->pattern_mode                             ) |
                   SPICA_VAL(SPICA_OTX_TXD_GEN_CFG__NRZ_MODE,      gen_rules->nrz_mode                                 );

            SPICA_OTX_TXD_GEN_CFG__WRITE(die, channel, data);

            // Toggle to de-sync the MSB and LSB generator streams when in dual PRBS mode
            if (gen_rules->gen_en_lsb)
            {
                SPICA_OTX_TXD_GEN_CFG__GEN_EN_ODD__RMW(die, channel, 0);
                SPICA_OTX_TXD_GEN_CFG__GEN_EN_ODD__RMW(die, channel, 1);
            }

            if (SPICA_PRBS_PATTERN_FIXED == gen_rules->pattern_mode)
            {
                SPICA_OTX_TXD_GEN_SEEDE_FIX0_CFG0__WRITE(die, channel, gen_rules->seed_evn_0);
                SPICA_OTX_TXD_GEN_SEEDE_FIX0_CFG1__WRITE(die, channel, gen_rules->seed_evn_1);
                SPICA_OTX_TXD_GEN_SEEDE_FIX0_CFG2__WRITE(die, channel, gen_rules->seed_evn_2);
                SPICA_OTX_TXD_GEN_SEEDE_FIX0_CFG3__WRITE(die, channel, gen_rules->seed_evn_3);
                /* repeat the pattern for the 2nd 64-bit word */
                SPICA_OTX_TXD_GEN_SEEDO_FIX1_CFG0__WRITE(die, channel, gen_rules->seed_odd_0);
                SPICA_OTX_TXD_GEN_SEEDO_FIX1_CFG1__WRITE(die, channel, gen_rules->seed_odd_1);
                SPICA_OTX_TXD_GEN_SEEDO_FIX1_CFG2__WRITE(die, channel, gen_rules->seed_odd_2);
                SPICA_OTX_TXD_GEN_SEEDO_FIX1_CFG3__WRITE(die, channel, gen_rules->seed_odd_3);
            }
            // Take the generator out of reset after the pattern has been updated
            SPICA_OTX_TXD_RESET__GEN__RMW(die, channel, 0);
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (SPICA_INTF_MTX == intf)
    {
        if (gen_rules->en == false)
        {
            //INPHI_NOTE("Turning OFF the %s PRBS generator for Die=%x Channel=%d\n", label, die, channel);
            SPICA_SMTX_PMR_TXD_CLKEN__GEN__RMW(die, channel, 0);
            SPICA_SMTX_PMR_TXD_CLKEN__INJ__RMW(die, channel, 1);
            SPICA_SMTX_PMR_TXD_GEN_CFG__WRITE(die, channel, 0);
        }
        else
        {
            //INPHI_NOTE("Turning ON the %s PRBS generator for Die=%x Channel=%d\n", label, die, channel);
            SPICA_SMTX_PMR_TXD_CLKEN__GEN__RMW(die, channel, 1);

            // Put the generator in reset when the configuration is being changed
            SPICA_SMTX_PMR_TXD_RESET__GEN__RMW(die, channel, 1);
            
            data = SPICA_VAL(SPICA_SMTX_PMR_TXD_GEN_CFG__DUAL_PRBS,     (gen_rules->prbs_mode != SPICA_PRBS_MODE_COMBINED)  ) |
                   SPICA_VAL(SPICA_SMTX_PMR_TXD_GEN_CFG__GEN_EN,        gen_rules->en                                       ) |
                   SPICA_VAL(SPICA_SMTX_PMR_TXD_GEN_CFG__GEN_EN_ODD,    gen_rules->gen_en_lsb                               ) |
                   SPICA_VAL(SPICA_SMTX_PMR_TXD_GEN_CFG__PRBS_MODE_ODD, spica_prbs_get_hdwr_pat(gen_rules->prbs_pattern_lsb)) |
                   SPICA_VAL(SPICA_SMTX_PMR_TXD_GEN_CFG__PRBS_MODE,     spica_prbs_get_hdwr_pat(gen_rules->prbs_pattern)    ) |
                   SPICA_VAL(SPICA_SMTX_PMR_TXD_GEN_CFG__PATTERN_MODE,  gen_rules->pattern_mode                             ) |
                   SPICA_VAL(SPICA_SMTX_PMR_TXD_GEN_CFG__NRZ_MODE,      gen_rules->nrz_mode                                 );

            SPICA_SMTX_PMR_TXD_GEN_CFG__WRITE(die, channel, data);

            // Toggle to de-sync the MSB and LSB generator streams when in dual PRBS mode
            if (gen_rules->gen_en_lsb)
            {
                SPICA_SMTX_PMR_TXD_GEN_CFG__GEN_EN_ODD__RMW(die, channel, 0);
                SPICA_SMTX_PMR_TXD_GEN_CFG__GEN_EN_ODD__RMW(die, channel, 1);
            }

            if (SPICA_PRBS_PATTERN_FIXED == gen_rules->pattern_mode)
            {
                SPICA_SMTX_PMR_TXD_GEN_SEEDE_FIX0_CFG0__WRITE(die, channel, gen_rules->seed_evn_0);
                SPICA_SMTX_PMR_TXD_GEN_SEEDE_FIX0_CFG1__WRITE(die, channel, gen_rules->seed_evn_1);
                SPICA_SMTX_PMR_TXD_GEN_SEEDE_FIX0_CFG2__WRITE(die, channel, gen_rules->seed_evn_2);
                SPICA_SMTX_PMR_TXD_GEN_SEEDE_FIX0_CFG3__WRITE(die, channel, gen_rules->seed_evn_3);
                /* repeat the pattern for the 2nd 64-bit word */
                SPICA_SMTX_PMR_TXD_GEN_SEEDO_FIX1_CFG0__WRITE(die, channel, gen_rules->seed_odd_0);
                SPICA_SMTX_PMR_TXD_GEN_SEEDO_FIX1_CFG1__WRITE(die, channel, gen_rules->seed_odd_1);
                SPICA_SMTX_PMR_TXD_GEN_SEEDO_FIX1_CFG2__WRITE(die, channel, gen_rules->seed_odd_2);
                SPICA_SMTX_PMR_TXD_GEN_SEEDO_FIX1_CFG3__WRITE(die, channel, gen_rules->seed_odd_3);
            }
            // Take the generator out of reset after the pattern has been updated
            SPICA_SMTX_PMR_TXD_RESET__GEN__RMW(die, channel, 0);
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    else if (SPICA_INTF_STX == intf)
    {
        if (gen_rules->en == false)
        {
            //INPHI_NOTE("Turning OFF the %s PRBS generator for Die=%x Channel=%d\n", label, die, channel);
            SPICA_SMTX_PSR_TXD_CLKEN__GEN__RMW(die, channel, 0);
            SPICA_SMTX_PSR_TXD_CLKEN__INJ__RMW(die, channel, 1);
            SPICA_SMTX_PSR_TXD_GEN_CFG__WRITE(die, channel, 0);
        }
        else
        {
            //INPHI_NOTE("Turning ON the %s PRBS generator for Die=%x Channel=%d\n", label, die, channel);
            SPICA_SMTX_PSR_TXD_CLKEN__GEN__RMW(die, channel, 1);

            // Put the generator in reset when the configuration is being changed
            SPICA_SMTX_PSR_TXD_RESET__GEN__RMW(die, channel, 1);
            
            data = SPICA_VAL(SPICA_SMTX_PSR_TXD_GEN_CFG__DUAL_PRBS,     (gen_rules->prbs_mode != SPICA_PRBS_MODE_COMBINED)  ) |
                   SPICA_VAL(SPICA_SMTX_PSR_TXD_GEN_CFG__GEN_EN,        gen_rules->en                                       ) |
                   SPICA_VAL(SPICA_SMTX_PSR_TXD_GEN_CFG__GEN_EN_ODD,    gen_rules->gen_en_lsb                               ) |
                   SPICA_VAL(SPICA_SMTX_PSR_TXD_GEN_CFG__PRBS_MODE_ODD, spica_prbs_get_hdwr_pat(gen_rules->prbs_pattern_lsb)) |
                   SPICA_VAL(SPICA_SMTX_PSR_TXD_GEN_CFG__PRBS_MODE,     spica_prbs_get_hdwr_pat(gen_rules->prbs_pattern)    ) |
                   SPICA_VAL(SPICA_SMTX_PSR_TXD_GEN_CFG__PATTERN_MODE,  gen_rules->pattern_mode                             ) |
                   SPICA_VAL(SPICA_SMTX_PSR_TXD_GEN_CFG__NRZ_MODE,      gen_rules->nrz_mode                                 );

            SPICA_SMTX_PSR_TXD_GEN_CFG__WRITE(die, channel, data);

            // Toggle to de-sync the MSB and LSB generator streams when in dual PRBS mode
            if (gen_rules->gen_en_lsb)
            {
                SPICA_SMTX_PSR_TXD_GEN_CFG__GEN_EN_ODD__RMW(die, channel, 0);
                SPICA_SMTX_PSR_TXD_GEN_CFG__GEN_EN_ODD__RMW(die, channel, 1);
            }

            if (SPICA_PRBS_PATTERN_FIXED == gen_rules->pattern_mode)
            {
                SPICA_SMTX_PSR_TXD_GEN_SEEDE_FIX0_CFG0__WRITE(die, channel, gen_rules->seed_evn_0);
                SPICA_SMTX_PSR_TXD_GEN_SEEDE_FIX0_CFG1__WRITE(die, channel, gen_rules->seed_evn_1);
                SPICA_SMTX_PSR_TXD_GEN_SEEDE_FIX0_CFG2__WRITE(die, channel, gen_rules->seed_evn_2);
                SPICA_SMTX_PSR_TXD_GEN_SEEDE_FIX0_CFG3__WRITE(die, channel, gen_rules->seed_evn_3);
                /* repeat the pattern for the 2nd 64-bit word */
                SPICA_SMTX_PSR_TXD_GEN_SEEDO_FIX1_CFG0__WRITE(die, channel, gen_rules->seed_odd_0);
                SPICA_SMTX_PSR_TXD_GEN_SEEDO_FIX1_CFG1__WRITE(die, channel, gen_rules->seed_odd_1);
                SPICA_SMTX_PSR_TXD_GEN_SEEDO_FIX1_CFG2__WRITE(die, channel, gen_rules->seed_odd_2);
                SPICA_SMTX_PSR_TXD_GEN_SEEDO_FIX1_CFG3__WRITE(die, channel, gen_rules->seed_odd_3);
            }
            // Take the generator out of reset after the pattern has been updated
            SPICA_SMTX_PSR_TXD_RESET__GEN__RMW(die, channel, 0);
        }
    }
#endif // defined(INPHI_REMOVE_PSR)
    else
    {
        INPHI_NOTE("Generator interface must be one of OTX, MTX or STX!\n");
        status |= INPHI_ERROR;
    }

    SPICA_UNLOCK(die);

    return status;

}

/*
 * Configure the default PRBS checker rules
 */ 
inphi_status_t spica_prbs_chk_rules_default_set(
    spica_prbs_chk_rules_t* chk_rules)
{
    if(!chk_rules)
    {
        INPHI_NOTE("PRBS Checker rules pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    INPHI_MEMCPY(chk_rules, &spica_prbs_chk_rules_default, sizeof(spica_prbs_chk_rules_t));

    return INPHI_OK;
}

bool spica_prbs_chk_is_enabled(
    uint32_t      die, 
    uint32_t      channel,
    e_spica_intf  intf) 
{
    bool enabled = false;

    SPICA_LOCK(die);

    if (SPICA_INTF_ORX == intf) 
    {
        // Check the clock gate
        bool clocked = SPICA_ORX_TOP_CLKEN__CHK__READ(die, channel);
        if(clocked)
        {
            // Then check whether the PRBS is enabled
            enabled = SPICA_ORX_DDP_CHK_CFG__PRBS_EN__READ(die, channel);
        }
    }
#if !defined(INPHI_REMOVE_PMR) 
    else if (SPICA_INTF_MRX == intf)
    {
        // Check the clock gate
        bool clocked = SPICA_MRX_TOP_CLKEN__CHK__READ(die, channel);
        if(clocked)
        {
            // Then check whether the PRBS is enabled
            enabled = SPICA_MRX_DDP_CHK_CFG__PRBS_EN__READ(die, channel);
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR) 
    else if (SPICA_INTF_SRX == intf)
    {
        // Check the clock gate
        bool clocked = SPICA_SRX_RXD_CLKEN__CHK__READ(die, channel);
        if(clocked)
        {
            // Then check whether the PRBS is enabled
            enabled = SPICA_SRX_RXD_DP_CHK_CFG__PRBS_EN__READ(die, channel);
        }
    }
#endif // defined(INPHI_REMOVE_PSR)
    else
    {
        INPHI_NOTE("Checker interface must be one of ORX, MRX or SRX!\n");
    }

    SPICA_UNLOCK(die);

    return enabled;
}

/* 
 * Configure the PRBS checker
 */
inphi_status_t spica_prbs_chk_config(
    uint32_t      die, 
    uint32_t      channel,
    e_spica_intf  intf,
    spica_prbs_chk_rules_t* chk_rules)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data;

    if(!chk_rules)
    {
        INPHI_CRIT("PRBS Checker chk_rules pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    uint16_t chk_offset = 0;

    if (SPICA_INTF_ORX == intf) 
    {
        chk_offset = SPICA_ADDR_DIFF(SPICA_SRX_RXD_DP_CHK_CFG, SPICA_ORX_DDP_CHK_CFG);
    }
#if !defined(INPHI_REMOVE_PMR) 
    else if (SPICA_INTF_MRX == intf)
    {
        chk_offset = SPICA_ADDR_DIFF(SPICA_SRX_RXD_DP_CHK_CFG, SPICA_MRX_DDP_CHK_CFG);
    }
#endif // defined(INPHI_REMOVE_PMR) 
#if !defined(INPHI_REMOVE_PSR) 
    else if (SPICA_INTF_SRX == intf)
    {
        chk_offset = 0;
    }
#endif // defined(INPHI_REMOVE_PSR)
    else
    {
        INPHI_NOTE("Checker interface must be one of ORX, MRX or SRX!\n");
        return (INPHI_ERROR);
    }

    SPICA_LOCK(die);

    if (chk_rules->en == false) 
    { 
        if (SPICA_INTF_ORX == intf)
        {
            SPICA_ORX_DDP_CHK_CFG__PRBS_EN__RMW(die, channel, 0);
            SPICA_ORX_TOP_CLKEN__CHK__RMW(die, channel, 0);
        }
#if !defined(INPHI_REMOVE_PMR) 
        else if (SPICA_INTF_MRX == intf)
        {
            SPICA_MRX_DDP_CHK_CFG__PRBS_EN__RMW(die, channel, 0);
            SPICA_MRX_TOP_CLKEN__CHK__RMW(die, channel, 0);
        }
#endif // defined(INPHI_REMOVE_PMR) 
#if !defined(INPHI_REMOVE_PSR) 
        else if (SPICA_INTF_SRX == intf)
        {
            SPICA_SRX_RXD_DP_CHK_CFG__PRBS_EN__RMW(die, channel, 0);
            data = SPICA_SRX_RXD_CLKEN__READ(die, channel);
            data = SPICA_SRX_RXD_CLKEN__CHK__SET(data, 0);
            //always turn the DSP clock back on
            data = SPICA_SRX_RXD_CLKEN__DSP__SET(data, 1);
            SPICA_SRX_RXD_CLKEN__WRITE(die, channel, data);
            
        }
#endif // defined(INPHI_REMOVE_PSR)
    }
    else // (chk_rules->en == true) 
    {
        if (SPICA_INTF_ORX == intf)
        {
            SPICA_ORX_TOP_RESET__CHK__RMW(die, channel, 0);
            SPICA_ORX_TOP_RESET__CHK__RMW(die, channel, 1);
            SPICA_ORX_TOP_RESET__CHK__RMW(die, channel, 0);
            SPICA_ORX_TOP_CLKEN__CHK__RMW(die, channel, 1);
        }
#if !defined(INPHI_REMOVE_PMR) 
        else if (SPICA_INTF_MRX == intf)
        {
            SPICA_MRX_TOP_RESET__CHK__RMW(die, channel, 0);
            SPICA_MRX_TOP_RESET__CHK__RMW(die, channel, 1);
            SPICA_MRX_TOP_RESET__CHK__RMW(die, channel, 0);
            SPICA_MRX_TOP_CLKEN__CHK__RMW(die, channel, 1);
        }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR) 
        else if (SPICA_INTF_SRX == intf)
        {
            data = SPICA_SRX_RXD_CLKEN__READ(die, channel);
            data = SPICA_SRX_RXD_CLKEN__CHK__SET(data, 1);
            //always turn the DSP clock back on
            data = SPICA_SRX_RXD_CLKEN__DSP__SET(data, 1);
            SPICA_SRX_RXD_CLKEN__WRITE(die, channel, data);

        }
#endif // defined(INPHI_REMOVE_PSR)

        uint16_t dual_prbs;

        /* Force dual PRBS mode to false when signalling is NRZ */
        if (chk_rules->nrz_mode)
        {
            dual_prbs = false;
        }
        else
        {
            dual_prbs = (chk_rules->prbs_mode != SPICA_PRBS_MODE_COMBINED);
        }

        data = SPICA_VAL(SPICA_SRX_RXD_DP_CHK_PRBS_CFG__DUAL_PRBS,            dual_prbs                                                             ) |
               SPICA_VAL(SPICA_SRX_RXD_DP_CHK_PRBS_CFG__AUTO_POLARITY_THRESH, chk_rules->auto_polarity_thresh                                       ) |
               SPICA_VAL(SPICA_SRX_RXD_DP_CHK_PRBS_CFG__AUTO_POLARITY_EN,     chk_rules->auto_polarity_en                                           ) |
               SPICA_VAL(SPICA_SRX_RXD_DP_CHK_PRBS_CFG__PRBS_INV,             chk_rules->prbs_inv                                                   ) |
               SPICA_VAL(SPICA_SRX_RXD_DP_CHK_PRBS_CFG__PRBS_MODE_ODD,        spica_prbs_get_hdwr_pat((e_spica_prbs_pat)chk_rules->prbs_pattern_lsb)) |
               SPICA_VAL(SPICA_SRX_RXD_DP_CHK_PRBS_CFG__PRBS_MODE,            spica_prbs_get_hdwr_pat((e_spica_prbs_pat)chk_rules->prbs_pattern)    );
        spica_reg_channel_write(die, channel, SPICA_SRX_RXD_DP_CHK_PRBS_CFG__ADDRESS+chk_offset, data);

        if (SPICA_PRBS_PATTERN_FIXED == chk_rules->pattern_mode)
        {
            spica_reg_channel_write(die, channel, SPICA_SRX_RXD_DP_FIXED_PAT_VALUE_CFG0__ADDRESS+chk_offset, chk_rules->fixed_pat0);
            spica_reg_channel_write(die, channel, SPICA_SRX_RXD_DP_FIXED_PAT_VALUE_CFG1__ADDRESS+chk_offset, chk_rules->fixed_pat1);
            spica_reg_channel_write(die, channel, SPICA_SRX_RXD_DP_FIXED_PAT_VALUE_CFG2__ADDRESS+chk_offset, chk_rules->fixed_pat2);
            spica_reg_channel_write(die, channel, SPICA_SRX_RXD_DP_FIXED_PAT_VALUE_CFG3__ADDRESS+chk_offset, chk_rules->fixed_pat3);
        }

        data = SPICA_VAL(SPICA_SRX_RXD_DP_CHK_CFG__FIXED_PAT_EN, (SPICA_PRBS_PATTERN_FIXED == chk_rules->pattern_mode)) |
               SPICA_VAL(SPICA_SRX_RXD_DP_CHK_CFG__PRBS_EN,      1                                                    ) |
               SPICA_VAL(SPICA_SRX_RXD_DP_CHK_CFG__OOS_THRESH,   chk_rules->oos_thresh                                );
        spica_reg_channel_write(die, channel, SPICA_SRX_RXD_DP_CHK_CFG__ADDRESS+chk_offset, data);

#if 0
        // Never clear interrupts in the API, see Youtrack SPS-691
        /*  clear the PRBS checker interrupts */
        if (SPICA_INTF_ORX == intf)
        {
            data = SPICA_ORX_DDP_INT__READ(die, channel);
            data &= ~0x001f;
            SPICA_ORX_DDP_INT__WRITE(die, channel, data);
        }
        else if (SPICA_INTF_MRX == intf)
        {
            data = SPICA_MRX_DDP_INT__READ(die, channel);
            data &= ~0x001f;
            SPICA_MRX_DDP_INT__WRITE(die, channel, data);
        }
        else if (SPICA_INTF_SRX == intf)
        {
            data = SPICA_SRX_RXD_INT__READ(die, channel);
            data &= ~0x001f;
            SPICA_SRX_RXD_INT__WRITE(die, channel, data);
        }
#endif
    }

    SPICA_UNLOCK(die);

    return status;
}

/* 
 * Extract the PRBS checker status
 */
inphi_status_t spica_prbs_chk_status(
    uint32_t     die, 
    uint32_t     channel,
    e_spica_intf intf,
    spica_prbs_chk_status_t* chk_status)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data = 0;
    uint64_t word_count;
        
    if(!chk_status)
    {
        INPHI_NOTE("PRBS Checker status pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    uint16_t chk_offset = 0;

    if (SPICA_INTF_ORX == intf) 
    {
        chk_offset = SPICA_ADDR_DIFF(SPICA_SRX_RXD_DP_CHK_CFG, SPICA_ORX_DDP_CHK_CFG);
    }
    else if (SPICA_INTF_MRX == intf)
    {
        chk_offset = SPICA_ADDR_DIFF(SPICA_SRX_RXD_DP_CHK_CFG, SPICA_MRX_DDP_CHK_CFG);
    }
    else if (SPICA_INTF_SRX == intf)
    {
        chk_offset = 0;
    }
    else
    {
        INPHI_NOTE("Checker interface must be one of ORX, MRX or SRX!\n");
        return (INPHI_ERROR);
    }

    /* pre-set the status  */
    INPHI_MEMSET(chk_status, 0, sizeof(*chk_status));

    SPICA_LOCK(die);

    /* A zero to one transition triggers a capture of the statistics counters.*/
    data = spica_reg_channel_read(die, channel, SPICA_SRX_RXD_DP_CHK_CFG__ADDRESS+chk_offset);
    data = SPICA_SRX_RXD_DP_CHK_CFG__CNT_LATCH__SET(data, 0);
    spica_reg_channel_write(die, channel, SPICA_SRX_RXD_DP_CHK_CFG__ADDRESS+chk_offset, data);
    data = SPICA_SRX_RXD_DP_CHK_CFG__CNT_LATCH__SET(data, 1);
    spica_reg_channel_write(die, channel, SPICA_SRX_RXD_DP_CHK_CFG__ADDRESS+chk_offset, data);
    data = SPICA_SRX_RXD_DP_CHK_CFG__CNT_LATCH__SET(data, 0);
    spica_reg_channel_write(die, channel, SPICA_SRX_RXD_DP_CHK_CFG__ADDRESS+chk_offset, data);

    data = spica_reg_channel_read(die, channel, SPICA_SRX_RXD_DP_CHK_PRBS_CFG__ADDRESS+chk_offset);
    uint8_t pat = SPICA_SRX_RXD_DP_CHK_PRBS_CFG__PRBS_MODE__GET(data);
    chk_status->prbs_pattern = spica_prbs_get_hdwr_pat(pat); 
    if (SPICA_SRX_RXD_DP_CHK_PRBS_CFG__DUAL_PRBS__GET(data) == 1) 
    {
        chk_status->prbs_mode = SPICA_PRBS_MODE_MSB_LSB;
        pat = SPICA_SRX_RXD_DP_CHK_PRBS_CFG__PRBS_MODE_ODD__GET(data);
        chk_status->prbs_pattern_lsb = spica_prbs_get_hdwr_pat(pat); 
    }
    else
    {
        chk_status->prbs_mode = SPICA_PRBS_MODE_COMBINED;
        chk_status->prbs_pattern_lsb = chk_status->prbs_pattern;
    }

    data = spica_reg_channel_read(die, channel, SPICA_SRX_RXD_DP_CHK_WORD_CNT0__ADDRESS+chk_offset);
    word_count = (uint64_t)data;
    data = spica_reg_channel_read(die, channel, SPICA_SRX_RXD_DP_CHK_WORD_CNT1__ADDRESS+chk_offset);
    word_count += (((uint64_t)data) << 16);
    data = spica_reg_channel_read(die, channel, SPICA_SRX_RXD_DP_CHK_WORD_CNT2__ADDRESS+chk_offset);
    word_count += (((uint64_t)data) << 32);
    
    /* Convert the word count to a cycle count */
    chk_status->prbs_total_bit_count = ((uint64_t)(word_count) * 128);

    data = spica_reg_channel_read(die, channel, SPICA_SRX_RXD_DP_CHK_BIT_ERROR_CNT0__ADDRESS+chk_offset);
    chk_status->prbs_error_bit_count = data;
    data = spica_reg_channel_read(die, channel, SPICA_SRX_RXD_DP_CHK_BIT_ERROR_CNT1__ADDRESS+chk_offset);
    chk_status->prbs_error_bit_count += (((uint32_t)data) << 16);

    data = spica_reg_channel_read(die, channel, SPICA_SRX_RXD_DP_CHK_BIT_ERROR_ODD_CNT0__ADDRESS+chk_offset);
    chk_status->prbs_error_bit_count_lsb = data;
    data = spica_reg_channel_read(die, channel, SPICA_SRX_RXD_DP_CHK_BIT_ERROR_ODD_CNT1__ADDRESS+chk_offset);
    chk_status->prbs_error_bit_count_lsb += (((uint32_t)data) << 16);

    // declare saturation if the total word or errored bit counts saturate
    if ((word_count == 0xffffffffffffL) || 
        (chk_status->prbs_error_bit_count == 0xffffffffL) ||
        (chk_status->prbs_error_bit_count_lsb == 0xffffffffL))
    {
        chk_status->prbs_total_bit_count_saturated = true;
    }

    /*  Get the PRBS checker interrupts */
    if (SPICA_INTF_ORX == intf)
    {
        data = SPICA_ORX_DDP_INTS__READ(die, channel);
    }
    else if (SPICA_INTF_MRX == intf)
    {
        data = SPICA_MRX_DDP_INTS__READ(die, channel);
    }
    else if (SPICA_INTF_SRX == intf)
    {
        data = SPICA_SRX_RXD_INTS__READ(die, channel);
    }

    chk_status->prbs_fixed_pat_sync = SPICA_SRX_RXD_INTS__DP_FIXED_PAT_SYNCS__GET(data);
    chk_status->prbs_inv_lsb        = SPICA_SRX_RXD_INTS__DP_PRBS_POLARITY_INV_ODDS__GET(data);
    chk_status->prbs_lock_lsb       = SPICA_SRX_RXD_INTS__DP_PRBS_SYNC_ODDS__GET(data);
    chk_status->prbs_inv            = SPICA_SRX_RXD_INTS__DP_PRBS_POLARITY_INVS__GET(data);
    chk_status->prbs_lock           = SPICA_SRX_RXD_INTS__DP_PRBS_SYNCS__GET(data);
    
    SPICA_UNLOCK(die);

    return status;
}

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
/*
 * Find the BER
 */
inphi_status_t spica_prbs_chk_ber(
    spica_prbs_chk_status_t *chk_status,
    double *ber,
    double *ber_lsb)
{
    inphi_status_t status = INPHI_OK;
    *ber = 0.0;
    *ber_lsb = 0.0;

    if((0 == chk_status->prbs_total_bit_count) || chk_status->prbs_total_bit_count_saturated)
    {
        return INPHI_ERROR;
    }

    if(chk_status->prbs_total_bit_count) {
        *ber     = (double)chk_status->prbs_error_bit_count / (double)(chk_status->prbs_total_bit_count);
        *ber_lsb = (double)chk_status->prbs_error_bit_count_lsb / (double)(chk_status->prbs_total_bit_count);
    }

    return status;
}
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/* 
 * Print the PRBS checker status the selected channel
 */
inphi_status_t spica_prbs_chk_status_print(
    uint32_t                 die, 
    uint32_t                 channel,
    e_spica_intf             intf,
    spica_prbs_chk_status_t* chk_status)
{
    inphi_status_t status = INPHI_OK;

    INPHI_NOTE("\n%s PRBS checker status for die 0x%08x\n", 
                spica_dbg_translate_intf(intf), die);

    INPHI_NOTE("%5s| %5s| %10s| %8s| %8s| %12s| %21s| %10s| %10s|", 
               "| Ch#", 
               "Mode",
               "LockStat", 
               "Pattern", 
               "Invert", 
               "ErrBitCnt", 
               "TotalBit", 
               "BitCntSat", 
               "FixPatSnc");
#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    INPHI_NOTE("%12s|", "BER");
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    INPHI_NOTE("%s", "\n+----+------+-----------+---------+---------+-------------+----------------------+-----------+-----------+"); 
#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    INPHI_NOTE("%12s", "------------+");
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    INPHI_NOTE("\n");
    INPHI_NOTE("|  %2d| %5s| %10s| %8s| %8s| %12u| %21" PRIu64 "| %10s|", 
               channel, 
               chk_status->prbs_mode == SPICA_PRBS_MODE_COMBINED ? "CMB" : "MSB",
               chk_status->prbs_lock ? "True" : "False",
               spica_prbs_translate_pat((e_spica_prbs_pat)chk_status->prbs_pattern),
               chk_status->prbs_inv ? "True" : "False",
               chk_status->prbs_error_bit_count,
               chk_status->prbs_total_bit_count,
               chk_status->prbs_total_bit_count_saturated ? "True" : "False");

    INPHI_NOTE("%11s|", chk_status->prbs_fixed_pat_sync ? "True" : "False");

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    double ber;
    double ber_lsb;
    inphi_status_t tmp_status = spica_prbs_chk_ber(chk_status, &ber, &ber_lsb);
    if (INPHI_OK == tmp_status)
    {
        INPHI_NOTE("%12.2e|", ber);
    }
    else
    {
        INPHI_NOTE("%12s|", "N/A");
    }
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

    INPHI_NOTE("\n");

    // assume the mode is the same for all channels
    if (chk_status->prbs_mode == SPICA_PRBS_MODE_MSB_LSB)
    {        
        INPHI_NOTE("|  %2d| %5s| %10s| %8s| %8s| %12u| %21" PRIu64 "| %10s|", 
                   channel, 
                   "LSB",
                   chk_status->prbs_lock_lsb ? "True" : "False",
                   spica_prbs_translate_pat((e_spica_prbs_pat)chk_status->prbs_pattern_lsb),
                   chk_status->prbs_inv_lsb ? "True" : "False",
                   chk_status->prbs_error_bit_count_lsb,
                   chk_status->prbs_total_bit_count,
                   chk_status->prbs_total_bit_count_saturated ? "True" : "False");

        INPHI_NOTE("%11s|", chk_status->prbs_fixed_pat_sync ? "True" : "False");

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
        tmp_status = spica_prbs_chk_ber(chk_status, &ber, &ber_lsb);
        if (INPHI_OK == tmp_status)
        {
            INPHI_NOTE("%12.2e|", ber_lsb);
        }
        else
        {
            INPHI_NOTE("%12s|", "N/A");
        }

#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    
        INPHI_NOTE("\n");
    }

    INPHI_NOTE("\n");

    return status;
}

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

inphi_status_t spica_prbs_chk_status_query_print(
    uint32_t     die, 
    uint32_t     channel,
    e_spica_intf intf)
{
    inphi_status_t status = INPHI_OK;
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    spica_prbs_chk_status_t chk_status;
    
    // Query the status
    status |= spica_prbs_chk_status(die, channel, intf, &chk_status);

    // Print the output
    status |= spica_prbs_chk_status_print(die, channel, intf, &chk_status);
#else
    (void)die;
    (void)channel;
    (void)intf;
    status = INPHI_ERROR;
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

    return status;
}

/** @file spica_reg_dump.c
 ****************************************************************************
 *
 * @brief
 *  This module provides a method to print all of the accessible registers
 *  to a file for debugging.
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

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

inphi_status_t spica_diags_register_dump(uint32_t die)
{
    inphi_status_t status = INPHI_OK;

     static const uint32_t register_ranges[][2] =
    {
        {0x0, 0x8},
        {0x64, 0x64},
        {0xf0, 0xf2},
        {0x80000, 0x80000},
        {0x80002, 0x80007},
        {0x1e0002, 0x1e00a2},
        {0x1e0400, 0x1e0405},
        {0x1e0500, 0x1e0508},
        {0x1e0564, 0x1e0564},
        {0x1e05f0, 0x1e05f2},
        {0x1e0800, 0x1e0843},
        {0x1e0880, 0x1e0880},
        {0x1e0900, 0x1e0969},
        {0x1e0980, 0x1e09e9},
        {0x1e0a00, 0x1e0a69},
        {0x1e0a80, 0x1e0ae9},
        {0x1e0b00, 0x1e0b69},
        {0x1e0b80, 0x1e0be9},
        {0x1e0c00, 0x1e0c69},
        {0x1e0c80, 0x1e0ce9},
        {0x1e0d00, 0x1e0d69},
        {0x1e1000, 0x1e100d},
        {0x1e1010, 0x1e10aa},
        {0x1e1100, 0x1e1161},
        {0x1e1180, 0x1e11b6},
        {0x1e1200, 0x1e125c},
        {0x1e1280, 0x1e1298},
        {0x1e1300, 0x1e1361},
        {0x1e1380, 0x1e13b6},
        {0x1e1400, 0x1e145c},
        {0x1e1480, 0x1e1498},
        {0x1e1500, 0x1e1561},
        {0x1e1580, 0x1e15b6},
        {0x1e1600, 0x1e165c},
        {0x1e1680, 0x1e1698},
        {0x1e1800, 0x1e180d},
        {0x1e1810, 0x1e18aa},
        {0x1e1900, 0x1e1961},
        {0x1e1980, 0x1e19b6},
        {0x1e1a00, 0x1e1a5c},
        {0x1e1a80, 0x1e1a98},
        {0x1e1b00, 0x1e1b61},
        {0x1e1b80, 0x1e1bb6},
        {0x1e1c00, 0x1e1c5c},
        {0x1e1c80, 0x1e1c98},
        {0x1e1d00, 0x1e1d61},
        {0x1e1d80, 0x1e1db6},
        {0x1e1e00, 0x1e1e5c},
        {0x1e1e80, 0x1e1e98},
        {0x1e2000, 0x1e200d},
        {0x1e2010, 0x1e20aa},
        {0x1e2100, 0x1e2161},
        {0x1e2180, 0x1e21b6},
        {0x1e2200, 0x1e225c},
        {0x1e2280, 0x1e2298},
        {0x1e2300, 0x1e2361},
        {0x1e2380, 0x1e23b6},
        {0x1e2400, 0x1e245c},
        {0x1e2480, 0x1e2498},
        {0x1e2500, 0x1e2561},
        {0x1e2580, 0x1e25b6},
        {0x1e2600, 0x1e265c},
        {0x1e2680, 0x1e2698},
        {0x1e2800, 0x1e280d},
        {0x1e2810, 0x1e28aa},
        {0x1e2900, 0x1e2961},
        {0x1e2980, 0x1e29b6},
        {0x1e2a00, 0x1e2a5c},
        {0x1e2a80, 0x1e2a98},
        {0x1e2b00, 0x1e2b61},
        {0x1e2b80, 0x1e2bb6},
        {0x1e2c00, 0x1e2c5c},
        {0x1e2c80, 0x1e2c98},
        {0x1e2d00, 0x1e2d61},
        {0x1e2d80, 0x1e2db6},
        {0x1e2e00, 0x1e2e5c},
        {0x1e2e80, 0x1e2e98},
        {0x1e3000, 0x1e300d},
        {0x1e3010, 0x1e30aa},
        {0x1e3100, 0x1e3161},
        {0x1e3180, 0x1e31b6},
        {0x1e3200, 0x1e325c},
        {0x1e3280, 0x1e3298},
        {0x1e3300, 0x1e3361},
        {0x1e3380, 0x1e33b6},
        {0x1e3400, 0x1e345c},
        {0x1e3480, 0x1e3498},
        {0x1e3500, 0x1e3561},
        {0x1e3580, 0x1e35b6},
        {0x1e3600, 0x1e365c},
        {0x1e3680, 0x1e3698},
        {0x1e3800, 0x1e383d},
        {0x1e3840, 0x1e38c9},
        {0x1e38e0, 0x1e38f5},
        {0x1e3900, 0x1e3966},
        {0x1e3c00, 0x1e3c0a},
        {0x1e3c80, 0x1e3ca9},
        {0x1e3d00, 0x1e3d2d},
        {0x1e3d80, 0x1e3e7c},
        {0x1e3e80, 0x1e3f5b},
        {0x1e4000, 0x1e403d},
        {0x1e4040, 0x1e40c9},
        {0x1e40e0, 0x1e40f5},
        {0x1e4100, 0x1e4166},
        {0x1e4400, 0x1e440a},
        {0x1e4480, 0x1e44a9},
        {0x1e4500, 0x1e452d},
        {0x1e4580, 0x1e467c},
        {0x1e4680, 0x1e475b},
        {0x1e4800, 0x1e483d},
        {0x1e4840, 0x1e48c9},
        {0x1e48e0, 0x1e48f5},
        {0x1e4900, 0x1e4966},
        {0x1e4c00, 0x1e4c0a},
        {0x1e4c80, 0x1e4ca9},
        {0x1e4d00, 0x1e4d2d},
        {0x1e4d80, 0x1e4e7c},
        {0x1e4e80, 0x1e4f5b},
        {0x1e5000, 0x1e503d},
        {0x1e5040, 0x1e50c9},
        {0x1e50e0, 0x1e50f5},
        {0x1e5100, 0x1e5166},
        {0x1e5400, 0x1e540a},
        {0x1e5480, 0x1e54a9},
        {0x1e5500, 0x1e552d},
        {0x1e5580, 0x1e567c},
        {0x1e5680, 0x1e575b},
        {0x1e5800, 0x1e583d},
        {0x1e5840, 0x1e58c9},
        {0x1e58e0, 0x1e58f5},
        {0x1e5900, 0x1e5966},
        {0x1e5c00, 0x1e5c0a},
        {0x1e5c80, 0x1e5ca9},
        {0x1e5d00, 0x1e5d2d},
        {0x1e5d80, 0x1e5e7c},
        {0x1e5e80, 0x1e5f5b},
        {0x1e6000, 0x1e603d},
        {0x1e6040, 0x1e60c9},
        {0x1e60e0, 0x1e60f5},
        {0x1e6100, 0x1e6166},
        {0x1e6400, 0x1e640a},
        {0x1e6480, 0x1e64a9},
        {0x1e6500, 0x1e652d},
        {0x1e6580, 0x1e667c},
        {0x1e6680, 0x1e675b},
        {0x1e6800, 0x1e683d},
        {0x1e6840, 0x1e68c9},
        {0x1e68e0, 0x1e68f5},
        {0x1e6900, 0x1e6966},
        {0x1e6c00, 0x1e6c0a},
        {0x1e6c80, 0x1e6ca9},
        {0x1e6d00, 0x1e6d2d},
        {0x1e6d80, 0x1e6e7c},
        {0x1e6e80, 0x1e6f5b},
        {0x1e7000, 0x1e703d},
        {0x1e7040, 0x1e70c9},
        {0x1e70e0, 0x1e70f5},
        {0x1e7100, 0x1e7166},
        {0x1e7400, 0x1e740a},
        {0x1e7480, 0x1e74a9},
        {0x1e7500, 0x1e752d},
        {0x1e7580, 0x1e767c},
        {0x1e7680, 0x1e775b},
        {0x1e7800, 0x1e783d},
        {0x1e7840, 0x1e78c9},
        {0x1e78e0, 0x1e78f5},
        {0x1e7900, 0x1e7966},
        {0x1e7c00, 0x1e7c0a},
        {0x1e7c80, 0x1e7ca9},
        {0x1e7d00, 0x1e7d2d},
        {0x1e7d80, 0x1e7e7c},
        {0x1e7e80, 0x1e7f5b},
        {0x1e8000, 0x1e803d},
        {0x1e8040, 0x1e80c9},
        {0x1e80e0, 0x1e80f5},
        {0x1e8100, 0x1e8166},
        {0x1e8400, 0x1e840a},
        {0x1e8480, 0x1e84a9},
        {0x1e8500, 0x1e852d},
        {0x1e8580, 0x1e867c},
        {0x1e8680, 0x1e875b},
        {0x1e8800, 0x1e880f},
        {0x1e8840, 0x1e885d},
        {0x1e8860, 0x1e8869},
        {0x1e8880, 0x1e8890},
        {0x1e8900, 0x1e893c},
        {0x1e89a0, 0x1e89a8},
        {0x1e8a00, 0x1e8a3c},
        {0x1e8aa0, 0x1e8aa8},
        {0x1e8b00, 0x1e8b3c},
        {0x1e8ba0, 0x1e8ba8},
        {0x1e8c00, 0x1e8c4e},
        {0x1e8c80, 0x1e8ca7},
        {0x1e8d00, 0x1e8ddb},
        {0x1e8e00, 0x1e8efc},
        {0x1e9000, 0x1e900f},
        {0x1e9040, 0x1e905d},
        {0x1e9060, 0x1e9069},
        {0x1e9080, 0x1e9090},
        {0x1e9100, 0x1e913c},
        {0x1e91a0, 0x1e91a8},
        {0x1e9200, 0x1e923c},
        {0x1e92a0, 0x1e92a8},
        {0x1e9300, 0x1e933c},
        {0x1e93a0, 0x1e93a8},
        {0x1e9400, 0x1e944e},
        {0x1e9480, 0x1e94a7},
        {0x1e9500, 0x1e95db},
        {0x1e9600, 0x1e96fc},
        {0x1e9800, 0x1e980f},
        {0x1e9840, 0x1e985d},
        {0x1e9860, 0x1e9869},
        {0x1e9880, 0x1e9890},
        {0x1e9900, 0x1e993c},
        {0x1e99a0, 0x1e99a8},
        {0x1e9a00, 0x1e9a3c},
        {0x1e9aa0, 0x1e9aa8},
        {0x1e9b00, 0x1e9b3c},
        {0x1e9ba0, 0x1e9ba8},
        {0x1e9c00, 0x1e9c4e},
        {0x1e9c80, 0x1e9ca7},
        {0x1e9d00, 0x1e9ddb},
        {0x1e9e00, 0x1e9efc},
        {0x1ea000, 0x1ea00f},
        {0x1ea040, 0x1ea05d},
        {0x1ea060, 0x1ea069},
        {0x1ea080, 0x1ea090},
        {0x1ea100, 0x1ea13c},
        {0x1ea1a0, 0x1ea1a8},
        {0x1ea200, 0x1ea23c},
        {0x1ea2a0, 0x1ea2a8},
        {0x1ea300, 0x1ea33c},
        {0x1ea3a0, 0x1ea3a8},
        {0x1ea400, 0x1ea44e},
        {0x1ea480, 0x1ea4a7},
        {0x1ea500, 0x1ea5db},
        {0x1ea600, 0x1ea6fc},
        {0x1ea800, 0x1ea80f},
        {0x1ea840, 0x1ea85d},
        {0x1ea860, 0x1ea869},
        {0x1ea880, 0x1ea890},
        {0x1ea900, 0x1ea93c},
        {0x1ea9a0, 0x1ea9a8},
        {0x1eaa00, 0x1eaa3c},
        {0x1eaaa0, 0x1eaaa8},
        {0x1eab00, 0x1eab3c},
        {0x1eaba0, 0x1eaba8},
        {0x1eac00, 0x1eac4e},
        {0x1eac80, 0x1eaca7},
        {0x1ead00, 0x1eaddb},
        {0x1eae00, 0x1eaefc},
        {0x1eb000, 0x1eb04b},
        {0x1eb080, 0x1eb0a7},
        {0x1eb0c0, 0x1eb0da},
        {0x1eb100, 0x1eb11a},
        {0x1eb140, 0x1eb18e},
        {0x1eb1c0, 0x1eb1c8},
        {0x1eb1d0, 0x1eb1ed},
        {0x1eb200, 0x1eb2db},
        {0x1eb300, 0x1eb3fc},
        {0x1eb800, 0x1eb84b},
        {0x1eb880, 0x1eb8a7},
        {0x1eb8c0, 0x1eb8da},
        {0x1eb900, 0x1eb91a},
        {0x1eb940, 0x1eb98e},
        {0x1eb9c0, 0x1eb9c8},
        {0x1eb9d0, 0x1eb9ed},
        {0x1eba00, 0x1ebadb},
        {0x1ebb00, 0x1ebbfc},
        {0x1ec000, 0x1ec04b},
        {0x1ec080, 0x1ec0a7},
        {0x1ec0c0, 0x1ec0da},
        {0x1ec100, 0x1ec11a},
        {0x1ec140, 0x1ec18e},
        {0x1ec1c0, 0x1ec1c8},
        {0x1ec1d0, 0x1ec1ed},
        {0x1ec200, 0x1ec2db},
        {0x1ec300, 0x1ec3fc},
        {0x1ec800, 0x1ec84b},
        {0x1ec880, 0x1ec8a7},
        {0x1ec8c0, 0x1ec8da},
        {0x1ec900, 0x1ec91a},
        {0x1ec940, 0x1ec98e},
        {0x1ec9c0, 0x1ec9c8},
        {0x1ec9d0, 0x1ec9ed},
        {0x1eca00, 0x1ecadb},
        {0x1ecb00, 0x1ecbfc},
        {0x1ed000, 0x1ed04b},
        {0x1ed080, 0x1ed0a7},
        {0x1ed0c0, 0x1ed0da},
        {0x1ed100, 0x1ed11a},
        {0x1ed140, 0x1ed18e},
        {0x1ed1c0, 0x1ed1c8},
        {0x1ed1d0, 0x1ed1ed},
        {0x1ed200, 0x1ed2db},
        {0x1ed300, 0x1ed3fc},
        {0x1ed800, 0x1ed89a},
        {0x1ed900, 0x1ed9f7},
        {0x1edb00, 0x1edb9a},
        {0x1edc00, 0x1edcf7},
        {0x1ede00, 0x1ede2b},
        {0x1ee000, 0x1ee0b5},
        {0x1ee400, 0x1ee400},
        {0x1ee800, 0x1ee800},
        {0x1ef000, 0x1ef041},
        {0x1ef200, 0x1ef241},
        {0x1ef400, 0x1ef441},
        {0x1ef600, 0x1ef607},
        {0x1ef800, 0x1ef817},
    };

    uint32_t range;

    INPHI_NOTE("DIE %x\n-----------\n", die);

    if(spica_lock(die) != INPHI_OK) return INPHI_ERROR;

    for(range = 0; range < (sizeof(register_ranges)/sizeof(register_ranges[0])); range++)
    {
        uint32_t start = register_ranges[range][0];
        uint32_t end   = register_ranges[range][1];
        uint32_t addr;

        for(addr = start; addr < end+1;)
        {
            uint32_t reg_data = 0;
            reg_data = spica_reg_read(die, addr);

            // registers are 16bits, and the addresses increment by 1
            INPHI_NOTE("0x%06x = 0x%04x\n", addr, reg_data);
            addr += 1;
        }
    }

    status |= spica_unlock(die);
    return status;
}

#endif //!defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

/** @file sw_fec.c
 ****************************************************************************
 *
 * @brief
 *     This module describes the SW FEC API methods provided
 *     by the Spica API.
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

#if !defined(INPHI_REMOVE_MESSAGING)

#define F16_EXP_BIAS (-24)
#define F16_EXP_BITS (5)
#define F16_EXP_MASK  ((1<<F16_EXP_BITS)-1)
#define F16_MAN_BITS (11)
#define F16_MAN_MASK ((1<<F16_MAN_BITS)-1)
#define F16_EXP_GET(val) ((((int)(val)>>F16_MAN_BITS)&F16_EXP_MASK)+F16_EXP_BIAS)
#define F16_MAN_GET(val) (((int)(val)&F16_MAN_MASK))
#define F16_EXP_SET(val) ((((int)(val)-F16_EXP_BIAS)&F16_EXP_MASK)<<F16_MAN_BITS)
#define F16_MAN_SET(val) (((int)(val)&F16_MAN_MASK))

inphi_status_t spica_fec_stats_poller_cfg(
    uint32_t   die,
    e_spica_intf intf,
    const spica_fec_stats_poller_rules_t *stats_rules
    )
{
    inphi_status_t status = INPHI_OK;

    if (SPICA_INTF_IG_FEC != intf)
    {
        INPHI_CRIT("Interface must be INTF_IG_FEC\n");
        return INPHI_ERROR;
    }

    if(stats_rules->en)
    {
        if(stats_rules->accumulation_time <= 1)
        {
            INPHI_CRIT("accumulation_time must be >1\n");
            return INPHI_ERROR;
        }
        if((stats_rules->accumulation_time > SPICA_FEC_STATS_MAX_TIME) || (stats_rules->interval_time > SPICA_FEC_STATS_MAX_TIME))
        {
            INPHI_CRIT("accumulation or interval time is too large, must be < %d \n", SPICA_FEC_STATS_MAX_TIME);
            return INPHI_ERROR;
        }
    }

    SPICA_LOCK(die);

    status |= spica_mcu_fec_stats_poller_cfg(die, intf, stats_rules);

    SPICA_UNLOCK(die);

    return status;
}

inphi_status_t spica_fec_stats_poller_request(
    uint32_t   die,
    e_spica_intf intf,
    bool clear_on_read,
    spica_fec_stats_cp_block_t *stats
    )
{
    inphi_status_t status = INPHI_OK;

    if (SPICA_INTF_IG_FEC != intf)
    {
        INPHI_CRIT("Interface must be INTF_IG_FEC\n");
        return INPHI_ERROR;
    }

    // initialize the stats structure to NaN
    const uint16_t f16_nan = ((F16_EXP_MASK)<<F16_MAN_BITS);
    uint16_t *ptr = (uint16_t*)stats;
    for(uint32_t i=0; i<sizeof(*stats)/sizeof(*ptr); i+=1) {
        ptr[i] = f16_nan;
    }
    // update the state
    stats->_state = 0;
    // update the count
    stats->poll_count = 0;

    SPICA_LOCK(die);

    status |= spica_mcu_fec_stats_poller_request(die, intf, clear_on_read);

    SPICA_UNLOCK(die);

    return status;
}

#define SPICA_FEC_F16_NAN 0xf800

void spica_fec_stats_poller_ins_NaNs(
    spica_fec_stats_cp_block_t *stats
    )
{
    stats->corr_cw_hist_15_curr  = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_15_avg   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_15_max   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_14_curr  = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_14_avg   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_14_max   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_13_curr  = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_13_avg   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_13_max   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_12_curr  = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_12_avg   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_12_max   = SPICA_FEC_F16_NAN;

    stats->corr_cw_hist_11_curr  = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_11_avg   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_11_max   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_10_curr  = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_10_avg   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_10_max   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_9_curr   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_9_avg    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_9_max    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_8_curr   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_8_avg    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_8_max    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_7_curr   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_7_avg    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_7_max    = SPICA_FEC_F16_NAN;
    stats->ser_curr              = SPICA_FEC_F16_NAN;
    stats->ser_avg               = SPICA_FEC_F16_NAN;
    stats->ser_max               = SPICA_FEC_F16_NAN;

    stats->corr_cw_hist_6_curr   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_6_avg    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_6_max    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_5_curr   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_5_avg    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_5_max    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_4_curr   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_4_avg    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_4_max    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_3_curr   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_3_avg    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_3_max    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_2_curr   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_2_avg    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_2_max    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_1_curr   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_1_avg    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_1_max    = SPICA_FEC_F16_NAN;

    stats->ser_min               = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_15_min   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_14_min   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_13_min   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_12_min   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_11_min   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_10_min   = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_9_min    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_8_min    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_7_min    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_6_min    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_5_min    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_4_min    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_3_min    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_2_min    = SPICA_FEC_F16_NAN;
    stats->corr_cw_hist_1_min    = SPICA_FEC_F16_NAN;
}

e_spica_poller_status spica_fec_stats_poller_get(
    uint32_t   die,
    e_spica_intf intf,
    uint32_t blocks_to_read,
    spica_fec_stats_cp_block_t *stats
    )
{
    e_spica_poller_status poller_status = SPICA_POLLER_OK;

    if (SPICA_INTF_IG_FEC != intf)
    {
        INPHI_CRIT("Interface must be INTF_IG_FEC\n");
        return INPHI_ERROR;
    }

#ifndef INPHI_DONT_USE_STDLIB
    poller_status |= spica_mcu_fec_stats_poller_get(die, intf, blocks_to_read, stats);
#endif //ifndef INPHI_DONT_USE_STDLIB

    // for public builds, insert NaN codes in all non ber/ferc values, see SPS-786
    spica_fec_stats_poller_ins_NaNs(stats);

    return poller_status;
}

inphi_status_t spica_fec_stats_poller_clear(
    uint32_t   die,
    e_spica_intf intf
    )
{
    inphi_status_t status = INPHI_OK;

    if (SPICA_INTF_IG_FEC != intf)
    {
        INPHI_CRIT("Interface must be INTF_IG_FEC\n");
        return INPHI_ERROR;
    }

    SPICA_LOCK(die);

    status |= spica_mcu_fec_stats_poller_clear(die, intf);

    SPICA_UNLOCK(die);

    return status;
}

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
#if defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)

spica_rate_t cmis_f16_to_float(uint16_t value)
{
    if(0 == value)
    {
        return 0;
    }
    if(0 == F16_MAN_GET(value))
    {
        //not-a-number
        return NAN;
    }
    if(0xffff == value)
    {
        //infinity
        return INFINITY;
    }

    spica_rate_t ret = F16_MAN_GET(value);
    //true exponent, unbiased
    int _exp = F16_EXP_GET(value);

    while(_exp > 0)
    {
        ret *= 10.0;
        _exp -= 1;
    }
    while(_exp < 0)
    {
        ret /= 10.0;
        _exp += 1;
    }
    return ret;
}

inphi_status_t spica_fec_stats_poller_calc_ber(
        uint32_t die,
        e_spica_intf intf,
        spica_fec_stats_cp_block_t *stats,
        spica_fec_stats_poller_t *avg_rates,
        spica_fec_stats_poller_t *min_rates,
        spica_fec_stats_poller_t *max_rates,
        spica_fec_stats_poller_t *cur_rates
        )
{
    inphi_status_t status = INPHI_OK;

    if (SPICA_INTF_IG_FEC != intf)
    {
        INPHI_CRIT("Interface must be INTF_IG_FEC\n");
        return INPHI_ERROR;
    }

    if(avg_rates) INPHI_MEMSET(avg_rates, 0, sizeof(*avg_rates));
    if(min_rates) INPHI_MEMSET(min_rates, 0, sizeof(*min_rates));
    if(max_rates) INPHI_MEMSET(max_rates, 0, sizeof(*max_rates));
    if(cur_rates) INPHI_MEMSET(cur_rates, 0, sizeof(*cur_rates));

    if(avg_rates)
    {
        avg_rates->ser = cmis_f16_to_float(stats->ser_avg);
        avg_rates->ber = cmis_f16_to_float(stats->ber_avg);
        avg_rates->ferc = cmis_f16_to_float(stats->ferc_avg);
        avg_rates->corrected_ratio_hist[ 0] = cmis_f16_to_float( stats->corr_cw_hist_1_avg);
        avg_rates->corrected_ratio_hist[ 1] = cmis_f16_to_float( stats->corr_cw_hist_2_avg);
        avg_rates->corrected_ratio_hist[ 2] = cmis_f16_to_float( stats->corr_cw_hist_3_avg);
        avg_rates->corrected_ratio_hist[ 3] = cmis_f16_to_float( stats->corr_cw_hist_4_avg);
        avg_rates->corrected_ratio_hist[ 4] = cmis_f16_to_float( stats->corr_cw_hist_5_avg);
        avg_rates->corrected_ratio_hist[ 5] = cmis_f16_to_float( stats->corr_cw_hist_6_avg);
        avg_rates->corrected_ratio_hist[ 6] = cmis_f16_to_float( stats->corr_cw_hist_7_avg);
        avg_rates->corrected_ratio_hist[ 7] = cmis_f16_to_float( stats->corr_cw_hist_8_avg);
        avg_rates->corrected_ratio_hist[ 8] = cmis_f16_to_float( stats->corr_cw_hist_9_avg);
        avg_rates->corrected_ratio_hist[ 9] = cmis_f16_to_float(stats->corr_cw_hist_10_avg);
        avg_rates->corrected_ratio_hist[10] = cmis_f16_to_float(stats->corr_cw_hist_11_avg);
        avg_rates->corrected_ratio_hist[11] = cmis_f16_to_float(stats->corr_cw_hist_12_avg);
        avg_rates->corrected_ratio_hist[12] = cmis_f16_to_float(stats->corr_cw_hist_13_avg);
        avg_rates->corrected_ratio_hist[13] = cmis_f16_to_float(stats->corr_cw_hist_14_avg);
        avg_rates->corrected_ratio_hist[14] = cmis_f16_to_float(stats->corr_cw_hist_15_avg);
    }

    if(min_rates)
    {
        min_rates->ser = cmis_f16_to_float(stats->ser_min);
        min_rates->ber = cmis_f16_to_float(stats->ber_min);
        min_rates->ferc = cmis_f16_to_float(stats->ferc_min);
        min_rates->corrected_ratio_hist[ 0] = cmis_f16_to_float( stats->corr_cw_hist_1_min);
        min_rates->corrected_ratio_hist[ 1] = cmis_f16_to_float( stats->corr_cw_hist_2_min);
        min_rates->corrected_ratio_hist[ 2] = cmis_f16_to_float( stats->corr_cw_hist_3_min);
        min_rates->corrected_ratio_hist[ 3] = cmis_f16_to_float( stats->corr_cw_hist_4_min);
        min_rates->corrected_ratio_hist[ 4] = cmis_f16_to_float( stats->corr_cw_hist_5_min);
        min_rates->corrected_ratio_hist[ 5] = cmis_f16_to_float( stats->corr_cw_hist_6_min);
        min_rates->corrected_ratio_hist[ 6] = cmis_f16_to_float( stats->corr_cw_hist_7_min);
        min_rates->corrected_ratio_hist[ 7] = cmis_f16_to_float( stats->corr_cw_hist_8_min);
        min_rates->corrected_ratio_hist[ 8] = cmis_f16_to_float( stats->corr_cw_hist_9_min);
        min_rates->corrected_ratio_hist[ 9] = cmis_f16_to_float(stats->corr_cw_hist_10_min);
        min_rates->corrected_ratio_hist[10] = cmis_f16_to_float(stats->corr_cw_hist_11_min);
        min_rates->corrected_ratio_hist[11] = cmis_f16_to_float(stats->corr_cw_hist_12_min);
        min_rates->corrected_ratio_hist[12] = cmis_f16_to_float(stats->corr_cw_hist_13_min);
        min_rates->corrected_ratio_hist[13] = cmis_f16_to_float(stats->corr_cw_hist_14_min);
        min_rates->corrected_ratio_hist[14] = cmis_f16_to_float(stats->corr_cw_hist_15_min);
    }

    if(max_rates)
    {
        max_rates->ser = cmis_f16_to_float(stats->ser_max);
        max_rates->ber = cmis_f16_to_float(stats->ber_max);
        max_rates->ferc = cmis_f16_to_float(stats->ferc_max);
        max_rates->corrected_ratio_hist[ 0] = cmis_f16_to_float( stats->corr_cw_hist_1_max);
        max_rates->corrected_ratio_hist[ 1] = cmis_f16_to_float( stats->corr_cw_hist_2_max);
        max_rates->corrected_ratio_hist[ 2] = cmis_f16_to_float( stats->corr_cw_hist_3_max);
        max_rates->corrected_ratio_hist[ 3] = cmis_f16_to_float( stats->corr_cw_hist_4_max);
        max_rates->corrected_ratio_hist[ 4] = cmis_f16_to_float( stats->corr_cw_hist_5_max);
        max_rates->corrected_ratio_hist[ 5] = cmis_f16_to_float( stats->corr_cw_hist_6_max);
        max_rates->corrected_ratio_hist[ 6] = cmis_f16_to_float( stats->corr_cw_hist_7_max);
        max_rates->corrected_ratio_hist[ 7] = cmis_f16_to_float( stats->corr_cw_hist_8_max);
        max_rates->corrected_ratio_hist[ 8] = cmis_f16_to_float( stats->corr_cw_hist_9_max);
        max_rates->corrected_ratio_hist[ 9] = cmis_f16_to_float(stats->corr_cw_hist_10_max);
        max_rates->corrected_ratio_hist[10] = cmis_f16_to_float(stats->corr_cw_hist_11_max);
        max_rates->corrected_ratio_hist[11] = cmis_f16_to_float(stats->corr_cw_hist_12_max);
        max_rates->corrected_ratio_hist[12] = cmis_f16_to_float(stats->corr_cw_hist_13_max);
        max_rates->corrected_ratio_hist[13] = cmis_f16_to_float(stats->corr_cw_hist_14_max);
        max_rates->corrected_ratio_hist[14] = cmis_f16_to_float(stats->corr_cw_hist_15_max);
    }

    if(cur_rates)
    {
        cur_rates->ser = cmis_f16_to_float(stats->ser_curr);
        cur_rates->ber = cmis_f16_to_float(stats->ber_curr);
        cur_rates->ferc = cmis_f16_to_float(stats->ferc_curr);
        cur_rates->corrected_ratio_hist[ 0] = cmis_f16_to_float( stats->corr_cw_hist_1_curr);
        cur_rates->corrected_ratio_hist[ 1] = cmis_f16_to_float( stats->corr_cw_hist_2_curr);
        cur_rates->corrected_ratio_hist[ 2] = cmis_f16_to_float( stats->corr_cw_hist_3_curr);
        cur_rates->corrected_ratio_hist[ 3] = cmis_f16_to_float( stats->corr_cw_hist_4_curr);
        cur_rates->corrected_ratio_hist[ 4] = cmis_f16_to_float( stats->corr_cw_hist_5_curr);
        cur_rates->corrected_ratio_hist[ 5] = cmis_f16_to_float( stats->corr_cw_hist_6_curr);
        cur_rates->corrected_ratio_hist[ 6] = cmis_f16_to_float( stats->corr_cw_hist_7_curr);
        cur_rates->corrected_ratio_hist[ 7] = cmis_f16_to_float( stats->corr_cw_hist_8_curr);
        cur_rates->corrected_ratio_hist[ 8] = cmis_f16_to_float( stats->corr_cw_hist_9_curr);
        cur_rates->corrected_ratio_hist[ 9] = cmis_f16_to_float(stats->corr_cw_hist_10_curr);
        cur_rates->corrected_ratio_hist[10] = cmis_f16_to_float(stats->corr_cw_hist_11_curr);
        cur_rates->corrected_ratio_hist[11] = cmis_f16_to_float(stats->corr_cw_hist_12_curr);
        cur_rates->corrected_ratio_hist[12] = cmis_f16_to_float(stats->corr_cw_hist_13_curr);
        cur_rates->corrected_ratio_hist[13] = cmis_f16_to_float(stats->corr_cw_hist_14_curr);
        cur_rates->corrected_ratio_hist[14] = cmis_f16_to_float(stats->corr_cw_hist_15_curr);
    }

    return status;
}

#endif // defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)
#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

#endif // defined(INPHI_REMOVE_MESSAGING)

/** @file spica.c
 ****************************************************************************
 *
 * @brief
 *     This module describes the high level API methods provided
 *     by the Spica API.
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

#if !defined(INPHI_REMOVE_MESSAGING)
#endif // defined(INPHI_REMOVE_MESSAGING)

static spica_callback_lock   g_spica_callback_lock   = NULL;
static spica_callback_unlock g_spica_callback_unlock = NULL;
spica_bundle_rules_t  g_bundle_storage; // storage for the bundle info

void spica_set_callback_for_lock(
    spica_callback_lock callback)
{
    g_spica_callback_lock = callback;
}

/* Get the API version information */
inphi_status_t spica_version(
    char*    buffer, 
    uint32_t buffer_len)
{
    if(!buffer)
    {
        INPHI_CRIT("ERROR: buffer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    INPHI_STRNCPY(buffer,
            "API Version " SPICA_API_VERSION "\n"
            "API Built on " SPICA_API_BUILD_DATE "\n",
            buffer_len); 

    return INPHI_OK;
}

/* Get the firmware version information */
inphi_status_t spica_version_firmware(
    uint32_t die,
    char*    buffer, 
    uint32_t buffer_len)
{
    inphi_status_t status = INPHI_OK;
    uint16_t mode;
    uint16_t fw_rev0;
    uint16_t fw_rev1;

    if(buffer == NULL)
    {
        return INPHI_ERROR;
    }
    if(buffer_len == 0) return INPHI_ERROR;

    SPICA_LOCK(die);

    mode    = SPICA_MCU_FW_MODE__READ(die);
    fw_rev0 = SPICA_MCU_FIRMWARE_REV0_OVL__READ(die);
    fw_rev1 = SPICA_MCU_FIRMWARE_REV1_OVL__READ(die);

    fw_rev0 = fw_rev0; // avoid compiler un-used var warning
    fw_rev1 = fw_rev1;

    /* Application mode */
    if(mode == 0xACC0)
    {
        INPHI_SNPRINTF(buffer,
            buffer_len,
            "Application Firmware Version (Major.Minor.Revision.Build) %d.%d.%d.%d\n", 
            SPICA_MCU_FIRMWARE_REV1_OVL__MAJOR__GET(fw_rev1),
            SPICA_MCU_FIRMWARE_REV1_OVL__MINOR__GET(fw_rev1),
            SPICA_MCU_FIRMWARE_REV1_OVL__REVISION__GET(fw_rev1),
            fw_rev0);
    }
    /* Unknown mode */
    else
    {
        mode    = SPICA_MCU_BOOTVER__READ(die);
        INPHI_SNPRINTF(buffer,
            buffer_len,
            "Firmware Unknown Mode (BOOTVER) %x, (FIRMWARE) %x%x\n",
            mode, fw_rev1, fw_rev0);
    }

    SPICA_UNLOCK(die);

    return status;
}

void spica_set_callback_for_unlock(
    spica_callback_unlock callback)
{
    g_spica_callback_unlock = callback;
}

/* Lock the device for exclusive access */
inphi_status_t spica_lock(
    uint32_t die)
{
    // This gets called a lot so don't use INPHI_FN_START
    if(g_spica_callback_lock == NULL)
    {
        return INPHI_OK;
    }

    inphi_status_t status = g_spica_callback_lock(die);
    if(status)
    {
        INPHI_CRIT("ERROR: Could not obtain lock on die %x\n", die);
    }
    return status;
}

/* Unlock the device for exclusive access */
inphi_status_t spica_unlock(
    uint32_t die)
{
    // This gets called a lot so don't use INPHI_FN_START
    if(g_spica_callback_unlock == NULL)
    {
        return INPHI_OK;
    }
    inphi_status_t status = g_spica_callback_unlock(die);
    if(status)
    {
        INPHI_CRIT("ERROR: Could not release lock on die %x\n", die);
    }
    return status;
}

const char* spica_dbg_translate_fw_mode(
    e_spica_fw_mode mode)
{
    switch(mode)
    {
        case SPICA_FW_MODE_UNKNOWN:     return "UNKNOWN";
        case SPICA_FW_MODE_APPLICATION: return "APPLICATION (ACC0)";
        default: break;
    }

    return ("???");
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

const char* spica_dbg_translate_operational_mode(
    e_spica_operational_mode operational_mode)
{
    switch (operational_mode)
    {
        case SPICA_MODE_MISSION_MODE:                return ("MISSION_MODE");
        case SPICA_MODE_LINE_PRBS:                   return ("LINE_PRBS");
        case SPICA_MODE_HOST_PRBS:                   return ("HOST_PRBS");
        case SPICA_MODE_DUAL_PRBS:                   return ("DUAL_PRBS");
        case SPICA_MODE_SHALLOW_LINE_LOOPBACK:       return ("SHALLOW_LINE_LOOPBACK");
        case SPICA_MODE_SHALLOW_HOST_LOOPBACK:       return ("SHALLOW_HOST_LOOPBACK");
        case SPICA_MODE_INGRESS_PRBS:                return ("INGRESS_PRBS");
        case SPICA_MODE_EGRESS_PRBS:                 return ("EGRESS_PRBS");
        default:
            break;
    }
    return ("???");
}

const char* spica_dbg_translate_protocol_mode(
    e_spica_protocol_mode protocol_mode)
{
    switch (protocol_mode)
    {
        case SPICA_MODE_400G_4Px53p1_TO_4Px53p1:    return("400G_4Px53p1_TO_4Px53p1");
        case SPICA_MODE_100G_4Nx25p8_TO_4Nx25p8:    return("100G_4Nx25p8_TO_4Nx25p8");
        case SPICA_MODE_300G_4Px41p3_TO_4Px41p3:    return("300G_4Px41p3_TO_4Px41p3");
        case SPICA_MODE_200G_4Px26p6_TO_4Px26p6:    return("200G_4Px26p6_TO_4Px26p6");
        case SPICA_MODE_100G_4Nx25p8_TO_2Px25p8:    return("100G_4Nx25p8_TO_2Px25p8");
        case SPICA_MODE_400G_8Px26p6_TO_4Px53p1:    return("400G_8Px26p6_TO_4Px53p1");
        case SPICA_MODE_200G_4Px26p6_TO_2Px53p1:    return("200G_4Px26p6_TO_2Px53p1");
        case SPICA_MODE_100G_2Px26p6_TO_1Px53p1:    return("100G_2Px26p6_TO_1Px53p1");
        case SPICA_MODE_100G_4Nx26p6_TO_1Px53p1:    return("100G_4Nx26p6_TO_1Px53p1");
        case SPICA_MODE_200G_4Nx53p1_TO_4Nx53p1:    return("200G_4Nx53p1_TO_4Nx53p1");
        case SPICA_MODE_200G_8Nx26p6_TO_4Px26p6:    return("200G_8Nx26p6_TO_4Px26p6");
        default:
            break;
    }
    return ("???");
}

const char* spica_dbg_translate_intf(
    e_spica_intf intf)
{
    switch(intf)
    {
        case SPICA_INTF_ORX: return ("ORX");
        case SPICA_INTF_OTX: return ("OTX");
        case SPICA_INTF_MRX: return ("MRX");
        case SPICA_INTF_MTX: return ("MTX");
        case SPICA_INTF_SRX: return ("SRX");
        case SPICA_INTF_STX: return ("STX");
        case SPICA_INTF_POR: return ("POR");
        case SPICA_INTF_PMR: return ("PMR");
        case SPICA_INTF_PSR: return ("PSR");
        case SPICA_INTF_ALL: return ("ALL");

        default: 
            break;
    }
    return ("???");
}

const char* spica_dbg_translate_baud_rate(e_spica_baud_rate baud_rate)
{
    switch (baud_rate)
    {
        case SPICA_BAUD_RATE_25p8:               return ("25p8");
        case SPICA_BAUD_RATE_26p6:               return ("26p6");
        case SPICA_BAUD_RATE_41p3:               return ("41p3");
        case SPICA_BAUD_RATE_51p6:               return ("51p6");
        case SPICA_BAUD_RATE_53p1:               return ("53p1");
        case SPICA_BAUD_RATE_56p3:               return ("56p3");
        default:
            break;
    }
    return ("Unkn");
}

const char* spica_dbg_translate_package_type(
    e_spica_package_type package)
{
    switch(package)
    {
        case SPICA_PACKAGE_TYPE_UNMAPPED:        return ("UN-MAPPED");
        case SPICA_PACKAGE_TYPE_EML_BOT_15x14:   return ("EML Bottom 15x14");
        case SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14: return ("SiPho Bottom 14x14");
        case SPICA_PACKAGE_TYPE_EML_TOP_15x14:   return ("EML Top 15x14");
        case SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14: return ("SiPho Top 15x14");
        case SPICA_PACKAGE_TYPE_EML_12x13:       return ("EML 12x13");
        case SPICA_PACKAGE_TYPE_EML_12x13_REV1:  return ("EML 12x13 (Rev1)");
        case SPICA_PACKAGE_TYPE_STD_10x13:       return ("STD 10x13");
        case SPICA_PACKAGE_TYPE_SIPHO:           return ("SiPho");

        default:
            break;
    }
    return ("???");
}

const char* spica_dbg_translate_driver_type_override(
    e_spica_driver_type driver_type_override)
{
    switch(driver_type_override)
    {
        case SPICA_DRIVER_TYPE_NONE:     return ("None");
        case SPICA_DRIVER_TYPE_EML:      return ("EML");
        case SPICA_DRIVER_TYPE_SIPHO:    return ("SiPho");
        case SPICA_DRIVER_TYPE_1VPP:     return ("1Vpp");

        default:
            break;
    }
    return ("???");
}

const char* spica_dbg_translate_tx_swing(
    e_spica_tx_swing tx_swing)
{
    switch(tx_swing)
    {
        case SPICA_TX_SWING_60p:  return (" 60 %");
        case SPICA_TX_SWING_70p:  return (" 70 %");
        case SPICA_TX_SWING_80p:  return (" 80 %");
        case SPICA_TX_SWING_90p:  return (" 90 %");
        case SPICA_TX_SWING_100p: return ("100 %");
        case SPICA_TX_SWING_110p: return ("110 %");
        case SPICA_TX_SWING_120p: return ("120 %");
        case SPICA_TX_SWING_NA:   return ("  n/a");
        default:
            break;
    }
    return ("  ???");
}

const char* spica_dbg_translate_lut_mode(
    e_spica_lut_mode lut_mode)
{
    switch (lut_mode)
    {
        case SPICA_LUT_4TAP:     return ("   4Tap");
        case SPICA_LUT_BYPASS:   return (" Bypass");
        case SPICA_LUT_7TAP_LIN: return ("7TapLIN");
        case SPICA_LUT_7TAP_LUT: return ("   7Tap");
        default:
            break;
    }
    return ("    ???");
}

const char* spica_dbg_translate_signalling(
    e_spica_signal_mode signalling)
{
    switch (signalling)
    {
        case SPICA_SIGNAL_MODE_NRZ: return ("NRZ");
        case SPICA_SIGNAL_MODE_PAM: return ("PAM");
        default:
            break;
    }
    return ("???");
}

const char* spica_dbg_translate_bootloader_error_status(
    e_spica_bootloader_error_status bootloader_error_status)
{
    switch(bootloader_error_status)
    {
        case SPICA_BOOT_DOWNLOAD_OK:              return ("Download Ok");
        case SPICA_BOOT_ERR_SPI_IMG_SIZE:         return ("SPI image Size");
        case SPICA_BOOT_ERR_SPI_IRAM_SIZE:        return ("SPI IRAM Size");
        case SPICA_BOOT_ERR_SPI_DRAM_SIZE:        return ("SPI DRAM Size");
        case SPICA_BOOT_ERR_SPI_RECEIVE_TIMEOUT:  return ("SPI Receive Timeout");
        case SPICA_BOOT_ERR_BOOT_CRC_FAIL:        return ("Boot CRC Fail");
        case SPICA_BOOT_BOOT_IN_PROGRESS:         return ("Boot in Progress");
        case SPICA_BOOT_ERR_SPI_RESET_TIMEOUT:    return ("SPI Reset Timeout");
        case SPICA_BOOT_ERR_MEMORY_GRANT:         return ("Memory Grant");
        case SPICA_BOOT_ERR_MESSAGE_UNNOWN_PARAM: return ("Message Unknown Parameter");
        case SPICA_BOOT_ERR_MESSAGE_INVALID_TYPE: return ("Message Invalid Type");
        case SPICA_BOOT_ERR_MESSAGE_ABORT:        return ("Message Abort");
        default:
            break;
    }
    return ("Unknown");
}

const char* spica_dbg_translate_six_bit_mode(
    uint8_t six_bit_mode)
{
    switch (six_bit_mode)
    {
        case SPICA_6BIT_MODE_DISABLE: return ("False");
        case SPICA_6BIT_MODE_ENABLE:  return (" True");
        case SPICA_6BIT_MODE_AUTO:    return (" Auto");
        default:
            break;
    }
    return (" ???");
}

const char* spica_dbg_translate_bootloader_status(
    uint16_t bootloader_status)
{
    /* rifle thru the status bit map and return the first hit! */
    for (uint32_t i = 0; i < 16; i++)
    {
        switch(bootloader_status & (1 << i))
        {
            case SPICA_BOOT_COMPLETE:               return ("Boot complete");
            case SPICA_BOOT_FROM_EEPROM_FAILED:     return ("Boot from EEPROM failed");
            case SPICA_BOOT_FROM_EEPROM_ABORTED:    return ("Boot from EEPROM aborted");
            case SPICA_EEPROM_EMPTY:                return ("EEPROM empty");
            case SPICA_BOOT_CORRUPT_IMAGE_DETECTED: return ("Boot corrupt image detected");
            case SPICA_BOOT_IN_PROGRESS:            return ("Boot in progress");
            default:
                break;
        }
    }
    return ("Unknown");
}

const char* spica_dbg_translate_rx_qc_snr_thresh(
    e_spica_rx_qc_snr_threshold snr_thresh)
{
    switch (snr_thresh)
    {
        case SPICA_RX_QC_SNR_THRESH_10p1dB:  return ("10.1 dB"); 
        case SPICA_RX_QC_SNR_THRESH_10p5dB:  return ("10.5 dB");
        case SPICA_RX_QC_SNR_THRESH_11dB  :  return ("11 dB  ");
        case SPICA_RX_QC_SNR_THRESH_11p5dB:  return ("11.5 dB");
        case SPICA_RX_QC_SNR_THRESH_12dB  :  return ("12 dB  ");
        case SPICA_RX_QC_SNR_THRESH_12p5dB:  return ("12.5 dB");
        case SPICA_RX_QC_SNR_THRESH_13dB  :  return ("13 dB  ");
        case SPICA_RX_QC_SNR_THRESH_13p5dB:  return ("13.5 dB");
        case SPICA_RX_QC_SNR_THRESH_14dB  :  return ("14 dB  ");
        case SPICA_RX_QC_SNR_THRESH_14p5dB:  return ("14.5 dB");
        case SPICA_RX_QC_SNR_THRESH_15dB  :  return ("15 dB  ");
        case SPICA_RX_QC_SNR_THRESH_15p5dB:  return ("15.5 dB");
        case SPICA_RX_QC_SNR_THRESH_16dB  :  return ("16 dB  ");
        case SPICA_RX_QC_SNR_THRESH_16p5dB:  return ("16.5 dB");
        case SPICA_RX_QC_SNR_THRESH_17dB  :  return ("17 dB  ");
        case SPICA_RX_QC_SNR_THRESH_17p5dB:  return ("17.5 dB");
        case SPICA_RX_QC_SNR_THRESH_18dB  :  return ("18 dB  ");
        case SPICA_RX_QC_SNR_THRESH_18p5dB:  return ("18.5 dB");
        case SPICA_RX_QC_SNR_THRESH_19dB  :  return ("19 dB  ");
        case SPICA_RX_QC_SNR_THRESH_19p5dB:  return ("19.5 dB");
        case SPICA_RX_QC_SNR_THRESH_20dB  :  return ("20 dB  ");
        case SPICA_RX_QC_SNR_THRESH_20p5dB:  return ("20.5 dB");
        case SPICA_RX_QC_SNR_THRESH_21dB  :  return ("21 dB  ");
        case SPICA_RX_QC_SNR_THRESH_21p5dB:  return ("21.5 dB");
        case SPICA_RX_QC_SNR_THRESH_22dB  :  return ("22 dB  ");
        case SPICA_RX_QC_SNR_THRESH_22p5dB:  return ("22.5 dB");
        case SPICA_RX_QC_SNR_THRESH_23dB  :  return ("23 dB  ");
        case SPICA_RX_QC_SNR_THRESH_23p5dB:  return ("23.5 dB");
        case SPICA_RX_QC_SNR_THRESH_24dB  :  return ("24 dB  ");
        case SPICA_RX_QC_SNR_THRESH_24p5dB:  return ("24.5 dB");
        case SPICA_RX_QC_SNR_THRESH_25dB  :  return ("25 dB  ");
        default:
            break;
    }
    return (" ???");
}

const char* spica_dbg_translate_los_ctrl_amp(
    e_spica_los_ctrl_amp los_ctrl_amp)
{
    switch (los_ctrl_amp)
    {
        case SPICA_LOS_CTRL_AMP_50 : return ("50 mV ");
        case SPICA_LOS_CTRL_AMP_100: return ("100 mV");
        case SPICA_LOS_CTRL_AMP_150: return ("150 mV");
        case SPICA_LOS_CTRL_AMP_200: return ("200 mV");
        case SPICA_LOS_CTRL_AMP_250: return ("250 mV");
        case SPICA_LOS_CTRL_AMP_300: return ("300 mV");
        case SPICA_LOS_CTRL_AMP_350: return ("350 mV");

        default:
            break;
    }
    return (" ???");
}

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * This method is used to check the TX rules for errors in configuration.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param intf    [I] - The ASIC interface being accessed.
 * @param rules   [I] - The default rules for the application.
 *
 * @private
 *
 * @since 1.1.0.0
 */
inphi_status_t spica_tx_check_rules(
    uint32_t          die,
    uint32_t          channel,
    e_spica_intf      intf,
    spica_tx_rules_t* tx_rules)
{
    inphi_status_t status = INPHI_OK;

    // don't warn about anything if the channel isn't enabled
    if(!tx_rules->channel_enable)
    {
        return INPHI_OK;
    }

    if(tx_rules->lut_mode == SPICA_LUT_4TAP)
    {
        if(tx_rules->fir_taps[4] || tx_rules->fir_taps[5] || tx_rules->fir_taps[6])
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_CRIT("%s:ch%d: fir_taps outside of range for 4TAP Tx FIR mode are set\n", spica_dbg_translate_intf(intf), channel);
#else
            INPHI_CRIT("%d:ch%d: fir_taps outside of range for 4TAP Tx FIR mode are set\n", intf, channel);
#endif
        }
    }

#if !defined(INPHI_REMOVE_PSR)
    if(intf == SPICA_INTF_STX) 
    {
        if((tx_rules->lut_mode == SPICA_LUT_7TAP_LIN) ||
           (tx_rules->lut_mode == SPICA_LUT_7TAP_LUT))
        {
            INPHI_CRIT("HTX:ch%d: 7TAP modes are not supported\n", channel);
        }
    }
#endif // defined(INPHI_REMOVE_PSR)

    return status;
}

/*
 * Copy the bundle storage to the bundle rules structure
 */
inphi_status_t spica_cp_bundle_storage_to_rules(
    spica_bundle_rules_t* bundle_rules)
{
    inphi_status_t status = INPHI_OK;

    if(!bundle_rules)
    {
        INPHI_CRIT("ERROR: Bundle rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    for (uint8_t bundle_idx = 0; bundle_idx < SPICA_MAX_BUNDLES; bundle_idx++) 
    {
        bundle_rules->en[bundle_idx]          = g_bundle_storage.en[bundle_idx];        
        bundle_rules->die[bundle_idx]         = g_bundle_storage.die[bundle_idx];       
        bundle_rules->line_ch_map[bundle_idx] = g_bundle_storage.line_ch_map[bundle_idx];
        bundle_rules->host_ch_map[bundle_idx] = g_bundle_storage.host_ch_map[bundle_idx];
    }

    return status;
}

/*
 * Copy the bundle rules structure to the bundle storage
 */
inphi_status_t spica_cp_bundle_rules_to_storage(
    spica_bundle_rules_t* bundle_rules)
{
    inphi_status_t status = INPHI_OK;

    if(!bundle_rules)
    {
        INPHI_CRIT("ERROR: Bundle rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    for (uint8_t bundle_idx = 0; bundle_idx < SPICA_MAX_BUNDLES; bundle_idx++) 
    {
        g_bundle_storage.en[bundle_idx]          = bundle_rules->en[bundle_idx];         
        g_bundle_storage.die[bundle_idx]         = bundle_rules->die[bundle_idx];        
        g_bundle_storage.line_ch_map[bundle_idx] = bundle_rules->line_ch_map[bundle_idx];
        g_bundle_storage.host_ch_map[bundle_idx] = bundle_rules->host_ch_map[bundle_idx];
    }

    return status;
}

uint32_t spica_bundle_get_die_from_bundle(
    uint32_t bundle_idx)
{
    return (g_bundle_storage.die[bundle_idx]);
}

void spica_bundle_ch_cfg(
    uint32_t bundle_idx);

inphi_status_t spica_bundle_cfg(
    spica_bundle_rules_t* bundle_rules)
{
    inphi_status_t status = INPHI_OK;

    if(!bundle_rules)
    {
        INPHI_CRIT("ERROR: Bundle_rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    INPHI_MEMSET(&g_bundle_storage, 0, sizeof(g_bundle_storage));

    status |= spica_cp_bundle_rules_to_storage(bundle_rules);

    for (uint8_t bundle_idx = 0; bundle_idx < SPICA_MAX_BUNDLES; bundle_idx++)
    {
        if (bundle_rules->en[bundle_idx])
        {
            spica_bundle_ch_cfg(bundle_idx);
        }
    }
    
    return status;
}

inphi_status_t spica_bundle_default_set(
    uint32_t die,
    spica_bundle_rules_t* bundle_rules)
{
    inphi_status_t status = INPHI_OK;

    uint32_t base_die = spica_package_get_base_die(die);

    if(!bundle_rules)
    {
        INPHI_CRIT("ERROR: Bundle_rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    e_spica_package_type package = spica_package_get_type(base_die);

    INPHI_MEMSET(bundle_rules, 0, sizeof(spica_bundle_rules_t));

    switch (package)
    {
        case SPICA_PACKAGE_TYPE_EML_BOT_15x14:
        case SPICA_PACKAGE_TYPE_EML_TOP_15x14:
        case SPICA_PACKAGE_TYPE_SIPHO_TOP_15x14:
            bundle_rules->en[0]          = true;
            bundle_rules->die[0]         = base_die | 1; // upper die
            bundle_rules->line_ch_map[0] = 0x001e;  // 000011110b ie ch 1..4
            bundle_rules->host_ch_map[0] = 0x001e;  // 000011110b

            bundle_rules->en[1]          = true;
            bundle_rules->die[1]         = base_die;     // lower die
            bundle_rules->line_ch_map[1] = 0x01e0;  // 111100000b ie ch 5..8
            bundle_rules->host_ch_map[1] = 0x01e0;  // 111100000b
            break;

        case SPICA_PACKAGE_TYPE_SIPHO_BOT_14x14:
            bundle_rules->en[0]          = true;
            bundle_rules->die[0]         = base_die;// lower die
            bundle_rules->line_ch_map[0] = 0x001e;  // 000011110b ie ch 1..4
            bundle_rules->host_ch_map[0] = 0x001e;  // 000011110b

            bundle_rules->en[1]          = true;
            bundle_rules->die[1]         = base_die | 1;  // upper die
            bundle_rules->line_ch_map[1] = 0x01e0;  // 111100000b ie ch 5..8
            bundle_rules->host_ch_map[1] = 0x01e0;  // 111100000b
            break;

        case SPICA_PACKAGE_TYPE_EML_12x13:      // PG3 12x13
        case SPICA_PACKAGE_TYPE_EML_12x13_REV1: // PG3 12x13 (Rev1)
        case SPICA_PACKAGE_TYPE_STD_10x13:      // PG3 10x13
            bundle_rules->en[0]          = true;
            bundle_rules->die[0]         = base_die;     // only die
            bundle_rules->line_ch_map[0] = 0x001e;  // 000011110b ie ch 1..4
            bundle_rules->host_ch_map[0] = 0x01fe;  // 111111110b ie ch 1..8
            break;

        case SPICA_PACKAGE_TYPE_UNMAPPED:       // Bare-die
            bundle_rules->en[0]          = true;
            bundle_rules->die[0]         = base_die;     // only die
            bundle_rules->line_ch_map[0] = 0x001e;  // 000011110b ie ch 1..4
            if (spica_package_has_pmr(base_die))
            {
                bundle_rules->host_ch_map[0] = 0x001e;  // 000011110b ie ch 1..4
            }
            else // host side is PSR
            {
                bundle_rules->host_ch_map[0] = 0x01fe;  // 111111110b ie ch 1..8
            }
            break;

        default: 
            INPHI_CRIT("ERROR: Bundle init invalid package %d\n", package);
            status = INPHI_ERROR;
            break;
    } 
    
    return status;
}

bool spica_bundle_is_en(
    uint32_t bundle_idx)
{
    return g_bundle_storage.en[bundle_idx];
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

void spica_bundle_dbg_print_rules(
    spica_bundle_rules_t* bundle_rules)
{
    uint32_t ch_num;

    if(!bundle_rules)
    {
        INPHI_CRIT("ERROR: Bundle_rules cannot be NULL!\n");
        return;
    }

    INPHI_NOTE("\n");
    INPHI_NOTE("Bundle Config               |  Line Ch|  Host Ch|\n");
    INPHI_NOTE("-------+--------+-----------+---------+---------+\n");
    INPHI_NOTE("Bundle |  Enable|        Die| 87654321| 87654321|\n");
    INPHI_NOTE("-------+--------+-----------+---------+---------+\n");
    for (uint8_t bundle_idx = 0; bundle_idx < SPICA_MAX_BUNDLES; bundle_idx++) 
    {
        INPHI_NOTE("     %d |", bundle_idx);
        INPHI_NOTE("%s", bundle_rules->en[bundle_idx] ? "    True" : "   False" );
        INPHI_NOTE("| 0x%08x", bundle_rules->die[bundle_idx]);
        INPHI_NOTE("| ");
        ch_num = 0;
        for (int32_t ch_idx = INBIT8; ch_num < 8; ch_idx >>= 1)
        {
            INPHI_NOTE("%s", (bundle_rules->line_ch_map[bundle_idx] & ch_idx) ? "1" : ".");
            ch_num++;
        }
        INPHI_NOTE("| ");
        ch_num = 0;
        for (int32_t ch_idx = INBIT8; ch_num < 8; ch_idx >>= 1)
        {
            INPHI_NOTE("%s", (bundle_rules->host_ch_map[bundle_idx] & ch_idx) ? "1" : ".");
            ch_num++;
        }
        INPHI_NOTE("|\n");
    }
    INPHI_NOTE("\n");
}

void spica_bundle_dbg_query_rules(
    spica_bundle_rules_t* bundle_rules)
{
    spica_cp_bundle_storage_to_rules(bundle_rules);
}

void spica_bundle_dbg_query_print_rules(void)
{
    spica_bundle_rules_t bundle_rules;

    spica_bundle_dbg_query_rules(&bundle_rules);
    spica_bundle_dbg_print_rules(&bundle_rules);
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
void spica_dbg_print_fw_warn_if_mismatch(
    uint32_t die)
{
    uint32_t fw_rev0 = SPICA_MCU_FIRMWARE_REV0_OVL__READ(die);
    uint32_t fw_rev1 = SPICA_MCU_FIRMWARE_REV1_OVL__READ(die);

    uint16_t fw_major    = SPICA_MCU_FIRMWARE_REV1_OVL__MAJOR__GET(fw_rev1);
    uint16_t fw_minor    = SPICA_MCU_FIRMWARE_REV1_OVL__MINOR__GET(fw_rev1);
    uint16_t fw_revision = SPICA_MCU_FIRMWARE_REV1_OVL__REVISION__GET(fw_rev1);
    uint16_t fw_build    = SPICA_MCU_FIRMWARE_REV0_OVL__BUILD__GET(fw_rev0);

    if ((fw_major    != SPICA_APP_VERSION_MAJOR)    ||
        (fw_minor    != SPICA_APP_VERSION_MINOR)    ||
        (fw_revision != SPICA_APP_VERSION_REVISION) ||
        (fw_build    != SPICA_APP_VERSION_BUILD))
    {
        INPHI_FPRINTF(stderr, "\n\n");
        INPHI_WARN("MCU Firmware running on die 0x%08x may not be compatible with API\n", die);
        INPHI_WARN("MCU Firmware running (major.minor.revision.build) %d.%d.%d.%d but API expecting %d.%d.%d.%d\n",
                        fw_major,
                        fw_minor,
                        fw_revision,
                        fw_build,
                        SPICA_APP_VERSION_MAJOR,
                        SPICA_APP_VERSION_MINOR,
                        SPICA_APP_VERSION_REVISION,
                        SPICA_APP_VERSION_BUILD);
        INPHI_WARN("You can disable this warning by setting rules.fw_warn_if_mismatched = false\n");
        INPHI_FPRINTF(stderr, "\n\n");
    }
}
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

void spica_dbg_print_rules_per_bundle(
    uint32_t       die,
    uint32_t       bundle_idx,
    spica_rules_t* rules)
{
    char ver[80];
    int16_t tap;
    uint32_t ch_num;
    uint32_t base_die = spica_package_get_base_die(die);

    e_spica_package_type package = spica_package_get_type(base_die);
    spica_bundle_rules_t bundle_rules;

    spica_cp_bundle_storage_to_rules(&bundle_rules);

    spica_version(ver, 80);
    INPHI_NOTE("\n%s", ver);
    spica_version_firmware(base_die, ver, 80);
    INPHI_NOTE("%s\n", ver);

    if(!rules)
    {
        INPHI_CRIT("ERROR: Rules cannot be NULL!\n");
        return;
    }

    if (!spica_bundle_is_en(bundle_idx))
    {
        INPHI_CRIT("ERROR: Bundle not enabled %d\n", bundle_idx);
        return;
    }

    INPHI_NOTE("Device Initialization Rules\n\n");
    
    if (spica_package_has_pmr(die))
    {
#if !defined(INPHI_REMOVE_PMR)
        INPHI_NOTE("Top Rules\n"
                   "  Die                        0x%08x\n"
                   "  Package                    %s\n"
                   "  Efuse Driver Override      %s\n"
                   "  FW Download Timeout        %d milli-secs\n"
                   "  FW Warn if Mismatched      %s\n" 
                   "  LRX QC SNR Thresh mm Enter %s\n" 
                   "  LRX QC SNR Thresh mm Exit  %s\n" 
                   "  LRX QC SLC Err Limit       %d\n"
                   "  HRX QC SNR Thresh mm Enter %s\n" 
                   "  HRX QC SNR Thresh mm Exit  %s\n" 
                   "  HRX QC SLC Err Limit       %d\n" 
                   "  LRX LOS DSRT Ctrl Startup  %s\n" 
                   "  LRX LOS ASRT Ctrl Startup  %s\n" 
                   "  LRX LOS ASRT Ctrl Datamode %s\n",

                   /* Top Rules */
                   base_die,
                   spica_dbg_translate_package_type(package),
                   spica_dbg_translate_driver_type_override(rules->driver_type_override),
                   rules->fw_dwld_timeout * SPICA_MCU_POLL_DELAY_MS,
                   rules->fw_warn_if_mismatched ? "True": "False",
                   spica_dbg_translate_rx_qc_snr_thresh(rules->lrx_qc.snr_threshold_mm_enter),
                   spica_dbg_translate_rx_qc_snr_thresh(rules->lrx_qc.snr_threshold_mm_exit),
                   rules->lrx_qc.slc_err_limit,
                   spica_dbg_translate_rx_qc_snr_thresh(rules->hrx_qc.snr_threshold_mm_enter),
                   spica_dbg_translate_rx_qc_snr_thresh(rules->hrx_qc.snr_threshold_mm_exit),
                   rules->hrx_qc.slc_err_limit,
                   spica_dbg_translate_los_ctrl_amp(rules->lrx_los_dsrt_ctrl_startup),
                   spica_dbg_translate_los_ctrl_amp(rules->lrx_los_asrt_ctrl_startup),
                   spica_dbg_translate_los_ctrl_amp(rules->lrx_los_asrt_ctrl_datamode)
                   );
#endif // defined(INPHI_REMOVE_PMR)
    }
    else // PSR package ie no HRX QC
    {
#if !defined(INPHI_REMOVE_PSR)
        INPHI_NOTE("Top Rules\n"
                   "  Die                        0x%08x\n"
                   "  Package                    %s\n"
                   "  Efuse Driver Override      %s\n"
                   "  FW Download Timeout        %d milli-secs\n"
                   "  FW Warn if Mismatched      %s\n" 
                   "  LRX QC SNR Thresh mm Enter %s\n" 
                   "  LRX QC SNR Thresh mm Exit  %s\n" 
                   "  LRX QC SLC Err Limit       %d\n"
                   "  LRX LOS DSRT Ctrl Startup  %s\n" 
                   "  LRX LOS ASRT Ctrl Startup  %s\n" 
                   "  LRX LOS ASRT Ctrl Datamode %s\n",

                   /* Top Rules */
                   base_die,
                   spica_dbg_translate_package_type(package),
                   spica_dbg_translate_driver_type_override(rules->driver_type_override),
                   rules->fw_dwld_timeout * SPICA_MCU_POLL_DELAY_MS,
                   rules->fw_warn_if_mismatched ? "True": "False",
                   spica_dbg_translate_rx_qc_snr_thresh(rules->lrx_qc.snr_threshold_mm_enter),
                   spica_dbg_translate_rx_qc_snr_thresh(rules->lrx_qc.snr_threshold_mm_exit),
                   rules->lrx_qc.slc_err_limit,
                   spica_dbg_translate_los_ctrl_amp(rules->lrx_los_dsrt_ctrl_startup),
                   spica_dbg_translate_los_ctrl_amp(rules->lrx_los_asrt_ctrl_startup),
                   spica_dbg_translate_los_ctrl_amp(rules->lrx_los_asrt_ctrl_datamode)
                   );
#endif // defined(INPHI_REMOVE_PSR)
    }

    INPHI_NOTE("\n");

    INPHI_NOTE("Bundle Rules\n"
               "  Bundle                 %d\n"
               "  Line Ch Map            0x%04x\n"
               "  Host Ch Map            0x%04x\n"
               "  Operational Mode       %s\n"
               "  Protocol Mode          %s\n",

               /* Bundle Rules */
               bundle_idx,
               bundle_rules.line_ch_map[bundle_idx],
               bundle_rules.host_ch_map[bundle_idx],
               spica_dbg_translate_operational_mode(rules->operational_mode),
               spica_dbg_translate_protocol_mode(rules->protocol_mode)
               );

    // OTX XBAR --------------------------------------------------------
    ch_num = 0; 
    INPHI_NOTE("\nOTX XBR Rules     |");
    for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
    {
        if (bundle_rules.line_ch_map[bundle_idx] & ch_idx)
        {
            INPHI_NOTE("     Ch%d|", ch_num);
        }
        ch_num++;
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("------------------+");
    for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
    {
        if (bundle_rules.line_ch_map[bundle_idx] & ch_idx)
        {
            INPHI_NOTE("--------+");
        }
    }

    INPHI_NOTE("\n");
    INPHI_NOTE("  Source Ch 1     ");
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_OTX)
    {
        INPHI_NOTE("|       %x", rules->otx_xbar_src_chan[channel][0]);
    }
    INPHI_NOTE("|\n");
    INPHI_NOTE("  Source Ch 2     ");
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_OTX)
    {
        INPHI_NOTE("|       %x", rules->otx_xbar_src_chan[channel][1]);
    }
    INPHI_NOTE("|\n");
    INPHI_NOTE("  Source Ch 3     ");
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_OTX)
    {
        INPHI_NOTE("|       %x", rules->otx_xbar_src_chan[channel][2]);
    }
    INPHI_NOTE("|\n");
    INPHI_NOTE("  Source Ch 4     ");
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_OTX)
    {
        INPHI_NOTE("|       %x", rules->otx_xbar_src_chan[channel][3]);
    }
    INPHI_NOTE("|\n");

    // MTX/STX XBAR --------------------------------------------------------
    if (spica_package_has_pmr(die))
    {
        INPHI_NOTE("\nMTX XBR Rules     |");
    }
    if (spica_package_has_psr(die))
    {
        INPHI_NOTE("\nSTX XBR Rules     |");
    }
    ch_num = 0; 
    for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
    {
        if (bundle_rules.host_ch_map[bundle_idx] & ch_idx)
        {
            INPHI_NOTE("     Ch%d|", ch_num);
        }
        ch_num++;
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("------------------+");
    for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
    {
        if (bundle_rules.host_ch_map[bundle_idx] & ch_idx)
        {
            INPHI_NOTE("--------+");
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    if (spica_package_has_pmr(die))
    {
        INPHI_NOTE("\n");
        INPHI_NOTE("  Source Ch 1     ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_MTX)
        {
            INPHI_NOTE("|       %x", rules->mtx_xbar_src_chan[channel][0]);
        }
        INPHI_NOTE("|\n");
        INPHI_NOTE("  Interleave      ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_MTX)
        {
            INPHI_NOTE("|       %x", rules->mtx_xbar_src_chan[channel][1]);
        }
        INPHI_NOTE("|\n");
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    if (spica_package_has_psr(die))
    {
        INPHI_NOTE("\n");
        INPHI_NOTE("  Source Ch 1     ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_STX)
        {
            INPHI_NOTE("|       %x", rules->stx_xbar_src_chan[channel][0]);
        }
        INPHI_NOTE("|\n");
        INPHI_NOTE("  Interleave      ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_STX)
        {
            INPHI_NOTE("|       %x", rules->stx_xbar_src_chan[channel][1]);
        }
        INPHI_NOTE("|\n");
    }
#endif // defined(INPHI_REMOVE_PSR)

    // OTX CLK XBAR --------------------------------------------------------
    ch_num = 0; 
    INPHI_NOTE("\nOTX CLK XBR Rules |");
    for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
    {
        if (bundle_rules.line_ch_map[bundle_idx] & ch_idx)
        {
            INPHI_NOTE("     Ch%d|", ch_num);
        }
        ch_num++;
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("------------------+");
    for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
    {
        if (bundle_rules.line_ch_map[bundle_idx] & ch_idx)
        {
            INPHI_NOTE("--------+");
        }
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("  Clk Source Ch   ");
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_OTX)
    {
        INPHI_NOTE("|       %x", rules->otx_clk_xbar[channel]);
    }
    INPHI_NOTE("|\n");

    // MTX/STX CLK XBAR --------------------------------------------------------
    if (spica_package_has_pmr(die))
    {
        INPHI_NOTE("\nMTX CLK XBR Rules |");
    }
    if (spica_package_has_psr(die))
    {
        INPHI_NOTE("\nSTX CLK XBR Rules |");
    }
    ch_num = 0; 
    for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
    {
        if (bundle_rules.host_ch_map[bundle_idx] & ch_idx)
        {
            INPHI_NOTE("     Ch%d|", ch_num);
        }
        ch_num++;
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("------------------+");
    for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
    {
        if (bundle_rules.host_ch_map[bundle_idx] & ch_idx)
        {
            INPHI_NOTE("--------+");
        }
    }
    if (spica_package_has_pmr(die))
    {
        INPHI_NOTE("\n");
        INPHI_NOTE("  Clk Source Ch   ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_MTX)
        {
            INPHI_NOTE("|       %x", rules->mtx_clk_xbar[channel]);
        }
        INPHI_NOTE("|\n");
    }
    if (spica_package_has_psr(die))
    {
        INPHI_NOTE("\n");
        INPHI_NOTE("  Clk Source      ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_STX)
        {
            INPHI_NOTE("|       %x", rules->stx_clk_xbar[channel]);
        }
        INPHI_NOTE("|\n");
    }

    for (uint8_t side = 0; side < 2; side++)
    {
        e_spica_intf         rx_intf;
        e_spica_intf         tx_intf;
        spica_ant_rx_rules_t *rx_ant_rules = NULL;
        spica_sun_rx_rules_t *rx_sun_rules = NULL;
        spica_tx_rules_t     *tx_rules = NULL;

        //
        // Rx Interfaces ------------------------------------------------------------------------------------------------
        //

        if (side == 0) // line side, ORX 
        {
            rx_intf = SPICA_INTF_ORX;
            rx_ant_rules = rules->orx;
            ch_num = 0;
            INPHI_NOTE("\n");
            INPHI_NOTE("ORX Ch Rules      |");
            for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
            {
                if (bundle_rules.line_ch_map[bundle_idx] & ch_idx)
                {
                    INPHI_NOTE("     Ch%d|", ch_num);
                }
                ch_num++;
            }
            INPHI_NOTE("\n");
            INPHI_NOTE("------------------+");
            for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
            {
                if (bundle_rules.line_ch_map[bundle_idx] & ch_idx)
                {
                    INPHI_NOTE("--------+");
                }
            }

            INPHI_NOTE("\n");
            INPHI_NOTE("  Ch Enable       ");
            SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
            {
                INPHI_NOTE("%s", rx_ant_rules[channel].channel_enable ? "|    True" : "|   False");
            }

            INPHI_NOTE("|\n");
            INPHI_NOTE("  Signalling      ");
            SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
            {
                INPHI_NOTE("|     %s", spica_dbg_translate_signalling(rx_ant_rules[channel].signalling));
            }

            INPHI_NOTE("|\n");
            INPHI_NOTE("  Baud Rate (GBd) ");
            SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
            {
                INPHI_NOTE("|    %s", spica_dbg_translate_baud_rate(rx_ant_rules[channel].baud_rate));
            }

            INPHI_NOTE("|\n");
            INPHI_NOTE("  IEEE Demap      ");
            SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
            {
                INPHI_NOTE("%s", rx_ant_rules[channel].ieee_demap ? "|    True" : "|   False");
            }

            INPHI_NOTE("|\n");
            INPHI_NOTE("  Gray Mapping    ");
            SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
            {
                INPHI_NOTE("%s", rx_ant_rules[channel].gray_mapping ? "|    True" : "|   False");
            }

            INPHI_NOTE("|\n");
            INPHI_NOTE("  Invert Ch       ");
            SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
            {
                INPHI_NOTE("%s", rx_ant_rules[channel].invert_chan ? "|    True" : "|   False");
            }

            INPHI_NOTE("|\n");
            INPHI_NOTE("  6-Bit Mode      ");
            SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
            {
                INPHI_NOTE("|   %s", spica_dbg_translate_six_bit_mode(rx_ant_rules[channel].six_bit_mode));
            }

            INPHI_NOTE("|\n");
            INPHI_NOTE("  Force Mission M ");
            SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
            {
                INPHI_NOTE("%s", rx_ant_rules[channel].force_mission_mode ? "|    True" : "|   False");
            }
            INPHI_NOTE("|\n");

            INPHI_NOTE("  SDT DSP Enable  ");
            SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
            {
                INPHI_NOTE("%s", rx_ant_rules[channel].sdt_dsp_en ? "|    True" : "|   False");
            }
            INPHI_NOTE("|\n");
        } 
        else // host side
        {
            if (spica_package_get_intf(base_die) & SPICA_INTF_MRX)
            {
                rx_intf = SPICA_INTF_MRX;
                rx_ant_rules = rules->mrx;
                ch_num = 0;
                INPHI_NOTE("\n");
                INPHI_NOTE("MRX Ch Rules      |");
            }
            else
            {
                rx_intf = SPICA_INTF_SRX;
                rx_sun_rules = rules->srx;
                ch_num = 0;
                INPHI_NOTE("\n");
                INPHI_NOTE("SRX Ch Rules      |");
            }

            for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
            {
                if (bundle_rules.host_ch_map[bundle_idx] & ch_idx)
                {
                    INPHI_NOTE("     Ch%d|", ch_num);
                }
                ch_num++;
            }
            INPHI_NOTE("\n");
            INPHI_NOTE("------------------+");
            for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
            {
                if (bundle_rules.host_ch_map[bundle_idx] & ch_idx)
                {
                    INPHI_NOTE("--------+");
                }
            }

            if (spica_package_get_intf(base_die) & SPICA_INTF_MRX)
            {
                INPHI_NOTE("\n");
                INPHI_NOTE("  Ch Enable       ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_ant_rules[channel].channel_enable ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Signalling      ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("|     %s", spica_dbg_translate_signalling(rx_ant_rules[channel].signalling));
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Baud Rate (GBd) ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("|    %s", spica_dbg_translate_baud_rate(rx_ant_rules[channel].baud_rate));
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  IEEE Demap      ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_ant_rules[channel].ieee_demap ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Gray Mapping    ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_ant_rules[channel].gray_mapping ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Invert Ch       ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_ant_rules[channel].invert_chan ? "|    True" : "|   False");
                }
                INPHI_NOTE("|\n");

                INPHI_NOTE("  Force Mission M ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_ant_rules[channel].force_mission_mode ? "|    True" : "|   False");
                }
                INPHI_NOTE("|\n");

                INPHI_NOTE("  SDT DSP Enable  ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_ant_rules[channel].sdt_dsp_en ? "|    True" : "|   False");
                }
                INPHI_NOTE("|\n");
            }
            else // host side, SRX
            {
                INPHI_NOTE("\n");
                INPHI_NOTE("  Ch Enable       ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].channel_enable ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Signalling      ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("|     %s", spica_dbg_translate_signalling(rx_sun_rules[channel].signalling));
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Baud Rate (GBd) ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("|    %s", spica_dbg_translate_baud_rate(rx_sun_rules[channel].baud_rate));
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Gray Mapping    ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].gray_mapping ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Invert Ch       ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].invert_chan ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  IEEE Demap      ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].ieee_demap ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Skip Adapt      ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].skip_adapt ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  CTLE Adapt Dis  ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].ctle_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  CTLE Override   ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("|  0x%04x", rx_sun_rules[channel].ctle_override);
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  CTLE C Ad En    ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].ctle_c_adapt_en ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  CTLE R Ad Dis   ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].ctle_r_adapt_dis? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  LFEQ Adapt Dis  ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].lfeq_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  LFEQ Override   ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("|  0x%04x", rx_sun_rules[channel].lfeq_override);
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  DFE Adapt Dis   ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].dfe_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Data Skw Ad Dis ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].data_skew_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Edge Skw Ad Dis ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].edge_skew_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  SLC Adapt Dis   ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].slc_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Edge Off Ad Dis ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].edge_off_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  AGC Adapt Dis   ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].agc_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  VCO Tmp Cal Dis ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].vco_temp_cal_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  AFE BW Ad Dis   ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].afe_bw_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  DC Off Ad Dis   ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].dc_off_adapt_dis ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  LFEQ Ad Aft Dis ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].lfeq_adapt_dis_after_init_adapt ? "|   False" : "|    True");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  VCO Mode        ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("%s", rx_sun_rules[channel].vco_mode ? "|    True" : "|   False");
                }

                INPHI_NOTE("|\n");
                INPHI_NOTE("  Baudrate (kBps) ");
                SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, rx_intf)
                {
                    INPHI_NOTE("|%8d", rx_sun_rules[channel].rates);
                }

                INPHI_NOTE("|\n");

            }
        }
        //
        // Tx Interfaces ------------------------------------------------------------------------------------------------
        //

        if (side == 0) // line side, OTX 
        {
            tx_intf = SPICA_INTF_OTX;
            tx_rules = rules->otx;
            ch_num = 0;
            INPHI_NOTE("\n");
            INPHI_NOTE("OTX Ch Rules      |");
            for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
            {
                if (bundle_rules.line_ch_map[bundle_idx] & ch_idx)
                {
                    INPHI_NOTE("     Ch%d|", ch_num);
                }
                ch_num++;
            }
            INPHI_NOTE("\n");
            INPHI_NOTE("------------------+");
            for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
            {
                if (bundle_rules.line_ch_map[bundle_idx] & ch_idx)
                {
                    INPHI_NOTE("--------+");
                }
            }
        } 
        else // host side, MTX or STX
        {
            if (spica_package_get_intf(base_die) & SPICA_INTF_MTX)
            {
                // PMR interface on the host side
                tx_intf = SPICA_INTF_MTX;
                tx_rules = rules->mtx;
                INPHI_NOTE("\n");
                INPHI_NOTE("MTX Ch Rules      |");
            }
            else 
            {
                // PSR interface on the host side
                tx_intf = SPICA_INTF_STX;
                tx_rules = rules->stx; 
                INPHI_NOTE("\n");
                INPHI_NOTE("STX Ch Rules      |");
            }
            ch_num = 0;
            for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
            {
                if (bundle_rules.host_ch_map[bundle_idx] & ch_idx)
                {
                    INPHI_NOTE("     Ch%d|", ch_num);
                }
                ch_num++;
            }
            INPHI_NOTE("\n");
            INPHI_NOTE("------------------+");
            for (uint32_t ch_idx = 1; ch_idx <= INBIT15; ch_idx <<= 1)
            {
                if (bundle_rules.host_ch_map[bundle_idx] & ch_idx)
                {
                    INPHI_NOTE("--------+");
                }
            }
        } 

        INPHI_NOTE("\n");
        INPHI_NOTE("  Ch Enable       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("%s", tx_rules[channel].channel_enable ? "|    True" : "|   False");
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  Signalling      ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("|     %s", spica_dbg_translate_signalling(tx_rules[channel].signalling));
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  Baud Rate       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("|    %s", spica_dbg_translate_baud_rate(tx_rules[channel].baud_rate));
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  Squelch Lock    ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("%s", tx_rules[channel].squelch_lock ? "|    True" : "|   False");
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  LUT Mode        ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("| %s", spica_dbg_translate_lut_mode(tx_rules[channel].lut_mode));
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  IEEE Demap      ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("%s", tx_rules[channel].ieee_demap ? "|    True" : "|   False");
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  Gray Mapping    ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("%s", tx_rules[channel].gray_mapping ? "|    True" : "|   False");
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  Invert Ch       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("%s", tx_rules[channel].invert_chan ? "|    True" : "|   False");
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  Tx Swing        ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("|   %s", spica_dbg_translate_tx_swing(tx_rules[channel].swing));
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  DFE Precoder En ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            INPHI_NOTE("%s", tx_rules[channel].dfe_precoder_en ? "|    True" : "|   False");
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  FIR Tap 1       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        { 
            tap = tx_rules[channel].fir_taps[0];
            if ((tap >= -1000) && (tap <= 1000)) { INPHI_NOTE("|    %4d", tap); }
            else { INPHI_NOTE("|     ???"); }
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  FIR Tap 2       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            tap = tx_rules[channel].fir_taps[1];
            if ((tap >= -1000) && (tap <= 1000)) { INPHI_NOTE("|    %4d", tap); }
            else  { INPHI_NOTE("|     ???"); }
        }
        INPHI_NOTE("|\n");
        INPHI_NOTE("  FIR Tap 3       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            tap = tx_rules[channel].fir_taps[2];
            if ((tap >= -1000) && (tap <= 1000)) { INPHI_NOTE("|    %4d", tap); }
            else  { INPHI_NOTE("|     ???"); }
        }
        INPHI_NOTE("|\n");
        INPHI_NOTE("  FIR Tap 4       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            tap = tx_rules[channel].fir_taps[3];
            if ((tap >= -1000) && (tap <= 1000)) { INPHI_NOTE("|    %4d", tap); }
            else  { INPHI_NOTE("|     ???"); }
        }
        INPHI_NOTE("|\n");
        INPHI_NOTE("  FIR Tap 5       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            tap = tx_rules[channel].fir_taps[4];
            if ((tap >= -1000) && (tap <= 1000)) { INPHI_NOTE("|    %4d", tap); }
            else  { INPHI_NOTE("|     ???"); }
        }
        INPHI_NOTE("|\n");
        INPHI_NOTE("  FIR Tap 6       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            tap = tx_rules[channel].fir_taps[5];
            if ((tap >= -1000) && (tap <= 1000)) { INPHI_NOTE("|    %4d", tap); }
            else  { INPHI_NOTE("|     ???"); }
        }
        INPHI_NOTE("|\n");
        INPHI_NOTE("  FIR Tap 7       ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            tap = tx_rules[channel].fir_taps[6];
            if ((tap >= -1000) && (tap <= 1000)) { INPHI_NOTE("|    %4d", tap); }
            else  { INPHI_NOTE("|     ???"); }
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  Inner Eye 1     ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            tap = tx_rules[channel].inner_eye1;
            if ((tap >= 500) && (tap <= 1500)) { INPHI_NOTE("|    %4d", tap); }
            else  { INPHI_NOTE("|     ???"); }
        }

        INPHI_NOTE("|\n");
        INPHI_NOTE("  Inner Eye 2     ");
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, tx_intf)
        {
            tap = tx_rules[channel].inner_eye2;
            if ((tap >= 1500) && (tap <= 2500)) { INPHI_NOTE("|    %4d", tap); }
            else  { INPHI_NOTE("|     ???"); }
        }

        INPHI_NOTE("|\n");
    }
    INPHI_NOTE("\n");
}

// forward declaration
inphi_status_t spica_cp_overlays_to_rules(
    uint32_t       die,
    uint32_t       bundle_idx,
    spica_rules_t* rules);

/**
 * This method is used to fetch then print the rules of a 
 * specific bundle.
 */
void spica_dbg_query_print_rules_per_bundle(
    uint32_t die,
    uint32_t bundle_idx)
{
    spica_rules_t rules;

    if (!spica_bundle_is_en(bundle_idx))
    {
        INPHI_CRIT("ERROR: Bundle not enabled %d\n", bundle_idx);
        return;
    }

    spica_cp_overlays_to_rules(die, bundle_idx, &rules);

    spica_dbg_print_rules_per_bundle(die, bundle_idx, &rules);
}

/**
 * This method is used to fetch then print the rules.
 */
void spica_dbg_query_print_rules(
    uint32_t die)
{
    for (uint8_t bundle_idx = 0; bundle_idx < SPICA_MAX_BUNDLES; bundle_idx++) 
    {
        if (spica_bundle_is_en(bundle_idx))
        {   
            spica_dbg_query_print_rules_per_bundle(die, bundle_idx);
        }
    }
}

/**
 * This method is used to fetch then print the rules.
 */
void spica_dbg_print_rules(
    uint32_t die, 
    spica_rules_t* rules)
{
    for (uint8_t bundle_idx = 0; bundle_idx < SPICA_MAX_BUNDLES; bundle_idx++) 
    {
        if (spica_bundle_is_en(bundle_idx))
        {   
            spica_dbg_print_rules_per_bundle(die, bundle_idx, rules);
        }
    }
}

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * This is an internal method used to program the API version
 * number in one of the scratch registers so that it can be
 * identified through register dumps
 *
 * @param die [I] - The ASIC die being accessed.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @private
 *
 * @since 0.1
 */
inphi_status_t spica_init_api_version(
    uint32_t die)
{
    SPICA_LOCK(die);

    SPICA_MCU_API_INFO0_OVL__BUILD__RMW(die, SPICA_API_VERSION_UPDATE);
    SPICA_MCU_API_INFO1_OVL__MAJOR__RMW(die, SPICA_API_VERSION_MAJOR);
    SPICA_MCU_API_INFO1_OVL__MINOR__RMW(die, SPICA_API_VERSION_MINOR);
    SPICA_MCU_API_INFO1_OVL__REVISION__RMW(die, SPICA_API_VERSION_REVISION);
    
    SPICA_UNLOCK(die);
    
    return INPHI_OK;
}

// Check to see if the FW is running ok
bool spica_is_fw_running_ok(
    uint32_t   die)
{
    bool ok = true;
    SPICA_LOCK(die);
    uint16_t fw_mode       = SPICA_MCU_FW_MODE__READ(die);
    uint16_t fw_exception  = SPICA_MCU_SP6_FW_STATUS__EXCEPTION__READ(die);
    uint16_t fw_top_state  = SPICA_MCU_SP5_TOP_STATE__READ(die);
    uint16_t fw_loop_count = SPICA_MCU_SP2_LOOP_COUNT__READ(die);
    uint16_t fw_stalled    = SPICA_MCU_GEN_CFG__RUNSTALL__READ(die);

    // get the state of the FW
    if ((fw_mode != 0xACC0)      || // FW not running application code
        (fw_exception == 1)      || // FW has an exception
        (fw_top_state == 0xffff) || // FW high-level state stuck in start-up
        (fw_stalled == 1))          // MCU is stalled
    {
        ok = false;
    }

    // Check to see if the loop counter is incrementing or not.
    int max_delay = 500;
    bool loop_counter_incrementing = false;
    while(max_delay > 0)
    {
        // Delay a bit to see if the loop counter is incrementing
        INPHI_MDELAY(5);

        // If the loop counter changed then it's incrementing
        // so break out right away.
        if(fw_loop_count != SPICA_MCU_SP2_LOOP_COUNT__READ(die))
        {
            loop_counter_incrementing = true;
            break;
        }
        max_delay -= 5;
    }

    if(!loop_counter_incrementing)
    {
        ok = false;
    }

    // if the FW state is not ok, print out debug info
    if (!ok)
    {
        INPHI_NOTE("\nERROR: FW on die 0x%08x not running ok, printing state:\n", die);
        if (fw_mode != 0xACC0) 
        {
            INPHI_NOTE("  - FW NOT in application mode, mode = (UNKNOWN)0x%04x\n", fw_mode); 
        }
        else
        {
            INPHI_NOTE("  - FW in APPLICATION (0xACC0) mode\n");
        }

        if (fw_exception == 1)
        {
            INPHI_NOTE("  - FW hit an unrecoverable exception and cannot continue\n");
        }
        else
        {
            INPHI_NOTE("  - FW hit NO unrecoverable exceptions\n");
        }

        if (fw_top_state == 0xffff)
        {
            INPHI_NOTE("  - FW high-level state stuck in start-up\n");
        }
        else
        {
            INPHI_NOTE("  - FW high-level state OK, state = 0x%04x\n", fw_top_state);
        }

        if (!loop_counter_incrementing)
        {
            INPHI_NOTE("  - FW loop counter not incrementing, stuck at 0x%04x\n", fw_loop_count);
        }
        else
        {
            INPHI_NOTE("  - FW loop count incrementing\n");
        }

        if (fw_stalled == 1) 
        {
            INPHI_NOTE("  - MCU is stalled\n");
        }
        else
        {
            INPHI_NOTE("  - MCU is NOT stalled\n");
        }

        INPHI_NOTE("\n");
    }

    SPICA_UNLOCK(die);
    return ok;
}

#if defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW==1)
/*
 * Download the FW to the MCU
 */
inphi_status_t spica_dwld_fw(
    uint32_t  die,
    uint32_t  fw_dwld_timeout,
    bool      fw_warn_if_mismatched) 
{
    inphi_status_t status = INPHI_OK;
 
    // take part out of global reset
    SPICA_MMD30_RESET_CFG__WRITE(die, 0x0);
    
    status |= spica_mcu_download_firmware(die, true);

    // We must be in app fw mode to run spica_init
    status |= spica_mcu_block_application_mode(die, fw_dwld_timeout);

    if(INPHI_OK != status)
    {
        INPHI_CRIT("ERROR: Cannot run spica_init unless the device %d is in application FW mode\n", die);
    }
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    else if(fw_warn_if_mismatched)
    {
        spica_dbg_print_fw_warn_if_mismatch(die);
    }
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    
    return status;
}
#endif // defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW==1)

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/* Print the bootloader status */
inphi_status_t spica_bootloader_status_print(
    spica_bootloader_status_t* bootloader_status)
{
    inphi_status_t status = INPHI_OK;

    INPHI_NOTE("Bootloader status:       %s\n", spica_dbg_translate_bootloader_status(bootloader_status->status));
    INPHI_NOTE("Bootloader error status: %s\n", spica_dbg_translate_bootloader_error_status(bootloader_status->error_status));
    INPHI_NOTE("Bootloader retries:      %d\n", (bootloader_status->retries));

    return(status);
}

/* Print the bootloader status */
inphi_status_t spica_bootloader_status_query_print(
    uint32_t die)
{
    inphi_status_t status = INPHI_OK;
    spica_bootloader_status_t bootloader_status;

    status |= spica_bootloader_status_query(die, &bootloader_status);

    status |= spica_bootloader_status_print(&bootloader_status);

    return(status);
}
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/* Fetch the bootloader status */
inphi_status_t spica_bootloader_status_query(
    uint32_t die,
    spica_bootloader_status_t* bootloader_status)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data;

    if(!bootloader_status)
    {
        INPHI_CRIT("ERROR: Bootloader_status cannot be NULL!\n");
        return(INPHI_ERROR);
    }

    data = SPICA_MCU_BOOT_STATUS__READ(die);
    bootloader_status->status = data & 0xff00;
    bootloader_status->error_status = (e_spica_bootloader_error_status)(data & 0x000f);
    bootloader_status->retries = (data >> 4) & 0x000f;

    return(status);
}

/**
 * Returns the enabled interfaces based on the op_mode
 * return type is e_spica_intf's |'d together
 */
static e_spica_intf spica_op_mode_en_intfs(
    uint32_t die,
    e_spica_operational_mode op_mode)
{
    //use 32b int for now, then cast as the enum when returning
    uint32_t intf = 0;
    switch(op_mode)
    {
        case SPICA_MODE_MISSION_MODE:
        case SPICA_MODE_DUAL_PRBS:
        case SPICA_MODE_INGRESS_PRBS:
        case SPICA_MODE_EGRESS_PRBS:
            intf |= SPICA_INTF_OTX;
            intf |= SPICA_INTF_ORX;
            if (spica_package_has_pmr(die))
            {
                intf |= SPICA_INTF_MTX;
                intf |= SPICA_INTF_MRX;
            }
            if (spica_package_has_psr(die))
            {
                intf |= SPICA_INTF_STX;
                intf |= SPICA_INTF_SRX;
            }
            break;
        case SPICA_MODE_LINE_PRBS:
        case SPICA_MODE_SHALLOW_LINE_LOOPBACK:
            intf |= SPICA_INTF_OTX;
            intf |= SPICA_INTF_ORX;
            break;
        case SPICA_MODE_HOST_PRBS:
        case SPICA_MODE_SHALLOW_HOST_LOOPBACK:
            if (spica_package_has_pmr(die))
            {
                intf |= SPICA_INTF_MTX;
                intf |= SPICA_INTF_MRX;
            }
            if (spica_package_has_psr(die))
            {
                intf |= SPICA_INTF_STX;
                intf |= SPICA_INTF_SRX;
            }
            break;
#if 0
        case SPICA_MODE_SHALLOW_LINE_LOOPBACK_TX_EN:
            intf |= SPICA_INTF_ORX;
            intf |= SPICA_INTF_OTX;
            if (spica_package_has_pmr(die))
            {
                intf |= SPICA_INTF_MTX;
            }
            if (spica_package_has_psr(die))
            {
                intf |= SPICA_INTF_STX;
            }
            break;
        case SPICA_MODE_SHALLOW_HOST_LOOPBACK_TX_EN:
            intf |= SPICA_INTF_OTX;
            if (spica_package_has_pmr(die))
            {
                intf |= SPICA_INTF_MTX;
                intf |= SPICA_INTF_MRX;
            }
            if (spica_package_has_psr(die))
            {
                intf |= SPICA_INTF_STX;
                intf |= SPICA_INTF_SRX;
            }
            break;
#endif

        default:
            INPHI_CRIT("ERROR: Invalid op mode=%d\n", op_mode);
            break;
    }
    return (e_spica_intf)intf;
}
/*
 * Update the tx rules structure 
 */
static inphi_status_t spica_cp_tx_overlays_to_rules(
    uint32_t          die,
    uint32_t          channel,
    e_spica_intf      intf,
    spica_tx_rules_t* tx_rules)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data;

    if(!tx_rules)
    {
        INPHI_CRIT("ERROR: tx_rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    if(intf == SPICA_INTF_OTX)
    {
        data = SPICA_OTX_RULES_0__READ(die, channel);
        tx_rules->channel_enable  = SPICA_OTX_RULES_0__CHANNEL_ENABLE__GET(data);
        tx_rules->lut_mode        = SPICA_OTX_RULES_0__LUT_MODE__GET(data);
        tx_rules->ieee_demap      = SPICA_OTX_RULES_0__IEEE_DEMAP__GET(data);
        tx_rules->gray_mapping    = SPICA_OTX_RULES_0__GRAY_MAPPING__GET(data);
        tx_rules->invert_chan     = SPICA_OTX_RULES_0__INVERT_CHAN__GET(data);
        tx_rules->signalling      = SPICA_OTX_RULES_0__SIGNALLING__GET(data);
        tx_rules->swing           = SPICA_OTX_RULES_0__SWING__GET(data);
        tx_rules->squelch_lock    = SPICA_OTX_RULES_0__SQUELCH_LOCK__GET(data);
        tx_rules->fll_mode        = SPICA_OTX_RULES_0__FLL_MODE__GET(data);

        tx_rules->baud_rate       = 0xF;

        tx_rules->dfe_precoder_en = SPICA_OTX_TXD_MISC_CFG__PRECODE_EN__READ(die, channel);

        tx_rules->fir_taps[0]     = SPICA_OTX_RULES_1__READ(die, channel);
        tx_rules->fir_taps[1]     = SPICA_OTX_RULES_2__READ(die, channel);
        tx_rules->fir_taps[2]     = SPICA_OTX_RULES_3__READ(die, channel);
        tx_rules->fir_taps[3]     = SPICA_OTX_RULES_4__READ(die, channel);
        tx_rules->fir_taps[4]     = SPICA_OTX_RULES_5__READ(die, channel);
        tx_rules->fir_taps[5]     = SPICA_OTX_RULES_6__READ(die, channel);
        tx_rules->fir_taps[6]     = SPICA_OTX_RULES_7__READ(die, channel);
                            
        tx_rules->inner_eye1      = SPICA_OTX_RULES_8__READ(die, channel);
        tx_rules->inner_eye2      = SPICA_OTX_RULES_9__READ(die, channel);
    }
    else if (intf == SPICA_INTF_MTX)
    {
#if !defined(INPHI_REMOVE_PMR)
        data = SPICA_MTX_RULES_0__READ(die, channel);
        tx_rules->channel_enable  = SPICA_MTX_RULES_0__CHANNEL_ENABLE__GET(data);
        tx_rules->lut_mode        = SPICA_MTX_RULES_0__LUT_MODE__GET(data);
        tx_rules->ieee_demap      = SPICA_MTX_RULES_0__IEEE_DEMAP__GET(data);
        tx_rules->gray_mapping    = SPICA_MTX_RULES_0__GRAY_MAPPING__GET(data);
        tx_rules->invert_chan     = SPICA_MTX_RULES_0__INVERT_CHAN__GET(data);
        tx_rules->signalling      = SPICA_MTX_RULES_0__SIGNALLING__GET(data);
        tx_rules->swing           = SPICA_MTX_RULES_0__SWING__GET(data);
        tx_rules->squelch_lock    = SPICA_MTX_RULES_0__SQUELCH_LOCK__GET(data);
        tx_rules->fll_mode        = SPICA_MTX_RULES_0__FLL_MODE__GET(data);

        tx_rules->baud_rate       = 0xF;

        tx_rules->dfe_precoder_en = SPICA_SMTX_PMR_TXD_MISC_CFG__PRECODE_EN__READ(die, channel);

        tx_rules->fir_taps[0]     = SPICA_MTX_RULES_1__READ(die, channel);
        tx_rules->fir_taps[1]     = SPICA_MTX_RULES_2__READ(die, channel);
        tx_rules->fir_taps[2]     = SPICA_MTX_RULES_3__READ(die, channel);
        tx_rules->fir_taps[3]     = SPICA_MTX_RULES_4__READ(die, channel);
        tx_rules->fir_taps[4]     = SPICA_MTX_RULES_5__READ(die, channel);
        tx_rules->fir_taps[5]     = SPICA_MTX_RULES_6__READ(die, channel);
        tx_rules->fir_taps[6]     = SPICA_MTX_RULES_7__READ(die, channel);
                            
        tx_rules->inner_eye1      = SPICA_MTX_RULES_8__READ(die, channel);
        tx_rules->inner_eye2      = SPICA_MTX_RULES_9__READ(die, channel);
#endif // defined(INPHI_REMOVE_PMR)
    }
    else if (intf == SPICA_INTF_STX)
    {
#if !defined(INPHI_REMOVE_PSR)
        data = SPICA_STX_RULES_0__READ(die, channel);
        tx_rules->channel_enable = SPICA_STX_RULES_0__CHANNEL_ENABLE__GET(data);
        tx_rules->lut_mode       = SPICA_STX_RULES_0__LUT_MODE__GET(data);
        tx_rules->ieee_demap     = SPICA_STX_RULES_0__IEEE_DEMAP__GET(data);
        tx_rules->gray_mapping   = SPICA_STX_RULES_0__GRAY_MAPPING__GET(data);
        tx_rules->invert_chan    = SPICA_STX_RULES_0__INVERT_CHAN__GET(data);
        tx_rules->signalling     = SPICA_STX_RULES_0__SIGNALLING__GET(data);
        tx_rules->swing          = SPICA_TX_SWING_NA;
        tx_rules->squelch_lock   = SPICA_STX_RULES_0__SQUELCH_LOCK__GET(data);
        tx_rules->fll_mode       = SPICA_STX_RULES_0__FLL_MODE__GET(data); 

        tx_rules->baud_rate       = 0xF;

        tx_rules->dfe_precoder_en  = SPICA_SMTX_PSR_TXD_MISC_CFG__PRECODE_EN__READ(die, channel);

        tx_rules->fir_taps[0] = SPICA_STX_RULES_1__READ(die, channel);
        tx_rules->fir_taps[1] = SPICA_STX_RULES_2__READ(die, channel);
        tx_rules->fir_taps[2] = SPICA_STX_RULES_3__READ(die, channel);
        tx_rules->fir_taps[3] = SPICA_STX_RULES_4__READ(die, channel);

        tx_rules->inner_eye1  = SPICA_STX_RULES_8__READ(die, channel);
        tx_rules->inner_eye2  = SPICA_STX_RULES_9__READ(die, channel);
#endif // defined(INPHI_REMOVE_PSR)
    }
    else
    {
        INPHI_CRIT("ERROR: Only OTX, MTX or STX interfaces supported");
        return INPHI_ERROR;
    }

    return status;
}

/*
 * Update the rules in the registers
 */
static inphi_status_t spica_cp_tx_rules_to_overlays(
    uint32_t          die,
    uint32_t          channel,
    e_spica_intf      intf,
    spica_tx_rules_t* tx_rules)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data;

    if(!tx_rules)
    {
        INPHI_CRIT("ERROR: tx_rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    if(intf == SPICA_INTF_OTX)
    {
        data = SPICA_OTX_RULES_0__READ(die, channel);
        data = SPICA_OTX_RULES_0__CHANNEL_ENABLE__SET(data, tx_rules->channel_enable);
        data = SPICA_OTX_RULES_0__LUT_MODE__SET(data, tx_rules->lut_mode);
        data = SPICA_OTX_RULES_0__IEEE_DEMAP__SET(data, tx_rules->ieee_demap);
        data = SPICA_OTX_RULES_0__GRAY_MAPPING__SET(data, tx_rules->gray_mapping);
        data = SPICA_OTX_RULES_0__INVERT_CHAN__SET(data, tx_rules->invert_chan);
        data = SPICA_OTX_RULES_0__SIGNALLING__SET(data, tx_rules->signalling);
        data = SPICA_OTX_RULES_0__SWING__SET(data, tx_rules->swing);
        data = SPICA_OTX_RULES_0__SQUELCH_LOCK__SET(data, tx_rules->squelch_lock);
        data = SPICA_OTX_RULES_0__FLL_MODE__SET(data, tx_rules->fll_mode);
        SPICA_OTX_RULES_0__WRITE(die, channel, data);

        SPICA_OTX_TXD_MISC_CFG__PRECODE_EN__RMW(die, channel, tx_rules->dfe_precoder_en);

        SPICA_OTX_RULES_1__WRITE(die, channel, tx_rules->fir_taps[0]);
        SPICA_OTX_RULES_2__WRITE(die, channel, tx_rules->fir_taps[1]);
        SPICA_OTX_RULES_3__WRITE(die, channel, tx_rules->fir_taps[2]);
        SPICA_OTX_RULES_4__WRITE(die, channel, tx_rules->fir_taps[3]);
        SPICA_OTX_RULES_5__WRITE(die, channel, tx_rules->fir_taps[4]);
        SPICA_OTX_RULES_6__WRITE(die, channel, tx_rules->fir_taps[5]);
        SPICA_OTX_RULES_7__WRITE(die, channel, tx_rules->fir_taps[6]);

        SPICA_OTX_RULES_8__WRITE(die, channel, tx_rules->inner_eye1);
        SPICA_OTX_RULES_9__WRITE(die, channel, tx_rules->inner_eye2);
    }
    else if (intf == SPICA_INTF_MTX)
    {
#if !defined(INPHI_REMOVE_PMR)
        data = SPICA_MTX_RULES_0__READ(die, channel);
        data = SPICA_MTX_RULES_0__CHANNEL_ENABLE__SET(data, tx_rules->channel_enable);
        data = SPICA_MTX_RULES_0__LUT_MODE__SET(data, tx_rules->lut_mode);
        data = SPICA_MTX_RULES_0__IEEE_DEMAP__SET(data, tx_rules->ieee_demap);
        data = SPICA_MTX_RULES_0__GRAY_MAPPING__SET(data, tx_rules->gray_mapping);
        data = SPICA_MTX_RULES_0__INVERT_CHAN__SET(data, tx_rules->invert_chan);
        data = SPICA_MTX_RULES_0__SIGNALLING__SET(data, tx_rules->signalling);
        data = SPICA_MTX_RULES_0__SWING__SET(data, tx_rules->swing);
        data = SPICA_MTX_RULES_0__SQUELCH_LOCK__SET(data, tx_rules->squelch_lock);
        data = SPICA_MTX_RULES_0__FLL_MODE__SET(data, tx_rules->fll_mode);
        SPICA_MTX_RULES_0__WRITE(die, channel, data);

        SPICA_SMTX_PMR_TXD_MISC_CFG__PRECODE_EN__RMW(die, channel, tx_rules->dfe_precoder_en);

        SPICA_MTX_RULES_1__WRITE(die, channel, tx_rules->fir_taps[0]);
        SPICA_MTX_RULES_2__WRITE(die, channel, tx_rules->fir_taps[1]);
        SPICA_MTX_RULES_3__WRITE(die, channel, tx_rules->fir_taps[2]);
        SPICA_MTX_RULES_4__WRITE(die, channel, tx_rules->fir_taps[3]);
        SPICA_MTX_RULES_5__WRITE(die, channel, tx_rules->fir_taps[4]);
        SPICA_MTX_RULES_6__WRITE(die, channel, tx_rules->fir_taps[5]);
        SPICA_MTX_RULES_7__WRITE(die, channel, tx_rules->fir_taps[6]);

        SPICA_MTX_RULES_8__WRITE(die, channel, tx_rules->inner_eye1);
        SPICA_MTX_RULES_9__WRITE(die, channel, tx_rules->inner_eye2);
#endif // defined(INPHI_REMOVE_PMR)
    }
    else if (intf == SPICA_INTF_STX)
    {
#if !defined(INPHI_REMOVE_PSR)
        data = SPICA_STX_RULES_0__READ(die, channel);
        data = SPICA_STX_RULES_0__CHANNEL_ENABLE__SET(data, tx_rules->channel_enable);
        data = SPICA_STX_RULES_0__LUT_MODE__SET(data, tx_rules->lut_mode);
        data = SPICA_STX_RULES_0__IEEE_DEMAP__SET(data, tx_rules->ieee_demap);
        data = SPICA_STX_RULES_0__GRAY_MAPPING__SET(data, tx_rules->gray_mapping);
        data = SPICA_STX_RULES_0__INVERT_CHAN__SET(data, tx_rules->invert_chan);
        data = SPICA_STX_RULES_0__SIGNALLING__SET(data, tx_rules->signalling);
        data = SPICA_STX_RULES_0__SQUELCH_LOCK__SET(data, tx_rules->squelch_lock);
        data = SPICA_STX_RULES_0__FLL_MODE__SET(data, tx_rules->fll_mode);
        SPICA_STX_RULES_0__WRITE(die, channel, data);

        SPICA_SMTX_PSR_TXD_MISC_CFG__PRECODE_EN__RMW(die, channel, tx_rules->dfe_precoder_en);

        SPICA_STX_RULES_1__WRITE(die, channel, tx_rules->fir_taps[0]);
        SPICA_STX_RULES_2__WRITE(die, channel, tx_rules->fir_taps[1]);
        SPICA_STX_RULES_3__WRITE(die, channel, tx_rules->fir_taps[2]);
        SPICA_STX_RULES_4__WRITE(die, channel, tx_rules->fir_taps[3]);

        SPICA_STX_RULES_8__WRITE(die, channel, tx_rules->inner_eye1);
        SPICA_STX_RULES_9__WRITE(die, channel, tx_rules->inner_eye2);
#endif // defined(INPHI_REMOVE_PSR)
    }
    else
    {
        INPHI_CRIT("ERROR: Only OTX, MTX or STX interfaces supported");
        return INPHI_ERROR;
    }

    return status;
}

// This method is used to populate the overlays with the baud rates
// and also to update the per channel baud rate selector fields
inphi_status_t spica_cp_baud_rate_to_overlays(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    uint32_t baud_rate,
    uint8_t *num_rates,
    uint32_t rates_lut[7])
{
    inphi_status_t status = INPHI_OK;
    bool is_unique;
    uint8_t baud_rate_sel;

    // INPHI_NOTE("in spica_cp_baud_rate_to_overlays, die:0x%08x, ch:%d, intf:%d, bd:%d=%s\n", 
    // die, channel, intf, baud_rate, spica_dbg_translate_baud_rate(baud_rate)); 

    if(baud_rate != 0)
    {
        // We found an instance where the user is trying to overide w/ a custom rate
        is_unique = true; // Assume rate is unused unless we discover otherwise
        for(int i=1; i<6; i++)
        {
            if(rates_lut[i] == baud_rate)
            {
                //INPHI_NOTE("Rate is NOT unique!\n");
                // This rate is already programmed to an overlay
                baud_rate_sel = i; // Figure out baud_rate_sel based on position in LUT
                is_unique = false;
                break;
            }
        }
        if(is_unique)
        {
            (*num_rates)++;
            baud_rate_sel = *num_rates;
            rates_lut[baud_rate_sel] = baud_rate; // Add baud_rate to LUT
            //INPHI_NOTE("Rate is unique. Adding to LUT.\n");
        }

        // Send the selector rule to the overlays
        switch(intf)
        {
            case SPICA_INTF_OTX:
                SPICA_OTX_RULES_0__BAUD_RATE_SEL__RMW(die, channel, baud_rate_sel);
                break;
            case SPICA_INTF_MTX:
                SPICA_MTX_RULES_0__BAUD_RATE_SEL__RMW(die, channel, baud_rate_sel);
                break;
            case SPICA_INTF_ORX:
                SPICA_ORX_RULES_0__BAUD_RATE_SEL__RMW(die, channel, baud_rate_sel);
                break;
            case SPICA_INTF_MRX:
                SPICA_MRX_RULES_0__BAUD_RATE_SEL__RMW(die, channel, baud_rate_sel);
                break;
            case SPICA_INTF_STX:
                SPICA_STX_RULES_0__BAUD_RATE_SEL__RMW(die, channel, baud_rate_sel);
                break;
            case SPICA_INTF_SRX:
                SPICA_SRX_RULES_0__BAUD_RATE_SEL__RMW(die, channel, baud_rate_sel);
                break;
            default:
                INPHI_CRIT("Invalid interface specified\n");
        }

        // Send the data rate to the overlay bank (Only if we haven't already done so)
        if(is_unique)
        {
            uint32_t rate;
            rate = rates_lut[baud_rate_sel];
            switch (baud_rate_sel)
            {
                case 1:
                    SPICA_TOP_RULES_8__WRITE(die, rate);          // BAUD_RATE_1_LSW
                    SPICA_TOP_RULES_9__WRITE(die, (rate >> 16));  // BAUD_RATE_1_MSW
                    break;
                case 2:
                    SPICA_TOP_RULES_10__WRITE(die, rate);         // BAUD_RATE_2_LSW
                    SPICA_TOP_RULES_11__WRITE(die, (rate >> 16)); // BAUD_RATE_2_MSW
                    break;
                case 3:
                    SPICA_TOP_RULES_12__WRITE(die, rate);         // BAUD_RATE_3_LSW
                    SPICA_TOP_RULES_13__WRITE(die, (rate >> 16)); // BAUD_RATE_3_MSW
                    break;
                case 4:
                    SPICA_TOP_RULES_14__WRITE(die, rate);         // BAUD_RATE_4_LSW
                    SPICA_TOP_RULES_15__WRITE(die, (rate >> 16)); // BAUD_RATE_4_MSW
                    break;
                case 5:
                    SPICA_TOP_RULES_16__WRITE(die, rate);         // BAUD_RATE_5_LSW
                    SPICA_TOP_RULES_17__WRITE(die, (rate >> 16)); // BAUD_RATE_5_MSW
                    break;
                case 6:
                    SPICA_TOP_RULES_18__WRITE(die, rate);         // BAUD_RATE_6_LSW
                    SPICA_TOP_RULES_19__WRITE(die, (rate >> 16)); // BAUD_RATE_6_MSW
                    break;
                default:
                    INPHI_CRIT("Chip does not support more than 6 custom rates configured simultaneously.\n");
                    status |= INPHI_ERROR;
                    break;
            }
        }
    }
    return status;
}

/**
 * LOS Assert/De-assert mv to DAC code LUT - ASSERT 
 */
static const uint16_t los_ctrl_amp_thresholds_asrt[2][7] = {
    { /** PAM LUT */
        /** 7bit value: [0:4] Threshold voltage control, [5:6] hysterisis control*/
        /** Input signal amplitude, 50 mv ppd  */
        0x46,
        /** Input signal amplitude, 100 mv ppd  */
        0x46,
        /** Input signal amplitude, 150 mv ppd  */
        0x46,
        /** Input signal amplitude, 200 mv ppd  */
        0x46,
        /** Input signal amplitude, 250 mv ppd  */
        0x4A,
        /** Input signal amplitude, 300 mv ppd  */
        0x50,
        /** Input signal amplitude, 350 mv ppd  */
        0x56,
    },
    { /** NRZ LUT */
        /** Input signal amplitude, 50 mv ppd  */
        0x46,
        /** Input signal amplitude, 100 mv ppd  */
        0x46,
        /** Input signal amplitude, 150 mv ppd  */
        0x4A,
        /** Input signal amplitude, 200 mv ppd  */
        0x52,
        /** Input signal amplitude, 250 mv ppd  */
        0x5C,
        /** Input signal amplitude, 300 mv ppd  */
        0x5C,
        /** Input signal amplitude, 350 mv ppd  */
        0x5C,
    }
};

/**
 * LOS Assert/De-assert mv to DAC code LUT - DE-ASSERT
 */
static const uint16_t los_ctrl_amp_thresholds_dsrt[2][7] = {
    { /** PAM LUT */
        /** 7bit value: [0:4] Threshold voltage control, [5:6] hysterisis control*/
        /** Input signal amplitude, 50 mv ppd  */
        0x46,
        /** Input signal amplitude, 100 mv ppd  */
        0x46,
        /** Input signal amplitude, 150 mv ppd  */
        0x46,
        /** Input signal amplitude, 200 mv ppd  */
        0x46,
        /** Input signal amplitude, 250 mv ppd  */
        0x4A,
        /** Input signal amplitude, 300 mv ppd  */
        0x4E,
        /** Input signal amplitude, 350 mv ppd  */
        0x54,
    },
    { /** NRZ LUT */
        /** Input signal amplitude, 50 mv ppd  */
        0x46,
        /** Input signal amplitude, 100 mv ppd  */
        0x46,
        /** Input signal amplitude, 150 mv ppd  */
        0x48,
        /** Input signal amplitude, 200 mv ppd  */
        0x50,
        /** Input signal amplitude, 250 mv ppd  */
        0x56,
        /** Input signal amplitude, 300 mv ppd  */
        0x5E,
        /** Input signal amplitude, 350 mv ppd  */
        0x5E,
    }
};

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/*
 * Update the top, rx and tx rules structure 
 */
inphi_status_t spica_cp_overlays_to_rules(
    uint32_t       die,
    uint32_t       bundle_idx,
    spica_rules_t* rules)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data = 0;

    if(!rules)
    {
        INPHI_CRIT("ERROR: rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    if (!spica_bundle_is_en(bundle_idx))
    {
        INPHI_CRIT("ERROR: Bundle not enabled %d\n", bundle_idx);
        return INPHI_ERROR;
    }

    // e_spica_package_type package = spica_package_query_efuse(die);

    // get the die associated with the bundle
    uint32_t bdie = spica_bundle_get_die_from_bundle(bundle_idx);

    data = SPICA_TOP_RULES_0__READ(bdie);
    e_spica_operational_mode op_mode    = SPICA_TOP_RULES_0__OP_MODE__GET(data);
    e_spica_protocol_mode protocol_mode = SPICA_TOP_RULES_0__PROTOCOL_MODE__GET(data);

    spica_rules_default_set_per_bundle(die, bundle_idx, op_mode, protocol_mode, rules);

    data = SPICA_TOP_RULES_7__READ(bdie);
    rules->driver_type_override = SPICA_TOP_RULES_7__DRIVER_TYPE__GET(data);

    data = SPICA_TOP_RULES_22__READ(bdie);
    rules->lrx_qc.snr_threshold_mm_enter = SPICA_TOP_RULES_22__LRX_QC_SNR_THRESHOLD_MM_ENTER__GET(data);
    rules->lrx_qc.snr_threshold_mm_exit  = SPICA_TOP_RULES_22__LRX_QC_SNR_THRESHOLD_MM_EXIT__GET(data);

    data = SPICA_TOP_RULES_23__READ(bdie);
    rules->hrx_qc.snr_threshold_mm_enter = SPICA_TOP_RULES_23__HRX_QC_SNR_THRESHOLD_MM_ENTER__GET(data);
    rules->hrx_qc.snr_threshold_mm_exit  = SPICA_TOP_RULES_23__HRX_QC_SNR_THRESHOLD_MM_EXIT__GET(data);

    data = SPICA_TOP_RULES_25__READ(bdie);
    rules->lrx_qc.slc_err_limit = SPICA_TOP_RULES_25__LRX_QC_SLC_ERR_LIMIT__GET(data);
    rules->hrx_qc.slc_err_limit = SPICA_TOP_RULES_25__HRX_QC_SLC_ERR_LIMIT__GET(data);

    data = SPICA_TOP_RULES_24__READ(bdie);
    rules->advanced.lrx_ddlf_en              = SPICA_TOP_RULES_24__POR_DDLF_EN__GET(data);
    rules->advanced.hrx_ddlf_en              = SPICA_TOP_RULES_24__PMR_DDLF_EN__GET(data);
    rules->advanced.lrx_low_loss_det_en      = SPICA_TOP_RULES_24__POR_LOW_LOSS_DET_EN__GET(data);
    rules->advanced.hrx_low_loss_det_en      = SPICA_TOP_RULES_24__PMR_LOW_LOSS_DET_EN__GET(data);
    rules->advanced.lrx_double_restart_dis   = SPICA_TOP_RULES_24__POR_DOUBLE_RESTART_DIS__GET(data);
    rules->advanced.lrx_cid_losd_det_en      = SPICA_TOP_RULES_24__POR_CID_LOSD_DET_EN__GET(data);
    rules->advanced.hrx_cid_losd_det_en      = SPICA_TOP_RULES_24__PMR_CID_LOSD_DET_EN__GET(data);

    /* read from some of the ORX overlay registers */
    SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_ORX)
    {
        data = SPICA_ORX_RULES_0__READ(bdie, channel);
        rules->orx[channel].channel_enable     = SPICA_ORX_RULES_0__CHANNEL_ENABLE__GET(data);
        rules->orx[channel].ieee_demap         = SPICA_ORX_RULES_0__IEEE_DEMAP__GET(data);
        rules->orx[channel].gray_mapping       = SPICA_ORX_RULES_0__GRAY_MAPPING__GET(data);
        rules->orx[channel].invert_chan        = SPICA_ORX_RULES_0__INVERT_CHAN__GET(data);
        rules->orx[channel].signalling         = SPICA_ORX_RULES_0__SIGNALLING__GET(data);
        rules->orx[channel].sdt_dsp_en         = SPICA_ORX_RULES_0__SDT_DSP_EN__GET(data);
        rules->orx[channel].los_dsp_en         = SPICA_ORX_RULES_0__LOS_DSP_EN__GET(data);
        rules->orx[channel].six_bit_mode       = SPICA_ORX_RULES_0__6BIT_MODE__GET(data);
        rules->orx[channel].force_mission_mode = SPICA_ORX_RULES_0__FORCE_MISSION_MODE__GET(data);
        rules->orx[channel].baud_rate          = 0xF;
        rules->orx[channel].restart_on_los_dis    = SPICA_ORX_RULES_0__RESTART_ON_LOS_DIS__GET(data);

        data = SPICA_ORX_RULES_1__READ(bdie, channel);
        rules->orx[channel].ffe_const_diff_en    = SPICA_ORX_RULES_1__FFE_CONST_DIFF_EN__GET(data);
        rules->orx[channel].bw_idx_max           = SPICA_ORX_RULES_1__BW_IDX_MAX__GET(data);
        rules->orx[channel].vga1_tracking_period = SPICA_ORX_RULES_1__VGA1_TRACKING_PERIOD__GET(data);
        rules->orx[channel].alg1_dis             = SPICA_ORX_RULES_1__ALG1_DIS__GET(data);
        rules->orx[channel].alg2_dis             = SPICA_ORX_RULES_1__ALG2_DIS__GET(data);
        rules->orx[channel].alg3_dis             = SPICA_ORX_RULES_1__ALG3_DIS__GET(data);
        rules->orx[channel].alg4_dis             = SPICA_ORX_RULES_1__ALG4_DIS__GET(data);

        data = SPICA_ORX_ALG_CTRL__READ(bdie, channel);
        rules->orx[channel].qc_all_dis           = SPICA_ORX_ALG_CTRL__QC_ALL_DIS__GET(data);
        rules->orx[channel].qc_hist_dis          = SPICA_ORX_ALG_CTRL__QC_HIST_DIS__GET(data);
        rules->orx[channel].qc_slc_dis           = SPICA_ORX_ALG_CTRL__QC_SLC_DIS__GET(data);
        rules->orx[channel].qc_snr_dis           = SPICA_ORX_ALG_CTRL__QC_SNR_DIS__GET(data);

    }

    if (SPICA_INTF_PMR & spica_package_get_intf(die))
    {
#if !defined(INPHI_REMOVE_PMR)
        /* read from some of the MRX overlay registers */
        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_MRX)
        {
            data = SPICA_MRX_RULES_0__READ(bdie, channel);
            rules->mrx[channel].channel_enable     = SPICA_MRX_RULES_0__CHANNEL_ENABLE__GET(data);
            rules->mrx[channel].ieee_demap         = SPICA_MRX_RULES_0__IEEE_DEMAP__GET(data);
            rules->mrx[channel].gray_mapping       = SPICA_MRX_RULES_0__GRAY_MAPPING__GET(data);
            rules->mrx[channel].invert_chan        = SPICA_MRX_RULES_0__INVERT_CHAN__GET(data);
            rules->mrx[channel].signalling         = SPICA_MRX_RULES_0__SIGNALLING__GET(data);
            rules->mrx[channel].sdt_dsp_en         = SPICA_MRX_RULES_0__SDT_DSP_EN__GET(data);
            rules->mrx[channel].los_dsp_en         = SPICA_MRX_RULES_0__LOS_DSP_EN__GET(data);
            rules->mrx[channel].force_mission_mode = SPICA_MRX_RULES_0__FORCE_MISSION_MODE__GET(data);
            rules->mrx[channel].baud_rate          = 0xF;
            rules->mrx[channel].restart_on_los_dis    = SPICA_MRX_RULES_0__RESTART_ON_LOS_DIS__GET(data);

            data = SPICA_MRX_RULES_1__READ(bdie, channel);
            rules->mrx[channel].ffe_const_diff_en    = SPICA_MRX_RULES_1__FFE_CONST_DIFF_EN__GET(data);
            rules->mrx[channel].bw_idx_max           = SPICA_MRX_RULES_1__BW_IDX_MAX__GET(data);
            rules->mrx[channel].vga1_tracking_period = SPICA_MRX_RULES_1__VGA1_TRACKING_PERIOD__GET(data);
            rules->mrx[channel].alg1_dis             = SPICA_MRX_RULES_1__ALG1_DIS__GET(data);
            rules->mrx[channel].alg2_dis             = SPICA_MRX_RULES_1__ALG2_DIS__GET(data);
            rules->mrx[channel].alg3_dis             = SPICA_MRX_RULES_1__ALG3_DIS__GET(data);
            rules->mrx[channel].alg4_dis             = SPICA_MRX_RULES_1__ALG4_DIS__GET(data);

            data = SPICA_MRX_ALG_CTRL__READ(bdie, channel);
            rules->mrx[channel].qc_all_dis           = SPICA_MRX_ALG_CTRL__QC_ALL_DIS__GET(data);
            rules->mrx[channel].qc_hist_dis          = SPICA_MRX_ALG_CTRL__QC_HIST_DIS__GET(data);
            rules->mrx[channel].qc_slc_dis           = SPICA_MRX_ALG_CTRL__QC_SLC_DIS__GET(data);
            rules->mrx[channel].qc_snr_dis           = SPICA_MRX_ALG_CTRL__QC_SNR_DIS__GET(data);
        }
#endif // defined(INPHI_REMOVE_PMR)
    }
    else if (SPICA_INTF_PSR & spica_package_get_intf(die))
    {
#if !defined(INPHI_REMOVE_PSR)
        /* read from some of the SRX overlay registers */
        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_SRX)
        {
            data = SPICA_SRX_RULES_0__READ(bdie, channel);
            rules->srx[channel].channel_enable       = SPICA_SRX_RULES_0__CHANNEL_ENABLE__GET(data);
            rules->srx[channel].ctle_adapt_dis       = SPICA_SRX_RULES_0__CTLE_ADAPT_DIS__GET(data);
            rules->srx[channel].lfeq_adapt_dis       = SPICA_SRX_RULES_0__LFEQ_ADAPT_DIS__GET(data);
            rules->srx[channel].skip_adapt           = SPICA_SRX_RULES_0__SKIP_ADAPT__GET(data);
            rules->srx[channel].dfe_adapt_dis        = SPICA_SRX_RULES_0__DFE_ADAPT_DIS__GET(data);
            rules->srx[channel].signalling           = SPICA_SRX_RULES_0__SIGNALLING__GET(data);
            rules->srx[channel].data_skew_adapt_dis  = SPICA_SRX_RULES_0__DSKEW_ADAPT_DIS__GET(data);
            rules->srx[channel].edge_skew_adapt_dis  = SPICA_SRX_RULES_0__ESKEW_ADAPT_DIS__GET(data);
            rules->srx[channel].vco_temp_cal_dis     = SPICA_SRX_RULES_0__VCO_TEMP_CAL_DIS__GET(data);

            data = SPICA_SRX_RULES_1__READ(bdie, channel);
            rules->srx[channel].slc_adapt_dis        = SPICA_SRX_RULES_1__SLC_ADAPT_DIS__GET(data);
            rules->srx[channel].edge_off_adapt_dis   = SPICA_SRX_RULES_1__EDGE_OFF_ADAPT_DIS__GET(data);
            rules->srx[channel].agc_adapt_dis        = SPICA_SRX_RULES_1__AGC_ADAPT_DIS__GET(data);
            rules->srx[channel].gray_mapping         = SPICA_SRX_RULES_1__GRAY_MAPPING__GET(data);
            rules->srx[channel].invert_chan          = SPICA_SRX_RULES_1__INVERT_CHAN__GET(data);
            rules->srx[channel].ieee_demap           = SPICA_SRX_RULES_1__IEEE_DEMAP__GET(data);
            rules->srx[channel].ctle_r_adapt_dis     = SPICA_SRX_RULES_1__CTLE_R_ADAPT_DIS__GET(data);
            rules->srx[channel].ctle_c_adapt_en      = SPICA_SRX_RULES_1__CTLE_C_ADAPT__GET(data);
            rules->srx[channel].dc_off_adapt_dis     = SPICA_SRX_RULES_1__DC_OFF_ADAPT_DIS__GET(data);
            rules->srx[channel].afe_bw_adapt_dis     = SPICA_SRX_RULES_1__AFE_BW_ADAPT_DIS__GET(data);
            rules->srx[channel].lfeq_adapt_dis_after_init_adapt = SPICA_SRX_RULES_1__LFEQ_ADAPT_DIS_AFTER_INIT_ADAPT__GET(data);
            rules->srx[channel].vco_mode             = SPICA_SRX_RULES_1__VCO_MODE__GET(data);

            rules->srx[channel].baud_rate            = 0xF;

            if(rules->srx[channel].ctle_adapt_dis)
            {
                rules->srx[channel].ctle_override = SPICA_SRX_RXA_AFE_CTLE_CFG__READ(die, channel);
            }
            if(rules->srx[channel].lfeq_adapt_dis)
            {
                rules->srx[channel].lfeq_override = SPICA_SRX_RXA_AFE_LFEQ_CFG__READ(die, channel);
            }
        }
#endif // defined(INPHI_REMOVE_PSR)
    }
    SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_OTX)
    {
        // update the remainder of OTX rules
        status |= spica_cp_tx_overlays_to_rules(bdie, channel, SPICA_INTF_OTX, &rules->otx[channel]);
    }

    if (SPICA_INTF_PMR & spica_package_get_intf(die))
    {
#if !defined(INPHI_REMOVE_PMR)
        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_MTX)
        {
            // update the remainder of MTX rules
            status |= spica_cp_tx_overlays_to_rules(bdie, channel, SPICA_INTF_MTX, &rules->mtx[channel]);
        }
#endif // defined(INPHI_REMOVE_PMR)
    }
    else if (SPICA_INTF_PSR & spica_package_get_intf(die))
    {
#if !defined(INPHI_REMOVE_PSR)
        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_STX)
        {
            // update the remainder of STX rules
            status |= spica_cp_tx_overlays_to_rules(bdie, channel, SPICA_INTF_STX, &rules->stx[channel]);
        }
#endif // defined(INPHI_REMOVE_PSR)
    }

    // Done at end since we need to know the LRX signalling type
    data = SPICA_TOP_RULES_20__READ(bdie);
    uint16_t lrx_los_dsrt_startup_dac = SPICA_TOP_RULES_20__LRX_LOS_DSRT_STARTUP__GET(data);
    uint16_t lrx_los_asrt_startup_dac = SPICA_TOP_RULES_20__LRX_LOS_ASRT_STARTUP__GET(data);
    data = SPICA_TOP_RULES_21__READ(bdie);
    uint16_t lrx_los_asrt_datamode_dac= SPICA_TOP_RULES_21__LRX_LOS_ASRT_DATAMODE__GET(data);

    for(int i=0; i<SPICA_LOS_CTRL_AMP_MAX; i++) 
    {
        if(lrx_los_dsrt_startup_dac ==  los_ctrl_amp_thresholds_dsrt[rules->orx[1].signalling][i]) rules->lrx_los_dsrt_ctrl_startup  = i; 
        if(lrx_los_asrt_startup_dac ==  los_ctrl_amp_thresholds_asrt[rules->orx[1].signalling][i]) rules->lrx_los_asrt_ctrl_startup  = i; 
        if(lrx_los_asrt_datamode_dac == los_ctrl_amp_thresholds_asrt[rules->orx[1].signalling][i]) rules->lrx_los_asrt_ctrl_datamode = i; 
    }

    return status;
}
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

inphi_status_t spica_cp_rules_to_overlays(
    uint32_t       die,
    uint32_t       bundle_idx,
    spica_rules_t* rules)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data = 0;

    if(!rules)
    {
        INPHI_CRIT("ERROR: rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    if (!spica_bundle_is_en(bundle_idx))
    {
        INPHI_CRIT("ERROR: Bundle not enabled %d\n", bundle_idx);
        return INPHI_ERROR;
    }

    // Variables used for sending baud_rates to the FW
    uint8_t num_rates = 0; // We start off with zero custom rates. Need to iterate through rules to find them.
    uint32_t rates_lut[7] = {0}; // Used to track rates we have already sent to the overlays

    // e_spica_package_type package = spica_package_query_efuse(die);

    // get the die associated with the bundle
    uint32_t bdie = spica_bundle_get_die_from_bundle(bundle_idx);

    data = SPICA_TOP_RULES_0__READ(bdie);
    data = SPICA_TOP_RULES_0__OP_MODE__SET(data, rules->operational_mode);
    data = SPICA_TOP_RULES_0__PROTOCOL_MODE__SET(data, rules->protocol_mode);
    SPICA_TOP_RULES_0__WRITE(bdie, data);

    data = SPICA_TOP_RULES_7__READ(bdie);
    data = SPICA_TOP_RULES_7__DRIVER_TYPE__SET(data, rules->driver_type_override);
    SPICA_TOP_RULES_7__WRITE(bdie, data);

    if(rules->orx[1].sdt_dsp_en)
    {
        SPICA_TOP_RULES_20__LRX_LOS_DSRT_STARTUP__RMW(bdie, rules->lrx_los_dsrt_ctrl_startup);
    }
    else
    {
        // Must do a look up, based on signalling, to determine code corresponding to mV level
        SPICA_TOP_RULES_20__LRX_LOS_DSRT_STARTUP__RMW(bdie, los_ctrl_amp_thresholds_dsrt[rules->orx[1].signalling][rules->lrx_los_dsrt_ctrl_startup]); 
    }
 
    if(rules->orx[1].los_dsp_en)
    {
        SPICA_TOP_RULES_20__LRX_LOS_ASRT_STARTUP__RMW(bdie, rules->lrx_los_asrt_ctrl_startup);
        SPICA_TOP_RULES_21__LRX_LOS_ASRT_DATAMODE__RMW(bdie, rules->lrx_los_asrt_ctrl_datamode);
    }
    else
    {
        // Must do a look up, based on signalling, to determine code corresponding to mV level
        SPICA_TOP_RULES_20__LRX_LOS_ASRT_STARTUP__RMW(bdie, los_ctrl_amp_thresholds_asrt[rules->orx[1].signalling][rules->lrx_los_asrt_ctrl_startup]);
        SPICA_TOP_RULES_21__LRX_LOS_ASRT_DATAMODE__RMW(bdie, los_ctrl_amp_thresholds_asrt[rules->orx[1].signalling][rules->lrx_los_asrt_ctrl_datamode]);
    }

    SPICA_TOP_RULES_22__LRX_QC_SNR_THRESHOLD_MM_ENTER__RMW(bdie, rules->lrx_qc.snr_threshold_mm_enter);
    SPICA_TOP_RULES_22__LRX_QC_SNR_THRESHOLD_MM_EXIT__RMW(bdie,  rules->lrx_qc.snr_threshold_mm_exit);

    SPICA_TOP_RULES_23__HRX_QC_SNR_THRESHOLD_MM_ENTER__RMW(bdie, rules->hrx_qc.snr_threshold_mm_enter);
    SPICA_TOP_RULES_23__HRX_QC_SNR_THRESHOLD_MM_EXIT__RMW(bdie,  rules->hrx_qc.snr_threshold_mm_exit);

    data = SPICA_TOP_RULES_25__READ(bdie);
    data = SPICA_TOP_RULES_25__LRX_QC_SLC_ERR_LIMIT__SET(data, rules->lrx_qc.slc_err_limit);
    data = SPICA_TOP_RULES_25__HRX_QC_SLC_ERR_LIMIT__SET(data, rules->hrx_qc.slc_err_limit);
    SPICA_TOP_RULES_25__WRITE(bdie, data);

    data = SPICA_TOP_RULES_24__READ(bdie);
    data = SPICA_TOP_RULES_24__POR_DDLF_EN__SET(data,              rules->advanced.lrx_ddlf_en);
    data = SPICA_TOP_RULES_24__PMR_DDLF_EN__SET(data,              rules->advanced.hrx_ddlf_en);
    data = SPICA_TOP_RULES_24__PMR_LOW_LOSS_DET_EN__SET(data,      rules->advanced.hrx_low_loss_det_en);
    data = SPICA_TOP_RULES_24__POR_LOW_LOSS_DET_EN__SET(data,      rules->advanced.lrx_low_loss_det_en);
    data = SPICA_TOP_RULES_24__POR_DOUBLE_RESTART_DIS__SET(data,   rules->advanced.lrx_double_restart_dis);
    data = SPICA_TOP_RULES_24__POR_CID_LOSD_DET_EN__SET(data,          rules->advanced.lrx_cid_losd_det_en);
    data = SPICA_TOP_RULES_24__PMR_CID_LOSD_DET_EN__SET(data,          rules->advanced.hrx_cid_losd_det_en);
    SPICA_TOP_RULES_24__WRITE(bdie, data);

    /* update some of the ORX registers based on the rules */
    SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_ORX)
    {
        data = SPICA_ORX_RULES_0__CHANNEL_ENABLE__SET(0,        rules->orx[channel].channel_enable);
        data = SPICA_ORX_RULES_0__IEEE_DEMAP__SET(data,         rules->orx[channel].ieee_demap);
        data = SPICA_ORX_RULES_0__GRAY_MAPPING__SET(data,       rules->orx[channel].gray_mapping);
        data = SPICA_ORX_RULES_0__INVERT_CHAN__SET(data,        rules->orx[channel].invert_chan);
        data = SPICA_ORX_RULES_0__SIGNALLING__SET(data,         rules->orx[channel].signalling);
        data = SPICA_ORX_RULES_0__SDT_DSP_EN__SET(data,         rules->orx[channel].sdt_dsp_en);
        data = SPICA_ORX_RULES_0__LOS_DSP_EN__SET(data,         rules->orx[channel].los_dsp_en);
        data = SPICA_ORX_RULES_0__6BIT_MODE__SET(data,          rules->orx[channel].six_bit_mode);
        data = SPICA_ORX_RULES_0__FORCE_MISSION_MODE__SET(data, rules->orx[channel].force_mission_mode);
        data = SPICA_ORX_RULES_0__RESTART_ON_LOS_DIS__SET(data, rules->orx[channel].restart_on_los_dis);
        SPICA_ORX_RULES_0__WRITE(bdie, channel, data);

        data = SPICA_ORX_RULES_1__FFE_CONST_DIFF_EN__SET(0,     rules->orx[channel].ffe_const_diff_en);
        data = SPICA_ORX_RULES_1__BW_IDX_MAX__SET(data,         rules->orx[channel].bw_idx_max);
        data = SPICA_ORX_RULES_1__VGA1_TRACKING_PERIOD__SET(data, rules->orx[channel].vga1_tracking_period);
        data = SPICA_ORX_RULES_1__ALG1_DIS__SET(data,           rules->orx[channel].alg1_dis);
        data = SPICA_ORX_RULES_1__ALG2_DIS__SET(data,           rules->orx[channel].alg2_dis);
        data = SPICA_ORX_RULES_1__ALG3_DIS__SET(data,           rules->orx[channel].alg3_dis);
        data = SPICA_ORX_RULES_1__ALG4_DIS__SET(data,           rules->orx[channel].alg4_dis);
        SPICA_ORX_RULES_1__WRITE(bdie, channel, data);

        data = SPICA_ORX_ALG_CTRL__QC_ALL_DIS__SET(0,             rules->orx[channel].qc_all_dis);
        data = SPICA_ORX_ALG_CTRL__QC_HIST_DIS__SET(data,         rules->orx[channel].qc_hist_dis);
        data = SPICA_ORX_ALG_CTRL__QC_SLC_DIS__SET(data,          rules->orx[channel].qc_slc_dis);
        data = SPICA_ORX_ALG_CTRL__QC_SNR_DIS__SET(data,          rules->orx[channel].qc_snr_dis);
        SPICA_ORX_ALG_CTRL__WRITE(bdie, channel, data);

        // Set baud rate and baud_rate_sel value in the overlays
        status |= spica_cp_baud_rate_to_overlays(bdie, channel, SPICA_INTF_ORX, rules->orx[channel].baud_rate, &num_rates, rates_lut);

        //do a read on this in case the PRBS API was used to enable the checker prior to enter op state
        data = SPICA_ORX_ODP_DSP_DSP_MODE_CONTROL_CFG__READ(bdie, channel);
        data = SPICA_ORX_ODP_DSP_DSP_MODE_CONTROL_CFG__PAMX_MODE__SET(data, rules->orx[channel].signalling);
        SPICA_ORX_ODP_DSP_DSP_MODE_CONTROL_CFG__WRITE(bdie, channel, data);
    }

    if (SPICA_INTF_PMR & spica_package_get_intf(die))
    {
#if !defined(INPHI_REMOVE_PMR)
        /* update some of the MRX registers based on the rules */
        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_MRX)
        {
            data = SPICA_MRX_RULES_0__CHANNEL_ENABLE__SET(0,  rules->mrx[channel].channel_enable);
            data = SPICA_MRX_RULES_0__IEEE_DEMAP__SET(data,   rules->mrx[channel].ieee_demap);
            data = SPICA_MRX_RULES_0__GRAY_MAPPING__SET(data, rules->mrx[channel].gray_mapping);
            data = SPICA_MRX_RULES_0__INVERT_CHAN__SET(data,  rules->mrx[channel].invert_chan);
            data = SPICA_MRX_RULES_0__SIGNALLING__SET(data,   rules->mrx[channel].signalling);
            data = SPICA_MRX_RULES_0__SDT_DSP_EN__SET(data,   rules->mrx[channel].sdt_dsp_en);
            data = SPICA_MRX_RULES_0__LOS_DSP_EN__SET(data,   rules->mrx[channel].los_dsp_en);
            data = SPICA_MRX_RULES_0__FORCE_MISSION_MODE__SET(data, rules->mrx[channel].force_mission_mode);
            data = SPICA_MRX_RULES_0__RESTART_ON_LOS_DIS__SET(data, rules->mrx[channel].restart_on_los_dis);
            SPICA_MRX_RULES_0__WRITE(bdie, channel, data);

            data = SPICA_MRX_RULES_1__FFE_CONST_DIFF_EN__SET(0,     rules->mrx[channel].ffe_const_diff_en);
            data = SPICA_MRX_RULES_1__BW_IDX_MAX__SET(data,         rules->mrx[channel].bw_idx_max);
            data = SPICA_MRX_RULES_1__VGA1_TRACKING_PERIOD__SET(data, rules->mrx[channel].vga1_tracking_period);
            data = SPICA_MRX_RULES_1__ALG1_DIS__SET(data,           rules->mrx[channel].alg1_dis);
            data = SPICA_MRX_RULES_1__ALG2_DIS__SET(data,           rules->mrx[channel].alg2_dis);
            data = SPICA_MRX_RULES_1__ALG3_DIS__SET(data,           rules->mrx[channel].alg3_dis);
            data = SPICA_MRX_RULES_1__ALG4_DIS__SET(data,           rules->mrx[channel].alg4_dis);
            SPICA_MRX_RULES_1__WRITE(bdie, channel, data);

            data = SPICA_MRX_ALG_CTRL__QC_ALL_DIS__SET(0,             rules->mrx[channel].qc_all_dis);
            data = SPICA_MRX_ALG_CTRL__QC_HIST_DIS__SET(data,         rules->mrx[channel].qc_hist_dis);
            data = SPICA_MRX_ALG_CTRL__QC_SLC_DIS__SET(data,          rules->mrx[channel].qc_slc_dis);
            data = SPICA_MRX_ALG_CTRL__QC_SNR_DIS__SET(data,          rules->mrx[channel].qc_snr_dis);
            SPICA_MRX_ALG_CTRL__WRITE(bdie, channel, data);

            // Set baud rate and baud_rate_sel value in the overlays
            status |= spica_cp_baud_rate_to_overlays(bdie, channel, SPICA_INTF_MRX, rules->mrx[channel].baud_rate, &num_rates, rates_lut);
    
            //do a read on this in case the PRBS API was used to enable the checker prior to enter op state
            data = SPICA_MRX_ODP_DSP_DSP_MODE_CONTROL_CFG__READ(bdie, channel);
            data = SPICA_MRX_ODP_DSP_DSP_MODE_CONTROL_CFG__PAMX_MODE__SET(data, rules->mrx[channel].signalling);
            SPICA_MRX_ODP_DSP_DSP_MODE_CONTROL_CFG__WRITE(bdie, channel, data);
        }
#endif // defined(INPHI_REMOVE_PMR)
    }
    else if (SPICA_INTF_PSR & spica_package_get_intf(die))
    {
#if !defined(INPHI_REMOVE_PSR)
        /* update some of the SRX registers based on the rules */
        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_SRX)
        {
            data = SPICA_SRX_RULES_0__CHANNEL_ENABLE__SET(0,        rules->srx[channel].channel_enable);
            data = SPICA_SRX_RULES_0__CTLE_ADAPT_DIS__SET(data,     rules->srx[channel].ctle_adapt_dis);
            data = SPICA_SRX_RULES_0__LFEQ_ADAPT_DIS__SET(data,     rules->srx[channel].lfeq_adapt_dis);
            data = SPICA_SRX_RULES_0__SKIP_ADAPT__SET(data,         rules->srx[channel].skip_adapt);
            data = SPICA_SRX_RULES_0__DFE_ADAPT_DIS__SET(data,      rules->srx[channel].dfe_adapt_dis);
            data = SPICA_SRX_RULES_0__SIGNALLING__SET(data,         rules->srx[channel].signalling);
            data = SPICA_SRX_RULES_0__DSKEW_ADAPT_DIS__SET(data,    rules->srx[channel].data_skew_adapt_dis);
            data = SPICA_SRX_RULES_0__ESKEW_ADAPT_DIS__SET(data,    rules->srx[channel].edge_skew_adapt_dis);
            data = SPICA_SRX_RULES_0__VCO_TEMP_CAL_DIS__SET(data,   rules->srx[channel].vco_temp_cal_dis);      
            SPICA_SRX_RULES_0__WRITE(die, channel, data);

            // Set baud rate and baud_rate_sel value in the overlays
            status |= spica_cp_baud_rate_to_overlays(bdie, channel, SPICA_INTF_SRX, rules->srx[channel].baud_rate, &num_rates, rates_lut);

            data = SPICA_SRX_RULES_1__SLC_ADAPT_DIS__SET(0,         rules->srx[channel].slc_adapt_dis);
            data = SPICA_SRX_RULES_1__EDGE_OFF_ADAPT_DIS__SET(data, rules->srx[channel].edge_off_adapt_dis);
            data = SPICA_SRX_RULES_1__AGC_ADAPT_DIS__SET(data,      rules->srx[channel].agc_adapt_dis);
            data = SPICA_SRX_RULES_1__GRAY_MAPPING__SET(data,       rules->srx[channel].gray_mapping);
            data = SPICA_SRX_RULES_1__INVERT_CHAN__SET(data,        rules->srx[channel].invert_chan);
            data = SPICA_SRX_RULES_1__IEEE_DEMAP__SET(data,         rules->srx[channel].ieee_demap);
            data = SPICA_SRX_RULES_1__CTLE_R_ADAPT_DIS__SET(data,   rules->srx[channel].ctle_r_adapt_dis);
            data = SPICA_SRX_RULES_1__CTLE_C_ADAPT__SET(data,       rules->srx[channel].ctle_c_adapt_en);
            data = SPICA_SRX_RULES_1__DC_OFF_ADAPT_DIS__SET(data,   rules->srx[channel].dc_off_adapt_dis);

            data = SPICA_SRX_RULES_1__AFE_BW_ADAPT_DIS__SET(data,   rules->srx[channel].afe_bw_adapt_dis);
            data = SPICA_SRX_RULES_1__LFEQ_ADAPT_DIS_AFTER_INIT_ADAPT__SET(data, rules->srx[channel].lfeq_adapt_dis_after_init_adapt);
            data = SPICA_SRX_RULES_1__VCO_MODE__SET(data,           rules->srx[channel].vco_mode);
            SPICA_SRX_RULES_1__WRITE(die, channel, data);

            // ??? = rules->srx[channel].rates
            
            if(rules->srx[channel].ctle_adapt_dis)
            {
                SPICA_SRX_RXA_AFE_CTLE_CFG__WRITE(die, channel, rules->srx[channel].ctle_override);
            }
            if(rules->srx[channel].lfeq_adapt_dis)
            {
                SPICA_SRX_RXA_AFE_LFEQ_CFG__WRITE(die, channel, rules->srx[channel].lfeq_override);
            }
        }
#endif // defined(INPHI_REMOVE_PSR)
    }
    SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_OTX)
    {
        // Set baud rate and baud_rate_sel value in the overlays
        status |= spica_cp_baud_rate_to_overlays(bdie, channel, SPICA_INTF_OTX, rules->otx[channel].baud_rate, &num_rates, rates_lut);

        // Send remainder of tx rules
        status |= spica_cp_tx_rules_to_overlays(bdie, channel, SPICA_INTF_OTX, &rules->otx[channel]);
    }

    if (SPICA_INTF_PMR & spica_package_get_intf(die))
    {
#if !defined(INPHI_REMOVE_PMR)
        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_MTX)
        {
            // Set baud rate and baud_rate_sel value in the overlays
            status |= spica_cp_baud_rate_to_overlays(bdie, channel, SPICA_INTF_MTX, rules->mtx[channel].baud_rate, &num_rates, rates_lut);

            // Send remainder of tx rules
            status |= spica_cp_tx_rules_to_overlays(bdie, channel, SPICA_INTF_MTX, &rules->mtx[channel]);
        }
#endif // defined(INPHI_REMOVE_PMR)
    }
    else if (SPICA_INTF_PSR & spica_package_get_intf(die))
    {
#if !defined(INPHI_REMOVE_PSR)
        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_STX)
        {
            // Set baud rate and baud_rate_sel value in the overlays
            status |= spica_cp_baud_rate_to_overlays(bdie, channel, SPICA_INTF_STX, rules->stx[channel].baud_rate, &num_rates, rates_lut);

            // Send remainder of tx rules
            status |= spica_cp_tx_rules_to_overlays(bdie, channel, SPICA_INTF_STX, &rules->stx[channel]);
        }
#endif // defined(INPHI_REMOVE_PSR)
    }

    e_spica_intf src_intf;
    uint32_t src_ch;
    uint32_t src_clk_ch;
    uint32_t src_inst;
    uint32_t src_clk_inst;

    //get the enabled interfaces based on the op mode
    e_spica_intf en_intfs = spica_op_mode_en_intfs(die, rules->operational_mode);

    if (SPICA_INTF_POR & spica_package_get_intf(die))
    {
        // OTX xbar
        uint8_t size_of_src_ch_array = sizeof(rules->otx_xbar_src_chan[0])/sizeof(rules->otx_xbar_src_chan[0][0]);
        uint8_t tmp_xbar[sizeof(rules->otx_xbar_src_chan[0])/sizeof(rules->otx_xbar_src_chan[0][0])];

        // NOTE: Rebases package channel to FW channel (What the register requires)
        switch(rules->operational_mode)
        {
            case SPICA_MODE_MISSION_MODE:
            case SPICA_MODE_EGRESS_PRBS:
                if(en_intfs & SPICA_INTF_MRX) src_intf = SPICA_INTF_MRX;
                else src_intf = SPICA_INTF_SRX;
                break;
            case SPICA_MODE_SHALLOW_LINE_LOOPBACK:
                src_intf = SPICA_INTF_ORX;
                break;
            default:
                src_intf = SPICA_INTF_MRX;
        }

        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_OTX)
        {
            INPHI_MEMSET(tmp_xbar, 0xf, size_of_src_ch_array);
            for(int i=0; i<size_of_src_ch_array; i++)
            {
                src_ch = rules->otx_xbar_src_chan[channel][i];
               
                if ((src_ch > 0) && (src_ch < 0xf))
                {
                    src_inst = spica_get_die_inst_from_pkg_ch(die, src_ch, src_intf);
                    if (src_intf == SPICA_INTF_SRX) 
                    {
                        src_inst -= (src_inst)/3; // To remap {0,1,3,4,6,7,9,10} -> {0,1,2,3,4,5,6,7}
                    }
                    tmp_xbar[i] = src_inst;
                }
            }

            src_clk_ch = rules->otx_clk_xbar[channel];
            if((src_clk_ch == 0) || (src_clk_ch >= 0xf)) // out of range
            {
               src_clk_inst = 0xf;
            }
            else 
            {
                src_clk_inst = spica_get_die_inst_from_pkg_ch(die, src_clk_ch, src_intf);
                if (src_intf == SPICA_INTF_SRX) 
                {
                    src_clk_inst -= (src_clk_inst)/3; // To remap {0,1,3,4,6,7,9,10} -> {0,1,2,3,4,5,6,7}
                }
            }
            SPICA_OTX_CLK_XBAR__SRC_CHANNEL__RMW(die, channel, src_clk_inst);

            //INPHI_NOTE("OTX ch%d tmp_xbar [%d, %d, %d, %d]\n", channel, tmp_xbar[0], tmp_xbar[1], tmp_xbar[2], tmp_xbar[3]);
            data = SPICA_OTX_XBAR__READ(die, channel); 
            data |= SPICA_OTX_XBAR__SRC_CHANNEL_0__SET(data, tmp_xbar[0]);
            data |= SPICA_OTX_XBAR__SRC_CHANNEL_1__SET(data, tmp_xbar[1]);
            data |= SPICA_OTX_XBAR__SRC_CHANNEL_2__SET(data, tmp_xbar[2]);
            data |= SPICA_OTX_XBAR__SRC_CHANNEL_3__SET(data, tmp_xbar[3]);
            SPICA_OTX_XBAR__WRITE(die, channel, data);       
        }
    }

#if !defined(INPHI_REMOVE_PMR)
    if (SPICA_INTF_PMR & spica_package_get_intf(die))
    {
        // MTX xbar
        switch(rules->operational_mode)
        {
            case SPICA_MODE_MISSION_MODE:
            case SPICA_MODE_INGRESS_PRBS:
                src_intf = SPICA_INTF_ORX;
                break;
            case SPICA_MODE_SHALLOW_HOST_LOOPBACK:
                src_intf = SPICA_INTF_MRX;
                break;
            default:
                src_intf = SPICA_INTF_MRX;
        }

        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_MTX)
        {
            // The Rx channel to select as a source
            src_ch = rules->mtx_xbar_src_chan[channel][0];
            if((src_ch == 0) || (src_ch >= 0xf))
            {
                src_inst = 0xf;
            }
            else
            {
                // NOTE: Rebases package channel to FW channel (What the register requires)
                src_inst = spica_get_die_inst_from_pkg_ch(die, src_ch, src_intf);
            }

            src_clk_ch = rules->mtx_clk_xbar[channel];
            if((src_clk_ch == 0) || (src_clk_ch >= 0xf)) // out of range
            {
               src_clk_inst = 0xf;
            }
            else 
            {
                src_clk_inst = spica_get_die_inst_from_pkg_ch(die, src_clk_ch, src_intf);
            }
            SPICA_MTX_CLK_XBAR__SRC_CHANNEL__RMW(die, channel, src_clk_inst);

            //INPHI_NOTE("MTX ch%d src_inst=%d, src_ch_interleave=%d\n", channel, src_inst, rules->mtx_xbar_src_chan[channel][1]);
            SPICA_MTX_XBAR__SRC_CHANNEL__RMW(die, channel, src_inst);

            // The sub-channel interleave to select within the selected Rx channel
            // The offset value is already zero based, no need to rebase
            SPICA_MTX_XBAR__SRC_CHANNEL_INTERLEAVE__RMW(die, channel, rules->mtx_xbar_src_chan[channel][1]);
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    if (SPICA_INTF_PSR & spica_package_get_intf(die))
    {
        // STX xbar
        switch(rules->operational_mode)
        {
            case SPICA_MODE_MISSION_MODE:
            case SPICA_MODE_INGRESS_PRBS:
                src_intf = SPICA_INTF_ORX;
                break;
            case SPICA_MODE_SHALLOW_HOST_LOOPBACK:
                src_intf = SPICA_INTF_SRX;
                break;
            default:
                src_intf = SPICA_INTF_SRX;
        }

        SPICA_FOR_CHANNEL_IN_BUNDLE(die, bundle_idx, SPICA_INTF_STX)
        {
            // The Rx channel to select as a source
            src_ch = rules->stx_xbar_src_chan[channel][0];
            if((src_ch == 0) || (src_ch >= 0xf))
            {
                src_inst = 0xf;
            }
            else
            {
                // NOTE: Rebases package channel to FW channel (What the register requires)
                src_inst = spica_get_die_inst_from_pkg_ch(die, src_ch, src_intf);
                if (src_intf == SPICA_INTF_SRX) 
                {
                    src_inst -= (src_inst)/3; // To remap {0,1,3,4,6,7,9,10} -> {0,1,2,3,4,5,6,7}
                }
            }

            src_clk_ch = rules->stx_clk_xbar[channel];
            if((src_clk_ch == 0) || (src_clk_ch >= 0xf)) // out of range
            {
               src_clk_inst = 0xf;
            }
            else
            {
                src_clk_inst = spica_get_die_inst_from_pkg_ch(die, src_clk_ch, src_intf);
                if (src_intf == SPICA_INTF_SRX) 
                {
                    src_clk_inst -= (src_clk_inst)/3; // To remap {0,1,3,4,6,7,9,10} -> {0,1,2,3,4,5,6,7}
                }
            }
            SPICA_STX_CLK_XBAR__SRC_CHANNEL__RMW(die, channel, src_clk_inst);

            //INPHI_NOTE("STX ch%d src_ch=%d, src_ch_interleave=%d\n", channel, src_ch, rules->stx_xbar_src_chan[channel][1]);
            SPICA_STX_XBAR__SRC_CHANNEL__RMW(die, channel, src_inst);

            // The sub-channel interleave to select within the selected Rx channel
            // The offset value is already zero based, no need to rebase
            SPICA_STX_XBAR__SRC_CHANNEL_INTERLEAVE__RMW(die, channel, rules->stx_xbar_src_chan[channel][1]);
        }
    }
#endif // defined(INPHI_REMOVE_PSR)

    return status;
}

/**
 * This method is used to check the rules for possible errors in configuration.
 *
 * @param die     [I] - The ASIC die being accessed.
 * @param rules   [I] - The rules for the application.
 *
 * @private
 *
 * @since 0.9.0.0
 */
inphi_status_t spica_check_rules(
    uint32_t       die,
    spica_rules_t* rules)
{
    inphi_status_t status = INPHI_OK;
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    e_spica_package_type package = spica_package_get_type(die);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

#if !defined(INPHI_REMOVE_PMR)
    if (spica_package_has_pmr(die))
    {
        if (rules->protocol_mode == SPICA_MODE_400G_8Px26p6_TO_4Px53p1)
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_CRIT("Protocol Mode %s not valid for %s package\n", 
                spica_dbg_translate_protocol_mode(rules->protocol_mode), 
                spica_dbg_translate_package_type(package));
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            return INPHI_ERROR;
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    if (spica_package_has_psr(die))
    {
        if ((rules->protocol_mode == SPICA_MODE_400G_4Px53p1_TO_4Px53p1) ||
            (rules->protocol_mode == SPICA_MODE_300G_4Px41p3_TO_4Px41p3))
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_CRIT("Protocol Mode %s not valid for %s package\n", 
                spica_dbg_translate_protocol_mode(rules->protocol_mode), 
                spica_dbg_translate_package_type(package));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            return INPHI_ERROR;
        }
    }
#endif // defined(INPHI_REMOVE_PSR)
    
    // Find out if there are any channels on any interfaces that have their
    // signalling set to NRZ, if yes, then force that channels gray_mapping
    // rule to false.

    SPICA_FOR_CHANNEL_IN_CHANNELS(rules->package_type, SPICA_INTF_ORX)
    {
        //don't test if disabled
        if(!rules->orx[channel].channel_enable) {
            continue;
        }

        if ((rules->orx[channel].signalling == SPICA_SIGNAL_MODE_NRZ) &&
            (rules->orx[channel].gray_mapping == true))
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_WARN("Signalling is NRZ, forcing LRX channel %d gray_mapping rule to FALSE\n", channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            rules->orx[channel].gray_mapping = false;
        }
    }

#if !defined(INPHI_REMOVE_PMR)
    if (spica_package_has_pmr(die))
    {
        // Force gray_mapping to false if signalling is NRZ
        SPICA_FOR_CHANNEL_IN_CHANNELS(rules->package_type, SPICA_INTF_MRX)
        {
            //don't test if disabled
            if(!rules->mrx[channel].channel_enable) {
                continue;
            }

            if ((rules->mrx[channel].signalling == SPICA_SIGNAL_MODE_NRZ) &&
                (rules->mrx[channel].gray_mapping == true))
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_WARN("Signalling is NRZ, forcing HRX channel %d gray_mapping rule to FALSE\n", channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
                rules->mrx[channel].gray_mapping = false;
            }
        }
    }
#endif // defined(INPHI_REMOVE_PMR)

#if !defined(INPHI_REMOVE_PSR)
    if (spica_package_has_psr(die))
    {
        // Force gray_mapping to false if signalling is NRZ
        SPICA_FOR_CHANNEL_IN_CHANNELS(rules->package_type, SPICA_INTF_SRX)
        {
            //don't test if disabled
            if(!rules->srx[channel].channel_enable) {
                continue;
            }

            if ((rules->srx[channel].signalling == SPICA_SIGNAL_MODE_NRZ) &&
                (rules->srx[channel].gray_mapping == true))
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_WARN("Signalling is NRZ, forcing HRX channel %d gray_mapping rule to FALSE\n", channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
                rules->srx[channel].gray_mapping = false;
            }
        }
    }
#endif // defined(INPHI_REMOVE_PSR)

    SPICA_FOR_CHANNEL_IN_CHANNELS(rules->package_type, SPICA_INTF_OTX)
    {
        status |=  spica_tx_check_rules(die, channel, SPICA_INTF_OTX, &rules->otx[channel]);
    }
#if !defined(INPHI_REMOVE_PMR)
    if (spica_package_has_pmr(die))
    {
        SPICA_FOR_CHANNEL_IN_CHANNELS(rules->package_type, SPICA_INTF_MTX)
        {
            status |=  spica_tx_check_rules(die, channel, SPICA_INTF_MTX, &rules->mtx[channel]);
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    if (spica_package_has_psr(die))
    {
        SPICA_FOR_CHANNEL_IN_CHANNELS(rules->package_type, SPICA_INTF_STX)
        {
            status |=  spica_tx_check_rules(die, channel, SPICA_INTF_STX, &rules->stx[channel]);
        }
    }
#endif // defined(INPHI_REMOVE_PSR)

    // Check for user enabling CID in NRZ
    if((rules->orx[1].signalling == SPICA_SIGNAL_MODE_NRZ) && (rules->advanced.lrx_cid_losd_det_en))
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_WARN("lrx_cid_losd_det_en untested for NRZ\n");
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    }
#if !defined(INPHI_REMOVE_PMR)
    if (spica_package_has_pmr(die))
    {
        if((rules->mrx[1].signalling == SPICA_SIGNAL_MODE_NRZ) && (rules->advanced.hrx_cid_losd_det_en))
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_WARN("hrx_cid_losd_det_en untested for NRZ\n");
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    if (spica_package_has_psr(die))
    {
        if((rules->srx[1].signalling == SPICA_SIGNAL_MODE_NRZ) && (rules->advanced.hrx_cid_losd_det_en))
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_WARN("hrx_cid_losd_det_en untested for NRZ\n");
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        }
    }
#endif // defined(INPHI_REMOVE_PSR)

    SPICA_FOR_CHANNEL_IN_CHANNELS(rules->package_type, SPICA_INTF_ORX)
    {
        // Check for user enabling dsp_los_en ... print warning about threshold
        if(rules->orx[channel].los_dsp_en)
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_WARN("orx[%d].los_dsp_en set to true. Note this feature is untested.\n", channel);
            INPHI_WARN("User must ensure lrx_los_asrt_ctrl_startup and lrx_los_asrt_ctrl_datamode set to DAC code.\n");
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)            
        }
        // Check for user enabling dsp_sdt_en ... print warning about threshold   
        if(rules->orx[channel].sdt_dsp_en)
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_WARN("orx[%d].sdt_dsp_en set to true. Note this feature is untested.\n", channel);
            INPHI_WARN("User must ensure lrx_los_dsrt_ctrl_startup set to DAC code.\n");
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)            
        }
    }

    // Check if user is attempting to set "los_asrt" levels in PAM
    if(rules->orx[1].signalling == SPICA_SIGNAL_MODE_PAM) 
    {
        if(rules->lrx_los_asrt_ctrl_startup != SPICA_LOS_CTRL_AMP_100)
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_WARN("lrx_los_asrt_ctrl_startup value changed by user. This value is ignored for PAM signalling\n");
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        }
        if(rules->lrx_los_asrt_ctrl_datamode != SPICA_LOS_CTRL_AMP_100)
        {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
            INPHI_WARN("lrx_los_asrt_ctrl_datamode value changed by user. This value is ignored for PAM signalling\n");
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        }
    }

    if((rules->lrx_los_dsrt_ctrl_startup - rules->lrx_los_asrt_ctrl_startup) < 2)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_WARN("lrx_los_dsrt_ctrl_startup should be at least 100mV higher than lrx_los_asrt_ctrl_startup.\n");
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    }

    if((rules->lrx_los_dsrt_ctrl_startup - rules->lrx_los_asrt_ctrl_datamode) < 2)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_WARN("lrx_los_dsrt_ctrl_startup should be at least 100mV higher than lrx_los_asrt_ctrl_datamode.\n");
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    }

    return status;
}

/*
 * Reset the die (associated to the bundle) to have it ready for any user config
 */
inphi_status_t spica_init_per_bundle(
    uint32_t       bundle_idx,
    spica_rules_t* rules)
{
    inphi_status_t status = INPHI_OK;

    if (!spica_bundle_is_en(bundle_idx))
    {
        INPHI_CRIT("ERROR: Bundle not enabled %d\n", bundle_idx);
        return INPHI_ERROR;
    }

    uint32_t bundle_die = spica_bundle_get_die_from_bundle(bundle_idx);

    // Set the API version in the spare registers
    spica_init_api_version(bundle_die);

    SPICA_LOCK(bundle_die);

    // Check if part is in reset, then take part out of global reset
    if(!SPICA_MMD30_RESET_CFG__READ(bundle_die))
    {
        SPICA_MMD30_RESET_CFG__WRITE(bundle_die, 0x0);

        int32_t attempts=30000; // 3 seconds
        while(attempts > 0)
        {
            e_spica_fw_mode mode;
            status |= spica_mcu_fw_mode_query(bundle_die, &mode);
            //FW mode will be UNKNOWN until something has loaded
            if((status) || (mode != SPICA_FW_MODE_UNKNOWN)) {
                break;
            }
            INPHI_UDELAY(100);
            attempts -= 1;
        }
        if((status) || (attempts <= 0))
        {
            INPHI_CRIT("ERROR: Timed out waiting for bootloader...\n");
            SPICA_UNLOCK(bundle_die);
            return INPHI_ERROR;
        }
    }

    // Query the package type from the EFUSE. If it doesn't match then we
    // need to override the package type
    uint32_t base_die = spica_package_get_base_die(bundle_die);

    e_spica_package_type package = spica_package_query_efuse(base_die);

    // If the package is not set in the rules then set it to the EFUSE value.
    if(rules->package_type == SPICA_PACKAGE_TYPE_UNMAPPED)
    {
        rules->package_type = package;
    }

    //rules don't match the HW
    if(rules->package_type != package)
    {
        SPICA_MCU_SP4_FW_CFG0__PACKAGE_TYPE_VALUE__RMW(bundle_die, rules->package_type);
        SPICA_MCU_SP4_FW_CFG0__PACKAGE_TYPE_OVERRIDE__RMW(bundle_die, 1);
    }
    else
    {
        SPICA_MCU_SP4_FW_CFG0__PACKAGE_TYPE_OVERRIDE__RMW(bundle_die, 0);
    }

    // We must be in app fw mode to run spica_init
    status |= spica_mcu_block_application_mode(bundle_die, rules->fw_dwld_timeout);

    if(INPHI_OK != status)
    {
        INPHI_CRIT("ERROR: Cannot run spica_init unless the device is in application FW mode\n");
    }
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    else if(rules->fw_warn_if_mismatched)
    {
        spica_dbg_print_fw_warn_if_mismatch(bundle_die);
    }
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

    int32_t attempts=30000; // 3 seconds
    // Signal to the FW to do a top level chip init
    SPICA_TOP_RULES_0__CHIP_INIT_ACK__RMW(bundle_die, 0);
    SPICA_TOP_RULES_0__CHIP_INIT_REQ__RMW(bundle_die, 1);

    // Wait for FW to acknowledge the request
    while(attempts > 0)
    {
        // Wait for ACK
        if(SPICA_TOP_RULES_0__CHIP_INIT_ACK__READ(bundle_die)) 

        {
            break;
        }
        INPHI_UDELAY(100);
        attempts -= 1;
    }

    if (attempts <= 0)
    {
        INPHI_CRIT("ERROR: Timed out waiting for FW on die 0x%08x to ack chip_init request.\n", bundle_die);
        status |= INPHI_ERROR;
    }

    SPICA_UNLOCK(bundle_die);

    spica_bundle_rules_t bundle_rules;
    status |= spica_cp_bundle_storage_to_rules(&bundle_rules);

    return status;
}

/*
 * Reset the entire device to have it ready for any user config
 */
inphi_status_t spica_init(
    uint32_t       die,
    spica_rules_t* rules)
{
    inphi_status_t status = INPHI_OK;

    if(!rules)
    {
        INPHI_CRIT("ERROR: rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    // Before we do anything, do some sanity checking of the rules
    status |= spica_check_rules(die, rules);
    if (INPHI_OK != status)
    {
        return status;
    }

    // init all bundles
    for (uint8_t bundle_idx = 0; bundle_idx < SPICA_MAX_BUNDLES; bundle_idx++) 
    {
        if (spica_bundle_is_en(bundle_idx))
        { 
            status |= spica_init_per_bundle(bundle_idx, rules);
            if (INPHI_OK != status)
            {
                return status;
            }
        }
    }
    return status;
}

/*
 * This method is used to put a Spica bundle into operational
 * state. This method MUST be preceded by a call to spica_init.
 */
inphi_status_t spica_enter_operational_state_per_bundle(
    uint32_t       die,
    uint32_t       bundle_idx,
    spica_rules_t* rules)
{
    inphi_status_t status = INPHI_OK;
    
    if(!rules)
    {
        INPHI_CRIT("ERROR: rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    if (!spica_bundle_is_en(bundle_idx))
    {
        INPHI_CRIT("ERROR: Bundle not enabled %d\n", bundle_idx);
        return INPHI_ERROR;
    }

    status |= spica_cp_rules_to_overlays(die, bundle_idx, rules);

    if (status != INPHI_OK)
    {
        INPHI_CRIT("\nERROR sending rules to die:0x%08x, bundle:%d\n", die, bundle_idx);
        return status;
    }

    // get the die associated with the bundle
    uint32_t bdie = spica_bundle_get_die_from_bundle(bundle_idx);

    int32_t attempts=30000; // 3 seconds
    // Signal to the FW to do a top level chip init
    SPICA_TOP_RULES_0__UPDATE_ALL_RULES_ACK__RMW(bdie, 0);
    SPICA_TOP_RULES_0__UPDATE_ALL_RULES_REQ__RMW(bdie, 1);

    // Wait for FW to acknowledge the request
    while(attempts > 0)
    {
        // Wait for ACK
        if(SPICA_TOP_RULES_0__UPDATE_ALL_RULES_ACK__READ(bdie)) 
        {
            break;
        }
        INPHI_UDELAY(100);
        attempts -= 1;
    }

    if (attempts <= 0)
    {
        INPHI_CRIT("ERROR: Timed out waiting for FW on die 0x%08x to ack update_all_rules request.\n", bdie);
        status |= INPHI_ERROR;
    }

    return status;
}

/*
 * This method is used to put all the Spica bundles into operational
 * state. This method MUST be preceded by a call to spica_init.
 */
inphi_status_t spica_enter_operational_state(
    uint32_t       die,
    spica_rules_t* rules)
{
    inphi_status_t status = INPHI_OK;
    uint32_t base_die = spica_package_get_base_die(die);

    if(!rules)
    {
        INPHI_CRIT("ERROR: rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    for (uint32_t bundle_idx = 0; bundle_idx < SPICA_MAX_BUNDLES; bundle_idx++)
    {
        if (spica_bundle_is_en(bundle_idx))
        {
            status |= spica_enter_operational_state_per_bundle(base_die, bundle_idx, rules);
            if (status != INPHI_OK)
            {
                INPHI_CRIT("\nERROR calling enter_operation_state for die 0x%08x, bundle %d\n", base_die, bundle_idx);
                return status;
            }
        }
    }
    return status;
}

/*
 * This method is used to setup the default Tx rules
 */
inphi_status_t spica_tx_rules_default_set(
    uint32_t            die,
    e_spica_intf        intf,
    e_spica_driver_type driver_type_ovrd,
    spica_tx_rules_t*   tx_rules)
{
    inphi_status_t status = INPHI_OK;

    if(!tx_rules)
    {
        INPHI_CRIT("ERROR: tx rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    INPHI_MEMSET(tx_rules, 0, sizeof(spica_tx_rules_t));

    tx_rules->squelch_lock    = false;
    tx_rules->signalling      = SPICA_SIGNAL_MODE_PAM;
    tx_rules->baud_rate       = SPICA_BAUD_RATE_53p1;
    tx_rules->ieee_demap      = true;
    tx_rules->gray_mapping    = true;
    tx_rules->invert_chan     = false;
    tx_rules->swing           = SPICA_TX_SWING_100p; /* default = 100 percent */
    tx_rules->dfe_precoder_en = false; /* available on OTX only */
    tx_rules->fll_mode        = SPICA_FLL_MODE_BB_PD; 

    if (SPICA_INTF_MTX == intf)
    {
#if !defined(INPHI_REMOVE_PMR)
        // Spica HTX
        tx_rules->lut_mode    = SPICA_LUT_4TAP;
        tx_rules->fir_taps[0] = -30;  /* range -1000 to 1000 where -1000 = -1, 1000 = 1  */
        tx_rules->fir_taps[1] = 400;  
        tx_rules->fir_taps[2] = -30;  
        tx_rules->fir_taps[3] = 0;    
        tx_rules->fir_taps[4] = 0;    
        tx_rules->fir_taps[5] = 0;    
        tx_rules->fir_taps[6] = 0;    
        tx_rules->inner_eye1  = 1000; /* range  500 to 1500 where  500 = 0.5, 1500 = 1.5 */
        tx_rules->inner_eye2  = 2000; /* range 1500 to 2500 where 1500 = 1.5, 2500 = 2.5 */
#endif // defined(INPHI_REMOVE_PMR)
    }
    else if (SPICA_INTF_STX == intf)
    {
#if !defined(INPHI_REMOVE_PSR)
        // PG3 HTX
        tx_rules->lut_mode    = SPICA_LUT_4TAP;
        tx_rules->fir_taps[0] = -30;  /* range -1000 to 1000 where -1000 = -1, 1000 = 1  */
        tx_rules->fir_taps[1] = 400;  
        tx_rules->fir_taps[2] = 0;    
        tx_rules->fir_taps[3] = 0;    
        tx_rules->fir_taps[4] = 0;    
        tx_rules->fir_taps[5] = 0;    
        tx_rules->fir_taps[6] = 0;    
        tx_rules->inner_eye1  = 1000; /* range  500 to 1500 where  500 = 0.5, 1500 = 1.5 */
        tx_rules->inner_eye2  = 2000; /* range 1500 to 2500 where 1500 = 1.5, 2500 = 2.5 */
#endif // defined(INPHI_REMOVE_PSR)
    }
    else
    {
        // Spica/PG3 LTX 
        if ((SPICA_DRIVER_TYPE_EML  == driver_type_ovrd) ||
           ((SPICA_DRIVER_TYPE_NONE == driver_type_ovrd) &&
            (SPICA_DRIVER_TYPE_EML  == spica_package_get_driver_type(die))))
        {
            // driver type EML
            tx_rules->lut_mode    = SPICA_LUT_7TAP_LIN;
            tx_rules->fir_taps[0] = -50;  /* range -1000 to 1000 where -1000 = -1, 1000 = 1  */
            tx_rules->fir_taps[1] = 750;  
            tx_rules->fir_taps[2] = 50;   
            tx_rules->fir_taps[3] = -40;  
            tx_rules->fir_taps[4] = -30;  
            tx_rules->fir_taps[5] = -20;  
            tx_rules->fir_taps[6] = -10;  
            tx_rules->inner_eye1  = 1380; /* range  500 to 1500 where  500 = 0.5, 1500 = 1.5 */
            tx_rules->inner_eye2  = 2230; /* range 1500 to 2500 where 1500 = 1.5, 2500 = 2.5 */
        }
        else // driver type SiPho, 1Vpp or None 
        {
            tx_rules->lut_mode    = SPICA_LUT_7TAP_LIN;
            tx_rules->fir_taps[0] = -50;  /* range -1000 to 1000 where -1000 = -1, 1000 = 1  */
            tx_rules->fir_taps[1] = 450;  
            tx_rules->fir_taps[2] = -50;    
            tx_rules->fir_taps[3] = 0;    
            tx_rules->fir_taps[4] = 0;    
            tx_rules->fir_taps[5] = 0;    
            tx_rules->fir_taps[6] = 0;    
            tx_rules->inner_eye1  = 1000; /* range  500 to 1500 where  500 = 0.5, 1500 = 1.5 */
            tx_rules->inner_eye2  = 2000; /* range 1500 to 2500 where 1500 = 1.5, 2500 = 2.5 */
        }
    }

    return status;
}

/**
 * Struct to define channel defaults
 * @private
 */
typedef struct {
    /** line baud rate */
    e_spica_baud_rate lbr;
    /** line num chs 1-4 */
    uint8_t lchs;
    /** line signalling */
    e_spica_signal_mode lsig;
    /** host baud rate */
    e_spica_baud_rate hbr;
    /** host num chs 1-8 */
    uint8_t hchs;
    /** host signalling */
    e_spica_signal_mode hsig;
} spica_proto_mode_t;

/* Big LUT of all the protocol modes
 */
const spica_proto_mode_t spica_rules_protocol_mode_lut[] = {
    [SPICA_MODE_400G_4Px53p1_TO_4Px53p1] = {
        .hchs = 4, .lchs = 4,
        .hbr = SPICA_BAUD_RATE_53p1, .hsig = SPICA_SIGNAL_MODE_PAM,
        .lbr = SPICA_BAUD_RATE_53p1, .lsig = SPICA_SIGNAL_MODE_PAM,
    },
    [SPICA_MODE_100G_4Nx25p8_TO_4Nx25p8] = {
        .hchs = 4, .lchs = 4,
        .hbr = SPICA_BAUD_RATE_25p8, .hsig = SPICA_SIGNAL_MODE_NRZ,
        .lbr = SPICA_BAUD_RATE_25p8, .lsig = SPICA_SIGNAL_MODE_NRZ,
    },
    [SPICA_MODE_300G_4Px41p3_TO_4Px41p3] = {
        .hchs = 4, .lchs = 4,
        .hbr = SPICA_BAUD_RATE_41p3, .hsig = SPICA_SIGNAL_MODE_PAM,
        .lbr = SPICA_BAUD_RATE_41p3, .lsig = SPICA_SIGNAL_MODE_PAM,
    },
    [SPICA_MODE_200G_4Px26p6_TO_4Px26p6] = {
        .hchs = 4, .lchs = 4,
        .hbr = SPICA_BAUD_RATE_26p6, .hsig = SPICA_SIGNAL_MODE_PAM,
        .lbr = SPICA_BAUD_RATE_26p6, .lsig = SPICA_SIGNAL_MODE_PAM,
    },
    [SPICA_MODE_100G_4Nx25p8_TO_2Px25p8] = {
        .hchs = 4, .lchs = 2,
        .hbr = SPICA_BAUD_RATE_25p8, .hsig = SPICA_SIGNAL_MODE_NRZ,
        .lbr = SPICA_BAUD_RATE_25p8, .lsig = SPICA_SIGNAL_MODE_PAM,
    },
    [SPICA_MODE_400G_8Px26p6_TO_4Px53p1] = {
        .hchs = 8, .lchs = 4,
        .hbr = SPICA_BAUD_RATE_26p6, .hsig = SPICA_SIGNAL_MODE_PAM,
        .lbr = SPICA_BAUD_RATE_53p1, .lsig = SPICA_SIGNAL_MODE_PAM,
    },
    [SPICA_MODE_200G_4Px26p6_TO_2Px53p1] = {
        .hchs = 4, .lchs = 2,
        .hbr = SPICA_BAUD_RATE_26p6, .hsig = SPICA_SIGNAL_MODE_PAM,
        .lbr = SPICA_BAUD_RATE_53p1, .lsig = SPICA_SIGNAL_MODE_PAM,
    },
    [SPICA_MODE_100G_2Px26p6_TO_1Px53p1] = {
        .hchs = 2, .lchs = 1,
        .hbr = SPICA_BAUD_RATE_26p6, .hsig = SPICA_SIGNAL_MODE_PAM,
        .lbr = SPICA_BAUD_RATE_53p1, .lsig = SPICA_SIGNAL_MODE_PAM,
    },
    [SPICA_MODE_100G_4Nx26p6_TO_1Px53p1] = {
        .hchs = 4, .lchs = 1,
        .hbr = SPICA_BAUD_RATE_26p6, .hsig = SPICA_SIGNAL_MODE_NRZ,
        .lbr = SPICA_BAUD_RATE_53p1, .lsig = SPICA_SIGNAL_MODE_PAM,
    },
    [SPICA_MODE_200G_4Nx53p1_TO_4Nx53p1] = {
        .hchs = 4, .lchs = 4,
        .hbr = SPICA_BAUD_RATE_53p1, .hsig = SPICA_SIGNAL_MODE_NRZ,
        .lbr = SPICA_BAUD_RATE_53p1, .lsig = SPICA_SIGNAL_MODE_NRZ,
    },
    [SPICA_MODE_200G_8Nx26p6_TO_4Px26p6] = {
        .hchs = 8, .lchs = 4,
        .hbr = SPICA_BAUD_RATE_26p6, .hsig = SPICA_SIGNAL_MODE_NRZ,
        .lbr = SPICA_BAUD_RATE_26p6, .lsig = SPICA_SIGNAL_MODE_PAM,
    },

};

/* setup the default rules structure for a bundle based on the op_mode */
inphi_status_t spica_rules_default_set_per_bundle(
    uint32_t                 die,
    uint32_t                 bundle_idx,
    e_spica_operational_mode op_mode,
    e_spica_protocol_mode    protocol_mode,
    spica_rules_t*           rules)
{
    inphi_status_t status = INPHI_OK;

    if(!rules)
    {
        INPHI_CRIT("ERROR: rules cannot be NULL!\n");
        return INPHI_ERROR;
    }
    if (!spica_bundle_is_en(bundle_idx))
    {
        INPHI_CRIT("ERROR: Bundle not enabled %d\n", bundle_idx);
        return INPHI_ERROR;
    }
    if(op_mode >= SPICA_MODE_OP_END)
    {
        INPHI_CRIT("ERROR: Invalid op mode %d\n", op_mode);
        return INPHI_ERROR;
    }
    if(protocol_mode >= SPICA_MODE_PROT_END)
    {
        INPHI_CRIT("ERROR: Invalid protocol_mode %d\n", protocol_mode);
        return INPHI_ERROR;
    }

    //setup the host/line details based on the protocol mode
    const spica_proto_mode_t *pro = &spica_rules_protocol_mode_lut[protocol_mode];

    e_spica_signal_mode host_signalling = pro->hsig;
    e_spica_signal_mode line_signalling = pro->lsig;
    uint32_t host_baud_rate             = pro->hbr;
    uint32_t line_baud_rate             = pro->lbr;
    uint32_t host_num_channels_en       = pro->hchs;
    uint32_t line_num_channels_en       = pro->lchs;

    rules->fw_dwld_timeout              = 300; /* 15 seconds, units are SPICA_MCU_POLL_DELAY_MS milli-secs */

    // By default warn if the f/w version encountered does not
    // match the version the API was compiled with.
    rules->fw_warn_if_mismatched        = true;

    //setup the high-level rules
    rules->operational_mode             = op_mode;
    rules->protocol_mode                = protocol_mode;

    rules->driver_type_override         = SPICA_DRIVER_TYPE_NONE;

    rules->lrx_los_dsrt_ctrl_startup    = SPICA_LOS_CTRL_AMP_200;

    // Only needed for NRZ ... hardcode for PAM
    if(line_signalling == SPICA_SIGNAL_MODE_PAM)
    {
        rules->lrx_los_asrt_ctrl_startup    = SPICA_LOS_CTRL_AMP_100;
        rules->lrx_los_asrt_ctrl_datamode   = SPICA_LOS_CTRL_AMP_100;
    }
    else // NRZ 
    {
        rules->lrx_los_asrt_ctrl_startup    = SPICA_LOS_CTRL_AMP_100;
        rules->lrx_los_asrt_ctrl_datamode   = SPICA_LOS_CTRL_AMP_100;
    }

    if(line_signalling == SPICA_SIGNAL_MODE_PAM)
    {
        rules->lrx_qc.snr_threshold_mm_enter = SPICA_RX_QC_SNR_THRESH_17dB;
        rules->lrx_qc.snr_threshold_mm_exit  = SPICA_RX_QC_SNR_THRESH_16dB;
        rules->lrx_qc.slc_err_limit          = 50;
        rules->advanced.lrx_ddlf_en          = true; // hide in public API
        rules->advanced.lrx_cid_losd_det_en  = true;
    }
    else // NRZ 
    {
        rules->lrx_qc.snr_threshold_mm_enter = SPICA_RX_QC_SNR_THRESH_19dB;
        rules->lrx_qc.snr_threshold_mm_exit  = SPICA_RX_QC_SNR_THRESH_18dB;
        rules->lrx_qc.slc_err_limit          = 50;
        rules->advanced.lrx_ddlf_en          = false;
        rules->advanced.lrx_cid_losd_det_en  = false;
    }  
 
    if(host_signalling == SPICA_SIGNAL_MODE_PAM)
    {
        rules->hrx_qc.snr_threshold_mm_enter = SPICA_RX_QC_SNR_THRESH_17dB;
        rules->hrx_qc.snr_threshold_mm_exit  = SPICA_RX_QC_SNR_THRESH_16dB;
        rules->hrx_qc.slc_err_limit          = 50;
        rules->advanced.hrx_ddlf_en          = false;
        rules->advanced.hrx_cid_losd_det_en  = true;
    }
    else // NRZ 
    {
        rules->hrx_qc.snr_threshold_mm_enter = SPICA_RX_QC_SNR_THRESH_19dB;
        rules->hrx_qc.snr_threshold_mm_exit  = SPICA_RX_QC_SNR_THRESH_18dB;
        rules->hrx_qc.slc_err_limit          = 50;
        rules->advanced.hrx_ddlf_en          = false;
        rules->advanced.hrx_cid_losd_det_en  = false;
    }

    rules->advanced.lrx_low_loss_det_en      = false;

    if(host_baud_rate > SPICA_BAUD_RATE_41p3)
    { 
        rules->advanced.hrx_low_loss_det_en      = true;
    }
    else if (host_baud_rate == SPICA_BAUD_RATE_41p3)
    {
        rules->advanced.hrx_low_loss_det_en      = false;
    }
    else 
    {
        rules->advanced.hrx_low_loss_det_en      = false;
    }

    rules->advanced.lrx_double_restart_dis   = false;

    //handle host channel enables and signalling based on the op mode and package
    bool host_gray_mapping = (host_signalling == SPICA_SIGNAL_MODE_PAM);
    bool line_gray_mapping = (line_signalling == SPICA_SIGNAL_MODE_PAM);

    uint32_t base_die = spica_package_get_base_die(die);

    //get the enabled interfaces based on the op mode
    e_spica_intf en_intfs = spica_op_mode_en_intfs(base_die, op_mode);

    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_ORX)
    {
        // Channel enable dependant on operational_mode (en_intfs) and protocol_mode (line_num_channels_en)
        rules->orx[channel].channel_enable      = (en_intfs & SPICA_INTF_ORX) && (((channel-1)%SPICA_NUM_OF_ORX_CHANNELS+1) <= line_num_channels_en);
        rules->orx[channel].signalling          = line_signalling;
        rules->orx[channel].baud_rate           = line_baud_rate;
        rules->orx[channel].ieee_demap          = true;
        rules->orx[channel].gray_mapping        = line_gray_mapping;
        rules->orx[channel].invert_chan         = false;
        rules->orx[channel].sdt_dsp_en          = false;
        rules->orx[channel].los_dsp_en          = false;
        rules->orx[channel].six_bit_mode        = SPICA_6BIT_MODE_DISABLE;
        rules->orx[channel].force_mission_mode  = false;
        rules->orx[channel].restart_on_los_dis     = false;
        rules->orx[channel].ffe_const_diff_en   = true;
        rules->orx[channel].bw_idx_max          = 1;
        rules->orx[channel].vga1_tracking_period= 4; 
        rules->orx[channel].alg1_dis            = false; 
        rules->orx[channel].alg2_dis            = false; 
        rules->orx[channel].alg3_dis            = false; 
        rules->orx[channel].alg4_dis            = false; 
        rules->orx[channel].qc_all_dis          = false; 
        rules->orx[channel].qc_hist_dis         = false; 
        rules->orx[channel].qc_slc_dis          = false; 
        rules->orx[channel].qc_snr_dis          = false; 
    }
#if !defined(INPHI_REMOVE_PMR)
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_MRX)
    {
        // Channel enable dependant on operational_mode (en_intfs) and protocol_mode (host_num_channels_en)
        rules->mrx[channel].channel_enable      = (en_intfs & SPICA_INTF_MRX) && (((channel-1)%SPICA_NUM_OF_MRX_CHANNELS+1) <= host_num_channels_en);
        rules->mrx[channel].signalling          = host_signalling;
        rules->mrx[channel].baud_rate           = host_baud_rate;
        rules->mrx[channel].ieee_demap          = true;
        rules->mrx[channel].gray_mapping        = host_gray_mapping;
        rules->mrx[channel].invert_chan         = false;
        rules->mrx[channel].sdt_dsp_en          = false;
        rules->mrx[channel].los_dsp_en          = false;
        rules->mrx[channel].force_mission_mode  = false;
        rules->mrx[channel].restart_on_los_dis  = false;
        rules->mrx[channel].ffe_const_diff_en   = true;
        rules->mrx[channel].bw_idx_max          = 6;
        rules->mrx[channel].vga1_tracking_period= 4;
        rules->mrx[channel].alg1_dis            = false; 
        rules->mrx[channel].alg2_dis            = false; 
        rules->mrx[channel].alg3_dis            = false; 
        rules->mrx[channel].alg4_dis            = false;
        rules->mrx[channel].qc_all_dis          = false; 
        rules->mrx[channel].qc_hist_dis         = false; 
        rules->mrx[channel].qc_slc_dis          = false; 
        rules->mrx[channel].qc_snr_dis          = false;  
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_SRX)
    {
        // Channel enable dependant on operational_mode (en_intfs) and protocol_mode (host_num_channels_en)
        rules->srx[channel].channel_enable       = (en_intfs & SPICA_INTF_SRX) && (((channel-1)%SPICA_NUM_OF_SRX_CHANNELS+1) <= host_num_channels_en);
        rules->srx[channel].ctle_adapt_dis       = false;
        rules->srx[channel].lfeq_adapt_dis       = false;
        rules->srx[channel].skip_adapt           = false;
        rules->srx[channel].dfe_adapt_dis        = false;
        rules->srx[channel].signalling           = host_signalling;
        rules->srx[channel].data_skew_adapt_dis  = false;
        rules->srx[channel].edge_skew_adapt_dis  = false;
        rules->srx[channel].vco_temp_cal_dis     = false;
        rules->srx[channel].slc_adapt_dis        = false;
        rules->srx[channel].edge_off_adapt_dis   = false;
        rules->srx[channel].agc_adapt_dis        = false;
        rules->srx[channel].gray_mapping         = host_gray_mapping;
        rules->srx[channel].invert_chan          = false;
        rules->srx[channel].ieee_demap           = true;
        rules->srx[channel].ctle_r_adapt_dis     = false;
        rules->srx[channel].ctle_c_adapt_en      = false;
        rules->srx[channel].afe_bw_adapt_dis     = false;
        rules->srx[channel].lfeq_adapt_dis_after_init_adapt = true;
        rules->srx[channel].vco_mode             = false;

        rules->srx[channel].baud_rate            = host_baud_rate;

        rules->srx[channel].ctle_override = SPICA_SRX_RXA_AFE_CTLE_CFG__DEFAULT;
        rules->srx[channel].lfeq_override = SPICA_SRX_RXA_AFE_LFEQ_CFG__DEFAULT;

    }
#endif // defined(INPHI_REMOVE_PSR)

    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_OTX)
    {
        // set the default Tx rules
        status |= spica_tx_rules_default_set(base_die, SPICA_INTF_OTX, rules->driver_type_override, &rules->otx[channel]);
        // Channel enable dependant on operational_mode (en_intfs) and protocol_mode (line_num_channels_en)
        rules->otx[channel].channel_enable  = (en_intfs & SPICA_INTF_OTX) && (((channel-1)%SPICA_NUM_OF_OTX_CHANNELS+1) <= line_num_channels_en);
        rules->otx[channel].gray_mapping    = line_gray_mapping;
        rules->otx[channel].signalling      = line_signalling;
        rules->otx[channel].baud_rate       = line_baud_rate;
    }
#if !defined(INPHI_REMOVE_PMR)
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_MTX)
    {
        // set the default Tx rules
        status |= spica_tx_rules_default_set(base_die, SPICA_INTF_MTX, rules->driver_type_override, &rules->mtx[channel]);
        // Channel enable dependant on operational_mode (en_intfs) and protocol_mode (line_num_channels_en)
        rules->mtx[channel].channel_enable  = (en_intfs & SPICA_INTF_MTX) && (((channel-1)%SPICA_NUM_OF_MTX_CHANNELS+1) <= host_num_channels_en);
        rules->mtx[channel].gray_mapping    = host_gray_mapping;
        rules->mtx[channel].signalling      = host_signalling;
        rules->mtx[channel].baud_rate       = host_baud_rate;
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_STX)
    {
        // set the default Tx rules
        status |= spica_tx_rules_default_set(base_die, SPICA_INTF_STX, rules->driver_type_override, &rules->stx[channel]);
        // Channel enable dependant on operational_mode (en_intfs) and protocol_mode (line_num_channels_en)
        rules->stx[channel].channel_enable  = (en_intfs & SPICA_INTF_STX) && (((channel-1)%SPICA_NUM_OF_STX_CHANNELS+1) <= host_num_channels_en);
        rules->stx[channel].gray_mapping    = host_gray_mapping;
        rules->stx[channel].signalling      = host_signalling;
        rules->stx[channel].baud_rate       = host_baud_rate;
        rules->stx[channel].swing           = SPICA_TX_SWING_NA; /* Override, not applicable to STX interface */
    }
#endif // defined(INPHI_REMOVE_PSR)

    // OTX/MTX/STX xbar defaults (Dependant on operational mode and protocol mode)
    int eg_gb_ratio = host_num_channels_en/line_num_channels_en;  // Egress gearbox ratio (host:line)
    int ig_gb_ratio = eg_gb_ratio;  // Ingress gearbox ratio - default to eg_gb_ratio (host:line)

    // Set all xbar vectors in bundle to 0xf initially
    uint8_t j;
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_OTX)
    {
        for(j=0; j<sizeof(rules->otx_xbar_src_chan[0])/sizeof(rules->otx_xbar_src_chan[0][0]); j++)
        {
            rules->otx_xbar_src_chan[channel][j] = 0xf;
        }
        rules->otx_clk_xbar[channel] = 0xf;
    }
#if !defined(INPHI_REMOVE_PMR)
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_MTX)
    {
        for(j=0; j<sizeof(rules->mtx_xbar_src_chan[0])/sizeof(rules->mtx_xbar_src_chan[0][0]); j++)
        {
            rules->mtx_xbar_src_chan[channel][j] = 0xf;
        }
        rules->mtx_clk_xbar[channel] = 0xf;
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_STX)
    {
        for(j=0; j<sizeof(rules->stx_xbar_src_chan[0])/sizeof(rules->stx_xbar_src_chan[0][0]); j++)
        {
            rules->stx_xbar_src_chan[channel][j] = 0xf;
        }
        rules->stx_clk_xbar[channel] = 0xf;
    }
#endif // defined(INPHI_REMOVE_PSR)

    switch(rules->operational_mode) {
        case SPICA_MODE_LINE_PRBS:
        case SPICA_MODE_HOST_PRBS:
        case SPICA_MODE_DUAL_PRBS:
        case SPICA_MODE_EGRESS_PRBS:
        case SPICA_MODE_INGRESS_PRBS:
        case SPICA_MODE_MISSION_MODE:
            // Default ingress/egress xbar config
            break;
        case SPICA_MODE_SHALLOW_LINE_LOOPBACK:
            // Override default OTX xbar configs
            eg_gb_ratio = 1;
            break;
        case SPICA_MODE_SHALLOW_HOST_LOOPBACK:
            // Override default MTX/STX xbar settings
            ig_gb_ratio = 1;
            break;

        default:
            break;
    }

    // OTX XBAR CONFIG
    uint32_t num_channels=0;
    uint32_t first_ch_in_gb_set;
    SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_OTX)
    {
        if(num_channels>=line_num_channels_en)
        {
            // All channels needed for protocol_mode allocated within bundle 
            break;
        }

        // Calculate the base channel for gearbox set of channels
        first_ch_in_gb_set = channel + num_channels*(eg_gb_ratio - 1);

        // clk xbar config
        rules->otx_clk_xbar[channel] = first_ch_in_gb_set;

        // data xbar config
        for(int n=0; n<eg_gb_ratio; n++)
        {
            // Spread Rx channels equally amongst line channels.
            // otx_xbar_src_chan[line_channel] = {rx_channel_1, rx_channel_2, etc.}
            // ie. 4:1 gearbox mode
            // otx_xbar_src_chan[1] = {1, 2, 3, 4}
            // ie. 2:2 gearbox mode
            // otx_xbar_src_chan[1] = {1, 0xf, 0xf, 0xf}
            // otx_xbar_src_chan[2] = {2, 0xf, 0xf, 0xf}

            rules->otx_xbar_src_chan[channel][n] = first_ch_in_gb_set + n;
            //INPHI_NOTE("otx_xbar_src_chan[%d][%d] = %d\n", channel, n, rules->otx_xbar_src_chan[channel][n]);
        }
        num_channels++;
    }

#if !defined(INPHI_REMOVE_PMR)
    num_channels=0;
    if(SPICA_INTF_PMR & spica_package_get_intf(die))
    {
        // MTX XBAR CONFIG
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_MTX)
        {
            if(num_channels>=host_num_channels_en)
            {
                // All channels needed for protocol_mode allocated within bundle 
                break;
            }

            // Calculate the base channel for gearbox set of channels
            first_ch_in_gb_set = channel + (num_channels/ig_gb_ratio) - num_channels;

            // clk xbar config
            rules->mtx_clk_xbar[channel] = first_ch_in_gb_set;

            // data xbar config
            // Split up the Rx channels (Either ORX or MRX) equally amongst MTX channels.
            // For each MTX Tx channel specify a src Rx channel, and the interleave index within the channel (Reverse Gearbox)
            // An Rx channel can contain up to 4 MTX channels (When RX is ORX)
            // ie. 4:1 gearbox mode
            // mtx_xbar_src_chan[host_tx_channel][0] = src_channel
            // mtx_xbar_src_chan[host_tx_channel][1] = interleave index // 0-based
            // mtx_xbar_src_chan[1][0] = 1 // channel
            // mtx_xbar_src_chan[1][1] = 0 // interleave index 
            // mtx_xbar_src_chan[2][0] = 1
            // mtx_xbar_src_chan[2][1] = 1
            // mtx_xbar_src_chan[3][0] = 1
            // mtx_xbar_src_chan[3][1] = 2
            // mtx_xbar_src_chan[4][0] = 1
            // mtx_xbar_src_chan[4][1] = 3

            rules->mtx_xbar_src_chan[channel][0] = first_ch_in_gb_set;
            rules->mtx_xbar_src_chan[channel][1] = (channel-1)%ig_gb_ratio;
            //INPHI_NOTE("mtx_xbar_src_chan[%d][0] = %d\n", channel, rules->mtx_xbar_src_chan[channel][0]);
            //INPHI_NOTE("mtx_xbar_src_chan[%d][1] = %d\n", channel, rules->mtx_xbar_src_chan[channel][1]);

            num_channels++;
       }
    }
#endif // defined(INPHI_REMOVE_PMR)

#if !defined(INPHI_REMOVE_PSR)
    num_channels=0;
    if(SPICA_INTF_PSR & spica_package_get_intf(die))
    {   
        // STX XBAR CONFIG
        SPICA_FOR_CHANNEL_IN_BUNDLE(base_die, bundle_idx, SPICA_INTF_STX)
        {
            if(num_channels>=host_num_channels_en)
            {
                // All channels needed for protocol_mode allocated within bundle 
                break;
            }
            // Calculate the base channel for gearbox set of channels
            first_ch_in_gb_set = channel + (num_channels/ig_gb_ratio) - num_channels;

            // clk xbar config
            rules->stx_clk_xbar[channel] = first_ch_in_gb_set;

            // data xbar config
            // Split up the Rx channels (Either ORX or SRX) equally amongst STX channels.
            // For each STX Tx channel specify a src Rx channel, and the interleave index within the channel (Reverse Gearbox)
            // An Rx channel can contain up to 4 STX channels (When RX is ORX)
            // ie. 4:1 gearbox mode
            // stx_xbar_src_chan[host_tx_channel][0] = src_channel
            // stx_xbar_src_chan[host_tx_channel][1] = interleave index // 0-based
            // stx_xbar_src_chan[1][0] = 1 // channel
            // stx_xbar_src_chan[1][1] = 0 // interleave index 
            // stx_xbar_src_chan[2][0] = 1
            // stx_xbar_src_chan[2][1] = 1
            // stx_xbar_src_chan[3][0] = 1
            // stx_xbar_src_chan[3][1] = 2
            // stx_xbar_src_chan[4][0] = 1
            // stx_xbar_src_chan[4][1] = 3
            // stx_xbar_src_chan[5][0] = 0xf
            // stx_xbar_src_chan[5][1] = 0xf
            // ...
            // stx_xbar_src_chan[8][0] = 0xf
            // stx_xbar_src_chan[8][0] = 0xf

            rules->stx_xbar_src_chan[channel][0] = first_ch_in_gb_set;
            rules->stx_xbar_src_chan[channel][1] = (channel-1)%ig_gb_ratio;
            //INPHI_NOTE("stx_xbar_src_chan[%d][0] = %d\n", channel, rules->stx_xbar_src_chan[channel][0]);
            //INPHI_NOTE("stx_xbar_src_chan[%d][1] = %d\n", channel, rules->stx_xbar_src_chan[channel][1]);

            num_channels++;
        }
    }
#endif // defined(INPHI_REMOVE_PSR)

    return status;
}

/* setup the default rules structure for all bundles */
inphi_status_t spica_rules_default_set(
    uint32_t                 die,
    e_spica_operational_mode op_mode,
    e_spica_protocol_mode    protocol_mode,
    spica_rules_t*           rules)
{
    inphi_status_t status = INPHI_OK;

    if(!rules)
    {
        INPHI_CRIT("ERROR: rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    // reset the entire rules structure
    INPHI_MEMSET(rules, 0, sizeof(spica_rules_t));

    for (uint8_t bundle_idx = 0; bundle_idx < SPICA_MAX_BUNDLES; bundle_idx++) 
    {
        if (spica_bundle_is_en(bundle_idx))
        {   
            status |= spica_rules_default_set_per_bundle(die, bundle_idx, op_mode, protocol_mode, rules);
        }
    }

    return status;
}

// Squelch the transmit output for the specified channel
inphi_status_t spica_tx_squelch(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,
    bool         squelch)
{
    inphi_status_t status = INPHI_OK;

    SPICA_LOCK(die);

    if(intf == SPICA_INTF_OTX)
    {
        SPICA_OTX_TXD_SQUELCH_EN_CFG__SQUELCH_EN__RMW(die, channel, squelch);
    }
    else if (intf == SPICA_INTF_MTX)
    {
        SPICA_SMTX_PMR_TXD_SQUELCH_EN_CFG__SQUELCH_EN__RMW(die, channel, squelch);
    }
    else if (intf == SPICA_INTF_STX)
    {
        SPICA_SMTX_PSR_TXD_SQUELCH_EN_CFG__SQUELCH_EN__RMW(die, channel, squelch);
    }
    else
    {
        INPHI_CRIT("ERROR: Unsupported Interface\n");
    }

    SPICA_UNLOCK(die);

    return status;
}

/*
 * This method may be called to query the current configuration of the
 * transmitters from the ASIC.
 */
inphi_status_t spica_tx_fir_query(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    spica_tx_rules_t* tx_rules)
{
    inphi_status_t status = INPHI_OK;

    if(!tx_rules)
    {
        INPHI_CRIT("ERROR: tx rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    INPHI_MEMSET(tx_rules, 0, sizeof(*tx_rules));

    status |= spica_cp_tx_overlays_to_rules(die, channel, intf, tx_rules);

    return status;
}

/*
 * Update the TX FIR configuration.
 */
inphi_status_t spica_tx_fir_set(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    spica_tx_rules_t* tx_rules)
{
    inphi_status_t status = INPHI_OK;
    bool update_done = false;
    uint16_t data;

    // NOTE: spica_tx_fir_set() only supported on-the-fly updates to the following rules
    // - lut_mode 
    // - swing
    // - fir_taps
    // - inner_eye1
    // - inner_eye2
    // Check that user has not attempted to change unsupported rules
    if (intf == SPICA_INTF_OTX) 
    {
        data = SPICA_OTX_RULES_0__READ(die, channel);
        if(tx_rules->squelch_lock   != SPICA_OTX_RULES_0__SQUELCH_LOCK__GET(data))   status |= INPHI_ERROR;
        if(tx_rules->channel_enable != SPICA_OTX_RULES_0__CHANNEL_ENABLE__GET(data)) status |= INPHI_ERROR;
        if(tx_rules->signalling     != SPICA_OTX_RULES_0__SIGNALLING__GET(data))     status |= INPHI_ERROR;
        if(tx_rules->ieee_demap     != SPICA_OTX_RULES_0__IEEE_DEMAP__GET(data))     status |= INPHI_ERROR;
        if(tx_rules->invert_chan    != SPICA_OTX_RULES_0__INVERT_CHAN__GET(data))    status |= INPHI_ERROR;
        if(tx_rules->gray_mapping   != SPICA_OTX_RULES_0__GRAY_MAPPING__GET(data))   status |= INPHI_ERROR;
    }
    else if (intf == SPICA_INTF_MTX) 
    {
#if !defined(INPHI_REMOVE_PMR)
        data = SPICA_MTX_RULES_0__READ(die, channel);
        if(tx_rules->squelch_lock   != SPICA_MTX_RULES_0__SQUELCH_LOCK__GET(data))   status |= INPHI_ERROR;
        if(tx_rules->channel_enable != SPICA_MTX_RULES_0__CHANNEL_ENABLE__GET(data)) status |= INPHI_ERROR;
        if(tx_rules->signalling     != SPICA_MTX_RULES_0__SIGNALLING__GET(data))     status |= INPHI_ERROR;
        if(tx_rules->ieee_demap     != SPICA_MTX_RULES_0__IEEE_DEMAP__GET(data))     status |= INPHI_ERROR;
        if(tx_rules->invert_chan    != SPICA_MTX_RULES_0__INVERT_CHAN__GET(data))    status |= INPHI_ERROR;
        if(tx_rules->gray_mapping   != SPICA_MTX_RULES_0__GRAY_MAPPING__GET(data))   status |= INPHI_ERROR;
#endif // defined(INPHI_REMOVE_PMR)
    }
    else // intf == SPICA_INTF_STX 
    {
#if !defined(INPHI_REMOVE_PSR)
        data = SPICA_STX_RULES_0__READ(die, channel);
        if(tx_rules->squelch_lock   != SPICA_STX_RULES_0__SQUELCH_LOCK__GET(data))   status |= INPHI_ERROR;
        if(tx_rules->channel_enable != SPICA_STX_RULES_0__CHANNEL_ENABLE__GET(data)) status |= INPHI_ERROR;
        if(tx_rules->signalling     != SPICA_STX_RULES_0__SIGNALLING__GET(data))     status |= INPHI_ERROR;
        if(tx_rules->ieee_demap     != SPICA_STX_RULES_0__IEEE_DEMAP__GET(data))     status |= INPHI_ERROR;
        if(tx_rules->invert_chan    != SPICA_STX_RULES_0__INVERT_CHAN__GET(data))    status |= INPHI_ERROR;
        if(tx_rules->gray_mapping   != SPICA_STX_RULES_0__GRAY_MAPPING__GET(data))   status |= INPHI_ERROR;
#endif // defined(INPHI_REMOVE_PSR)
    }

    if(status != INPHI_OK) 
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Member of tx_rules() not supported by this method has been changed  ...\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        return status;
    }

    // Checks that settings for rules allowed to be changed are valid
    status |= spica_tx_check_rules(die, channel, intf, tx_rules);

    //send the rules
    status |= spica_cp_tx_rules_to_overlays(die, channel, intf, tx_rules);

    if(status != INPHI_OK) 
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Failed copying tx rules to overlays ...\n", spica_dbg_translate_intf(intf), channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        return status;
    }

    // Tell the FW that new tx rules are now available
    int32_t attempts=30000; // 3 seconds
    // Signal to the FW to config the Tx with the new rules
    if (intf == SPICA_INTF_OTX) 
    {
        SPICA_OTX_RULES_UPDATE__UPDATE_TX_FIR_ACK__RMW(die, channel, 0); // Clear ACK
        SPICA_OTX_RULES_UPDATE__UPDATE_TX_FIR_REQ__RMW(die, channel, 1); // Set REQ
        // Wait for FW to update rules
        while(attempts > 0)
        {
            update_done = SPICA_OTX_RULES_UPDATE__UPDATE_TX_FIR_ACK__READ(die, channel); // Wait for ACK
            if(update_done) 
            {
                break;
            }
            INPHI_UDELAY(100);
            attempts -= 1;
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (intf == SPICA_INTF_MTX)
    {
        SPICA_MTX_RULES_UPDATE__UPDATE_TX_FIR_ACK__RMW(die, channel, 0); // Clear ACK
        SPICA_MTX_RULES_UPDATE__UPDATE_TX_FIR_REQ__RMW(die, channel, 1); // Set REQ
        // Wait for FW to update rules
        while(attempts > 0)
        {
            update_done = SPICA_MTX_RULES_UPDATE__UPDATE_TX_FIR_ACK__READ(die, channel); // Wait for ACK
            if(update_done) 
            {
                break;
            }
            INPHI_UDELAY(100);
            attempts -= 1;
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    else // intf == SPICA_INTF_STX
    {
        SPICA_STX_RULES_UPDATE__UPDATE_TX_FIR_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_STX_RULES_UPDATE__UPDATE_TX_FIR_REQ__RMW(die, channel, 1); // Set REQ
        // Wait for FW to update rules
        while(attempts > 0)
        {
            update_done = SPICA_STX_RULES_UPDATE__UPDATE_TX_FIR_ACK__READ(die, channel); // Wait for ACK
            if(update_done) 
            {
                break;
            }
            INPHI_UDELAY(100);
            attempts -= 1;
        }
    }
#endif // defined(INPHI_REMOVE_PSR)

    if((status) || (attempts <= 0))
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Timed out waiting for FW to update tx_fir...\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        status |= INPHI_ERROR;
    }

    return status;
}

/*
 * This method may be called to query the current status of 
 * one or more interfaces of a selected channel.
 */
bool spica_channel_is_link_ready(
    uint32_t      die,
    uint32_t      channel,
    e_spica_intf  intf)
{
    uint32_t fw_lock = 0; // 0/1 bit map, same map as e_spica_intf

    if (SPICA_INTF_OTX & intf)
    {
        if (SPICA_OTX_FW_STATUS__LOCKED__READ(die, channel))
        {
            fw_lock |= SPICA_INTF_OTX;
        }
    }
    if (SPICA_INTF_ORX & intf)
    {
        if (SPICA_ORX_FW_STATUS__LOCKED__READ(die, channel))
        {
           fw_lock |= SPICA_INTF_ORX;
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    if (SPICA_INTF_MTX & intf)
    {
        if (SPICA_MTX_FW_STATUS__LOCKED__READ(die, channel))
        {
            fw_lock |= SPICA_INTF_MTX;
        }
    }
    if (SPICA_INTF_MRX & intf)
    {
        if (SPICA_MRX_FW_STATUS__LOCKED__READ(die, channel))
        {
           fw_lock |= SPICA_INTF_MRX;
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    if (SPICA_INTF_STX & intf)
    {
        if (SPICA_STX_FW_STATUS__LOCKED__READ(die, channel))
        {
            fw_lock |= SPICA_INTF_STX;
        }
    }
    if (SPICA_INTF_SRX & intf)
    {
        if (SPICA_SRX_FW_STATUS__LOCKED__READ(die, channel))
        {
           fw_lock |= SPICA_INTF_SRX;
        }
    }
#endif // defined(INPHI_REMOVE_PSR)

    // INPHI_NOTE("die=0x%08x, channel=%d, intf=0x%08x, fw_lock=0x%08x\n", die, channel, intf, fw_lock);

    if (intf == fw_lock)
    {
        return true;
    }

    return false;
}

/*
 * Wait for all channels to be in the receive ready state
 */
inphi_status_t spica_wait_for_link_ready(
    uint32_t   die,
    uint32_t   timeout_in_usecs)
{
    // Clear bottom bits to make the next stuff easier
    die = spica_package_get_base_die(die);
    uint32_t num_dies = spica_package_get_num_dies(die);

    // If there are multiple dies inside the package then
    // iterate through each one and check the status of all
    // channels.
    for(uint32_t i = 0; i < num_dies; i++)
    {
        uint32_t timer = 0;
        while((timer < timeout_in_usecs) && 
              (0 == SPICA_MCU_SP6_FW_STATUS__LOCKED__READ(die+i)))
        {
            INPHI_UDELAY(1000);
            timer += 1000;
        }
        if(timer >= timeout_in_usecs)
        {
            return INPHI_ERROR;
        }
    }
    return INPHI_OK;
}

/*
 * Wait for the selected interfaces of a channel ie ORX,OTX,MRX and MTX 
 * to be in the locked state.
 */
inphi_status_t spica_channel_wait_for_link_ready(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,
    uint32_t     timeout_in_usecs)
{
    uint32_t timer = 0;

    while (timer < timeout_in_usecs)
    {
        if (spica_channel_is_link_ready(die, channel, intf))
        {
            return INPHI_OK;
        }

        INPHI_UDELAY(1000);

        timer += 1000;
    }

    return INPHI_ERROR;
}

/*
 * This method may be called to query the current link status
 * of the interfaces of the device.
 */
inphi_status_t spica_link_status_query(
    uint32_t die,
    spica_link_status_t* link_status)
{
    inphi_status_t status = INPHI_OK;

    // Clear bottom bits to make the next stuff easier
    die = spica_package_get_base_die(die);

    uint32_t num_dies = spica_package_get_num_dies(die);

    // One entry per die
    uint16_t reset_cfg[SPICA_MAX_DIES_IN_PACKAGE] = {0};

    /* pre-set the status  */
    INPHI_MEMSET(link_status, 0, sizeof(*link_status));

    link_status->fw_lock = true;
    for(uint32_t i = 0; i < num_dies; i++) 
    {
        // get the reset state of the interface blocks
        reset_cfg[i] = SPICA_MMD30_RESET_CFG__READ(die+i);

        // Top Level is the LOCKED bit on both dies
        link_status->fw_lock &= (1 == SPICA_MCU_SP6_FW_STATUS__LOCKED__READ(die+i));
    }

    // ORX
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_ORX)
    {
        uint32_t i = spica_reg_channel_to_die(die, channel, SPICA_INTF_ORX)&1;
        if (SPICA_MMD30_RESET_CFG__ORX_SR__GET(reset_cfg[i]))
        {
            break; //bust out, this block is in reset
        }
        link_status->orx_pll_lock[channel]      = SPICA_ORX_PLL_FW_STATUS__LOCKED__READ(die, channel);
        link_status->orx_pll_fsm_state[channel] = SPICA_ORX_PLL_FW_STATUS__PLL_FSM_STATE__READ(die, channel);
        link_status->orx_fw_lock[channel]       = SPICA_ORX_FW_STATUS__LOCKED__READ(die, channel);
        link_status->orx_reset_cnt[channel]     = SPICA_ORX_FW_STATUS__RESET_COUNT__READ(die, channel);
        link_status->orx_sdt[channel]           = SPICA_ORX_FW_STATUS__SDT__READ(die, channel);
        link_status->orx_fsm_state[channel]     = SPICA_ORX_FW_STATES__FSM_STATE_TOP__READ(die, channel);
    }

    // OTX
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_OTX)
    {
        uint32_t i = spica_reg_channel_to_die(die, channel, SPICA_INTF_OTX)&1;
        if (SPICA_MMD30_RESET_CFG__OTX_SR__GET(reset_cfg[i]))
        {
            break; //bust out, this block is in reset
        }
        link_status->otx_pll_lock[channel]      = SPICA_OTX_PLL_FW_STATUS__LOCKED__READ(die, channel);
        link_status->otx_pll_fsm_state[channel] = SPICA_OTX_PLL_FW_STATUS__PLL_FSM_STATE__READ(die, channel);
        link_status->otx_fw_lock[channel]       = SPICA_OTX_FW_STATUS__LOCKED__READ(die, channel);
        link_status->otx_reset_cnt[channel]     = SPICA_OTX_FW_STATUS__RESET_COUNT__READ(die, channel);
        link_status->otx_fsm_state[channel]     = SPICA_OTX_FW_STATUS__STATE__READ(die, channel);
    }

#if !defined(INPHI_REMOVE_PMR)
    if (spica_package_has_pmr(die))
    {
        // MRX
        SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_MRX)
        {
            uint32_t i = spica_reg_channel_to_die(die, channel, SPICA_INTF_MRX)&1;
            if (SPICA_MMD30_RESET_CFG__MRX_SR__GET(reset_cfg[i]))
            {
                break; //bust out, this block is in reset or powered down
            }
            link_status->hrx_pll_lock[channel]      = SPICA_MRX_PLL_FW_STATUS__LOCKED__READ(die, channel);
            link_status->hrx_pll_fsm_state[channel] = SPICA_MRX_PLL_FW_STATUS__PLL_FSM_STATE__READ(die, channel);
            link_status->hrx_fw_lock[channel]       = SPICA_MRX_FW_STATUS__LOCKED__READ(die, channel);
            link_status->hrx_reset_cnt[channel]     = SPICA_MRX_FW_STATUS__RESET_COUNT__READ(die, channel);
            link_status->hrx_sdt[channel]           = SPICA_MRX_FW_STATUS__SDT__READ(die, channel);
            link_status->hrx_fsm_state[channel]     = SPICA_MRX_FW_STATES__FSM_STATE_TOP__READ(die, channel);
        }

        // MTX
        SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_MTX)
        {
            uint32_t i = spica_reg_channel_to_die(die, channel, SPICA_INTF_MTX)&1;
            if (SPICA_MMD30_RESET_CFG__SMTX_SR__GET(reset_cfg[i]))
            {
                break; //bust out, this block is in reset
            }
            link_status->htx_pll_lock[channel]      = SPICA_SMTX_PLL_FW_STATUS__LOCKED__READ(die, channel);
            link_status->htx_pll_fsm_state[channel] = SPICA_SMTX_PLL_FW_STATUS__PLL_FSM_STATE__READ(die, channel);
            link_status->htx_fw_lock[channel]       = SPICA_MTX_FW_STATUS__LOCKED__READ(die, channel);
            link_status->htx_reset_cnt[channel]     = SPICA_MTX_FW_STATUS__RESET_COUNT__READ(die, channel);
            link_status->htx_fsm_state[channel]     = SPICA_MTX_FW_STATUS__STATE__READ(die, channel);
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    if (spica_package_has_psr(die))
    {
        // SRX
        SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_SRX)
        {
            uint32_t i = spica_reg_channel_to_die(die, channel, SPICA_INTF_SRX)&1;
            if (SPICA_MMD30_RESET_CFG__SRX_SR__GET(reset_cfg[i]))
            {
                break; //bust out, this block is in reset
            }
            // link_status->hrx_pll_lock[channel]      = SPICA_MRX_PLL_FW_STATUS__LOCKED__READ(die, channel);
            // link_status->hrx_pll_fsm_state[channel] = SPICA_MRX_PLL_FW_STATUS__PLL_FSM_STATE__READ(die, channel);
            // link_status->hrx_vco_lock[channel]      = SPICA_SRX_RXD_INTS__CTRL_LOCKDET_LOCK_FILTEREDS__READ(die, channel);
            link_status->hrx_cdr_lock[channel]      = SPICA_SRX_RXD_INTS__CTRL_LOCKDET_LOCK_FILTEREDS__READ(die, channel);
            link_status->hrx_fw_lock[channel]       = SPICA_SRX_FW_STATUS__LOCKED__READ(die, channel);
            link_status->hrx_reset_cnt[channel]     = SPICA_SRX_FW_STATUS__RESET_COUNT__READ(die, channel);
            link_status->hrx_fsm_state[channel]     = SPICA_SRX_FW_STATUS__STATE__READ(die, channel);
            link_status->hrx_sdt[channel]           = SPICA_SRX_CH_STATUS2__SDT__READ(die, channel);
        }

        // STX
        SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_STX)
        {
            uint32_t i = spica_reg_channel_to_die(die, channel, SPICA_INTF_STX)&1;
            if (SPICA_MMD30_RESET_CFG__SMTX_SR__GET(reset_cfg[i]))
            {
                break; //bust out, this block is in reset
            }
            link_status->htx_pll_lock[channel]      = SPICA_SMTX_PLL_FW_STATUS__LOCKED__READ(die, channel);
            link_status->htx_pll_fsm_state[channel] = SPICA_SMTX_PLL_FW_STATUS__PLL_FSM_STATE__READ(die, channel);
            link_status->htx_fw_lock[channel]       = SPICA_STX_FW_STATUS__LOCKED__READ(die, channel);
            link_status->htx_reset_cnt[channel]     = SPICA_STX_FW_STATUS__RESET_COUNT__READ(die, channel);
            link_status->htx_fsm_state[channel]     = SPICA_STX_FW_STATUS__STATE__READ(die, channel);
        }
    }
#endif // defined(INPHI_REMOVE_PSR)
    return status;
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/*
 * This method may be called to print the current link status
 * of the interfaces of the device.
 */
inphi_status_t spica_link_status_print(
    uint32_t die,
    spica_link_status_t* link_status)
{
    inphi_status_t status = INPHI_OK;
    e_spica_intf rx_intf = SPICA_INTF_MRX;
    e_spica_intf tx_intf = SPICA_INTF_MTX;
    
    const spica_channels_t* line_ch;
    const spica_channels_t* host_ch;

    // get the number of channels on the line and host sides
    line_ch = spica_channels(die, SPICA_INTF_POR);
    if (spica_package_has_pmr(die))
    {     
        host_ch = spica_channels(die, SPICA_INTF_PMR);
    }
    else
    {     
        host_ch = spica_channels(die, SPICA_INTF_PSR);
    }

    INPHI_NOTE("Link Status for die 0x%08x\n", die);
    INPHI_NOTE("+---------------------------------------------------------------------------------+\n");
    INPHI_NOTE("|  Top FW Lock    %s                                                               |\n", link_status->fw_lock ? "Y" : ".");
    INPHI_NOTE("+----------------------------------------+----------------------------------------+\n");

    if (spica_package_has_pmr(die))
    {
        INPHI_NOTE("|  MTX                                   |  MRX                                   |\n");
    }
    if (spica_package_has_psr(die))
    {
        rx_intf = SPICA_INTF_SRX;
        tx_intf = SPICA_INTF_STX;
        INPHI_NOTE("|  STX                                   |  SRX                                   |\n");
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("|  Channel        1  2  3  4             |  Channel        1  2  3  4             |\n");
        INPHI_NOTE("|                -----------             |                 ----------             |\n");    
    }
    else
    {
        INPHI_NOTE("|  Channel        1  2  3  4  5  6  7  8 |  Channel        1  2  3  4  5  6  7  8 |\n");
        INPHI_NOTE("|                ----------------------- |                ----------------------- |\n");
    }
    // ------------------------------ SMTX/SMRX BLOCKS ---------------------------------------

    INPHI_NOTE("|  Reg Instance  ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, tx_intf)
    {
        uint32_t die_inst = spica_get_die_inst_from_pkg_ch(die, channel, tx_intf);
        INPHI_NOTE("%d%1x ", (die_inst >> 16), (die_inst & 0xffff));
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE("|  Reg Instance  ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, rx_intf)
    {
        uint32_t die_inst = spica_get_die_inst_from_pkg_ch(die, channel, rx_intf);
        INPHI_NOTE("%d%1x ", (die_inst >> 16), (die_inst & 0xffff));
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE("|\n");
    INPHI_NOTE("|  FW Lock      ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, tx_intf)
    {
        INPHI_NOTE("  %s", link_status->htx_fw_lock[channel] ? "Y" : ".");
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    INPHI_NOTE(" |  FW Lock      ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, rx_intf)
    {
        INPHI_NOTE("  %s", link_status->hrx_fw_lock[channel] ? "Y" : ".");
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");

    INPHI_NOTE("|  FSM State    ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, tx_intf)
    {
        INPHI_NOTE(" %02x", link_status->htx_fsm_state[channel]);
    }

    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |  FSM State    ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, rx_intf)
    {
        INPHI_NOTE(" %02x", link_status->hrx_fsm_state[channel]);
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");

    INPHI_NOTE("|  PLL Lock     ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, tx_intf)
    {
        INPHI_NOTE("  %s", link_status->htx_pll_lock[channel] ? "Y" : ".");
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    if (spica_package_has_pmr(die))
    {
        INPHI_NOTE(" |  PLL Lock     ");
        SPICA_FOR_CHANNEL_IN_CHANNELS(die, rx_intf)
        {
            INPHI_NOTE("  %s", link_status->hrx_pll_lock[channel] ? "Y" : ".");
        }
        if (host_ch->num == 4)
        {
            INPHI_NOTE("            ");
        }
        INPHI_NOTE(" |\n");
    }
    if (spica_package_has_psr(die))
    {
        INPHI_NOTE(" |  CDR Lock     ");
        SPICA_FOR_CHANNEL_IN_CHANNELS(die, rx_intf)
        {
            INPHI_NOTE("  %s", link_status->hrx_cdr_lock[channel] ? "Y" : ".");
        }
        if (host_ch->num == 4)
        {
            INPHI_NOTE("            ");
        }
        INPHI_NOTE(" |\n");
    }

    INPHI_NOTE("|  PLL FSM State");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, tx_intf)
    {
        INPHI_NOTE(" %02x", link_status->htx_pll_fsm_state[channel]);
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    if (spica_package_has_pmr(die))
    {
        INPHI_NOTE(" |  PLL FSM State");
        SPICA_FOR_CHANNEL_IN_CHANNELS(die, rx_intf)
        {
            INPHI_NOTE(" %02x", link_status->hrx_pll_fsm_state[channel]);
        }
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");
 
    INPHI_NOTE("|  Reset Count  ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, tx_intf)
    {
        INPHI_NOTE(" %02x", link_status->htx_reset_cnt[channel]);
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    INPHI_NOTE(" |  Reset Count  ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, rx_intf)
    {
        INPHI_NOTE(" %02x", link_status->hrx_reset_cnt[channel]);
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");

    INPHI_NOTE("|                                        ");
    INPHI_NOTE("|  Signal Detect");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, rx_intf)
    {
        INPHI_NOTE("  %s", link_status->hrx_sdt[channel] ? "Y" : ".");
    }
    if (host_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");

    INPHI_NOTE("|                                        |                                        |\n");
    INPHI_NOTE("+----------------------------------------+----------------------------------------+\n");
    INPHI_NOTE("|  ORX                                   |  OTX                                   |\n");
    if (host_ch->num == 4)
    {
        INPHI_NOTE("|  Channel        1  2  3  4             |  Channel        1  2  3  4             |\n");
        INPHI_NOTE("|                -----------             |                -----------             |\n");
    }
    else
    {
        INPHI_NOTE("|  Channel        1  2  3  4  5  6  7  8 |  Channel        1  2  3  4  5  6  7  8 |\n");
        INPHI_NOTE("|                ----------------------- |                ----------------------- |\n");
    }
    
    INPHI_NOTE("|  Reg Instance  ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_ORX)
    {
        uint32_t die_inst = spica_get_die_inst_from_pkg_ch(die, channel, SPICA_INTF_ORX);
        INPHI_NOTE("%d%1x ", (die_inst >> 16), (die_inst & 0xffff));
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    INPHI_NOTE("|  Reg Instance  ");
    
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_OTX)
    {
        uint32_t die_inst = spica_get_die_inst_from_pkg_ch(die, channel, SPICA_INTF_OTX);
        INPHI_NOTE("%d%1x ", (die_inst >> 16), (die_inst & 0xffff));
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE("|\n");

    INPHI_NOTE("|  FW Lock      ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_ORX)
    {
        INPHI_NOTE("  %s", link_status->orx_fw_lock[channel] ? "Y" : ".");
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    INPHI_NOTE(" |  FW Lock      ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_OTX)
    {
        INPHI_NOTE("  %s", link_status->otx_fw_lock[channel] ? "Y" : ".");
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");

    INPHI_NOTE("|  FSM State    ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_ORX)
    {
        INPHI_NOTE(" %02x", link_status->orx_fsm_state[channel]);
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    INPHI_NOTE(" |  FSM State    ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_OTX)
    {
        INPHI_NOTE(" %02x", link_status->otx_fsm_state[channel]);
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");

    INPHI_NOTE("|  PLL Lock     ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_ORX)
    {
        INPHI_NOTE("  %s", link_status->orx_pll_lock[channel] ? "Y" : ".");
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    INPHI_NOTE(" |  PLL Lock     ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_OTX)
    {
        INPHI_NOTE("  %s", link_status->otx_pll_lock[channel] ? "Y" : ".");
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");

    INPHI_NOTE("|  PLL FSM State");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_ORX)
    {
        INPHI_NOTE(" %02x", link_status->orx_pll_fsm_state[channel]);
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    INPHI_NOTE(" |  PLL FSM State");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_OTX)
    {
        INPHI_NOTE(" %02x", link_status->otx_pll_fsm_state[channel]);
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");

    INPHI_NOTE("|  Reset Count  ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_ORX)
    {
        INPHI_NOTE(" %02x", link_status->orx_reset_cnt[channel]);
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }

    INPHI_NOTE(" |  Reset Count  ");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_OTX)
    {
        INPHI_NOTE(" %02x", link_status->otx_reset_cnt[channel]);
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |\n");

    INPHI_NOTE("|  Signal Detect");
    SPICA_FOR_CHANNEL_IN_CHANNELS(die, SPICA_INTF_ORX)
    {
        INPHI_NOTE("  %s", link_status->orx_sdt[channel] ? "Y" : ".");
    }
    if (line_ch->num == 4)
    {
        INPHI_NOTE("            ");
    }
    INPHI_NOTE(" |                                        |\n");

    INPHI_NOTE("|                                        |                                        |\n");
    INPHI_NOTE("+----------------------------------------+----------------------------------------+\n");
    INPHI_NOTE("Legend: Status Y=yes, .=no\n");
    INPHI_NOTE("        Reg Instance jk, j=die, k=instance\n");

    return status;
}

/*
 * This method may be called to query then print the current link status
 * of the interfaces of the device.
 */
inphi_status_t spica_link_status_query_print(
    uint32_t die)
{
    inphi_status_t status = INPHI_OK;
    spica_link_status_t link_status;

    status |= spica_link_status_query(die, &link_status);
    status |= spica_link_status_print(die, &link_status);

    // check to see if the FW is responsible
    // spica_is_fw_running_ok(die);

    return status;
}

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

inphi_status_t spica_tx_man_config(
    uint32_t            die,
    uint32_t            channel,
    e_spica_intf        intf,
    e_spica_lut_mode    lut_mode,
    bool                is_lut_unsigned,
    bool                toggle_squelch,
    int8_t              lut[256],
    int16_t             coef[28])
{
    inphi_status_t status = INPHI_OK;
    bool squelched = false;
    uint16_t data = 0;

    // Set the API version in the spare registers
    spica_init_api_version(die);

    //Check the rules
    if((!lut) && (lut_mode != SPICA_LUT_7TAP_LIN))
    {
        INPHI_CRIT("ERROR: Must specify lut unless you're using 7TAP_LIN mode\n");
        return INPHI_ERROR;
    }
    if((lut_mode == SPICA_LUT_7TAP_LIN) || (lut_mode == SPICA_LUT_7TAP_LUT))
    {
        if((intf != SPICA_INTF_OTX) && (intf != SPICA_INTF_MTX))
        {
            INPHI_CRIT("ERROR: Only OTX and MTX interfaces support 7TAP modes\n");
            return INPHI_ERROR;
        }
        if(!coef)
        {
            INPHI_CRIT("ERROR: Must specify coef to program in 7TAP_LIN/LUT modes\n");
            return INPHI_ERROR;
        }
    }
    if(channel == SPICA_BROADCAST_CHANNEL)
    {
        INPHI_CRIT("ERROR: Cannot write Tx LUT to broadcast channel\n");
        return INPHI_ERROR;
    }

    //squelch if we need to
    if(toggle_squelch)
    {
        if(intf == SPICA_INTF_OTX) 
        {
            squelched = SPICA_OTX_TXD_SQUELCH_EN_CFG__SQUELCH_EN__READ(die, channel);
            SPICA_OTX_TXD_SQUELCH_EN_CFG__SQUELCH_EN__RMW(die, channel, 1);
        }  
#if !defined(INPHI_REMOVE_PMR)
        else if (intf == SPICA_INTF_MTX)
        {
            squelched = SPICA_SMTX_PMR_TXD_SQUELCH_EN_CFG__SQUELCH_EN__READ(die, channel);
            SPICA_SMTX_PMR_TXD_SQUELCH_EN_CFG__SQUELCH_EN__RMW(die, channel, 1);
        }    
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
        else if (intf == SPICA_INTF_STX)
        {
            squelched = SPICA_SMTX_PSR_TXD_SQUELCH_EN_CFG__SQUELCH_EN__READ(die, channel);
            SPICA_SMTX_PSR_TXD_SQUELCH_EN_CFG__SQUELCH_EN__RMW(die, channel, 1);
        }    
#endif // defined(INPHI_REMOVE_PSR)
        else
        {
            INPHI_CRIT("ERROR: INTF %d not supported\n", intf);
        } 
    }

    //make sure the FW is past the Power-on state
    int timeout = 1000;
    if(intf == SPICA_INTF_OTX)
    {
        data = SPICA_OTX_FW_STATUS__READ(die, channel);
        while((SPICA_OTX_FW_STATUS__STATE__GET(data) < 7) && (timeout > 0))
        {
            timeout -= 1;
            INPHI_UDELAY(1000);
            data = SPICA_OTX_FW_STATUS__READ(die, channel);
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (intf == SPICA_INTF_MTX)
    {
        data = SPICA_MTX_FW_STATUS__READ(die, channel);
        while((SPICA_MTX_FW_STATUS__STATE__GET(data) < 7) && (timeout > 0))
        {
            timeout -= 1;
            INPHI_UDELAY(1000);
            data = SPICA_MTX_FW_STATUS__READ(die, channel);
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    else if (intf == SPICA_INTF_STX)
    {
        data = SPICA_STX_FW_STATUS__READ(die, channel);
        while((SPICA_STX_FW_STATUS__STATE__GET(data) < 8) && (timeout > 0))
        {
            timeout -= 1;
            INPHI_UDELAY(1000);
            data = SPICA_STX_FW_STATUS__READ(die, channel);
        }
    }
#endif // defined(INPHI_REMOVE_PSR)
    else
    {
        INPHI_CRIT("ERROR: INTF %d not supported\n", intf);
    }
 
    if(timeout <= 0)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("Timed out waiting for FW to power-up %s ch %d\n", spica_dbg_translate_intf(intf), channel);
#else
        INPHI_CRIT("Timed out waiting for FW to power-up intf %d ch %d\n", intf, channel);
#endif
        return INPHI_ERROR;
    }

    //make sure the FW isn't currently accessing the LUT
    timeout = 100;
    if(intf == SPICA_INTF_OTX) 
    {
        while(SPICA_OTX_TXD_DSP_LUT_ACCESS__RBW__READ(die, channel) && (timeout > 0))
        {
            timeout -= 1;
            INPHI_UDELAY(10);
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (intf == SPICA_INTF_MTX) 
    {
        while(SPICA_SMTX_PMR_TXD_DSP_LUT_ACCESS__RBW__READ(die, channel) && (timeout > 0))
        {
            timeout -= 1;
            INPHI_UDELAY(10);
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    else if (intf == SPICA_INTF_STX) 
    {
        while(SPICA_SMTX_PSR_TXD_DSP_LUT_ACCESS__RBW__READ(die, channel) && (timeout > 0))
        {
            timeout -= 1;
            INPHI_UDELAY(10);
        }
    }
#endif // defined(INPHI_REMOVE_PSR)
    else
    {
        INPHI_CRIT("ERROR: INTF %d not supported\n", intf);
    }

    if(timeout <= 0)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("ERROR: Timed out waiting for FW to stop writing to %s ch %d LUT\n", spica_dbg_translate_intf(intf), channel);
#else
        INPHI_CRIT("ERROR: Timed out waiting for FW to stop writing to intf %d ch %d LUT\n", intf, channel);
#endif
        return INPHI_ERROR;
    }

    //ok, we need to quickly write the LUT now since the FW isn't accessing it

    if(lut_mode != SPICA_LUT_7TAP_LIN)
    {
        if(intf == SPICA_INTF_OTX) 
        {
            //write the big LUT
            SPICA_OTX_TXD_DSP_LUT_ACCESS__ADDR__RMW(die, channel, 0);
            data = SPICA_OTX_TXD_DSP_LUT_ACCESS__RBW__SET(0, 1);
            for(int i=0; i<256; i++)
            {
                SPICA_OTX_TXD_DSP_LUT_WRITE__DATA__WRITE(die, channel, lut[i]);
                data = SPICA_OTX_TXD_DSP_LUT_ACCESS__ADDR__SET(data, i);
                SPICA_OTX_TXD_DSP_LUT_ACCESS__WRITE(die, channel, data);
            }
            //set the RBW back to 0
            SPICA_OTX_TXD_DSP_LUT_ACCESS__WRITE(die, channel, 0);
        }
#if !defined(INPHI_REMOVE_PMR)
        else if (intf == SPICA_INTF_MTX)
        {
            //write the big LUT
            SPICA_SMTX_PMR_TXD_DSP_LUT_ACCESS__ADDR__RMW(die, channel, 0);
            data = SPICA_SMTX_PMR_TXD_DSP_LUT_ACCESS__RBW__SET(0, 1);
            for(int i=0; i<256; i++)
            {
                SPICA_SMTX_PMR_TXD_DSP_LUT_WRITE__DATA__WRITE(die, channel, lut[i]);
                data = SPICA_SMTX_PMR_TXD_DSP_LUT_ACCESS__ADDR__SET(data, i);
                SPICA_SMTX_PMR_TXD_DSP_LUT_ACCESS__WRITE(die, channel, data);
            }
            //set the RBW back to 0
            SPICA_SMTX_PMR_TXD_DSP_LUT_ACCESS__WRITE(die, channel, 0);
        }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
        else if (intf == SPICA_INTF_STX)
        {
            //write the big LUT
            SPICA_SMTX_PSR_TXD_DSP_LUT_ACCESS__ADDR__RMW(die, channel, 0);
            data = SPICA_SMTX_PSR_TXD_DSP_LUT_ACCESS__RBW__SET(0, 1);
            for(int i=0; i<256; i++)
            {
                SPICA_SMTX_PSR_TXD_DSP_LUT_WRITE__DATA__WRITE(die, channel, lut[i]);
                data = SPICA_SMTX_PSR_TXD_DSP_LUT_ACCESS__ADDR__SET(data, i);
                SPICA_SMTX_PSR_TXD_DSP_LUT_ACCESS__WRITE(die, channel, data);
            }
            //set the RBW back to 0
            SPICA_SMTX_PSR_TXD_DSP_LUT_ACCESS__WRITE(die, channel, 0);
        }
#endif // defined(INPHI_REMOVE_PSR)
        else 
        {
            INPHI_CRIT("ERROR: INTF %d not supported\n", intf);
        }
        //leave the RBW set while we do the COEFFs, this will prevent the FW from overwriting stuff
    }

    //write the small LUT if needed
    if(((intf == SPICA_INTF_OTX) || (intf == SPICA_INTF_MTX)) && (coef) &&
            ((lut_mode == SPICA_LUT_7TAP_LIN) || (lut_mode == SPICA_LUT_7TAP_LUT)) )
    {
        if(intf == SPICA_INTF_OTX) 
        {
            data = SPICA_OTX_TXD_DSP_COEFF_ACCESS__RBW__SET(0, 1);
            for(int i=0; i<28; i++)
            {
                data = SPICA_OTX_TXD_DSP_COEFF_ACCESS__ADDR__SET(data, i);
                data = SPICA_OTX_TXD_DSP_COEFF_ACCESS__WRITE_DATA__SET(data, coef[i]);
                SPICA_OTX_TXD_DSP_COEFF_ACCESS__WRITE(die, channel, data);
            }
            //set the RBW back to 0
            SPICA_OTX_TXD_DSP_COEFF_ACCESS__WRITE(die, channel, 0);
        }
#if !defined(INPHI_REMOVE_PMR)
        else if (intf == SPICA_INTF_MTX)
        {
            data = SPICA_SMTX_PMR_TXD_DSP_COEFF_ACCESS__RBW__SET(0, 1);
            for(int i=0; i<28; i++)
            {
                data = SPICA_SMTX_PMR_TXD_DSP_COEFF_ACCESS__ADDR__SET(data, i);
                data = SPICA_SMTX_PMR_TXD_DSP_COEFF_ACCESS__WRITE_DATA__SET(data, coef[i]);
                SPICA_SMTX_PMR_TXD_DSP_COEFF_ACCESS__WRITE(die, channel, data);
            }
            //set the RBW back to 0
            SPICA_SMTX_PMR_TXD_DSP_COEFF_ACCESS__WRITE(die, channel, 0);
        }
#endif // defined(INPHI_REMOVE_PMR)
        else 
        {
            INPHI_CRIT("ERROR: INTF %d not supported\n", intf);
        }
    }

    if(intf == SPICA_INTF_OTX) 
    {
        //set the DSP mode in HW directly
        data = SPICA_OTX_TXD_DSP_CFG__IS_LUT_UNSIGNED__SET(0, is_lut_unsigned);
        data = SPICA_OTX_TXD_DSP_CFG__MODE__SET(data, lut_mode);
        SPICA_OTX_TXD_DSP_CFG__WRITE(die, channel, data);

        //if the Tx was already unsquelched
        if(toggle_squelch && !squelched)
        {
            SPICA_OTX_TXD_SQUELCH_EN_CFG__SQUELCH_EN__RMW(die, channel, 0);
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (intf == SPICA_INTF_MTX)
    {
        //set the DSP mode in HW directly
        data = SPICA_SMTX_PMR_TXD_DSP_CFG__IS_LUT_UNSIGNED__SET(0, is_lut_unsigned);
        data = SPICA_SMTX_PMR_TXD_DSP_CFG__MODE__SET(data, lut_mode);
        SPICA_SMTX_PMR_TXD_DSP_CFG__WRITE(die, channel, data);

        //if the Tx was already unsquelched
        if(toggle_squelch && !squelched)
        {
            SPICA_SMTX_PMR_TXD_SQUELCH_EN_CFG__SQUELCH_EN__RMW(die, channel, 0);
        }
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    else if (intf == SPICA_INTF_STX)
    {
        //set the DSP mode in HW directly
        data = SPICA_SMTX_PSR_TXD_DSP_CFG__IS_LUT_UNSIGNED__SET(0, is_lut_unsigned);
        data = SPICA_SMTX_PSR_TXD_DSP_CFG__MODE__SET(data, lut_mode);
        SPICA_SMTX_PSR_TXD_DSP_CFG__WRITE(die, channel, data);

        //if the Tx was already unsquelched
        if(toggle_squelch && !squelched)
        {
            SPICA_SMTX_PSR_TXD_SQUELCH_EN_CFG__SQUELCH_EN__RMW(die, channel, 0);
        }
    }
#endif // defined(INPHI_REMOVE_PSR)
    else 
    {
        INPHI_CRIT("ERROR: INTF %d not supported\n", intf);
    }

    return status;
}

inphi_status_t spica_clock_group_enable(uint32_t die, uint32_t channel, e_spica_intf intf, bool enable)
{
    inphi_status_t status = INPHI_OK;
    bool update_done = false;
    uint32_t base_die = spica_package_get_base_die(die);

    // Communicate to FW to notify of desired clock group enable/disable
    // Use overlays

    uint32_t die_inst = spica_get_die_inst_from_pkg_ch(die, channel, intf);
    die = base_die | ((die_inst >> 16) & 0xFF);// Must redefined die since we are writing to MCU reg
    uint16_t inst = die_inst & 0xFF;

    uint16_t data;
    data = SPICA_CLOCK_GROUP_ENABLE_CFG__INTF__SET(0, intf);
    data = SPICA_CLOCK_GROUP_ENABLE_CFG__CHANNEL__SET(data, inst);
    data = SPICA_CLOCK_GROUP_ENABLE_CFG__ENABLE__SET(data, enable);
    SPICA_CLOCK_GROUP_ENABLE_CFG__WRITE(die, data);

    SPICA_GENERIC_ACK__CLK_GRP_EN_ACK__RMW(die, 0); // Clear the ACK
    SPICA_GENERIC_REQ__CLK_GRP_EN_REQ__RMW(die, 1); // Set the REQ

    int32_t attempts=30000; // 3 seconds
    // Wait for FW to update rules
    while(attempts > 0)
    {
        update_done = SPICA_GENERIC_ACK__CLK_GRP_EN_ACK__READ(die); // Wait for ACK
        if(update_done) 
        {
            break;
        }
        INPHI_UDELAY(100);
        attempts -= 1;
    }
    

    if((status) || (attempts <= 0))
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Timed out waiting for FW to dis/en clock group...\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        status |= INPHI_ERROR;
    }
    

    return status;
}

// Enables or disables the squelch lock for the specified channel
inphi_status_t spica_tx_squelch_lock(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,
    bool         squelch_lock)
{
    inphi_status_t status = INPHI_OK;

    if(intf == SPICA_INTF_OTX)
    {
        // Update the overlay rule
        SPICA_OTX_RULES_0__SQUELCH_LOCK__RMW(die, channel, squelch_lock);

        // Now notify FW that squelch_lock rule ready for update
        SPICA_OTX_RULES_UPDATE__UPDATE_TX_SQUELCH_LOCK_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_OTX_RULES_UPDATE__UPDATE_TX_SQUELCH_LOCK_REQ__RMW(die, channel, 1); // Set the REQ
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (intf == SPICA_INTF_MTX)
    {
        // Update the overlay rule
        SPICA_MTX_RULES_0__SQUELCH_LOCK__RMW(die, channel, squelch_lock);

        // Now notify FW that squelch_lock rule ready for update
        SPICA_MTX_RULES_UPDATE__UPDATE_TX_SQUELCH_LOCK_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_MTX_RULES_UPDATE__UPDATE_TX_SQUELCH_LOCK_REQ__RMW(die, channel, 1); // Set the REQ
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    else if (intf == SPICA_INTF_STX) 
    {
        // Update the overlay rule
        SPICA_STX_RULES_0__SQUELCH_LOCK__RMW(die, channel, squelch_lock);

        // Now notify FW that squelch_lock rule ready for update
        SPICA_STX_RULES_UPDATE__UPDATE_TX_SQUELCH_LOCK_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_STX_RULES_UPDATE__UPDATE_TX_SQUELCH_LOCK_REQ__RMW(die, channel, 1); // Set the REQ
    }
#endif // defined(INPHI_REMOVE_PSR)
    else 
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Invalid intf\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)     
        status |= INPHI_ERROR;
    }

    bool update_done = false;
    int32_t attempts=30000; // 3 seconds
    // Wait for FW to update rules
    while(attempts > 0)
    {
        
        if(intf == SPICA_INTF_OTX)      update_done = SPICA_OTX_RULES_UPDATE__UPDATE_TX_SQUELCH_LOCK_ACK__READ(die, channel); // Wait for ACK
        else if(intf == SPICA_INTF_MTX) update_done = SPICA_MTX_RULES_UPDATE__UPDATE_TX_SQUELCH_LOCK_ACK__READ(die, channel); // Wait for ACK
        else if(intf == SPICA_INTF_STX) update_done = SPICA_STX_RULES_UPDATE__UPDATE_TX_SQUELCH_LOCK_ACK__READ(die, channel); // Wait for ACK

        if(update_done) 
        {
            break;
        }
        INPHI_UDELAY(100);
        attempts -= 1;
    }
    
    if((status) || (attempts <= 0))
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Timed out waiting for FW to update squelch_lock...\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        status |= INPHI_ERROR;
    }
    return status;
}

// Toggle the invert status of a TX channel
inphi_status_t spica_tx_invert_toggle(
    uint32_t          die,
    uint32_t          channel,
    e_spica_intf      intf)
{
    inphi_status_t status = INPHI_OK;

    if(intf == SPICA_INTF_OTX)
    {
        // notify FW to toggle the invert_chan rule 
        SPICA_OTX_RULES_UPDATE__UPDATE_TX_INVERT_CHAN_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_OTX_RULES_UPDATE__UPDATE_TX_INVERT_CHAN_REQ__RMW(die, channel, 1); // Set the REQ
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (intf == SPICA_INTF_MTX)
    {
        // notify FW to toggle the invert_chan rule 
        SPICA_MTX_RULES_UPDATE__UPDATE_TX_INVERT_CHAN_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_MTX_RULES_UPDATE__UPDATE_TX_INVERT_CHAN_REQ__RMW(die, channel, 1); // Set the REQ
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    else if (intf == SPICA_INTF_STX) 
    {
        // notify FW to toggle the invert_chan rule 
        SPICA_STX_RULES_UPDATE__UPDATE_TX_INVERT_CHAN_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_STX_RULES_UPDATE__UPDATE_TX_INVERT_CHAN_REQ__RMW(die, channel, 1); // Set the REQ
    }
#endif // defined(INPHI_REMOVE_PSR)
    else 
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Invalid intf\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)     
        status |= INPHI_ERROR;
    }

    bool update_done = false;
    int32_t attempts=30000; // 3 seconds
    // Wait for FW to update rules
    while(attempts > 0)
    {
        
        if(intf == SPICA_INTF_OTX)      update_done = SPICA_OTX_RULES_UPDATE__UPDATE_TX_INVERT_CHAN_ACK__READ(die, channel); // Wait for ACK
        else if(intf == SPICA_INTF_MTX) update_done = SPICA_MTX_RULES_UPDATE__UPDATE_TX_INVERT_CHAN_ACK__READ(die, channel); // Wait for ACK
        else if(intf == SPICA_INTF_STX) update_done = SPICA_STX_RULES_UPDATE__UPDATE_TX_INVERT_CHAN_ACK__READ(die, channel); // Wait for ACK

        if(update_done) 
        {
            break;
        }
        INPHI_UDELAY(100);
        attempts -= 1;
    }
    
    if((status) || (attempts <= 0))
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Timed out waiting for FW to update invert_chan...\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        status |= INPHI_ERROR;
    }
    return status;

}

// Toggle the invert status of an RX channel
inphi_status_t spica_rx_invert_toggle(
    uint32_t          die,
    uint32_t          channel,
    e_spica_intf      intf)
{
    inphi_status_t status = INPHI_OK;

    if(intf == SPICA_INTF_ORX)
    {
        // notify FW to toggle the invert_chan rule 
        SPICA_ORX_FW_CONTROL__UPDATE_RX_INVERT_CHAN_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_ORX_FW_CONTROL__UPDATE_RX_INVERT_CHAN_REQ__RMW(die, channel, 1); // Set the REQ
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (intf == SPICA_INTF_MRX)
    {
        // notify FW to toggle the invert_chan rule 
        SPICA_MRX_FW_CONTROL__UPDATE_RX_INVERT_CHAN_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_MRX_FW_CONTROL__UPDATE_RX_INVERT_CHAN_REQ__RMW(die, channel, 1); // Set the REQ
    }
#endif // defined(INPHI_REMOVE_PMR)
#if !defined(INPHI_REMOVE_PSR)
    else if (intf == SPICA_INTF_SRX) 
    {
        // notify FW to toggle the invert_chan rule 
        SPICA_SRX_FW_CONTROL__UPDATE_RX_INVERT_CHAN_ACK__RMW(die, channel, 0); // Clear the ACK
        SPICA_SRX_FW_CONTROL__UPDATE_RX_INVERT_CHAN_REQ__RMW(die, channel, 1); // Set the REQ
    }
#endif // defined(INPHI_REMOVE_PSR)
    else 
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Invalid intf\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)     
        status |= INPHI_ERROR;
    }

    bool update_done = false;
    int32_t attempts=30000; // 3 seconds
    // Wait for FW to update rules
    while(attempts > 0)
    {
        
        if(intf == SPICA_INTF_ORX)      update_done = SPICA_ORX_FW_CONTROL__UPDATE_RX_INVERT_CHAN_ACK__READ(die, channel); // Wait for ACK
        else if(intf == SPICA_INTF_MRX) update_done = SPICA_MRX_FW_CONTROL__UPDATE_RX_INVERT_CHAN_ACK__READ(die, channel); // Wait for ACK
        else if(intf == SPICA_INTF_SRX) update_done = SPICA_SRX_FW_CONTROL__UPDATE_RX_INVERT_CHAN_ACK__READ(die, channel); // Wait for ACK

        if(update_done) 
        {
            break;
        }
        INPHI_UDELAY(100);
        attempts -= 1;
    }
    
    if((status) || (attempts <= 0))
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        INPHI_CRIT("%s ch%d: Timed out waiting for FW to update invert_chan...\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
        status |= INPHI_ERROR;
    }
    return status;

}

// Query the temperature
inphi_status_t spica_temperature_query(uint32_t die, int16_t* temperature)
{
    inphi_status_t status = INPHI_OK;
	int16_t temp=-273;

    if(SPICA_TMON_STATUS_1__IS_VALID__READ(die))
    {
        temp = SPICA_TMON_STATUS__READ(die);
    }
    else
    {
        INPHI_CRIT("Temperature not ready to read.\n");
        status |= INPHI_ERROR;
    }

    *temperature = temp;

    return status;
}

/** @file spica_dsp.c
 ****************************************************************************
 *
 * @brief
 *     This module contains the high level DSP diagnostic methods
 *     implemented by the API.
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

// needed to save the alg values in order to restore them
static uint16_t en1;
static uint16_t en2;
static uint16_t en3;
static uint16_t en4;
 
inphi_status_t spica_rx_dsp_acquire_estimation_semaphore(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data;
    uint16_t counter;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    if (SPICA_INTF_ORX == intf)
    {
        // Wait until rsp is 0
        // Otherwise timeout and throw error
        counter = 0;
        while (SPICA_ORX_ALG_STATUS__RSP__READ(die, channel) != 0)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                INPHI_CRIT("%s channel %d: API timed out waiting for ALG_STATUS__RSP == 0.\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                return INPHI_ERROR;
            }
        }
        
        // Wait until ctrl is 0
        // Otherwise timeout and throw error
        counter = 0;
        while (SPICA_ORX_ALG_CTRL__CTRL__READ(die, channel) != 0)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                INPHI_CRIT("%s channel %d: API timed out waiting for ALG_CTRL__CTRL == 0.\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                return INPHI_ERROR;
            }
        }

        // save the current en1...en4
        en1 = SPICA_ORX_ALG_CTRL__ALG1_EN__READ(die, channel);
        en2 = SPICA_ORX_ALG_CTRL__ALG2_EN__READ(die, channel);
        en3 = SPICA_ORX_ALG_CTRL__ALG3_EN__READ(die, channel);
        en4 = SPICA_ORX_ALG_CTRL__ALG4_EN__READ(die, channel);

        // set all en0...en3 to 0
        SPICA_ORX_ALG_CTRL__ALG1_EN__RMW(die, channel, 0);
        SPICA_ORX_ALG_CTRL__ALG2_EN__RMW(die, channel, 0);
        SPICA_ORX_ALG_CTRL__ALG3_EN__RMW(die, channel, 0);
        SPICA_ORX_ALG_CTRL__ALG4_EN__RMW(die, channel, 0);
        INPHI_MDELAY(1000);

        // wait until all algs in f/w have finished
        bool algs_running = true;
        counter = 0;
        while (algs_running)
        {
            uint16_t sts1 = SPICA_ORX_ALG_STATUS__ALG1_STATUS__READ(die, channel);
            uint16_t sts2 = SPICA_ORX_ALG_STATUS__ALG2_STATUS__READ(die, channel);
            uint16_t sts3 = SPICA_ORX_ALG_STATUS__ALG3_STATUS__READ(die, channel);
            uint16_t sts4 = SPICA_ORX_ALG_STATUS__ALG4_STATUS__READ(die, channel);

            if ((sts1 == 0) && (sts2 == 0) && (sts3 == 0) && (sts4 == 0)) 
            {
                algs_running = false;
            }

            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
                INPHI_NOTE("f/w failed waiting for DSP alg to stop running\n");
                INPHI_NOTE("ALGn=%d,%d,%d,%d\n", sts1,sts2,sts3,sts4);
                return INPHI_ERROR;
            }
        }
        // if we use search engine set the ddsl bit to 1, lets set it to 1 to be safe
        // set the ctrl = 1 and ddsl = 1 at the same time (it is important these to be 
        // set at the same time otherwise f/w won't disable the dsl)
        data = SPICA_ORX_ALG_CTRL__READ(die, channel);
        data = SPICA_ORX_ALG_CTRL__CTRL__SET(data, 1);
        data = SPICA_ORX_ALG_CTRL__DDSL__SET(data, 1);
        SPICA_ORX_ALG_CTRL__WRITE(die, channel, data);

        // wait until rsp is set to 1 by f/w
        counter = 0;
        while (SPICA_ORX_ALG_STATUS__RSP__READ(die, channel) != 1)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
                INPHI_NOTE("f/w failed to acquire semaphore\n");
                return INPHI_ERROR;
            }
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (SPICA_INTF_MRX == intf)
    {
        // Wait until rsp is 0
        // Otherwise timeout and throw error
        counter = 0;
        while (SPICA_MRX_ALG_STATUS__RSP__READ(die, channel) != 0)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                INPHI_CRIT("%s channel %d: API timed out waiting for ALG_STATUS__RSP == 0.\n", spica_dbg_translate_intf(intf), channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                return INPHI_ERROR;
            }
        }
        
        // Wait until ctrl is 0
        // Otherwise timeout and throw error
        counter = 0;
        while (SPICA_MRX_ALG_CTRL__CTRL__READ(die, channel) != 0)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                INPHI_CRIT("%s channel %d: API timed out waiting for ALG_CTRL__CTRL == 0.\n", spica_dbg_translate_intf(intf), channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                return INPHI_ERROR;
            }
        }

        // save the current en1...en4
        en1 = SPICA_MRX_ALG_CTRL__ALG1_EN__READ(die, channel);
        en2 = SPICA_MRX_ALG_CTRL__ALG2_EN__READ(die, channel);
        en3 = SPICA_MRX_ALG_CTRL__ALG3_EN__READ(die, channel);
        en4 = SPICA_MRX_ALG_CTRL__ALG4_EN__READ(die, channel);

        // set all en0...en3 to 0
        SPICA_MRX_ALG_CTRL__ALG1_EN__RMW(die, channel, 0);
        SPICA_MRX_ALG_CTRL__ALG2_EN__RMW(die, channel, 0);
        SPICA_MRX_ALG_CTRL__ALG3_EN__RMW(die, channel, 0);
        SPICA_MRX_ALG_CTRL__ALG4_EN__RMW(die, channel, 0);
        INPHI_MDELAY(1000);

        // wait until all algs in f/w have finished
        bool algs_running = true;
        counter = 0;
        while (algs_running)
        {
            uint16_t sts1 = SPICA_MRX_ALG_STATUS__ALG1_STATUS__READ(die, channel);
            uint16_t sts2 = SPICA_MRX_ALG_STATUS__ALG2_STATUS__READ(die, channel);
            uint16_t sts3 = SPICA_MRX_ALG_STATUS__ALG3_STATUS__READ(die, channel);
            uint16_t sts4 = SPICA_MRX_ALG_STATUS__ALG4_STATUS__READ(die, channel);

            if ((sts1 == 0) && (sts2 == 0) && (sts3 == 0) && (sts4 == 0)) 
            {
                algs_running = false;
            }

            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
                INPHI_NOTE("f/w failed waiting for DSP alg to stop running\n");
                INPHI_NOTE("ALGn=%d,%d,%d,%d\n", sts1,sts2,sts3,sts4);
                return INPHI_ERROR;
            }
        }
        // if we use search engine set the ddsl bit to 1, lets set it to 1 to be safe
        // set the ctrl = 1 and ddsl = 1 at the same time (it is important these to be 
        // set at the same time otherwise f/w won't disable the dsl)
        data = SPICA_MRX_ALG_CTRL__READ(die, channel);
        data = SPICA_MRX_ALG_CTRL__CTRL__SET(data, 1);
        data = SPICA_MRX_ALG_CTRL__DDSL__SET(data, 1);
        SPICA_MRX_ALG_CTRL__WRITE(die, channel, data);

        // wait until rsp is set to 1 by f/w
        counter = 0;
        while (SPICA_MRX_ALG_STATUS__RSP__READ(die, channel) != 1)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
                INPHI_NOTE("f/w failed to acquire semaphore\n");
                return INPHI_ERROR;
            }
        }
    }
#endif // defined(INPHI_REMOVE_PMR)

    return status;
}

inphi_status_t spica_rx_dsp_release_estimation_semaphore(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf)
{
    inphi_status_t status = INPHI_OK;
    uint32_t counter = 0;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    if (SPICA_INTF_ORX == intf)
    {
        // Wait until rsp is 1
        // Otherwise timeout and throw error
        counter = 0;
        while (SPICA_ORX_ALG_STATUS__RSP__READ(die, channel) != 1)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                INPHI_CRIT("%s channel %d: API timed out waiting for ALG_STATUS__RSP == 1.\n", spica_dbg_translate_intf(intf), channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                return INPHI_ERROR;
            }
        }
        
        // Wait until ctrl is 1
        // Otherwise timeout and throw error
        counter = 0;
        while (SPICA_ORX_ALG_CTRL__CTRL__READ(die, channel) != 1)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                INPHI_CRIT("%s channel %d: API timed out waiting for ALG_CTRL__CTRL == 1.\n", spica_dbg_translate_intf(intf), channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                return INPHI_ERROR;
            }
        }

        // restore all en1...en4
        SPICA_ORX_ALG_CTRL__ALG1_EN__RMW(die, channel, en1);
        SPICA_ORX_ALG_CTRL__ALG2_EN__RMW(die, channel, en2);
        SPICA_ORX_ALG_CTRL__ALG3_EN__RMW(die, channel, en3);
        SPICA_ORX_ALG_CTRL__ALG4_EN__RMW(die, channel, en4);

        // set ctrl to 0
        SPICA_ORX_ALG_CTRL__CTRL__RMW(die, channel, 0);

        // wait until rsp is set to 0 by f/w
        counter = 0;
        while (SPICA_ORX_ALG_STATUS__RSP__READ(die, channel) != 0)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
                INPHI_NOTE("f/w failed to release semaphore\n");
                return INPHI_ERROR;
            }
        }
        // Set DDSL to 0, if it has been set to 1 when acquiring semaphore
        SPICA_ORX_ALG_CTRL__DDSL__RMW(die, channel, 0);
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (SPICA_INTF_MRX == intf)
    {
        // Wait until rsp is 1
        // Otherwise timeout and throw error
        counter = 0;
        while (SPICA_MRX_ALG_STATUS__RSP__READ(die, channel) != 1)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                INPHI_CRIT("%s channel %d: API timed out waiting for ALG_STATUS__RSP == 1.\n", spica_dbg_translate_intf(intf), channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                return INPHI_ERROR;
            }
        }
        
        // Wait until ctrl is 1
        // Otherwise timeout and throw error
        counter = 0;
        while (SPICA_MRX_ALG_CTRL__CTRL__READ(die, channel) != 1)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                INPHI_CRIT("%s channel %d: API timed out waiting for ALG_CTRL__CTRL == 1.\n", spica_dbg_translate_intf(intf), channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
                return INPHI_ERROR;
            }
        }

        // restore all en1...en4
        SPICA_MRX_ALG_CTRL__ALG1_EN__RMW(die, channel, en1);
        SPICA_MRX_ALG_CTRL__ALG2_EN__RMW(die, channel, en2);
        SPICA_MRX_ALG_CTRL__ALG3_EN__RMW(die, channel, en3);
        SPICA_MRX_ALG_CTRL__ALG4_EN__RMW(die, channel, en4);

        // set ctrl to 0
        SPICA_MRX_ALG_CTRL__CTRL__RMW(die, channel, 0);

        // wait until rsp is set to 0 by f/w
        counter = 0;
        while (SPICA_MRX_ALG_STATUS__RSP__READ(die, channel) != 0)
        {
            counter++;
            INPHI_MDELAY(10);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
                INPHI_NOTE("f/w failed to release semaphore\n");
                return INPHI_ERROR;
            }
        }
        // Set DDSL to 0, if it has been set to 1 when acquiring semaphore
        SPICA_MRX_ALG_CTRL__DDSL__RMW(die, channel, 0);
    }
#endif // defined(INPHI_REMOVE_PMR)

    return status;
}

inphi_status_t spica_rx_dsp_snr_wait_for_done(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    uint32_t* snr_results)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data;
    uint16_t sto_acc;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    if (SPICA_INTF_ORX == intf)
    {
        uint16_t counter = 0;
        while (0 == SPICA_ORX_CP_ALG_DONE_INT__SNR__READ(die, channel))
        {
            counter++;
            INPHI_UDELAY(1);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
                INPHI_NOTE(" SNR estimation algorithm has not completed\n");
                return INPHI_ERROR;
            }
        }

        data = SPICA_ORX_CP_SLC_RUN_CFG__DEFAULT;
        data = SPICA_ORX_CP_SLC_RUN_CFG__MANUAL_CEN__SET(data, 0);
        SPICA_ORX_CP_SLC_RUN_CFG__WRITE(die, channel, data);

        SPICA_ORX_CP_SNR_RUN_CFG__RUN_ALG__RMW(die, channel, 0);  // clear run_alg
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__RBW__SET(0, 0);    // always doing reads
        // always doing 24b accesses (sometimes ignored by H/W based on ID)
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 0);
        // always doing an access    
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1);

        for (uint16_t slice = 0; slice < 128; slice++)
        {
            // read from storage
            sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, slice % 4);
            sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ID__SET(sto_acc, 0x88 + slice / 4);
            SPICA_ORX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
            INPHI_UDELAY(1);
            data = SPICA_ORX_CP_STORAGE_DATA1__READ(die, channel);
            uint32_t snr_data1 = ((uint32_t)data << 16);
            data = SPICA_ORX_CP_STORAGE_DATA0__READ(die, channel);
            uint32_t snr_data0 = data;
            snr_results[slice] = ((snr_data0 + snr_data1) >> 8);
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (SPICA_INTF_MRX == intf)
    {
        uint16_t counter = 0;
        while (0 == SPICA_MRX_CP_ALG_DONE_INT__SNR__READ(die, channel))
        {
            counter++;
            INPHI_UDELAY(1);
            if (counter > SPICA_RX_DSP_FW_TIME_OUT)
            {
                INPHI_NOTE(" SNR estimation algorithm has not completed\n");
                return INPHI_ERROR;
            }
        }

        data = SPICA_MRX_CP_SLC_RUN_CFG__DEFAULT;
        data = SPICA_MRX_CP_SLC_RUN_CFG__MANUAL_CEN__SET(data, 0);
        SPICA_MRX_CP_SLC_RUN_CFG__WRITE(die, channel, data);

        SPICA_MRX_CP_SNR_RUN_CFG__RUN_ALG__RMW(die, channel, 0);  // clear run_alg
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__RBW__SET(0, 0);    // always doing reads
        // always doing 24b accesses (sometimes ignored by H/W based on ID)
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 0);
        // always doing an access    
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1);

        for (uint16_t slice = 0; slice < 128; slice++)
        {
            // read from storage
            sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, slice % 4);
            sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ID__SET(sto_acc, 0x88 + slice / 4);
            SPICA_MRX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
            INPHI_UDELAY(1);
            data = SPICA_MRX_CP_STORAGE_DATA1__READ(die, channel);
            uint32_t snr_data1 = ((uint32_t)data << 16);
            data = SPICA_MRX_CP_STORAGE_DATA0__READ(die, channel);
            uint32_t snr_data0 = data;
            snr_results[slice] = ((snr_data0 + snr_data1) >> 8);
        }
    }
#endif // defined(INPHI_REMOVE_PMR)

    return status;
}
        

inphi_status_t spica_rx_dsp_snr_init_and_start(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    uint32_t step_size,
    uint32_t duration,
    uint32_t settle)
{
    inphi_status_t status = INPHI_OK;
    uint16_t data;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    if (SPICA_INTF_ORX == intf)
    {
        data = SPICA_ORX_CP_SLC_RUN_CFG__DEFAULT;
        data = SPICA_ORX_CP_SLC_RUN_CFG__MANUAL_CEN__SET(data, 1);
        SPICA_ORX_CP_SLC_RUN_CFG__WRITE(die, channel, data);

        data = SPICA_ORX_CP_SNR_CFG__DEFAULT;
        data = SPICA_ORX_CP_SNR_CFG__STEP_SIZE__SET(data, step_size);
        data = SPICA_ORX_CP_SNR_CFG__STORE_ADDR__SET(data, 0xa);
        SPICA_ORX_CP_SNR_CFG__WRITE(die, channel, data);

        // clear the snr alg 'done' interrupt bitfield
        SPICA_ORX_CP_ALG_DONE_INT__WRITE(die, channel, 1 << 12);
        SPICA_ORX_CP_SNR_RUN_CFG__DURATION__RMW(die, channel, duration);
        SPICA_ORX_CP_SNR_RUN_CFG__SETTLE__RMW(die, channel, settle);
        SPICA_ORX_CP_SNR_RUN_CFG__RUN_ALG__RMW(die, channel, 0);
        SPICA_ORX_CP_SNR_RUN_CFG__RUN_ALG__RMW(die, channel, 1);
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (SPICA_INTF_MRX == intf)
    {
        data = SPICA_MRX_CP_SLC_RUN_CFG__DEFAULT;
        data = SPICA_MRX_CP_SLC_RUN_CFG__MANUAL_CEN__SET(data, 1);
        SPICA_MRX_CP_SLC_RUN_CFG__WRITE(die, channel, data);

        data = SPICA_MRX_CP_SNR_CFG__DEFAULT;
        data = SPICA_MRX_CP_SNR_CFG__STEP_SIZE__SET(data, step_size);
        data = SPICA_MRX_CP_SNR_CFG__STORE_ADDR__SET(data, 0xa);
        SPICA_MRX_CP_SNR_CFG__WRITE(die, channel, data);

        // clear the snr alg 'done' interrupt bitfield
        SPICA_MRX_CP_ALG_DONE_INT__WRITE(die, channel, 1 << 12);
        SPICA_MRX_CP_SNR_RUN_CFG__DURATION__RMW(die, channel, duration);
        SPICA_MRX_CP_SNR_RUN_CFG__SETTLE__RMW(die, channel, settle);
        SPICA_MRX_CP_SNR_RUN_CFG__RUN_ALG__RMW(die, channel, 0);
        SPICA_MRX_CP_SNR_RUN_CFG__RUN_ALG__RMW(die, channel, 1);
    }
#endif // defined(INPHI_REMOVE_PMR)

    return status;
}

/*
 *  Returns 64 element array in this order:
 *          M3 (16)
 *          M1 (16)
 *          P1 (16)
 *          P3 (16)
 */
  inphi_status_t spica_rx_dsp_get_amp_all(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,
    uint32_t*    amp_locs)
{
    inphi_status_t status = INPHI_OK;
    uint16_t sto_acc;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    // // only update AMP levels once
    // if (amp_lvls_init)
    // {
    //     return status;
    // }

    // INPHI_NOTE("Initializing SNR AMP levels\n");
    // amp_lvls_init = true;

    // Returns 16x4-element over all 16 slices for each of the 
    // four PAM4 levels: [-3, -1, +1, +3] (in that order).
    // INPHI_MEMSET(amp_locs, 0, 16*4*4); // this done by calling method

    if (SPICA_INTF_ORX == intf)
    {
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__RBW__SET(   0,       0); // always doing reads
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 1); // always doing 12b accesses
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1); // always doing an access
     
        for (uint16_t level = 0; level < 4; level++)
        {
            for (uint16_t slice = 0; slice < 16; slice++)
            {
                sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ID__SET(sto_acc, 0xa8 + level*2 + slice / 8);
                sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, slice % 8);
                SPICA_ORX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
                INPHI_UDELAY(1);
                amp_locs[level*16 + slice] = SPICA_ORX_CP_STORAGE_DATA0__READ(die, channel) / 8; //convert from u12.3 to u9.0
            }
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (SPICA_INTF_MRX == intf)
    {
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__RBW__SET(   0,       0); // always doing reads
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 1); // always doing 12b accesses
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1); // always doing an access
     
        for (uint16_t level = 0; level < 4; level++)
        {
            for (uint16_t slice = 0; slice < 16; slice++)
            {
                sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ID__SET(sto_acc, 0xa8 + level*2 + slice / 8);
                sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, slice % 8);
                SPICA_MRX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
                INPHI_UDELAY(1);
                amp_locs[level*16 + slice] = SPICA_MRX_CP_STORAGE_DATA0__READ(die, channel) / 8; //convert from u12.3 to u9.0
            }
        }
    }
#endif // defined(INPHI_REMOVE_PMR)

    return status;
}

inphi_status_t spica_rx_dsp_hist_dsl(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,
    bool         is_nrz,
    uint32_t*    histo)
{
    inphi_status_t status = INPHI_OK;
    uint32_t steps[64];
    uint32_t i;
    uint32_t snr_results[128];
    uint32_t amp_locs[16*4];

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    status |= spica_rx_dsp_acquire_estimation_semaphore(die, channel, intf);
    if (status  != INPHI_OK)
    {
        return status;
    }

    INPHI_MEMSET(steps, 0, sizeof(steps)); 
    INPHI_MEMSET(snr_results, 0, sizeof(snr_results));
    INPHI_MEMSET(amp_locs, 0, sizeof(amp_locs));
 
    for (i = 0; i < SPICA_RX_DSP_MAX_STEP; i++)
    {
        uint32_t j = i * SPICA_RX_DSP_STEP_SIZE;
        if (j >= SPICA_RX_DSP_MAX_STEP)
        {
            break;
        }
        steps[i] = j;
    }
    uint32_t num_steps = i;

    // uint8_t single_hist_length = 4 * (2*num_steps - 1);
    // amp estimation once before running this not needed
    // since the DSL is actually running in the background
    // before this is called
    // if (is_nrz)
    // {
    //     amp_locs[0] = num_steps-1;
    //     for (i = 0; i < 3; i++)
    //     {
    //         amp_locs[i+1] = amp_locs[i] + (2 * num_steps - 1);
    //     }
    //     INPHI_NOTE("amp_locs[0] = %d\n", amp_locs[0]);
    //     INPHI_NOTE("amp_locs[1] = %d\n", amp_locs[1]);
    //     INPHI_NOTE("amp_locs[2] = %d\n", amp_locs[2]);
    //     INPHI_NOTE("amp_locs[3] = %d\n", amp_locs[3]);
    // }
    // else //PAM
    {
        // Fetch the amp locations for all humps/interleaves ie (16*4*32-bits)
        // Note: This doesn't seem right for NRZ so only for PAM now!
        status |= spica_rx_dsp_get_amp_all(die, channel, intf, amp_locs);
        if (status != INPHI_OK)
        {
            return status;
        }
        // for PAM divide the values by 2 (ie from 512 bins to 256)
        for (uint16_t level = 0; level < 4; level++)
        {
            for (uint16_t slice = 0; slice < 16; slice++)
            {
                amp_locs[level*16 + slice] >>= 1;
            }
        }
    }
    // for (uint16_t slice = 0; slice < 16; slice++)
    // {
    //     INPHI_NOTE("\nHist amp locs: i:%2d, ", slice);
    //     for (uint16_t level = 0; level < 4; level++)
    //     {
    //         INPHI_NOTE("loc(%d):%3d, ", level, amp_locs[level*16 + slice]);
    //     }
    // }
    // INPHI_NOTE("\n");
    
    
    for (i = 0; i < SPICA_RX_DSP_MAX_STEP; i++)
    {
        uint32_t step_val = steps[i];
        if (i == num_steps)
        {
            break;
        }

        // SNR results for -3 and +3 levels do not change based on nrz vs pam4
        // The 128 return values are exactly the same in nrz and pam4 but all the ones for -1 and +1 will be garbage in nrz
        // 6 slices * 4 levels/slice * 2 lo/hi per level (2 of the 4 levels will be garbage in NRZ)
        spica_rx_dsp_snr_init_and_start(die, channel, intf, step_val, 
                                             SPICA_RX_DSP_DURATION_16, 
                                             SPICA_RX_DSP_SETTLE_11);
        status = spica_rx_dsp_snr_wait_for_done(die, channel, intf, snr_results);  // 128 values (64 useful in NRZ)
        
        // snr_results is an array of 128 32-bit unsigned integers.
        // index   0.. 15: interleave 0..15, level -3, +step_val
        // index  16.. 31: interleave 0..15, level -3, -step_val
        // index  32.. 47: interleave 0..15, level -1, +step_val
        // index  48.. 63: interleave 0..15, level -1, -step_val
        // index  64.. 79: interleave 0..15, level +1, +step_val
        // index  80.. 95: interleave 0..15, level +1, -step_val
        // index  96..111: interleave 0..15, level +3, +step_val
        // index 112..127: interleave 0..15, level +3, -step_val
        
        // // Morrie: print out one slice, in order
        // for (uint32_t temp_level = 0; temp_level < 4; temp_level++)
        // {
        //     if ((temp_level == 1) || (temp_level == 2)) continue;
        //     INPHI_NOTE("%d,%d,%d,%d\n", 0, temp_level, -1*step_val, snr_results[temp_level*32+16+0]);
        //     INPHI_NOTE("%d,%d,%d,%d\n", 0, temp_level,    step_val, snr_results[temp_level*32   +0]);
        // }

        for (uint32_t amp_idx = 0; amp_idx < 4; amp_idx++)
        {
            for (uint32_t th_idx = 0; th_idx < SPICA_RX_DSP_HIST_TH_SLICES; th_idx++)
            {
                uint32_t cur_loc     = (th_idx*SPICA_RX_DSP_HIST_BINS*4)+amp_locs[amp_idx*16 + th_idx];
                uint32_t temp_idx    = th_idx + (amp_idx * 32);
                uint32_t hump_offset = amp_idx*SPICA_RX_DSP_HIST_BINS; // each hump has one 256 entry bin
                // here we get the 16 track and hold values, will calc the average later...
                if (step_val == 0) 
                {
                    histo[cur_loc+hump_offset] = (snr_results[temp_idx] + snr_results[temp_idx + 16]) / 2;
                    //INPHI_NOTE("histo[cur_loc]=[%d]=%d, \n", cur_loc, histo[cur_loc]);
                }
                else
                {
                    histo[cur_loc-i+hump_offset] = snr_results[temp_idx + 16];
                    //INPHI_NOTE("histo[cur_loc-idx]=[%d-%d]=[%d]=%d, \n", cur_loc, idx, cur_loc-idx, histo[cur_loc-idx]);

                    histo[cur_loc+i+hump_offset] = snr_results[temp_idx];
                    //INPHI_NOTE("histo[cur_loc+idx]=[%d+%d]=[%d]=%d, \n", cur_loc, idx, cur_loc+idx, histo[cur_loc+idx]);
                }
            }
        }
    }
    status |= spica_rx_dsp_release_estimation_semaphore(die, channel, intf);
    if (status  != INPHI_OK)
    {
        return status;
    }

    return status;
}

inphi_status_t spica_rx_dsp_hist_get(
    uint32_t     die,
    uint32_t     channel,
    e_spica_intf intf,
    uint32_t*    histo)
{
    inphi_status_t status = INPHI_OK;
    bool    fw_lock;
    bool    is_nrz = false;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    SPICA_LOCK(die);

    if (SPICA_INTF_ORX == intf)
    {
        fw_lock = SPICA_ORX_FW_STATUS__LOCKED__READ(die, channel);
        is_nrz  = SPICA_ORX_RULES_0__SIGNALLING__READ(die, channel);
    }
    else 
    {
        // must be MRX
        fw_lock = SPICA_MRX_FW_STATUS__LOCKED__READ(die, channel);
        is_nrz  = SPICA_MRX_RULES_0__SIGNALLING__READ(die, channel);
    }
    if (!fw_lock)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_WARN("%s[Channel %d]: NOT FW LOCKED!\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        status |= INPHI_ERROR;
#if 0
        // load a stripes pattern
        for (uint16_t i = 0; i < 255; i += 2) 
        {
            histo[i+0] = 0;
            histo[i+1] = 1048575; // 2^20
        }
#endif
    }
    else 
    {
        status = spica_rx_dsp_hist_dsl(die, channel, intf, is_nrz, histo);
        
        if (is_nrz)
        {
            // For NRZ, here's a look at the layout of a slice in histo
            // |---------|---------+---------|---------|
            // |0     255|256   511|512   767|768  1023|
            // |---------|---------+---------|---------|
            // |    -3   |    -1   |   +1    |    +3   |
            // |---------|---------+---------|---------| 
            // So here we clear the garbage in the area -1 and +1
            for (uint32_t th_idx = 0; th_idx < SPICA_RX_DSP_HIST_TH_SLICES; th_idx++)
            {
                uint32_t start_idx = 256+(th_idx*SPICA_RX_DSP_HIST_BINS*4);
                uint32_t end_idx   = 768+(th_idx*SPICA_RX_DSP_HIST_BINS*4);
                for (uint32_t idx = start_idx; idx < end_idx; idx++)  
                {
                    histo[idx] = 0;
                }
                // // mb: There is a problem in the RTL where it does not saturate the 
                // // DAC code when applying the step_size.  We can get around this in 
                // // software by ignoring results at the edges which are out-of-whack. 
                // // I observed saturated values at 61..63, 125..127 so we clear them.
                // histo[61+(th_idx*SPICA_RX_DSP_HIST_BINS)]  = 0;
                // histo[62+(th_idx*SPICA_RX_DSP_HIST_BINS)]  = 0;
                // histo[63+(th_idx*SPICA_RX_DSP_HIST_BINS)]  = 0;
                // histo[125+(th_idx*SPICA_RX_DSP_HIST_BINS)] = 0;
                // histo[126+(th_idx*SPICA_RX_DSP_HIST_BINS)] = 0;
                // histo[127+(th_idx*SPICA_RX_DSP_HIST_BINS)] = 0;
            }
        }
    }
    // for (uint32_t idx = 0; idx < SPICA_RX_DSP_HIST_BINS*SPICA_RX_DSP_HIST_TH_SLICES; idx++)
    // {
    //     INPHI_NOTE("histo[%d]=%d\n", idx, histo[idx]);
    // }
    SPICA_UNLOCK(die);
    
    return status;
}

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
double spica_rx_dsp_snr_read_db(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf)
{
    double snr_db = 0.0;
    uint16_t snr_val;

    snr_val = spica_rx_dsp_snr_read_db_fixp(die, channel, intf); 

    snr_db = (double)snr_val / 1600.0;

    return snr_db;
}
#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

uint16_t spica_rx_dsp_snr_read_db_fixp(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf)
{
    uint16_t snr_val = 0;
    bool fw_lock = false;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return snr_val;
    }

    if (intf == SPICA_INTF_ORX)
    {
         fw_lock = SPICA_ORX_FW_STATUS__LOCKED__READ(die, channel);
    }
    else
    {
         fw_lock = SPICA_MRX_FW_STATUS__LOCKED__READ(die, channel);
    }
    if(!fw_lock)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("%s Channel %d FW not locked. Cannot query VGA1\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return snr_val;
    }

    if (intf == SPICA_INTF_ORX)
    {
        snr_val = SPICA_ORX_SNR_METRIC__VALUE__READ(die, channel);
    }
    else if (intf == SPICA_INTF_MRX)
    {
        snr_val = SPICA_MRX_SNR_METRIC__VALUE__READ(die, channel);
    }
    else
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return snr_val; 
    }

    return snr_val;
}

inphi_status_t spica_rx_dsp_ltp_read_fixp(uint32_t die, uint32_t channel, e_spica_intf intf, uint16_t *ltp)
{
    if(!((intf == SPICA_INTF_ORX) || (intf == SPICA_INTF_MRX)))
    {
        INPHI_CRIT("only supported on ORX and MRX interfaces\n");
        return INPHI_ERROR;
    }

    *ltp = 0;

    uint16_t data = 0;

    if (intf == SPICA_INTF_ORX)
    {
        data = SPICA_ORX_LTP__READ(die, channel);
    }
    else 
    {
        data = SPICA_MRX_LTP__READ(die, channel);
    }

    if(0 == data)
    {
        //not available yet
        return INPHI_ERROR;
    }

    *ltp = data;
    return INPHI_OK;
}

#if defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)
#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)
double spica_rx_dsp_ltp_format(uint16_t ltp)
{
    //handle special case
    if(0xffff == ltp) {
        return INFINITY; //defined in math.h as part of C99
    }
    return ltp/256.0;
}
#endif // defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)
#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)

inphi_status_t spica_rx_dsp_vga1_query(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    uint16_t* vga1_gain)
{
    inphi_status_t status = INPHI_OK;
    uint16_t sto_acc;
    bool fw_lock = false;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    if (intf == SPICA_INTF_ORX)
    {
         fw_lock = SPICA_ORX_FW_STATUS__LOCKED__READ(die, channel);
    }
    else
    {
         fw_lock = SPICA_MRX_FW_STATUS__LOCKED__READ(die, channel);
    }
    if(!fw_lock)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("%s Channel %d FW not locked. Cannot query VGA1\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        *vga1_gain = 0xffff;
        return INPHI_ERROR;
    }

    status |= spica_rx_dsp_acquire_estimation_semaphore(die, channel, intf);
    if (status  != INPHI_OK)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("%s Channel %d failed acquiring semaphore.\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return status;
    }

    if (intf == SPICA_INTF_ORX)
    {
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__RBW__SET(0, 0); // always doing reads
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 0); // always doing 24b accesses (sometimes ignored by H/W based on ID)
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1); // always doing an access

        // VGA1 Gain
        //"VGA1 Gain (V1G), 8b binary offset (i.e. 128 center):"
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ID__SET (sto_acc, 0x131);
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__IDX__SET(sto_acc,     0); // ignored by H/W
        SPICA_ORX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
        *vga1_gain = (SPICA_ORX_CP_STORAGE_DATA1__READ(die, channel) >> 8);
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (intf == SPICA_INTF_MRX)
    {
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__RBW__SET(0, 0); // always doing reads
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 0); // always doing 24b accesses (sometimes ignored by H/W based on ID)
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1); // always doing an access

        // VGA1 Gain
        //"VGA1 Gain (V1G), 8b binary offset (i.e. 128 center):"
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ID__SET (sto_acc, 0x131);
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__IDX__SET(sto_acc,     0); // ignored by H/W
        SPICA_MRX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
        *vga1_gain = (SPICA_MRX_CP_STORAGE_DATA1__READ(die, channel) >> 8);
    }
#endif // defined(INPHI_REMOVE_PMR)

    status |= spica_rx_dsp_release_estimation_semaphore(die, channel, intf);
    if (status  != INPHI_OK)
    {
        return status;
    }

    return status;
}

inphi_status_t spica_rx_dsp_vga2_query(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    int16_t vga2_gain[SPICA_RX_DSP_SLICES])
{
    inphi_status_t status = INPHI_OK;
    uint16_t sto_acc;
    bool fw_lock = false;
    int16_t rdata = 0;
    int i = 0;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    if (intf == SPICA_INTF_ORX)
    {
         fw_lock = SPICA_ORX_FW_STATUS__LOCKED__READ(die, channel);
    }
    else
    {
         fw_lock = SPICA_MRX_FW_STATUS__LOCKED__READ(die, channel);
    }
    if(!fw_lock)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("%s Channel %d FW not locked. Cannot query VGA2\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        *vga2_gain = 0xffff;
        return INPHI_ERROR;
    }

    status |= spica_rx_dsp_acquire_estimation_semaphore(die, channel, intf);
    if (status  != INPHI_OK)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("%s Channel %d failed acquiring semaphore.\n", spica_dbg_translate_intf(intf), channel);
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return status;
    }

    if (intf == SPICA_INTF_ORX)
    {
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__RBW__SET(0, 0); // always doing reads
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 0); // always doing 24b accesses (sometimes ignored by H/W based on ID)
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1); // always doing an access

        // VGA2 Gain
        //"VGA2 Gain (V2G), 8b binary offset (i.e. 128 center):"
        for (i=0; i<SPICA_RX_DSP_SLICES; i++)
        {
            sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ID__SET (sto_acc, 0xbe + i/4);
            sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, i%4);
            SPICA_ORX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
            rdata = SPICA_ORX_CP_STORAGE_DATA1__READ(die, channel);

            rdata = rdata >> 8;            

            if (rdata >= (1 << 7)) 
            {
                rdata -= (1 << 8);
            }

            vga2_gain[i] = rdata + 128;
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if (intf == SPICA_INTF_MRX)
    {
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__RBW__SET(0, 0); // always doing reads
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 0); // always doing 24b accesses (sometimes ignored by H/W based on ID)
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1); // always doing an access

        // VGA2 Gain
        //"VGA2 Gain (V2G), 8b binary offset (i.e. 128 center):"
        for (i=0; i<SPICA_RX_DSP_SLICES; i++)
        {
            sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ID__SET (sto_acc, 0xbe + i/4);
            sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, i%4);
            SPICA_MRX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
            rdata = SPICA_MRX_CP_STORAGE_DATA1__READ(die, channel);

            rdata = rdata >> 8;            

            if (rdata >= (1 << 7)) 
            {
                rdata -= (1 << 8);
            }

            vga2_gain[i] = rdata + 128;
        }

    }
#endif // defined(INPHI_REMOVE_PMR)

    status |= spica_rx_dsp_release_estimation_semaphore(die, channel, intf);
    if (status  != INPHI_OK)
    {
        return status;
    }

    return status;
}

inphi_status_t spica_rx_dsp_ffe_taps_query(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    int16_t ffe_taps[SPICA_RX_DSP_SLICES*SPICA_RX_DSP_NUM_FFE_TAPS])
{
    inphi_status_t status = INPHI_OK;

    int16_t rdata = 0;
    uint16_t sto_acc;
    int16_t ffe_prescale[SPICA_RX_DSP_SLICES*(SPICA_RX_DSP_NUM_FFE_TAPS-1)];
    int i, j, k;
    uint16_t constrained;
    bool fw_lock = false;

    if (SPICA_INTF_SRX == intf)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("Invalid interface %s\n", spica_dbg_translate_intf(intf));
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    if (intf == SPICA_INTF_ORX)
    {
         fw_lock = SPICA_ORX_FW_STATUS__LOCKED__READ(die, channel);
    }
    else
    {
         fw_lock = SPICA_MRX_FW_STATUS__LOCKED__READ(die, channel);
    }
    if(!fw_lock)
    {
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        INPHI_CRIT("%s Channel %d FW not locked. Cannot query FFE Taps.\n", spica_dbg_translate_intf(intf), channel);
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1) 
        return INPHI_ERROR;
    }

    status |= spica_rx_dsp_acquire_estimation_semaphore(die, channel, intf);
    if (status  != INPHI_OK)
    {
        return status;
    }

    if(intf == SPICA_INTF_ORX)
    {
        constrained = SPICA_ORX_CP_FFE_CFG__CON__READ(die, channel);

        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__RBW__SET(0, 0); // always doing reads
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 0); // 24b accesses (sometimes ignored by H/W based on ID)
        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1); // always doing an access

        // "Choose FFE based on mode"
        if (SPICA_ORX_CP_FFE_CFG__MODE__READ(die, channel))
        {
            // "9x FFE Independent, s32.25, DACs are s8.0 sign-magnitude MSB=0 is positive (i.e. -127...+127)"
            for (i=0; i<SPICA_RX_DSP_SLICES; i++)
            {
                // INPHI_NOTE("Reading interleave %d data\n", i);
                for (j=0; j<3; j++)  // ID, i.e. row number within slice
                {
                    for (k=0; k<3; k++)  // IDX, i.e. accumulator within the row
                    {
                        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ID__SET(sto_acc, 0x030 + 3*i + j);
                        sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, k);
                        SPICA_ORX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
                        rdata = SPICA_ORX_CP_STORAGE_DATA1__READ(die, channel);

                        if(j==1 && k==0 && constrained)
                        {
                            //# post1 handled specially
                            rdata = rdata >> 7;
                            if (rdata >= (1 << 8)) 
                            {
                                rdata -= (1 << 9);
                            }
                            ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS-1) + j*3 + k] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS-1) + 2] + rdata;  // pre1 + post1 in constrained mode
                        }
                        else
                        {
                            rdata = rdata >> 9;
                            if (rdata >= (1 << 6)) 
                            {
                                rdata -= (1 << 7);
                            }
                            ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS-1) + j*3 + k] = rdata;
                        }
                    }
                }
            }
        }   
        else
        {
            uint16_t ffe_ca[SPICA_RX_DSP_NUM_FFE_TAPS-1];
            // "9x FFE Common (CA), s32.25, DACs are s8.0 sign-magnitude MSB=0 is positive (i.e. -127...+127)"
            //  "Actual ranges: taps -3/+3/+4/+5/+6: -15...+15; taps -2/+2: -31...+31; taps -1/+1: -63...+63)"
            sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, 0);
            for(i=0; i<9; i++)
            {
                sto_acc = SPICA_ORX_CP_STORAGE_ACCESS__ID__SET(sto_acc, 0x120 + i);
                SPICA_ORX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
                rdata = SPICA_ORX_CP_STORAGE_DATA1__READ(die, channel);
                if (i==3 && constrained==1)
                {  
                    // post1 handled specially
                    rdata = rdata >> 7;
                    if (rdata >= (1 << 8)) 
                    {
                        rdata -= (1 << 9);
                    }
                    ffe_ca[i] = ffe_ca[2] + rdata;  // pre1 + post1 in constrained mode
                }
                else
                {
                    rdata = rdata >> 9;

                    if (rdata >= (1 << 6)) 
                    {
                        rdata -= (1 << 7);
                    }
                    ffe_ca[i] = rdata;
                }
            }
            for (i=0; i<SPICA_RX_DSP_SLICES; i++)
            {
                for (j=0; j<(SPICA_RX_DSP_NUM_FFE_TAPS-1); j++) 
                {
                    ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS-1) + j] = ffe_ca[j];
                }
            }
        }
    }
#if !defined(INPHI_REMOVE_PMR)
    else if(intf == SPICA_INTF_MRX)
    {
        constrained = SPICA_MRX_CP_FFE_CFG__CON__READ(die, channel);

        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__RBW__SET(0, 0); // always doing reads
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__FORMAT__SET(sto_acc, 0); // 24b accesses (sometimes ignored by H/W based on ID)
        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ACCESS__SET(sto_acc, 1); // always doing an access

        // "Choose FFE based on mode"
        if (SPICA_MRX_CP_FFE_CFG__MODE__READ(die, channel))
        {
            // "9x FFE Independent, s32.25, DACs are s8.0 sign-magnitude MSB=0 is positive (i.e. -127...+127)"
            for (i=0; i<SPICA_RX_DSP_SLICES; i++)
            {
                // INPHI_NOTE("Reading interleave %d data\n", i);
                for (j=0; j<3; j++)  // ID, i.e. row number within slice
                {
                    for (k=0; k<3; k++)  // IDX, i.e. accumulator within the row
                    {
                        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ID__SET(sto_acc, 0x030 + 3*i + j);
                        sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, k);
                        SPICA_MRX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
                        rdata = SPICA_MRX_CP_STORAGE_DATA1__READ(die, channel);

                        if(j==1 && k==0 && constrained)
                        {
                            //# post1 handled specially
                            rdata = rdata >> 7;
                            if (rdata >= (1 << 8)) 
                            {
                                rdata -= (1 << 9);
                            }
                            ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS-1) + j*3 + k] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS-1) + 2] + rdata;  // pre1 + post1 in constrained mode
                        }
                        else
                        {
                            rdata = rdata >> 9;
                            if (rdata >= (1 << 6)) 
                            {
                                rdata -= (1 << 7);
                            }
                            ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS-1) + j*3 + k] = rdata;
                        }
                    }
                }
            }
        }   
        else
        {
            uint16_t ffe_ca[SPICA_RX_DSP_NUM_FFE_TAPS-1];
            // "9x FFE Common (CA), s32.25, DACs are s8.0 sign-magnitude MSB=0 is positive (i.e. -127...+127)"
            //  "Actual ranges: taps -3/+3/+4/+5/+6: -15...+15; taps -2/+2: -31...+31; taps -1/+1: -63...+63)"
            sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__IDX__SET(sto_acc, 0);
            for(i=0; i<9; i++)
            {
                sto_acc = SPICA_MRX_CP_STORAGE_ACCESS__ID__SET(sto_acc, 0x120 + i);
                SPICA_MRX_CP_STORAGE_ACCESS__WRITE(die, channel, sto_acc);
                rdata = SPICA_MRX_CP_STORAGE_DATA1__READ(die, channel);
                if (i==3 && constrained==1)
                {  
                    // post1 handled specially
                    rdata = rdata >> 7;
                    if (rdata >= (1 << 8)) 
                    {
                        rdata -= (1 << 9);
                    }
                    ffe_ca[i] = ffe_ca[2] + rdata;  // pre1 + post1 in constrained mode
                }
                else
                {
                    rdata = rdata >> 9;

                    if (rdata >= (1 << 6)) 
                    {
                        rdata -= (1 << 7);
                    }
                    ffe_ca[i] = rdata;
                }
            }
            for (i=0; i<SPICA_RX_DSP_SLICES; i++)
            {
                for (j=0; j<(SPICA_RX_DSP_NUM_FFE_TAPS-1); j++) 
                {
                    ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS-1) + j] = ffe_ca[j];
                }
            }
        }
    } 
#endif // defined(INPHI_REMOVE_PMR)

    // "Scale FFE"
    for (i=0; i<SPICA_RX_DSP_SLICES; i++)
    {
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 0] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS - 1) + 0]*1000 / 120.0;
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 1] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS - 1) + 1]*1000 / 124.0;
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 2] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS - 1) + 2]*1000 / 105.0;
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 3] = 1000;
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 4] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS - 1) + 3]*1000 / 105.0;
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 5] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS - 1) + 4]*1000 / 124.0;
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 6] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS - 1) + 5]*1000 / 120.0;
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 7] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS - 1) + 6]*1000 / 120.0;
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 8] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS - 1) + 7]*1000 / 120.0;
        ffe_taps[i*SPICA_RX_DSP_NUM_FFE_TAPS + 9] = ffe_prescale[i*(SPICA_RX_DSP_NUM_FFE_TAPS - 1) + 8]*1000 / 120.0;
    }   
 
    spica_rx_dsp_release_estimation_semaphore(die, channel, intf);
    if (status  != INPHI_OK)
    {
        return status;
    }

    return status;

}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS == 1)
// Translate DSP FFE Tap indices into text
const char* spica_rx_dsp_dbg_translate_ffe_tap_index(
    e_spica_ffe_taps tap_index)
{
    switch(tap_index)
    {
        case SPICA_FFE_TAP_PRE_CURSOR_3:  return("FFE_TAP_PRE_CURSOR_3");
        case SPICA_FFE_TAP_PRE_CURSOR_2:  return("FFE_TAP_PRE_CURSOR_2");
        case SPICA_FFE_TAP_PRE_CURSOR_1:  return("FFE_TAP_PRE_CURSOR_1");
        case SPICA_FFE_TAP_MAIN_CURSOR:   return("FFE_TAP_MAIN_CURSOR");
        case SPICA_FFE_TAP_POST_CURSOR_1: return("FFE_TAP_POST_CURSOR_1");
        case SPICA_FFE_TAP_POST_CURSOR_2: return("FFE_TAP_POST_CURSOR_2");
        case SPICA_FFE_TAP_POST_CURSOR_3: return("FFE_TAP_POST_CURSOR_3");
        case SPICA_FFE_TAP_POST_CURSOR_4: return("FFE_TAP_POST_CURSOR_4");
        case SPICA_FFE_TAP_POST_CURSOR_5: return("FFE_TAP_POST_CURSOR_5");
        case SPICA_FFE_TAP_POST_CURSOR_6: return("FFE_TAP_POST_CURSOR_6");
        default: break;
    }
    return "Invalid FFE Tap Index";
}

inphi_status_t spica_rx_dsp_ffe_taps_print(
    uint32_t die,
    uint32_t channel,
    e_spica_intf intf,
    int16_t ffe_taps[SPICA_RX_DSP_SLICES*SPICA_RX_DSP_NUM_FFE_TAPS])
{
    inphi_status_t status = INPHI_OK;

    uint16_t interleave;
    uint16_t tap_index;
    
    INPHI_NOTE("\n");
    INPHI_NOTE("%s Channel %d: DSP FFE Tap Values\n", spica_dbg_translate_intf(intf), channel);
    INPHI_NOTE("==================================\n");
    
    INPHI_NOTE("Interleave | PRE3 | PRE2 | PRE1 | MAIN | PST1 | PST2 | PST3 | PST4 | PST5 | PST6 |\n");
    INPHI_NOTE("-----------+------+------+------+------+------+------+------+------+------+------+\n");
    for (interleave = 0; interleave < 16; interleave++)
    {
        INPHI_NOTE("%4s%2d %4s|", "", interleave+1, "");
        for (tap_index = 0; tap_index < 10; tap_index++)
        {
           INPHI_NOTE("%6d|", (int16_t)ffe_taps[interleave*10+tap_index]);
        }
        INPHI_NOTE("\n");
    }

    return status;
}
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

/*
 * Get the first few pulse response values from the FW info buffer.
 */
inphi_status_t spica_srx_pulse_resp_query(
    uint32_t die,
    uint32_t channel,
    int32_t* resp_values,
    int32_t* len)
{
    inphi_status_t status = INPHI_OK;

    SPICA_LOCK(die);

    // Check the f/w lock status. If it's not locked don't attempt
    // to query the f/w because it may timeout
    bool locked = SPICA_SRX_FW_STATUS__LOCKED__READ(die, channel);

    if(!locked)
    {
        *len = 0;
        INPHI_CRIT("SRX not locked on channel %d, cannot fetch pulse response\n", channel);
        status = INPHI_ERROR;
        goto done;
    }

    //pulse response
    status |= spica_msg_srx_pulse_resp_request(die, channel, resp_values, *len);
    if(status)
    {
        INPHI_CRIT("Failed waiting for the pulse response from the h/w\n");
        goto done;
    }

done:
    SPICA_UNLOCK(die);

    return status;
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1
inphi_status_t spica_srx_pulse_resp_query_dump_range(uint32_t die, uint32_t start, uint32_t end)
{
    inphi_status_t status = INPHI_OK;
    e_spica_package_type package = spica_package_get_type(die);

    SPICA_LOCK(die);

    INPHI_NOTE(
        "+---------------------------------------------------------------+\n"
        "| HRX Pulse Response                                            |\n"
        "+---------+--------+--------+--------+--------+--------+--------+\n"
        "| Channel |     -3 |     -2 |     -1 |      0 |      1 |      2 |\n"
        "+---------+--------+--------+--------+--------+--------+--------+\n");

    SPICA_FOR_CHANNEL_IN_CHANNELS(package, SPICA_INTF_SRX)
    {
        if(channel < start || channel > end)
        {
            continue;
        }
        //Grab pulse response for Enabled channels only
        if(!SPICA_SRX_RULES_0__CHANNEL_ENABLE__READ(die, channel))
        {
            continue;
        }

        INPHI_NOTE("| %7d |", channel);

        int32_t resp[6];
        int32_t len = sizeof(resp)/sizeof(resp[0]);
        status |= spica_srx_pulse_resp_query(die, channel, resp, &len);
        if(INPHI_OK != status)
            goto done;

        for(int32_t i=0; i<len; i++)
        {
            INPHI_NOTE("%8d|", resp[i]);
        }
        INPHI_NOTE("\n");
    }

    INPHI_NOTE("+---------+--------+--------+--------+--------+--------+--------+\n");

done:
    SPICA_UNLOCK(die);

    return status;
}

inphi_status_t spica_srx_pulse_resp_query_dump(uint32_t die)
{
    return spica_srx_pulse_resp_query_dump_range(die, 0, 0xff);
}

#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1
/** @file mcu.c
 ****************************************************************************
 *
 * @brief
 *     This module contains the implementation of the interface to the
 *     embedded MCU.
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

#if defined(INPHI_HAS_FILESYSTEM)
#include <string.h> // String methods for progrmaming ucode from disk
#include <stdio.h>  // File IO methods for programming ucode from disk
#endif // INPHI_HAS_FILESYSTEM

/** Max debug buffer length for query_print */
#define SPICA_MCU_DEBUG_BUFFER_MAX_LENGTH 2048

/**
 * Simple function to decode the top bytes of the BOOTVER register
 * 
 * These are the valid firmware modes:
 *
 *   0xBCDD (boot upgrade/direct download)
 *   0xACC0 (Application code)
 * 
 * @param bootver [I] - BOOTVER >> 16
 * 
 * @return mode the FW is running in
 *
 * @private
 */
e_spica_fw_mode spica_mcu_decode_bootver(
    uint32_t bootver)
{
    if(bootver == 0xACC0)
    {
        return SPICA_FW_MODE_APPLICATION;
    }
    return SPICA_FW_MODE_UNKNOWN;
}

/**
 * This method is used to get the fw mode
 */
inphi_status_t spica_mcu_fw_mode_query(
    uint32_t       die,
    e_spica_fw_mode* mode)
{
    inphi_status_t status = INPHI_OK;

    uint16_t bootver = 0;
    bootver = SPICA_MCU_FW_MODE__READ(die);
    *mode = spica_mcu_decode_bootver(SPICA_MCU_FW_MODE__FW_MODE__GET(bootver));

    return status;
}

/*
 * This method blocks until the MCU is in application mode or
 * the until the timeout expires.
 */
inphi_status_t spica_mcu_block_application_mode(
    uint32_t die,
    int      timeout_in_ms)
{
    inphi_status_t status = INPHI_OK;
    e_spica_fw_mode fw_mode = SPICA_FW_MODE_UNKNOWN;
    int i = 0;

    if(timeout_in_ms < 0) {
        INPHI_CRIT("timeout needs to be >= 0\n");
        return INPHI_ERROR;
    }

    SPICA_LOCK(die);

    // Turn on the PC trace
    SPICA_MCU_GEN_CFG__PDEBUG_EN__RMW(die, 1);

    for(i = 0; i <= timeout_in_ms; i++)
    {
        status |= spica_mcu_fw_mode_query(die, &fw_mode);
        if(status != INPHI_OK) return status;
        
        if (fw_mode == SPICA_FW_MODE_APPLICATION)
        {
            /* we can proceed now that the FW is in application mode */
            break;
        }
        else if(0 == fw_mode)
        {
            /* Still waiting for application f/w to start */
            INPHI_MDELAY(1);
            continue;
        }
        else
        {
            INPHI_CRIT("Invalid FW mode: 0x%x\n", fw_mode);
            goto error;
        }
    }
    if((i >= timeout_in_ms) && (fw_mode != SPICA_FW_MODE_APPLICATION))
    {
        INPHI_CRIT("Timed-out waiting for MCU to run Application code, timeout=%d (ms)\n", timeout_in_ms);
        goto error;
    }
    goto done;
error:
    status |= INPHI_ERROR;
done:
    SPICA_UNLOCK(die);

    return status;
}

/**
 * Read from the memory through the inbound PIF interface
 */
inphi_status_t spica_mcu_pif_read(
    uint32_t  die,
    uint32_t  addr,
    uint32_t* buffer,
    uint32_t  num_words)
{
#if defined(INPHI_GUI)
    // If we're running in the GUI use the optimized
    // Inbound PIF methods for better performance.
    extern inphi_status_t inphi_gui_mcu_pif_read(
        uint32_t        die,
        uint32_t        addr,
        const uint32_t* buffer,
        uint32_t        num_words);
    return inphi_gui_mcu_pif_read(die, addr, buffer, num_words);
#endif

    inphi_status_t status = INPHI_OK;
    uint16_t temp = 0;
    uint16_t cfg = 0;
    uint16_t i;
    int guard = 1000;
    SPICA_LOCK(die);

    while(SPICA_MCU_INBPIF_RSTATUS1__RD_PENDING__READ(die) && (guard > 0))
    {
        guard--;
        continue;
    }

    if(guard <= 0)
    {
        INPHI_CRIT("Memory access failure on die %x\n", die);
        status |= INPHI_ERROR;
        goto exit;
    }
    
    cfg = SPICA_MCU_INBPIF_CFG0__READ(die);
    cfg = SPICA_MCU_INBPIF_CFG0__CNTL__SET(cfg, 1);
    cfg = SPICA_MCU_INBPIF_CFG0__PRIORITY__SET(cfg, 3);
    SPICA_MCU_INBPIF_CFG0__WRITE(die, cfg);

    //setup the controller, do NOT change the order of these accesses
    cfg = SPICA_MCU_INBPIF_CFG1__READ(die);
    cfg = SPICA_MCU_INBPIF_CFG1__RDENA__SET(cfg, 1);
    cfg = SPICA_MCU_INBPIF_CFG1__STRIDE__SET(cfg, 2); //32b at a time
    SPICA_MCU_INBPIF_CFG1__WRITE(die, cfg);

    SPICA_MCU_INBPIF_ADDR0__WRITE(die, addr & 0xffff);
    SPICA_MCU_INBPIF_ADDR1__WRITE(die, (addr >> 16) & 0xffff);

    for(i = 0; i < num_words; ++i)
    {
        guard = 1000;
#if (!defined(INPHI_HAS_INBPIF_READ_POLLING)) || \
    (defined(INPHI_HAS_INBPIF_READ_POLLING) && (INPHI_HAS_INBPIF_READ_POLLING == 1))
        while(SPICA_MCU_INBPIF_RSTATUS1__RD_PENDING__READ(die) && guard > 0)
        {
            guard--;
            continue;
        }
            
        if(guard <= 0)
        {
            INPHI_CRIT("Memory access failure on die %x\n", die);
            status |= INPHI_ERROR;
        }
#endif
    
        temp = SPICA_MCU_INBPIF_RDATA__READ(die);
        buffer[i] = (uint32_t)temp;
        temp = SPICA_MCU_INBPIF_RDATA__READ(die);
        buffer[i] |= (uint32_t)temp << 16;
        if(status) goto exit;
    }

exit:
    //disable the read enable so that we can do register dumps once more
    cfg = SPICA_MCU_INBPIF_CFG1__READ(die);
    cfg = SPICA_MCU_INBPIF_CFG1__RDENA__SET(cfg, 0);
    SPICA_MCU_INBPIF_CFG1__WRITE(die, cfg);

    SPICA_UNLOCK(die);

    return status;
}

/**
 * Top bits of the MCU DRAM address space
 * @private
 */
#define SPICA_MCU_DRAM_ADDR_MSW 0x5ff8

/**
 * Write to the memory through the inbound PIF interface
 */
inphi_status_t spica_mcu_pif_write(
    uint32_t        die,
    uint32_t        addr,
    const uint32_t* buffer,
    uint32_t        num_words)
{
#if defined(INPHI_GUI)
    // If we're running in the GUI use the optimized
    // Inbound PIF methods for better performance.
    extern inphi_status_t inphi_gui_mcu_pif_write(
        uint32_t        die,
        uint32_t        addr,
        const uint32_t* buffer,
        uint32_t        num_words);
    return inphi_gui_mcu_pif_write(die, addr, buffer, num_words);
#endif

    inphi_status_t status = INPHI_OK;
    uint16_t cfg = 0;
    uint16_t i;
    int guard = 1000;

    SPICA_LOCK(die);

    while(SPICA_MCU_INBPIF_RSTATUS1__RD_PENDING__READ(die) && (guard > 0))
    {
        guard--;
        continue;
    }
    
    if(guard <= 0)
    {
        INPHI_CRIT("Memory access failure on die %x\n", die);
        status |= INPHI_ERROR;
        goto exit;
    }
    
    cfg = SPICA_MCU_INBPIF_CFG0__READ(die);
    cfg = SPICA_MCU_INBPIF_CFG0__CNTL__SET(cfg, 0x81);
    cfg = SPICA_MCU_INBPIF_CFG0__PRIORITY__SET(cfg, 0x3);
    SPICA_MCU_INBPIF_CFG0__WRITE(die, cfg);

    //setup the controller, do NOT change the order of these accesses
    cfg = SPICA_MCU_INBPIF_CFG1__READ(die);
    cfg = SPICA_MCU_INBPIF_CFG1__RDENA__SET(cfg, 0);
    cfg = SPICA_MCU_INBPIF_CFG1__STRIDE__SET(cfg, 4); //32b at a time
    SPICA_MCU_INBPIF_CFG1__WRITE(die, cfg);

    SPICA_MCU_INBPIF_ADDR0__WRITE(die, addr & 0xffff);
    SPICA_MCU_INBPIF_ADDR1__WRITE(die, (addr >> 16) & 0xffff);
    
    // Turn on burst mode in case the end user supports it
    SPICA_MCU_MDIO_CFG__WRITE(die, 1);
    
    for(i = 0; i < num_words; ++i)
    {
        //while(SPICA_MCU_INBPIF_RSTATUS1__RD_PENDING__READ(die))
        //    continue;
    
        //INPHI_NOTE("%08x\n", buffer[i]);
        SPICA_MCU_INBPIF_WDATA0__WRITE(die, (uint16_t)buffer[i]);
        SPICA_MCU_INBPIF_WDATA0__WRITE(die, (uint16_t)(buffer[i]>>16));
        if(status) goto exit;
    }
    

exit:
    // Disable burst mode after the download has finished
    SPICA_MCU_MDIO_CFG__WRITE(die, 0);

    SPICA_UNLOCK(die);

    return status;
}

// Write to the memory through the inbound PIF interface
inphi_status_t spica_mcu_pif_write_bcast(
    uint32_t die,
    uint32_t addr,
    const uint32_t* buffer,
    uint32_t num_words)
{
    inphi_status_t status = INPHI_OK;
    uint16_t cfg = 0;
    uint16_t i;

    SPICA_LOCK(die);

    cfg = 0;
    cfg = SPICA_MCU_INBPIF_CFG0__CNTL__SET(cfg, 0x81);
    cfg = SPICA_MCU_INBPIF_CFG0__PRIORITY__SET(cfg, 0x3);
    SPICA_MCU_INBPIF_CFG0__WRITE(die, cfg);

    //setup the controller, do NOT change the order of these accesses
    cfg = 0;
    cfg = SPICA_MCU_INBPIF_CFG1__RDENA__SET(cfg, 0);
    cfg = SPICA_MCU_INBPIF_CFG1__STRIDE__SET(cfg, 4); //32b at a time
    SPICA_MCU_INBPIF_CFG1__WRITE(die, cfg);

    SPICA_MCU_INBPIF_ADDR0__WRITE(die, addr & 0xffff);
    SPICA_MCU_INBPIF_ADDR1__WRITE(die, (addr >> 16) & 0xffff);
    
    // Turn on burst mode in case the end user supports it
    SPICA_MCU_MDIO_CFG__WRITE(die, 1);
    
    for(i = 0; i < num_words; ++i)
    {
        SPICA_MCU_INBPIF_WDATA0__WRITE(die, (uint16_t)buffer[i]);
        SPICA_MCU_INBPIF_WDATA0__WRITE(die, (uint16_t)(buffer[i]>>16));
    }
    
    // Disable burst mode after the download has finished
    SPICA_MCU_MDIO_CFG__WRITE(die, 0);

    SPICA_UNLOCK(die);

    return status;
}

#if defined(INPHI_HAS_DIRECT_DOWNLOAD)
//include the app image, will not be compiled in without the proper defines

/* Program the app fw directly from the API
 */
inphi_status_t spica_mcu_direct_download_image_impl(
    uint32_t        die,
    const uint32_t* image,
    uint32_t        image_length,
    bool            verify,
    inphi_status_t (*pif_write)(uint32_t, uint32_t, const uint32_t*, uint32_t))
{
    uint32_t offset = 0;
    inphi_status_t status = INPHI_OK;
    
    SPICA_LOCK(die);

    // Ensure everything is reset to a known state on each F/W download.
    // The "hard" reset in from the pin and "soft" reset from the MMD08_PMA_CONTROL 
    // register are logically "ORed" together so the MMD08 reset should be the 
    // equivalent to toggling the reset pin.
    SPICA_MMD08_PMA_CONTROL__WRITE(die, 0x8000);
    INPHI_MDELAY(1);

    // hit the runstall to stall the MCU when programming the f/w
    // this will get reset when using reset_into_mode
    SPICA_MCU_GEN_CFG__WRITE(die, 0x1001);

    // Clear the FIRMWARE version when downloading
    // so we can verify the app code restarts properly.
    SPICA_MCU_FIRMWARE_REV0_OVL__WRITE(die, 0);
    SPICA_MCU_FIRMWARE_REV1_OVL__WRITE(die, 0);

    // If we're currently in application mode then
    // make sure we clear the FW_MODE register so that
    // we don't hit a race condition when we restart
    // the firmware.
    SPICA_MCU_FW_MODE__WRITE(die, 0xACDD);

    // Zero initialize the IRAM and DRAM memories
    // to ensure ECC bits are properly initialized
    SPICA_MCU_DRAM_INIT_CFG__WRITE(die, 0x1fff);
    SPICA_MCU_IRAM_INIT_CFG__WRITE(die, 0x8000);
    // IRAM/DRAM memory will be initialized on a 0 to 1 transition 
    SPICA_MCU_GEN_CFG__INIT_IRAM__WRITE(die, 0);
    SPICA_MCU_GEN_CFG__INIT_DRAM__WRITE(die, 0);
    SPICA_MCU_GEN_CFG__INIT_IRAM__WRITE(die, 1);
    SPICA_MCU_GEN_CFG__INIT_DRAM__WRITE(die, 1);

    // Wait for the init operation to finish
    INPHI_MDELAY(2);

    SPICA_UNLOCK(die);

    //step through every block in the image...
    while(offset < image_length)
    {
        //...grabbing the block header...

        //addr in spica mem where the block needs to go
        uint32_t block_addr = image[offset++];
        //block size in 32b words
        uint32_t num_32b_words = image[offset++];
        
        if(num_32b_words == 0)
        {
            INPHI_NOTE("\n");
            INPHI_CRIT("Malformed image. offset=%u num_words=%u\n", offset, num_32b_words);
            status |= INPHI_ERROR;
            goto exit;
        }

        //memory_set requires length in number of 32b words (num of indexes) instead of in bytes
        status |= pif_write(die, block_addr, image+offset, num_32b_words);
        if(status != INPHI_OK) goto exit;

        // verify the block if requested to do so...
        if (verify)
        {
            for(uint32_t i = 0; i < num_32b_words; i+=1)
            {
                uint32_t data[1] = {0};
                uint32_t addr = block_addr + (i*4);
                spica_mcu_pif_read(die, addr, data, 1);
                
                if(data[0] != image[offset + i])
                {
                    INPHI_NOTE("Data at address %x does not match (programmed=%x, read=%x)!\n", addr, image[offset+i], data[0]);
                    status = INPHI_ERROR;
                    goto exit;
                }
            }
        }

        offset += num_32b_words;
    }

exit:

    return status;
}

// Program the app fw directly from the API without an EEPROM
inphi_status_t spica_mcu_direct_download_image(
    uint32_t die,
    const uint32_t* image,
    uint32_t image_length,
    bool verify)
{
    return spica_mcu_direct_download_image_impl(die, image, image_length, verify, spica_mcu_pif_write);
}

// Program the app fw directly from the API without an EEPROM via broadcast
inphi_status_t spica_mcu_direct_download_image_bcast(
    uint32_t die,
    inphi_status_t (*get_firmware)(const uint32_t** ptr, uint32_t* length))
{
    const uint32_t* image_ptr = NULL;
    uint32_t        image_len = 0;

    inphi_status_t status = get_firmware(&image_ptr, &image_len);
    status |= spica_mcu_direct_download_image_impl(die, image_ptr, image_len, false, spica_mcu_pif_write_bcast);

    return status;
}

// This is a wrapper method for testing broadcasting a particular
// firmware image to multiple IPs.
inphi_status_t spica_mcu_direct_download_image_bcast_buffer(
    uint32_t die,
    const uint32_t* image_ptr,
    uint32_t length)
{
    return spica_mcu_direct_download_image_impl(die, image_ptr, length, false, spica_mcu_pif_write_bcast);
}

#if defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW == 1)
// This is a wrapper method, mostly for python testing to broadcast
// the inlined f/w image to multiple ASICs
inphi_status_t spica_mcu_direct_download_image_bcast_inline(uint32_t die)
{
    return spica_mcu_direct_download_image_bcast(die, spica_mcu_get_inline_firmware);
}
#endif //defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW == 1)

#if 0

// Wrapper for the Verify f/w image method
inphi_status_t spica_mcu_verify_image_wrapper(
    uint32_t        die)
{
    inphi_status_t status = INPHI_OK;
    const uint32_t* ptr = NULL;
    uint32_t length = 0;

    // Get the inlined f/w image
    status |= spica_mcu_get_inline_firmware(&ptr, &length);

    // Verify the image against its CRC-32 checksums
    status |= spica_mcu_verify_image(die, ptr, length);

    return status;
}

// Verify the f/w image
inphi_status_t spica_mcu_verify_image(
    uint32_t        die,
    const uint32_t* image,
    uint32_t        image_length)
{
    uint32_t offset = 0;
    inphi_status_t status = INPHI_OK;
    uint32_t iram_crc = 0;
    uint32_t dram_crc = 0;
    bool     iram_only;

    SPICA_LOCK(die);
    
    // Verify the f/w is still runstalled before verifying
    if(1 != SPICA_MCU_GEN_CFG__RUNSTALL__READ(die))
    {
        INPHI_NOTE("Firmware not stalled, verifying the IRAM image only\n");
        iram_only = true;
    }   
    else
    {
        INPHI_NOTE("Firmware stalled, verifying both the IRAM/DRAM images\n");
        iram_only = false;
    }   
 
    //...grabbing the block header...

    //addr in spica mem where the block needs to go
    uint32_t block_addr = image[offset++];
    //block size in bytes
    uint32_t num_bytes = image[offset++]*4;
    
    //pull out the IRAM/DRAM CRC-32 values
    if ((block_addr == 0x5ffa0000) && (num_bytes == 8)) 
    {
        iram_crc = image[2];
        dram_crc = image[3];
    }

    if(num_bytes % 4 != 0)
    {
        INPHI_NOTE("\n");
        INPHI_CRIT("Malformed image. offset=%u num_bytes=%u\n", offset, num_bytes);
        status |= INPHI_ERROR;
        goto exit;
    }

    // Verify the programmed image using the HW CRC-32 engine  
    uint32_t ram_addr[2]     = {SPICA_MCU_IRAM_BASE_ADDR, SPICA_MCU_DRAM_BASE_ADDR};
    uint16_t ram_size[2]     = {SPICA_MCU_IRAM_SIZE, SPICA_MCU_DRAM_SIZE};
    uint32_t expected_crc[2] = {iram_crc, dram_crc};
    uint32_t calc_crc;

    for (uint8_t ram = 0; ram < 2; ram++)
    {
        // The memory verify should take about 200us at 156.25MHz:
        //   clk_period        = 1/156.25MHz
        //   memory_size       = 0x8000 32b words
        //   duration in usecs = clk_period * memory_size * (1000*1000)
        //                     = 209.7152us
        // As a precaution the guard will be 1ms
        int guard = 1000;

        // bust out of loop after IRAM verified if neccessary...
        if ((iram_only == true) && (ram == 1))
        {
            continue;
        }

        // enable the CRC-32 engine 
        SPICA_MCU_CHKSUM_CFG__WRITE(die, 0x0001);
        // define the IRAM/DRAM start address
        SPICA_MCU_CHKSUM_ADDR_CFG1__WRITE(die, (uint16_t)(ram_addr[ram] >> 16));
        SPICA_MCU_CHKSUM_ADDR_CFG0__WRITE(die, (uint16_t)ram_addr[ram]);
        // number of IRAM/DRAM locations 
        SPICA_MCU_CHKSUM_CNT_CFG__WRITE(die, ram_size[ram]);
        // start the CRC_32 engine
        SPICA_MCU_CHKSUM_CFG__WRITE(die, 0x8001);
        // wait for it to complete
        while (SPICA_MCU_CHKSUM_STATUS__READ(die) == 0 && (guard > 0))
        {
            INPHI_UDELAY(1);
            guard -= 1;
        }
        if(guard <= 0)
        {
            INPHI_CRIT("Timed out verifying the CRC on the IRAM/DRAM\n");
            status |= INPHI_ERROR;
        }

        // get the results
        calc_crc  = SPICA_MCU_CHKSUM_RESULT_STATUS0__READ(die);
        calc_crc |= (SPICA_MCU_CHKSUM_RESULT_STATUS1__READ(die) << 16);

        if (calc_crc != expected_crc[ram])
        {
            INPHI_CRIT("\nERROR: %s CRC-32 calculation NOT successful, expected = 0x%08x, calculated = 0x%08x\n", 
                        (ram ==0) ? "IRAM" : "DRAM", expected_crc[ram], calc_crc);
            status = INPHI_ERROR;
        }
        else
        {
            INPHI_NOTE("\nPASS: %s CRC-32 calculation successful, expected = 0x%08x, calculated = 0x%08x\n", 
                        (ram == 0) ? "IRAM" : "DRAM", expected_crc[ram], calc_crc);       
        }       
    }
    INPHI_NOTE(" - Done!\n");

exit:

    return status;
}
#endif

// Get the inlined f/w version number
uint32_t spica_mcu_get_inline_firmware_version(void)
{
#if defined(SPICA_INPHI_HAS_INLINE_APP_FW)
    return SPICA_APP_VERSION_NUMBER;
#else
    return 0;
#endif
}

#if defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW == 1)

/* Provide access to the inlined MCU firmware */
inphi_status_t spica_mcu_get_inline_firmware(
    const uint32_t** ptr, 
    uint32_t* length)
{
    inphi_status_t status = INPHI_OK;

    *ptr = spica_app_fw_image;
    *length = spica_app_fw_image_length;

    return status;
}

// Download the inlined firmware image */
inphi_status_t spica_mcu_download_firmware(
    uint32_t die, 
    bool verify)
{
    inphi_status_t status = INPHI_OK;

    const uint32_t* ptr = NULL;
    uint32_t length = 0;

    SPICA_LOCK(die);

    // Get the inlined f/w image
    status |= spica_mcu_get_inline_firmware(&ptr, &length);

    // Download the image
    if(status == INPHI_OK)
    {
        status |= spica_mcu_direct_download_image(die, ptr, length, verify);

        // Switch to the application bank
        SPICA_MCU_GEN_CFG__STATVECTOR_SEL__RMW(die, 0x1);

        // Reset the MCU
        SPICA_MCU_RESET__PROCRST__RMW(die, 0x1);

        // Now bring it out of runstall
        SPICA_MCU_GEN_CFG__RUNSTALL__RMW(die, 0x0);

        // Finally wait for it to jump into application mode
        status |= spica_mcu_block_application_mode(die, 2000);
    }

    SPICA_UNLOCK(die);

    return status;
}
#endif // defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW == 1)

#if defined(INPHI_HAS_INLINE_BOOTLOADER_FW) && (INPHI_HAS_INLINE_BOOTLOADER_FW == 1)

/* Provide access to the inlined MCU Bootlader */
inphi_status_t spica_mcu_get_inline_bootloader(
    const uint32_t** ptr,
    uint32_t* length)
{
    inphi_status_t status = INPHI_OK;

    *ptr = spica_bootloader_image;
    *length = spica_bootloader_image_length;

    if((*ptr == NULL) || (*length == 0))
        status = INPHI_ERROR;
 
    return status;
}

// Download the inlined bootloader image */
inphi_status_t spica_mcu_download_bootloader(
    uint32_t die,
    bool verify)
{
    inphi_status_t status = INPHI_OK;

    const uint32_t* ptr = NULL;
    uint32_t length = 0;

    SPICA_LOCK(die);

    // Get the inlined bootloader image
    status |= spica_mcu_get_inline_bootloader(&ptr, &length);

    uint32_t num_dies = spica_package_get_num_dies(die);

    //lock both dies
    for(uint32_t d = 0; d < num_dies; d++)
    {
        uint32_t pdie = spica_package_get_base_die(die) + d;
        status |= spica_lock(pdie);
    }

    if(status == INPHI_OK)
    {
        //Download the bootloader on all dies before running any MCU
        for(uint32_t d = 0; d < num_dies; d++)
        {
            uint32_t pdie = spica_package_get_base_die(die) + d;

            // Download the bootloader image
            status |= spica_mcu_direct_download_image(pdie, ptr, length, verify);
        }

        for(uint32_t d = 0; d < num_dies; d++)
        {
            uint32_t pdie = spica_package_get_base_die(die) + d;

            // If the download was ok then start the application image up.
            if(status == INPHI_OK)
            {
                INPHI_NOTE("Starting App Code on die %x\n", pdie);

                // Switch to the application bank
                SPICA_MCU_GEN_CFG__STATVECTOR_SEL__RMW(pdie, 0x1);

                // Reset the MCU
                SPICA_MCU_RESET__PROCRST__RMW(pdie, 0x1);

                // Now bring it out of runstall
                SPICA_MCU_GEN_CFG__RUNSTALL__RMW(pdie, 0x0);

                // Finally wait for it to jump into application mode
                status |= spica_mcu_block_application_mode(pdie, 2000);
            }
        }
    }

    SPICA_UNLOCK(die);
    INPHI_NOTE("Done!\n");

    return status;
}
#endif //defined(INPHI_HAS_INLINE_BOOTLOADER_FW) && (INPHI_HAS_INLINE_BOOTLOADER_FW == 1)

#endif // defined(INPHI_HAS_DIRECT_DOWNLOAD)

// Download the firmware image from a file
inphi_status_t spica_mcu_download_firmware_from_file(
    uint32_t    die, 
    const char* path, 
    bool        verify)
{
    inphi_status_t status = INPHI_OK;

#if defined(INPHI_HAS_FILESYSTEM) && (INPHI_HAS_FILESYSTEM == 1)
    SPICA_LOCK(die);
    
    FILE* handle = fopen(path, "rt");
    if(handle == NULL)
    {
        INPHI_CRIT("Failed accessing the firmware [%s] to download to the module\n", path);
        return INPHI_ERROR;
    }
    
    char buffer[256];

    uint32_t num_dies = spica_package_get_num_dies(die);

    //lock both dies
    for(uint32_t d = 0; d < num_dies; d++)
    {
        uint32_t pdie = spica_package_get_base_die(die) + d;        
        status |= spica_lock(pdie);
    }
    if(status) goto exit;

    for(uint32_t d = 0; d < num_dies; d++)
    {
    
        uint32_t pdie = spica_package_get_base_die(die) + d;

        // Make sure we rewind the file pointer when programming multiple dies.
        rewind(handle);
        
        // Ensure everything is reset to a known state on each F/W download.
        // The "hard" reset in from the pin and "soft" reset from the MMD08_PMA_CONTROL 
        // register are logically "ORed" together so the MMD08 reset should be the 
        // equivalent to toggling the reset pin.
        SPICA_MMD08_PMA_CONTROL__WRITE(pdie, 0x8000);
        INPHI_MDELAY(1);

        // hit the runstall to stall the MCU when programming the f/w
        // this will get reset when using reset_into_mode
        SPICA_MCU_GEN_CFG__RUNSTALL__RMW(pdie, 1);

        // Clear the FIRMWARE version when downloading
        // so we can verify the app code restarts properly.
        SPICA_MCU_FIRMWARE_REV0_OVL__WRITE(pdie, 0);
        SPICA_MCU_FIRMWARE_REV1_OVL__WRITE(pdie, 0);

        // If we're currently in application mode then
        // make sure we clear the FW_MODE register so that
        // we don't hit a race condition when we restart
        // the firmware.
        SPICA_MCU_FW_MODE__WRITE(pdie, 0xACDD);

        // Zero initialize the IRAM and DRAM memories
        // to ensure ECC bits are properly initialized
        SPICA_MCU_DRAM_INIT_CFG__WRITE(pdie, 0x1fff);
        SPICA_MCU_IRAM_INIT_CFG__WRITE(pdie, 0x8000);
        // IRAM/DRAM memory will be initialized on a 0 to 1 transition
        SPICA_MCU_GEN_CFG__INIT_IRAM__WRITE(pdie, 0);
        SPICA_MCU_GEN_CFG__INIT_DRAM__WRITE(pdie, 0);
        SPICA_MCU_GEN_CFG__INIT_IRAM__WRITE(pdie, 1);
        SPICA_MCU_GEN_CFG__INIT_DRAM__WRITE(pdie, 1);

        // Wait for the init operation to finish
        INPHI_MDELAY(2);
        
        if (verify)
        {
            INPHI_NOTE("Writing FW image directly to die %x (with verify)\n", pdie);
        }
        else
        {
            INPHI_NOTE("Writing FW image directly to die %x (without verify)\n", pdie);
        }
        
        uint32_t block_addr = 0;
        uint32_t block_offset = 0;
        
        // Parse through the image file reading it a chunk at a time
        // and programming the firmware to the target.
        while(status == INPHI_OK && 0 == feof(handle))
        {
            uint32_t block_data[32];
            uint32_t verif_data[32];
            int      block_index = 0;

            // Read head to try to construct a bigger block
            // of data to program.
            for(int i = 0; i < 32; i++)
            {
                // read a line of data
                if(NULL == fgets(buffer, 255, handle))
                {
                    break;
                }
                
                // Skip any blank lines
                if(strlen(buffer) == 0)
                {
                    continue;
                }
                
                if(buffer[0] == '#' || buffer[0] == '/')
                {
                    continue;
                }
                
                if(buffer[0] == '@')
                {
                    if(block_index > 0)
                    {
                        // INPHI_NOTE("WR die:0x%08x, addr:0x%08x, num32:%d\n", pdie, block_addr + block_offset, block_index);
                        status |= spica_mcu_pif_write(pdie, block_addr + block_offset, block_data, block_index);
                        
                        // verify the block if requested to do so...
                        if (verify)
                        {
                            status |= spica_mcu_pif_read(pdie, block_addr + block_offset, verif_data, block_index);
                            for(int j = 0; j < block_index; j+=1)
                            {
                                if(verif_data[j] != block_data[j])
                                {
                                    INPHI_NOTE("Data at die 0x%08x address 0x%08x does not match (programmed=0x%08x, read=0x%08x)!\n", 
                                                    pdie, block_addr + block_offset, block_data[j], verif_data[j]);
                                    status = INPHI_ERROR;
                                    goto exit;
                                }
                            }
                        }
                        block_offset += (block_index * 4);
                    }
                    
                    block_index = 0;
                    
                    block_addr = strtoul(&buffer[1], NULL, 16);
                    
                    if(block_addr == 0)
                    {
                        INPHI_CRIT("Block address is zero. Something wrong with the input image\n");
                        status |= INPHI_ERROR;
                        goto exit;
                    }
                    
                    block_offset = 0;

                    break;
                }
                else
                {
                    // block_index++;
                    uint32_t word_to_write = strtoul(buffer, NULL, 16);
                    block_data[block_index++] = word_to_write;
                }
            }
            
            if(block_index > 0)
            {
                //INPHI_NOTE("Programming %d words at %x\n", block_index, block_addr + block_offset);
                status |= spica_mcu_pif_write(pdie, block_addr + block_offset, block_data, block_index);
                    
                // verify the block if requested to do so...
                if (verify)
                {
                    status |= spica_mcu_pif_read(pdie, block_addr + block_offset, verif_data, block_index);
                    for(int j = 0; j < block_index; j+=1)
                    {
                        if(verif_data[j] != block_data[j])
                        {
                            INPHI_NOTE("Data at die 0x%08x address 0x%08x does not match (programmed=0x%08x, read=0x%08x)!\n", 
                                            pdie, block_addr + block_offset, block_data[j], verif_data[j]);
                            status = INPHI_ERROR;
                            goto exit;
                        }
                    }
                }

                block_offset += (block_index * 4);
            }
        }
    }

    for(uint32_t d = 0; d < num_dies; d++)
    {
        uint32_t pdie = spica_package_get_base_die(die) + d;

        // If the download was ok then start the application image up.
        if(status == INPHI_OK)
        {
            INPHI_NOTE("Starting App Code on die %x\n", pdie);
            
            // Switch to the application bank
            SPICA_MCU_GEN_CFG__STATVECTOR_SEL__RMW(pdie, 0x1);

            // Reset the MCU
            SPICA_MCU_RESET__PROCRST__RMW(pdie, 0x1);

            // Now bring it out of runstall
            SPICA_MCU_GEN_CFG__RUNSTALL__RMW(pdie, 0x0);
            
            // Finally wait for it to jump into application mode
            status |= spica_mcu_block_application_mode(pdie, 2000);
        }
    }
    
exit:
    // Finally close the firmware handle
    fclose(handle);
    
    SPICA_UNLOCK(die);
    
    INPHI_NOTE(" - Done!\n");
#else
    (void)die;
    (void)path;
    (void)verify;
    INPHI_CRIT("INPHI_HAS_FILESYSTEM must be defined to use spica_mcu_download_firmware_from_file\n");
    status = INPHI_ERROR;
#endif // INPHI_HAS_FILESYSTEM

    return status;
}

inphi_status_t spica_mcu_ram_init(
    uint32_t die)
{
    inphi_status_t status = INPHI_OK;

    SPICA_LOCK(die);

    // Zero initialize the IRAM and DRAM memories
    // to ensure ECC bits are properly initialized
    SPICA_MCU_DRAM_INIT_CFG__WRITE(die, 0x1fff);
    SPICA_MCU_IRAM_INIT_CFG__WRITE(die, 0x8000);

    // IRAM/DRAM memory will be initialized on a 0 to 1 transition
    SPICA_MCU_GEN_CFG__INIT_IRAM__WRITE(die, 0);
    SPICA_MCU_GEN_CFG__INIT_DRAM__WRITE(die, 0);
    SPICA_MCU_GEN_CFG__INIT_IRAM__WRITE(die, 1);
    SPICA_MCU_GEN_CFG__INIT_DRAM__WRITE(die, 1);

    SPICA_UNLOCK(die);

    // Wait for the init operation to finish
    // The HW can write to the RAM on every MCU clock cycle so the initialization 
    // should take approx: (1/156000000) * 0x8000 ~= 210us
    INPHI_UDELAY(500);
    
    return status;
}

/**
 * Get the fw_info struct containing some important buffer addresses
 */
inphi_status_t spica_mcu_fw_info_query(
    uint32_t       die,
    spica_fw_info_t* fw_info)
{
    inphi_status_t status = INPHI_OK;
    uint32_t fw_info_sz = 0;
    uint32_t buf[sizeof(spica_fw_info_t)/sizeof(uint32_t)+1];

    //get the address of the 'fw_info' struct
    uint32_t fw_info_addr = 0x5ffc0000 | SPICA_MCU_SP3_FW_INFO__READ(die);
    if(fw_info_addr == 0x5ffc0000) {
        return INPHI_ERROR;
    }

    //get the size in bytes of the struct
    status |= spica_mcu_pif_read(die, fw_info_addr, &fw_info_sz, 1);
    if(status) return status;

    //if we don't have a large enough buf
    if(sizeof(buf) < fw_info_sz) {
        return INPHI_ERROR;
    }
    //if we have more members in our struct than the FW's
    // not including the length member in the FW's
    if(sizeof(spica_fw_info_t) < fw_info_sz-sizeof(uint32_t)) {
        return INPHI_ERROR;
    }

    //get the full fw_info_struct
    status |= spica_mcu_pif_read(die, fw_info_addr, buf, fw_info_sz/4);
    if(status) return status;

    fw_info->debug_buffer_address = buf[1];
    fw_info->info_buf_address = buf[2];

    return status;
}

inphi_status_t spica_mcu_reset_into_mode(
    uint32_t      die, 
    e_spica_fw_mode mode, 
    bool          wait_till_started)
{
    inphi_status_t status = INPHI_OK;
    int cnt = 10;
    
    uint32_t iram_cfg = SPICA_MCU_IRAM_INIT_CFG__READ(die);
    uint32_t dram_cfg = SPICA_MCU_DRAM_INIT_CFG__READ(die);
        
    SPICA_LOCK(die);
        
    // Stall the processor if it is running
    SPICA_MCU_GEN_CFG__RUNSTALL__RMW(die, 1);

    SPICA_MCU_IRAM_INIT_CFG__WRITE(die, 0);
    SPICA_MCU_DRAM_INIT_CFG__WRITE(die, 0);

    // // Make sure BOOT_CTRL is set properly
    // uint32_t boot_ctrl = SPICA_MCU_BOOT_CTRL__READ(die);
    // boot_ctrl = SPICA_MCU_BOOT_CTRL__FORCE_SELF_INIT__SET(boot_ctrl, 1);

    // // if(mode == SPICA_FW_MODE_BOOT_UPGRADE)
    // // {
    // //     boot_ctrl = SPICA_MCU_BOOT_CTRL__SELF_INIT__SET(boot_ctrl, 0);
    // // }

    // SPICA_MCU_BOOT_CTRL__WRITE(die, boot_ctrl);
    //  
    // // SPICA_MCU_GEN_CFG__INIT_IRAM__RMW(die, 0);
    // // SPICA_MCU_GEN_CFG__INIT_DRAM__RMW(die, 0);
    //     
    // SPICA_MCU_BOOTVER__WRITE(die, 0);
    // SPICA_MCU_FW_MODE__WRITE(die, 0);
        
    // Reset the MCU and wait for it to startup
    if(mode == SPICA_FW_MODE_APPLICATION)
    {
        SPICA_MCU_GEN_CFG__STATVECTOR_SEL__RMW(die, 1); // For the application code
    }
    else
    {
        SPICA_MCU_GEN_CFG__STATVECTOR_SEL__RMW(die, 0); 
    }
    
    SPICA_MCU_RESET__PROCRST__RMW(die, 1);    // Reset the MCU
    SPICA_MCU_GEN_CFG__RUNSTALL__RMW(die, 0); // Clear any runstall

    // Wait for the firmware to startup
    if(wait_till_started)
    {
        uint32_t data = SPICA_MCU_FW_MODE__READ(die);
        
        while ((data == 0) && (cnt > 0))
        {
            data = SPICA_MCU_FW_MODE__READ(die);
        
            cnt = cnt - 1;
            INPHI_MDELAY(500);
        }

        if (cnt == 0)
        {
            INPHI_CRIT("Timed-out waiting for firmware to start, die = %x, fw_mode = %x\n", die,data);
            status = INPHI_ERROR;
        }
    }
    
    SPICA_MCU_IRAM_INIT_CFG__WRITE(die, iram_cfg);
    SPICA_MCU_DRAM_INIT_CFG__WRITE(die, dram_cfg);

    SPICA_UNLOCK(die);

    return status;
}

inphi_status_t spica_mcu_reset_into_application(
    uint32_t die, 
    bool wait_till_started)
{
    return spica_mcu_reset_into_mode(die, SPICA_FW_MODE_APPLICATION, wait_till_started);
}

// Query the MCU status
inphi_status_t spica_mcu_status_query(
    uint32_t die, 
    spica_mcu_status_t* mcu_status)
{
    inphi_status_t status = INPHI_OK;
    
    // Query the firmware mode
    status |= spica_mcu_fw_mode_query(die, &mcu_status->fw_mode);
    mcu_status->fw_mode_str = spica_dbg_translate_fw_mode(mcu_status->fw_mode);
    
    // Capture any MDIO address errors
    mcu_status->mdio_addr_err = (SPICA_MCU_MDIO_AERR_STATUS1__READ(die) << 16) |
                                SPICA_MCU_MDIO_AERR_STATUS0__READ(die);
                             
    // Query the application version information
    mcu_status->app_version = (SPICA_MCU_FIRMWARE_REV1_OVL__READ(die) << 16) |
                               SPICA_MCU_FIRMWARE_REV0_OVL__READ(die);
    mcu_status->app_version_build    = SPICA_MCU_FIRMWARE_REV0_OVL__BUILD__READ(die);
    mcu_status->app_version_major    = SPICA_MCU_FIRMWARE_REV1_OVL__MAJOR__READ(die);
    mcu_status->app_version_minor    = SPICA_MCU_FIRMWARE_REV1_OVL__MINOR__READ(die);
    mcu_status->app_version_revision = SPICA_MCU_FIRMWARE_REV1_OVL__REVISION__READ(die);
    
    // Query the API version information (if it was programmed)
    mcu_status->api_version = (SPICA_MCU_API_INFO1_OVL__READ(die) << 16) |
                               SPICA_MCU_API_INFO0_OVL__READ(die);

    // If the API version was not populated yet then use the API defines.
    if(0 == mcu_status->api_version)
    {
        mcu_status->api_version = SPICA_MCU_API_INFO0_OVL__BUILD__SET(mcu_status->api_version, SPICA_API_VERSION_BUILD);
        SPICA_MCU_API_INFO0_OVL__BUILD__WRITE(die, mcu_status->api_version);

        uint16_t tmp;
        tmp = SPICA_MCU_API_INFO1_OVL__MAJOR__SET(0, SPICA_API_VERSION_MAJOR);
        tmp = SPICA_MCU_API_INFO1_OVL__MINOR__SET(tmp, SPICA_API_VERSION_MINOR);
        tmp = SPICA_MCU_API_INFO1_OVL__REVISION__SET(tmp, SPICA_API_VERSION_REVISION);
        SPICA_MCU_API_INFO1_OVL__WRITE(die, tmp);
        mcu_status->api_version |= (tmp << 16);
    }
    
    mcu_status->api_version_major    =  SPICA_MCU_API_INFO1_OVL__MAJOR__READ(die);
    mcu_status->api_version_minor    =  SPICA_MCU_API_INFO1_OVL__MINOR__READ(die);
    mcu_status->api_version_revision =  SPICA_MCU_API_INFO1_OVL__REVISION__READ(die);
    mcu_status->api_version_build    =  SPICA_MCU_API_INFO0_OVL__BUILD__READ(die);

    // Check the runstall bit
    mcu_status->runstall = SPICA_MCU_GEN_CFG__RUNSTALL__READ(die);
    
    // Query the loop counter spaced 1 second apart
    for(int i = 0; i < 2; i++)
    {
        mcu_status->loop_count[i] = SPICA_MCU_SP2_LOOP_COUNT__READ(die);
        INPHI_MDELAY(1000);
    }
    mcu_status->loop_delta = mcu_status->loop_count[1] - mcu_status->loop_count[0];
    if(mcu_status->loop_delta < 0) mcu_status->loop_delta = -mcu_status->loop_delta;

    // guard against div by 0
    if (mcu_status->loop_delta != 0)
    {
        mcu_status->loop_duration = (1000*1000)/mcu_status->loop_delta;
    }
    else
    {
        mcu_status->loop_duration = 0;
    }
    
    // Query the program counter
    status |= spica_mcu_pc_log_query(die, mcu_status->pc_trace, 10);
    
    return status;
}

// Dump the MCU status
inphi_status_t spica_mcu_status_query_print(
    uint32_t die)
{
    inphi_status_t status = INPHI_OK;
    
#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

    uint32_t num_dies = spica_package_get_num_dies(die);
    for(uint32_t i = 0; i < num_dies; i++)
    {
        spica_mcu_status_t mcu_status;
        uint32_t pdie = spica_package_get_base_die(die) + i;
        spica_mcu_status_query(pdie, &mcu_status);

        INPHI_NOTE("MCU Status (die=0x%x)\n"
                   "=========================\n"
                   "  Mode:          %s\n"
                   "  Runstall:      %s\n"
                   "  Application Version:\n"
                   "    %x = %d.%d.%d.%d\n"
                   "  API Version:\n"
                   "    %x = %d.%d.%d.%d\n"
                   "  MDIO Address Error:\n"
                   "    %x\n"
                   "  Loop count:\n",
                   pdie,
                   mcu_status.fw_mode_str,
                   mcu_status.runstall == true ? "Yes" : "No",
                   mcu_status.app_version,
                   mcu_status.app_version_major,
                   mcu_status.app_version_minor,
                   mcu_status.app_version_revision,
                   mcu_status.app_version_build,
                   mcu_status.api_version,
                   mcu_status.api_version_major,
                   mcu_status.api_version_minor,
                   mcu_status.api_version_revision,
                   mcu_status.api_version_build,
                   mcu_status.mdio_addr_err);
        
        // Display the loop counter
        for(int j = 0; j < 2; j++)
        {
            INPHI_NOTE("    %d\n", mcu_status.loop_count[j]);
        }
        if (mcu_status.loop_duration != 0)
        {
            INPHI_NOTE("  Loop duration: %dus\n", mcu_status.loop_duration);
        }
        else
        {
            INPHI_NOTE("  Loop duration: infinity\n");
        }
        INPHI_NOTE("  Number loops : %d\n", mcu_status.loop_delta);
        
        // Display the program counter
        INPHI_NOTE("  Program Counter:\n");
        for(int j = 0; j < 10; j++)
        {
            INPHI_NOTE("    0x%x\n", mcu_status.pc_trace[j]);
        }
        
        INPHI_NOTE("\n");
    }
#else
    (void)die;
    status = INPHI_ERROR;
#endif //(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    
    return status;
}

inphi_status_t spica_mcu_pc_log_query(
    uint32_t die,
    uint32_t* entries,
    uint32_t num_entries)
{
    inphi_status_t status = INPHI_OK;

    // Enable the program counter
    SPICA_MCU_GEN_CFG__PDEBUG_EN__RMW(die, 1);

    for(uint32_t i = 0; i < num_entries; i++)
    {
        uint16_t pc_lo = SPICA_MCU_PDEBUG_PC0__READ(die);
        uint16_t pc_hi = SPICA_MCU_PDEBUG_PC1__READ(die);

        *(entries + i) = ((uint32_t)pc_hi << 16) | (uint32_t)pc_lo;
    }
    return status;
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
inphi_status_t spica_mcu_pc_log_query_print(
    uint32_t die,
    uint32_t num_entries)
{
    inphi_status_t status = INPHI_OK;

    // Enable the program counter
    SPICA_MCU_GEN_CFG__PDEBUG_EN__RMW(die, 1);

    // Now dump the trace log
    INPHI_NOTE("MCU PC Trace:\n");
    INPHI_NOTE("=============\n");
    for(uint32_t i = 0; i < num_entries; i++)
    {
        uint16_t pc_lo = SPICA_MCU_PDEBUG_PC0__READ(die);
        uint16_t pc_hi = SPICA_MCU_PDEBUG_PC1__READ(die);

        INPHI_NOTE("  %x\n", ((pc_hi << 16) | pc_lo));
    }

    return status;
}

inphi_status_t spica_mcu_debug_log_query_print(
    uint32_t die)
{
    inphi_status_t status = INPHI_OK;

    char buff[SPICA_MCU_DEBUG_BUFFER_MAX_LENGTH];
    uint32_t buff_size = sizeof(buff)/sizeof(*buff);

    INPHI_MEMSET(buff, 0, sizeof(buff));

    status |= spica_mcu_debug_log_query(die, buff, buff_size);

    INPHI_NOTE("MCU Debug Log\n");
    INPHI_NOTE("=============\n");
    INPHI_NOTE("%s", buff);
    INPHI_NOTE("\n");

    return status;
}

/**
 * This method is used to dump the firmware trace log into a buffer,
 * for debug purposes.
 */
inphi_status_t spica_mcu_debug_log_query(
    uint32_t die,
    char* buff,
    uint32_t buff_size)
{
    inphi_status_t status = INPHI_OK;

    if((buff == NULL) || (buff_size < 1))
    {
        INPHI_CRIT("Input buffer is NULL\n");
        return INPHI_ERROR;
    }
    //in case we return an error, always set buff
    buff[0] = 0;

    // Figure out the address of the debug log
    uint32_t addr_fw_info = (SPICA_MCU_DRAM_ADDR_MSW<<16) | SPICA_MCU_SPARE3__READ(die);
    if((addr_fw_info&0xffff) == 0)
    {
        INPHI_CRIT("FW info spare has been erased, not fetching the log\n");
        return INPHI_ERROR;
    }

    //tmp buffer to use, can make the "page" bigger but 16 is fine for now
    uint32_t buffer[16];
    const uint32_t buffer_len = sizeof(buffer)/sizeof(*buffer);

    // Get the length and debug buffer address
    status |= spica_mcu_pif_read(die, addr_fw_info, buffer, 3);
    //length is unused
    //uint32_t length = buffer[0];
    //address of the debug buffer structure
    uint32_t addr_debug_buffer = buffer[1];

    //INPHI_NOTE("MCU Debug Log\n");
    //INPHI_NOTE("=============\n");
    //INPHI_NOTE("addr.fwinfo: %x\n", addr_fw_info);
    //INPHI_NOTE("addr.log:    %x\n", addr_debug_buffer);

    if(((addr_debug_buffer>>16) != SPICA_MCU_DRAM_ADDR_MSW) || ((addr_debug_buffer&0xffff) == 0))
    {
        INPHI_CRIT("MCU debug log addr not valid!\n");
        return INPHI_ERROR;
    }

    // Read the debug buffer header
    status |= spica_mcu_pif_read(die, addr_debug_buffer, buffer, 3);
    /*uint32_t dbg_buffer_filter = buffer[0];*/
    uint32_t dbg_buffer_offset = buffer[1];
    uint32_t dbg_buffer_length = buffer[2];

    //INPHI_NOTE("dbg_buffer_length = %d, (input)buff_size = %d\n", dbg_buffer_length, buff_size);
    //INPHI_NOTE("offset:      %d\n", dbg_buffer_offset);
    //INPHI_NOTE("length:      %d\n", dbg_buffer_length);
    //INPHI_NOTE("filter:      %x\n", dbg_buffer_filter);
    //INPHI_NOTE("log:\n\n");

    if((dbg_buffer_length < 1) || (dbg_buffer_offset >= dbg_buffer_length))
    {
        INPHI_CRIT("MCU debug log length (%d) or offset (%d) invalid!\n", dbg_buffer_length, dbg_buffer_offset);
        return INPHI_ERROR;
    }

    //skip the 3 words we just read, to get the start of the actual string data
    addr_debug_buffer += 3*4;
    //add the offset so we start at the "beginning" of the log (in time)
    uint32_t str_addr = addr_debug_buffer + dbg_buffer_offset;
    //the end address that we'll work our way up to
    uint32_t end_addr = addr_debug_buffer + dbg_buffer_length;

    //set the length we'll read to the min
    uint32_t total_bytes = dbg_buffer_length;
    //is our buffer too small?
    if (dbg_buffer_length > buff_size-1)
    {
        INPHI_WARN("buff_size-1 (%d) < total MCU debug buf len of %d\n", buff_size-1, dbg_buffer_length);
        total_bytes = buff_size-1;

        //start not at the dbg_buffer_offset, but at the earliest (in time) we can grab with this buffer
        str_addr -= total_bytes;
        //handle underflow
        if(str_addr < addr_debug_buffer) {
            str_addr += dbg_buffer_length;
        }
    }
    //otherwise we have enough room

    //keep track of the total bytes read
    uint32_t i = 0;
    //the length only changes between FW builds, sometimes we'll shrink it to save room
    while(i < total_bytes)
    {
        //it's OK if this reads past the end of the actual debug buffer, we'll ignore those bytes
        status |= spica_mcu_pif_read(die, str_addr, buffer, buffer_len);
        if(status) break; //don't return so we always set the last ch in buff
        //go through the contents of the buffer one-by-one
        for(uint32_t j=0; j<buffer_len; j++)
        {
            uint32_t data = buffer[j];
            //we start at the buffer offset, go to the end, and then wrap around
            //we still need to check our totals every character we pop
            char str[4] = {data>>0, data>>8, data>>16, data>>24};
            bool exit_fn = false;
            for(char *c=str; c<str+4; c++)
            {
                if(i >= total_bytes)
                {
                    //totally done, break!
                    exit_fn = true;
                    break;
                }
                if(str_addr >= end_addr)
                {
                    //wrap to the beginning now
                    str_addr = addr_debug_buffer;
                    exit_fn = true;
                    break;
                }
                // ignore unprintable characters
                if( (*c == '\t') || (*c == '\n') || (*c == '\r')
                    || (*c >= 0x20 && *c <= 0x7e) // normal
                  )
                {
                    *buff++ = *c;
                }
                //add another byte
                str_addr++;
                i++;
            }
            if(exit_fn) break;
        }
    }

    //regardless of all else, make sure we form a valid C string!
    // note that above we check to see if buff is big enough + 1 for the null terminator
    // so we should always have enough room at this point
    *buff = 0;

    //INPHI_NOTE("\n");

    return status;
}

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

inphi_status_t spica_mcu_debug_log_filter_set(uint32_t die, uint32_t filter)
{
    inphi_status_t status = INPHI_OK;
    uint32_t data[3];
    uint32_t addr_debug_buffer = 0;

    SPICA_LOCK(die);

    // Figure out the address of the debug log
    uint32_t addr_fw_info = 0x5ff80000 | SPICA_MCU_SP3_FW_INFO__READ(die);
    if((addr_fw_info & 0xffff) == 0)
    {
        INPHI_CRIT("FW info spare has been erased, can't set the log fitler");
        status |= INPHI_ERROR;
        goto exit;
    }

    // Get the length and debug buffer address
    status |= spica_mcu_pif_read(die, addr_fw_info, data, 3);
    if(INPHI_OK != status)
    {
        goto exit;
    }

    addr_debug_buffer = data[1];

    // Update the log filter
    data[0] = filter;
    status |= spica_mcu_pif_write(die, addr_debug_buffer, data, 1);

exit:
    SPICA_UNLOCK(die);

    return status;
}

#if defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)
/**
 * This method provides an example of programming the EEPROM on
 * the target ASIC.
 */
inphi_status_t spica_mcu_download_eeprom_from_file(
    uint32_t die,
    const char* path)
{
    inphi_status_t status = INPHI_OK;

#if defined(INPHI_HAS_FILESYSTEM) && (INPHI_HAS_FILESYSTEM==1)
    e_spica_spi_clk_div clkdiv = SPICA_SPI_CLK_DIV_64;

    FILE* stream; // The file stream being accessed.

    // A buffer used to read each line from the EEPROM file
    char buffer[256];

    // The size of each EEPROM block to read from the input file.
    const uint32_t block_size = 32;
    uint32_t eeprom_block[32];

    // Indexes of where we are in the source image and where we are
    // in the EEPROM.
    uint32_t block_index = 0;
    uint32_t eeprom_address = 0;

    stream = fopen(path, "rt");
    if(stream == NULL)
    {
        INPHI_CRIT("Input file %s not found\n", path);
        return INPHI_ERROR;
    }

    // Alway use lowest die
    die = spica_package_get_base_die(die);

    uint32_t num_dies = spica_package_get_num_dies(die);

    for(uint32_t i = 0; i < num_dies; i++)
    {
        uint16_t data;
        uint32_t pdie = spica_package_get_base_die(die) + i;

        // Force the MCU(s) to stall
        data = SPICA_MCU_GEN_CFG__READ(pdie);
        data = SPICA_MCU_GEN_CFG__RUNSTALL__SET(data, 1);
        SPICA_MCU_GEN_CFG__WRITE(pdie, data);

        // Reset the SPI block on the die(s)
        data = SPICA_MCU_RESET__READ(pdie);
        data = SPICA_MCU_RESET__SPIRST__SET(data, 1);
        SPICA_MCU_RESET__WRITE(pdie, data);

        // if clk overide is true then ensure divider is minimum 5
        data = SPICA_MCU_BOOT_CTRL__READ(pdie);
        if ((SPICA_MCU_BOOT_CTRL__SPI_CLK_DIVIDER_OVERRIDE__GET(data) == 1) &&
           (SPICA_MCU_BOOT_CTRL__SPI_CLK_DIVIDER__GET(data) < 5))
        {
            data = SPICA_MCU_BOOT_CTRL__SPI_CLK_DIVIDER__SET(data, 5);
            SPICA_MCU_BOOT_CTRL__WRITE(pdie, data);
        }
    }

    while(status == INPHI_OK && 0 == feof(stream))
    {
        if(NULL != fgets(buffer, 255, stream))
        {
            if(buffer[0] == '#' || buffer[0] == '/')
            {
                continue;
            }

            uint32_t data = strtoul(buffer, NULL, 16);
            data = INPHI_NTOHL(data);

#if defined(INPHI_I2C_NEEDS_BYTES_REVERSED)
            data = INPHI_NTOHL(data);
#endif

            eeprom_block[block_index] = data;
            block_index++;

            if(block_index == block_size)
            {
#if 0 //don't print so much
                uint32_t i;
                INPHI_NOTE("\nProgramming EEPROM block at offset %d", eeprom_address);
                for(i = 0; i < block_size; i++)
                {
                    if ((i % 8) == 0) { INPHI_NOTE("\n"); }
                    INPHI_NOTE("  0x%08x", eeprom_block[i]);
                }
#endif
                INPHI_NOTE(".");

                status |= spica_spi_write_data_block(die, eeprom_address, eeprom_block, block_size, clkdiv);
                //status |= spica_mcu_eeprom_set(die, eeprom_address, eeprom_block, block_size);

                eeprom_address += (block_size*4);

                block_index = 0;
            }
        }
    }

    //write the leftovers
    if(status == INPHI_OK && block_index > 0)
    {
#if 0 //don't print so much
        uint32_t i;
        INPHI_NOTE("\nProgramming EEPROM block at offset %d", eeprom_address);
        for(i = 0; i < block_index; i++)
        {
            if ((i % 8) == 0) { INPHI_NOTE("\n"); }
            INPHI_NOTE("  0x%08x", eeprom_block[i]);
        }
#endif
        INPHI_NOTE(".");

        status |= spica_spi_write_data_block(die, eeprom_address, eeprom_block, block_size, clkdiv);
        //status |= spica_mcu_eeprom_set(die, eeprom_address, eeprom_block, block_index);
    }

    INPHI_NOTE("\n");

    fclose(stream);

    for(uint32_t i = 0; i < num_dies; i++)
    {
        uint16_t data;
        uint32_t pdie = spica_package_get_base_die(die) + i;

        // Reset the SPI block on the die(s)
        data = SPICA_MCU_RESET__READ(pdie);
        data = SPICA_MCU_RESET__SPIRST__SET(data, 1);
        SPICA_MCU_RESET__WRITE(pdie, data);

        // Unstall the the MCU(s)
        data = SPICA_MCU_GEN_CFG__READ(pdie);
        data = SPICA_MCU_GEN_CFG__RUNSTALL__SET(data, 0);
        SPICA_MCU_GEN_CFG__WRITE(pdie, data);
    }

#ifdef INCL_OPTIONAL_MSGIF
    // // Now verify the EEPROM image that was just programmed
    // uint32_t calc = 0;
    // uint32_t exp  = 0;
    // status |= spica_mcu_eeprom_verify_with_checksum(die, 0, &calc, &exp);
    // INPHI_NOTE("  Calculated checksum: %x\n", calc);
    // INPHI_NOTE("  Expected checksum:   %x\n", exp);
#endif
#else
    INPHI_CRIT("INPHI_HAS_FILESYSTEM must be defined to use spica_mcu_download_eeprom_from_file\n");
    status = INPHI_ERROR;
#endif // INPHI_HAS_FILESYSTEM

    return status;
}

/* Read the metadata from the EEPROM image */
inphi_status_t spica_mcu_eeprom_read_metadata(
    uint32_t     die,
    char*        metadata,
    uint32_t     metadata_size) /*in bytes*/
{
    uint32_t i = 0;
    inphi_status_t status = INPHI_OK;
    uint32_t temp[6] = {0};
    e_spica_spi_clk_div clkdiv = SPICA_SPI_CLK_DIV_64;

    uint32_t iram_info;
    uint32_t dram_info;
    uint32_t num_words_iram;
    uint32_t num_words_dram;
    uint32_t start_of_metadata;

    // Alway use lowest die
    die = spica_package_get_base_die(die);

    uint32_t num_dies = spica_package_get_num_dies(die);

    for(i = 0; i < num_dies; i++)
    {
        uint16_t data;
        uint32_t pdie = spica_package_get_base_die(die) + i;

        // Reset the SPI block on the die(s)
        data = SPICA_MCU_RESET__READ(pdie);
        data = SPICA_MCU_RESET__SPIRST__SET(data, 1);
        SPICA_MCU_RESET__WRITE(pdie, data);

        // if clk overide is true then ensure divider is minimum 5
        data = SPICA_MCU_BOOT_CTRL__READ(pdie);
        if ((SPICA_MCU_BOOT_CTRL__SPI_CLK_DIVIDER_OVERRIDE__GET(data) == 1) &&
           (SPICA_MCU_BOOT_CTRL__SPI_CLK_DIVIDER__GET(data) < 5))
        {
            data = SPICA_MCU_BOOT_CTRL__SPI_CLK_DIVIDER__SET(data, 5);
            SPICA_MCU_BOOT_CTRL__WRITE(pdie, data);
        }
    }

    for(i = 0; i < metadata_size; i++)
    {
        metadata[i] = 0;
    }

    SPICA_LOCK(die);

    if(metadata_size < 252)
    {
        INPHI_CRIT("Please allocate at least 252 bytes to retrieve the EEPROM metadata information\n");
        status |= INPHI_ERROR;
        goto done;
    }

    // Don't read further than the end of the metadata buffer
    metadata_size = 252;

    // Read the first word. If it is 0xffffffff then the EEPROM
    // is not programmed
    status = spica_spi_read_data_block(die, 0, &temp[0], 1, clkdiv);
    if(status != INPHI_OK)
    {
        INPHI_CRIT("Failed reading EEPROM header");
        goto done;
    }

    if(temp[0] >= 0xfffffffful)
    {
        INPHI_CRIT("EEPROM is empty");
        goto done;
    }

    // Read the EEPROM header
    status |= spica_spi_read_data_block(die, 4, &temp[1], 5, clkdiv);
    if (status != INPHI_OK)
    {
        INPHI_CRIT("Failed reading EEPROM header");
        goto done;
    }

    //uint32_t fw_version = temp[0];
    iram_info  = temp[4];
    dram_info  = temp[5];

    num_words_iram = iram_info & 0xffff;
    num_words_dram = dram_info & 0xffff;

    // The metadata resides in EEPROM after the header + IRAM + DRAM + CRC
    //uint32_t num_block_headers = (num_blocks_iram + num_blocks_dram) * 2;

    // The metadata resides in EEPROM after the header + IDRAM + DRAM + CRC
    start_of_metadata =
                (6*4 +                                    // EEPROM header
                8 +
                (4 * (num_words_iram + num_words_dram + 1)));

    // Make sure we don't exceed the bounds of the EEPROM
    if(start_of_metadata >= ((2L << 20) - 256))
    {
        INPHI_CRIT("EEPROM metadata could not be extracted from the EEPROM\n");
        status |= INPHI_ERROR;
        goto done;
    }

    status |= spica_spi_read_data_block(die, start_of_metadata, (uint32_t*)metadata, metadata_size/4, clkdiv);

    // Convert any new lines.
    for(i = 0; i < metadata_size; i++)
    {
        if((metadata[i] == '\\') &&
           // Make sure we don't exceed the bounds of the array
           ((i+1) < ((metadata_size)-1)) &&
           (metadata[i+1] == 'n'))
        {
            metadata[i] = ' ';
            metadata[i+1] = '\n';
        }
    }

    metadata[metadata_size-1] = 0;

    if(INPHI_OK != status)
    {
        INPHI_CRIT("Failed reading the EEPROM metadata\n");
        goto done;
    }

done:
    for(i = 0; i < num_dies; i++)
    {
        uint16_t data;
        uint32_t pdie = spica_package_get_base_die(die) + i;

        // Reset the SPI block on the die(s)
        data = SPICA_MCU_RESET__READ(pdie);
        data = SPICA_MCU_RESET__SPIRST__SET(data, 1);
        SPICA_MCU_RESET__WRITE(pdie, data);
    }

    SPICA_UNLOCK(die);

    return status;
}

#endif //  defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)

/*
 * This method is called to fetch a buffer address from the MCU
 */
inphi_status_t spica_mcu_get_buffer_address(
    uint32_t  die,
    uint32_t  buffer_type,
    uint32_t* buffer_address,
    uint16_t* buff_32b_size)
{
    inphi_status_t status = INPHI_OK;
    uint8_t req_id;
    msg_hdr_t resp;
    uint32_t payload[3];
    uint32_t rc;

    req_id = spica_mcu_msg_id();
    
    /* Construct the message to send to the MCU */
    payload[0] = spica_mcu_msg_type(SPICA_MCU_MSG_GET_BUFFER_REQUEST, req_id, 2);
    payload[1] = buffer_type;

    SPICA_LOCK(die);

    /* Send the request to the MCU */
    status |= spica_msg_send(die, payload, 1, &payload[1], 1);
    if(status != INPHI_OK)
    {
        goto done;
    }
    
    /* Wait for the response from the MCU */
    status |= spica_msg_recv(die, payload, 3, &resp, &rc, SPICA_MCU_MBOX_MAX_TIMEOUT);

    /* Make sure the ID field in the response matches the request */
    if((rc != true) || (status != INPHI_OK) || (req_id != resp.get.msg_id))
    {
        status |= INPHI_ERROR;
        goto done;
    }

    /* Make sure we got the correct response back from the MCU */
    if(resp.get.msg_type != SPICA_MCU_MSG_GET_BUFFER_RESPONSE)
    {
        status |= INPHI_ERROR;
        goto done;
    }

    /* DEBUG BRAD: For some reason this message doesn't have a return code */
    *buffer_address = payload[0];
    *buff_32b_size  = payload[1]/4; /* number of 32b words */ 

done:
    SPICA_UNLOCK(die);

    return status;
}

/** @file msg.c
 ****************************************************************************
 *
 * @brief
 *     This module contains the implementation of the messaging interface 
 *     to the embedded MCU.
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

#if !defined(INPHI_REMOVE_MESSAGING)

#if defined(INPHI_HAS_FILESYSTEM)
#include <string.h> // String methods for progrmaming ucode from disk
#include <stdio.h>  // File IO methods for programming ucode from disk
#endif // INPHI_HAS_FILESYSTEM

// Swap to account for re-ordering problem when reading the EEPROM via the MCU
#define SPICA_ORDER_MCU(x) ((((x)>>24)&0xff) | (((x)>>8)&0xff00) | (((x)&0xff00)<<8) | (((x)&0xff)<<24))

/**
 * This method is used to manage msg_id, avoid using global variable.
 *
 * @param get_msg_id    [I] if get_msg_id is true, return message ID
 *                          Otherwise will clear the message ID
 * @return An 8 bit message ID or 0 if get_msg_id is false
 *
 * @since 1.11
 *
 * @private
 */
static uint8_t spica_mcu_msg_id_management(bool get_msg_id){
    static uint8_t msg_id = 0;
    if(get_msg_id){
        return msg_id++;
    } else {
        msg_id = 0;
    }
    return 0;
}

/**
 * This method is used to clear message ID
 *
 * @since 1.11
 */
inphi_status_t spica_mcu_msg_id_reset(void){
    spica_mcu_msg_id_management(false);
    return INPHI_OK;
}

/**
 * This method is used to assign a unique ID to
 * messages being sent to the MCU. This number will
 * roll around at 255 which isn't critical since there
 * cannot be that many messages in flight at once.
 *
 * @return An 8 bit message ID
 *
 * @since 0.1
 *
 * @private
 */
uint8_t spica_mcu_msg_id(void)
{
    return spica_mcu_msg_id_management(true);
}

/**
 * This method is used to build a control message word to
 * to send to the MCU. This control message word will be
 * stuffed into offset 0 of the message buffer.
 *
 * @param msg_type     [I] - The message type, see e_spica_mcu_msg_type
 * @param msg_id       [I] - The message's unique ID
 * @param msg_len      [I] - The length of the message, number of 32 bit words
 *
 * @return A 32 bit control message word
 *
 * @since 0.1
 *
 * @private
 */
uint32_t spica_mcu_msg_type(
    uint32_t msg_type,
    uint8_t  msg_id,
    uint8_t  msg_len)
{
    uint32_t msg_ctrl;

    msg_ctrl = ((uint32_t)msg_id << 24) | ((uint32_t)msg_type << 16) | (uint32_t)msg_len;

    return msg_ctrl;
}

/**
 * Waits for a Rx mailbox to have at least one free space or Tx mailbox to have at least one entry
 *
 * @param die          [I] - The ASIC die to target
 * @param is_rx        [I] - The mailbox type Rx=true, Tx=false
 * @param timeout      [I] - The maximum time to wait for the mailbox to become available
 *                           (units are milli-secs)
 *
 * @return INPHI_OK on mbox cleared, INPHI_ERROR if timed out
 *
 * @since 0.1
 *
 * @private
 */
inphi_status_t spica_mcu_wait_mbox(
        uint32_t die,
        bool is_rx,
        uint32_t timeout)
{
    inphi_status_t status = INPHI_OK;
    int16_t mbox_avail = 0;
    uint16_t data = 0;
    int32_t max_iterations;

    max_iterations = timeout / SPICA_MCU_MBOX_ITER_DELAY;
    if (max_iterations == 0) max_iterations = 1;

    /* Wait for space in the mailbox queue to the MCU. */
    while(mbox_avail <= 0)
    {
        data = SPICA_MCU_MBOX_STATUS__READ(die);
        if(status != INPHI_OK)
        {
            return status;
        }

        if (is_rx)
        {
            mbox_avail = SPICA_MCU_RXMBOX_MAX_ENTRIES - SPICA_MCU_MBOX_STATUS__RXCNT__GET(data);
        }
        else
        {
            mbox_avail = SPICA_MCU_MBOX_STATUS__TXCNT__GET(data);
        }

        if(mbox_avail <= 0)
        {
            INPHI_MDELAY(SPICA_MCU_MBOX_ITER_DELAY);
            max_iterations -= 1;

            // INPHI_NOTE(".");
            if(max_iterations <= 0)
            {
                INPHI_CRIT("Timed out waiting for MCU to clear mailbox\n");
                return INPHI_ERROR;
            }
        }
    }

    return status;
}

/**
 * If the API failed to send a message to the MCU for some reason
 * the clear the RX mailbox for next time.
 */
void spica_clear_rx_mbox(
    uint32_t die)
{
    uint16_t rxmbox_avail;
    uint32_t i;
    int32_t timeout = 1000;

    // If there are any unprocessed entries in the TX mailbox
    // we need to discard them to avoid synchronization issues.
    do
    {
        rxmbox_avail = SPICA_MCU_MBOX_STATUS__RXCNT__READ(die);

        for(i = 0; i < rxmbox_avail; i++)
        {
            SPICA_RXMBOX_RXMAILBOX__READ(die);
        }

        timeout -= 1;
    }
    while((timeout > 0) && ((rxmbox_avail = SPICA_MCU_MBOX_STATUS__RXCNT__READ(die)) > 0));
}

/**
 * This method is called to send a message to the MCU
 * for processing.
 *
 * @param die          [I] - The ASIC die to target
 * @param header       [I] - The header of the message
 * @param header_size  [I] - The size of the header (units are 32 bit words).
 * @param payload      [I] - The payload of the message.
 * @param payload_size [I] - The length of the payload (units are 32 bit words).
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @private
 */
inphi_status_t spica_msg_send(
    uint32_t       die,
    const uint32_t *header,
    uint16_t       header_size,
    const uint32_t *payload,
    uint16_t       payload_size)
{
    inphi_status_t status = INPHI_OK;
    e_spica_fw_mode mode;
    uint32_t i;
    uint16_t txmbox_avail = 0;

    /* First ensure the MCU is in a mode where it an receive messages */
    status |= spica_mcu_fw_mode_query(die, &mode);
    if(status || (mode == SPICA_FW_MODE_UNKNOWN))
    {
        INPHI_CRIT("Not in application or upgrade mode, MCU can't handle messages\n");
        return INPHI_ERROR;
    }

    /* If there are any unprocessed entries in the TX mailbox
     * we need to discard them to avoid synchronization issues.
     */
    int32_t timeout = 1000;
    do
    {
        txmbox_avail = SPICA_MCU_MBOX_STATUS__TXCNT__READ(die);

        for(i = 0; i < txmbox_avail; i++)
        {
            SPICA_TXMBOX_TXMAILBOX__READ(die);
        }

        timeout -= 1;
    }
    while((timeout > 0) && ((txmbox_avail = SPICA_MCU_MBOX_STATUS__TXCNT__READ(die)) > 0));
    if(timeout <= 0)
    {
        INPHI_CRIT("Timeout clearing TX MBOX\n");
        return INPHI_ERROR;
    }

    SPICA_LOCK(die);

    i = 0;
    while(i < header_size)
    {

        /* Wait for space in the mailbox queue to the MCU. */
        status |= spica_mcu_wait_mbox(die, true, SPICA_MCU_MBOX_MAX_TIMEOUT);
        if(status) break;

        /* Write to the RXMBOX. The format of this request is dependent on the
         * setting in MCU.MDIO register. */
        // printf("value %x\n", header[i]);
        SPICA_RXMBOX_RXMAILBOX__WRITE(die, (uint16_t)(header[i] >> 16));
        SPICA_RXMBOX_RXMAILBOX__WRITE(die, (uint16_t)header[i]);

        i += 1;
    }
    if(status != INPHI_OK)
    {
        INPHI_CRIT("Could not send header\n");
        spica_clear_rx_mbox(die);
        SPICA_UNLOCK(die);
        return status;
    }

    i = 0;
    while(i < payload_size)
    {
        /* Wait for space in the mailbox queue to the MCU. */
        status |= spica_mcu_wait_mbox(die, true, SPICA_MCU_MBOX_MAX_TIMEOUT);
        if(status) break;

        /* Write to the RXMBOX. The format of this request is dependent on the
         * setting in MCU.MDIO register. */
        //printf("value %x\n", payload[i]);
        SPICA_RXMBOX_RXMAILBOX__WRITE(die, (uint16_t)(payload[i] >> 16));
        SPICA_RXMBOX_RXMAILBOX__WRITE(die, (uint16_t)payload[i]);

        i += 1;
    }
    if(status != INPHI_OK)
    {
        INPHI_CRIT("Could not send payload\n");
        spica_clear_rx_mbox(die);
    }

    SPICA_UNLOCK(die);

    return status;
}

/**
 * This method is called to receive a message from the MCU
 * for processing.
 *
 * @param die            [I] - The ASIC die to target
 * @param payload_buffer [I] - The buffer to store the response to.
 * @param max_payload    [I] - The maximum payload the buffer can accept (num 32bit words)
 * @param resp_hdr       [O] - The message response header

 * @param resp_rc        [O] - The return code from the MCU; true: good, false: bad
 * @param timeout        [I] - The max time to wait for a response from the MCU.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @private
 */
inphi_status_t spica_msg_recv(
    uint32_t   die,
    uint32_t*  payload_buffer,
    uint16_t   max_payload,
    msg_hdr_t* resp_hdr,
    uint32_t*  resp_rc,
    uint32_t   timeout)
{
    inphi_status_t status = INPHI_OK;
    uint32_t txmbox_avail = 0;
    uint32_t payload_index = 0;

    uint16_t data;
    int32_t  length;
    bool has_rc = true;

    //assume the worst
    *resp_rc = 0;

    //wait for a message
    status |= spica_mcu_wait_mbox(die, false, timeout);
    if(status)
    {
        INPHI_CRIT("Failed waiting for MCU Tx mailbox\n");
        return status;
    }

    //read the header
    data = SPICA_TXMBOX_TXMAILBOX__READ(die);
    resp_hdr->raw  = (uint32_t) data << 16;
    data = SPICA_TXMBOX_TXMAILBOX__READ(die);
    resp_hdr->raw |= (uint32_t) data;

    length = resp_hdr->get.msg_len;

    /* Exclude the header */
    length -= 1;

    /* These messages unfortunately have no return code */
    if(((resp_hdr->get.msg_type == SPICA_MCU_MSG_GET_BUFFER_RESPONSE) ||
        (resp_hdr->get.msg_type == SPICA_MCU_MSG_ERROR_RESPONSE)      ||
        /* This message should have a return code, see bug 2l-78 */
        (resp_hdr->get.msg_type == SPICA_MCU_MSG_RELEASE_BUFFER_RESPONSE)))
    {
        has_rc = false;
        *resp_rc = 1;
    }

    /* Now pop the actual data off the queue */
    while(length > 0)
    {
        /* Wait for data to be available */
        status |= spica_mcu_wait_mbox(die, false, SPICA_MCU_MBOX_MAX_TIMEOUT);
        if(status) break;
    
        if(0 == payload_index && has_rc)
        {
            data = SPICA_TXMBOX_TXMAILBOX__READ(die);
            *resp_rc = (uint32_t)data << 16;
            data = SPICA_TXMBOX_TXMAILBOX__READ(die);
            *resp_rc |= (uint32_t)data;
            has_rc = false;
        }
        else
        {
            if(payload_index < max_payload)
            {
                data = SPICA_TXMBOX_TXMAILBOX__READ(die);
                payload_buffer[payload_index] = (uint32_t)data << 16;
                data = SPICA_TXMBOX_TXMAILBOX__READ(die);
                payload_buffer[payload_index] |= (uint32_t)data;
            }
            else
            {
                INPHI_CRIT("Payload is bigger than the allocated response buffer, "
                        "payload size = %d, max = %d\n", payload_index, max_payload );
                return INPHI_ERROR;
            }
            payload_index++;
        }
    
        txmbox_avail -= 1;
        length -= 1;
    }
    if(status != INPHI_OK)
    {
        INPHI_CRIT("Failed receiving message from MCU\n");
    }
    
    return status;
}

/**
 * Struct representing the msg2 buffer
 *
 * @since 0.1
 *
 * @private
 */
typedef struct {
    /** Address of this struct in the FW */
    uint32_t self_addr;
    /** length of the buffer */
    uint32_t length;
    /** write index */
    uint32_t wr_idx;
    /** read index */
    uint32_t rd_idx;
    /** Buffer address in FW */
    uint32_t buffer_addr;
} spica_msg2_buffer;

/**
 * Enum specifying the buffer index. One buffer per direction
 *
 * @since 0.1
 *
 * @private
 */
typedef enum {
    SPICA_MSG2_BUF_API2FW = 0,
    SPICA_MSG2_BUF_FW2API,
    SPICA_MSG2_BUF_END, //must be last
} e_spica_msg2_buffer_idx;

/**
 * Enum for using the lock turns
 *
 * @since 0.1
 *
 * @private
 */
typedef enum {
    SPICA_LOCK_TURN_FW = 0,
    SPICA_LOCK_TURN_API = 1
} e_lock_turn;

/**
 * Queries the buffer info from the FW.
 *
 * Doesn't need the FW to be running at the time of the query, but since the address is set by the app
 * FW, it had to run at some point.
 *
 * @param msg_buffer [IO] - one index per e_spica_msg2_buffer_idx, one for API2FW and another for FW2API
 *                          msg_buffer must be zero-initialized prior to the first time this method is called.
 *
 * @since 0.1
 *
 * @private
 */
static inphi_status_t spica_msg2_buffer_query(
        uint32_t die,
        spica_msg2_buffer msg_buffer[2])
{
    inphi_status_t status = INPHI_OK;
    uint32_t pif_buf[3];
    uint32_t pif_buf_len = sizeof(pif_buf)/sizeof(*pif_buf);

    if(!msg_buffer) return INPHI_ERROR;

    uint32_t buff_addr = msg_buffer[0].self_addr;
    if(((buff_addr>>16) != SPICA_MCU_DRAM_ADDR_MSW) || ((buff_addr&0xffff) == 0)) {
        // Grab the buffer address
        buff_addr = (SPICA_MCU_DRAM_ADDR_MSW<<16) | SPICA_MCU_SP12_MSG2_BUFF_ADDR__READ(die);
        if(buff_addr == (SPICA_MCU_DRAM_ADDR_MSW<<16)) return INPHI_ERROR;
    }

    //get the first index API2FW
    status |= spica_mcu_pif_read(die, buff_addr, pif_buf, pif_buf_len);
    msg_buffer[SPICA_MSG2_BUF_API2FW].self_addr = buff_addr;
    msg_buffer[SPICA_MSG2_BUF_API2FW].length = pif_buf[0];
    msg_buffer[SPICA_MSG2_BUF_API2FW].wr_idx = pif_buf[1];
    msg_buffer[SPICA_MSG2_BUF_API2FW].rd_idx = pif_buf[2];
    msg_buffer[SPICA_MSG2_BUF_API2FW].buffer_addr = buff_addr+3*sizeof(uint32_t);
    uint32_t msg_buffer_size = (3+msg_buffer[SPICA_MSG2_BUF_API2FW].length)*sizeof(uint32_t);

    //get the second index FW2API
    status |= spica_mcu_pif_read(die, buff_addr+msg_buffer_size, pif_buf, pif_buf_len);
    msg_buffer[SPICA_MSG2_BUF_FW2API].self_addr = buff_addr+msg_buffer_size;
    msg_buffer[SPICA_MSG2_BUF_FW2API].length = pif_buf[0];
    msg_buffer[SPICA_MSG2_BUF_FW2API].wr_idx = pif_buf[1];
    msg_buffer[SPICA_MSG2_BUF_FW2API].rd_idx = pif_buf[2];
    msg_buffer[SPICA_MSG2_BUF_FW2API].buffer_addr = buff_addr+msg_buffer_size+3*sizeof(uint32_t);

#if 0 // debug
    INPHI_NOTE("msg_buffer\n");
    INPHI_NOTE("  msg_buffer[API_2_FW].self_addr   = 0x%08x\n", msg_buffer[SPICA_MSG2_BUF_API2FW].self_addr);  
    INPHI_NOTE("  msg_buffer[API_2_FW].length      = %d\n", msg_buffer[SPICA_MSG2_BUF_API2FW].length);
    INPHI_NOTE("  msg_buffer[API_2_FW].wr_idx      = %d\n", msg_buffer[SPICA_MSG2_BUF_API2FW].wr_idx);
    INPHI_NOTE("  msg_buffer[API_2_FW].rd_idx      = %d\n", msg_buffer[SPICA_MSG2_BUF_API2FW].rd_idx);
    INPHI_NOTE("  msg_buffer[API_2_FW].buffer_addr = 0x%08x\n", msg_buffer[SPICA_MSG2_BUF_API2FW].buffer_addr);
    INPHI_NOTE("  msg_buffer[FW_2_API].self_addr   = 0x%08x\n", msg_buffer[SPICA_MSG2_BUF_FW2API].self_addr);
    INPHI_NOTE("  msg_buffer[FW_2_API].length      = %d\n", msg_buffer[SPICA_MSG2_BUF_FW2API].length);
    INPHI_NOTE("  msg_buffer[FW_2_API].wr_idx      = %d\n", msg_buffer[SPICA_MSG2_BUF_FW2API].wr_idx);
    INPHI_NOTE("  msg_buffer[FW_2_API].rd_idx      = %d\n", msg_buffer[SPICA_MSG2_BUF_FW2API].rd_idx);
    INPHI_NOTE("  msg_buffer[FW_2_API].buffer_addr = 0x%08x\n", msg_buffer[SPICA_MSG2_BUF_FW2API].buffer_addr);
#endif

    return status;
}

// mutex is done based on Peterson's algo:
// https://en.wikipedia.org/wiki/Peterson%27s_algorithm

/**
 * Lock the mcu messaging buffer for use by the API
 *
 * @return true if locked, false otherwise
 *
 * @since 0.1
 *
 * @private
 */
static bool spica_msg2_lock(uint32_t die)
{
    uint16_t data = SPICA_MCU_SYNC_API__READ(die);
    //check for bugs!
    if(SPICA_MCU_SYNC_API__MSG__GET(data)) {
        INPHI_CRIT("Called msg_lock when already locked\n");
    }
    //we want lock
    data = SPICA_MCU_SYNC_API__MSG__SET(data, 1);
    SPICA_MCU_SYNC_API__WRITE(die, data);
    //our turn next
    SPICA_MCU_SYNC_MSG_TURN__WRITE(die, SPICA_LOCK_TURN_API);
    //mem barrier?
    //if the other guy is accessing we need to wait
    if(SPICA_MCU_SYNC_FW__MSG__READ(die) && (SPICA_MCU_SYNC_MSG_TURN__TURN__READ(die) == SPICA_LOCK_TURN_API)) {
        //reset our flag
        SPICA_MCU_SYNC_API__MSG__RMW(die, 0);
        return false;
    }
    //we have it!
    return true;
}

/**
 * Unlock the mcu messaging buffer for use by the API
 *
 * @since 0.1
 *
 * @private
 */
static void spica_msg2_unlock(uint32_t die)
{
    uint16_t data = SPICA_MCU_SYNC_API__READ(die);
    //check for bugs!
    if(!SPICA_MCU_SYNC_API__MSG__GET(data)) {
        INPHI_CRIT("Called msg_unlock w/out first being locked\n");
    }
    //reset our flag
    data = SPICA_MCU_SYNC_API__MSG__SET(data, 0);
    SPICA_MCU_SYNC_API__WRITE(die, data);
}

/**
 * Test whether we're locked or not.
 *
 * @since 0.1
 *
 * @private
 */
static bool spica_msg2_is_locked(uint32_t die)
{
    uint16_t data = SPICA_MCU_SYNC_API__READ(die);
    //check for bugs!
    return SPICA_MCU_SYNC_API__MSG__GET(data);
}

/**
 * Calc simple 32bit checksum on src data
 *
 * @param cksum [I] - previous cksum, use 0 for the first one
 *
 * @return new checksum value
 *
 * @since 0.1
 *
 * @private
 */
static uint32_t spica_msg2_checksum(const void *src, uint32_t size, uint32_t cksum)
{
    const uint8_t *s_ptr = (const uint8_t*)src;
    const uint8_t *end = s_ptr + size;

    for(; s_ptr < end; s_ptr++) {
        cksum = (cksum >> 1) | (cksum << (32 - 1));
        cksum += *s_ptr;
    }
    return cksum;
}

/**
 * Calc the number of available read or write entries
 *
 * Does not update msg_buffers from the FW, just uses the cached data.
 *
 * @since 0.1
 *
 * @private
 */
static uint32_t spica_msg2_num_avail(spica_msg2_buffer msg_buffers[2], e_spica_msg2_buffer_idx idx)
{
    spica_msg2_buffer *buf = &msg_buffers[idx];
    if(SPICA_MSG2_BUF_FW2API == idx) {
        //num entries we have to read
        return buf->wr_idx - buf->rd_idx;
    }
    else {
        //num entries we have to write
        return buf->length - buf->wr_idx;
    }
}

/**
 * Wait for a message to be in the desired buffer, and lock the buffer once it's ready for access.
 *
 * @param msg_length [I] - Expected length of the message to be pulled, use 2 for any valid message
 *                         Expected length of the message to be pushed, use the exact message length (header+payload+checksum)
 *
 * @since 0.1
 *
 * @private
 */
static inphi_status_t spica_msg2_wait_and_lock(
        uint32_t die,
        spica_msg2_buffer msg_buffers[2],
        e_spica_msg2_buffer_idx idx,
        uint32_t msg_length,
        uint32_t timeout)
{
    inphi_status_t status = INPHI_OK;
    int32_t max_iterations;

    max_iterations = timeout / SPICA_MCU_MBOX_ITER_DELAY;
    if (max_iterations == 0) max_iterations = 1;

    // grab the buffers without locking, which is fine as we're in read-only mode
    status |= spica_msg2_buffer_query(die, msg_buffers);
    if(status) return status;

    // INPHI_NOTE("msg buf avail = %d, msg len = %d\n", spica_msg2_num_avail(msg_buffers, idx),  msg_length);

    // wait until we have room
    while(spica_msg2_num_avail(msg_buffers, idx) < msg_length)
    {
        max_iterations -= 1;
        if(max_iterations <= 0)
        {
            INPHI_CRIT("Timed out waiting for MCU to clear/fill msg2 buffer\n");
            return INPHI_ERROR;
        }
        INPHI_MDELAY(SPICA_MCU_MBOX_ITER_DELAY);

        //update the buffer info
        status |= spica_msg2_buffer_query(die, msg_buffers);
        if(status) return INPHI_ERROR;
    }

    //now we know for sure that a message is waiting and it's the right length
    // lock the queue which will allow us to pull the whole message out and erase the queue
    while(!spica_msg2_lock(die)) {
        max_iterations -= 1;
        if(max_iterations <= 0)
        {
            INPHI_CRIT("Timed out waiting for MCU to release msg2 lock\n");
            return INPHI_ERROR;
        }
        INPHI_MDELAY(SPICA_MCU_MBOX_ITER_DELAY);
    }

    // ********** START MSG2 LOCKED *************

    //after lock we must update the buffer info one last time in case the FW modified it
    status |= spica_msg2_buffer_query(die, msg_buffers);
    if(status) spica_msg2_unlock(die);

    return status;
}

/**
 * Sends a message to the MCU via the new PIF interface. This can only be done when running application FW.
 *
 * @param die            [I] - The ASIC die to target
 * @param msg_id         [I] - Unique message id to use
 * @param msg_type       [I] - Message type
 * @param payload        [I] - The payload of the message without header/checksum info
 *                             Use NULL if not sending a payload.
 * @param payload_length [I] - The num of elements in the payload (units are 32 bit words).
 *                             Use 0 if not sending a payload.
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @private
 */
static inphi_status_t spica_msg2_push_message(
    uint32_t die,
    uint8_t msg_id,
    e_spica_mcu_msg_type msg_type,
    const uint32_t *payload,
    uint16_t payload_length)
{
    inphi_status_t status = INPHI_OK;
    e_spica_fw_mode mode;
    uint32_t msg_length = payload_length + 2;
    //not necessary to initialize, but it makes it easier for static analysis
    uint32_t pif_buf[3] = {0};

    uint32_t cksum = 0;
    uint32_t wr_addr;

    // Fixme: Add support for NULL payloads
    if(payload == NULL){
        INPHI_CRIT("NULL payload is not supported yet.");
        return INPHI_ERROR;
    }

    //make sure that the payload/payload_length is valid
    if((payload == NULL) && (payload_length != 0)) {
        INPHI_CRIT("Invalid payload length when payload is NULL\n");
        return INPHI_ERROR;
    }

    /* First ensure the MCU is in a mode where it an receive messages */
    status |= spica_mcu_fw_mode_query(die, &mode);
    if(status || (mode != SPICA_FW_MODE_APPLICATION))
    {
        INPHI_CRIT("Not in application mode, MCU can't handle PIF messages\n");
        return INPHI_ERROR;
    }

    SPICA_LOCK(die);

    //read the buffers, which can be done without locking it
    spica_msg2_buffer msg_buffers[2];
    INPHI_MEMSET(msg_buffers, 0, sizeof(msg_buffers));

    //we don't need to capture the buffer; wait_and_lock will do that for us
    /*status |= spica_msg2_buffer_query(die, msg_buffers);*/
    /*if(status) goto exit;*/

    //wait for the API2FW buffer to clear
    status |= spica_msg2_wait_and_lock(die, msg_buffers, SPICA_MSG2_BUF_API2FW, msg_length, SPICA_MCU_MBOX_MAX_TIMEOUT);
    if(status) goto exit;

    // ********** START MSG2 LOCKED *************

    /* If there are any unprocessed entries in the TX mailbox
     * we need to discard them to avoid synchronization issues.
     */
    //blow away the wr_idx/rd_idx on the FW2API buffer, effectively erasing the TX buffer
    pif_buf[0] = 0;
    pif_buf[1] = 0;
    status |= spica_mcu_pif_write(die, msg_buffers[SPICA_MSG2_BUF_FW2API].self_addr+sizeof(uint32_t), pif_buf, 2);
    if(status) goto msg2_unlock;

    //generate the header
    pif_buf[0] = spica_mcu_msg_type(msg_type, msg_id, msg_length);
    //start the checksum
    cksum = spica_msg2_checksum(pif_buf, sizeof(*pif_buf), 0);

    //write header
    wr_addr = msg_buffers[SPICA_MSG2_BUF_API2FW].buffer_addr + msg_buffers[SPICA_MSG2_BUF_API2FW].wr_idx*sizeof(uint32_t);
    status |= spica_mcu_pif_write(die, wr_addr, pif_buf, 1);
    if(status) goto msg2_unlock;
    wr_addr += sizeof(uint32_t);
    //write data
    status |= spica_mcu_pif_write(die, wr_addr, payload, payload_length);
    wr_addr += payload_length*sizeof(uint32_t);
    if(status) goto msg2_unlock;

    //calc checksum
    cksum = spica_msg2_checksum(payload, payload_length*sizeof(*payload), cksum);
    //write it
    status |= spica_mcu_pif_write(die, wr_addr, &cksum, 1);
    wr_addr += sizeof(uint32_t);
    (void)wr_addr;
    if(status) goto msg2_unlock;

    //update the wr_idx; 2 for header/cksum, then payload length
    pif_buf[0] = msg_buffers[SPICA_MSG2_BUF_API2FW].wr_idx+2+payload_length;
    status |= spica_mcu_pif_write(die, msg_buffers[SPICA_MSG2_BUF_API2FW].self_addr+sizeof(uint32_t), pif_buf, 1);

    // ********** END MSG2 LOCKED *************

    //unlock the buffer
msg2_unlock:
    spica_msg2_unlock(die);

exit:
    SPICA_UNLOCK(die);

    return status;
}

/**
 * Pulls a message header (not data) from the MCU via the new PIF interface.
 *
 * This can only be done when running application FW.
 *
 * @param die            [I] - The ASIC die to target
 * @param payload        [I] - The buffer to save the payload of the message to without header/checksum info.
 *                             Cannot be NULL.
 * @param max_payload_len [I] - The max num of 32b elements we can save in the payload.
 * @param timeout        [I] - Max amount of ms to wait for the FW, not very accurate.
 * @param msg_id         [O] - Unique message id of the Rx'd message
 * @param msg_type       [O] - Message type
 * @param msg_len        [O] - Length of the Rx'd payload without header/checksum
 *
 * @return INPHI_OK on success, INPHI_ERROR on failure.
 *
 * @since 0.1
 *
 * @private
 */
static inphi_status_t spica_msg2_pull_message(
    uint32_t die,
    uint32_t *payload,
    uint16_t max_payload_len,
    uint32_t timeout,
    uint8_t *msg_id,
    e_spica_mcu_msg_type *msg_type,
    uint16_t *msg_len)
{
    inphi_status_t status = INPHI_OK;
    e_spica_fw_mode mode;
    //initializing makes it easier for static analysis
    uint32_t pif_buf[3] = {0};

    *msg_id = 0;
    *msg_type = SPICA_MCU_MSG_ERROR_RESPONSE;
    *msg_len = 0;

    bool was_locked;
    uint32_t rd_addr;
    uint16_t total_len;
    uint32_t cksum = 0;

    /* First ensure the MCU is in a mode where it an receive messages */
    status |= spica_mcu_fw_mode_query(die, &mode);
    if(status || (mode != SPICA_FW_MODE_APPLICATION))
    {
        INPHI_CRIT("Not in application mode, MCU can't handle PIF messages\n");
        return INPHI_ERROR;
    }

    SPICA_LOCK(die);

    spica_msg2_buffer msg_buffers[2];
    INPHI_MEMSET(msg_buffers, 0, sizeof(msg_buffers));

    //if we're already locked then rememebr that and don't bother with lock/unlocking the buffer
    was_locked = spica_msg2_is_locked(die);
    if(!was_locked)
    {
        //wait for the FW2API buffer to have something in it
        //len=2 since that's the min message length we need (header+checksum)
        //msg_buffers will be updated by the wait_and_check method
        status |= spica_msg2_wait_and_lock(die, msg_buffers, SPICA_MSG2_BUF_FW2API, 2, timeout);
        //after this, all status checks must go to msg2_unlock
        if(status) goto exit;
    }
    else {
        //if we're already locked then it means this fn is running in a loop
        //check if there is a message, if not, then don't block
        status |= spica_msg2_buffer_query(die, msg_buffers);
        if(status) goto exit;

        if(spica_msg2_num_avail(msg_buffers, SPICA_MSG2_BUF_FW2API) == 0) {
            //once we have no more messages, reset the rd/wr_indexes
            goto exit;
        }
    }

    //get the header
    rd_addr = msg_buffers[SPICA_MSG2_BUF_FW2API].buffer_addr + msg_buffers[SPICA_MSG2_BUF_FW2API].rd_idx*sizeof(uint32_t);
    status |= spica_mcu_pif_read(die, rd_addr, pif_buf, 1);
    rd_addr += sizeof(uint32_t);
    if(status) goto msg2_unlock;

    *msg_id = (pif_buf[0]>>24) & 0xff;
    *msg_type = (e_spica_mcu_msg_type)((pif_buf[0]>>16) & 0xff);
    //including the header and cksum
    total_len = (pif_buf[0] & 0xffff);
    //not including header and cksum
    *msg_len = total_len -2;

    if(max_payload_len < *msg_len)
    {
        INPHI_CRIT("max_payload_len %d too small to hold msg_type %d msg_len %d\n", max_payload_len, *msg_type, *msg_len);
        status |= INPHI_ERROR;
        goto msg2_unlock;
    }

    //make sure we actually have enough entiries in the buffer to read
    if((total_len < 2) || (spica_msg2_num_avail(msg_buffers, SPICA_MSG2_BUF_FW2API) < total_len)) {
        INPHI_CRIT("partial msg2 of type %d\n", *msg_type);
        //all messages are invalid, need to blow them away
        status |= INPHI_ERROR;
        goto msg2_erase_and_unlock;
    }

    //start checksum
    cksum = spica_msg2_checksum(pif_buf, sizeof(pif_buf[0]), 0);

    //read the data
    status |= spica_mcu_pif_read(die, rd_addr, payload, *msg_len);
    rd_addr += *msg_len*sizeof(uint32_t);
    if(status) goto msg2_unlock;
    //calc checksum
    cksum = spica_msg2_checksum(payload, *msg_len*sizeof(*payload), cksum);

    //compare checksum
    status |= spica_mcu_pif_read(die, rd_addr, pif_buf, 1);
    rd_addr += sizeof(uint32_t);
    (void)rd_addr;
    if(status) goto msg2_unlock;
    if(cksum != pif_buf[0]) {
        INPHI_CRIT("msg_type %d calc cksum %x != read cksum %x\n", *msg_type, cksum, pif_buf[0]);
        //message is invalid, so we can't trust the rest of the messages either...
        status |= INPHI_ERROR;
        goto msg2_erase_and_unlock;
    }

    //at this point the message is valid!

    //if we're in a polling loop, then don't bother unlocking and resetting the indexes
    if(was_locked)
    {
        //update the rd_idx for next time
        pif_buf[0] = msg_buffers[SPICA_MSG2_BUF_FW2API].rd_idx+total_len;
        status |= spica_mcu_pif_write(die, msg_buffers[SPICA_MSG2_BUF_FW2API].self_addr+2*sizeof(uint32_t), pif_buf, 1);
        //just exit
        goto exit;
    }

msg2_erase_and_unlock:
    //update the rd/wr_idx, which will erase the messages
    pif_buf[0] = 0;
    pif_buf[1] = 0;
    status |= spica_mcu_pif_write(die, msg_buffers[SPICA_MSG2_BUF_FW2API].self_addr+sizeof(uint32_t), pif_buf, 2);

msg2_unlock:
    //unlock the buffer if it wasn't locked before this fn
    if(!was_locked)
    {
        spica_msg2_unlock(die);
    }

exit:
    SPICA_UNLOCK(die);

    return status;
}

/*
 * Update the FEC stats poller rules
 */
inphi_status_t spica_mcu_fec_stats_poller_cfg(
    uint32_t   die,
    e_spica_intf intf,
    const spica_fec_stats_poller_rules_t *stats_rules
    )
{
    inphi_status_t status = INPHI_OK;
    uint8_t req_id;
    uint32_t payload[3];

    payload[0] = intf&0xffff;
    payload[1] = (stats_rules->en)<<31;
    payload[1] |= (stats_rules->interval_time&0x3fff)<<16;
    payload[1] |= (stats_rules->accumulation_time&0x3fff);

    /* Send the request to the MCU */
    req_id = spica_mcu_msg_id();
    status |= spica_msg2_push_message(die, req_id, SPICA_MCU_MSG_FEC_STATS_CFG, payload, 2);
    if(status != INPHI_OK)
    {
        INPHI_CRIT("Failed sending request to f/w\n");
        return status;
    }

    //no response needed from FW
    return status;
}

inphi_status_t spica_mcu_fec_stats_poller_request(
    uint32_t   die,
    e_spica_intf intf,
    bool clear_on_read
    )
{
    inphi_status_t status = INPHI_OK;
    uint8_t req_id;
    uint32_t payload[3];
    int len = 1;
    e_spica_mcu_msg_type msg_type;

    payload[0] = (intf&0xffff);
    //if we're doing a clear on read
    payload[1] = (intf&0xffff);

    if(clear_on_read)
    {
        msg_type = SPICA_MCU_MSG_FEC_STATS_GET_AND_CLEAR;
        len = 2;
    }
    else {
        msg_type = SPICA_MCU_MSG_FEC_STATS_GET;
        len = 1;
    }

    /* Send the request to the MCU */
    req_id = spica_mcu_msg_id();
    status |= spica_msg2_push_message(die, req_id, msg_type, payload, len);
    if(status != INPHI_OK)
    {
        INPHI_CRIT("Failed sending request to f/w\n");
        return status;
    }

    //no need to wait for the FW

    return status;
}

#ifndef INPHI_DONT_USE_STDLIB
/*
 * Get the FEC stats from the poller
 */
e_spica_poller_status spica_mcu_fec_stats_poller_get(
    uint32_t   die,
    e_spica_intf intf,
    uint32_t blocks_to_read,
    spica_fec_stats_cp_block_t *stats
    )
{
    inphi_status_t status = INPHI_OK;
    e_spica_poller_status ret = SPICA_POLLER_OK;

    // expected size of the structure from the FW
    const uint32_t exp_len = offsetof(spica_fec_stats_cp_block_t, _state)/sizeof(uint32_t);

    SPICA_LOCK(die);

    typedef enum
    {
        FSPG_INIT = 0,
        FSPG_GRAB,
        FSPG_ERROR,
    } e_fspg_state;
    e_fspg_state state = (e_fspg_state)stats->_state;

    //before we do anything, see if we have an unhandled error from before
    if(FSPG_ERROR == state)
    {
        //we have an error, you can't call this method anymore
        INPHI_CRIT("spica_fec_stats_poller_get error, state %d not valid, call spica_fec_stats_poller_request to clear\n", state);
        status |= INPHI_ERROR;
        //msg has already been cleared last time, no need to do that again
        goto exit;
    }

    /*
     * We can't call spica_msg2_pull_message directly because it'll
     * a) read the whole message which is gigantic
     * b) clear the queue after reading
     * So instead we'll manually lock and read chunks of the msg at a time. Where we are at in the process
     * is tracked by our simple _state member so we don't repeat some expensive stuff (header checking).
     */

    spica_msg2_buffer msg_buffers[2];
    INPHI_MEMSET(msg_buffers, 0, sizeof(msg_buffers));
    // resp just has to be big enough to hold the header for the Rx msg and the read/write indexes in the Tx msg
    uint32_t resp[2];

    //wait for at least one msg (len = header+checksum) to be populated by the FW
    //don't wait as long as 1s either, just a few loops
    status |= spica_msg2_wait_and_lock(die, msg_buffers, SPICA_MSG2_BUF_FW2API, 2, SPICA_MCU_MBOX_ITER_DELAY*10);
    if(status)
    {
        // OK to exit, we just need to wait longer
        status = INPHI_OK;
        ret = SPICA_POLLER_WAITING;
        goto exit;
    }
    // have a message and have locked the buffer for reading, get the FW2API read address
    const uint32_t rd_addr = msg_buffers[SPICA_MSG2_BUF_FW2API].buffer_addr + msg_buffers[SPICA_MSG2_BUF_FW2API].rd_idx*sizeof(uint32_t);

    // ********** START MSG2 LOCKED *************

    switch(state)
    {
        case FSPG_INIT:
        {
            // at this point there is some message in the buffer, grab the header and verify the response
            // is what we're looking for
            // +1 to grab the poll_count too, may as well update that now
            status |= spica_mcu_pif_read(die, rd_addr, resp, 2);

            e_spica_mcu_msg_type resp_type;
            uint16_t resp_len;
            uint8_t resp_id;
            resp_id = (resp[0]>>24) & 0xff;
            resp_type = (e_spica_mcu_msg_type)((resp[0]>>16) & 0xff);
            //not including header and cksum
            resp_len = (resp[0] & 0xffff) -2;

            // make sure the message type is correct
            //if we have an error, it's a flat-out failure
            if((status != INPHI_OK) || (resp_type != SPICA_MCU_MSG_FEC_STATS_RET))
            {
                INPHI_CRIT("Error pulling message or FW returned error:\n"
                           "status %d resp_id %d resp_type %d\n", status, resp_id, resp_type);
                //must always unlock
                status |= INPHI_ERROR;
                goto msg2_error;
            }
            // < so that we can update the structure in FW while maintaining backwards compatibility
            if(resp_len < exp_len)
            {
                INPHI_CRIT("Unexpected resp_len %u != %u for msg %d, incompatible API/FW\n", resp_len, exp_len, resp_type);
                status |= INPHI_ERROR;
                goto msg2_error;
            }

            //if the poll_count is still 0 or the same as last time then we didn't wait long enough for the
            // FW to accumulate once again.
            if(0 == resp[1])
            {
                INPHI_WARN("FW hasn't captured stats yet, wait and req again\n");
                status |= INPHI_ERROR;
                goto msg2_error;
            }
            else if(stats->poll_count == resp[1])
            {
                INPHI_WARN("FW hasn't captured stats since last time, wait and req again\n");
                status |= INPHI_ERROR;
                goto msg2_error;
            }
            //update the poller count
            stats->poll_count = resp[1];

        }
            //otherwise we have the right message, update our state
            state += 1;
            INPHI_FALLTHROUGH
            // fall through
        case FSPG_GRAB:
        {
            //there is no nice way to do this, so build a LUT with indexes and lengths
#define FSPG_LUT(start, end) {\
        (offsetof(spica_fec_stats_cp_block_t, start)),\
        ((offsetof(spica_fec_stats_cp_block_t, end)-offsetof(spica_fec_stats_cp_block_t, start)+sizeof(uint16_t))/sizeof(uint32_t))\
    }
            static const struct
            {
                // bytes offset to the start of the block
                uint32_t off;
                // num of 32b words length to read
                uint32_t len;
            } block_lut[SPICA_FEC_STATS_CP_BLOCKS] = {
                FSPG_LUT(ber_avg, ferc_avg), // 0
                FSPG_LUT(ber_curr, ferc_curr), // 1
                FSPG_LUT(ber_max, ferc_max), // 2
                FSPG_LUT(ber_min, ferc_min), // 3
                FSPG_LUT(corr_cw_hist_15_curr, corr_cw_hist_12_max), // 4
                FSPG_LUT(corr_cw_hist_11_curr, ser_max), // 5
                FSPG_LUT(corr_cw_hist_6_curr, corr_cw_hist_1_max), // 6
                FSPG_LUT(ser_min, corr_cw_hist_1_min), // 7
            };
#undef FSPG_LUT

            int i = 0;
            while(blocks_to_read && (i < SPICA_FEC_STATS_CP_BLOCKS))
            {
                if(blocks_to_read & (1<<i))
                {
                    uint32_t off = block_lut[i].off;
                    uint32_t len = block_lut[i].len;
                    //read the data, saving it directly to our stats structure at the right offset
                    uint32_t *ptr = (uint32_t*)stats+off/sizeof(*ptr);
                    // rd_addr+1 because we want to skip the header which we already read
                    status |= spica_mcu_pif_read(die, rd_addr+sizeof(uint32_t)+off, ptr, len);
                    if(status) goto msg2_error;

                    //done with this block
                    blocks_to_read &= ~(1<<i);
                }
                i += 1;
            }
        }
            break;

        default:
            //should never get here!
            status |= INPHI_ERROR;
            goto msg2_error;
    }

    //no errors, probably still have data in the buffer
    //even if we don't the next call to spica_fec_stats_poller_request will clear the FW2API buffer and our state
    goto msg2_unlock;

msg2_error:
    //hit some error
    //update the rd/wr_idx, which will erase the messages
    resp[0] = 0;
    resp[1] = 0;
    status |= spica_mcu_pif_write(die, msg_buffers[SPICA_MSG2_BUF_FW2API].self_addr+sizeof(uint32_t), resp, 2);

    //update our state to say we have an error and we can't use this method again
    state = FSPG_ERROR;

msg2_unlock:
    // ********** END MSG2 LOCKED *************
    spica_msg2_unlock(die);

    //update the state
    stats->_state = state;

exit:
    SPICA_UNLOCK(die);

    if(status)
    {
        ret = status;
    }
    return ret;
}
#endif //ifndef INPHI_DONT_USE_STDLIB

/*
 * Clear the internal FEC stats poller
 */
inphi_status_t spica_mcu_fec_stats_poller_clear(
    uint32_t   die,
    e_spica_intf intf
    )
{
    inphi_status_t status = INPHI_OK;
    uint8_t req_id;
    uint32_t payload[3];

    payload[0] = (intf&0xffff);

    /* Send the request to the MCU */
    req_id = spica_mcu_msg_id();
    status |= spica_msg2_push_message(die, req_id, SPICA_MCU_MSG_FEC_STATS_CLEAR, payload, 1);
    if(status != INPHI_OK)
    {
        INPHI_CRIT("Failed sending request to f/w\n");
        return status;
    }

    //no response needed from FW
    return status;
}

/**
 * Get the SRX pulse resp
 */
inphi_status_t spica_msg_srx_pulse_resp_request(
    uint32_t die,
    uint32_t channel,
    int32_t *resp_values,
    uint32_t len)
{
    inphi_status_t status = INPHI_OK;
    uint8_t req_id;
    uint32_t payload[3];

    uint8_t resp_id;
    e_spica_mcu_msg_type resp_type;
    uint16_t resp_len;

    SPICA_LOCK(die);

    if(len < 2) {
        INPHI_CRIT("Pulse resp len must be > 2: len = %d\n", len);
        status |= INPHI_ERROR;
        goto done;
    }

    req_id = spica_mcu_msg_id();

    //convert to a FW channel and the correct die for this channel
    //INPHI_NOTE("BEFORE spica_rebase_channel_intf:ch:%d\n", channel);
    //INPHI_NOTE("BEFORE spica_rebase_channel_intf:die:%d\n", die);
    status |= spica_rebase_channel_by_intf(&die, &channel, SPICA_INTF_SRX);
    // Map offset multiplier to FW channel
    // Specific for SRX INTF
    // OFFSET MULT: 0  1  4  5  8  9  12  13
    // FW CHANNEL : 0  1  3  4  6  7  9   10
    channel -= (channel)/4; 
    //INPHI_NOTE("AFTER spica_rebase_channel_intf:ch:%d\n", channel);
    //INPHI_NOTE("AFTER spica_rebase_channel_intf:die:%d\n", die);
    if(status) goto done;

    //payload is
    // 0: channel 31:16   intf 15:0
    // 1: num of taps
    payload[0] = ((channel&0xffff)<<16) | (SPICA_INTF_SRX&0xffff);
    payload[1] = len;

    status |= spica_msg2_push_message(die, req_id, SPICA_MCU_MSG_SRX_PULSE_REQUEST, payload, 2);
    if(status)
    {
        INPHI_CRIT("Failed sending the info request for the histogram data to the h/w\n");
        goto done;
    }

    //get the data from the FW, wait forever for it to come in...
    //resp is {status, value0, ...}
    /* Wait for the response from the MCU */
    status |= spica_msg2_pull_message(die, (uint32_t*)resp_values, len, 2000, &resp_id, &resp_type, &resp_len);

    if((status != INPHI_OK) || (req_id != resp_id))
    {
        INPHI_CRIT("Unexpected response from the f/w, req_id = %d, resp_id = %d\n",
                   req_id, resp_id);
        status |= INPHI_ERROR;
        goto done;
    }

    //we use the len to figure out whether there was an error or not
    if((resp_len != len) || (resp_type != SPICA_MCU_MSG_SRX_PULSE_RESPONSE))
    {
        INPHI_CRIT("FW failed getting pulse resp. l%d t%d\n", resp_len, resp_type);
        status |= INPHI_ERROR;
        goto done;
    }

done:
    SPICA_UNLOCK(die);

    return status;
}
#endif // defined(INPHI_REMOVE_MESSAGING)

/**
 ****************************************************************************
 *
 * @brief
 *     This module describes the high level API methods provided
 *     by the Spica API.
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

#if defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)
inphi_status_t spica_spi_poll_rx_fifo(uint32_t die);

//! This is an internal method that is used to reset the SPI
//! bus. It should not be called directly by the user.
//!
//! @param die [I] - The ASIC die being accessed.
//!
//! @private
inphi_status_t spica_spi_reset(
    uint32_t die)
{
    inphi_status_t status = INPHI_OK;

    SPICA_LOCK(die);

    SPICA_MCU_RESET__SPIRST__RMW(die, 1);
    SPICA_MCU_RESET__SPIRST__RMW(die, 0);

    SPICA_UNLOCK(die);

    INPHI_MDELAY(1);

    return status;
}

//! This is an internal method that is used to read a single word from the
//! EEPROM. It should not be called directly by the user.
//!
//! @param die [I] - The ASIC die being accessed.
//!
//! @private
inphi_status_t spica_spi_read_word(
    uint32_t die,
    uint32_t *word)
{
    inphi_status_t status = INPHI_OK;
    uint16_t spi_int_status0, lsw, msw;
    uint16_t attempts = 1000;
    uint16_t fifo_not_empty;

    // Wait for a response from the SPI block
    spi_int_status0 = SPICA_APB_SPI_INT_STATUS0__READ(die);
    SPICA_APB_SPI_INT_STATUS1__READ(die);

    fifo_not_empty = SPICA_APB_SPI_INT_STATUS0__RX_FIFO_NOTEMPTY__GET(spi_int_status0);

    while (!fifo_not_empty)
    {
        if (attempts <= 0)
        {
            return INPHI_ERROR;
        }
        attempts--;

        spi_int_status0 = SPICA_APB_SPI_INT_STATUS0__READ(die);
        SPICA_APB_SPI_INT_STATUS1__READ(die);

        fifo_not_empty = SPICA_APB_SPI_INT_STATUS0__RX_FIFO_NOTEMPTY__GET(spi_int_status0);
    }

    // Pop the data from the FIFO
    lsw = SPICA_APB_SPI_RX_DATA0__READ(die);
    msw = SPICA_APB_SPI_RX_DATA1__READ(die);

    // Write a word to request the next data
    SPICA_APB_SPI_TX_DATA0__WRITE(die, 0xffff);
    SPICA_APB_SPI_TX_DATA1__WRITE(die, 0xffff);

    SPICA_UNLOCK(die);

    *word = ((uint32_t)msw << 16) | (uint32_t)lsw;

    return status;
}

//! Initializes the SPI interface to read from a location
//! in the EEPROM
//! @private
inphi_status_t spica_spi_read_init(
    uint32_t      die,
    uint32_t      addr,
    e_spica_spi_clk_div clkdiv)
{
    inphi_status_t status = INPHI_OK;
    uint16_t spi_config0, spi_config1, lsw, msw;
    uint32_t cmd_word, read_word;

    SPICA_LOCK(die);

    spi_config0 = SPICA_APB_SPI_CONFIG0__READ(die);
    spi_config1 = SPICA_APB_SPI_CONFIG1__READ(die);
    spi_config0 = SPICA_APB_SPI_CONFIG0__MANUAL_CS__SET(spi_config0, 1); // Manual mode
    spi_config0 = SPICA_APB_SPI_CONFIG0__BAUD_RATE_DIV__SET(spi_config0, clkdiv);
    spi_config0 = SPICA_APB_SPI_CONFIG0__MODE_SEL__SET(spi_config0, 1);  // Master
    spi_config0 = SPICA_APB_SPI_CONFIG0__WORD_SIZE__SET(spi_config0, 3); // 32 bits
    SPICA_APB_SPI_CONFIG0__WRITE(die, spi_config0);
    SPICA_APB_SPI_CONFIG1__WRITE(die, spi_config1);

    SPICA_APB_SPI_SPI_EN0__WRITE(die, 1);
    SPICA_APB_SPI_SPI_EN1__WRITE(die, 0);

    SPICA_APB_SPI_TX_THRESHOLD0__WRITE(die, 4);
    SPICA_APB_SPI_TX_THRESHOLD1__WRITE(die, 1);
    SPICA_APB_SPI_RX_THRESHOLD0__WRITE(die, 1);
    SPICA_APB_SPI_RX_THRESHOLD1__WRITE(die, 0);

    SPICA_APB_SPI_DELAY0__WRITE(die, 0);
    SPICA_APB_SPI_DELAY1__WRITE(die, 0);

    cmd_word = 0x03000000 | addr;
    lsw = cmd_word & 0xffff;
    msw = (cmd_word >> 16) & 0xffff;

    SPICA_APB_SPI_TX_DATA0__WRITE(die, lsw);
    SPICA_APB_SPI_TX_DATA1__WRITE(die, msw);

    SPICA_UNLOCK(die);

    // Discard the first word returned from the FIFO
    // since it will be garbage
    status |= spica_spi_read_word(die, &read_word);

    return status;
}

//! @private
inphi_status_t spica_spi_write_init(uint32_t die, e_spica_spi_clk_div clkdiv)
{
    inphi_status_t status = INPHI_OK;
    uint16_t spi_cfg0,spi_cfg1;

    spi_cfg0 = SPICA_APB_SPI_CONFIG0__READ(die);
    spi_cfg1 = SPICA_APB_SPI_CONFIG1__READ(die);
    spi_cfg0 = SPICA_APB_SPI_CONFIG0__WORD_SIZE__SET(spi_cfg0, 0); // 8 bits
    spi_cfg0 = SPICA_APB_SPI_CONFIG0__BAUD_RATE_DIV__SET(spi_cfg0, clkdiv);
    spi_cfg0 = SPICA_APB_SPI_CONFIG0__MODE_SEL__SET(spi_cfg0,  1); // Master
    spi_cfg0 = SPICA_APB_SPI_CONFIG0__MANUAL_CS__SET(spi_cfg0, 0); // Normal CS

    SPICA_APB_SPI_CONFIG0__WRITE(die, spi_cfg0);
    SPICA_APB_SPI_CONFIG1__WRITE(die, spi_cfg1);

    SPICA_APB_SPI_SPI_EN0__WRITE(die, 1);
    SPICA_APB_SPI_SPI_EN1__WRITE(die, 0);

    SPICA_APB_SPI_TX_THRESHOLD0__WRITE(die, 4);
    SPICA_APB_SPI_TX_THRESHOLD1__WRITE(die, 0);
    SPICA_APB_SPI_RX_THRESHOLD0__WRITE(die, 1);
    SPICA_APB_SPI_RX_THRESHOLD1__WRITE(die, 0);

    // Adjust delay to SPI Reference Clk (Fixes intermittency with 8-bit Flash/EEPROM write and erase)
    SPICA_APB_SPI_DELAY0__WRITE(die, 0x0000);
    SPICA_APB_SPI_DELAY1__WRITE(die, 0x8000);

    return status;
}

//! @private
inphi_status_t spica_spi_eeprom_write_enable(uint32_t die)
{
    // Write enable command
    uint32_t spi_cmd = 0x06000000;
    uint16_t lsw = spi_cmd & 0xffff;
    uint16_t msw = (spi_cmd >> 16) & 0xffff;

    SPICA_APB_SPI_TX_DATA0__WRITE(die, lsw);
    SPICA_APB_SPI_TX_DATA1__WRITE(die, msw);

    // DEBUG BRAD: Not sure if i should remove
    //             the poll or not.
    return spica_spi_poll_rx_fifo(die);
}

//! @private
inphi_status_t spica_spi_eeprom_write_data_init(uint32_t die)
{
    uint16_t spi_cfg0 = SPICA_APB_SPI_CONFIG0__READ(die);
    uint16_t spi_cfg1 = SPICA_APB_SPI_CONFIG1__READ(die);
    spi_cfg0 = SPICA_APB_SPI_CONFIG0__MANUAL_CS__SET(spi_cfg0, 1); // Manual CS
    spi_cfg0 = SPICA_APB_SPI_CONFIG0__WORD_SIZE__SET(spi_cfg0, 3); // 32 bit
    SPICA_APB_SPI_CONFIG0__WRITE(die, spi_cfg0);
    SPICA_APB_SPI_CONFIG1__WRITE(die, spi_cfg1);

    return INPHI_OK;
}

//! @private
inphi_status_t spica_spi_eeprom_write_data_fini(uint32_t die)
{
    uint16_t spi_cfg0 = SPICA_APB_SPI_CONFIG0__READ(die);
    uint16_t spi_cfg1 = SPICA_APB_SPI_CONFIG1__READ(die);
    spi_cfg0 = SPICA_APB_SPI_CONFIG0__PERIPHERAL_CS__SET(spi_cfg0, 0);
    SPICA_APB_SPI_CONFIG0__WRITE(die, spi_cfg0);
    SPICA_APB_SPI_CONFIG1__WRITE(die, spi_cfg1);

    return INPHI_OK;
}

//! @private
inphi_status_t spica_spi_poll_rx_fifo(uint32_t die)
{
    uint16_t spi_int_status0 = SPICA_APB_SPI_INT_STATUS0__READ(die);
                               SPICA_APB_SPI_INT_STATUS1__READ(die);

    uint32_t attempts = 10000;
    while(!SPICA_APB_SPI_INT_STATUS0__RX_FIFO_NOTEMPTY__GET(spi_int_status0))
    {
        if(attempts <= 0)
        {
            return INPHI_ERROR;
        }

        spi_int_status0 = SPICA_APB_SPI_INT_STATUS0__READ(die);
                          SPICA_APB_SPI_INT_STATUS1__READ(die);
        attempts -= 1;
    }

    // Pop the data from the FIFO
    SPICA_APB_SPI_RX_DATA0__READ(die);
    SPICA_APB_SPI_RX_DATA1__READ(die);

    return INPHI_OK;
}

//! @private
inphi_status_t spica_spi_eeprom_write_data_segment(uint32_t die, uint32_t addr, uint32_t words[], uint32_t num_words)
{
    // Issue the write command
    uint32_t cmd = 0x02000000 | addr;
    uint16_t lsw = cmd & 0xffff;
    uint16_t msw = (cmd >> 16) & 0xffff;
    SPICA_APB_SPI_TX_DATA0__WRITE(die, lsw);
    SPICA_APB_SPI_TX_DATA1__WRITE(die, msw);

    for(uint32_t i = 0; i < num_words; i++)
    {
        lsw = words[i] & 0xffff;
        msw = (words[i] >> 16) & 0xffff;
        SPICA_APB_SPI_TX_DATA0__WRITE(die, lsw);
        SPICA_APB_SPI_TX_DATA1__WRITE(die, msw);

        if(INPHI_OK != spica_spi_poll_rx_fifo(die))
        {
            return INPHI_ERROR;
        }
    }

    if(INPHI_OK != spica_spi_poll_rx_fifo(die))
    {
        return INPHI_ERROR;
    }

    uint16_t spi_cfg0 = SPICA_APB_SPI_CONFIG0__READ(die);
    uint16_t spi_cfg1 = SPICA_APB_SPI_CONFIG1__READ(die);

    spi_cfg0 = SPICA_APB_SPI_CONFIG0__PERIPHERAL_CS__SET(spi_cfg0, 1);

    SPICA_APB_SPI_CONFIG0__WRITE(die, spi_cfg0);
    SPICA_APB_SPI_CONFIG1__WRITE(die, spi_cfg1);

    // DEBUG BRAD: Need to reduce this time
    //INPHI_MDELAY(1000);
    INPHI_MDELAY(10);

    return INPHI_OK;
}

//! This method is called to write a block of data to the EEPROM via the SPI
//! interface. The input words should not be byte swapped.
//!
//! @param die         [I] - The ASIC die being accessed.
//! @param eeprom_addr [I] - The byte address of the EEPROM to start reading from.
//! @param words       [I] - The array of 32 bit words to write to the EEPROM.
//! @param clkdiv      [I] - The clock divide ratio used to write to the EEPROM.
//!
//! @return INPHI_OK on success, INPHI_ERROR on failure.
//!
//! @private
inphi_status_t spica_spi_write_data_block(uint32_t die,
                                        uint32_t eeprom_addr,
                                        uint32_t *words,
                                        uint32_t num_words,
                                        e_spica_spi_clk_div clkdiv)
{
    inphi_status_t status = INPHI_OK;

    spica_spi_reset(die);

    spica_spi_write_init(die, clkdiv);

    // Send WREN command to SPI slave (EEPROM)
    if(INPHI_OK != spica_spi_eeprom_write_enable(die))
    {
        return INPHI_ERROR;
    }

    // Set CS to Manual mode and xfer size to 32 bits
    spica_spi_eeprom_write_data_init(die);

    status |= spica_spi_eeprom_write_data_segment(die, eeprom_addr, words, num_words);

    spica_spi_eeprom_write_data_fini(die);

    return status;
}

//! This method is called to read a block of data from the EEPROM via the
//! SPI interface. This method will return the EEPROM data in the actual
//! data order. That is, it won't be byte-swapped as it is in the EEPROM
//! image file
//!
//! @param die         [I] - The die of the ASIC being accessed
//! @param eeprom_addr [I] - The byte address in the EEPROM to read from
//! @param words       [O] - The buffer to fetch the EEPROM data into
//! @param num_words   [I] - The number of 32 bit words to read from the EEPROM
//! @param clkdiv      [I] - The SPI clock divide ratio
//!
//! @return A tuple containing:
//!         - INPHI_OK on success, INPHI_ERROR on failure
//!         - A list of data read from the EEPROM in non-swapped order.
//!
//! @private
inphi_status_t spica_spi_read_data_block(
    uint32_t      die,
    uint32_t      eeprom_addr,
    uint32_t      *words,
    uint32_t      num_words,
    e_spica_spi_clk_div clkdiv)
{
    inphi_status_t status = INPHI_OK;

    spica_spi_reset(die);
    spica_spi_read_init(die, eeprom_addr, clkdiv);
    for(uint32_t i = 0; i < num_words; i++)
    {
        status |= spica_spi_read_word(die, &words[i]);
    }

    return status;
}

//! This method is called to erase the EEPROM
//!
//! @param die         [I] - The physical ASIC die being accessed.
//!
//! @return INPHI_OK on success, INPHI_ERROR on failure.
//!
//! Note: This command does not work on EEPROMs. It only works
//!       on Flash devices.
//!
//!       List of basic Flash commands:
//!
//!       1.  Write Status Register:   0x01
//!       2.  Read:                    0x02
//!       3.  Write:                   0x03
//!       4.  Write Disable:           0x04
//!       5.  Read Status Register:    0x05
//!       6.  Write Enable:            0x06
//!       7.  Chip Erase:              0x60 or 0xC7
//!       8.  Read ID:                 0x90
//!       9.  JEDEC ID:                0x9F
//!       10. Power Down:              0xB9
//!       11. Resume from Power down:  0xAB
//!
//! @since 1.0
//!
inphi_status_t spica_spi_eeprom_erase(uint32_t die)
{
    inphi_status_t status = INPHI_OK;

    //Reset the SPI bus before sending the erase command
    status |= spica_spi_reset(die);
    if(status != INPHI_OK)
    {
        INPHI_NOTE("Error with spica_spi_reset()\n");
        return status;
    }

    spica_spi_write_init(die, SPICA_SPI_CLK_DIV_64);

    SPICA_APB_SPI_TX_DATA0__WRITE(die, 0x0000);
    SPICA_APB_SPI_TX_DATA1__WRITE(die, 0x0600);
    status |= spica_spi_poll_rx_fifo(die);

    SPICA_APB_SPI_TX_DATA0__WRITE(die, 0x0000);
    SPICA_APB_SPI_TX_DATA1__WRITE(die, 0x6000);
    status |= spica_spi_poll_rx_fifo(die);

    return status;
}

#endif // defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)

/** @file por_package.c
 *****************************************************************************
 *
 * @brief
 * This module contains the implementation of the packagement management
 * methods used to cache access to the ASIC registers and map API
 * channel numbers to the approriate ASIC pins.
 *
 *****************************************************************************
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

// Query the ASIC package type
e_por_package_type por_package_get_type(uint32_t die)
{
    e_spica_package_type pkg_type = spica_package_get_type(die);

    return (e_por_package_type)pkg_type;
}

uint32_t por_package_get_num_dies(uint32_t die)
{
    return spica_package_get_num_dies(die);
}

uint32_t por_package_get_base_die(uint32_t die)
{
    return spica_package_get_base_die(die);
}

// Override the package type, this will be saved in bits [7:5] of the die
uint32_t por_package_type_set_in_die(uint32_t die, e_por_package_type package)
{
    return spica_package_type_set_in_die(die,
                                        (e_spica_package_type)package);
}

uint32_t por_package_discover_type(uint32_t die)
{
    e_por_package_type package = por_package_get_type(die);

    // Cache package type in the lower bits of the EFUSE
    // to avoid looking it up on every access.
    return por_package_type_set_in_die(die, package);
}

e_por_package_type por_package_query_efuse(
    uint32_t die)
{
    return (e_por_package_type)spica_package_query_efuse(die);
}

void por_package_get_channels(uint32_t die, e_por_intf intf, uint32_t* min, uint32_t* max)
{
    const por_channels_t* channels = por_channels(die, intf);

    if(channels != NULL)
    {
        *min = channels->ch[0];
        *max = channels->ch[(channels->num)-1];
    }
    else
    {
        *min = 0;
        *max = 0;
    }
}

/**
 * This method is called to dump the cache used to map a particular
 * die parameter to the associated ASIC package type. The package type
 * is important so that the API knows how to map channels to the external
 * pins of the ASIC.
 *
 * @since 0.6
 */
void por_package_cache_dump()
{
    spica_package_cache_dump();
}

/** @file por_reg_access.c
 *****************************************************************************
 *
 * @brief
 * These contain the register access functionality.
 *
 * End users must implement spica_reg_get and spica_reg_set for their comms
 * protocol (MDIO or I2C).
 * 
 *****************************************************************************
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

const por_channels_t _por_chs_1t8  = {8,  {1, 2, 3, 4, 5, 6, 7, 8}};  // (12x13 || 12x13_EB) HTX/HRX
const por_channels_t _por_chs_1t4  = {4,  {1, 2, 3, 4}};              // (12x13 || 12x13_EB) LRX/LTX

const por_channels_t* por_channels(uint32_t die, e_por_intf intf)
{
    e_por_package_type package = por_package_get_type(die);

    switch(package)
    {
        case POR_PACKAGE_TYPE_EML_12x13:
        case POR_PACKAGE_TYPE_EML_12x13_REV1:
        case POR_PACKAGE_TYPE_STD_10x13:
        {
            //line side
            if(intf & POR_INTF_PKR)
            {
                return &_por_chs_1t4;
            }
            //host side
            else if (intf & POR_INTF_PSR)
            {
                return &_por_chs_1t8;
            }
            break;
        }
        default:
            break;
    }

    return NULL;
}

/** @file por_prbs.c
 ****************************************************************************
 *
 * @brief
 *     This module contains the implementation of the PRBS interface
 *     on the Porrima Gen3 ASIC.
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

static spica_prbs_gen_rules_t g_spica_prbs_gen_rules;
static spica_prbs_chk_rules_t g_spica_prbs_chk_rules;

/*
 * Configure the default PRBS generator rules
 */
inphi_status_t por_tx_prbs_rules_set_default(
    por_tx_prbs_gen_rules_t* por_tx_prbs_gen_rules)
{
    inphi_status_t status = INPHI_OK;
    if(!por_tx_prbs_gen_rules)
    {
        INPHI_CRIT("PRBS Generator rules pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    INPHI_MEMSET(por_tx_prbs_gen_rules, 0, sizeof(por_tx_prbs_gen_rules_t));

    status = spica_prbs_gen_rules_default_set(&g_spica_prbs_gen_rules);
    
    if (INPHI_OK == status)
    {
        por_tx_prbs_gen_rules->en                = g_spica_prbs_gen_rules.en;
        por_tx_prbs_gen_rules->gen_en_lsb        = g_spica_prbs_gen_rules.gen_en_lsb;
        por_tx_prbs_gen_rules->prbs_mode         = g_spica_prbs_gen_rules.prbs_mode;
        por_tx_prbs_gen_rules->prbs_pattern_lsb  = g_spica_prbs_gen_rules.prbs_pattern_lsb;
        por_tx_prbs_gen_rules->prbs_pattern      = g_spica_prbs_gen_rules.prbs_pattern;
        por_tx_prbs_gen_rules->pattern_mode      = g_spica_prbs_gen_rules.pattern_mode;
        por_tx_prbs_gen_rules->fixed0_pat0       = g_spica_prbs_gen_rules.seed_evn_0;
        por_tx_prbs_gen_rules->fixed0_pat1       = g_spica_prbs_gen_rules.seed_evn_1;
        por_tx_prbs_gen_rules->fixed0_pat2       = g_spica_prbs_gen_rules.seed_evn_2;
        por_tx_prbs_gen_rules->fixed0_pat3       = g_spica_prbs_gen_rules.seed_evn_3;
        por_tx_prbs_gen_rules->fixed1_pat0       = g_spica_prbs_gen_rules.seed_odd_0;
        por_tx_prbs_gen_rules->fixed1_pat1       = g_spica_prbs_gen_rules.seed_odd_1;
        por_tx_prbs_gen_rules->fixed1_pat2       = g_spica_prbs_gen_rules.seed_odd_2;
        por_tx_prbs_gen_rules->fixed1_pat3       = g_spica_prbs_gen_rules.seed_odd_3;
        por_tx_prbs_gen_rules->fixed0_pat_repeat = 1; // repeat 64-bit fixed0_pat pattern 1 time
        por_tx_prbs_gen_rules->fixed1_pat_repeat = 0; // do not send the 64-bit fixed1_pat pattern
    }

    return status;
}

void apply_custom_prbs_gen_rules(
    por_tx_prbs_gen_rules_t* por_tx_prbs_gen_rules, 
    spica_prbs_gen_rules_t*  spica_prbs_gen_rules)
{
    spica_prbs_gen_rules->en               = por_tx_prbs_gen_rules->en;
    spica_prbs_gen_rules->gen_en_lsb       = por_tx_prbs_gen_rules->gen_en_lsb;
    spica_prbs_gen_rules->prbs_mode        = por_tx_prbs_gen_rules->prbs_mode;
    spica_prbs_gen_rules->prbs_pattern_lsb = por_tx_prbs_gen_rules->prbs_pattern_lsb;
    spica_prbs_gen_rules->prbs_pattern     = por_tx_prbs_gen_rules->prbs_pattern;
    spica_prbs_gen_rules->pattern_mode     = por_tx_prbs_gen_rules->pattern_mode;
    spica_prbs_gen_rules->seed_evn_0       = por_tx_prbs_gen_rules->fixed0_pat0;
    spica_prbs_gen_rules->seed_evn_1       = por_tx_prbs_gen_rules->fixed0_pat1;
    spica_prbs_gen_rules->seed_evn_2       = por_tx_prbs_gen_rules->fixed0_pat2;
    spica_prbs_gen_rules->seed_evn_3       = por_tx_prbs_gen_rules->fixed0_pat3;
    spica_prbs_gen_rules->seed_odd_0       = por_tx_prbs_gen_rules->fixed1_pat0;
    spica_prbs_gen_rules->seed_odd_1       = por_tx_prbs_gen_rules->fixed1_pat1;
    spica_prbs_gen_rules->seed_odd_2       = por_tx_prbs_gen_rules->fixed1_pat2;
    spica_prbs_gen_rules->seed_odd_3       = por_tx_prbs_gen_rules->fixed1_pat3;
} 

/*
 * Configure the Line or Host side PRBS generator
 */
inphi_status_t por_tx_prbs_gen_config(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_tx_prbs_gen_rules_t* por_tx_prbs_gen_rules)
{
    inphi_status_t status = INPHI_OK;
    if(!por_tx_prbs_gen_rules)
    {
        INPHI_CRIT("PRBS Generator rules pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    //Internal method to apply custom prbs rules
    apply_custom_prbs_gen_rules(por_tx_prbs_gen_rules, &g_spica_prbs_gen_rules); 

    status = spica_prbs_gen_config(die, channel, 
                                  (e_spica_intf)intf, 
                                   &g_spica_prbs_gen_rules);

    return status;
}

/**
 * This method is called to inject errors into the TX datapath.
 */ 
inphi_status_t por_tx_error_inject(
    uint32_t             die,
    uint32_t             channel,
    e_por_intf           intf,
    bool                 enable,
    e_por_tx_err_inj_pat pattern,
    uint8_t              gap,
    uint8_t              duration)
{
    return spica_prbs_gen_error_inject(die, channel,
                                      (e_spica_intf)intf,
                                       enable,
                                      (e_spica_prbs_err_inj_pat)pattern,
                                       gap, duration);
}

/*
 * Configure the Line and Host side PRBS checker rules
 */
inphi_status_t por_rx_prbs_rules_set_default(
    por_rx_prbs_chk_rules_t* por_rx_prbs_chk_rules)
{
    inphi_status_t status = INPHI_OK;
    if(!por_rx_prbs_chk_rules)
    {
        INPHI_CRIT("PRBS Checker rules pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    INPHI_MEMSET(por_rx_prbs_chk_rules, 0, sizeof(por_rx_prbs_chk_rules_t));

    status = spica_prbs_chk_rules_default_set(&g_spica_prbs_chk_rules);
    
    if (INPHI_OK == status)
    {
        // generic rx checker rules
        por_rx_prbs_chk_rules->en                                = g_spica_prbs_chk_rules.en; 
        por_rx_prbs_chk_rules->prbs_mode                         = g_spica_prbs_chk_rules.prbs_mode;
        por_rx_prbs_chk_rules->prbs_inv                          = g_spica_prbs_chk_rules.prbs_inv;
        por_rx_prbs_chk_rules->prbs_pattern_lsb                  = g_spica_prbs_chk_rules.prbs_pattern_lsb;
        por_rx_prbs_chk_rules->prbs_pattern                      = g_spica_prbs_chk_rules.prbs_pattern;

        // rules specific to the host rx checker
        por_rx_prbs_chk_rules->hrx_advanced.auto_polarity_en     = g_spica_prbs_chk_rules.auto_polarity_en;  
        por_rx_prbs_chk_rules->hrx_advanced.auto_polarity_thresh = g_spica_prbs_chk_rules.auto_polarity_thresh;
        por_rx_prbs_chk_rules->hrx_advanced.pattern_mode         = g_spica_prbs_chk_rules.pattern_mode;
        por_rx_prbs_chk_rules->hrx_advanced.fixed_pat0           = g_spica_prbs_chk_rules.fixed_pat0;
        por_rx_prbs_chk_rules->hrx_advanced.fixed_pat1           = g_spica_prbs_chk_rules.fixed_pat1;
        por_rx_prbs_chk_rules->hrx_advanced.fixed_pat2           = g_spica_prbs_chk_rules.fixed_pat2;
        por_rx_prbs_chk_rules->hrx_advanced.fixed_pat3           = g_spica_prbs_chk_rules.fixed_pat3;
        por_rx_prbs_chk_rules->hrx_advanced.oos_thresh           = g_spica_prbs_chk_rules.oos_thresh; 

        // rules specific to the line rx checker
        por_rx_prbs_chk_rules->lrx_advanced.prbs_err_th_irq      = 4; 
        por_rx_prbs_chk_rules->lrx_advanced.prbs_auto_lock       = true; 
        por_rx_prbs_chk_rules->lrx_advanced.prbs_err_th_lock     = 4; 
        por_rx_prbs_chk_rules->lrx_advanced.prbs_cyc_th_lock     = 64; 
    }

    return status; 
}

void apply_custom_prbs_chk_rules(
    por_rx_prbs_chk_rules_t* por_rx_prbs_chk_rules, 
    spica_prbs_chk_rules_t* spica_prbs_chk_rules)
{
    // generic rx checker rules
    spica_prbs_chk_rules->en                    = por_rx_prbs_chk_rules->en;
    spica_prbs_chk_rules->prbs_mode             = por_rx_prbs_chk_rules->prbs_mode;
    spica_prbs_chk_rules->prbs_inv              = por_rx_prbs_chk_rules->prbs_inv;
    spica_prbs_chk_rules->prbs_pattern_lsb      = por_rx_prbs_chk_rules->prbs_pattern_lsb;
    spica_prbs_chk_rules->prbs_pattern          = por_rx_prbs_chk_rules->prbs_pattern;
                    
    // rules specific to the host rx checker
    spica_prbs_chk_rules->auto_polarity_en      = por_rx_prbs_chk_rules->hrx_advanced.auto_polarity_en;
    spica_prbs_chk_rules->auto_polarity_thresh  = por_rx_prbs_chk_rules->hrx_advanced.auto_polarity_thresh;
    spica_prbs_chk_rules->pattern_mode          = por_rx_prbs_chk_rules->hrx_advanced.pattern_mode;
    spica_prbs_chk_rules->fixed_pat0            = por_rx_prbs_chk_rules->hrx_advanced.fixed_pat0;
    spica_prbs_chk_rules->fixed_pat1            = por_rx_prbs_chk_rules->hrx_advanced.fixed_pat1;
    spica_prbs_chk_rules->fixed_pat2            = por_rx_prbs_chk_rules->hrx_advanced.fixed_pat2;
    spica_prbs_chk_rules->fixed_pat3            = por_rx_prbs_chk_rules->hrx_advanced.fixed_pat3;
    spica_prbs_chk_rules->oos_thresh            = por_rx_prbs_chk_rules->hrx_advanced.oos_thresh;
}

/*
 * Configure the Line or Host side PRBS checker
 */
inphi_status_t por_rx_prbs_chk_config(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_rx_prbs_chk_rules_t* por_rx_prbs_chk_rules)
{
    inphi_status_t status = INPHI_OK;

    if(!por_rx_prbs_chk_rules)
    {
        INPHI_CRIT("PRBS checker rules pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }
    
    //Internal method to apply custom chk rules
    apply_custom_prbs_chk_rules(por_rx_prbs_chk_rules, &g_spica_prbs_chk_rules);

    status = spica_prbs_chk_config(die, channel,
                                  (e_spica_intf)intf,
                                  &g_spica_prbs_chk_rules);

    return status;
}

/*
 * Extract the the Line or Host side PRBS checker status
 */
inphi_status_t por_rx_prbs_chk_status(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_rx_prbs_chk_status_t* chk_status)
{
    inphi_status_t status = INPHI_OK;

    if(!chk_status)
    {
        INPHI_CRIT("PRBS Checker status pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }
    
    //clear the struct
    INPHI_MEMSET(chk_status, 0, sizeof(por_rx_prbs_chk_status_t));
    
    spica_prbs_chk_status_t spica_chk_status;
    status = spica_prbs_chk_status(die, channel, 
                                  (e_spica_intf)intf,
                                   &spica_chk_status);
    if (INPHI_OK == status)
    {
        INPHI_MEMCPY(chk_status, &spica_chk_status, sizeof(spica_prbs_chk_status_t)); 
    }
    return status;
}

/*
 * Auto detect the HRX PRBS pattern, if any
 */
e_por_prbs_pat por_hrx_prbs_pat_auto_detect(
    uint32_t die,
    uint32_t channel,
    bool is_lsb)
{
    INPHI_PRINTF("API NOT supported in v%s\n",POR_API_VERSION);
    return 0;
}

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
/*
 * Find the BER
 */
inphi_status_t por_rx_prbs_ber(
    por_rx_prbs_chk_status_t *chk_status,
    double *ber,
    double *ber_lsb)
{
    if(!chk_status)
    {
        INPHI_CRIT("PRBS Checker status pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }
    return spica_prbs_chk_ber((spica_prbs_chk_status_t*)chk_status, ber, ber_lsb);
}
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/*
 * Print the Line/Host PRBS checker status
 */
inphi_status_t por_rx_prbs_chk_status_print(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_rx_prbs_chk_status_t* chk_status)
{

    if(!chk_status)
    {
        INPHI_CRIT("PRBS Checker status pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }
    return spica_prbs_chk_status_print(die, channel,
                                      (e_spica_intf)intf,
                                      (spica_prbs_chk_status_t*)chk_status);
}

/**
 * Returns the synthetic PRBS pattern
 */
const char* por_dbg_translate_synth_pat(
    e_por_prbs_pat pattern)
{
    return spica_prbs_translate_pat((e_spica_prbs_pat)pattern);
}

/*
 * Print the Line/Host PRBS checker status for all channels
 */
inphi_status_t por_rx_prbs_chk_status_query_all_print(
    uint32_t die,
    e_por_intf intf)
{
    inphi_status_t status = INPHI_OK;
    por_rx_prbs_chk_status_t chk_status[16];
    e_por_rx_prbs_mode prbs_mode = POR_PRBS_MODE_COMBINED;

    const char* intrface = "LRX";
    if(intf == POR_INTF_HRX)
    {
        intrface = "HRX";
    }

    /* collect all the check statuses */
    POR_FOR_CHANNEL_IN_CHANNELS(die, intf)
    {
        status |= por_rx_prbs_chk_status(die, channel, intf, &chk_status[channel]);
    }

    INPHI_NOTE("\n\n%s PRBS checker status of die: 0x%08x\n", intrface, die);
    INPHI_NOTE("%5s| %5s| %10s| %8s| %8s| %12s| %21s| %10s| %10s|",
               "| Ch#",
               "Mode",
               "LockStat",
               "Pattern",
               "Invert",
               "ErrBitCnt",
               "TotalBit",
               "BitCntSat",
               "FixPatSnc");
#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    INPHI_NOTE("%12s|", "BER");
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    INPHI_NOTE("%s", "\n+----+------+-----------+---------+---------+-------------+----------------------+-----------+-----------+");
#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    INPHI_NOTE("%12s", "------------+");
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
    INPHI_NOTE("\n");
    POR_FOR_CHANNEL_IN_CHANNELS(die, intf)
    {
        INPHI_NOTE("|  %2d| %5s| %10s| %8s| %8s| %12u| %21" PRIu64 "| %10s|",
                   channel,
                   chk_status[channel].prbs_mode == POR_PRBS_MODE_COMBINED ? "CMB" : "MSB",
                   chk_status[channel].prbs_lock ? "True" : "False",
                   por_dbg_translate_synth_pat(chk_status[channel].prbs_pattern),
                   chk_status[channel].prbs_inv ? "True" : "False",
                   chk_status[channel].prbs_error_bit_count,
                   chk_status[channel].prbs_total_bit_count,
                   chk_status[channel].prbs_total_bit_count_saturated ? "True" : "False");

        if (POR_INTF_HTX == intf || POR_INTF_HRX == intf)
        {
            INPHI_NOTE("%11s|", chk_status[channel].prbs_fixed_pat_sync ? "True" : "False");
        }
        else
        {
            INPHI_NOTE("%11s|", "N/A");
        }

        // if any channels prbs_mode is MSB/LSB then take note
        if (chk_status[channel].prbs_mode == POR_PRBS_MODE_MSB_LSB)
        {
            prbs_mode = POR_PRBS_MODE_MSB_LSB;
        }

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
        double ber;
        double ber_lsb;
        inphi_status_t tmp_status;
        tmp_status = por_rx_prbs_ber(&chk_status[channel], &ber, &ber_lsb);
        if (INPHI_OK == tmp_status)
        {
            INPHI_NOTE("%12.2e|", ber);
        }
        else
        {
            INPHI_NOTE("%12s|", "N/A");
        }
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

        INPHI_NOTE("\n");
    }

    // assume the mode is the same for all channels
    if (prbs_mode == POR_PRBS_MODE_MSB_LSB)
    {
        INPHI_NOTE("\n");

        INPHI_NOTE("%5s| %5s| %10s| %8s| %8s| %12s| %21s| %10s| %10s|",
                   "| Ch#",
                   "Mode",
                   "LockStat",
                   "Pattern",
                   "Invert",
                   "ErrBitCnt",
                   "TotalBit",
                   "BitCntSat",
                   "FixPatSnc");
#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
        INPHI_NOTE("%12s|", "BER");
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
        INPHI_NOTE("%s", "\n+----+------+-----------+---------+---------+-------------+----------------------+-----------+-----------+");
#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
        INPHI_NOTE("%12s", "------------+");
#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
        INPHI_NOTE("\n");

        POR_FOR_CHANNEL_IN_CHANNELS(die, intf)
        {
            INPHI_NOTE("|  %2d| %5s| %10s| %8s| %8s| %12u| %21" PRIu64 "| %10s|",
                       channel,
                       "LSB",
                       chk_status[channel].prbs_lock_lsb ? "True" : "False",
                       por_dbg_translate_synth_pat(chk_status[channel].prbs_pattern_lsb),
                       chk_status[channel].prbs_inv_lsb ? "True" : "False",
                       chk_status[channel].prbs_error_bit_count_lsb,
                       chk_status[channel].prbs_total_bit_count,
                       chk_status[channel].prbs_total_bit_count_saturated ? "True" : "False");

            if (POR_INTF_HTX == intf || POR_INTF_HRX == intf)
            {
                INPHI_NOTE("%11s|", chk_status[channel].prbs_fixed_pat_sync ? "True" : "False");
            }
            else
            {
                INPHI_NOTE("%11s|", "N/A");
            }

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
            double ber;
            double ber_lsb;
            inphi_status_t tmp_status;
            tmp_status = por_rx_prbs_ber(&chk_status[channel], &ber, &ber_lsb);
            if (INPHI_OK == tmp_status)
            {
                INPHI_NOTE("%12.2e|", ber_lsb);
            }
            else
            {
                INPHI_NOTE("%12s|", "N/A");
            }

#endif //defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

            INPHI_NOTE("\n");
        }
    }
    INPHI_NOTE("\n");

    return status;
}

/*
 *  Extract then print the Line or Host side PRBS checker status
 */
inphi_status_t por_rx_prbs_chk_status_dump(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_rx_prbs_chk_rules_t* chk_rules,
    uint16_t gate_time_sec,
    uint16_t n_times)
{
    inphi_status_t status = INPHI_OK;
    por_rx_prbs_chk_status_t chk_status;
    uint16_t i;

    if(!chk_rules)
    {
        INPHI_NOTE("PRBS Checker rules pointer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    status |= por_rx_prbs_chk_config(die, channel, intf, chk_rules);
    status |= por_rx_prbs_chk_status(die, channel, intf, &chk_status);

    for (i = 0; i < n_times; i++)
    {
        INPHI_MDELAY(gate_time_sec * 1000);
        status |= por_rx_prbs_chk_status(die, channel, intf, &chk_status);
        status |= por_rx_prbs_chk_status_print(die, channel, intf, &chk_status);

    }

    return status;
}

inphi_status_t por_rx_prbs_chk_summary_dump(
    uint32_t                  die,
    e_por_intf                intf,
    por_rx_prbs_chk_status_t* chk_status,
    uint32_t                  start,
    uint32_t                  end)
{
    (void)die; // Unused right now
    inphi_status_t status = INPHI_OK;

    const char* title = "LRX PRBS Statistics";
    if(intf == POR_INTF_HRX)
    {
        title = "HRX PRBS Statistics";
    }

    INPHI_NOTE("+---------------------------------------------------------------------------\n"
                 "| %s\n"
                 "+----+-------+--------------------------------------------------------------\n"
                 "|Ch# | Mode  | PRBS Status\n"
                 "+----+-------+--------------------------------------------------------------\n", title);

    for(uint32_t channel = start; channel <= end; channel++)
    {
        INPHI_NOTE("| %2d |", channel);

        // Combined Mode
        if(chk_status[channel].prbs_mode == POR_PRBS_MODE_COMBINED)
        {
            INPHI_NOTE("Combine|");

            // Flag an error if PRBS is not locked
            if(chk_status[channel].prbs_lock)
            {
                INPHI_NOTE(" Locked (%s), ", por_dbg_translate_synth_pat(chk_status[channel].prbs_pattern));
            }
            else
            {
                INPHI_NOTE(" Unlocked, ");
            }

            uint32_t prbs_error_bit_count = chk_status[channel].prbs_error_bit_count;

            INPHI_NOTE(" Errors = %u", prbs_error_bit_count);
            INPHI_NOTE("\n");
        }
        // MSB/LSB
        else
        {
            INPHI_NOTE("MSB/LSB|");

            // Flag an error if PRBS is not locked
            if(chk_status[channel].prbs_lock && chk_status[channel].prbs_lock_lsb)
            {
                INPHI_NOTE(" Locked (LSB=%s,MSB=%s), ",
                             por_dbg_translate_synth_pat(chk_status[channel].prbs_pattern_lsb),
                             por_dbg_translate_synth_pat(chk_status[channel].prbs_pattern));
            }
            else
            {
                INPHI_NOTE(" Unlocked, ");
            }

            uint32_t prbs_error_bit_count_msb = chk_status[channel].prbs_error_bit_count;
            uint32_t prbs_error_bit_count_lsb = chk_status[channel].prbs_error_bit_count_lsb;

            INPHI_NOTE(" Errors (MSB = %u, LSB = %u)",
                         prbs_error_bit_count_msb,
                         prbs_error_bit_count_lsb);

            INPHI_NOTE("\n");
        }
    }

    INPHI_NOTE("+----+-------+--------------------------------------------------------------\n");

    return status;
}

#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/** @file por.c
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

void por_set_callback_for_lock(
    por_callback_lock callback)
{
    spica_set_callback_for_lock((spica_callback_lock)(callback));
}

void por_set_callback_for_unlock(
    por_callback_lock callback)
{
    spica_set_callback_for_unlock((spica_callback_unlock)(callback));
}

/* Lock the device for exclusive access */
inphi_status_t por_lock(
    uint32_t die)
{
    return spica_lock(die);
}

/* Unlock the device for exclusive access */
inphi_status_t por_unlock(
    uint32_t die)
{
    return spica_unlock(die);
}

/* Get the API version information */
inphi_status_t por_version(
    char*    buffer, 
    uint32_t buffer_len)
{
    if(!buffer)
    {
        INPHI_CRIT("ERROR: buffer cannot be NULL!\n");
        return INPHI_ERROR;
    }

    INPHI_STRNCPY(buffer,
            "API Version " POR_API_VERSION "\n"
            "API Built on " POR_API_BUILD_DATE "\n",
            buffer_len); 

    return INPHI_OK;
}

/* Get the firmware version information */
inphi_status_t por_version_firmware(
    uint32_t die,
    char*    buffer, 
    uint32_t buffer_len)
{
    return spica_version_firmware(die,
                                  buffer,
                                  buffer_len);
}

void por_default_rules_populate(uint32_t die, 
                                spica_rules_t* spica_rules,
                                por_rules_t*   por_rules)
{
    por_rules->fw_dwld_timeout = spica_rules->fw_dwld_timeout; 

    // By default warn if the f/w version encountered does not
    // match the version the API was compiled with.
    por_rules->fw_warn_if_mismatched = spica_rules->fw_warn_if_mismatched;
    por_rules->driver_type_override  = spica_rules->driver_type_override;
 
    por_rules->host_baud_rate = spica_rules->srx[1].baud_rate;
    por_rules->line_baud_rate = spica_rules->orx[1].baud_rate;
    por_rules->ieee_demap     = true;
    por_rules->ref_clk        = 156250;

    por_rules->lrx_los_dsrt_ctrl_startup  = spica_rules->lrx_los_dsrt_ctrl_startup;
    por_rules->lrx_los_asrt_ctrl_startup  = spica_rules->lrx_los_asrt_ctrl_startup;
    por_rules->lrx_los_asrt_ctrl_datamode = spica_rules->lrx_los_asrt_ctrl_datamode;

    por_rules->lrx_qc.snr_threshold_mm_enter = spica_rules->lrx_qc.snr_threshold_mm_enter;
    por_rules->lrx_qc.snr_threshold_mm_exit  = spica_rules->lrx_qc.snr_threshold_mm_exit;
    por_rules->lrx_qc.slc_err_limit          = spica_rules->lrx_qc.slc_err_limit;

    por_rules->advanced.lrx_ddlf_en              = spica_rules->advanced.lrx_ddlf_en;
    por_rules->advanced.lrx_low_loss_det_en      = spica_rules->advanced.lrx_low_loss_det_en;
    por_rules->advanced.lrx_double_restart_dis   = spica_rules->advanced.lrx_double_restart_dis;
    por_rules->advanced.lrx_cid_losd_det_en      = spica_rules->advanced.lrx_cid_losd_det_en;

    //LRX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
    {
        por_rules->lrx[channel].channel_enable       = spica_rules->orx[channel].channel_enable;
        por_rules->lrx[channel].signalling           = spica_rules->orx[channel].signalling;
        por_rules->lrx[channel].baud_rate            = spica_rules->orx[channel].baud_rate;
        por_rules->lrx[channel].ieee_demap           = spica_rules->orx[channel].ieee_demap;
        por_rules->lrx[channel].gray_mapping         = spica_rules->orx[channel].gray_mapping;
        por_rules->lrx[channel].sdt_dsp_en           = spica_rules->orx[channel].sdt_dsp_en;
        por_rules->lrx[channel].los_dsp_en           = spica_rules->orx[channel].los_dsp_en;
        por_rules->lrx[channel].vga_tracking_en      = true;
        por_rules->lrx[channel].invert_chan          = spica_rules->orx[channel].invert_chan;
        por_rules->lrx[channel].six_bit_mode         = spica_rules->orx[channel].six_bit_mode;
        por_rules->lrx[channel].force_mission_mode   = spica_rules->orx[channel].force_mission_mode;
        por_rules->lrx[channel].restart_on_los_dis   = spica_rules->orx[channel].restart_on_los_dis;
        por_rules->lrx[channel].ffe_const_diff_en    = spica_rules->orx[channel].ffe_const_diff_en;
        por_rules->lrx[channel].bw_idx_max           = spica_rules->orx[channel].bw_idx_max;
        por_rules->lrx[channel].vga1_tracking_period = spica_rules->orx[channel].vga1_tracking_period;
        por_rules->lrx[channel].alg1_dis             = spica_rules->orx[channel].alg1_dis;
        por_rules->lrx[channel].alg2_dis             = spica_rules->orx[channel].alg2_dis;
        por_rules->lrx[channel].alg3_dis             = spica_rules->orx[channel].alg3_dis;
        por_rules->lrx[channel].alg4_dis             = spica_rules->orx[channel].alg4_dis;
        por_rules->lrx[channel].qc_all_dis           = spica_rules->orx[channel].qc_all_dis;
        por_rules->lrx[channel].qc_hist_dis          = spica_rules->orx[channel].qc_hist_dis;
        por_rules->lrx[channel].qc_slc_dis           = spica_rules->orx[channel].qc_slc_dis;
        por_rules->lrx[channel].qc_snr_dis           = spica_rules->orx[channel].qc_snr_dis;
          
    }

    //HRX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_MEMCPY(&por_rules->hrx[channel], &spica_rules->srx[channel], 
                        sizeof(por_hrx_rules_t));
    }

    //LTX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        // set the default Tx rules
        por_rules->ltx[channel].channel_enable = spica_rules->otx[channel].channel_enable;
        por_rules->ltx[channel].signalling     = spica_rules->otx[channel].signalling;
        por_rules->ltx[channel].squelch_lock   = spica_rules->otx[channel].squelch_lock;
        por_rules->ltx[channel].baud_rate      = spica_rules->otx[channel].baud_rate;
        por_rules->ltx[channel].fll_mode       = spica_rules->otx[channel].fll_mode;
        por_rules->ltx[channel].ieee_demap     = spica_rules->otx[channel].ieee_demap;
        por_rules->ltx[channel].gray_mapping   = spica_rules->otx[channel].gray_mapping;
        por_rules->ltx[channel].invert_chan    = spica_rules->otx[channel].invert_chan;
        por_rules->ltx[channel].lut_mode       = spica_rules->otx[channel].lut_mode;
        por_rules->ltx[channel].swing          = spica_rules->otx[channel].swing;
        por_rules->ltx[channel].fir_taps[0]    = spica_rules->otx[channel].fir_taps[0];
        por_rules->ltx[channel].fir_taps[1]    = spica_rules->otx[channel].fir_taps[1];
        por_rules->ltx[channel].fir_taps[2]    = spica_rules->otx[channel].fir_taps[2];
        por_rules->ltx[channel].fir_taps[3]    = spica_rules->otx[channel].fir_taps[3];
        por_rules->ltx[channel].fir_taps[4]    = spica_rules->otx[channel].fir_taps[4];
        por_rules->ltx[channel].fir_taps[5]    = spica_rules->otx[channel].fir_taps[5];
        por_rules->ltx[channel].fir_taps[6]    = spica_rules->otx[channel].fir_taps[6];
        por_rules->ltx[channel].inner_eye1     = spica_rules->otx[channel].inner_eye1;
        por_rules->ltx[channel].inner_eye2     = spica_rules->otx[channel].inner_eye2;
    }

    //HTX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        por_rules->htx[channel].channel_enable = spica_rules->stx[channel].channel_enable;
        por_rules->htx[channel].signalling     = spica_rules->stx[channel].signalling;
        por_rules->htx[channel].squelch_lock   = spica_rules->stx[channel].squelch_lock;
        por_rules->htx[channel].baud_rate      = spica_rules->stx[channel].baud_rate;
        por_rules->htx[channel].fll_mode       = spica_rules->stx[channel].fll_mode;
        por_rules->htx[channel].gray_mapping   = spica_rules->stx[channel].gray_mapping;
        por_rules->htx[channel].ieee_demap     = spica_rules->stx[channel].ieee_demap;
        por_rules->htx[channel].invert_chan    = spica_rules->stx[channel].invert_chan;
        por_rules->htx[channel].lut_mode       = spica_rules->stx[channel].lut_mode;
        por_rules->htx[channel].swing          = spica_rules->stx[channel].swing;
        por_rules->htx[channel].fir_taps[0]    = spica_rules->stx[channel].fir_taps[0];
        por_rules->htx[channel].fir_taps[1]    = spica_rules->stx[channel].fir_taps[1];
        por_rules->htx[channel].fir_taps[2]    = spica_rules->stx[channel].fir_taps[2];
        por_rules->htx[channel].fir_taps[3]    = spica_rules->stx[channel].fir_taps[3];
        por_rules->htx[channel].fir_taps[4]    = spica_rules->stx[channel].fir_taps[4];
        por_rules->htx[channel].fir_taps[5]    = spica_rules->stx[channel].fir_taps[5];
        por_rules->htx[channel].fir_taps[6]    = spica_rules->stx[channel].fir_taps[6];
        por_rules->htx[channel].inner_eye1     = spica_rules->stx[channel].inner_eye1;
        por_rules->htx[channel].inner_eye2     = spica_rules->stx[channel].inner_eye2;
    }
    //Advanced Rules
    por_rules->advanced.breakout   = (por_rules->fec_mode == POR_FEC_BYPASS);
    
    //XBAR LTX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        for(uint8_t j=0; j<sizeof(por_rules->ltx_xbar_src_chan[0])/sizeof(por_rules->ltx_xbar_src_chan[0][0]); j++)
        {
            por_rules->ltx_xbar_src_chan[channel][j] = spica_rules->otx_xbar_src_chan[channel][j];
        }
        por_rules->ltx_clk_xbar[channel] = spica_rules->otx_clk_xbar[channel];
    }

    //XBAR HTX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        for(uint8_t j=0; j<sizeof(por_rules->htx_xbar_src_chan[0])/sizeof(por_rules->htx_xbar_src_chan[0][0]); j++)
        {
            por_rules->htx_xbar_src_chan[channel][j] = spica_rules->stx_xbar_src_chan[channel][j];
        }
        por_rules->htx_clk_xbar[channel] = spica_rules->stx_clk_xbar[channel];
    }

}

/* setup the default rules for each op_mode */
inphi_status_t por_rules_set_default(
    uint32_t               die,
    e_por_operational_mode op_mode,
    e_por_protocol_mode    protocol_mode,
    e_por_fec_mode         fec_mode,
    por_rules_t*           rules)
{
    inphi_status_t status = INPHI_OK;

    if(!rules)
    {
        INPHI_CRIT("rules cannot be NULL!\n");
        return INPHI_ERROR;
    }
    if(protocol_mode >= POR_MODE_PROT_END)
    {
        INPHI_CRIT("Invalid protocol_mode %d\n", protocol_mode);
        return INPHI_ERROR;
    }
    if(fec_mode >= POR_FEC_MODE_END)
    {
        INPHI_CRIT("Invalid fec_mode %d\n", fec_mode);
        return INPHI_ERROR;
    }

    //Unused in PG3
    (void)fec_mode;

    spica_rules_t spica_rules;

    // reset the both entire rules structures
    INPHI_MEMSET(rules, 0, sizeof(por_rules_t));
    INPHI_MEMSET(&spica_rules, 0, sizeof(spica_rules_t));
    
    // Get the package type from the encoded die parameter
    rules->package_type = por_package_get_type(die);
    rules->operational_mode = op_mode;
    rules->protocol_mode = protocol_mode;
    
    spica_bundle_rules_t bundle_rules;
    status |= spica_bundle_default_set(die, &bundle_rules);

    if (INPHI_OK == status) 
    {
        status |= spica_bundle_cfg(&bundle_rules);
    }

    if (INPHI_OK == status)
    {
        status |= spica_rules_default_set(die,
                                         (e_spica_operational_mode)op_mode, 
                                         (e_spica_protocol_mode)protocol_mode,
                                         &spica_rules);
        if (INPHI_OK == status)
        {
            por_default_rules_populate(die, &spica_rules, rules);
        }
    }

    return status;
}

inphi_status_t por_tx_rules_set_default(
    por_tx_rules_t*  tx_rules)
{
    INPHI_WARN("API:por_rules_set_default() covers this in v%s",
                POR_API_VERSION);
    return INPHI_OK; 
}

inphi_status_t por_check_rules(
    uint32_t     die,
    por_rules_t* rules)
{
    INPHI_WARN("API NOT supported in v%s", POR_API_VERSION);
    return INPHI_OK; 
}

inphi_status_t por_tx_check_rules(
    uint32_t     die,
    uint32_t     channel,
    e_por_intf   intf,
    por_tx_rules_t* tx_rules)
{
    INPHI_WARN("API NOT supported in v%s", POR_API_VERSION);
    return INPHI_OK; 
}

inphi_status_t por_soft_reset(
    uint32_t die)
{
    INPHI_WARN("API NOT supported in v%s", POR_API_VERSION);
    return INPHI_OK; 
}

/**
 * This is an internal method used to copy the por_rules to spica_rules 
 */
void copy_rules(uint32_t die, por_rules_t* por_rules, spica_rules_t* spica_rules)
{    
    // Get the package type from the encoded die parameter
    spica_rules->package_type       = por_rules->package_type;
    spica_rules->operational_mode   = por_rules->operational_mode;
    spica_rules->protocol_mode      = por_rules->protocol_mode;

    spica_rules->driver_type_override       = por_rules->driver_type_override;
    
    spica_rules->lrx_los_dsrt_ctrl_startup   = por_rules->lrx_los_dsrt_ctrl_startup;
    spica_rules->lrx_los_asrt_ctrl_startup   = por_rules->lrx_los_asrt_ctrl_startup;
    spica_rules->lrx_los_asrt_ctrl_datamode  = por_rules->lrx_los_asrt_ctrl_datamode;

    spica_rules->lrx_qc.snr_threshold_mm_enter = por_rules->lrx_qc.snr_threshold_mm_enter;
    spica_rules->lrx_qc.snr_threshold_mm_exit  = por_rules->lrx_qc.snr_threshold_mm_exit;
    spica_rules->lrx_qc.slc_err_limit          = por_rules->lrx_qc.slc_err_limit;

    spica_rules->advanced.lrx_ddlf_en              = por_rules->advanced.lrx_ddlf_en;
    spica_rules->advanced.lrx_low_loss_det_en      = por_rules->advanced.lrx_low_loss_det_en;
    spica_rules->advanced.lrx_double_restart_dis   = por_rules->advanced.lrx_double_restart_dis;
    spica_rules->advanced.lrx_cid_losd_det_en      = por_rules->advanced.lrx_cid_losd_det_en;

    //LRX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
    {
        spica_rules->orx[channel].channel_enable       = por_rules->lrx[channel].channel_enable;
        spica_rules->orx[channel].signalling           = por_rules->lrx[channel].signalling;
        spica_rules->orx[channel].baud_rate            = 
              (por_rules->lrx[channel].baud_rate)? por_rules->lrx[channel].baud_rate:por_rules->line_baud_rate;
        spica_rules->orx[channel].ieee_demap           = por_rules->ieee_demap|por_rules->lrx[channel].ieee_demap;
        spica_rules->orx[channel].gray_mapping         = por_rules->lrx[channel].gray_mapping;
        spica_rules->orx[channel].invert_chan          = por_rules->lrx[channel].invert_chan;
        spica_rules->orx[channel].sdt_dsp_en           = por_rules->lrx[channel].sdt_dsp_en;
        spica_rules->orx[channel].los_dsp_en           = por_rules->lrx[channel].los_dsp_en;
        spica_rules->orx[channel].six_bit_mode         = por_rules->lrx[channel].six_bit_mode;
        spica_rules->orx[channel].force_mission_mode   = por_rules->lrx[channel].force_mission_mode;
        spica_rules->orx[channel].restart_on_los_dis   = por_rules->lrx[channel].restart_on_los_dis;
        spica_rules->orx[channel].ffe_const_diff_en    = por_rules->lrx[channel].ffe_const_diff_en;
        spica_rules->orx[channel].bw_idx_max           = por_rules->lrx[channel].bw_idx_max;
        spica_rules->orx[channel].vga1_tracking_period = por_rules->lrx[channel].vga1_tracking_period;
        spica_rules->orx[channel].alg1_dis             = por_rules->lrx[channel].alg1_dis;
        spica_rules->orx[channel].alg2_dis             = por_rules->lrx[channel].alg2_dis;
        spica_rules->orx[channel].alg3_dis             = por_rules->lrx[channel].alg3_dis;
        spica_rules->orx[channel].alg4_dis             = por_rules->lrx[channel].alg4_dis;
        spica_rules->orx[channel].qc_all_dis           = por_rules->lrx[channel].qc_all_dis;
        spica_rules->orx[channel].qc_hist_dis          = por_rules->lrx[channel].qc_hist_dis;
        spica_rules->orx[channel].qc_slc_dis           = por_rules->lrx[channel].qc_slc_dis;
        spica_rules->orx[channel].qc_snr_dis           = por_rules->lrx[channel].qc_snr_dis;
    }

    //HRX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_MEMCPY(&spica_rules->srx[channel], &por_rules->hrx[channel],
                        sizeof(por_hrx_rules_t));
        spica_rules->srx[channel].ieee_demap     = por_rules->ieee_demap|por_rules->hrx[channel].ieee_demap;
        spica_rules->srx[channel].baud_rate      = 
                (por_rules->hrx[channel].baud_rate)? por_rules->hrx[channel].baud_rate:por_rules->host_baud_rate;
    }

    //LTX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        // set the default Tx rules
        spica_rules->otx[channel].channel_enable = por_rules->ltx[channel].channel_enable;
        spica_rules->otx[channel].squelch_lock   = por_rules->ltx[channel].squelch_lock;
        spica_rules->otx[channel].signalling     = por_rules->ltx[channel].signalling;
        spica_rules->otx[channel].baud_rate      = 
              (por_rules->ltx[channel].baud_rate)? por_rules->ltx[channel].baud_rate:por_rules->line_baud_rate;
        spica_rules->otx[channel].fll_mode       = por_rules->ltx[channel].fll_mode;
        spica_rules->otx[channel].lut_mode       = por_rules->ltx[channel].lut_mode;
        spica_rules->otx[channel].ieee_demap     = por_rules->ieee_demap|por_rules->ltx[channel].ieee_demap;
        spica_rules->otx[channel].gray_mapping   = por_rules->ltx[channel].gray_mapping;
        spica_rules->otx[channel].invert_chan    = por_rules->ltx[channel].invert_chan;
        spica_rules->otx[channel].swing          = por_rules->ltx[channel].swing;
        for (uint8_t n=0;n<7;n++)
        {
            spica_rules->otx[channel].fir_taps[n]= por_rules->ltx[channel].fir_taps[n];
        }
        spica_rules->otx[channel].inner_eye1      = por_rules->ltx[channel].inner_eye1;
        spica_rules->otx[channel].inner_eye2      = por_rules->ltx[channel].inner_eye2;
        spica_rules->otx[channel].dfe_precoder_en = por_rules->ltx[channel].dfe_precoder_en;
    }

    //HTX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        spica_rules->stx[channel].channel_enable = por_rules->htx[channel].channel_enable;
        spica_rules->stx[channel].squelch_lock   = por_rules->htx[channel].squelch_lock;
        spica_rules->stx[channel].signalling     = por_rules->htx[channel].signalling;
        spica_rules->stx[channel].baud_rate      = 
              (por_rules->htx[channel].baud_rate)? por_rules->htx[channel].baud_rate:por_rules->host_baud_rate;
        spica_rules->stx[channel].fll_mode       = por_rules->htx[channel].fll_mode;
        spica_rules->stx[channel].lut_mode       = por_rules->htx[channel].lut_mode;
        spica_rules->stx[channel].gray_mapping   = por_rules->htx[channel].gray_mapping;
        spica_rules->stx[channel].ieee_demap     = por_rules->ieee_demap|por_rules->htx[channel].ieee_demap;
        spica_rules->stx[channel].invert_chan    = por_rules->htx[channel].invert_chan;
        spica_rules->stx[channel].swing          = por_rules->htx[channel].swing;
        for (uint8_t n=0;n<7;n++)
        {
            spica_rules->stx[channel].fir_taps[n]= por_rules->htx[channel].fir_taps[n];
        }
        spica_rules->stx[channel].inner_eye1      = por_rules->htx[channel].inner_eye1;
        spica_rules->stx[channel].inner_eye2      = por_rules->htx[channel].inner_eye2;
        spica_rules->stx[channel].dfe_precoder_en = por_rules->htx[channel].dfe_precoder_en;
    }

    //XBAR LTX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        for(uint8_t j=0; j<sizeof(por_rules->ltx_xbar_src_chan[0])/sizeof(por_rules->ltx_xbar_src_chan[0][0]); j++)
        {
            spica_rules->otx_xbar_src_chan[channel][j] = por_rules->ltx_xbar_src_chan[channel][j];
        }
        if(por_rules->advanced.breakout)
        {
            spica_rules->otx_clk_xbar[channel] = por_rules->ltx_clk_xbar[channel];
        }
        else 
        {
            spica_rules->otx_clk_xbar[channel] = 1;
        }
    }

    //XBAR HTX Rules
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        for(uint8_t j=0; j<sizeof(por_rules->htx_xbar_src_chan[0])/sizeof(por_rules->htx_xbar_src_chan[0][0]); j++)
        {
            spica_rules->stx_xbar_src_chan[channel][j] = por_rules->htx_xbar_src_chan[channel][j];
        }
        if(por_rules->advanced.breakout)
        {
            spica_rules->stx_clk_xbar[channel] = por_rules->htx_clk_xbar[channel];
        }
        else 
        {
            spica_rules->stx_clk_xbar[channel] = 1;
        }
    }
    
}

/*
 * Reset the device to have it ready for any user config
 */
inphi_status_t por_init(
    uint32_t die,
    por_rules_t* rules)
{
    inphi_status_t status = INPHI_OK;
    e_por_package_type package = por_package_get_type(die);
    
    if ((package != POR_PACKAGE_TYPE_EML_12x13) &&
        (package != POR_PACKAGE_TYPE_EML_12x13_REV1) &&
        (package != POR_PACKAGE_TYPE_STD_10x13))
    {
        INPHI_CRIT("NOT a PG3 Device!\n");
        return INPHI_ERROR;
    }

    spica_rules_t spica_rules;

    // Copy por_rules_t to spica_rules_t
    copy_rules(die, rules, &spica_rules);

    status = spica_init(die, &spica_rules);
    return status;
}

/*
 * This method is used to put the Porrima device into operational
 * state. This method MUST be preceded by a call to por_init.
 */
inphi_status_t por_enter_operational_state(
    uint32_t die,
    por_rules_t* rules)
{
    spica_rules_t spica_rules;

    // Copy por_rules_t to spica_rules_t
    copy_rules(die, rules, &spica_rules);

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
    if (rules->show_debug_info)
    {
        por_dbg_dump_rules(die, rules);
    }
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

    return spica_enter_operational_state(die, &spica_rules);
}

/*
 * Is the designated interface of a channel in the locked state
 */
bool por_channel_is_link_ready(
    uint32_t        die,
    uint32_t        channel,
    e_por_intf      intf)
{
    return spica_channel_is_link_ready(die, channel, (e_spica_intf)intf);
}

/*
 * Wait for a channels 4 interfaces ie LRX,LTX,HRX and HTX to be in the locked state
 */
inphi_status_t por_channel_wait_for_link_ready(
    uint32_t   die,
    uint32_t   channel,
    e_por_intf intf,
    uint32_t   timeout_in_usecs)
{
    return spica_channel_wait_for_link_ready(die,
                                             channel,
                                            (e_spica_intf)intf,
                                             timeout_in_usecs);
}

/*
 * Wait for all channels to be in the receive ready state
 */
inphi_status_t por_wait_for_link_ready(
    uint32_t   die,
    uint32_t   timeout_in_usecs)
{
    return spica_wait_for_link_ready(die, timeout_in_usecs);
}

bool por_is_fw_running_ok(
    uint32_t die)
{
    return spica_is_fw_running_ok(die);
}

inphi_status_t por_link_status_query(
    uint32_t die,
    por_link_status_t* link_status)
{
    inphi_status_t status = INPHI_OK;

    /* pre-set the status  */
    INPHI_MEMSET(link_status, 0, sizeof(*link_status));

    spica_link_status_t sls;
    status = spica_link_status_query(die, &sls);

    if (INPHI_OK == status)
    {
        //populate the porrima link status
        link_status->fw_lock = sls.fw_lock;

        //HRX        
        POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
        {
            link_status->hrx_sdt[channel]           = sls.hrx_sdt[channel];
            link_status->hrx_vco_lock[channel]      = sls.hrx_vco_lock[channel];
            link_status->hrx_cdr_lock[channel]      = sls.hrx_cdr_lock[channel];
            link_status->hrx_fw_lock[channel]       = sls.hrx_fw_lock[channel];
            link_status->hrx_reset_cnt[channel]     = sls.hrx_reset_cnt[channel];
            link_status->hrx_pll_fsm_state[channel] = sls.hrx_pll_fsm_state[channel];
            link_status->hrx_fsm_state[channel]     = sls.hrx_fsm_state[channel];
        }
            
        //HTX        
        POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
        {
            link_status->htx_pll_lock[channel]      = sls.htx_pll_lock[channel];
            link_status->htx_fw_lock[channel]       = sls.htx_fw_lock[channel];
            link_status->htx_reset_cnt[channel]     = sls.htx_reset_cnt[channel];
            link_status->htx_pll_fsm_state[channel] = sls.htx_pll_fsm_state[channel];
            link_status->htx_fsm_state[channel]     = sls.htx_fsm_state[channel];
        }

        //LRX        
        POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
        {
            link_status->lrx_sdt[channel]           = sls.orx_sdt[channel];
            link_status->lrx_dsp_ready[channel]     = sls.orx_dsp_ready[channel];
            link_status->lrx_pll_lock[channel]      = sls.orx_pll_lock[channel];
            link_status->lrx_fw_lock[channel]       = sls.orx_fw_lock[channel];
            link_status->lrx_pll_fsm_state[channel] = sls.orx_pll_fsm_state[channel];
            link_status->lrx_fsm_state[channel]     = sls.orx_fsm_state[channel];
            link_status->lrx_reset_cnt[channel]     = sls.orx_reset_cnt[channel];
        }

        //LTX        
        POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
        {
            link_status->ltx_pll_lock[channel]      = sls.otx_pll_lock[channel];
            link_status->ltx_fw_lock[channel]       = sls.otx_fw_lock[channel];
            link_status->ltx_reset_cnt[channel]     = sls.otx_reset_cnt[channel];
            link_status->ltx_pll_fsm_state[channel] = sls.otx_pll_fsm_state[channel];
            link_status->ltx_fsm_state[channel]     = sls.otx_fsm_state[channel];
        }
    }

    return status; 
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS == 1)
inphi_status_t por_link_status_print(
    uint32_t die,
    por_link_status_t* link_status)
{
    inphi_status_t status = INPHI_OK;

    INPHI_NOTE("Link Status for die 0x%08x\n", die);
    INPHI_NOTE("+-----------------------------------------------------------------------------------+\n");
    INPHI_NOTE("|  TOP LEVEL                                                                        |\n");
    INPHI_NOTE("|  FW Lock        %s                                                                 |\n", link_status->fw_lock ? "Y" : ".");
    INPHI_NOTE("+-----------------------------------------+-----------------------------------------+\n");

    INPHI_NOTE("|  HTX                                    |  HRX                                    |\n");
    INPHI_NOTE("|  Channel        1  2  3  4  5  6  7  8  |  Channel        1  2  3  4  5  6  7  8  |\n");
    INPHI_NOTE("|                 ----------------------  |                 ----------------------  |\n");

    // ------------------------------ HTX/HRX BLOCKS ---------------------------------------
// HTX - LINE1
    INPHI_NOTE("|  PLL Lock       ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("%s  ", link_status->htx_pll_lock[channel] ? "Y" : ".");
    }

// HRX - LINE1
    INPHI_NOTE("|  Signal Detect  ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_NOTE("%s  ", link_status->hrx_sdt[channel] ? "Y" : ".");
    }
    INPHI_NOTE("|\n");

// HTX - LINE2
    INPHI_NOTE("|  PLL FSM State ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("%2x ", link_status->htx_pll_fsm_state[channel]);
    }

// HRX - LINE2
    INPHI_NOTE(" |  PLL FSM State ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_NOTE("%2x ", link_status->hrx_pll_fsm_state[channel]);
    }
    INPHI_NOTE(" |\n");

// HTX - LINE3
    INPHI_NOTE("|  FSM State     ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("%2x ", link_status->htx_fsm_state[channel]);
    }

// HRX - LINE3
    INPHI_NOTE(" |  FSM State     ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_NOTE("%2x ", link_status->hrx_fsm_state[channel]);
    }
    INPHI_NOTE(" |\n");

// HTX - LINE4
    INPHI_NOTE("|  FW Lock        ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("%s  ", link_status->htx_fw_lock[channel] ? "Y" : ".");
    }

// HRX - LINE4
    INPHI_NOTE("|  CDR Lock       ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_NOTE("%s  ", link_status->hrx_cdr_lock[channel] ? "Y" : ".");
    }
    INPHI_NOTE("|\n");

// HTX - LINE5
    INPHI_NOTE("|  Reset Count    ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("%02x ", link_status->htx_reset_cnt[channel]);
    }

// HRX - LINE5
    INPHI_NOTE("|  FW Lock        ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_NOTE("%s  ", link_status->hrx_fw_lock[channel] ? "Y" : ".");
    }
    INPHI_NOTE("|\n");

// HTX - LINE6
    INPHI_NOTE("|                                         ");
// HRX - LINE6
    INPHI_NOTE("|  Reset Count    ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_NOTE("%02x ", link_status->hrx_reset_cnt[channel]);
    }
    INPHI_NOTE("|\n");

 // HTX - LINE7
    INPHI_NOTE("|                                         |                                         |\n");

        INPHI_NOTE("+-----------------------------------------+-----------------------------------------+\n");
        INPHI_NOTE("|  LRX                                    |  LTX                                    |\n");
        INPHI_NOTE("|  Channel        1  2  3  4              |  Channel        1  2  3  4              |\n");
        INPHI_NOTE("|                 ----------              |                 ----------              |\n");

// LRX - LINE1
    INPHI_NOTE("|  Signal Detect  ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
    {
        INPHI_NOTE("%s  ", link_status->lrx_sdt[channel] ? "Y" : ".");
    }
    INPHI_NOTE("            ");

//LTX - LINE1
    INPHI_NOTE("|  PLL Lock       ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("%s  ", link_status->ltx_pll_lock[channel] ? "Y" : ".");
    }
    INPHI_NOTE("            |\n");

// LRX - LINE2
    INPHI_NOTE("|  PLL Lock       ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
    {
        INPHI_NOTE("%s  ", link_status->lrx_pll_lock[channel] ? "Y" : ".");
    }
    INPHI_NOTE("            ");

// LTX - LINE2
    INPHI_NOTE("|  FW Lock        ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("%s  ", link_status->ltx_fw_lock[channel] ? "Y" : ".");
    }
    INPHI_NOTE("            |\n");

// LRX - LINE3
    INPHI_NOTE("|  FW Lock        ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
    {
        INPHI_NOTE("%s  ", link_status->lrx_fw_lock[channel] ? "Y" : ".");
    }
    INPHI_NOTE("            |");

// LTX - LINE3
    INPHI_NOTE("  PLL FSM State ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("%2x ", link_status->ltx_pll_fsm_state[channel]);
    }
    INPHI_NOTE("             |\n");

// LRX - LINE4
    INPHI_NOTE("|  PLL FSM State ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
    {
        INPHI_NOTE("%2x ", link_status->lrx_pll_fsm_state[channel]);
    }
    INPHI_NOTE("             ");

// LTX - LINE4
    INPHI_NOTE("|  FSM State     ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("%2x ", link_status->ltx_fsm_state[channel]);
    }
    INPHI_NOTE("             |\n");

// LRX - LINE5
    INPHI_NOTE("|  FSM State     ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
    {
        INPHI_NOTE("%2x ", link_status->lrx_fsm_state[channel]);
    }
    INPHI_NOTE("             |");

// LTX - LINE5
    INPHI_NOTE("  Reset Count    ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("%02x ", link_status->ltx_reset_cnt[channel]);
    }
    INPHI_NOTE("            |\n");

// LRX - LINE6
    INPHI_NOTE("|  Reset Count    ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
    {
        INPHI_NOTE("%02x ", link_status->lrx_reset_cnt[channel]);
    }
    INPHI_NOTE("            |");

// LTX - LINE6
    INPHI_NOTE("                                         |\n");

    INPHI_NOTE("|                                         |                                         |\n");
    INPHI_NOTE("+-----------------------------------------+-----------------------------------------+\n");
    INPHI_NOTE("Legend: Y=yes, .=no\n");

    return status;

}

/*
 * This method may be called to query then print the current link status
 * of the interfaces of the device.
 */
inphi_status_t por_link_status_query_dump(
    uint32_t die)
{
    inphi_status_t status = INPHI_OK;
    por_link_status_t link_status;

    status |= por_link_status_query(die, &link_status);
    status |= por_link_status_print(die, &link_status);

    return status;
}

const char* por_dbg_translate_package_type(e_por_package_type package)
{
    return spica_dbg_translate_package_type((e_spica_package_type)package);
}

const char* por_dbg_translate_driver_type_override(e_por_driver_type driver_type_override)
{
    return spica_dbg_translate_driver_type_override((e_spica_driver_type)driver_type_override);
}

const char* por_dbg_translate_operational_mode(e_por_operational_mode op_mode)
{
    return spica_dbg_translate_operational_mode((e_spica_operational_mode)op_mode);
}

const char* por_dbg_translate_protocol_mode(e_por_protocol_mode protocol_mode)
{
    switch (protocol_mode)
    {
        case POR_MODE_400G_KP4_TO_KP4:  return ("400G_KP4_TO_KP4");
        case POR_MODE_100G_KP4_TO_KP4:  return ("100G_KP4_TO_KP4");
        case POR_MODE_300G_KP4_TO_KP4:  return ("300G_KP4_TO_KP4");
        case POR_MODE_200G_KP4_TO_KP4:  return ("200G_KP4_TO_KP4");
        case POR_MODE_100G_KP4_TO_KP2:  return ("100G_KP4_TO_KP2");
        case POR_MODE_400G_KP8_TO_KP4:  return ("400G_KP8_TO_KP4");
        case POR_MODE_200G_KP4_TO_KP2:  return ("200G_KP4_TO_KP2");
        case POR_MODE_100G_KP2_TO_KP1:  return ("100G_KP2_TO_KP1");
        case POR_MODE_100G_KP4_TO_KP1:  return ("100G_KP4_TO_KP1");
        case POR_MODE_200G_KP8_TO_KP4:  return ("200G_KP8_TO_KP4");
        case POR_MODE_200G_4Nx53p1_TO_4Nx53p1: return ("200G_4Nx53p1_TO_4Nx53p1");

        default:
            break;
    }
    return ("Invalid Protocol Mode");
}

const char* por_dbg_translate_fec_mode(e_por_fec_mode fec_mode)
{
    switch (fec_mode)
    {
        //TODO Add additional cases
        case POR_FEC_BYPASS:                   return ("FEC_BYPASS");
        default:
            break;
    }
    return ("Invalid FEC Mode");
}

const char* por_dbg_translate_ref_clk_mode(e_por_ref_clk_mode ref_clk_mode)
{
    switch (ref_clk_mode)
    {
        case POR_CLK_MODE_LOCAL:   return ("Local");
        case POR_CLK_MODE_REFLESS: return ("Refless");
        default:
            break;
    }
    return ("Invalid Ref Clock Mode");
}

const char* por_dbg_trans_clk_src(e_por_clk_source src)
{
    switch(src)
    {
        case POR_CLK_SRC_DEFAULT:  return "def";
        case POR_CLK_SRC_REFCLK:   return "refclk";
        case POR_CLK_SRC_MM_RECOV: return "mm recov";
        case POR_CLK_SRC_LB_RECOV: return "lb recov";
    }
    return "Unknown";
}

const char* por_dbg_translate_dsp_mode(e_por_dsp_mode dsp_mode)
{
    return ("UnSupported");

    switch (dsp_mode)
    {
        case POR_DSP_MODE_SLC1:                return ("SLC1");
        case POR_DSP_MODE_SLC1_LDEQ:           return ("SLC1_LDEQ");
        case POR_DSP_MODE_SLC1_RC_SLC2:        return ("SLC1_RC_SLC2");
        case POR_DSP_MODE_SLC1_RC_LDEQ:        return ("SLC1_RC_LDEQ");
        case POR_DSP_MODE_SLC1_MPICAN_SLC2:    return ("SLC1_MPICAN_SLC2");
        case POR_DSP_MODE_SLC1_MPICAN_LDEQ:    return ("SLC1_MPICAN_LDEQ");
        case POR_DSP_MODE_SLC1_RC_MPICAN_SLC2: return ("SLC1_RC_MPICAN_SLC2");
        case POR_DSP_MODE_SLC1_RC_MPICAN_LDEQ: return ("SLC1_RC_MPICAN_LDEQ");
        case POR_DSP_MODE_DFE1:                return ("DFE1");
        case POR_DSP_MODE_DFE1_RC_DFE2:        return ("DFE1_RC_DFE2");
        case POR_DSP_MODE_DFE1_MPICAN_DFE2:    return ("DFE1_MPICAN_DFE2");
        case POR_DSP_MODE_DFE1_RC_MPICAN_DFE2: return ("DFE1_RC_MPICAN_DFE2");
        default:
            break;
    }
    return ("Invalid DSP Mode");
}

const char* por_dbg_translate_signalling(e_por_signal_mode signalling)
{
    return spica_dbg_translate_signalling((e_spica_signal_mode)signalling);
}

const char* por_dbg_translate_los_ctrl_amp(e_por_los_ctrl_amp los_ctrl_amp)
{
    switch(los_ctrl_amp)
    {
        case POR_LOS_CTRL_AMP_50:   return ("50");
        case POR_LOS_CTRL_AMP_100:  return ("100");
        case POR_LOS_CTRL_AMP_150:  return ("150");
        case POR_LOS_CTRL_AMP_200:  return ("200");
        case POR_LOS_CTRL_AMP_250:  return ("250");
        case POR_LOS_CTRL_AMP_300:  return ("300");
        case POR_LOS_CTRL_AMP_350:  return ("350");
        default:
            break;
    }
    return ("Unknown");
}

const char* por_dbg_translate_lut_mode(
    e_por_lut_mode lut_mode)
{
    return spica_dbg_translate_lut_mode((e_spica_lut_mode)lut_mode);
}

const char* por_dbg_translate_tx_swing(
    e_por_tx_swing tx_swing)
{
    return spica_dbg_translate_tx_swing((e_spica_tx_swing)tx_swing);
}

const char* por_dbg_translate_baud_rate(
    e_por_baud_rate baud_rate)
{
    return spica_dbg_translate_baud_rate((e_spica_baud_rate)baud_rate);
}

const char* por_dbg_translate_six_bit_mode(
    uint8_t six_bit_mode)
{
    return spica_dbg_translate_six_bit_mode(six_bit_mode);
}

const char* por_dbg_translate_nom_data_rate(e_por_nom_data_rate nom_data_rate)
{
    switch (nom_data_rate)
    {
        case POR_NOM_DATA_RATE_400: return ("400");
        case POR_NOM_DATA_RATE_200: return ("200");
        case POR_NOM_DATA_RATE_100: return ("100");
        case POR_NOM_DATA_RATE_50:  return ("50");
        case POR_NOM_DATA_RATE_25:  return ("25");
        default:
            break;
    }
    return ("Invalid Nominal Data Rate");
}

const char* por_dbg_translate_fec_lb_mode(e_por_fec_lb_mode fec_lb_mode)
{
    switch (fec_lb_mode)
    {
        case POR_FEC_LB_OFF: return ("Off");
        default:
            break;
    }
    return ("Invalid FEC loopback mode");
}

const char* por_dbg_translate_rx_qc_snr_thresh(
    e_por_lrx_qc_snr_threshold snr_thresh)
{
    switch (snr_thresh)
    {
        case POR_LRX_QC_SNR_THRESH_10p1dB:  return ("10.1 dB"); 
        case POR_LRX_QC_SNR_THRESH_10p5dB:  return ("10.5 dB");
        case POR_LRX_QC_SNR_THRESH_11dB  :  return ("11 dB  ");
        case POR_LRX_QC_SNR_THRESH_11p5dB:  return ("11.5 dB");
        case POR_LRX_QC_SNR_THRESH_12dB  :  return ("12 dB  ");
        case POR_LRX_QC_SNR_THRESH_12p5dB:  return ("12.5 dB");
        case POR_LRX_QC_SNR_THRESH_13dB  :  return ("13 dB  ");
        case POR_LRX_QC_SNR_THRESH_13p5dB:  return ("13.5 dB");
        case POR_LRX_QC_SNR_THRESH_14dB  :  return ("14 dB  ");
        case POR_LRX_QC_SNR_THRESH_14p5dB:  return ("14.5 dB");
        case POR_LRX_QC_SNR_THRESH_15dB  :  return ("15 dB  ");
        case POR_LRX_QC_SNR_THRESH_15p5dB:  return ("15.5 dB");
        case POR_LRX_QC_SNR_THRESH_16dB  :  return ("16 dB  ");
        case POR_LRX_QC_SNR_THRESH_16p5dB:  return ("16.5 dB");
        case POR_LRX_QC_SNR_THRESH_17dB  :  return ("17 dB  ");
        case POR_LRX_QC_SNR_THRESH_17p5dB:  return ("17.5 dB");
        case POR_LRX_QC_SNR_THRESH_18dB  :  return ("18 dB  ");
        case POR_LRX_QC_SNR_THRESH_18p5dB:  return ("18.5 dB");
        case POR_LRX_QC_SNR_THRESH_19dB  :  return ("19 dB  ");
        case POR_LRX_QC_SNR_THRESH_19p5dB:  return ("19.5 dB");
        case POR_LRX_QC_SNR_THRESH_20dB  :  return ("20 dB  ");
        case POR_LRX_QC_SNR_THRESH_20p5dB:  return ("20.5 dB");
        case POR_LRX_QC_SNR_THRESH_21dB  :  return ("21 dB  ");
        case POR_LRX_QC_SNR_THRESH_21p5dB:  return ("21.5 dB");
        case POR_LRX_QC_SNR_THRESH_22dB  :  return ("22 dB  ");
        case POR_LRX_QC_SNR_THRESH_22p5dB:  return ("22.5 dB");
        case POR_LRX_QC_SNR_THRESH_23dB  :  return ("23 dB  ");
        case POR_LRX_QC_SNR_THRESH_23p5dB:  return ("23.5 dB");
        case POR_LRX_QC_SNR_THRESH_24dB  :  return ("24 dB  ");
        case POR_LRX_QC_SNR_THRESH_24p5dB:  return ("24.5 dB");
        case POR_LRX_QC_SNR_THRESH_25dB  :  return ("25 dB  ");
        default:
            break;
    }
    return (" ???");
}

void por_dbg_dump_rules(
    uint32_t die,
    por_rules_t* rules)
{
    //spica_dbg_query_print_rules(die);
    char ver[80];

    por_version(ver, 80);
    INPHI_NOTE("\n%s", ver);
    por_version_firmware(die, ver, 80);
    INPHI_NOTE("%s\n", ver);

    INPHI_NOTE("Device Initialization Rules\n"
               "Top Rules\n"
               "  Die:                       0x%08x\n"
               "  Package:                   %s\n"
               "  Efuse Driver Override      %s\n"
               "  Operational mode:          %s\n"
               "  Protocol mode:             %s\n"
               "  FEC mode:                  %s\n"
               "  Ref clock mode:            %s\n"
               "  Ref clock:                 %d kHz\n"
               "  Line Baud Rate (KBd)       %d KBd\n"
               "  Host Baud Rate (KBd)       %d KBd\n"
               "  Show debug info:           %s\n"
               "  FW download timeout:       %d milliseconds\n"
               "  IEEE demap:                %s\n"
               "  FW warn if mismatched:     %s\n" 
               "  ADV Breakout:              %s\n" 
               "  LRX QC SNR Thresh mm Enter %s\n" 
               "  LRX QC SNR Thresh mm Exit  %s\n" 
               "  LRX QC SLC Err Limit       %d\n"
               "  LRX LOS DSRT Ctrl Startup  %s\n" 
               "  LRX LOS ASRT Ctrl Startup  %s\n" 
               "  LRX LOS ASRT Ctrl Datamode %s\n",

               /* Top Rules */
               die,
               por_dbg_translate_package_type(rules->package_type),
               por_dbg_translate_driver_type_override(rules->driver_type_override),
               por_dbg_translate_operational_mode(rules->operational_mode),
               por_dbg_translate_protocol_mode(rules->protocol_mode),
               por_dbg_translate_fec_mode(rules->fec_mode),
               por_dbg_translate_ref_clk_mode(rules->ref_clk_mode),
               rules->ref_clk,
               rules->line_baud_rate,
               rules->host_baud_rate,
               rules->show_debug_info ? "True" : "False",
               rules->fw_dwld_timeout * POR_MCU_POLL_DELAY_MS,
               rules->ieee_demap ? "True" : "False",
               rules->fw_warn_if_mismatched ? "True": "False",
               rules->advanced.breakout ? "True": "False",
               por_dbg_translate_rx_qc_snr_thresh(rules->lrx_qc.snr_threshold_mm_enter),
               por_dbg_translate_rx_qc_snr_thresh(rules->lrx_qc.snr_threshold_mm_exit),
               rules->lrx_qc.slc_err_limit,
               por_dbg_translate_los_ctrl_amp(rules->lrx_los_dsrt_ctrl_startup),
               por_dbg_translate_los_ctrl_amp(rules->lrx_los_asrt_ctrl_startup),
               por_dbg_translate_los_ctrl_amp(rules->lrx_los_asrt_ctrl_datamode)
               );

    // LTX XBAR --------------------------------------------------------
    INPHI_NOTE("\nLTX XBR Rules     |");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("     Ch%d|", channel);
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("------------------+");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("--------+");
        channel = channel; // unused var error fix
    }

    INPHI_NOTE("\n");
    INPHI_NOTE("  Source Ch 1     ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("|       %x", rules->ltx_xbar_src_chan[channel][0]);
    }
    INPHI_NOTE("|\n");
    INPHI_NOTE("  Source Ch 2     ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("|       %x", rules->ltx_xbar_src_chan[channel][1]);
    }
    INPHI_NOTE("|\n");
    INPHI_NOTE("  Source Ch 3     ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("|       %x", rules->ltx_xbar_src_chan[channel][2]);
    }
    INPHI_NOTE("|\n");
    INPHI_NOTE("  Source Ch 4     ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("|       %x", rules->ltx_xbar_src_chan[channel][3]);
    }
    INPHI_NOTE("|\n");

    // HTX XBAR --------------------------------------------------------
    INPHI_NOTE("\nHTX XBR Rules     |");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("     Ch%d|", channel);
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("------------------+");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("--------+");
        channel = channel; // unused var error fix
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("  Source Ch 1     ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("|       %x", rules->htx_xbar_src_chan[channel][0]);
    }
    INPHI_NOTE("|\n");
    INPHI_NOTE("  Interleave      ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("|       %x", rules->htx_xbar_src_chan[channel][1]);
    }
    INPHI_NOTE("|\n");

    // LTX CLK XBAR --------------------------------------------------------
    INPHI_NOTE("\nLTX CLK XBR Rules |");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("     Ch%d|", channel);
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("------------------+");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("--------+");
        channel = channel; // unused var error fix
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("  Clk Source Ch   ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {
        INPHI_NOTE("|       %x", rules->ltx_clk_xbar[channel]);
    }
    INPHI_NOTE("|\n");

    // HTX CLK XBAR --------------------------------------------------------
    INPHI_NOTE("\nHTX CLK XBR Rules |");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("     Ch%d|", channel);
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("------------------+");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("--------+");
        channel = channel; // unused var error fix
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("  Clk Source Ch   ");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("|       %x", rules->htx_clk_xbar[channel]);
    }
    INPHI_NOTE("|\n");

    INPHI_NOTE("\nLRX Rules\n");
    INPHI_NOTE("  Ch#  | Enable | DSP Mode    | Signalling | Gray Map | Baud Rate | Ieee Demap | Invert   | SDT En | 6-Bit Mode | Force MM ");
    INPHI_NOTE("\n");
    INPHI_NOTE("  -----+--------+-------------+------------+----------+-----------+------------+----------+----------+------------+----------");

    INPHI_NOTE("\n");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LRX)
    {
        INPHI_NOTE("  %4d | %6s | %11s | %10s | %8s | %9s | %10s | %8s | %8s | %10s | %8s ",
                   channel,
                   rules->lrx[channel].channel_enable ? "True" : "False",
                   por_dbg_translate_dsp_mode(rules->lrx[channel].dsp_mode),
                   por_dbg_translate_signalling(rules->lrx[channel].signalling),
                   rules->lrx[channel].gray_mapping ? "True" : "False",
                   por_dbg_translate_baud_rate((rules->lrx[channel].baud_rate)? rules->lrx[channel].baud_rate:rules->line_baud_rate),
                   rules->ieee_demap|rules->lrx[channel].ieee_demap ? "True" : "False",
                   rules->lrx[channel].invert_chan ? "True" : "False",
                   rules->lrx[channel].sdt_dsp_en ? "True" : "False",
                   por_dbg_translate_six_bit_mode(rules->lrx[channel].six_bit_mode),
                   rules->lrx[channel].force_mission_mode ? "True" : "False");
        INPHI_NOTE("\n");
    }

    INPHI_NOTE("\nLTX Rules\n");
    INPHI_NOTE("  Ch#  | Enable | Signalling | LUT Mode  | Gray Map | Invert | Ieee Demap | Squelch Lock | DFE Precoder | Tap    0    1    2    3    4    5    6 | Inner Eye   | Tx Swing\n"
               "  -----+--------+------------+-----------+----------+--------+------------+--------------+--------------+----------------------------------------+-------------+---------\n");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_LTX)
    {                                                                // tap
        INPHI_NOTE("%s%2d | %6s | %10s | %9s | %8s | %6s | %10s | %12s | %12s |     %4d %4d %4d %4d %4d %4d %4d | %4d | %4d | %8s\n",
                   "    ",
                   channel,
                   rules->ltx[channel].channel_enable ? "True" : "False",
                   por_dbg_translate_signalling(rules->ltx[channel].signalling),
                   por_dbg_translate_lut_mode(rules->ltx[channel].lut_mode),
                   rules->ltx[channel].gray_mapping ? "True" : "False",
                   rules->ltx[channel].invert_chan ? "True" : "False",
                   rules->ieee_demap|rules->ltx[channel].ieee_demap ? "True" : "False",
                   rules->ltx[channel].squelch_lock ? "True" : "False",
                   rules->ltx[channel].dfe_precoder_en ? "True" : "False",
                   rules->ltx[channel].fir_taps[0],
                   rules->ltx[channel].fir_taps[1],
                   rules->ltx[channel].fir_taps[2],
                   rules->ltx[channel].fir_taps[3],
                   rules->ltx[channel].fir_taps[4],
                   rules->ltx[channel].fir_taps[5],
                   rules->ltx[channel].fir_taps[6],
                   rules->ltx[channel].inner_eye1,
                   rules->ltx[channel].inner_eye2,
                   por_dbg_translate_tx_swing((e_por_tx_swing)rules->ltx[channel].swing)
                   );
    }

    INPHI_NOTE("\nHRX Rules\n");
    INPHI_NOTE("  Ch#  | Enable | Invert | Gray Map | Signalling | Ieee Demap\n"
               "  -----+--------+--------+----------+------------+-----------\n");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_NOTE("  %4d | %6s | %6s | %8s | %10s | %12s\n",
                   channel,
                   rules->hrx[channel].channel_enable ? "True" : "False",
                   rules->hrx[channel].invert_chan ? "True" : "False",
                   rules->hrx[channel].gray_mapping ? "True" : "False",
                   por_dbg_translate_signalling(rules->hrx[channel].signalling),
                   rules->ieee_demap|rules->hrx[channel].ieee_demap ? "True" : "False"
                   );
    }
    INPHI_NOTE("\n");
    INPHI_NOTE("  Ch#  | Skip adt | CTLE dis | CTLE ovr | LFEQ dis | LFEQ ovr | DFE dis | DSKEW dis | ESKEW dis | SLC dis | EOFF dis | AGC dis | BW dis | VCOT-Cal dis | DC-Off dis | LFEQ dis   | VCO Mode\n"
               "  -----+----------+----------+----------+----------+----------+---------+-----------+-----------+---------+----------+---------+--------+--------------+------------+------------+---------\n");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HRX)
    {
        INPHI_NOTE("  %4d | %8s | %8s | %8x | %8s | %8x | %7s | %9s | %9s | %7s | %8s | %7s | %6s | %12s | %10s | %10s | %7s\n",
                   channel,
                   rules->hrx[channel].skip_adapt ? "True" : "False",
                   rules->hrx[channel].ctle_adapt_dis ? "True" : "False",
                   rules->hrx[channel].ctle_override,
                   rules->hrx[channel].lfeq_adapt_dis ? "True" : "False",
                   rules->hrx[channel].lfeq_override,
                   rules->hrx[channel].dfe_adapt_dis ? "True" : "False",
                   rules->hrx[channel].data_skew_adapt_dis ? "True" : "False",
                   rules->hrx[channel].edge_skew_adapt_dis ? "True" : "False",
                   rules->hrx[channel].slc_adapt_dis ? "True" : "False",
                   rules->hrx[channel].edge_off_adapt_dis ? "True" : "False",
                   rules->hrx[channel].agc_adapt_dis ? "True" : "False",
                   rules->hrx[channel].afe_bw_adapt_dis ? "True" : "False",
                   rules->hrx[channel].vco_temp_cal_dis ? "True" : "False",
                   rules->hrx[channel].dc_off_adapt_dis ? "True" : "False",
                   rules->hrx[channel].lfeq_adapt_dis_after_init_adapt ? "False" : "True",
                   rules->hrx[channel].vco_mode ? "True" : "False"
                   );
    }

    INPHI_NOTE("\nHTX Rules\n");
    INPHI_NOTE("  Ch#  | Enable | Signalling | LUT Mode  | Gray Map | Invert | Ieee Demap | Squelch Lock | DFE Precoder | Tap    0    1    2    3    4    5    6 | Inner Eye   | Tx Swing\n"
               "  -----+--------+------------+-----------+----------+--------+------------+--------------+--------------+----------------------------------------+-------------+---------\n");
    POR_FOR_CHANNEL_IN_CHANNELS(die, POR_INTF_HTX)
    {
        INPHI_NOTE("  %4d | %6s | %10s | %9s | %8s | %6s | %10s | %12s | %12s |     %4d %4d %4d %4d %4d %4d %4d | %4d | %4d | %8s\n",
                   channel,
                   rules->htx[channel].channel_enable ? "True" : "False",
                   por_dbg_translate_signalling(rules->htx[channel].signalling),
                   por_dbg_translate_lut_mode(rules->htx[channel].lut_mode),
                   rules->htx[channel].gray_mapping ? "True" : "False",
                   rules->htx[channel].invert_chan ? "True" : "False",
                   rules->ieee_demap|rules->htx[channel].ieee_demap ? "True" : "False",
                   rules->htx[channel].squelch_lock ? "True" : "False",
                   rules->htx[channel].dfe_precoder_en ? "True" : "False",
                   rules->htx[channel].fir_taps[0],
                   rules->htx[channel].fir_taps[1],
                   rules->htx[channel].fir_taps[2],
                   rules->htx[channel].fir_taps[3],
                   rules->htx[channel].fir_taps[4],
                   rules->htx[channel].fir_taps[5],
                   rules->htx[channel].fir_taps[6],
                   rules->htx[channel].inner_eye1,
                   rules->htx[channel].inner_eye2,
                   por_dbg_translate_tx_swing((e_por_tx_swing)rules->htx[channel].swing)
                   );
    }

    INPHI_NOTE("\nFEC Rules NOT Supported\n");
 
}
#endif //defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/*
 * This method may be called to query the current configuration of the
 * transmitters from the ASIC.
 */
inphi_status_t por_tx_fir_query(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_tx_rules_t* tx_rules)
{
    inphi_status_t status = INPHI_OK;
    
    if (!tx_rules)
    {
        INPHI_CRIT("ERROR: tx rules cannot be NULL!\n");
        return INPHI_ERROR;
    }
    INPHI_MEMSET(tx_rules, 0, sizeof(por_tx_rules_t));

    spica_tx_rules_t spica_tx_rules;
    status = spica_tx_fir_query(die, channel, (e_spica_intf)intf, &spica_tx_rules);

    if (INPHI_OK == status)
    {
        tx_rules->channel_enable  = spica_tx_rules.channel_enable;
        tx_rules->lut_mode        = spica_tx_rules.lut_mode       ;
        tx_rules->gray_mapping    = spica_tx_rules.gray_mapping   ;
        tx_rules->ieee_demap      = spica_tx_rules.ieee_demap     ;
        tx_rules->invert_chan     = spica_tx_rules.invert_chan    ;
        tx_rules->signalling      = spica_tx_rules.signalling     ;
        tx_rules->swing           = spica_tx_rules.swing          ;
        tx_rules->squelch_lock    = spica_tx_rules.squelch_lock   ;
        tx_rules->baud_rate       = spica_tx_rules.baud_rate      ;
        tx_rules->fll_mode        = spica_tx_rules.fll_mode     ;
        tx_rules->dfe_precoder_en = spica_tx_rules.dfe_precoder_en;
        tx_rules->inner_eye1      = spica_tx_rules.inner_eye1     ;
        tx_rules->inner_eye2      = spica_tx_rules.inner_eye2     ;
        tx_rules->const_vpk       = false;
        for(int i=0;i<7;i++)
            tx_rules->fir_taps[i] = spica_tx_rules.fir_taps[i];
    }
    return status;
}

/*
 * Update the TX FIR configuration.
 */
inphi_status_t por_tx_fir_set(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf,
    por_tx_rules_t* tx_rules)
{
    inphi_status_t status = INPHI_OK;
        
    if (!tx_rules)
    {
        INPHI_CRIT("ERROR: tx rules cannot be NULL!\n");
        return INPHI_ERROR;
    }

    spica_tx_rules_t spica_tx_rules;

    // NOTE: por_tx_fir_set() only supported on-the-fly updates to the following rules
    // - lut_mode 
    // - swing
    // - fir_taps
    // - inner_eye1
    // - inner_eye2
    // Check that user has not attempted to change unsupported rules
    spica_tx_rules.channel_enable  =  tx_rules->channel_enable; 
    spica_tx_rules.lut_mode        =  tx_rules->lut_mode;
    spica_tx_rules.gray_mapping    =  tx_rules->gray_mapping;
    spica_tx_rules.ieee_demap      =  tx_rules->ieee_demap;
    spica_tx_rules.invert_chan     =  tx_rules->invert_chan;
    spica_tx_rules.signalling      =  tx_rules->signalling;
    spica_tx_rules.swing           =  tx_rules->swing;
    spica_tx_rules.squelch_lock    =  tx_rules->squelch_lock;
    spica_tx_rules.baud_rate       =  tx_rules->baud_rate;
    spica_tx_rules.fll_mode        =  tx_rules->fll_mode;
    spica_tx_rules.dfe_precoder_en = tx_rules->dfe_precoder_en;
    spica_tx_rules.inner_eye1      =  tx_rules->inner_eye1;
    spica_tx_rules.inner_eye2      =  tx_rules->inner_eye2;
    for(int i=0;i<7;i++)
        spica_tx_rules.fir_taps[i] = tx_rules->fir_taps[i];
    
    status = spica_tx_fir_set(die, channel, (e_spica_intf)intf, &spica_tx_rules); 
    return status;
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
/*
 * Query then dump the TX FIR configuration.
 */
inphi_status_t por_tx_fir_query_dump(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf)
{
    inphi_status_t status = INPHI_OK;
    por_tx_rules_t tx_rules;

    status |= por_tx_fir_query(die, channel, intf, &tx_rules);

    INPHI_NOTE("  Ch#  | LUT Mode   | Gray Map | IEEE DeM | Invert | TAP_1 | TAP_2 | TAP_3 | TAP_4 | TAP_5 | TAP_6 | TAP_7 | Inner Eye   | Tx Swing\n"
               "  -----+------------+----------+----------+--------+-------+-------+-------+-------+-------+-------+-------+-------------+---------\n");
    INPHI_NOTE("  %3d  | %10s | %8s | %8s | %6s | %5d | %5d | %5d | %5d | %5d | %5d | %5d | %4d | %4d | %8s\n",
               channel,
               por_dbg_translate_lut_mode(tx_rules.lut_mode),
               tx_rules.gray_mapping ? "True" : "False",
               tx_rules.ieee_demap ? "True" : "False",
               tx_rules.invert_chan ? "True" : "False",
               tx_rules.fir_taps[0],
               tx_rules.fir_taps[1],
               tx_rules.fir_taps[2],
               tx_rules.fir_taps[3],
               tx_rules.fir_taps[4],
               tx_rules.fir_taps[5],
               tx_rules.fir_taps[6],
               tx_rules.inner_eye1,
               tx_rules.inner_eye2,
               por_dbg_translate_tx_swing((e_por_tx_swing)tx_rules.swing)
               );

    return status;
}
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

// Squelch the transmit output for the specified channel
inphi_status_t por_tx_squelch(
    uint32_t   die,
    uint32_t   channel,
    e_por_intf intf,
    bool       squelch)
{
    return spica_tx_squelch(die, channel, (e_spica_intf)intf, squelch);
}

inphi_status_t por_bundle_enable(
    uint32_t die, 
    uint32_t channel, 
    e_por_intf intf, 
    bool enable)
{
    inphi_status_t status = INPHI_OK;

    status |= spica_clock_group_enable(die, channel, (e_spica_intf)intf, enable);

    return status;
}

// Enables or disables the squelch lock for the specified channel
inphi_status_t por_tx_squelch_lock(
    uint32_t   die,
    uint32_t   channel,
    e_por_intf intf,
    bool       squelch_lock)
{
    inphi_status_t status = INPHI_OK;
    
    status |= spica_tx_squelch_lock(die, channel, (e_spica_intf)intf, squelch_lock);

    return status; 
}

// Toggle the invert status of a TX channel
inphi_status_t por_tx_invert_toggle(
    uint32_t          die,
    uint32_t          channel,
    e_por_intf        intf)
{
    inphi_status_t status = INPHI_OK;
    
    status |= spica_tx_invert_toggle(die, channel, (e_spica_intf)intf);

    return status; 
}

// Toggle the invert status of an RX channel
inphi_status_t por_rx_invert_toggle(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf)
{
    inphi_status_t status = INPHI_OK;
    
    status |= spica_rx_invert_toggle(die, channel, (e_spica_intf)intf);

    return status; 
}

// Query the temperature
inphi_status_t por_temperature_query(uint32_t die, int16_t* temperature)
{
    inphi_status_t status = INPHI_OK;

    status |= spica_temperature_query(die, temperature);

    return status;
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1
inphi_status_t por_diags_register_dump(uint32_t die)
{
    return spica_diags_register_dump(die); 
}
#endif //!defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

inphi_status_t por_tx_man_config(
    uint32_t            die,
    uint32_t            channel,
    e_por_intf          intf,
    e_por_lut_mode      lut_mode,
    bool                is_lut_unsigned,
    bool                toggle_squelch,
    int8_t              lut[256],
    int16_t             coef[28])
{
    inphi_status_t status = INPHI_OK;

    status |= spica_tx_man_config(die, channel, (e_spica_intf)intf, (e_spica_lut_mode)lut_mode, is_lut_unsigned, toggle_squelch, lut, coef);

    return status;
}

#if !defined(INPHI_REMOVE_MESSAGING)

inphi_status_t por_fec_stats_poller_cfg(
    uint32_t   die,
    e_por_intf intf,
    const por_fec_stats_poller_rules_t *stats_rules)
{
    inphi_status_t status = INPHI_OK;
    
    status |= spica_fec_stats_poller_cfg(die, intf, (spica_fec_stats_poller_rules_t*)stats_rules);

    return status;
}

inphi_status_t por_fec_stats_poller_request(
    uint32_t   die,
    e_por_intf intf,
    bool clear_on_read,
    por_fec_stats_cp_block_t *stats)
{
    inphi_status_t status = INPHI_OK;
    
    status |= spica_fec_stats_poller_request(die, intf, clear_on_read, (spica_fec_stats_cp_block_t*)stats);

    return status;
}

e_por_poller_status por_fec_stats_poller_get(
    uint32_t   die,
    e_por_intf intf,
    uint32_t blocks_to_read,
    por_fec_stats_cp_block_t *stats)
{
    e_por_poller_status status = SPICA_POLLER_OK;

    status |= (e_por_poller_status)spica_fec_stats_poller_get(die, intf, blocks_to_read, (spica_fec_stats_cp_block_t*)stats);

    return status;
}

inphi_status_t por_fec_stats_poller_clear(
    uint32_t   die,
    e_por_intf intf)
{
    inphi_status_t status = INPHI_OK;
    
    status |= spica_fec_stats_poller_clear(die, intf);

    return status;
}

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)
#if defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)

inphi_status_t por_fec_stats_poller_calc_ber(
    uint32_t die,
    e_por_intf intf,
    por_fec_stats_cp_block_t *stats,
    por_fec_stats_poller_t *avg_rates,
    por_fec_stats_poller_t *min_rates,
    por_fec_stats_poller_t *max_rates,
    por_fec_stats_poller_t *cur_rates)
{
    inphi_status_t status = INPHI_OK;

    status |= spica_fec_stats_poller_calc_ber(die, intf,
                                              (spica_fec_stats_cp_block_t*)stats,  
                                              (spica_fec_stats_poller_t*)avg_rates,
                                              (spica_fec_stats_poller_t*)min_rates,
                                              (spica_fec_stats_poller_t*)max_rates,
                                              (spica_fec_stats_poller_t*)cur_rates);
    return status;
}

#endif // defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)
#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT==1)

#endif // defined(INPHI_REMOVE_MESSAGING)

/** @file por_dsp.c
 ****************************************************************************
 *
 * @brief
 *     This module contains the high level DSP diagnostic methods
 *     implemented by the API.
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

uint32_t por_lrx_dsp_snr_read_db_fixp(
    uint32_t die,
    uint32_t channel)
{
    return spica_rx_dsp_snr_read_db_fixp(die, channel, SPICA_INTF_ORX);
}

uint32_t por_rx_dsp_snr_read_db_fixp(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf)
{
    return spica_rx_dsp_snr_read_db_fixp(die, channel, SPICA_INTF_ORX);
}

#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)
double por_lrx_dsp_snr_read_db(
    uint32_t die,
    uint32_t channel)
{
    return spica_rx_dsp_snr_read_db(die, channel, SPICA_INTF_ORX);
}

double por_rx_dsp_snr_read_db(
    uint32_t die,
    uint32_t channel,
    e_por_intf intf)
{
    return spica_rx_dsp_snr_read_db(die, channel, SPICA_INTF_ORX);
}
#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)

inphi_status_t por_rx_dsp_ltp_read_fixp(uint32_t die, uint32_t channel, e_por_intf intf, uint16_t *ltp)
{
    if(POR_INTF_LRX != intf)
    {
        INPHI_CRIT("only supported on LRX side\n");
        return INPHI_ERROR;
    }

    spica_rx_dsp_ltp_read_fixp(die, channel, (e_spica_intf)intf, ltp);

    return INPHI_OK;
}

#if defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)
#if defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)
double por_rx_dsp_ltp_format(uint16_t ltp)
{
    return spica_rx_dsp_ltp_format(ltp);
}
#endif // defined(INPHI_HAS_MATH_DOT_H) && (INPHI_HAS_MATH_DOT_H == 1)
#endif // defined(INPHI_HAS_FLOATING_POINT) && (INPHI_HAS_FLOATING_POINT == 1)

inphi_status_t por_lrx_dsp_ffe_taps_query(
    uint32_t die,
    uint32_t channel,
    int16_t  ffe_taps[POR_RX_DSP_SLICES*POR_RX_DSP_NUM_FFE_TAPS])
{
    return spica_rx_dsp_ffe_taps_query(die, channel, SPICA_INTF_ORX, ffe_taps);
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS == 1)
inphi_status_t por_lrx_dsp_ffe_taps_print(
    uint32_t die,
    uint32_t channel,
    int16_t  ffe_taps[POR_RX_DSP_SLICES*POR_RX_DSP_NUM_FFE_TAPS])
{
    return spica_rx_dsp_ffe_taps_print(die, channel, SPICA_INTF_ORX, ffe_taps);
}
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

inphi_status_t por_lrx_dsp_vga1_query(
    uint32_t die,
    uint32_t channel,
    uint16_t* vga1_gain)
{
    return spica_rx_dsp_vga1_query(die, channel, SPICA_INTF_ORX, vga1_gain);
}

inphi_status_t por_lrx_dsp_get_histogram(
    uint32_t die,
    uint32_t channel,
    uint32_t *hist_data)
{
    return spica_rx_dsp_hist_get(die, channel, SPICA_INTF_ORX, hist_data);
}

inphi_status_t por_hrx_pulse_resp_query(uint32_t die,  uint32_t channel, int32_t* resp_values,  int32_t* len) 
{
    inphi_status_t status = INPHI_OK;

    status |= spica_srx_pulse_resp_query(die, channel, resp_values, len);

    return status;
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1
inphi_status_t por_hrx_pulse_resp_query_dump_range(uint32_t die, uint32_t start, uint32_t end)
{
    inphi_status_t status = INPHI_OK;

    status |= spica_srx_pulse_resp_query_dump_range(die, start, end);

    return status;
}

inphi_status_t por_hrx_pulse_resp_query_dump(uint32_t die)
{
    inphi_status_t status = INPHI_OK;

    status |= spica_srx_pulse_resp_query_dump(die);

    return status;
}

 
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && INPHI_HAS_DIAGNOSTIC_DUMPS == 1

/** @file mcu.c
 ****************************************************************************
 *
 * @brief
 *     This module contains the implementation of the interface to the
 *     embedded MCU.
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

#if defined(INPHI_HAS_FILESYSTEM) && (INPHI_HAS_FILESYSTEM==1)
#include <string.h> // String methods for progrmaming ucode/EEPROM from disk
#include <stdio.h>  // File IO methods for programming ucode/EEPROM from disk
#endif // INPHI_HAS_FILESYSTEM

inphi_status_t por_mcu_reset_into_application(
    uint32_t die,
    bool wait_till_started)
{
    return spica_mcu_reset_into_application(die, wait_till_started);
}

inphi_status_t por_mcu_reset_into_boot_upgrade(
    uint32_t die,
    bool wait_till_started)
{
    INPHI_WARN("API currently NOT supported in v%s\n",POR_API_VERSION);
    return INPHI_OK;
}

inphi_status_t por_mcu_reset_into_boot_from_eeprom(
    uint32_t die,
    bool wait_till_started)
{
    return spica_mcu_download_bootloader(die, wait_till_started);
}

#if defined(INPHI_HAS_DIRECT_DOWNLOAD) && (INPHI_HAS_DIRECT_DOWNLOAD==1)

// Download the firmware from an external source like flash memory
inphi_status_t por_mcu_download_firmware_from_external_memory(
    uint32_t die,
    uint32_t (*fw_get_word)(uint32_t offset, void* user_data),
    uint32_t length,
    bool     verify,
    void*    user_data)
{
    INPHI_WARN("API currently NOT supported in v%s\n",POR_API_VERSION);
    return INPHI_OK;
}

// Download the firmware image from a file
inphi_status_t por_mcu_download_firmware_from_file(
    uint32_t die,
    const char* path,
    bool verify)
{
    return spica_mcu_download_firmware_from_file(die, path, verify);
}

#if defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW==1)
//include the app image, will not be compiled in without the proper defines (INPHI_HAS_INLINE_APP_FW)

// Download the inlined firmware image
inphi_status_t por_mcu_download_firmware(
    uint32_t die,
    bool verify)
{
    return spica_mcu_download_firmware(die, verify);
}
#endif // defined(INPHI_HAS_INLINE_APP_FW) && (INPHI_HAS_INLINE_APP_FW==1)
#endif // defined(INPHI_HAS_DIRECT_DOWNLOAD) && (INPHI_HAS_DIRECT_DOWNLOAD==1)

#if defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)
inphi_status_t por_mcu_download_eeprom_from_file(
    uint32_t die,
    const char* path)
{
    return spica_mcu_download_eeprom_from_file(die, path);
}

/* This method is called to verify the integrity of the eeprom
   and returned the checksum values. */
inphi_status_t por_mcu_eeprom_verify_with_checksum(
    uint32_t  die,
    uint32_t  eeprom_address,
    uint32_t* checksum_calculated,
    uint32_t* checksum_expected)
{
    INPHI_WARN("API currently NOT supported in v%s\n",POR_API_VERSION);
    return INPHI_OK;
}

inphi_status_t por_mcu_eeprom_read_metadata(
    uint32_t die,
    char*    metadata,
    uint32_t metadata_size)
{
    return spica_mcu_eeprom_read_metadata(die, metadata, metadata_size);
}
#endif // defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)

inphi_status_t por_mcu_status_query(
    uint32_t            die,
    por_mcu_status_t* mcu_status)
{
    return spica_mcu_status_query(die,
                                 (spica_mcu_status_t*)mcu_status);
}

#if defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)
inphi_status_t por_mcu_status_query_print(
    uint32_t die)
{
    return spica_mcu_status_query_print(die);
}

inphi_status_t por_mcu_pc_log_query_dump(
    uint32_t die,
    uint32_t num_entries)
{
    return spica_mcu_pc_log_query_print(die, num_entries);
}

inphi_status_t por_mcu_debug_log_query_dump(
    uint32_t die)
{
    return spica_mcu_debug_log_query_print(die);
}

/**
 * This method is used to dump the firmware trace log into a buffer,
 * for debug purposes.
 */
inphi_status_t por_mcu_debug_log_query(
    uint32_t die,
    char* buff,
    uint32_t buff_size)
{
    return spica_mcu_debug_log_query(die, buff, buff_size);
}
#endif // defined(INPHI_HAS_DIAGNOSTIC_DUMPS) && (INPHI_HAS_DIAGNOSTIC_DUMPS==1)

/**
 * This method is used to get the fw mode
 */
inphi_status_t por_mcu_fw_mode_query(
    uint32_t die,
    e_por_fw_mode *mode)
{
    return spica_mcu_fw_mode_query(die,
                                  (e_spica_fw_mode*) mode);
}

inphi_status_t por_mcu_pc_log_query(
    uint32_t die,
    uint32_t* entries,
    uint32_t num_entries)
{
    return spica_mcu_pc_log_query(die, entries, num_entries);
}

/*
 * This method blocks until the MCU is in application mode or
 * the until the timeout expires.
 */
inphi_status_t por_mcu_block_application_mode(
    uint32_t die,
    uint32_t timeout)
{
    return spica_mcu_block_application_mode(die, timeout);
}

#if defined(INPHI_HAS_SHARED_EEPROM) && (INPHI_HAS_SHARED_EEPROM==1)
inphi_status_t por_mcu_boot_from_shared_eeprom(
    uint32_t* dies,
    uint32_t  num_dies)
{
    (void)num_dies;
    return spica_mcu_download_bootloader(dies[0], false);
}

/**
 * This method is setup as a callback method to allow the user to not
 * completely block while the bootloader is busy loading the firmware from
 * the EEPROM for each die on the device. Only one die can be SPI
 * master at any one time so the boot procedure needs to be controlled to
 * avoid damage to the SPI pins.
 *
 * This method will be called multiple times until the application image
 * starts or the user aborts the polling operation.
 */
inphi_status_t por_mcu_check_boot_from_eeprom_complete(
    uint32_t die,
    void*    user_data,
    bool*    complete,
    bool*    abort_polling)
{
    (void)user_data; // Not used right now.
    inphi_status_t status = INPHI_OK;

    uint16_t reg_data = 0;
    *complete = false;

    // If you want to abort polling because it is taking too long then set
    // this to true and return.
    *abort_polling = false;

    // Check to see if the bootloader has completed booting from EEPROM
    // and has jumped to the application code.
    reg_data = SPICA_MCU_FW_MODE__READ(die);
    if(0xACC0 == SPICA_MCU_FW_MODE__FW_MODE__GET(reg_data))
    {
        *complete = true;
    }

    return status;
}
#endif //defined(INPHI_HAS_SHARED_EEPROM) && (INPHI_HAS_SHARED_EEPROM==1)

/**
 * Get the fw_info struct containing some important buffer addresses
 */
inphi_status_t por_mcu_fw_info_query(
    uint32_t       die,
    por_fw_info_t* fw_info)
{
    return spica_mcu_fw_info_query(die, (spica_fw_info_t*)fw_info);
}

#if defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)

//! This method is called to erase the EEPROM
//!
//! @param die         [I] - The physical ASIC die being accessed.
//!
//! @return INPHI_OK on success, INPHI_ERROR on failure.
//!
//! Note: This command does not work on EEPROMs. It only works
//!       on Flash devices.
//!
//!       List of basic Flash commands:
//!
//!       1.  Write Status Register:   0x01
//!       2.  Read:                    0x02
//!       3.  Write:                   0x03
//!       4.  Write Disable:           0x04
//!       5.  Read Status Register:    0x05
//!       6.  Write Enable:            0x06
//!       7.  Chip Erase:              0x60 or 0xC7
//!       8.  Read ID:                 0x90
//!       9.  JEDEC ID:                0x9F
//!       10. Power Down:              0xB9
//!       11. Resume from Power down:  0xAB
//!
//! @since 1.0
//!
inphi_status_t por_spi_eeprom_erase(
    uint32_t die)
{
    return spica_spi_eeprom_erase(die);
}

inphi_status_t por_spi_read_data_block(
    uint32_t          die,
    uint32_t          eeprom_addr,
    uint32_t          *words,
    uint32_t          num_words,
    e_por_spi_clk_div clkdiv)
{
    return spica_spi_read_data_block(die, eeprom_addr, words, num_words, clkdiv); 
}

inphi_status_t por_spi_write_data_block(
    uint32_t          die,
    uint32_t          eeprom_addr,
    uint32_t          *words,
    uint32_t          num_words,
    e_por_spi_clk_div clkdiv)
{
    return spica_spi_write_data_block(die, eeprom_addr, words, num_words, clkdiv); 
}

#endif // defined(INPHI_HAS_EEPROM_ACCESS) && (INPHI_HAS_EEPROM_ACCESS==1)




