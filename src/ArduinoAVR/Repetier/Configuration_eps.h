/**
 * Configuration file.
 * Variable you can adjust, like delay timer.
 * 
 * **/

#ifndef __CONFIGURATION_EPS_H__
#define __CONFIGURATION_EPS_H__

//#define IS_SLAVE            1          
#define IS_MASTER            1

#ifdef IS_SLAVE
 #define board boards[0]
 #define WRITE_PIN(p,v) boards[0].write_bpin(p,v)
 #define PIN_MODE(p,t) boards[0].write_bpin_type(p,t)
#endif

#define BOARD_ID            1
#define NUM_BOARD           4 // number of board 
#define PINS_PER_BOARD      56

#define BUFFER_LENGTH		32
#endif // __CONFIGURATION_EPS_H__
