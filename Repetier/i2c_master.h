#ifndef __IC2_MASTER__
#define __IC2_MASTER__

#include "Reptier.h"

#include <SPI.h>

#include <Wire.h>
#include "QueueList.h"
#include "i2c.h"


#define Receiver 4	// Who I want to talk to
#define LAST_MASTER_PIN 56
/* ---------VARIABLES------- */
extern volatile byte execute_i2c;
extern volatile byte timer_i2c_update;

/* ---------FUNCTIONS------- */
void operator delete(void * p); 
void * operator new(size_t size); 

void i2c_update_pin_value( int pin, int value);
void i2c_update_pin_type( int pin, int type);
int i2c_read_pin_value( int pin );

#define WRITE_VPIN(i, t) i2c_update_pin_value(  i, t)
#define READ_VPIN(i) i2c_read_pin_value( i )
#define VPIN_MODE(i, v) i2c_update_pin_type( i, v)




void i2cReceiveEvent(int howMany);
void setup_slave_master() ;

void i2c_send_get( int slave_number );
void i2c_send_update();
void i2c_update();

void check_i2c_periodical();



#endif // __IC2_MASTER__
