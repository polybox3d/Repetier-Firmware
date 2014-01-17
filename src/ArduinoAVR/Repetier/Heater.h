#ifndef __HEATER_H__
#define __HEATER_H__

#include <inttypes.h>
#include "Repetier.h"

class Heater
{
	public:
	
	float targetTemperatureC; ///< Target temperature in degC.
	uint32_t lastTemperatureUpdate; ///< Time in millis of the last temperature update.
	int8_t heatManager; ///< How is temperature controled. 0 = on/off, 1 = PID-Control, 3 = deat time control
#ifdef TEMP_PID
    float tempIState; ///< Temp. var. for PID computation.
    uint8_t pidDriveMax; ///< Used for windup in PID calculation.
    uint8_t pidDriveMin; ///< Used for windup in PID calculation.
    float pidPGain; ///< Pgain (proportional gain) for PID temperature control [0,01 Units].
    float pidIGain; ///< Igain (integral) for PID temperature control [0,01 Units].
    float pidDGain;  ///< Dgain (damping) for PID temperature control [0,01 Units].
    uint8_t pidMax; ///< Maximum PWM value, the heater should be set.
    float tempIStateLimitMax;
    float tempIStateLimitMin;
    uint8_t tempPointer;
    float tempArray[4];
#endif
	uint8_t output; /// pwm output to controle heater
	Heater(	){};
	Heater(	float targetTemperatureC,
			uint32_t lastTemperatureUpdate,
			int8_t heatManager
			#ifdef TEMP_PID
			,float tempIState,
			uint8_t pidDriveMax,
			uint8_t pidDriveMin,
			float pidPGain,
			float pidIGain,
			float pidDGain,
			uint8_t pidMax,
			float tempIStateLimitMax,
			float tempIStateLimitMin,
			uint8_t tempPointer
			#endif
		):targetTemperatureC(targetTemperatureC), 
			lastTemperatureUpdate(lastTemperatureUpdate),
			heatManager(heatManager)
			#ifdef TEMP_PID
			,tempIState(tempIState),
			pidDriveMax(pidDriveMax),
			pidDriveMin(pidDriveMin),
			pidPGain(pidPGain),
			pidIGain(pidIGain),
			pidDGain(pidDGain),
			pidMax(pidMax),
			tempIStateLimitMax(tempIStateLimitMax),
			tempIStateLimitMin(tempIStateLimitMin),
			tempPointer(tempPointer)
			#endif
			
	{
		#ifdef TEMP_PID
		this->tempArray[0] = 0;
		this->tempArray[1] = 0;
		this->tempArray[2] = 0;
		this->tempArray[3] = 0;
		#endif
		this->output = 0;
	};
	
	~Heater(){}
	
	
	uint8_t computeOutput(float currentTemperatureC )
	{
		uint8_t on = currentTemperatureC >= targetTemperatureC ? LOW : HIGH;
	#ifdef TEMP_PID
		this->tempArray[this->tempPointer++] = currentTemperatureC;
		this->tempPointer &= 3;
		if(this->heatManager == 1)
		{
			float error = targetTemperatureC - currentTemperatureC;
			if(targetTemperatureC<20.0f) output = 0; // off is off, even if damping term wants a heat peak!
			else if(error>PID_CONTROL_RANGE)
				output = this->pidMax;
			else if(error<-PID_CONTROL_RANGE)
				output = 0;
			else
			{
				float pidTerm = this->pidPGain * error;
				this->tempIState = constrain(this->tempIState+error,this->tempIStateLimitMin,this->tempIStateLimitMax);
				pidTerm += this->pidIGain * this->tempIState*0.1;
				long dgain = this->pidDGain * (this->tempArray[this->tempPointer]-currentTemperatureC)*3.333f;
				pidTerm += dgain;
	#if SCALE_PID_TO_MAX==1
				pidTerm = (pidTerm*this->pidMax)*0.0039062;
	#endif
				output = constrain((int)pidTerm, 0, this->pidMax);
			}
		}
		else if(this->heatManager == 3)     // deat-time control
		{
			float error = targetTemperatureC - currentTemperatureC;
			if(targetTemperatureC<20.0f)
				output = 0; // off is off, even if damping term wants a heat peak!
			else if(error>PID_CONTROL_RANGE)
				output = this->pidMax;
			else if(error < -PID_CONTROL_RANGE)
				output = 0;
			else
			{
				float raising = 3.333 * (currentTemperatureC - this->tempArray[this->tempPointer]); // raising dT/dt, 3.33 = reciproke of time interval (300 ms)
				this->tempIState = 0.25 * (3.0 * this->tempIState + raising); // damp raising
				output = (currentTemperatureC + this->tempIState * this->pidPGain > targetTemperatureC ? 0 : output = this->pidDriveMax);
			}
		}
		else
	#endif
			if(this->heatManager == 2)    // Bang-bang with reduced change frequency to save relais life
			{
				unsigned long time = HAL::timeInMilliseconds();
				if (time - this->lastTemperatureUpdate > HEATED_BED_SET_INTERVAL)
				{
					output = (on ? 255 : 0);
					this->lastTemperatureUpdate = time;
				}
			}
			else     // Fast Bang-Bang fallback
			{
				output = (on ? 255 : 0);
			}
		return output;
	}

	
};

#endif // __HEATER_H__
