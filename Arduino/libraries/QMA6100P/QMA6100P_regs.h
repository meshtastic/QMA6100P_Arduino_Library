//  QMA6100P_regs.h
//
// This is a library written for the SparkFun Triple Axis Accelerometer - QMA6100P

// This file holds the bit fields for the QMA6100P registers.

#define SFE_QMA6100P_CHIP_ID 0x00 //      Retuns "KION" in ASCII
                              //
typedef struct
{
  uint8_t man_id : 8;
} sfe_qma6100p_chip_id_t;


#define SFE_QMA6100P_XADP_L 0x02
typedef struct
{
  uint8_t xadp_l : 8;
} sfe_qma6100p_xadp_l_t;

#define SFE_QMA6100P_XADP_H 0x03
typedef struct
{
  uint8_t xadp_h : 8;
} sfe_qma6100p_xadp_h_t;

#define SFE_QMA6100P_YADP_L 0x04
typedef struct
{
  uint8_t yadp_l : 8;
} sfe_qma6100p_yadp_l_t;

#define SFE_QMA6100P_YADP_H 0x05
typedef struct
{
  uint8_t yadp_h : 8;
} sfe_qma6100p_yadp_h_t;

#define SFE_QMA6100P_ZADP_L 0x06
typedef struct
{
  uint8_t zadp_l : 8;
} sfe_qma6100p_zadp_l_t;

#define SFE_QMA6100P_ZADP_H 0x07
typedef struct
{
  uint8_t zadp_h : 8;
} sfe_qma6100p_zadp_h_t;

#define SFE_QMA6100P_XOUT_L 0x08
typedef struct
{
  uint8_t xout_l : 8;
} sfe_qma6100p_xout_l_t;

#define SFE_QMA6100P_XOUT_H 0x09
typedef struct
{
  uint8_t xout_h : 8;
} sfe_qma6100p_xout_h_t;

#define SFE_QMA6100P_YOUT_L 0x0A
typedef struct
{
  uint8_t yout_l : 8;
} sfe_qma6100p_yout_l_t;

#define SFE_QMA6100P_YOUT_H 0x0B
typedef struct
{
  uint8_t yout_h : 8;
} sfe_qma6100p_yout_h_t;

#define SFE_QMA6100P_ZOUT_L 0x0C
typedef struct
{
  uint8_t zout_l : 8;
} sfe_qma6100p_zout_l_t;

#define SFE_QMA6100P_ZOUT_H 0x0D
typedef struct
{
  uint8_t zout_h : 8;
} sfe_qma6100p_zout_h_t;

#define SFE_QMA6100P_COTR 0x12
// Command Test Response
// Verifies the proper integrated circuit intergrity
typedef struct
{
  uint8_t dc_str : 8; // Default 0b01010101 : 0x55
} sfe_qma6100p_cotr_t;

#define SFE_KXI3X_TSCP 0x14
// Current Tilt Position Register reports current position data
typedef struct
{
  uint8_t face_up_state : 1;   // Z+
  uint8_t face_down_state : 1; // Z-
  uint8_t up_state : 1;        // Y+
  uint8_t down_state : 1;      // Y-
  uint8_t right_state : 1;     // X+
  uint8_t left_state : 1;      // X-
  uint8_t reserved_one : 1;
  uint8_t reserved_two : 1;
} sfe_qma6100p_tscp_t;

#define SFE_QMA6100P_TSPP 0x15
// Previous Tilt Position Register reports previous position data
typedef struct
{
  uint8_t face_up_state : 1;   // Z+
  uint8_t face_down_state : 1; // Z-
  uint8_t up_state : 1;        // Y+
  uint8_t down_state : 1;      // Y-
  uint8_t right_state : 1;     // X+
  uint8_t left_state : 1;      // X-
  uint8_t reserved_one : 1;
  uint8_t reserved_two : 1;
} sfe_qma6100p_tspp_t;

#define SFE_QMA6100P_INS1 0x16
// Reports Tap and Double Tap interrupts according to the bit. Bit
// is cleared when the interrupt latch release register (INT_REL) is read.
typedef struct
{
  uint8_t tap_face_up : 1;   // Z+
  uint8_t tap_face_down : 1; // Z-
  uint8_t tap_up : 1;        // Y+
  uint8_t tap_down : 1;      // Y-
  uint8_t tap_right : 1;     // X+
  uint8_t tap_left : 1;      // X-
  uint8_t reserved_one : 1;
  uint8_t reserved_two : 1;
} sfe_qma6100p_ins1_t;

