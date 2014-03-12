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
#define NUM_BOARD           5 // number of board 
#define PINS_PER_BOARD      (54+14)

#define BUFFER_LENGTH		32

#define EPS_BASETIME		(200)
#define HANDSHAKE_TIME		(1)
#define PING_PONG_DELAY		(1)

/*#define EPS_BASETIME		400 //ms
#define HANDSHAKE_TIME		(EPS_BASETIME/EPS_BASETIME)
#define PING_PONG_DELAY		(800/EPS_BASETIME)
*/
#define GET_DELAY			(100)
#define SEND_UPDATE_DELAY	(1)
#define TOKEN_DELAY			2
#endif // __CONFIGURATION_EPS_H__
