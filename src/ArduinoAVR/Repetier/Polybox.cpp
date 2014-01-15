#include "Polybox.h"
#include "Repetier.h"

/***********************************************************************
 * 
 *    Variables
 * 
 **********************************************************************/
volatile float filamentPrinted_lastCheck = 0.0;
volatile long encoder_currentSteps = 0 ;
volatile long encoder_lastSteps = 0;
volatile byte isClogged = 0;
volatile uint8_t last_check = 0;
volatile uint8_t timer_i2c_update=0;
volatile int timer_i2c_send_get=0;
volatile uint8_t i2c_update_time = BOARD_UPDATE_CHECK_DELAY;
volatile float ic_current_temp = 0; ///< temp inside IC box

#define SETUP_PIN(p,t)  if (p>-1)  VPIN_MODE( p, t)
  
 


/***********************************************************************
 * 
 *    Init./Setup functions 
 * 
 **********************************************************************/
void init_polybox()
{
	setup_slave_master();
	init_slaves();
	init_printer();
	init_cn();
	init_mon();
	init_atu();
	init_scanner();
	init_therm();
}
void init_therm()
{
	SETUP_PIN( THERM_BOX0, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );
	SETUP_PIN( THERM_BOX1, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );
	SETUP_PIN( THERM_BOX2, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );

	SETUP_PIN( THERM_ELEC1, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );
	SETUP_PIN( THERM_ELEC0, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );

	SETUP_PIN( THERM_B1, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );
	SETUP_PIN( THERM_CF_B1_B, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );
	SETUP_PIN( THERM_CF_B1_H, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );

	SETUP_PIN( THERM_B0, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );
	SETUP_PIN( THERM_CF_B0_B, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );
	SETUP_PIN( THERM_CF_B0_H, PIN_TYPE_INPUT| PIN_TYPE_ANALOG );
}
void init_printer()
{
	SETUP_PIN( DETECTION_E0, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_E1, PIN_TYPE_INPUT);
	
	SETUP_PIN( DETECTION_BED_0, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_BED_1, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_BED_2, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_BED_3, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_OPT, PIN_TYPE_INPUT);

	SETUP_PIN( E0_FILAMENT_0, PIN_TYPE_INPUT);
	SETUP_PIN( E0_FILAMENT_1, PIN_TYPE_INPUT);
	SETUP_PIN( E1_FILAMENT_0, PIN_TYPE_INPUT);
	SETUP_PIN( E1_FILAMENT_1, PIN_TYPE_INPUT);
 
	SETUP_PIN( DETECTION_PEL_BOX_0, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_PEL_BOX_1, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_PEL_BOX_2, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_PEL_BOX_3, PIN_TYPE_INPUT);
}
void init_slaves()
{
	SETUP_PIN( DETECTION_SLAVE_1, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_SLAVE_2, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_SLAVE_3, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_SLAVE_4, PIN_TYPE_INPUT);
	SETUP_PIN( DETECTION_SLAVE_5, PIN_TYPE_INPUT);
}
void init_mon()
{
	SETUP_PIN( MON_FAN_BOX, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_BOX_IN, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_BOX_OUT, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_BUSE_0, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_BUSE_1, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_PEL_BOX_0, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_PEL_BOX_1, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_PEL_BOX_2, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_PEL_BOX_3, PIN_TYPE_INPUT);
	SETUP_PIN( MON_PEL_BOX_0, PIN_TYPE_INPUT);
	SETUP_PIN( MON_PEL_BOX_1, PIN_TYPE_INPUT);
	SETUP_PIN( MON_PEL_BOX_2, PIN_TYPE_INPUT);
	SETUP_PIN( MON_PEL_BOX_3, PIN_TYPE_INPUT);

	SETUP_PIN( MON_PEL_BUSE_0, PIN_TYPE_INPUT);
	SETUP_PIN( MON_PEL_BUSE_1, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_PEL_BUSE_0, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_PEL_BUSE_1, PIN_TYPE_INPUT);
	SETUP_PIN( MON_BED_0, PIN_TYPE_INPUT);
	SETUP_PIN( MON_BED_1, PIN_TYPE_INPUT);
	SETUP_PIN( MON_BED_2, PIN_TYPE_INPUT);
	SETUP_PIN( MON_BED_3, PIN_TYPE_INPUT);

// optional mesure

	SETUP_PIN( MON_OPT7, PIN_TYPE_INPUT);
	SETUP_PIN( MON_OPT6, PIN_TYPE_INPUT);
	SETUP_PIN( MON_OPT5, PIN_TYPE_INPUT);
	SETUP_PIN( MON_OPT4, PIN_TYPE_INPUT);
	SETUP_PIN( MON_OPT3, PIN_TYPE_INPUT);
	SETUP_PIN( MON_OPT2, PIN_TYPE_INPUT);
	SETUP_PIN( MON_OPT1, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_OPT2, PIN_TYPE_INPUT);
	SETUP_PIN( MON_FAN_OPT1, PIN_TYPE_INPUT);
}
void init_atu()
{
	SETUP_PIN(ATU_MAIN, PIN_TYPE_INPUT);

	SETUP_PIN( POWER_ONOFF_0, PIN_TYPE_INPUT);
 	SETUP_PIN(POWER_ONOFF_1, PIN_TYPE_INPUT);

 	SETUP_PIN(ATU_COM_ONOFF_0, PIN_TYPE_INPUT);
 	SETUP_PIN(ATU_COM_ONOFF_1, PIN_TYPE_INPUT);

	SETUP_PIN( ATU_MON_POWER_0, PIN_TYPE_INPUT);
	SETUP_PIN( ATU_MON_POWER_1, PIN_TYPE_INPUT);

	SETUP_PIN( ATU_MON_ONOFF_0, PIN_TYPE_INPUT);
	SETUP_PIN( ATU_MON_ONOFF_1, PIN_TYPE_INPUT);

	SETUP_PIN( ATU_LVM, PIN_TYPE_INPUT);
	SETUP_PIN( ATU_HEATERS_BED_BOX, PIN_TYPE_INPUT);
	SETUP_PIN( ATU_TOOL, PIN_TYPE_INPUT);
	SETUP_PIN( ATU_PRE_ASI_0, PIN_TYPE_INPUT);
	SETUP_PIN( ATU_PRE_ASI_1, PIN_TYPE_INPUT);

	SETUP_PIN( BOX_OPEN_0_PIN, PIN_TYPE_INPUT);
	SETUP_PIN( BOX_OPEN_1_PIN, PIN_TYPE_INPUT);
	SETUP_PIN( IC_OPEN_0_PIN, PIN_TYPE_INPUT);
	SETUP_PIN( IC_OPEN_1_PIN, PIN_TYPE_INPUT);
}