#define SFE_QMA6100P_INS2 0x17
// Reports which function caused an interrupt
typedef struct
{
  uint8_t tps : 1; // Tilt Position
  uint8_t reserved : 1;
  uint8_t tdts : 2; // Tap/Double Tap
  uint8_t drdy : 1; // Data Ready
  uint8_t wmi : 1;  // Watermark
  uint8_t bfi : 1;  // Buffer full
  uint8_t ffs : 1;  // Free fall
} sfe_qma6100p_ins2_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_ins2_t bits;
} sfe_qma6100p_ins2_bitfield_t;

#define SFE_QMA6100P_INS3 0x18
// Reports which axis and direction of detected motion triggered the wakeup interrupt
typedef struct
{
  uint8_t zpwu : 1; // Z+
  uint8_t znwu : 1; // Z-
  uint8_t ypwu : 1; // Y+
  uint8_t ynwu : 1; // Y-
  uint8_t xpwu : 1; // X+
  uint8_t xnwu : 1; // X-
  uint8_t bts : 1;
  uint8_t wufs : 1;
} sfe_qma6100p_ins3_t;

#define SFE_QMA6100P_STATUS_REG 0x19
// Reports the combined status of the interrupts and the wake/back to sleep state
typedef struct
{
  uint8_t wake : 1;
  uint8_t reserved_one : 3;
  uint8_t combined_int : 1;
  uint8_t reserved_two : 3;
} sfe_qma6100p_status_reg_t;

#define SFE_QMA6100P_INT_REL 0x1A
// Interrupt latch release: when an interrupt is flipped read this status to clear
// interrupt.
typedef struct
{
  uint8_t latch_release : 8;
} sfe_qma6100p_int_rel_t;

#define SFE_QMA6100P_PM 0x11
/* Read/write control register that controls the "MODE"
MODE_BIT : 1, set device into active mode
           0, set device into standby mode
T_RSTB_SINC_SEL<1:0>: Reset clock setting. The preset time is reserved for CIC filter in digital
MCLK_SEL<3:0>: set the master clock to digital
*/
typedef struct
{
  uint8_t MCLK_SEL : 4;
  uint8_t T_RSTB_SINC_SEL : 2;
  uint8_t BLANK : 1;
  uint8_t MODE_BIT : 1;
} sfe_qma6100p_pm_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_pm_t bits;
} sfe_qma6100p_pm_bitfield_t;

#define SFE_QMA6100P_CNTL2 0x1C
// Read/Write control register that controls tilt position state enabling
// Default value: 0b00111111
typedef struct
{
  uint8_t fum : 1;  // Face-Up state (Z+)
  uint8_t fdm : 1;  // Face-Down state (Z-)
  uint8_t upm : 1;  // Up state (Y+)
  uint8_t dom : 1;  // Down state (Y-)
  uint8_t rim : 1;  // Right state (X+)
  uint8_t lem : 1;  // Left state (X-)
  uint8_t cotc : 1; // Command Test Control bit
                    //  The following bits control when an interrupt is generated
                    //  for tilt: 1 = enabled
  uint8_t srst : 1; // Software reset
} sfe_qma6100p_cntl2_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_cntl2_t bits;
} sfe_qma6100p_cntl2_bitfield_t;

#define SFE_QMA6100P_CNTL3 0x1D
// Read/Write control register that provides control of the Output Data Rate (ODR)
// for tilt, tap, wake-up registers.
typedef struct
{
  uint8_t owuf : 3; // ORR wake-up
  uint8_t otdt : 3; // ODR tap/double-tap
  uint8_t otp : 2;  // ODR tilt position
} sfe_qma6100p_cntl3_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_cntl3_t bits;
} sfe_qma6100p_cntl3_bitfield_t;

#define SFE_QMA6100P_CNTL4 0x1E
// Read/write control register that provides more feature set control.
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t obts : 3;
  uint8_t pr_mode : 1;
  uint8_t btse : 1;
  uint8_t wufe : 1;
  uint8_t th_mode : 1;
  uint8_t c_mode : 1;
} sfe_qma6100p_cntl4_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_cntl4_t bits;
} sfe_qma6100p_cntl4_bitfield_t;

