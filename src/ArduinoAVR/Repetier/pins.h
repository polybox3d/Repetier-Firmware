#ifndef PINS_H
#define PINS_H

/*
The board assignment defines the capabilities of the motherboard and the used pins.
Each board definition follows the following scheme:

CPU_ARCH
  ARCH_AVR for AVR based boards
  ARCH_ARM for all arm based boards

STEPPER_CURRENT_CONTROL
  CURRENT_CONTROL_MANUAL  1  // mechanical poti, default if not defined
  CURRENT_CONTROL_DIGIPOT 2  // Use a digipot like RAMBO does
  CURRENT_CONTROL_LTC2600 3  // Use LTC2600 like Foltyn 3D Master

*/

#define ARCH_AVR 1
#define ARCH_ARM 2

#define CURRENT_CONTROL_MANUAL  1  // mechanical poti, default if not defined
#define CURRENT_CONTROL_DIGIPOT 2  // Use a digipot like RAMBO does
#define CURRENT_CONTROL_LTC2600 3  // Use LTC2600 like Foltyn 3D Master

/****************************************************************************************
* Arduino Mega pin assignment
*
****************************************************************************************/
#if MOTHERBOARD == 33
#define MOTHERBOARD 3
#define RAMPS_V_1_3
#elif MOTHERBOARD == 34
#define MOTHERBOARD 3
#define RAMPS_V_1_3
#define AZTEEG_X3
#endif
#if MOTHERBOARD == 3
#define KNOWN_BOARD 1

//////////////////FIX THIS//////////////
#ifndef __AVR_ATmega1280__
#ifndef __AVR_ATmega2560__
#error Oops!  Make sure you have 'Arduino Mega' selected from the 'Tools -> Boards' menu.
#endif
#endif


/**********************************************************************\
 * ******************************************************************* |
 *                    POLYBOX ADD									   |
 * ******************************************************************* |
 * ********************************************************************/
#define PIN_ANALOG			54
// detect slave
#define DETECTION_SLAVE_1	19
#define DETECTION_SLAVE_2	16
#define DETECTION_SLAVE_3	17
#define DETECTION_SLAVE_4	18
#define DETECTION_SLAVE_5	-1

/***********************************************************************
 *                    Printer
 * ********************************************************************/
#define ID_BOARD_PRINTER	2

#define DETECTION_E0		(34 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define DETECTION_E1		(52 +PINS_PER_BOARD*ID_BOARD_PRINTER)

#define HEATER_BED_0		(2 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define HEATER_BED_1		(3 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define HEATER_BED_2		(46 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define HEATER_BED_3		(44 +PINS_PER_BOARD*ID_BOARD_PRINTER)

#define HEATER_BED_0_SENSOR	(11 +PIN_ANALOG)
#define HEATER_BED_1_SENSOR	(12 +PIN_ANALOG)
#define HEATER_BED_2_SENSOR	(13 +PIN_ANALOG)
#define HEATER_BED_3_SENSOR	(14 +PIN_ANALOG)

#define DETECTION_BED_0		(42 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define DETECTION_BED_1		(40 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define DETECTION_BED_2		(38 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define DETECTION_BED_3		(36 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define DETECTION_OPT		(28 +PINS_PER_BOARD*ID_BOARD_PRINTER)

#define E0_FILAMENT_0		(30 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define E0_FILAMENT_1		(32 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define E1_FILAMENT_0		(48 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define E1_FILAMENT_1		(50 +PINS_PER_BOARD*ID_BOARD_PRINTER)

#define PEL_E0				(11 +PINS_PER_BOARD*ID_BOARD_PRINTER)
#define PEL_E1				(8 +PINS_PER_BOARD*ID_BOARD_PRINTER)


/***********************************************************************
 *                    CN
 * ********************************************************************/
#define ID_BOARD_CN 		3
#define CN_MOD_PROX			(22 +PINS_PER_BOARD*ID_BOARD_CN)
#define CN_MOD_MANUAL		(23 +PINS_PER_BOARD*ID_BOARD_CN)
#define CN_GEST_INT			(25 +PINS_PER_BOARD*ID_BOARD_CN)
#define CN_GEST_EXT			(27 +PINS_PER_BOARD*ID_BOARD_CN)
#define CN_PRES_LUB			(37 +PINS_PER_BOARD*ID_BOARD_CN)
#define CN_PRES_VACUUM		(43 +PINS_PER_BOARD*ID_BOARD_CN)