void init_cn()
{
	SETUP_PIN( CN_MOD_PROX, PIN_TYPE_INPUT);
	SETUP_PIN( CN_MOD_MANUAL, PIN_TYPE_INPUT);
	SETUP_PIN( CN_GEST_INT, PIN_TYPE_INPUT);
	SETUP_PIN( CN_GEST_EXT, PIN_TYPE_INPUT);
	SETUP_PIN( CN_PRES_LUB, PIN_TYPE_INPUT);
	SETUP_PIN( CN_PRES_VACUUM, PIN_TYPE_INPUT);

	SETUP_PIN( CN_STATE_LUB, PIN_TYPE_INPUT);
	SETUP_PIN( CN_STATE_VACUUM, PIN_TYPE_INPUT);
	SETUP_PIN( CN_STATE_RECYCLE, PIN_TYPE_INPUT);

	SETUP_PIN( CN_LUB_LEVEL_LOW, PIN_TYPE_INPUT);
	SETUP_PIN( CN_LUB_LEVEL_MEDIUM, PIN_TYPE_INPUT);
	SETUP_PIN( CN_LUB_LEVEL_HIGH, PIN_TYPE_INPUT);
}

void init_scanner()
{
	SETUP_PIN( LASER_0_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( L0_STEP_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( L0_DIR_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( L0_ENABLE_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( LASER_0_PRES, PIN_TYPE_INPUT);
	SETUP_PIN( LASER_0_MON, PIN_TYPE_INPUT);

	SETUP_PIN( LASER_1_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( L1_STEP_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( L1_DIR_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( L1_ENABLE_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( LASER_1_PRES, PIN_TYPE_INPUT);
	SETUP_PIN( LASER_1_MON, PIN_TYPE_INPUT);

	SETUP_PIN( TABLE0_DETECTED_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( TABLE0_STEP_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( TABLE0_DIR_PIN, PIN_TYPE_OUTPUT);
	SETUP_PIN( TABLE0_ENABLE_PIN, PIN_TYPE_OUTPUT);
}

/***********************************************************************
 * 
 *    Function Tools
 * 
 **********************************************************************/

void pin_x_steps( int PIN , int steps )
{
    for( int i=0 ; i<steps ; i++ )
    {
        WRITE_VPIN( PIN, LOW);
        delay(3);
        WRITE_VPIN( PIN, HIGH);
        delay(3);
    }    
}

/**
 * Handle IC temp. 
 * We dont really regulate this value, but we check if the temps is too high or
 * too low (due to pelletier and cooler).
 * **/
void manage_ic_temp()
{
	#if THERM_ELEC2 >-1 && THERM_ELEC1 > -1
	if ( ic_current_temp < IC_BOX_MIN_TEMP ) // too cold
	{
		//HAL::emergencyStop();
	}
	else if ( ic_current_temp > IC_BOX_MIN_TEMP ) // too hot
	{
		//HAL::emergencyStop();
	}
	#endif
}

/**
 * Handle PWM. If ENABLE_ARCH_PWM is true, firmware use AnalogWrite to output PWM
 * No software emulation with ISR.
 * This routine is called from checkAction in Command::
 * Grab pwm_pos and extruder::cooler values and set PWM output using EPS
 * **/
void manage_pwm()
{
 #if ENABLE_ARCH_PWM == true
#if defined(EXT0_HEATER_PIN) &&  EXT0_HEATER_PIN>-1 && NUM_EXTRUDER>1
        WRITE_VPIN(EXT0_HEATER_PIN, pwm_pos[0]);
#if EXT0_EXTRUDER_COOLER_PIN>-1
        WRITE_VPIN(EXT0_EXTRUDER_COOLER_PIN, extruder[0].coolerPWM);
#endif
#endif
#if defined(EXT1_HEATER_PIN) &&  EXT1_HEATER_PIN>-1
        WRITE_VPIN(EXT1_HEATER_PIN, pwm_pos[1]);
#if EXT1_EXTRUDER_COOLER_PIN>-1
        WRITE_VPIN(EXT1_EXTRUDER_COOLER_PIN, extruder[1].coolerPWM);
#endif
#endif
#if defined(EXT2_HEATER_PIN) && EXT2_HEATER_PIN>-1
        WRITE_VPIN(EXT2_HEATER_PIN, pwm_pos[2]);
#if EXT2_EXTRUDER_COOLER_PIN>-1
        WRITE_VPIN(EXT2_EXTRUDER_COOLER_PIN, extruder[2].coolerPWM);
#endif
#endif

#if defined(EXT3_HEATER_PIN) && EXT3_HEATER_PIN>-1
        WRITE_VPIN(EXT3_HEATER_PIN, pwm_pos[3]);
#if EXT3_EXTRUDER_COOLER_PIN>-1
        WRITE_VPIN(EXT3_EXTRUDER_COOLER_PIN, extruder[3].coolerPWM);
#endif
#endif

#if defined(EXT4_HEATER_PIN) &&  EXT4_HEATER_PIN>-1
        WRITE_VPIN(EXT4_HEATER_PIN, pwm_pos[4]);
#if EXT4_EXTRUDER_COOLER_PIN>-1
        WRITE_VPIN(EXT4_EXTRUDER_COOLER_PIN, extruder[4].coolerPWM);
#endif
#endif

#if defined(EXT5_HEATER_PIN) &&  EXT5_HEATER_PIN>-1
        WRITE_VPIN(EXT5_HEATER_PIN, pwm_pos[5]);
#if EXT5_EXTRUDER_COOLER_PIN>-1
        WRITE_VPIN(EXT5_EXTRUDER_COOLER_PIN, extruder[5].coolerPWM);
#endif
#endif
#if FAN_BOARD_PIN>-1
        WRITE_VPIN(FAN_BOARD_PIN, pwm_pos[POS_PWM_FAN_BOARD]);
#endif
#if FAN_PIN>-1 && FEATURE_FAN_CONTROL
        WRITE_VPIN(FAN_PIN, pwm_pos[POS_PWM_FAN]);
#endif
#if HEATER_BED_0 >-1 && HAVE_HEATED_BED
        if( pwm_pos[NUM_EXTRUDER]>0) WRITE_VPIN(HEATER_BED_0, pwm_pos[NUM_EXTRUDER]);
#endif
#if HEATER_BED_1 >-1 && HAVE_HEATED_BED
        if( pwm_pos[NUM_EXTRUDER+1]>0) WRITE_VPIN(HEATER_BED_1, pwm_pos[NUM_EXTRUDER+1]);
#endif
#if HEATER_BED_2 >-1 && HAVE_HEATED_BED
        if( pwm_pos[NUM_EXTRUDER+2]>0) WRITE_VPIN(HEATER_BED_2, pwm_pos[NUM_EXTRUDER+2]);
#endif
#if HEATER_BED_3 >-1 && HAVE_HEATED_BED
        if( pwm_pos[NUM_EXTRUDER+3]>0) WRITE_VPIN(HEATER_BED_3, pwm_pos[NUM_EXTRUDER+3]);
#endif	
	
 #endif
}

byte is_box_open()
{
	return  ( READ_VPIN(BOX_OPEN_0_PIN) || READ_VPIN(BOX_OPEN_1_PIN) );
}

byte laser_detected( uint8_t laser_id )
{
	byte detection = false;
	switch ( laser_id )
	{
		case 0:
			detection = LASER_0_PIN>-1 && READ_VPIN( LASER_0_PRES ) ;
		break;
		case 1:
			detection = LASER_1_PIN>-1 && READ_VPIN( LASER_1_PRES )  ;
		break;
		default:
		return false;
		break;
	}
	return detection;
}

byte bed_detected( uint8_t bed_id )
{
	byte detection = false;
	switch ( bed_id )
	{
		case 0:
			detection = READ_VPIN( DETECTION_BED_0 ) && (HEATER_BED_0>-1) ;
		break;
		case 1:
			detection = READ_VPIN( DETECTION_BED_1 ) && (HEATER_BED_1>-1) ;
		break;
		case 2:
			detection = READ_VPIN( DETECTION_BED_2 ) && (HEATER_BED_2>-1) ;
		break;
		case 3:
			detection = READ_VPIN( DETECTION_BED_3 ) && (HEATER_BED_3>-1) ;
		break;
		default:
		return false;
		break;
	}
	return detection;
}

byte is_ic_open()
{
	return  ( READ_VPIN(IC_OPEN_0_PIN) || READ_VPIN(IC_OPEN_1_PIN) );
}

void i2c_send_update()
{
    for (uint8_t i = 1 ; i < NUM_BOARD ; ++i )
    {
        if ( boards[i].connected )
        {
            eps_send_board_update( i );
        }
    }
}
void i2c_send_get()
{
    for (uint8_t i = 1 ; i < NUM_BOARD ; ++i )
    {
        if ( boards[i].connected )
        {
            eps_send_action( i+1, EPS_GET );
        }
    }
}

void check_i2c_periodical()
{
  if(++timer_i2c_update>= i2c_update_time )
  {
     timer_i2c_update=0;
     i2c_send_update();
  }
  if(++timer_i2c_send_get>= BOARD_SEND_GET_DELAY )
  {
     timer_i2c_send_get=0;
     i2c_send_get();
  }
}
uint8_t get_lub_level()
{
	uint8_t level = 0;
	#if CN_LUB_LEVEL_LOW >=0 
		level &= READ_VPIN( CN_LUB_LEVEL_LOW );
	#endif
	#if CN_LUB_LEVEL_MEDIUM >=0 
		level &= READ_VPIN( CN_LUB_LEVEL_MEDIUM );
	#endif
	#if CN_LUB_LEVEL_HIGH >=0 
		level &= READ_VPIN( CN_LUB_LEVEL_HIGH );
	#endif
	return level;
}

void check_all_ATU()
{
	if ( !ENABLE_ATU )
	{
		return;
	}
	if ( READ_VPIN( ATU_MAIN ) )
	{
		Commands::emergencyStop();
	}
	// command
	if ( READ_VPIN( ATU_COM_ONOFF_0 ) || READ_VPIN( ATU_COM_ONOFF_1 ) )
	{
		Commands::emergencyStop();
	}
	//monitor
	if ( READ_VPIN( ATU_MON_ONOFF_0 ) ||	READ_VPIN( ATU_MON_ONOFF_1 ) )
	{
		Commands::emergencyStop();
	}
	//monitor
	if ( READ_VPIN( ATU_MON_POWER_0 ) ||	READ_VPIN( ATU_MON_POWER_1 ) )
	{
		Commands::emergencyStop();
	}
	//labviewmodule
	if ( READ_VPIN( ATU_LVM ) )
	{
		Commands::emergencyStop();
	}
	if ( READ_VPIN( ATU_HEATERS_BED_BOX) )
	{
		Commands::emergencyStop();
	}
	if ( READ_VPIN( ATU_TOOL ) )
	{
		Commands::emergencyStop();
	}
	if ( READ_VPIN( ATU_PRE_ASI_0) || READ_VPIN( ATU_PRE_ASI_1) )
	{
		Commands::emergencyStop();
	}
	if ( is_box_open() || is_ic_open() )
	{
		Commands::emergencyStop();
	}
} 

void check_boards_connected()
{   // need to wait more ?
    if ( last_check < BOARD_CONNECTED_CHECK_DELAY )
    {
        last_check++;
        return;
    }
    // code to execute
    last_check = 0; // reset cmpt
    #if NUM_BOARD > 1
		//check if slave detected (elec.)
		#if ENABLE_HARDWARE_CHECK_SLAVE
		boards[1].connected = !READ_VPIN( DETECTION_SLAVE_1 );
		// if slave detected (elec.) we check if slave is UP (software check)
		if ( boards[1].connected )
		#endif
			boards[1].check_connected( 1+1 );
    #endif
    #if NUM_BOARD > 2
		#if ENABLE_HARDWARE_CHECK_SLAVE
		boards[2].connected = !READ_VPIN( DETECTION_SLAVE_2 );
		if ( boards[2].connected )
		#endif
			boards[2].check_connected( 2+1 );
    #endif
    #if NUM_BOARD > 3
    	#if ENABLE_HARDWARE_CHECK_SLAVE
		boards[3].connected = !READ_VPIN( DETECTION_SLAVE_3 );
		if ( boards[3].connected )
		#endif
			boards[3].check_connected( 3+1 );
    #endif
    #if NUM_BOARD > 4
    	#if ENABLE_HARDWARE_CHECK_SLAVE
		boards[4].connected = !READ_VPIN( DETECTION_SLAVE_4 );
		if ( boards[4].connected )
		#endif
			boards[4].check_connected( 4+1 );
    #endif
    #if NUM_BOARD > 5
    	#if ENABLE_HARDWARE_CHECK_SLAVE
		boards[5].connected = !READ_VPIN( DETECTION_SLAVE_5 );
		if ( boards[5].connected )
		#endif
			boards[5].check_connected( 5+1 );
    #endif
}

byte is_clogged()
{
    return isClogged;
}

void encoder_incr()
{
    encoder_currentSteps++;
    if ( encoder_currentSteps < 0 )
        encoder_currentSteps = 0;
}
byte check_clogged()
{
 /*   float deltaExtrude;
    long deltaEncoder;
    
    BEGIN_INTERRUPT_PROTECTED
    deltaExtrude = abs(printer_state.filamentPrinted - filamentPrinted_lastCheck); //compute delta between previous filament prinetd and current printed.
    filamentPrinted_lastCheck = printer_state.filamentPrinted; // update value for next check.
    deltaEncoder = abs(encoder_currentSteps - encoder_lastSteps); // delta between current encode step count and last.
    encoder_lastSteps = encoder_currentSteps;
    END_INTERRUPT_PROTECTED
    
    float deltaEncoderMM = (float)deltaEncoder / (float)ENCODER_STEPS_PER_MM;
    if ( deltaExtrude > MIN_DELTAEXTRUDE_VALUE )
    {
        float clogged_value = abs( deltaEncoderMM * 100 / deltaExtrude) ; // 100 % means no error, 90% means 10% of error (miss 10% of the E-steps)
         if ( clogged_value < DETECT_CLOGGED_PERCENT )
         {
            isClogged = 1;
            OUT_POLY();
            OUT_MCODE( POLY_MCODE_ISCLOGGED );
            OUT_P_I_LN(" ",is_clogged());
            
            return 1;
         }
    }*/
    return 0;
}

/*
 
  case UI_ACTION_PAUSE:
      OUT_P("RequestPause:");
    if ( param == POLY_MCODE_ISCLOGGED )
      {
        OUT_P_LN( "Clogged detected. You need to check your filament." );
      }
      else
      {
        OUT_P_LN( "Paused." );
      }
      break;
*/
