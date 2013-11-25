#ifndef __PIN_H__
#define __PIN_H__

#define PINS_PER_BOARD      56

#define PIN_TYPE_INPUT      INPUT //0
#define PIN_TYPE_OUTPUT     OUTPUT //1
#define PIN_TYPE_DIGITAL    0
#define PIN_TYPE_ANALOG     2
#define PIN_TYPE_DISABLE    4
#define PIN_NOONE           NULL

#define PIN_TYPE_IO_MASK   ( PIN_TYPE_INPUT | PIN_TYPE_OUTPUT )
#define IS_DIGITAL(n) ( n & PIN_TYPE_IO_MASK ) == PIN_TYPE_DIGITAL
#define IS_ANALOG(n) ( n & PIN_TYPE_IO_MASK ) ==  PIN_TYPE_ANALOG
#define GET_IO_TYPE type & PIN_TYPE_IO_MASK


typedef struct Pin {
    uint8_t type;
    int value;
} Pin;



#endif