#define SFE_QMA6100P_CNTL5 0x1F
// Read/Write control register that providers more feature set control.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t man_sleep : 1;
  uint8_t man_wake : 1;
  uint8_t reserved_one : 2;
  uint8_t adpe : 1;
  uint8_t reserved_two : 3;
} sfe_qma6100p_cntl5_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_cntl5_t bits;
} sfe_qma6100p_cntl5_bitfield_t;

#define SFE_QMA6100P_CNTL6 0x20
// Read/Write control register that providers more feature set control.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t i2c_alc : 2;
  uint8_t reserved_one : 5;
  uint8_t i2c_ale : 1;
} sfe_qma6100p_cntl6_t;

#define SFE_QMA6100P_ODCNTL 0x21
// Control registers that contorls acceleration outputs.
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t osa : 4;
  uint8_t reserved_one : 1;
  uint8_t fstup : 1;
  uint8_t lpro : 1; // 0 - Filter ODR/9 : 1 - Filter ODR/2
  uint8_t iir_bypass : 1;
} sfe_qma6100p_odcntl_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_odcntl_t bits;
} sfe_qma6100p_odcntl_bitfield_t;

#define SFE_QMA6100P_INC1 0x22
// Controls settings for physical interrupt pin
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t spi3e : 1;
  uint8_t stpol : 1;
  uint8_t reserved_one : 1;
  uint8_t iel1 : 1; // Interrupt lactch control, 0 - latched : 1 - pulsed
  uint8_t iea1 : 1; // Interrupt active level control, 0 - LOW : 1 - HIGH
  uint8_t ien1 : 1; // Enable/disable physical interrupt pin
  uint8_t pw1 : 2;
} sfe_qma6100p_inc1_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_inc1_t bits;
} sfe_qma6100p_inc1_bitfield_t;

#define SFE_QMA6100P_INC2 0x23
// Defines behavior for Wake-Up Function and Back To Sleep
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t zpwue : 1; // Z+
  uint8_t znwue : 1; // Z-
  uint8_t ypwue : 1; // Y+
  uint8_t ynwue : 1; // Y-
  uint8_t xpwue : 1; // X+
  uint8_t xnwue : 1; // X-
  uint8_t aoi : 1;
  uint8_t reserved_one : 1;
} sfe_qma6100p_inc2_t;

#define SFE_QMA6100P_INC3 0x24
// Defines which axes can cause a tap based interrupt
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t tfum : 1; // Z+
  uint8_t tfdm : 1; // Z-
  uint8_t tupm : 1; // Y+
  uint8_t tdom : 1; // Y-
  uint8_t trim : 1; // X+
  uint8_t tlem : 1; // X-
  uint8_t tmen : 1; // Alternate masking scheme
  uint8_t undefined : 1;
} sfe_qma6100p_inc3_t;

#define SFE_QMA6100P_INC4 0x25
// Controls which function triggers INT1
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t tpi1 : 1;
  uint8_t wufi1 : 1;
  uint8_t tdti1 : 1;
  uint8_t btsi1 : 1;
  uint8_t drdyi1 : 1;
  uint8_t wmi1 : 1;
  uint8_t bfi1 : 1;
  uint8_t ffi1 : 1;
} sfe_qma6100p_inc4_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_inc4_t bits;
} sfe_qma6100p_inc4_bitfield_t;

#define SFE_QMA6100P_INC5 0x26
// Controls the settings for the physical interrupt pin INT2.
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t aclr1 : 1;
  uint8_t aclr2 : 1;
  uint8_t reserved_one : 1;
  uint8_t iel2 : 1;
  uint8_t iea2 : 1;
  uint8_t ien2 : 1;
  uint8_t pw2 : 2;
} sfe_qma6100p_inc5_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_inc5_t bits;
} sfe_qma6100p_inc5_bitfield_t;

#define SFE_QMA6100P_INC6 0x27
// Controls which function triggers INT2
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t tpi2 : 1;
  uint8_t wufi2 : 1;
  uint8_t tdti2 : 1;
  uint8_t btsi2 : 1;
  uint8_t drdyi2 : 1;
  uint8_t wmi2 : 1;
  uint8_t bfi2 : 1;
  uint8_t ffi2 : 1;
} sfe_qma6100p_inc6_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_inc6_t bits;
} sfe_qma6100p_inc6_bitfield_t;

#define SFE_QMA6100P_TILT_TIMER 0x29
// Initial Count Registers for the tilt position state time (0 to 255 counts)
// Count is calculated as 1/ODR
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t tsc : 8;
} sfe_qma6100p_tilt_timer_t;

