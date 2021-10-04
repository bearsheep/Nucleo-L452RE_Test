/** @file por_rules.h
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
#ifndef __POR_RULES_H__
#define __POR_RULES_H__

/**
 * @h2 Misc defines
 * =======================================================
 *
 * @brief
 * Default number of MS to poll for MCU status
 * 
 * @private
 */
#define POR_MCU_POLL_DELAY_MS 50

/**
 * @h2 ASIC Package and Channel Utilities
 * =======================================================
 *
 * @brief
 * The maximum number of dies inside the ASIC package. When only
 * working on a single die package this can be re-defined to 1 to
 * conserve memory utilization.
 */
#define POR_MAX_DIES_IN_PACKAGE 1

/** the maximum number of line Rx channels per die */
#define POR_NUM_OF_LRX_CHANNELS 4
/** the maximum number of line Tx channels per die */
#define POR_NUM_OF_LTX_CHANNELS 4
/** the maximum number of host Rx channels per die */
#define POR_NUM_OF_HRX_CHANNELS 8
/** the maximum number of host Tx channels per die */
#define POR_NUM_OF_HTX_CHANNELS 8

/** The maximum number of line receivers in the ASIC package */
#define POR_MAX_LRX_CHANNELS (POR_NUM_OF_LRX_CHANNELS * POR_MAX_DIES_IN_PACKAGE)
/** The maximum number of line transmitters in the ASIC package */
#define POR_MAX_LTX_CHANNELS (POR_NUM_OF_LTX_CHANNELS * POR_MAX_DIES_IN_PACKAGE)
/** The maximum number of host PSR receivers in the ASIC package */
#define POR_MAX_HRX_CHANNELS (POR_NUM_OF_HRX_CHANNELS * POR_MAX_DIES_IN_PACKAGE)
/** The maximum number of host PSR transmitters in the ASIC package */
#define POR_MAX_HTX_CHANNELS (POR_NUM_OF_HTX_CHANNELS * POR_MAX_DIES_IN_PACKAGE)


/**
 * The ASIC package type which defines the channel
 * mapping. See the user guide section API Channel Mapping for more info.
 */
typedef enum
{
    /** Unknown package type, channels will not be re-mapped */
    POR_PACKAGE_TYPE_UNMAPPED = 0,

    /** 400G EML 12x13 package (PG3) */
    POR_PACKAGE_TYPE_EML_12x13 = 5,

    /** 400G STD 10x13 package (PG3) */
    POR_PACKAGE_TYPE_STD_10x13 = 6,

    /** 400G EML 12x13 package (PG3) Rev 1 */
    POR_PACKAGE_TYPE_EML_12x13_REV1 = 8,

    /** For range checking of the package type, don't use this value. */ 
    POR_PACKAGE_TYPE_MAX,
} e_por_package_type;

/**
 * These are interface or definitions used by the API to
 * configure certain parts of the datapath.
 */
typedef enum
{
    /** POR Unknown */
    POR_INTF_NONE   = 0,
    /** POR Line RX */
    POR_INTF_LRX    = 1<<0,
    /** POR Line TX */
    POR_INTF_LTX    = 1<<1,
    /** POR Host RX */
    POR_INTF_HRX    = 1<<4,    //INTF_SRX on Spica
    /** POR Host TX */
    POR_INTF_HTX    = 1<<5,    //INTF_STX on Spica
    /** Egress FEC */
    POR_INTF_EG_FEC = 1<<6,
    /** Ingress FEC */
    POR_INTF_IG_FEC = 1<<7,
    /** Any FEC */
    POR_INTF_ANY_FEC = (POR_INTF_EG_FEC | POR_INTF_IG_FEC),
    /** The PKR line side interface */
    POR_INTF_PKR  = POR_INTF_LRX | POR_INTF_LTX,
    /** The PSR host side interface */
    POR_INTF_PSR  = POR_INTF_HRX | POR_INTF_HTX,
    /** All interfaces */
    POR_INTF_ALL = POR_INTF_PKR | POR_INTF_PSR

} e_por_intf;

/**
 * @h2 High Level Configuration Rules
 * =======================================================
 * The following section describes the public types and structures
 * used by the API.
 *
 * @brief
 * The operational mode defines the data flow through the device.
 * The protocol mode specifies the signalling and baud rate of host/line interfaces
 * The FEC mode specifies whether or not FEC is enabled
 *
 * Note that op_mode, protocol_mode, and fec_mode directly impact the default rules set
 * by the por_rules_set_default function. Differences are noted below. These operating
 * modes are also passed to the FW to provide high-level configuration cues.
 *
 */
