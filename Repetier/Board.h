#ifndef __BOARD_H__
#define __BOARD_H__

#include "Reptier.h"

#include "Pin.h"
#include "Update.h"

#define BOARD_CHECK_OK    0
#define BOARD_CHECK_WAIT_PONG   1
#define BOARD_CHECK_DELAY   10*5 //total time is : 100ms * board_check_timer = 5sec

class Board
{
    public:
    Board();
    Pin pin_values[PINS_PER_BOARD];
    byte connected;
    uint8_t check_state; 
    QueueList<Update> pin_update_queue;   
};


void check_boards_connected();

#endif