#define CN_STATE_LUB		(35 +PINS_PER_BOARD*ID_BOARD_CN)
#define CN_STATE_VACUUM		(41 +PINS_PER_BOARD*ID_BOARD_CN)
#define CN_STATE_RECYCLE	(39 +PINS_PER_BOARD*ID_BOARD_CN)

#define CN_LUB_LEVEL_LOW	(15+PIN_ANALOG +PINS_PER_BOARD*1)
#define CN_LUB_LEVEL_MEDIUM	(14+PIN_ANALOG +PINS_PER_BOARD*1)
#define CN_LUB_LEVEL_HIGH	(13+PIN_ANALOG +PINS_PER_BOARD*1)

/***********************************************************************
 *                    ATU / INTER
 * ********************************************************************/
#define ID_BOARD_ATU 		1
#define ATU_MAIN			(25 +PINS_PER_BOARD*ID_BOARD_ATU)

/***** POWER *****/
///inter
#define INTER_POWER_0		51
#define INTER_POWER_1		53
///same, x2 for safety
#define INTER_COM_ONOFF_00	(28 +PINS_PER_BOARD*ID_BOARD_ATU)
#define INTER_COM_ONOFF_11	(30 +PINS_PER_BOARD*ID_BOARD_ATU)
///monitor
#define MON_POWER_0			1
#define MON_POWER_1			0
///same, x2 for safety
#define MON_POWER_00		(19 +PINS_PER_BOARD*ID_BOARD_ATU)
#define MON_POWER_11		(18 +PINS_PER_BOARD*ID_BOARD_ATU)

/***** FUNCTIONS *****/
//labviewmodule
#define INTER_LVM			(22 +PINS_PER_BOARD*ID_BOARD_ATU)
#define INTER_HEATER_BOX	(23 +PINS_PER_BOARD*ID_BOARD_ATU)
#define INTER_TOOL			(24 +PINS_PER_BOARD*ID_BOARD_ATU)
#define MON_PRE_ASI_0		(7 +PIN_ANALOG +PINS_PER_BOARD*ID_BOARD_ATU)
#define MON_PRE_ASI_1		(6 +PIN_ANALOG +PINS_PER_BOARD*ID_BOARD_ATU)
// Detect if the box (chamber, working space door) is open or not.
#define BOX_OPEN_0_PIN		(0+PINS_PER_BOARD*1)
#define BOX_OPEN_1_PIN		(1+PINS_PER_BOARD*1)
//IC = integrated circuit. Detect if the IC box is open or not.
#define IC_OPEN_0_PIN		(16+PINS_PER_BOARD*1)
#define IC_OPEN_1_PIN		(17+PINS_PER_BOARD*1)

#define SELECT_LVM			(28 +PINS_PER_BOARD*4)

/***********************************************************************
 *                    SCANNER
 * ********************************************************************/
#define ID_BOARD_SC 		3

#define LASER_0_PIN       	(2 +PINS_PER_BOARD*ID_BOARD_SC)
#define L0_STEP_PIN         46
#define L0_DIR_PIN          50
#define L0_ENABLE_PIN       48
#define LASER_0_PRES       	(0 +PINS_PER_BOARD*ID_BOARD_SC)
#define LASER_0_MON       	(14+PIN_ANALOG +PINS_PER_BOARD*ID_BOARD_SC)

#define LASER_1_PIN       	(3+PINS_PER_BOARD*ID_BOARD_SC)
#define L1_STEP_PIN         40
#define L1_DIR_PIN          47
#define L1_ENABLE_PIN       49
#define LASER_1_PRES       	(1 +PINS_PER_BOARD*ID_BOARD_SC)
#define LASER_1_MON       	(15+PIN_ANALOG +PINS_PER_BOARD*ID_BOARD_SC)

#define TABLE0_DETECTED_PIN 32
#define TABLE0_STEP_PIN     10
#define TABLE0_DIR_PIN      29
#define TABLE0_ENABLE_PIN   27

