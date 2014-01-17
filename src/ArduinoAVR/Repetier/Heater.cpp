/*#include "Heater.h"

#include "Repetier.h"
#include "pins_arduino.h"
#include "ui.h"
#if EEPROM_MODE!=0
#include "Eeprom.h"
#endif

//#include "Repetier.h"

/*uint8_t Heater::computePID(float currentTemperatureC,float targetTemperatureC)
{/*
#ifdef TEMP_PID
	this->tempArray[this->tempPointer++] = this->currentTemperatureC;
	this->tempPointer &= 3;
	if(this->heatManager == 1)
	{
		float error = this->targetTemperatureC - this->currentTemperatureC;
		if(this->targetTemperatureC<20.0f) output = 0; // off is off, even if damping term wants a heat peak!
		else if(error>PID_CONTROL_RANGE)
			output = this->pidMax;
		else if(error<-PID_CONTROL_RANGE)
			output = 0;
		else
		{
			float pidTerm = this->pidPGain * error;
			this->tempIState = constrain(this->tempIState+error,this->tempIStateLimitMin,this->tempIStateLimitMax);
			pidTerm += this->pidIGain * this->tempIState*0.1;
			long dgain = this->pidDGain * (this->tempArray[this->tempPointer]-this->currentTemperatureC)*3.333f;
			pidTerm += dgain;
#if SCALE_PID_TO_MAX==1
			pidTerm = (pidTerm*this->pidMax)*0.0039062;
#endif
			output = constrain((int)pidTerm, 0, this->pidMax);
		}
	}
	else if(this->heatManager == 3)     // deat-time control
	{
		float error = this->targetTemperatureC - this->currentTemperatureC;
		if(this->targetTemperatureC<20.0f)
			output = 0; // off is off, even if damping term wants a heat peak!
		else if(error>PID_CONTROL_RANGE)
			output = this->pidMax;
		else if(error < -PID_CONTROL_RANGE)
			output = 0;
		else
		{
			float raising = 3.333 * (this->currentTemperatureC - this->tempArray[this->tempPointer]); // raising dT/dt, 3.33 = reciproke of time interval (300 ms)
			this->tempIState = 0.25 * (3.0 * this->tempIState + raising); // damp raising
			output = (this->currentTemperatureC + this->tempIState * this->pidPGain > this->targetTemperatureC ? 0 : output = this->pidDriveMax);
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
}*/