typedef enum
{
    /**
     * Mission mode.
     *
     * This is the main operational mode of the Porrima device. It configures
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
    POR_MODE_MISSION_MODE = 0,

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
    POR_MODE_LINE_PRBS,                   // 1

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
    POR_MODE_HOST_PRBS,                   // 2     

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
    POR_MODE_DUAL_PRBS,                   // 3

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
    POR_MODE_SHALLOW_LINE_LOOPBACK,       // 4

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
    POR_MODE_SHALLOW_HOST_LOOPBACK,       // 5

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
    POR_MODE_INGRESS_PRBS,                // 6

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
    POR_MODE_EGRESS_PRBS,                 // 7

    POR_MODE_OP_END,
} e_por_operational_mode;   

/**
 * The protocol mode defines the baud rate and number of channels per interface
 * ie. POR_MODE_[Chip Throughput]G_[Host Mode]_TO_[Line Mode]
 * The selected protocol mode determines the channel enables, signalling, and baud
 * rates for all interfaces
 */
typedef enum 
{
    /** NOT SUPPORTED - Host 4x106.25Gbps (PAM4) to Line 4x106.25Gbps (PAM4*/
    POR_MODE_400G_KP4_TO_KP4       =  0,
    /** Host 4x25.78125 Gbps (NRZ) to Line 4x25.78125 Gbps (NRZ) */
    POR_MODE_100G_KP4_TO_KP4,
    /** NOT SUPPORTED - Host 4x82.5Gbps (PAM4) to Line 4x82.5Gbps (PAM4) [Discount Rate]*/
    POR_MODE_300G_KP4_TO_KP4,
    /** Host 200GAUI-4 (PAM4) to Line KP4 (PAM4), Host 4x53.125 Gbps (PAM4) to Line 4x53.125 Gbps (PAM4) */
    POR_MODE_200G_KP4_TO_KP4,
    /** Host 4x25.78125 Gbps (NRZ) to Line 2x51.5625 Gbps (PAM4) */
    POR_MODE_100G_KP4_TO_KP2,
    /** Host 400GAUI-8 (PAM4) to Line KP4 (PAM4), Host 8x53.125 Gbps (PAM) to Line 4x106.25 Gbps (PAM4) */
    POR_MODE_400G_KP8_TO_KP4,
    /** Host 200GAUI-4 (PAM4) to Line KP2 (PAM4), Host 4x53.125 Gbps (PAM) to Line 2x106.25 Gbps (PAM4) */
    POR_MODE_200G_KP4_TO_KP2,
    /** Host 100GAUI-2 (PAM4) to Line KP1 (PAM4), Host 2x53.125 Gbps (PAM) to Line 1x106.25 Gbps (PAM4) */
    POR_MODE_100G_KP2_TO_KP1,
    /** Host 100GAUI-4 (NRZ) to Line KP1 (PAM4), Host 4x26.5625 Gbps (NRZ) to Line 1x106.25 Gbps (PAM4) */
    POR_MODE_100G_KP4_TO_KP1,
    /** NOT SUPPORTED - Host 4x53.1Gbps (NRZ) to Line 4x53.1Gbps (NRZ)*/
    POR_MODE_200G_4Nx53p1_TO_4Nx53p1,
    /** Host 200GAUI-8 (NRZ) to Line KP4 (PAM4), Host 8x26.5625 Gbps (NRZ) to Line 4x53.1Gbps (PAM4) */
    POR_MODE_200G_KP8_TO_KP4,

    //Protocol Mode limiter
    POR_MODE_PROT_END,

}e_por_protocol_mode;

/**
 * The FEC mode defines the overall flow of data through the FEC blocks.
 *
 * It can be thought of as the output config; whether data is routed around
 * the core (POR_FEC_BYPASS), regenerated in the core (POR_FEC_REGEN), or
 * generated internally (POR_FEC_TP_GEN). 
 * Only FEC_BYPASS mode is supported on Porrima Gen3 device.
 *
 */
typedef enum
{
    /** No FEC encode/decode, output data is from bypass path.
     * Data agnostic, data type can be anything
     */
    POR_FEC_BYPASS = 0,
    
    /** Dummy enum for calculating the end
     * @private
     */
    POR_FEC_MODE_END //must be last

}e_por_fec_mode;

/**
 * The reference clock modes that the ASIC supports
 */
typedef enum
{
    /** Local Reference Clock */
    POR_CLK_MODE_LOCAL   = 0,
    /** Refless Reference Clock */
    POR_CLK_MODE_REFLESS = 1

} e_por_ref_clk_mode;

/**
 * Selected baud-rate, all units are kilo Baud per second (kBd/s). 
 * Note that when the channel is configured for NRZ signalling, the data-rate equals the baud-rate.
 * When configured for PAM signalling, the data-rate is 2x the baud-rate.
 */
typedef enum
{
    /** For KR4 */
    POR_BAUD_RATE_25p8  = 25781250,
    /** For KP4 */
    POR_BAUD_RATE_26p6  = 26562500,
    /** Proprietary Rate */
    POR_BAUD_RATE_41p3  = 41250000,
    /** For KR SL */
    POR_BAUD_RATE_51p6  = 51562500,
    /** For KP SL */
    POR_BAUD_RATE_53p1  = 53125000,
    /** Proprietary Rate */
    POR_BAUD_RATE_56p3  = 56250000,
} e_por_baud_rate;

/**
 * The RX quality-check approximate SNR thresholds
 * PAM supported range: 14p5dB to 21dB
 * NRZ supported range: 10p1dB to 14dB
 */
typedef enum
{
    /** SNR Thresholds (PAM and NRZ) */
    /** SNR 10.1 (dB) */
    POR_LRX_QC_SNR_THRESH_10p1dB   = 0x65,
    /** SNR 10.5 (dB) */
    POR_LRX_QC_SNR_THRESH_10p5dB   = 0x69,
    /** SNR 11 (dB) */
    POR_LRX_QC_SNR_THRESH_11dB     = 0x6E,
    /** SNR 11.5 (dB) */
    POR_LRX_QC_SNR_THRESH_11p5dB   = 0x73,
    /** SNR 12 (dB) */
    POR_LRX_QC_SNR_THRESH_12dB     = 0x78,
    /** SNR 12.5 (dB) */
    POR_LRX_QC_SNR_THRESH_12p5dB   = 0x7D,
    /** SNR 13 (dB) */
    POR_LRX_QC_SNR_THRESH_13dB     = 0x82,
    /** SNR 13.5 (dB) */
    POR_LRX_QC_SNR_THRESH_13p5dB   = 0x87,
    /** SNR 14 (dB) */
    POR_LRX_QC_SNR_THRESH_14dB     = 0x8C,
    /** SNR 14.5 (dB) */
    POR_LRX_QC_SNR_THRESH_14p5dB   = 0x91,
    /** SNR 15 (dB) */
    POR_LRX_QC_SNR_THRESH_15dB     = 0x96,
    /** SNR 15.5 (dB) */
    POR_LRX_QC_SNR_THRESH_15p5dB   = 0x9B,
    /** SNR 16 (dB) */
    POR_LRX_QC_SNR_THRESH_16dB     = 0xA0,
    /** SNR 16.5 (dB) */
    POR_LRX_QC_SNR_THRESH_16p5dB   = 0xA5,
    /** SNR 17 (dB) */
    POR_LRX_QC_SNR_THRESH_17dB     = 0xAA,
    /** SNR 17.5 (dB) */
    POR_LRX_QC_SNR_THRESH_17p5dB   = 0xAF,
    /** SNR 18 (dB) */
    POR_LRX_QC_SNR_THRESH_18dB     = 0xB4,
    /** SNR 18.5 (dB) */
    POR_LRX_QC_SNR_THRESH_18p5dB   = 0xB9,
    /** SNR 19 (dB) */
    POR_LRX_QC_SNR_THRESH_19dB     = 0xBE,
    /** SNR 19.5 (dB) */
    POR_LRX_QC_SNR_THRESH_19p5dB   = 0xC3,
    /** SNR 20 (dB) */
    POR_LRX_QC_SNR_THRESH_20dB     = 0xC8,
    /** SNR 20.5 (dB) */
    POR_LRX_QC_SNR_THRESH_20p5dB   = 0xCD,
    /** SNR 21 (dB) */
    POR_LRX_QC_SNR_THRESH_21dB     = 0xD2,
    /** SNR 21.5 (dB) */
    POR_LRX_QC_SNR_THRESH_21p5dB   = 0xD7,
    /** SNR 22 (dB) */
    POR_LRX_QC_SNR_THRESH_22dB     = 0xDC,
    /** SNR 22.5 (dB) */
    POR_LRX_QC_SNR_THRESH_22p5dB   = 0xE1,
    /** SNR 23 (dB) */
    POR_LRX_QC_SNR_THRESH_23dB     = 0xE6,
    /** SNR 23.5 (dB) */
    POR_LRX_QC_SNR_THRESH_23p5dB   = 0xEB,
    /** SNR 24 (dB) */
    POR_LRX_QC_SNR_THRESH_24dB     = 0xF0,
    /** SNR 24.5 (dB) */
    POR_LRX_QC_SNR_THRESH_24p5dB   = 0xF5,
    /** SNR 25 (dB) */
    POR_LRX_QC_SNR_THRESH_25dB     = 0xFA,
} e_por_lrx_qc_snr_threshold;

/**
 * Helper enum for the nominal fec data rates.
 */
typedef enum
{
    /** 400G */
    POR_NOM_DATA_RATE_400  = 0,
    /** 200G */
    POR_NOM_DATA_RATE_200  = 1,
    /** 100G */
    POR_NOM_DATA_RATE_100 = 2,
    /** 50G */
    POR_NOM_DATA_RATE_50 = 3,
    /* 25G */
    POR_NOM_DATA_RATE_25 = 4,
}e_por_nom_data_rate;

/**
 * FEC NOT supported in PG3
 */
typedef enum
{
    /** Unknown or unsupported type */
    POR_FEC_TYPE_NONE = 0,
} e_por_data_type;

/**
 * FEC loopback mode NOT supported in PG3
 */
typedef enum
{
    /** None */
    POR_FEC_LB_OFF,
} e_por_fec_lb_mode;

/**
 * Advanced clock selection enums
 */
typedef enum
{
    /** Default clock as determined by the FW, based on the configured op_mode */
    POR_CLK_SRC_DEFAULT = 0,
    /** Self-clocked based on the external refclk crystal */
    POR_CLK_SRC_REFCLK,
    /** Recovered clock from the upstream mission-mode receiver */
    POR_CLK_SRC_MM_RECOV,
    /** Recovered clock from the loopback receiver */
    POR_CLK_SRC_LB_RECOV,
} e_por_clk_source;

/**
 * Advanced rules for diagnostics and debug features.
 *
 * Note: Leave these as their defaults unless instructed to by a Inphi AE
 */
typedef struct
{
  /** Disable TIA opt */
    bool tia_opt_dis;

    /**
     *  Enable common LRX LOS to drive LOL0 pin
     *  This rule controls a common LOL pin to be used on the LRX interface. Default is false (i.e., rule not set).
     *
     *  If this rule is set, the LOS state of the LRX channels will be driven on the LOL0 pin as follows:
     *  - If one or more LRX lanes are in an LOS state, the FW will assert LOL0 in addition to asserting the LOL
     *    pin of that lane. If no LRX lanes are in LOS state, the FW will de-assert LOL0.
     *
     *  If the rule is NOT set, then:
     *  - FW will assert/de-assert the LOS on each LOL pin individually as normal, with the LOS state of any LRX
     *    lane depicted only on their respective LOL pin.
     *
     *  NOTE: "LOS" state of a given LRX lane is defined as the inverse of that lane's DSP_READY state.
     *  i.e., LOL pin de/asserted by FW when DSP_READY==1/0. For multiple-die package types,
     *  when the rule is set, the FW de/asserts the LOL0 pin of each die independently.
     */
    bool common_lol0_pin_out;

    /**
     *  Enable common LRX LOS indication on GPIO_0_3P3 pin
     *  This rule controls the use of GPIO_0_3P3 pin to indicate a common LOS on the LRX interface. Default is false (i.e., rule not set).
     *  This rule is identical in behavior to the common_lol0_pin_out rule, except that the output is driven to the GPIO_0_3P3 pin.
     *
     *  If this rule is set, the LOS state of the LRX channels will be driven on the GPIO_0_3P3 pin as follows:
     *  - If one or more LRX lanes are in an LOS state, the FW will assert GPIO_0_3P3. If no LRX lanes are in LOS state,
     *    the FW will de-assert GPIO_0_3P3.
     *
     *  If the rule is NOT set, then:
     *  - No LOS indication is provided to the GPIO_0_3P3 pin.
     *
     *  NOTE: "LOS" state of a given LRX lane is defined as the inverse of that lane's DSP_READY state.
     *  i.e., GPIO_0_3P3 pin de/asserted by FW when DSP_READY==1/0. For multiple-die package types,
     *  when the rule is set, the FW de/asserts the GPIO_0_3P3 pin of each die independently.
     */
    bool gpio_3p3_los_pin_out;

    /**
     * Select hrx_gck_channel
     */
    uint8_t hrx_gck_channel;

    /** Skip the LOS bringup method in the LRX */
    bool skip_los_fuse;

    /** Use the Ingress GCK */
    bool use_ig_gck;

    /** Use the Egress GCK */
    bool use_eg_gck;

    /** LRX clock source
     * - Use POR_CLK_SRC_MM_RECOV to select the HRX recov clock
     * - POR_CLK_SRC_LB_RECOV is invalid
     */
    e_por_clk_source lrx_pll_src;
    /** LTX PLL clock source */
    e_por_clk_source ltx_pll_src;
    /** HTX PLL clock source */
    e_por_clk_source htx_pll_src;


    /**
     * Override LTX FLL BW in mission mode.
     * Larger values are lower BW.
     * 0 is use the FW defaults. Valid values from 1-2.
     */
    uint8_t ltx_fll_bw_mod;

    /**
     * Override HTX FLL BW in mission mode.
     * Larger values are lower BW.
     * 0 is use the FW defaults. Valid values from 1-5.
     */
    uint8_t htx_fll_bw_mod;

    /**
     * Ability to speed up FFE adapt BW to compensate for variable TIA group delay.
     */
    bool lrx_ffe_high_bw_en;

    /** Enable egress lw-bw mode after FCAL/VCOMP is run */
    bool eg_low_bw_en;

    /**
     * Ability to skip the OPZ tirmming on the LTX.
     */
    bool ltx_skip_opz_trim;

    /**
     * Ability to skip the OPZ trimming on the HTX.
     */
    bool htx_skip_opz_trim;

   /** 
     * If this flag is set then all of the chip bundles will be disabled on start-up 
     * and the user will need to selectively enable them on demand
     */
    bool disable_all_bundles;

    /**
     * Disable the HTX FLL SDM on all channels. Default false.
     *
     * Used to resolve interop issues, otherwise leave it false.
     */
    bool htx_fll_sdm_dis;

   /** 
     * Set this flag to configure the chip's clocking for breakout mode. Default is true. The following
     * applies to both ingress and egress paths.
     * 
     * If true, each bundle (in 2:1 gearbox this would be a set of 2x HRX and 1x LTX channels)
     * is treated separately by the FW and can be asynchronous (phase and frequency) from other
     * bundles in the device. Use this mode if sending separate streams of data through the device
     * (ie 4x 100G).
     * 
     * If false, all the channels on the egress or ingress path are combined together to form a single syncronous
     * bundle. Use this mode if sending one stream of data through the device (ie 1x 400G). This behaves
     * similarly to Porrima A (100G DR1) devices.
     */
    bool breakout;

    /** LRX DDLF enable */
    bool lrx_ddlf_en;

    /** LRX low loss detection enable */
    bool lrx_low_loss_det_en;

    /** LRX double restart disable */
    bool lrx_double_restart_dis;

    /** LRX CID LOSD enable */
    bool lrx_cid_losd_det_en;

} por_advanced_rules_t;


/**
 * The signalling mode
 */
typedef enum
{
    /** PAM signalling mode */
    POR_SIGNAL_MODE_PAM = 0,
    /** NRZ signalling mode */
    POR_SIGNAL_MODE_NRZ = 1,

} e_por_signal_mode;

/**
 * The LRX DSP mode (NOT SUPPORTED)
 *
 * These DSP modes apply to the LRX interface only.
 *
 * Each of the suggestions below are only guidelines, your selection of DSP mode is very
 * system dependent. Contact your Inphi customer support rep and start a discussion on which DSP
 * mode is best for your platform.
 *
 * Nomenclature:
 *
 * - FFE is the feed forward equalizer, and is enabled for all modes
 * - Slicer is what slices the PAM4 signal at different voltages, and is enabled for all modes
 * - RC is the reflection canceler, which extends the FFE and smooths out the tail in the pulse response.
 *   Used for links with strong reflections or too much energy in the pulse response tail.
 * - LDEQ is the level-dependent equalizer, which will equalize the eyes differently for each
 *   voltage level. Used for optics which may have non-uniform eye openings at each voltage.
 * - DFE is the decision feedback equalizer, used for strenuous links.
 *
 */
typedef enum
{
    /** PAM4 slicer, used for short non-strenuous links */
    POR_DSP_MODE_SLC1                = 0,
    /** PAM4 slicer with level dependent equalizer, used for non-strenuous optical links */
    POR_DSP_MODE_SLC1_LDEQ           = 1,
    /** PAM4 slicer with reflection canceller */
    POR_DSP_MODE_SLC1_RC_SLC2        = 2,
    /** PAM4 slicer with reflection canceller and level dependent equalizer */
    POR_DSP_MODE_SLC1_RC_LDEQ        = 3,
    /** PAM4 slicer with MPI canceller */
    POR_DSP_MODE_SLC1_MPICAN_SLC2    = 8,
    /** PAM4 slicer with MPI canneller and level dependent equalizer */
    POR_DSP_MODE_SLC1_MPICAN_LDEQ    = 9,
    /** PAM4 slicer with reflection canceller and MPI canceller */
    POR_DSP_MODE_SLC1_RC_MPICAN_SLC2 = 10,
    /** PAM4 slicer with reflection canceller, MPI canceller and level dependent equalizer */
    POR_DSP_MODE_SLC1_RC_MPICAN_LDEQ = 11,
    /** Decision Feedback Equalizer (DFE) */
    POR_DSP_MODE_DFE1                = 4,
    /** DFE with reflection canceller */
    POR_DSP_MODE_DFE1_RC_DFE2        = 7,
    /** DFE with MPI canceller */
    POR_DSP_MODE_DFE1_MPICAN_DFE2    = 13,
    /** DFE with MPI canceller and reflection canceller */
    POR_DSP_MODE_DFE1_RC_MPICAN_DFE2 = 15,

} e_por_dsp_mode;

/**
 * The Transmitter Look-Up-Table (LUT) configuration
 */
typedef enum
{
    /**
     * Bypass mode
     *
     * FW will not touch the DSP_CFG and COEFF/LUT_ACCESS registers to allow loading of custom config.
     * The FW will still save/restore the LUT and COEFF memory when resetting the DSP.
     *
     * @{note, Using this mode will automatically enable the squelch_lock on that channel, forcing you to
     * take full control of the Tx LUT programming and unsquelch.}
     *
     * @see por_tx_man_config, por_tx_squelch
     */
    POR_TX_LUT_BYPASS   = 1,
    /**
     * 4-tap non-linear mode.
     * Inner eye and taps 0-3 are used to generate a 256-to-1 LUT.
     * Requires LUT to be programmed. 
     */
    POR_TX_LUT_4TAP     = 0,
    /**
     * 7-Tap Linear mode.
     * Does not use LUT, convolution output is used directly.
     */
    POR_TX_LUT_7TAP     = 2,
    /**
     * 7-tap non-linear + LUT mode.
     * The computation is divided into two steps;
     * - Inner eye settings and taps 0-6 are used directly in a small 7x4-to-1 LUT + convolution.
     * - That is then fed into a 128-to-1 LUT.
     */
    POR_TX_LUT_7TAP_LUT = 3,

} e_por_lut_mode;

/**
 * For setting the TX swing
 */
typedef enum
{
    /** 60 percent Tx swing */
    POR_TX_SWING_60p  = 0,
    /** 70 percent Tx swing */
    POR_TX_SWING_70p  = 1,
    /** 80 percent Tx swing */
    POR_TX_SWING_80p  = 2,
    /** 90 percent Tx swing */
    POR_TX_SWING_90p  = 3,
    /** 100 percent Tx swing */
    POR_TX_SWING_100p = 4,
    /** 110 percent Tx swing */
    POR_TX_SWING_110p = 5,
    /** 120 percent Tx swing */
    POR_TX_SWING_120p = 6,
    /** Tx swing not applicable */
    POR_TX_SWING_NA = 7 

} e_por_tx_swing;

/**
 * LOS Assert/De-assert control
 */
typedef enum
{
    /** Input signal amplitude, 50 mv ppd  */
    POR_LOS_CTRL_AMP_50 = 0,
    /** Input signal amplitude, 100 mv ppd  */
    POR_LOS_CTRL_AMP_100 = 1,
    /** Input signal amplitude, 150 mv ppd  */
    POR_LOS_CTRL_AMP_150 = 2,
    /** Input signal amplitude, 200 mv ppd  */
    POR_LOS_CTRL_AMP_200 = 3,
    /** Input signal amplitude, 250 mv ppd  */
    POR_LOS_CTRL_AMP_250 = 4,
    /** Input signal amplitude, 300 mv ppd  */
    POR_LOS_CTRL_AMP_300 = 5,
    /** Input signal amplitude, 350 mv ppd  */
    POR_LOS_CTRL_AMP_350 = 6,

}e_por_los_ctrl_amp;

/** 
 * FLL modes of operation
 */
typedef enum
{
    /** Counter-PD mode */
    POR_FLL_MODE_COUNTER_PD = 0,
    /** BB-PD mode */
    POR_FLL_MODE_BB_PD,
} e_por_fll_mode;

/**
 * This structure contains the rules used to control
 * the line receivers of the device.
 */
typedef struct
{
    /** Channel Enable, set to false to cause the FW to ignore this channel. Channels set to false
     * will be set to a low power mode. */
    bool channel_enable;

    /** Signalling type, NRZ or PAM */
    e_por_signal_mode signalling;

    /** Baud rate - overides top level interface baud rate */
    uint32_t baud_rate;

    /** DSP mode */
    e_por_dsp_mode dsp_mode;

    /** IEEE Demap flag */
    bool ieee_demap;

    /** Gray mapping */
    bool gray_mapping;

    /** DFE pre-coder enable
     * The DFE precoder helps to transform
     * burst errors from the DFE to error events with smaller number of bit
     * flips in order to improve BER. The precoder should not be turned on in
     * non-DFE modes since it can actually increase the BER.
     *
     * Note that the link partner's receive precoder must be enabled if
     * this rule is set to true.
     */
    bool dfe_precoder_en;

    /** Rx channel inversion */
    bool invert_chan;

    /** Enable VGA tracking */
    bool vga_tracking_en;


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

} por_lrx_rules_t;

/**
 * This structure contains the rules used to control
 * the host receivers of the device.
 */
typedef struct
{
    /** Channel Enable, set to false to cause the FW to ignore this channel. Channels set to false
     * will be set to a low power mode. */
    bool channel_enable;

    /** Signalling, whether PAM or NRZ */
    e_por_signal_mode signalling;

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

} por_hrx_rules_t;

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

    /** Signalling type, NRZ or PAM */
    e_por_signal_mode signalling;

    /** Baud rate - overides top level interface baud rate */
    uint32_t baud_rate;

    /**
     * LUT mode
     *
     * Note there are special restrictions around POR_TX_LUT_BYPASS, see the e_por_lut_mode and por_tx_man_config
     * documentation for more details.
     */
    e_por_lut_mode lut_mode;

    /** IEEE Demap flag */
    bool ieee_demap;

    /** Gray mapping */
    bool gray_mapping;

    /** Tx channel inversion */
    bool invert_chan;

    /** Constant peak-to-peak voltage */
    bool const_vpk;

    /** Tx swing adjustment, See e_por_tx_swing enum */
    e_por_tx_swing swing;

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
     * The DFE precoder helps to transform
     * burst errors from the DFE to error events with smaller number of bit
     * flips in order to improve BER. The precoder should not be turned on in
     * non-DFE modes since it can actually increase the BER.
     *
     * Note that the link partner's receive precoder must be enabled if
     * this rule is set to true.
    */
    bool dfe_precoder_en;

    /* 
     * Set to true to put the FLL in pd mode. Set to false to disable FLL pd mode. 
    */
    e_por_fll_mode fll_mode;


} por_tx_rules_t;

