/*
    This file is part of Repetier-Firmware.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Repetier-Firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef _ui_h
#define _ui_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#define COMPAT_PRE1
#endif
#include <avr/pgmspace.h>
#include "gcode.h"

// ----------------------------------------------------------------------------
//                          Action codes
// 1-999     : Autorepeat
// 1000-1999 : Execute
// 2000-2999 : Write code
// 4000-4999 : Show menu
// Add UI_ACTION_TOPMENU to show a menu as top menu
// ----------------------------------------------------------------------------

#define UI_ACTION_TOPMENU 8192

#define UI_ACTION_NEXT 1
#define UI_ACTION_PREVIOUS 2

#define UI_ACTION_X_UP                 100
#define UI_ACTION_X_DOWN               101
#define UI_ACTION_Y_UP                 102
#define UI_ACTION_Y_DOWN               103
#define UI_ACTION_Z_UP                 104
#define UI_ACTION_Z_DOWN               105
#define UI_ACTION_EXTRUDER_UP          106
#define UI_ACTION_EXTRUDER_DOWN        107
#define UI_ACTION_EXTRUDER_TEMP_UP     108
#define UI_ACTION_EXTRUDER_TEMP_DOWN   109
#define UI_ACTION_HEATED_BED_UP        110
#define UI_ACTION_HEATED_BED_DOWN      111
#define UI_ACTION_FAN_UP               112
#define UI_ACTION_FAN_DOWN             113

#define UI_ACTION_DUMMY 10000
#define UI_ACTION_BACK                  1000
#define UI_ACTION_OK                    1001
#define UI_ACTION_MENU_UP               1002
#define UI_ACTION_TOP_MENU              1003
#define UI_ACTION_EMERGENCY_STOP        1004
#define UI_ACTION_XPOSITION             1005
#define UI_ACTION_YPOSITION             1006
#define UI_ACTION_ZPOSITION             1007
#define UI_ACTION_EPOSITION             1008
#define UI_ACTION_BED_TEMP              1009
#define UI_ACTION_EXTRUDER_TEMP         1010
#define UI_ACTION_SD_DELETE             1012
#define UI_ACTION_SD_PRINT              1013
#define UI_ACTION_SD_PAUSE              1014
#define UI_ACTION_SD_CONTINUE           1015
#define UI_ACTION_SD_UNMOUNT            1016
#define UI_ACTION_SD_MOUNT              1017
#define UI_ACTION_XPOSITION_FAST        1018
#define UI_ACTION_YPOSITION_FAST        1019
#define UI_ACTION_ZPOSITION_FAST        1020
#define UI_ACTION_HOME_ALL              1021
#define UI_ACTION_HOME_X                1022
#define UI_ACTION_HOME_Y                1023
#define UI_ACTION_HOME_Z                1024
#define UI_ACTION_SELECT_EXTRUDER1      1025
#define UI_ACTION_OPS_RETRACTDISTANCE   1026
#define UI_ACTION_OPS_BACKLASH          1027
#define UI_ACTION_OPS_MOVE_AFTER        1028
#define UI_ACTION_OPS_MINDISTANCE       1029
#define UI_ACTION_STORE_EEPROM          1030
#define UI_ACTION_LOAD_EEPROM           1031
#define UI_ACTION_PRINT_ACCEL_X         1032
#define UI_ACTION_PRINT_ACCEL_Y         1033
#define UI_ACTION_PRINT_ACCEL_Z         1034
#define UI_ACTION_MOVE_ACCEL_X          1035
#define UI_ACTION_MOVE_ACCEL_Y          1036
#define UI_ACTION_MOVE_ACCEL_Z          1037
#define UI_ACTION_MAX_JERK              1038
#define UI_ACTION_MAX_ZJERK             1039
#define UI_ACTION_BAUDRATE              1040
#define UI_ACTION_HOMING_FEEDRATE_X     1041
#define UI_ACTION_HOMING_FEEDRATE_Y     1042
#define UI_ACTION_HOMING_FEEDRATE_Z     1043
#define UI_ACTION_MAX_FEEDRATE_X        1044
#define UI_ACTION_MAX_FEEDRATE_Y        1045
#define UI_ACTION_MAX_FEEDRATE_Z        1046
#define UI_ACTION_STEPS_X               1047
#define UI_ACTION_STEPS_Y               1048
#define UI_ACTION_STEPS_Z               1049
#define UI_ACTION_FAN_OFF               1050
#define UI_ACTION_FAN_25                1051
#define UI_ACTION_FAN_50                1052
#define UI_ACTION_FAN_75                1053
#define UI_ACTION_FAN_FULL              1054
#define UI_ACTION_FEEDRATE_MULTIPLY     1055
#define UI_ACTION_STEPPER_INACTIVE      1056
#define UI_ACTION_MAX_INACTIVE          1057
#define UI_ACTION_PID_PGAIN             1058
#define UI_ACTION_PID_IGAIN             1059
#define UI_ACTION_PID_DGAIN             1060
#define UI_ACTION_DRIVE_MIN             1061
#define UI_ACTION_DRIVE_MAX             1062
#define UI_ACTION_X_OFFSET              1063
#define UI_ACTION_Y_OFFSET              1064
#define UI_ACTION_EXTR_STEPS            1065
#define UI_ACTION_EXTR_ACCELERATION     1066
#define UI_ACTION_EXTR_MAX_FEEDRATE     1067
#define UI_ACTION_EXTR_START_FEEDRATE   1068
#define UI_ACTION_EXTR_HEATMANAGER      1069
#define UI_ACTION_EXTR_WATCH_PERIOD     1070
#define UI_ACTION_PID_MAX               1071
#define UI_ACTION_ADVANCE_K             1072
#define UI_ACTION_SET_ORIGIN            1073
#define UI_ACTION_DEBUG_ECHO            1074
#define UI_ACTION_DEBUG_INFO            1075
#define UI_ACTION_DEBUG_ERROR           1076
#define UI_ACTION_DEBUG_DRYRUN          1077
#define UI_ACTION_POWER                 1078
#define UI_ACTION_PREHEAT_PLA           1079
#define UI_ACTION_COOLDOWN              1080
#define UI_ACTION_HEATED_BED_OFF        1081
#define UI_ACTION_EXTRUDER0_OFF         1082
#define UI_ACTION_EXTRUDER1_OFF         1083
#define UI_ACTION_HEATED_BED_TEMP       1084
#define UI_ACTION_EXTRUDER0_TEMP        1085
#define UI_ACTION_EXTRUDER1_TEMP        1086
#define UI_ACTION_OPS_OFF               1087
#define UI_ACTION_OPS_CLASSIC           1088
#define UI_ACTION_OPS_FAST              1089
#define UI_ACTION_DISABLE_STEPPER       1090
#define UI_ACTION_RESET_EXTRUDER        1091
#define UI_ACTION_EXTRUDER_RELATIVE     1092
#define UI_ACTION_SELECT_EXTRUDER0      1093
#define UI_ACTION_ADVANCE_L             1094
#define UI_ACTION_PREHEAT_ABS           1095
#define UI_ACTION_FLOWRATE_MULTIPLY     1096
#define UI_ACTION_KILL                  1097
#define UI_ACTION_RESET                 1098
#define UI_ACTION_PAUSE                 1099
#define UI_ACTION_EXTR_WAIT_RETRACT_TEMP 1100
#define UI_ACTION_EXTR_WAIT_RETRACT_UNITS 1101

#define UI_ACTION_MENU_XPOS             4000
#define UI_ACTION_MENU_YPOS             4001
#define UI_ACTION_MENU_ZPOS             4002
#define UI_ACTION_MENU_XPOSFAST         4003
#define UI_ACTION_MENU_YPOSFAST         4004
#define UI_ACTION_MENU_ZPOSFAST         4005
#define UI_ACTION_MENU_SDCARD           4006
#define UI_ACTION_MENU_QUICKSETTINGS    4007
#define UI_ACTION_MENU_EXTRUDER         4008
#define UI_ACTION_MENU_POSITIONS        4009
#define UI_ACTION_SHOW_MEASUREMENT		4010
#define UI_ACTION_RESET_MEASUREMENT		4011
#define UI_ACTION_SET_MEASURED_ORIGIN	4012
#define UI_ACTION_SET_P1				4013
#define UI_ACTION_SET_P2				4014
#define UI_ACTION_SET_P3				4015
#define UI_ACTION_CALC_LEVEL			4016

#define UI_ACTION_SHOW_USERMENU1        4101
#define UI_ACTION_SHOW_USERMENU2        4102
#define UI_ACTION_SHOW_USERMENU3        4103
#define UI_ACTION_SHOW_USERMENU4        4104
#define UI_ACTION_SHOW_USERMENU5        4105
#define UI_ACTION_SHOW_USERMENU6        4106
#define UI_ACTION_SHOW_USERMENU7        4107
#define UI_ACTION_SHOW_USERMENU8        4108
#define UI_ACTION_SHOW_USERMENU9        4109
#define UI_ACTION_SHOW_USERMENU10       4110

// Load basic language definition to make sure all values are defined
#include "uilang.h"

#include "Configuration.h"
#include <avr/pgmspace.h>
#include "fastio.h"

//#ifdef COMPILE_I2C_DRIVER

/************************************************************************* 
* Title:    C include file for the I2C master interface 
*           (i2cmaster.S or twimaster.c)
* Author:   Peter Fleury <pfleury@gmx.ch>  http://jump.to/fleury
* File:     $Id: i2cmaster.h,v 1.10 2005/03/06 22:39:57 Peter Exp $
* Software: AVR-GCC 3.4.3 / avr-libc 1.2.3
* Target:   any AVR device
* Usage:    see Doxygen manual
**************************************************************************/

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

