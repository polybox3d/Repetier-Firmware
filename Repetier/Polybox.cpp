#include "Polybox.h"

#include "Reptier.h"

volatile float filamentPrinted_lastCheck = 0.0;
volatile long encoder_currentSteps = 0 ;
volatile long encoder_lastSteps = 0;
volatile byte isClogged = 0;

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

byte is_clogged()
{
    return isClogged;
}

byte check_clogged()
{
    float deltaExtrude = abs(printer_state.filamentPrinted - filamentPrinted_lastCheck); //compute delta between previous filament prinetd and current printed.
    filamentPrinted_lastCheck = printer_state.filamentPrinted; // update value for next check.
    long deltaEncoder = abs(encoder_currentSteps - encoder_lastSteps); // delta between current encore step count and last.
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
    }
    return 0;
}

void executeAction(int action, int param) {
  if(action>=2000 && action<3000)
  {
      
  }
  else
  switch(action) {
    case UI_ACTION_EMERGENCY_STOP:
      emergencyStop();
      break;
    case UI_ACTION_HOME_ALL:
      home_axis(true,true,true);
      printPosition();
      break;
    case UI_ACTION_HOME_X:
      home_axis(true,false,false);
      printPosition();
      break;
    case UI_ACTION_HOME_Y:
      home_axis(false,true,false);
      printPosition();
      break;
    case UI_ACTION_HOME_Z:
      home_axis(false,false,true);
      printPosition();
      break;
    case UI_ACTION_SET_ORIGIN:
      printer_state.currentPositionSteps[0] = -printer_state.offsetX;
      printer_state.currentPositionSteps[1] = -printer_state.offsetY;
      printer_state.currentPositionSteps[2] = 0;
      break;
    case UI_ACTION_DEBUG_ECHO:
      if(DEBUG_ECHO) debug_level-=1;else debug_level+=1;
      break;
    case UI_ACTION_DEBUG_INFO:
      if(DEBUG_INFO) debug_level-=2;else debug_level+=2;
      break;
    case UI_ACTION_DEBUG_ERROR:
      if(DEBUG_ERRORS) debug_level-=4;else debug_level+=4;
      break;
    case UI_ACTION_DEBUG_DRYRUN:
      if(DEBUG_DRYRUN) debug_level-=8;else debug_level+=8;
      if(DEBUG_DRYRUN) { // simulate movements without printing
          extruder_set_temperature(0,0);
#if NUM_EXTRUDER>1
          extruder_set_temperature(0,1);
#endif
#if HAVE_HEATED_BED==true
          heated_bed_set_temperature(0);
#endif
      }
      break;
    case UI_ACTION_POWER:
      break;
    case UI_ACTION_PREHEAT_PLA:
      extruder_set_temperature(UI_SET_PRESET_EXTRUDER_TEMP_PLA,0);
#if NUM_EXTRUDER>1
      extruder_set_temperature(UI_SET_PRESET_EXTRUDER_TEMP_PLA,1);
#endif
#if HAVE_HEATED_BED==true
      heated_bed_set_temperature(UI_SET_PRESET_HEATED_BED_TEMP_PLA);
#endif 
      break;
    case UI_ACTION_PREHEAT_ABS:
      extruder_set_temperature(UI_SET_PRESET_EXTRUDER_TEMP_ABS,0);
#if NUM_EXTRUDER>1
      extruder_set_temperature(UI_SET_PRESET_EXTRUDER_TEMP_ABS,1);
#endif
#if HAVE_HEATED_BED==true
      heated_bed_set_temperature(UI_SET_PRESET_HEATED_BED_TEMP_ABS);
#endif 
      break;
    case UI_ACTION_COOLDOWN:
      extruder_set_temperature(0,0);
#if NUM_EXTRUDER>1
      extruder_set_temperature(0,1);
#endif
#if HAVE_HEATED_BED==true
      heated_bed_set_temperature(0);
#endif 
      break;
    case UI_ACTION_HEATED_BED_OFF:
#if HAVE_HEATED_BED==true
      heated_bed_set_temperature(0);
#endif 
      break;
    case UI_ACTION_EXTRUDER0_OFF:
      extruder_set_temperature(0,0);
      break;
    case UI_ACTION_EXTRUDER1_OFF:
 #if NUM_EXTRUDER>1
      extruder_set_temperature(0,1);
 #endif
      break;
#if USE_OPS==1
    case UI_ACTION_OPS_OFF:
      printer_state.opsMode=0;
      break;
    case UI_ACTION_OPS_CLASSIC:
      printer_state.opsMode=1;
      break;
    case UI_ACTION_OPS_FAST:
      printer_state.opsMode=2;
      break;
 #endif
    case UI_ACTION_DISABLE_STEPPER:
      kill(true);
      break;
    case UI_ACTION_RESET_EXTRUDER:
      printer_state.currentPositionSteps[3] = 0;
      break;
    case UI_ACTION_EXTRUDER_RELATIVE:
      relative_mode_e=!relative_mode_e;
      break;
    case UI_ACTION_SELECT_EXTRUDER0:
      extruder_select(0);
      break;
    case UI_ACTION_SELECT_EXTRUDER1:
#if NUM_EXTRUDER>1
      extruder_select(1);
#endif
      break;
#if FAN_PIN>-1
    case UI_ACTION_FAN_OFF:
      set_fan_speed(0,false);
      OUT_P_LN("Fanspeed:0");
      break;
    case UI_ACTION_FAN_25:
      set_fan_speed(64,false);
      OUT_P_LN("Fanspeed:64");
      break;
    case UI_ACTION_FAN_50:
      set_fan_speed(128,false);
      OUT_P_LN("Fanspeed:128");
      break;
    case UI_ACTION_FAN_75:
      set_fan_speed(192,false);
      OUT_P_LN("Fanspeed:192");
      break;
    case UI_ACTION_FAN_FULL:
      set_fan_speed(255,false);
      OUT_P_LN("Fanspeed:255");
      break;
#endif
    case UI_ACTION_X_UP:
      move_steps(axis_steps_per_unit[0],0,0,0,homing_feedrate[0],false,true);
      break;
    case UI_ACTION_X_DOWN:
      move_steps(-axis_steps_per_unit[0],0,0,0,homing_feedrate[0],false,true);
      break;
    case UI_ACTION_Y_UP:
      move_steps(0,axis_steps_per_unit[1],0,0,homing_feedrate[1],false,true);
      break;
    case UI_ACTION_Y_DOWN:
      move_steps(0,-axis_steps_per_unit[1],0,0,homing_feedrate[1],false,true);
      break;
    case UI_ACTION_Z_UP:
      move_steps(0,0,axis_steps_per_unit[2],0,homing_feedrate[2],false,true);
      break;
    case UI_ACTION_Z_DOWN:
      move_steps(0,0,-axis_steps_per_unit[2],0,homing_feedrate[2],false,true);
      break;
    case UI_ACTION_EXTRUDER_UP:
      move_steps(0,0,0,axis_steps_per_unit[3],UI_SET_EXTRUDER_FEEDRATE,false,true);
      break;
    case UI_ACTION_EXTRUDER_DOWN:
      move_steps(0,0,0,-axis_steps_per_unit[3],UI_SET_EXTRUDER_FEEDRATE,false,true);
      break;
    case UI_ACTION_EXTRUDER_TEMP_UP: {
         int tmp = (int)(current_extruder->tempControl.targetTemperatureC)+1;
         if(tmp==1) tmp = UI_SET_MIN_EXTRUDER_TEMP;
         else if(tmp>UI_SET_MAX_EXTRUDER_TEMP) tmp = UI_SET_MAX_EXTRUDER_TEMP;
         extruder_set_temperature(tmp,current_extruder->id);
      }
      break;
    case UI_ACTION_EXTRUDER_TEMP_DOWN: {
         int tmp = (int)(current_extruder->tempControl.targetTemperatureC)-1;
         if(tmp<UI_SET_MIN_EXTRUDER_TEMP) tmp = 0;
         extruder_set_temperature(tmp,current_extruder->id);
      }
      break;
    case UI_ACTION_HEATED_BED_UP:
#if HAVE_HEATED_BED==true
    {
       int tmp = (int)heatedBedController.targetTemperatureC+1;
       if(tmp==1) tmp = UI_SET_MIN_HEATED_BED_TEMP;
       else if(tmp>UI_SET_MAX_HEATED_BED_TEMP) tmp = UI_SET_MAX_HEATED_BED_TEMP;
       heated_bed_set_temperature(tmp);
    }
#endif
      break;
	case UI_ACTION_SHOW_MEASUREMENT:
#ifdef STEP_COUNTER
	{
		out.print_float_P(PSTR("Measure/delta ="),printer_state.countZSteps * inv_axis_steps_per_unit[2]);
	}
#endif
      break;
	case UI_ACTION_RESET_MEASUREMENT:
#ifdef STEP_COUNTER
	{
		printer_state.countZSteps = 0;
		out.println_P(PSTR("Measurement reset."));
	}
#endif
      break;
	case UI_ACTION_SET_MEASURED_ORIGIN:
#ifdef STEP_COUNTER
	{
		if (printer_state.countZSteps < 0)
			printer_state.countZSteps = -printer_state.countZSteps;
		printer_state.zLength = inv_axis_steps_per_unit[2] * printer_state.countZSteps;
		printer_state.zMaxSteps = printer_state.countZSteps;
		for (byte i=0; i<3; i++) {
			printer_state.currentPositionSteps[i] = 0;
		}
		calculate_delta(printer_state.currentPositionSteps, printer_state.currentDeltaPositionSteps);
		out.println_P(PSTR("Measured origin set. Measurement reset."));
	}
#endif
	case UI_ACTION_SET_P1:
#ifdef SOFTWARE_LEVELING
		for (byte i=0; i<3; i++) {
			printer_state.levelingP1[i] = printer_state.currentPositionSteps[i];
		}
#endif
      break;
	case UI_ACTION_SET_P2:
#ifdef SOFTWARE_LEVELING
		for (byte i=0; i<3; i++) {
			printer_state.levelingP2[i] = printer_state.currentPositionSteps[i];
		}
#endif
      break;
	case UI_ACTION_SET_P3:
#ifdef SOFTWARE_LEVELING
		for (byte i=0; i<3; i++) {
			printer_state.levelingP3[i] = printer_state.currentPositionSteps[i];
		}
#endif
      break;
	case UI_ACTION_CALC_LEVEL:
#ifdef SOFTWARE_LEVELING
		long factors[4];
		calculate_plane(factors, printer_state.levelingP1, printer_state.levelingP2, printer_state.levelingP3);
		out.println_P(PSTR("Leveling calc:"));
		out.println_float_P(PSTR("Tower 1:"), calc_zoffset(factors, DELTA_TOWER1_X_STEPS, DELTA_TOWER1_Y_STEPS) * inv_axis_steps_per_unit[0]);
		out.println_float_P(PSTR("Tower 2:"), calc_zoffset(factors, DELTA_TOWER2_X_STEPS, DELTA_TOWER2_Y_STEPS) * inv_axis_steps_per_unit[1]);
		out.println_float_P(PSTR("Tower 3:"), calc_zoffset(factors, DELTA_TOWER3_X_STEPS, DELTA_TOWER3_Y_STEPS) * inv_axis_steps_per_unit[2]);
#endif
      break;
    case UI_ACTION_HEATED_BED_DOWN:
#if HAVE_HEATED_BED==true
    {
       int tmp = (int)heatedBedController.targetTemperatureC-1;
       if(tmp<UI_SET_MIN_HEATED_BED_TEMP) tmp = 0;
       heated_bed_set_temperature(tmp);
    }
#endif
      break;
    case UI_ACTION_FAN_UP:
      set_fan_speed(get_fan_speed()+32,false);
      OUT_P_I_LN("Fanspeed:",get_fan_speed());
      break;
    case UI_ACTION_FAN_DOWN:
      set_fan_speed(get_fan_speed()-32,false);
      OUT_P_I_LN("Fanspeed:",get_fan_speed());
      break;
    case UI_ACTION_KILL:
      cli(); // Don't allow interrupts to do their work
      kill(false);
      manage_temperatures();
      pwm_pos[0] = pwm_pos[1] = pwm_pos[2] = pwm_pos[3]=0;
#if EXT0_HEATER_PIN>-1
     WRITE(EXT0_HEATER_PIN,0);
#endif
#if defined(EXT1_HEATER_PIN) && EXT1_HEATER_PIN>-1 && NUM_EXTRUDER>1
     WRITE(EXT1_HEATER_PIN,0);
#endif
#if defined(EXT2_HEATER_PIN) && EXT2_HEATER_PIN>-1 && NUM_EXTRUDER>2
     WRITE(EXT2_HEATER_PIN,0);
#endif
#if FAN_PIN>-1
     WRITE(FAN_PIN,0);
#endif
      while(1) {}

      break;
    case UI_ACTION_RESET:
      resetFunc();
      break;
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
      default:
      break;
  }
}