/**
 * FEC rules
 */
typedef struct
{
    /** Whether the FEC core is enabled or not */
    bool enable;

    /** per-FEC mode, which in certain configs may be different between the ingress/egress */
    e_por_fec_mode mode;

    /** Input number of lanes from the Rx (not the loopback) */
    uint8_t num_in_chs;

    /** Output number of lanes to the Tx (not the loopback) */
    uint8_t num_out_chs;

    /** Nominal data rate through the FEC (100/200/etc, not exact rates) */
    e_por_nom_data_rate nom_data_rate;

    /** FEC input data type to the core */
    e_por_data_type in_fec_type;

    /** FEC output data type from the core */
    e_por_data_type out_fec_type;

    /** Loopback input config
     * If we're getting data from the other FEC, which path do we get it from?
     */
    e_por_fec_lb_mode lb_in_mode;

    /** Loopback output config
     * If we're sending data to the other FEC, which path does it come from?
     */
    e_por_fec_lb_mode lb_out_mode;

} por_fec_rules_t;

typedef enum
{
    POR_DRIVER_TYPE_NONE = 0,
    POR_DRIVER_TYPE_EML,
    POR_DRIVER_TYPE_SIPHO,
    POR_DRIVER_TYPE_1VPP,

} e_por_driver_type;

