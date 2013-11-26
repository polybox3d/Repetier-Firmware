#ifndef __POLYBOX_H__
#define __POLYBOX_H__

#include "eps.h"

extern volatile float filamentPrinted_lastCheck; ///< mm of filament printed since counting started but at previous check (n-1)
extern volatile long encoder_currentSteps; ///< steps count by encoder
extern volatile long encoder_lastSteps; ///< steps count by encoder at last check

extern volatile byte isClogged;
extern volatile uint8_t i2c_update_time;

#define POLY_MCODE_ISCLOGGED  639
byte is_clogged();
byte check_clogged();
void encoder_incr();
void pin_x_steps( int PIN , int steps );

void executeAction(int action, int param);

void check_i2c_periodical();
void check_boards_connected();

#endif // __POLYBOX_H__
