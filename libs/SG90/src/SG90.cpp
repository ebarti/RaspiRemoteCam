#include "SG90.h"
#include <pigpio.h>
#ifndef __cplusplus
extern "C++" {
#endif //#ifdef __cplusplus

// Constructor
sg90ctl::sg90ctl(int iGPIOidx)
{
	_GPIOidx = iGPIOidx;
}
// Destructor
sg90ctl::~sg90ctl()
{
    //Nothing to do for now
}

int sg90ctl::getGPIOIdx()
{
    return _GPIOidx;
}

int sg90ctl::setTargetLocation(double iAngle)
{
    if((iAngle < minAngle) || (iAngle > maxAngle)) return 0;
	return gpioServo(_GPIOidx, toPWM(iAngle));
}

int sg90ctl::getCurrentLocation()
{
	if (_GPIOidx) return toAngle(gpioGetServoPulsewidth(_GPIOidx));
    return 0;
}

#ifndef __cplusplus
}
#endif //ifndef __cplusplus