/***********************************************************************
 *                    THERM
 * ********************************************************************/
// -1 to desactivate
#define THERM_BOX0			(8 +PIN_ANALOG)
#define THERM_BOX1			(9 +PIN_ANALOG)
#define THERM_BOX2			(10 +PIN_ANALOG)

#define THERM_ELEC0			(7 +PIN_ANALOG)
#define THERM_ELEC1			(6 +PIN_ANALOG)

#define THERM_B1			(3 +PIN_ANALOG)
#define THERM_CF_B1_B		(5 +PIN_ANALOG)
#define THERM_CF_B1_H		(4 +PIN_ANALOG)

#define THERM_B0			(0 +PIN_ANALOG)
#define THERM_CF_B0_B		(2 +PIN_ANALOG)
#define THERM_CF_B0_H		(1 +PIN_ANALOG)

/***********************************************************************
 *                    Fans
 * ********************************************************************/
#define FAN_CHAMBER_EXT_0		(2 +PINS_PER_BOARD*1)
#define FAN_CHAMBER_PULS_0		(3 +PINS_PER_BOARD*1)

#define FAN_BOARD_PIN			FAN_BOARD_0 ///< repetier fan handler
#define FAN_BOARD_0				(10 +PINS_PER_BOARD*2)
#define FAN_BOARD_1				(9 +PINS_PER_BOARD*2)

#define FAN_CHAMBER_PEL_0		(9 +PINS_PER_BOARD*3)
#define FAN_CHAMBER_PEL_1 		(13 +PINS_PER_BOARD*3)
#define FAN_CHAMBER_PEL_2		(6 +PINS_PER_BOARD*3)
#define FAN_CHAMBER_PEL_3 		(8 +PINS_PER_BOARD*3)

#define FAN_PEL_BUSE_0			(13 +PINS_PER_BOARD*2)
#define FAN_PEL_BUSE_1			(10 +PINS_PER_BOARD*2)

#define FAN_BUSE_0				(5 +PINS_PER_BOARD*2)
#define FAN_BUSE_1				(4 +PINS_PER_BOARD*2)

#define FAN_OPT_0				(4 +PINS_PER_BOARD)

/***********************************************************************
 *                    Monitoring
 * ********************************************************************/
#define MON_FAN_BOX			(15 +PIN_ANALOG)
#define MON_FAN_BOARD_0		(1 +PIN_ANALOG)
#define MON_FAN_BOARD_1		(0 +PIN_ANALOG)
#define MON_FAN_BOX_IN		(3 +PIN_ANALOG +PINS_PER_BOARD)
#define MON_FAN_BOX_OUT		(2 +PIN_ANALOG +PINS_PER_BOARD)
#define MON_FAN_BUSE_0		(1 +PIN_ANALOG +PINS_PER_BOARD*2)
#define MON_FAN_BUSE_1		(8 +PIN_ANALOG +PINS_PER_BOARD*2)
#define MON_FAN_PEL_BOX_0	(2 +PIN_ANALOG +PINS_PER_BOARD*3)
#define MON_FAN_PEL_BOX_1	(1 +PIN_ANALOG +PINS_PER_BOARD*3)
#define MON_FAN_PEL_BOX_2	(0 +PIN_ANALOG +PINS_PER_BOARD*3)
#define MON_FAN_PEL_BOX_3	(13 +PIN_ANALOG +PINS_PER_BOARD*3)
#define MON_PEL_BOX_0		(3 +PIN_ANALOG +PINS_PER_BOARD*3)
#define MON_PEL_BOX_1		(10 +PIN_ANALOG +PINS_PER_BOARD*3)
#define MON_PEL_BOX_2		(11 +PIN_ANALOG +PINS_PER_BOARD*3)
#define MON_PEL_BOX_3		(12 +PIN_ANALOG +PINS_PER_BOARD*3)

