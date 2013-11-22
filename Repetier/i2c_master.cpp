#include "i2c_master.h"
/**
 *
 *  boards[x] handle all board, even the master board. Master board is store under boards[0].
 *  Be careful, I2C_board_n id is n+1. i.e master_i2c_device is 1 (0+1).
 *  Same when you receive the id from I2C, you need to -1.
 * 
 * **/

#define Receiver 4	// Who I want to talk to

union fb_tag {
      byte b[2];
      int f;
} fb;

/* ---------VARIABLES------- */
volatile byte timer_i2c_update = 0 ;// 10ms*10 = 100ms; use base counter
Board boards[NUM_BOARD];

/* ---------FUNCTIONS------- */
// define delete operator for Wire() class destructor...
void operator delete(void * p) // or delete(void *, std::size_t)
{
  free(p);
}
void * operator new(size_t size)
{
  return malloc(size);
}

 uint8_t vpin2pin(int vpin)
{
    return vpin%PINS_PER_BOARD;
}
 uint8_t vpin2board(int vpin)
{
    return vpin/PINS_PER_BOARD;
}

 int i2c_read_pin_value( int pin )
{
    return boards[vpin2board(pin)].pin_values[vpin2pin(pin)].value;
}
 uint8_t i2c_read_pin_type( int pin )
{
    return boards[vpin2board(pin)].pin_values[vpin2pin(pin)].type;
}

void i2c_update_pin_value( int pin, int value) {
    uint8_t real_pin = vpin2pin(pin);
    i2c_set_vpin_value( boards[vpin2board(pin)].pin_values, real_pin, value );
    if ( pin >= PINS_PER_BOARD ) // start virtual pin (i.e other Arduino board)
    {
        boards[vpin2board(pin)].pin_update_queue.push( Update{pin, I2C_SET} );
    }
    else
    {
        if ( value == HIGH || value == LOW ) // digital
        {
            digitalWrite( real_pin, value );
        }
        else
        {
            analogWrite( real_pin, value );
        }
    }
}
void i2c_update_pin_type(  int pin, uint8_t type) {
    if ( pin >= PINS_PER_BOARD ) // start virtual pin (i.e other Arduino board)
    // So we need to update the fifo queue.
    {
        boards[vpin2board(pin)].pin_update_queue.push( Update{pin, I2C_SETUP} );
    }
    else
    {
        pinMode(vpin2pin(pin), type );
    }
    i2c_set_vpin_type( boards[vpin2board(pin)].pin_values, vpin2pin(pin), type );
}

void i2cReceiveEvent(int howMany)
{
    //Serial.print(" [ISP ");    
    int sender = Wire.I2C_READ() -1;
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
            i2c_set_vpin_value( boards[sender].pin_values, pin, value );
        }
    }
    else if (action == I2C_PONG &&  boards[sender].check_state==BOARD_WAIT_PONG ) 
    {
        OUT_P_LN("pong");
        boards[sender].check_state = BOARD_OK;
    }
    else if (action == I2C_RESET ) 
    {
        resetFunc();
    }
    else if (action == I2C_INIT ) 
    {
        boards[sender].check_state = BOARD_OK;
        boards[sender].connected = true;
    }
    else if (action == I2C_VERSION ) 
    {
        while ( Wire.available() )
        {
            uint8_t value = Wire.I2C_READ();
            if ( value < BOARD_MIN_VERSION_REQUIRE )
            {
                boards[sender].check_state = BOARD_BAD_VERSION;
            }
            else
            {
                boards[sender].check_state = BOARD_WAIT_INIT;
            }
        }
    }
}


void setup_slave_master() {
    OUT_P_LN("Start i2c");
    Wire.begin( MASTER_ID );                // join i2c bus
    Wire.onReceive(i2cReceiveEvent); // register event  
}


void i2c_send_get( int slave_number ) 
{
    Wire.beginTransmission( slave_number );
    Wire.I2C_WRITE( I2C_GET );
    Wire.endTransmission();
}

void i2c_send_update() 
{
    Update up;
    byte count;
    for (uint8_t i = 1 ; i < NUM_BOARD ; ++i )
    {
        if ( ! boards[i].pin_update_queue.isEmpty() ) 
        {
            count = 2;
            Wire.beginTransmission( i+1 ); // Open th I2C link
            while ( !boards[i].pin_update_queue.isEmpty() && count < BUFFER_LENGTH-2) 
            {
                up = boards[i].pin_update_queue.pop();
                Wire.I2C_WRITE( up.set_setup );
                Wire.I2C_WRITE( up.pin );
                if ( up.set_setup == I2C_SET ) {
                    fb.f=READ_VPIN(up.pin);
                    Wire.I2C_WRITE( fb.b, FB_SIZE );
                    count = count+2+FB_SIZE;
                }    
                else if ( up.set_setup == I2C_SETUP ) {
                    Wire.I2C_WRITE( READ_VPIN_MODE(up.pin) );
                    count = count+2+1;
                }
            }
            Wire.endTransmission();
        }
    }
}


void i2c_update()
{
    i2c_send_update();
    for (uint8_t i = 1 ; i < NUM_BOARD ; ++i )
    {
      i2c_send_get( i+1 );
    }
}


void check_i2c_periodical()
{
  if(++timer_i2c_update>=10)
  {
     timer_i2c_update=0;
     i2c_update();
  }
}

