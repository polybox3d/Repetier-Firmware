
#ifndef __IC2_MASTER__
#define __IC2_MASTER__


#include "Reptier.h"

#include <Wire.h>
#include "QueueList.h"
#include "i2c.h"




#define LED_OUT 13
#define Receiver 4	// Who I want to talk to
#define LAST_MASTER_PIN 56
/* ---------VARIABLES------- */
int x;
int MyAddress;
char String1[20];
QueueList <Update> pin_update_queue;

volatile byte execute_i2c;
volatile byte timer_i2c_update = 0 ;// 10ms*10 = 100ms; use base counter

/* ---------FUNCTIONS------- */
// define delete operator for Wire() class destructor...
void operator delete(void * p) // or delete(void *, std::size_t)
{
  free(p);
}

void update_pin_value( int pin, int value) {
    set_pin_value( pin, value );
    pin_update_queue.push( Update{pin, I2C_SET} );

}

#define WRITE_PIN(i, t) update_pin_type(i, t)
#define PIN_MODE(i, v) set_pin_type(i, v)

void update_pin_type( int pin, int type) {
    if ( pin > LAST_MASTER_PIN ) // start virtual pin (i.e other Arduino board)
    // So we need to update the fifo queue.
    {
        pin_update_queue.push( Update{pin, I2C_SETUP} );
    }
    pinMode_ext( pin, type );
}

void i2cReceiveEvent(int howMany)
{
    //Serial.print(" [ISP ");    
    int sender = Wire.I2C_READ();
    byte action = Wire.I2C_READ();

    if ( action == I2C_SET ) 
    {
      //  Serial.print("***");
        byte pin = 0;
        int value = 0;
        while ( Wire.available() )
        {
            pin = Wire.I2C_READ();
            value = Wire.I2C_READ() << 8;
            value += Wire.I2C_READ();
            //check si c'ets bien une pin INPUT (eviter la latence induite entre slave/master sur la modif pinMode 
            // (si une pin ets devenu output entre tmeps apr exemple)
            // faire : type == INPUT
            set_pin_value( pin, value );
        }
    }
}


void setup_slave_master() {
    Wire.begin( MASTER_ID );                // join i2c bus
    Wire.onReceive(i2cReceiveEvent); // register event  
}


void i2c_send_get( int slave_number ) 
{
    Wire.beginTransmission( slave_number );
    Wire.I2C_WRITE( I2C_GET );
    Wire.endTransmission();
//    Serial.print("[MASTER] I2C send end <-");
//    Serial.flush();
}

void i2c_send_update() 
{
    if ( !pin_update_queue.isEmpty() ) 
    {
        byte count = 2;
        Wire.beginTransmission( 4 ); // Open th I2C link
        //Wire.write( MASTER_ID );
        while ( !pin_update_queue.isEmpty() && count < BUFFER_LENGTH-2) 
        {
            Update up = pin_update_queue.pop();
            Wire.I2C_WRITE( up.set_setup );
            Wire.I2C_WRITE( up.pin );
            if ( up.set_setup == I2C_SET ) {
                fb.f=pin_values[up.pin].value;
                Wire.I2C_WRITE( fb.b, FB_SIZE );
                count = count+2+FB_SIZE;
            }
            else if ( up.set_setup == I2C_SETUP ) {
                Wire.I2C_WRITE( pin_values[up.pin].type );
                count = count+2+1;
            }
        }
        Wire.endTransmission();
    }
}


void i2c_update()
{
    i2c_send_update();
    i2c_send_get( 4 );    
}


void check_i2c_periodical()
{
  if(!execute_i2c) return;
  execute_i2c=0;
  if(++timer_i2c_update>=10)
  {
     timer_i2c_update=0;
     i2c_update();
  }
}



#endif // __IC2_MASTER__