#define MON_PEL_BUSE_0		(6 +PIN_ANALOG +PINS_PER_BOARD*2)
#define MON_PEL_BUSE_1		(7 +PIN_ANALOG +PINS_PER_BOARD*2)
#define MON_FAN_PEL_BUSE_0	(3 +PIN_ANALOG +PINS_PER_BOARD*2)
#define MON_FAN_PEL_BUSE_1	(2 +PIN_ANALOG +PINS_PER_BOARD*2)
#define MON_BED_0			(4 +PIN_ANALOG +PINS_PER_BOARD*2)
#define MON_BED_1			(5 +PIN_ANALOG +PINS_PER_BOARD*2)
#define MON_BED_2			(0 +PIN_ANALOG +PINS_PER_BOARD*2)
#define MON_BED_3			(9 +PIN_ANALOG +PINS_PER_BOARD*2)

// optional mesure

#define MON_OPT5			(12 +PIN_ANALOG +PINS_PER_BOARD)
#define MON_OPT4			(11 +PIN_ANALOG +PINS_PER_BOARD)
#define MON_OPT3			(10 +PIN_ANALOG +PINS_PER_BOARD)
#define MON_OPT2			(9 +PIN_ANALOG +PINS_PER_BOARD)
#define MON_OPT1			(8 +PIN_ANALOG +PINS_PER_BOARD)
#define MON_FAN_OPT1		(5 +PIN_ANALOG +PINS_PER_BOARD)
#define MON_FAN_OPT2		(4 +PIN_ANALOG +PINS_PER_BOARD)

/***********************************************************************
 *                    Chamber
 * ********************************************************************/
 
#define DETECTION_PEL_BOX_0	(53 +PINS_PER_BOARD* 3)
#define DETECTION_PEL_BOX_1	(52 +PINS_PER_BOARD* 3)
#define DETECTION_PEL_BOX_2	(50 +PINS_PER_BOARD* 3)
#define DETECTION_PEL_BOX_3	(48 +PINS_PER_BOARD* 3)

#define PEL_BOX_0			(4 +PINS_PER_BOARD*3)
#define PEL_BOX_1 			(10 +PINS_PER_BOARD*3)
#define PEL_BOX_2			(5 +PINS_PER_BOARD*3)
#define PEL_BOX_3	 		(7 +PINS_PER_BOARD*3)


/***********************************************************************
 *                    Rot-X,Rot-Y, Optional
 * ********************************************************************/

#define RX_STEP_PIN         7
#define RX_DIR_PIN          34
#define RX_ENABLE_PIN       36
#define RX_MIN_PIN          (49 +PINS_PER_BOARD*1)
#define RX_MAX_PIN          (51 +PINS_PER_BOARD*1)
#define RX_HOME_PIN         (53 +PINS_PER_BOARD*1)

#define RY_STEP_PIN         6
#define RY_DIR_PIN          38
#define RY_ENABLE_PIN       40
#define RY_MIN_PIN          (52 +PINS_PER_BOARD*1)
#define RY_MAX_PIN          (50 +PINS_PER_BOARD*1)
#define RY_HOME_PIN         (48 +PINS_PER_BOARD*1)

#define OPT_STEP_PIN         9
#define OPT_DIR_PIN          31
#define OPT_ENABLE_PIN       33

/* ___________________POLYBOX ADD_END__________________ */

#define X_STEP_PIN         13
#define X_DIR_PIN          33
#define X_ENABLE_PIN       31
#define X_MIN_PIN          (29 +PINS_PER_BOARD*1)
#define X_MAX_PIN          (31 +PINS_PER_BOARD*1)
#define X_HOME_PIN         (33 +PINS_PER_BOARD*1)

#define Y_STEP_PIN         12
#define Y_DIR_PIN          32
#define Y_ENABLE_PIN       30
/**
 * You need to set FEATURE_TWO_YSTEPPER to true to use 2 motor for Y
 * File : Configuration: l.992
 * **/

#define Y_2_STEP_PIN       -1
#define Y_2_DIR_PIN        -1
#define Y_2_ENABLE_PIN     -1

#define Y_MIN_PIN          (35 +PINS_PER_BOARD*1)
#define Y_MAX_PIN          (37 +PINS_PER_BOARD*1)
#define Y_HOME_PIN         (39 +PINS_PER_BOARD*1)