#define SFE_QMA6100P_TDTRC 0x2A
// Double tap report control
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t stre : 1;
  uint8_t dtre : 1;
  uint8_t undefined : 6;
} sfe_qma6100p_tdtrc_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_tdtrc_t bits;
} sfe_qma6100p_tdtrc_bitfield_t;

#define SFE_QMA6100P_TDTC 0x2B
// Double tap time counter - see datashet for more specifics.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t tdtc : 8;
} sfe_qma6100p_tdtc_t;

#define SFE_QMA6100P_TTH 0x2C
// Double tap "jerk high" threshold to determine if a tap is detected.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t tth : 8;
} sfe_qma6100p_tth_t;

#define SFE_QMA6100P_TTL 0x2D
// Double tap "jerk low" threshold to determine if a tap is detected.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t ttl : 8;
} sfe_qma6100p_ttl_t;

#define SFE_QMA6100P_FTD 0x2E
// This register contains counter information for any single tap event.
// These settings can be changed on the fly - no need to put IC in stand-by.
// Check datasheet for conversion information.
typedef struct
{
  uint8_t ftdl : 3; // Default low limits is .05 seconds
  uint8_t ftdh : 5; // Default high limit is .05 seconds
} sfe_qma6100p_ftd_t;

#define SFE_QMA6100P_STD 0x2F
// This register contains counter information for any double tap event.
// These settings can be changed on the fly - no need to put IC in stand-by.
// Check datasheet for conversion information.
typedef struct
{
  uint8_t std : 8;
} sfe_qma6100p_std_t;

#define SFE_QMA6100P_TLT 0x30
// This register contains counter information for a tap event.
// These settings can be changed on the fly - no need to put IC in stand-by.
// Check datasheet for conversion information.
typedef struct
{
  uint8_t tlt : 8;
} sfe_qma6100p_tlt_t;

#define SFE_QMA6100P_TWS 0x31
// This register contains counter information for of single and double taps.
// These settings can be changed on the fly - no need to put IC in stand-by.
// Check datasheet for conversion information.
typedef struct
{
  uint8_t tws : 8;
} sfe_qma6100p_tws_t;

#define SFE_QMA6100P_FFTH 0x32
// This register configures the threshold for free fall detection.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t ffth : 8;
} sfe_qma6100p_ffth_t;

#define SFE_QMA6100P_FFC 0x33
// This register configures the counter for free fall detection.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t ffc : 8;
} sfe_qma6100p_ffc_t;

#define SFE_QMA6100P_FFCNTL 0x34
// This register configures the "main control" of the free fall engine i.e.
// engine enable, free fall latch, debouce, etc.
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t offi : 3;
  uint8_t dcrm : 1;
  uint8_t ffdc : 2;
  uint8_t ulmode : 1;
  uint8_t ffie : 1;
} sfe_qma6100p_ffcntl_t;

#define SFE_QMA6100P_TILT_ANGLE_LL 0x37
// This register sets the low-level threshold for tilt angle detection.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t ll : 8;
} sfe_qma6100p_ll_t;

#define SFE_QMA6100P_TILT_ANGLE_HL 0x38
// This register sets the high-level threshold for tilt angle detection.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t hl : 8;
} sfe_qma6100p_hl_t;

#define SFE_QMA6100P_HYST_SET 0x39
// This register sets hysteresis that is placed in between the Screen Rotation states.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t hyst : 6;
  uint8_t reserved : 2;
} sfe_qma6100p_hyst_t;

#define SFE_QMA6100P_LP_CNTL1 0x3A
// This register sets the Averging Filter Contrl which determines both -
// the number of internal aceleration samples to be averaged in low power mode
// and the number of internal acceleration samples to be averaged for digital engines
// operation: tap, double tap.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t reserved_one : 4;
  uint8_t avc : 3;
  uint8_t reserved_two : 1;
} sfe_qma6100p_lp_cntl1_t;

#define SFE_QMA6100P_LP_CNTL2 0x3B
// This register controls the advanced low power settings which can reduce
// the power consumption even more than low power and stand-by modes.
// To change these settings make sure IC is in "stand-by" mode: PC1 bit in CNTL1.
typedef struct
{
  uint8_t lpstpsel : 1;
  uint8_t reserved : 7;
} sfe_qma6100p_lpcntl2_t;

#define SFE_QMA6100P_WUFTH 0x49
// This register sets seven of the ten bits for the wake up threshold.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t wufth : 8;
} sfe_qma6100p_wufth_t;

