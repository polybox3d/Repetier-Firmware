#ifndef __CHAMBERTEMP_H__
#define __CHAMBERTEMP_H__

#include <inttypes.h>
#include "Repetier.h"

#define CHAMBER_FLAG_ALL_STOP		1
#define CHAMBER_FLAG_HEATERS_STOP	2

#define SETUP_PIN(p,t)  if (p>-1)  VPIN_MODE( p, t)

class PWM
{
	public:
	uint8_t pwm;
	uint8_t pin;
	PWM(){ pwm = 0; pin = -1;}
};

typedef PWM Fan;

class ChamberTempController
{
	public:
	
	Sensor _sensors[NUM_SENSOR_BOX];
	Heater _heaters[NUM_HEATER_CHAMBER];
	Fan _fans[NUM_FAN_CHAMBER];

	float _targetTemperatureC; ///< Target temperature for the chamber, in °C
	float _currentTemperatureC; ///< Current temperature for the chamber, in °C
	float _currentICTemperatureC; ///< Current temperature for the IC, in °C
	uint8_t _flags; ///< Flag/state 
	
	ChamberTempController()
	{
		_flags = 0;
		_currentICTemperatureC = 0;
		_currentTemperatureC = 0;
		setTargetTemperature( 0 );
		
	}
	/********      FAN          ******/
	void setFanPWMById( uint8_t id, uint8_t pwm)
	{
		_fans[id].pwm = pwm;
		WRITE_VPIN( _fans[id].pin, _fans[id].pwm );
	}
	void setAllFanPWM( uint8_t pwm)
	{
		for (uint8_t i = 0 ; i < NUM_FAN_CHAMBER ; i++ )
		{
			setFanPWMById( i, pwm );
		}
	}
	void setAllFanPercent( uint8_t percent)
	{
		if ( percent > 100 )
			percent = 100;
		setAllFanPWM(percent*255/100);
	}
	void setFanByMask( uint8_t mask, uint8_t pwm )
	{
		for (uint8_t i = 0; i < NUM_FAN_CHAMBER ; ++i )
		{
			if ( mask & (1<< i) ) // maskerading
			{
				setFanPWMById( i , pwm );
			}
		}
	}
	void disableAllFan()
	{
		setAllFanPWM(0);
	}
	
	/*void manageFanPWM()
	{
		for (uint8_t i = 0 ; i < NUM_HEATER_CHAMBER ; i++ )
		{
			WRITE_VPIN( _fans[i].pin, _fans[i].pwm );
		}
	}*/
	void initFan()
	{
		#if FAN_CHAMBER_PEL_0 > -1 
			_fans[0].pin = FAN_CHAMBER_PEL_0;
			SETUP_PIN( _fans[0].pin , PIN_TYPE_OUTPUT | PIN_TYPE_ANALOG );
		#endif
		#if FAN_CHAMBER_PEL_1 > -1 
			_fans[1].pin = FAN_CHAMBER_PEL_1;
			SETUP_PIN( _fans[1].pin , PIN_TYPE_OUTPUT | PIN_TYPE_ANALOG );
		#endif
		#if FAN_CHAMBER_PEL_2 > -1 
			_fans[2].pin = FAN_CHAMBER_PEL_2;
			SETUP_PIN( _fans[2].pin , PIN_TYPE_OUTPUT | PIN_TYPE_ANALOG );
		#endif
		#if FAN_CHAMBER_PEL_3 > -1 
			_fans[3].pin = FAN_CHAMBER_PEL_3;
			SETUP_PIN( _fans[3].pin , PIN_TYPE_OUTPUT | PIN_TYPE_ANALOG );
		#endif
		#if FAN_CHAMBER_EXT_0 > -1 
			_fans[4].pin = FAN_CHAMBER_EXT_0;
			SETUP_PIN( _fans[4].pin , PIN_TYPE_OUTPUT | PIN_TYPE_ANALOG );
		#endif
		#if FAN_CHAMBER_PULS_0 > -1 
			_fans[5].pin = FAN_CHAMBER_PULS_0;
			SETUP_PIN( _fans[5].pin , PIN_TYPE_OUTPUT | PIN_TYPE_ANALOG );
		#endif
		
		setAllFanPWM( 0 );
	}	
	float getCurrentTemp() const
	{
		return _currentTemperatureC;
	}
	float getCurrentTempById( uint8_t sensor_id )
	{
		if ( sensor_id >= NUM_SENSOR_BOX_INSIDE )
		{
			return 0;
		}
		return _sensors[sensor_id].currentTemperatureC;
	}
	float getCurrentICTemp() const
	{
		return _currentICTemperatureC;
	}
	