#define Z_STEP_PIN         8
#define Z_DIR_PIN          25
#define Z_ENABLE_PIN       23
#define Z_MIN_PIN          (41 +PINS_PER_BOARD*1)
#define Z_MAX_PIN          (43 +PINS_PER_BOARD*1)
#define Z_HOME_PIN         (47 +PINS_PER_BOARD*1)

#define E0_STEP_PIN         3
#define E0_DIR_PIN          37
#define E0_ENABLE_PIN       35

#define E1_STEP_PIN         2
#define E1_DIR_PIN          39
#define E1_ENABLE_PIN       41

#define SDPOWER            -1
#define SDSS               53
#define SDCARDDETECT 	   49

#define LED_PIN            13
#define FAN_PIN            9
#define PS_ON_PIN          12

#define HEATER_0_PIN       10 //*******************************
#define HEATER_1_PIN       8
#define HEATER_2_PIN       9
#define TEMP_0_PIN         THERM_B0   // ANALOG NUMBERING
#define TEMP_1_PIN         14   // ANALOG NUMBERING
#define TEMP_2_PIN         THERM_B1
#define E0_PINS E0_STEP_PIN,E0_DIR_PIN,E0_ENABLE_PIN,
#define E1_PINS E1_STEP_PIN,E1_DIR_PIN,E1_ENABLE_PIN,


// these pins are defined in the SD library if building with SD support
#define SCK_PIN          52
#define MISO_PIN         50
#define MOSI_PIN         51
#define MAX6675_SS       53

#ifdef AZTEEG_X3
#define SDSUPPORT true
#define SDCARDDETECTINVERTED false
#define SDCARDDETECT 49
#define FAN_PIN           4
#define FAN2_PIN          5
#define LIGHT_PIN         6
#define BEEPER_PIN        33  // Activate beeper on extension shield
#define BEEPER_TYPE        1

#define E2_STEP_PIN         27  // Only available with X3 shield
#define E2_DIR_PIN          29  // Only available with X3 shield
#define E2_ENABLE_PIN       41  // Only available with X3 shield
#define E3_STEP_PIN         23  // Only available with X3 shield
#define E3_DIR_PIN          25  // Only available with X3 shield
#define E3_ENABLE_PIN       40  // Only available with X3 shield
#define HEATER_3_PIN        17  // Only available with X3 shield
#define TEMP_3_PIN          12  // Only available with X3 shield
#define HEATER_4_PIN        16  // Only available with X3 shield
#define TEMP_4_PIN          5 //11  // Only available with X3 shield

#define E1_PINS E1_STEP_PIN,E1_DIR_PIN,E1_ENABLE_PIN,
#define E2_PINS E2_STEP_PIN,E2_DIR_PIN,E2_ENABLE_PIN,
#define E3_PINS E3_STEP_PIN,E3_DIR_PIN,E3_ENABLE_PIN,


#endif //AZTEEG_X3

#endif

#ifndef CPU_ARCH  // Set default architecture
#define CPU_ARCH ARCH_AVR
#endif

#ifndef SDSSORIG
#define SDSSORIG -1
#endif

#ifndef STEPPER_CURRENT_CONTROL // Set default stepper current control if not set yet.
#define STEPPER_CURRENT_CONTROL CURRENT_CONTROL_MANUAL
#endif

#ifndef FAN_BOARD_PIN
#define FAN_BOARD_PIN -1
#endif

#if NUM_EXTRUDER==1
#define E1_PINS
#endif

#if NUM_EXTRUDER<3
#define E2_PINS
#endif
#define SENSITIVE_PINS {0, 1, X_STEP_PIN, X_DIR_PIN, X_ENABLE_PIN, X_MIN_PIN, X_MAX_PIN, Y_STEP_PIN, Y_DIR_PIN, Y_ENABLE_PIN, Y_MIN_PIN, Y_MAX_PIN, Z_STEP_PIN, Z_DIR_PIN, Z_ENABLE_PIN, Z_MIN_PIN, Z_MAX_PIN, LED_PIN, PS_ON_PIN, \
HEATER_0_PIN, HEATER_1_PIN, FAN_PIN, E0_PINS E1_PINS E2_PINS TEMP_0_PIN, TEMP_1_PIN,SDSS }

#endif //PINS_H
