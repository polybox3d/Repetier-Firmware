#ifndef __I2C_H__
#define __I2C_H__


#if defined(ARDUINO) && ARDUINO >= 100
#define I2C_WRITE write
#define I2C_READ read
#include "Arduino.h"
#else
#include "WProgram.h"
#define I2C_WRITE send
#define I2C_READ receive
#endif


#include <inttypes.h>

/** We use an union to send float through I2C/TWI. Union allow us to share memory cell between Float and byte array.
 * So we use union as reinterpret_cast. Kinda classic but usefull.
 * Wire() class can send byte array and string but no float...
 * **/
#define FB_SIZE 2
union fb_tag {
      byte b[2];
      int f;
} fb;


#define PIN_MAX_NUMBER      56*4

#define PIN_TYPE_INPUT      INPUT
#define PIN_TYPE_OUTPUT     OUTPUT
#define PIN_TYPE_DISABLE    0
#define PIN_NOONE           NULL

#define I2C_SETUP           1
#define I2C_SET             2
#define I2C_GET             3
#define I2C_ALL             4

#define MASTER_ID           1

#include "Pin.h"
#include "Update.h"

Pin pin_values[PIN_MAX_NUMBER]= {0};

#define READ_PIN(i) pin_values[i].value

void set_pin_value( uint8_t pin, int value)
{
    pin_values[pin].value = value;
}

void set_pin_type( uint8_t pin, int type)
{
    pin_values[pin].type = type;
}

void pinMode_ext( uint8_t pin, int type)
{
    pinMode( pin, type );
    set_pin_type( pin, type );
}

void set_pin_Ext( uint8_t pin, int value)
{
    set_pin_value( pin, value );
    digitalWrite(pin, value);
}

#endif
