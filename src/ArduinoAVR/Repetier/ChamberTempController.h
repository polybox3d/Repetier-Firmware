#ifndef __CHAMBERTEMP_H__
#define __CHAMBERTEMP_H__

#include <inttypes.h>
#include "Repetier.h"

typedef uint8_t Fan;

class ChamberTempController
{
	public:
	
	Sensor sensors[NUM_SENSOR_BOX];
	Heater heaters[NUM_HEATER_CHAMBER];
	Fan fans[NUM_FAN_CHAMBER];
	float _targetTemperatureC; ///< Target temperature for the chamber, in °C
	float _currentTemperatureC; ///< Current temperature for the chamber, in °C
	float _currentICTemperatureC; ///< Current temperature for the IC, in °C
	uint8_t _flags; ///< Flag/state 
	
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
			heaters[i].output = 0;
		}
	}
	
	/********      Heater          ******/
	void disableHeaters()
	{
		_targetTemperatureC = 0;
		for (uint8_t i = 0 ; i < NUM_HEATER_CHAMBER ; i++ )
		{
			heaters[i].output = 0;
		}
	}
	/********      FAN          ******/
	void setFanPWM( uint8_t pwm)
	{
		for (uint8_t i = 0 ; i < NUM_FAN_CHAMBER ; i++ )
		{
			fans[i] = pwm;
		}
	}
	void setFanPercent( uint8_t percent)
	{
		setFanPWM(percent*255/100);
	}
	void disableFan()
	{
		setFanPWM(0);
	}
	
	void disableAll()
	{
		disableHeaters();
		disableFan();
	}
	void manageFanPWM()
	{
		#if NUM_FAN_CHAMBER >0
			WRITE_VPIN(EXT0_HEATER_PIN, pwm_pos[0]);
		#endif
	}
	void manageTemeprature(){}
	
	
	void initHeater(){}
	
	
};






#endif //__CHAMBERTEMP_H__