	void setTargetTemperature(float target)
	{
		_targetTemperatureC = target;
		/** Basic temp for now. But we want something smooth **/
		for (uint8_t i = 0 ; i < NUM_HEATER_CHAMBER ; i++ )
		{
			_heaters[i].output = target;
		}
	}
	
	/********      Heater          ******/
	bool isHeaterDisabled()
	{
		return _flags & CHAMBER_FLAG_HEATERS_STOP;
	}
	void enableHeaters()
	{
		WRITE_VPIN( INTER_HEATER_BOX, 0 );
		_flags &= ~CHAMBER_FLAG_HEATERS_STOP;
	}
	void disableHeaters()
	{
		_targetTemperatureC = 0;
		for (uint8_t i = 0 ; i < NUM_HEATER_CHAMBER ; i++ )
		{
			_heaters[i].output = 0;
			_heaters[i].targetTemperatureC = 0;
			WRITE_VPIN( _heaters[i].pin, 0 );
		}
		_flags |= CHAMBER_FLAG_HEATERS_STOP;
		WRITE_VPIN( INTER_HEATER_BOX, 1 );
	}
	void updateTemperature()
	{
		float current_temp_sum = 0;
		for (uint8_t i = 0 ; i < NUM_SENSOR_BOX_INSIDE ; i++ )
		{
			_sensors[i].updateCurrentTemperature();
			current_temp_sum+= _sensors[i].currentTemperatureC;
		}
		_currentTemperatureC = current_temp_sum;
		
		current_temp_sum = 0;
		for (uint8_t i = NUM_SENSOR_BOX_INSIDE ; i < NUM_SENSOR_BOX_IC+NUM_SENSOR_BOX_INSIDE ; i++ )
		{
			_sensors[NUM_SENSOR_BOX_INSIDE].updateCurrentTemperature();
			current_temp_sum+= _sensors[NUM_SENSOR_BOX_INSIDE].currentTemperatureC;
		}
		_currentICTemperatureC = current_temp_sum;
	}
	void manageTemperatures()
	{
		/** SENSORS **/
		updateTemperature();	
		
		/** HEATERS **/
		
		if ( isHeaterDisabled() )
		{
			return;
		}
		manageICTemp();
		uint8_t pin_output_value = 0;
		
		for (uint8_t i = 0 ; i < NUM_HEATER_CHAMBER ; i++ )
		{
			pin_output_value = _heaters[i].computeOutput( _currentTemperatureC );
			// for all heaters pin
			WRITE_VPIN( _heaters[i].pin, pin_output_value );
		}
		
		
	}
/**
 * Handle IC temp. 
 * We dont really regulate this value, but we check if the temps is too high or
 * too low (due to pelletier and cooler).
 * **/
	void manageICTemp()
	{
		#if NUM_SENSOR_BOX_IC > 0
		if ( getCurrentICTemp() < IC_BOX_MIN_TEMP ) // too cold
		{
			//HAL::emergencyStop();
		}
		else if ( getCurrentICTemp() > IC_BOX_MIN_TEMP ) // too hot
		{
			//HAL::emergencyStop();
		}
		#endif
	}
	
	
	void initHeaters()
	{
		#if NUM_HEATER_CHAMBER > 0
			_heaters[0] = Heater( 0,0,HEATED_BED_HEAT_MANAGER
			#ifdef TEMP_PID
				,0,CHAMBER_PID_INTEGRAL_DRIVE_MAX,CHAMBER_PID_INTEGRAL_DRIVE_MIN,CHAMBER_PID_PGAIN,CHAMBER_PID_IGAIN,CHAMBER_PID_DGAIN,CHAMBER_PID_MAX,0,0,0
			#endif 
			);
			_heaters[0].pin = PEL_BOX_0;
		#endif
		#if NUM_HEATER_CHAMBER > 1
			_heaters[1] = Heater( 0,0,HEATED_BED_HEAT_MANAGER
			#ifdef TEMP_PID
				,0,CHAMBER_PID_INTEGRAL_DRIVE_MAX,CHAMBER_PID_INTEGRAL_DRIVE_MIN,CHAMBER_PID_PGAIN,CHAMBER_PID_IGAIN,CHAMBER_PID_DGAIN,CHAMBER_PID_MAX,0,0,0
			#endif 
			);
			_heaters[1].pin = PEL_BOX_1;
		#endif
		#if NUM_HEATER_CHAMBER > 2
			_heaters[2] = Heater( 0,0,HEATED_BED_HEAT_MANAGER
			#ifdef TEMP_PID
				,0,CHAMBER_PID_INTEGRAL_DRIVE_MAX,CHAMBER_PID_INTEGRAL_DRIVE_MIN,CHAMBER_PID_PGAIN,CHAMBER_PID_IGAIN,CHAMBER_PID_DGAIN,CHAMBER_PID_MAX,0,0,0
			#endif 
			);
			_heaters[2].pin = PEL_BOX_2;
		#endif
		#if NUM_HEATER_CHAMBER > 3
			_heaters[3] = Heater( 0,0,HEATED_BED_HEAT_MANAGER
			#ifdef TEMP_PID
				,0,CHAMBER_PID_INTEGRAL_DRIVE_MAX,CHAMBER_PID_INTEGRAL_DRIVE_MIN,CHAMBER_PID_PGAIN,CHAMBER_PID_IGAIN,CHAMBER_PID_DGAIN,CHAMBER_PID_MAX,0,0,0
			#endif 
			);
			_heaters[3].pin = PEL_BOX_3;
		#endif
		#if NUM_HEATER_CHAMBER > 4
			_heaters[4] = Heater( 0,0,HEATED_BED_HEAT_MANAGER
			#ifdef TEMP_PID
				,0,CHAMBER_PID_INTEGRAL_DRIVE_MAX,CHAMBER_PID_INTEGRAL_DRIVE_MIN,CHAMBER_PID_PGAIN,CHAMBER_PID_IGAIN,CHAMBER_PID_DGAIN,CHAMBER_PID_MAX,0,0,0
			#endif 
			);
			_heaters[4].pin = PEL_BOX_4;
		#endif
	}
	void initSensors()
	{
		#if NUM_SENSOR_BOX_INSIDE > 0
			_sensors[0] = Sensor(HOT_CHAMBER_SENSOR_TYPE,CHAMBER_0_SENSOR_INDEX,0,0,0);
		#endif
		#if NUM_SENSOR_BOX_INSIDE > 1
			_sensors[1] = Sensor(HOT_CHAMBER_SENSOR_TYPE,CHAMBER_1_SENSOR_INDEX,0,0,0);
		#endif
		#if NUM_SENSOR_BOX_INSIDE > 2
			_sensors[2] = Sensor(HOT_CHAMBER_SENSOR_TYPE,CHAMBER_2_SENSOR_INDEX,0,0,0);
		#endif
		#if NUM_SENSOR_BOX_INSIDE > 3
			_sensors[3] = Sensor(HOT_CHAMBER_SENSOR_TYPE,CHAMBER_3_SENSOR_INDEX,0,0,0);
		#endif
		#if NUM_SENSOR_BOX_INSIDE > 4
			_sensors[4] = Sensor(HOT_CHAMBER_SENSOR_TYPE,CHAMBER_4_SENSOR_INDEX,0,0,0);
		#endif
	}
	
	void initAll()
	{
		initFan();
		initHeaters();
		initSensors();
	}
	void disableAll()
	{
		disableHeaters();
		disableAllFan();
		_flags |= CHAMBER_FLAG_ALL_STOP;
	}
	
};






#endif //__CHAMBERTEMP_H__
