#ifndef __CHAMBERTEMP_H__
#define __CHAMBERTEMP_H__

#include <inttypes.h>
#include "Repetier.h"

#define CHAMBER_FLAG_ALL_STOP		1
#define CHAMBER_FLAG_HEATERS_STOP	2


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
		setAllFanPWM( 0 );
	}
	
	float getCurrentTemp() const
	{
		return _currentTemperatureC;
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
			_heaters[i].output = 0;
		}
	}
	
	/********      Heater          ******/
	void disableHeaters()
	{
		_targetTemperatureC = 0;
		for (uint8_t i = 0 ; i < NUM_HEATER_CHAMBER ; i++ )
		{
			_heaters[i].output = 0;
		}
	}
	/********      FAN          ******/
	void setAllFanPWM( uint8_t pwm)
	{
		for (uint8_t i = 0 ; i < NUM_FAN_CHAMBER ; i++ )
		{
			_fans[i].pwm = pwm;
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
		
	}
	void disableAllFan()
	{
		setAllFanPWM(0);
	}
	
	void disableAll()
	{
		disableHeaters();
		disableAllFan();
		_flags = CHAMBER_FLAG_ALL_STOP;
	}
	void manageFanPWM()
	{
		for (uint8_t i = 0 ; i < NUM_HEATER_CHAMBER ; i++ )
		{
			WRITE_VPIN( _fans[i].pin, _fans[i].pwm );
		}
	}
	void manageTemeprature(){}
	
	
	void initHeater(){}
	
	
};






#endif //__CHAMBERTEMP_H__
