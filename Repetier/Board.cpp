#include "Board.h"

uint8_t last_check = 0;

Board::Board()
{
    this->pin_values={};
    this->connected = false;
    this->check_state = BOARD_WAIT_VERSION;
}

void check_boards_connected()
{
    // need to wait more ?
    if ( last_check < BOARD_CHECK_DELAY )
    {
        last_check++;
        return;
    }
    // code to execute
    last_check = 0; // reset cmpt
    for ( uint8_t i = 1; i < NUM_BOARD ; ++i )
    {
        switch ( boards[i].check_state )
        {   
            case BOARD_WAIT_VERSION :
                i2c_send_version( i+1 );
            break;         
            case BOARD_WAIT_INIT :
                i2c_send_action( i+1, I2C_INIT );
            break;
            
            case BOARD_WAIT_PONG :
                boards[i].connected = false ;
                boards[i].check_state = BOARD_WAIT_VERSION;
            break;            
            case BOARD_OK :
                boards[i].check_state = BOARD_WAIT_PONG;
                i2c_send_action( i+1, I2C_PING );
            break;
            default:
            break;
        }
        
    }
}