#define SFE_QMA6100P_BTSWUFTH 0x4A
// This register contains final three of the ten bits of the  back to sleep the threshold and
// the final three of ten bits of the wakup threshold.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t wufth : 3;
  uint8_t undefined_one : 1;
  uint8_t btsth : 3;
  uint8_t undefined_two : 1;
} sfe_qma6100p_btswufth_t;

#define SFE_QMA6100P_BTSTH 0x4B
// This register sets seven of the ten bits for the back to sleep threshold.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t btsth : 8;
} sfe_qma6100p_btsth_t;

#define SFE_QMA6100P_BTSC 0x4C
// This register debounce counter register for the Back-To-Sleep engine.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t btsc : 8;
} sfe_qma6100p_btsc_t;

#define SFE_QMA6100P_WUFC 0x4D
// This register debounce counter register for the Wake-Up Function engine.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t wufc : 8;
} sfe_qma6100p_wufc_t;

#define SFE_QMA6100P_SELF_TEST 0x5D
// The self test enable register.
// Check datasheet for more information.
typedef struct
{
  uint8_t self_test : 8;
} sfe_qma6100p_self_test_t;

#define SFE_QMA6100P_BUF_CNTL1 0x5E
// This register controls the buffer sample threshold.
// The total samples set in this register is dependent on the "BRES" bits in
// BUF_CNTL2.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t smp_th : 8;
} sfe_qma6100p_buf_cntl1_t;

#define SFE_QMA6100P_BUF_CNTL2 0x5F
// This register controls the buffer sample operation.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t bm : 2; // FIFO, Stream, Trigger
  uint8_t undefined : 3;
  uint8_t bfie : 1; // Full interrupt enable bit
  uint8_t bres : 1; // Resolution - 8 or 16 bit samples
  uint8_t bufe : 1; // Activation of sample buffer
} sfe_qma6100p_buf_cntl2_t;

typedef union
{
  uint8_t all;
  sfe_qma6100p_buf_cntl2_t bits;
} sfe_qma6100p_buf_cntl2_bitfield_t;

#define SFE_QMA6100P_BUF_STATUS_1 0x60
// The buffer status registers (buff status one and two) report the number of
// data bytes in the sample buffer.
// The smp_lev word is 10 bits, you can find the remaining three bits in buf_status2.
typedef struct
{
  uint8_t smp_lev : 8;
} sfe_qma6100p_buf_status1_t;

#define SFE_QMA6100P_BUF_STATUS_2 0x61
// The buffer status registers (buf_status_1/2) report the number of
// data bytes in the sample buffer.
// The smp_lev word is 10 bits, you can find the remaining first seven bits in
// buf_status1.
typedef struct
{
  uint8_t smp_lev : 2;
  uint8_t undefined : 5;
  uint8_t buf_trig : 1;
} sfe_qma6100p_buf_status2_t;

#define SFE_QMA6100P_BUF_CLEAR 0x62
// This register clears the sample level bits found in the previous buf_status_1/2
// register. This can be done by writing anything to this register.
// These settings can be changed on the fly - no need to put IC in stand-by.
typedef struct
{
  uint8_t buf_clear : 8;
} sfe_qma6100p_buf_clear_t;

#define SFE_QMA6100P_BUF_READ 0x63
// Buffer Output Register, data is in 2's copmlement format
typedef struct
{
  uint8_t buf_read : 8;
} sfe_qma6100p_buf_read_t;

#define SFE_QMA6100P_ADP_CNTL1 0x64
// This register sets the ODR of the Advanced Data Path and number of samples
// used to calculate RMS output.
typedef struct
{
  uint8_t oadp : 4;
  uint8_t rms_avc : 3;
  uint8_t reserved : 1;
} sfe_qma6100p_adp_cntl1_t;

#define SFE_QMA6100P_ADP_CNTL2 0x65
// This register controls route of data path, wake-up/back-to-sleep,
// filter bypass amongst others.
typedef struct
{
  uint8_t adp_f2_hp : 1;
  uint8_t adp_rms_osel : 1;
  uint8_t undefined : 1;
  uint8_t adp_flt1_byp : 1;
  uint8_t adp_flt2_byp : 1;
  uint8_t rms_wb_osel : 1;
  uint8_t adp_wb_isel : 1;
  uint8_t adp_buf_sel : 1;
} sfe_qma6100p_adp_cntl2_t;

