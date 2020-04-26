#include "SG90.h"
#include <pigpio.h>
#ifndef __cplusplus
extern "C++" {
#endif //#ifdef __cplusplus

const double minAngle = -90.0;
const double maxAngle = 90.0;
const double angleRange = (maxAngle - minAngle); // Degrees the servo is able to move
const double operatingFreq = 50.0;
const double signalPeriod = 1.0 / operatingFreq;
const double minPulse = 1000.0;
const double maxPulse = 2000.0;
const double pulseRange = (maxPulse - minPulse);
const double PWMtolerance = 1 * (pulseRange / angleRange); // one degree tolerance

// Constructor
sg90ctl::sg90ctl(int iGPIOidx/*, sg90ctlCB_t callback*/)
{
	_GPIOidx = iGPIOidx;
}
// Destructor
sg90ctl::~sg90ctl()
{
    //Nothing to do for now
}

int sg90ctl::initialise()
{
	if(isHardwarePWM())
		return gpioHardwarePWM(_GPIOidx, 0, 0);
	else
		return gpioServo(_GPIOidx, 0);
}

int sg90ctl::getGPIOIdx()
{
    return _GPIOidx;
}

int sg90ctl::setTargetLocation(double iAngle)
{
    if((iAngle < minAngle) || (iAngle > maxAngle)) return 0;
	if (isHardwarePWM())
	{
		double dutyCycle = toDutyCycle(iAngle);
		return gpioHardwarePWM(_GPIOidx, operatingFreq, dutyCycle);
	}
	double pwmAngle = toPWM(iAngle);
	return gpioServo(_GPIOidx, pwmAngle);
}
int sg90ctl::moveToLocation(double iAngle)
{
	if ((iAngle < minAngle) || (iAngle > maxAngle)) return 0;
	int retSts = setTargetLocation(iAngle);
	time_sleep(toPWM(iAngle) * 100 / 1000000);
	return retSts;
}

int sg90ctl::getCurrentLocation()
{
	int curWidth = 0;
	if (isHardwarePWM())
		curWidth = gpioGetPWMdutycycle(_GPIOidx);
	else
		curWidth = gpioGetServoPulsewidth(_GPIOidx);
	
	if (curWidth == PI_BAD_USER_GPIO || curWidth == PI_NOT_SERVO_GPIO) throw "bad configuration";
	if (_GPIOidx) return toAngle(curWidth);
    return 0;
}

double sg90ctl::toAngle(double iValue)
{
	double wrkValue = iValue;
	if (isHardwarePWM())
		wrkValue = wrkValue * signalPeriod;
	return ((wrkValue - minPulse) * angleRange / pulseRange + minAngle);
}

double sg90ctl::toPWM(double iAngle)
{
	return (minPulse + (iAngle - minAngle) * pulseRange / angleRange);
}

double sg90ctl::toDutyCycle(double iAngle)
{
	return toPWM(iAngle) / signalPeriod;
}

//void sg90ctl::_pwmChangedEXT(int gpio, int level, uint32_t tick, void *user)
//{
//	sg90ctl * myself = (sg90ctl *)user;
//	if (myself) myself->
//}


#ifndef __cplusplus
}
#endif //ifndef __cplusplus