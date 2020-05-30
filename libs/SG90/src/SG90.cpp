#include <pigpio.h>
#ifndef __cplusplus
extern "C++" {
#endif //#ifdef __cplusplus
#include "SG90.h"
#include <cmath>
const double minAngle = -90.0;
const double maxAngle = 90.0;
const double angleRange = 180.0; // Degrees the servo is able to move
const unsigned int operatingFreq = 50;
const double realMaxDuty = PI_HW_PWM_RANGE;
const double signalPeriodMs = 1000.0 / operatingFreq;
const double angleTolerance = 0.5;
// Constructor
sg90ctl::sg90ctl(int iGPIOidx, double iMaxDutyCycleFactor, double iMinDutyCycleFactor)
{
	_GPIOidx = iGPIOidx;
	_MaxDutyCycleFactor = iMaxDutyCycleFactor;
	_MinDutyCycleFactor = iMinDutyCycleFactor;
}
// Destructor
sg90ctl::~sg90ctl()
{
	
}

void sg90ctl::CleanUp()
{
	gpioHardwarePWM(getGPIOIdx(), 0, 0);
}

int sg90ctl::initialise()
{
	return gpioHardwarePWM(getGPIOIdx(), operatingFreq, toDutyCycle(0));
}

int sg90ctl::setTargetLocation(double iAngle)
{
	int rc = 1;
	double currentLocation = getCurrentLocation();
	double deltaangle = std::abs(iAngle - currentLocation);
	double delaytime = deltaangle / 60 * 0.1 * 2;
	unsigned int dutyCycle = toDutyCycle(iAngle);
	while ((currentLocation > (iAngle + angleTolerance)) || (currentLocation < (iAngle - angleTolerance)))
	{
		rc = gpioHardwarePWM(getGPIOIdx(), operatingFreq, dutyCycle);
		//rc = gpioPWM(getGPIOIdx(), dutyCycle);
		if (rc) break;

		gpioSleep(PI_TIME_RELATIVE, delaytime, 0); // sleep for 0.1 seconds
		currentLocation = getCurrentLocation();
	}
	return rc;
}
int sg90ctl::moveToLocation(double iAngle)
{
	if ((iAngle < minAngle) || (iAngle > maxAngle)) return 1;
	return setTargetLocation(iAngle);
}

double sg90ctl::getCurrentLocation()
{
	if (!getGPIOIdx()) return 0;
	int curWidth = gpioGetPWMdutycycle(getGPIOIdx());
		
	if (curWidth == PI_BAD_USER_GPIO || curWidth == PI_NOT_SERVO_GPIO) throw "bad configuration";
	return toAngle(curWidth);
}

int sg90ctl::move(bool iMovePlus) //Increment one degree
{
	double deltaAngle = (iMovePlus) ? 1.0 : -1.0;
	deltaAngle += getCurrentLocation();
	if ((deltaAngle < minAngle) || (deltaAngle > maxAngle)) return 1;
	return setTargetLocation(deltaAngle);
}

double sg90ctl::toAngle(unsigned int iValue) const
{
	return (iValue - realMaxDuty * _MinDutyCycleFactor) * angleRange / ((_MaxDutyCycleFactor - _MinDutyCycleFactor) * realMaxDuty) + minAngle;
}

unsigned int sg90ctl::toDutyCycle(double iAngle) const
{
	return realMaxDuty * _MinDutyCycleFactor + (iAngle - minAngle) * ((_MaxDutyCycleFactor -_MinDutyCycleFactor) * realMaxDuty) / angleRange;
}



#ifndef __cplusplus
}
#endif //ifndef __cplusplus