#include <avr/io.h>

/** defines the data direction (reading from I2C device) in i2c_start(),i2c_rep_start() */
#define I2C_READ    1
/** defines the data direction (writing to I2C device) in i2c_start(),i2c_rep_start() */
#define I2C_WRITE   0

/** 
 @brief Terminates the data transfer and releases the I2C bus 
 @param void
 @return none
 */
extern void i2c_stop(void);
/** 
 @brief Issues a start condition and sends address and transfer direction 
  
 @param    addr address and transfer direction of I2C device
 @retval   0   device accessible 
 @retval   1   failed to access device 
 */
extern unsigned char i2c_start(unsigned char addr);
/**
 @brief Issues a start condition and sends address and transfer direction 
   
 If device is busy, use ack polling to wait until device ready 
 @param    addr address and transfer direction of I2C device
 @return   none
 */
extern void i2c_start_wait(unsigned char addr);
/**
 @brief Send one byte to I2C device
 @param    data  byte to be transfered
 @retval   0 write successful
 @retval   1 write failed
 */
extern unsigned char i2c_write(unsigned char data);
/**
 @brief    read one byte from the I2C device, request more data from device 
 @return   byte read from I2C device
 */
extern unsigned char i2c_readAck(void);
/**
 @brief    read one byte from the I2C device, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char i2c_readNak(void);
/** 
 @brief    read one byte from the I2C device
 
 Implemented as a macro, which calls either i2c_readAck or i2c_readNak
 
 @param    ack 1 send ack, request more data from device<br>
               0 send nak, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char i2c_read(unsigned char ack);
#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak(); 
/**@}*/



#endif

