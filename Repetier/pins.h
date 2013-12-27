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


/* ___________________POLYBOX ADD__________________ */

#define Y2_MIN_PIN          4
// Detect if the box (chamber, working space door) is open or not.
#define BOX_OPEN_0_PIN		0+PINS_PER_BOARD*1
#define BOX_OPEN_1_PIN		1+PINS_PER_BOARD*1
//IC = integrated circuit. Detect if the IC box is open or not.
#define IC_OPEN_0_PIN		16+PINS_PER_BOARD*1
#define IC_OPEN_1_PIN		17+PINS_PER_BOARD*1
// detect slave
#define DETECTION_SLAVE_1	18
#define DETECTION_SLAVE_2	19
#define DETECTION_SLAVE_3	16
#define DETECTION_SLAVE_4	17
#define DETECTION_SLAVE_5	-1

/***********************************************************************
 *                    CN
 * ********************************************************************/
#define ID_BOARD_CN 		3
#define CN_MOD_PROX			22 +PINS_PER_BOARD*ID_BOARD_CN
#define CN_MOD_MANUAL		23 +PINS_PER_BOARD*ID_BOARD_CN
#define CN_GEST_INT			25 +PINS_PER_BOARD*ID_BOARD_CN
#define CN_GEST_EXT			27 +PINS_PER_BOARD*ID_BOARD_CN
#define CN_PRES_LUB			37 +PINS_PER_BOARD*ID_BOARD_CN
#define CN_PRES_VACUUM		43 +PINS_PER_BOARD*ID_BOARD_CN

#define CN_STATE_LUB		35 +PINS_PER_BOARD*ID_BOARD_CN
#define CN_STATE_VACUUM		41 +PINS_PER_BOARD*ID_BOARD_CN
#define CN_STATE_RECYCLE	39 +PINS_PER_BOARD*ID_BOARD_CN

#define CN_LUB_LEVEL_LOW	13+54 +PINS_PER_BOARD*ID_BOARD_CN
#define CN_LUB_LEVEL_MEDIUM	12+54 +PINS_PER_BOARD*ID_BOARD_CN
#define CN_LUB_LEVEL_HIGH	11+54 +PINS_PER_BOARD*ID_BOARD_CN

/***********************************************************************
 *                    ATU
 * ********************************************************************/
#define ID_BOARD_ATU 		1
#define ATU_MAIN			25 +PINS_PER_BOARD*ID_BOARD_ATU
// command
#define ATU_COM_ONOFF_0		28 +PINS_PER_BOARD*ID_BOARD_ATU
#define ATU_COM_ONOFF_1		30 +PINS_PER_BOARD*ID_BOARD_ATU
//monitor
#define ATU_MON_ONOFF_0		19 +PINS_PER_BOARD*ID_BOARD_ATU
#define ATU_MON_ONOFF_1		18 +PINS_PER_BOARD*ID_BOARD_ATU
//labviewmodule
#define ATU_LVM				22 +PINS_PER_BOARD*ID_BOARD_ATU
#define ATU_HEATERS_BED_BOX	23 +PINS_PER_BOARD*ID_BOARD_ATU
#define ATU_TOOL			24 +PINS_PER_BOARD*ID_BOARD_ATU
#define ATU_PRE_ASI_0		26 +PINS_PER_BOARD*ID_BOARD_ATU
#define ATU_PRE_ASI_1		27 +PINS_PER_BOARD*ID_BOARD_ATU

/***********************************************************************
 *                    SCANNER
 * ********************************************************************/
#define ID_BOARD_SC 		3

#define LASER_0_PIN       	3 +PINS_PER_BOARD*ID_BOARD_SC
#define L0_STEP_PIN         44
#define L0_DIR_PIN          48
#define L0_ENABLE_PIN       50
#define LASER_0_PRES       	1 +PINS_PER_BOARD*ID_BOARD_SC
#define LASER_0_MON       	14+54 +PINS_PER_BOARD*ID_BOARD_SC

#define LASER_1_PIN       	2+PINS_PER_BOARD*ID_BOARD_SC
#define L1_STEP_PIN         46
#define L1_DIR_PIN          47
#define L1_ENABLE_PIN       49
#define LASER_1_PRES       	0 +PINS_PER_BOARD*ID_BOARD_SC
#define LASER_1_MON       	15+54 +PINS_PER_BOARD*ID_BOARD_SC

#define TABLE0_DETECTED_PIN 32
#define TABLE0_STEP_PIN     5
#define TABLE0_DIR_PIN      38
#define TABLE0_ENABLE_PIN   40



/* ___________________POLYBOX ADD_END__________________ */

#define X_STEP_PIN         13
#define X_DIR_PIN          22
#define X_ENABLE_PIN       24
#define X_MIN_PIN          3
#define X_MAX_PIN          2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         8
#define Z_DIR_PIN          26
#define Z_ENABLE_PIN       28
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E0_STEP_PIN         3
#define E0_DIR_PIN          35
#define E0_ENABLE_PIN       37

#define E1_STEP_PIN         2
#define E1_DIR_PIN          39
#define E1_ENABLE_PIN       41

#define SDPOWER            -1
#define SDSS               53
#define SDCARDDETECT 	    49

#define LED_PIN            13
#define FAN_PIN            9
#define PS_ON_PIN          12
#define KILL_PIN           -1

#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define HEATER_2_PIN       9
#define TEMP_0_PIN         13   // ANALOG NUMBERING
#define TEMP_1_PIN         14   // ANALOG NUMBERING
#define TEMP_2_PIN         15
#define E0_PINS E0_STEP_PIN,E0_DIR_PIN,E0_ENABLE_PIN,
#define E1_PINS E1_STEP_PIN,E1_DIR_PIN,E1_ENABLE_PIN,


// SPI for Max6675 Thermocouple 

// these pins are defined in the SD library if building with SD support  
#define SCK_PIN          52
#define MISO_PIN         50
#define MOSI_PIN         51
#define MAX6675_SS       53

#ifdef AZTEEG_X3
#define SDSUPPORT true
#define SDCARDDETECTINVERTED false
#define SDCARDDETECT -1
#define FAN_PIN           4
#define FAN2_PIN          5
#define LIGHT_PIN         6
#define BEEPER_PIN        33  // Activate beeper on extension shield
#define BEEPER_TYPE        1
#endif

#endif


#ifndef CPU_ARCH  // Set default architecture
#define CPU_ARCH ARCH_AVR
#endif

#ifndef SDSSORIG
#define SDSSORIG -1
#endif

#ifndef STEPPER_CURRENT_CONTROL // Set default stepper current control if not set yet.
#define STEPPER_CURRENT_CONTROL  CURRENT_CONTROL_MANUAL
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
#endif

