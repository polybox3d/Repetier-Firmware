#ifndef __IC2_MASTER__
#define __IC2_MASTER__

#include "Reptier.h"

#include <SPI.h>

#include <Wire.h>
#include "QueueList.h"
#include "i2c.h"
#include "Board.h"

#define I2C_CHECK_TIMER 10*10 // *100ms  so it'ts => 10sec timer
#define LAST_MASTER_PIN 56
/* ---------VARIABLES------- */
extern volatile byte timer_i2c_update;
extern volatile uint8_t i2c_check_timer;
/* ---------FUNCTIONS------- */
void operator delete(void * p); 
void * operator new(size_t size); 

class Board;

extern Board boards[NUM_BOARD];
void i2c_update_pin_value( int pin, int value);
void i2c_update_pin_type( int pin, uint8_t type);
int i2c_read_pin_value( int pin );
uint8_t i2c_read_pin_type( int pin );
int board_read_pin_value( uint8_t b, uint8_t pin );
uint8_t board_read_pin_type( uint8_t b, uint8_t pin );

#define WRITE_VPIN(i, t) i2c_update_pin_value(  i, t)
#define READ_VPIN(i) i2c_read_pin_value( i )
#define READ_BPIN( b, i) board_read_pin_value( b, i )
#define READ_VPIN_MODE(i) i2c_read_pin_type( i )
#define READ_BPIN_MODE( b, i) board_read_pin_type( b, i )
#define VPIN_MODE(i, v) i2c_update_pin_type( i, v)




void i2cReceiveEvent(int howMany);
void setup_slave_master() ;

void i2c_send_get( int slave_number );
void i2c_send_update();
void i2c_update();

void check_i2c_periodical();



#endif // __IC2_MASTER__