/**
 * This structure contains the LRX quality-check rules.
 *
 */
typedef struct
{

    /** LRX QC SNR Threshold - Enter MM (default PAM:17dB, NRZ:19dB)
    */
    e_por_lrx_qc_snr_threshold snr_threshold_mm_enter;

    /** LRX QC SNR Threshold - Exit MM (default PAM:16dB, NRZ:18dB) 
    */
    e_por_lrx_qc_snr_threshold snr_threshold_mm_exit;

   /** The max allowable error percentage in the LRX DSP slicer location in order that the LRX state
      * can be deemed to be of acceptable quality.
      * 0% means the slicer has to be exactly the ideal value.
      * 100% means the slicer can deviate +/-100% from the ideal value.
      * Value is rounded down to the nearest 10% (ie 97% gets truncated to 90%) (default:50%)
      */
    uint8_t slc_err_limit;

} por_lrx_qc_rules_t;

/**
 * This structure contains the rules used to control
 * the operational behavior of the device.
 */
typedef struct
{
    /** The ASIC package type */
    e_por_package_type package_type;

    /** If the package AND driver type are unmapped in the EFUSE, this specifies the bare die driver type */
    e_por_driver_type driver_type_override;

    /** The operational mode of the device */
    e_por_operational_mode operational_mode;

    /** The protocol mode of the device */
    e_por_protocol_mode protocol_mode;

    /** FEC_MODE */
    e_por_fec_mode fec_mode;

    /** Line baud rate, in kilo-bauds/second
     * @see e_por_baud_rate
     */
    uint32_t line_baud_rate;

    /** Host baud rate, in kilo-bauds/second
     * @see e_por_baud_rate
     */
    uint32_t host_baud_rate;

    /** The reference clock mode */
    e_por_ref_clk_mode ref_clk_mode;

    /** reference clock rate, units are kHz. Only 156.250 MHz currently supported */
    uint32_t ref_clk;


    /** Flag to enable debug prints in the API */
    bool show_debug_info;

    /** Firmware download time-out value, units are 100 microseconds (default 5000 or 500ms) */
    uint32_t fw_dwld_timeout;

    /**
     * IEEE Demap, sometimes called bit order. True to use the IEEE standard bit order of LSB-first,
     * false to use legacy Inphi bit order of MSB-first.
     *
     * This should always be left to true unless the other device Porrima is connected
     * to (on either host or line) is a legacy Inphi device (ie 28nm PAM B0). Even in those cases, the
     * latest APIs for legacy devices support IEEE mode, and should be enabled on those devices.
     * */
    bool ieee_demap;

    /**
     * If this flag is set a warning will be generated if the firmware
     * version detected does not match the one the API was bundled with
     */
    bool fw_warn_if_mismatched;

    /**
     * LTX xbar has up to four HRX channel selections per single LTX channel (4:1 forward gearbox)
     */
    uint8_t ltx_xbar_src_chan[POR_MAX_LTX_CHANNELS+1][4];

    /**
     * LTX CLK xbar provides configurability of a clock source for each LTX channel
     */
    uint8_t ltx_clk_xbar[POR_MAX_LTX_CHANNELS+1];

    /**
     * Specifies the LRX channel and offset used as a source for the given HTX channel.  
     * Each LRX channel can contain up to 4 host channels of data.
     * - htx_xbar_src_chan[channel][0] - Specifies the SRC channel
     * - htx_xbar_src_chan[channel][1] - Specifies the offset within the SRC channel (Valid values are 0, 1, 2, 3)
     */
    uint8_t htx_xbar_src_chan[POR_MAX_HTX_CHANNELS+1][2];

    /**
     * HTX CLK xbar provides configurability of a clock source for each HTX channel
     */
    uint8_t htx_clk_xbar[POR_MAX_HTX_CHANNELS+1];


    /** Line receive rules */
    por_lrx_rules_t lrx[POR_MAX_LRX_CHANNELS+1];

    /** Host receive rules */
    por_hrx_rules_t hrx[POR_MAX_HRX_CHANNELS+1];

    /** Line transmit rules */
    por_tx_rules_t ltx[POR_MAX_LTX_CHANNELS+1];

    /** Host transmit rules */
    por_tx_rules_t htx[POR_MAX_HTX_CHANNELS+1];

    /** Ingress FEC rules */
    por_fec_rules_t ig_fec;
    /** Egress FEC rules */
    por_fec_rules_t eg_fec;

    /** Advanced rules */
    por_advanced_rules_t advanced;

    /** SDT (LOS De-assert) threshold (units are e_por_los_ctrl_amp enum) */
    e_por_los_ctrl_amp lrx_los_dsrt_ctrl_startup;

    /** LOS Assert threshold during startup (units are e_por_los_ctrl_amp enum) */
    e_por_los_ctrl_amp lrx_los_asrt_ctrl_startup;

    /** LOS Assert threshold during datamode (units are e_por_los_ctrl_amp enum) */
    e_por_los_ctrl_amp lrx_los_asrt_ctrl_datamode;

    /**
     * LRX quality-check rules, which are common for all LRX channels
     */
    por_lrx_qc_rules_t lrx_qc;

} por_rules_t;

#endif // __POR_RULES_H__
