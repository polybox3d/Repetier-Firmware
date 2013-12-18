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



/* ___________________POLYBOX ADD_END__________________ */

#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN          3
#define X_MAX_PIN          2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E0_STEP_PIN         26
#define E0_DIR_PIN          28
#define E0_ENABLE_PIN       24

#define E1_STEP_PIN         36
#define E1_DIR_PIN          34
#define E1_ENABLE_PIN       30

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

#define LASER_0_PIN       62
#define L0_STEP_PIN         63
#define L0_DIR_PIN          64
#define L0_ENABLE_PIN       65

#define LASER_1_PIN       66
#define L1_STEP_PIN         67
#define L1_DIR_PIN          68
#define L1_ENABLE_PIN       69

#define TABLE0_DETECTED_PIN         73
#define TABLE0_STEP_PIN         70
#define TABLE0_DIR_PIN          71
#define TABLE0_ENABLE_PIN       72

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

