#include "Polybox.h"


void pin_x_steps( int PIN , int steps )
{
    for( int i=0 ; i<steps ; i++ )
    {
        WRITE_VPIN( PIN, 0);
        delay(3);
        WRITE_VPIN( PIN, 1);
        delay(3);
    }    
}
