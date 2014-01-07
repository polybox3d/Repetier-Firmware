#ifndef __POLYBOX_H__
#define __POLYBOX_H__

#include "eps.h" // Extension pin system, allow to use external board as input/output device.
#include "lvm.h" // LabViewModule, handle light.

extern volatile float filamentPrinted_lastCheck; ///< mm of filament printed since counting started but at previous check (n-1)
extern volatile long encoder_currentSteps; ///< steps count by encoder
extern volatile long encoder_lastSteps; ///< steps count by encoder at last check

extern volatile byte isClogged;
extern volatile uint8_t i2c_update_time;

#define POLY_MCODE_ISCLOGGED  639
byte is_clogged();
byte laser_detected( uint8_t laser_id );
byte check_clogged();
byte is_box_open();
byte is_ic_open();
byte bed_detected( uint8_t bed_id);

void encoder_incr();
void pin_x_steps( int PIN , int steps );

void executeAction(int action, int param);

void check_i2c_periodical();
void check_boards_connected();
void check_all_ATU();

void manage_pwm();

uint8_t get_lub_level();



#endif // __POLYBOX_H__