#define SFE_QMA6100P_ADP_CNTL3 0x66
// Sets ADP filter-1 coefficient (1/A)
typedef struct
{
  uint8_t adp_f1_1a : 8;
} sfe_qma6100p_adp_cntl3_t;

#define SFE_QMA6100P_ADP_CNTL4 0x67
// Sets the ADP filter-1 coefficient (B/A)
// Bits [7:0]
typedef struct
{
  uint8_t adp_f1_ba : 8;
} sfe_qma6100p_adp_cntl4_t;

#define SFE_QMA6100P_ADP_CNTL5 0x68
// Sets the ADP filter-1 coefficient (B/A)
// Bits [15:8]
typedef struct
{
  uint8_t adp_f1_ba : 8;
} sfe_qma6100p_adp_cntl5_t;

#define SFE_QMA6100P_ADP_CNTL6 0x69
// Sets the ADP filter-1 coefficient (B/A)
// Bits [22:16]
typedef struct
{
  uint8_t adp_f1_ba : 7;
  uint8_t undefined : 1;
} sfe_qma6100p_adp_cntl6_t;

#define SFE_QMA6100P_ADP_CNTL7 0x6A
// Sets the ADP filter-1 coefficient (C/A)
// Bits [7:0]
typedef struct
{
  uint8_t adp_f1_ca : 8;
} sfe_qma6100p_adp_cntl7_t;

#define SFE_QMA6100P_ADP_CNTL8 0x6B
// Sets the ADP filter-1 coefficient (C/A)
// Bits [15:8]
typedef struct
{
  uint8_t adp_f1_ca : 8;
} sfe_qma6100p_adp_cntl8_t;

#define SFE_QMA6100P_ADP_CNTL9 0x6C
// Sets the ADP filter-1 coefficient (C/A)
// Bits [22:16]
typedef struct
{
  uint8_t adp_f1_ca : 7;
  uint8_t undefined : 1;
} sfe_qma6100p_adp_cntl9_t;

#define SFE_QMA6100P_ADP_CNTL10 0x6D
// Sets the ADP filter-1 input scale shift
typedef struct
{
  uint8_t adp_f1_ish : 5;
  uint8_t undefined : 3;
} sfe_qma6100p_adp_cntl10_t;

#define SFE_QMA6100P_ADP_CNTL11 0x6E
// Sets the ADP filter-2 coefficient (1/A)
typedef struct
{
  uint8_t adp_f2_1a : 7;
  uint8_t adp_f1_osh : 1;
} sfe_qma6100p_adp_cntl11_t;

#define SFE_QMA6100P_ADP_CNTL12 0x6F
// Sets the ADP filter-2 coefficient (B/A)
// Bits [7:0]
typedef struct
{
  uint8_t adp_f2_ba : 8;
} sfe_qma6100p_adp_cntl12_t;

#define SFE_QMA6100P_ADP_CNTL13 0x70
// Sets the ADP filter-2 coefficient (B/A)
// Bits [14:8]
typedef struct
{
  uint8_t adp_f2_ba : 7;
  uint8_t undefined : 1;
} sfe_qma6100p_adp_cntl13_t;

//---------------------------------- Set to Zero by Manufacturer vv ----
#define SFE_QMA6100P_ADP_CNTL14 0x71 // -------------------------------
#define SFE_QMA6100P_ADP_CNTL15 0x72 // -------------------------------
#define SFE_QMA6100P_ADP_CNTL16 0x73 // -------------------------------
#define SFE_QMA6100P_ADP_CNTL17 0x74 // -------------------------------
//---------------------------------- Set to Zero by Manufacturer ^^ ----

#define SFE_QMA6100P_ADP_CNTL18 0x75
// Sets the ADP filter-2 input scale shift
typedef struct
{
  uint8_t adp_f2_ish : 5;
  uint8_t undefined : 3;
} sfe_qma6100p_adp_cntl18_t;

#define SFE_QMA6100P_ADP_CNTL19 0x76
// Sets the ADP filter-2 output scale shift
typedef struct
{
  uint8_t adp_f2_osh : 5;
  uint8_t undefined : 3;
} sfe_qma6100p_adp_cntl19_t;

typedef struct
{
  uint8_t SFE_QMA6100P_SUCCESS = 0x00;
  uint8_t SFE_QMA6100P_GENERAL_ERROR = 0x01;
  uint8_t SFE_QMA6100P_I2C_ERROR = 0x03;
} sfe_error_code_t;