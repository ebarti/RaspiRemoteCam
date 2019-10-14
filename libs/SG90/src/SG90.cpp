#include "SG90.h"
#include <pigpio.h>
#ifndef __cplusplus
extern "C++" {
#endif //#ifdef __cplusplus

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
	return gpioServo(_GPIOidx, 0);
}

int sg90ctl::getGPIOIdx()
{
    return _GPIOidx;
}

int sg90ctl::setTargetLocation(double iAngle)
{
    if((iAngle < minAngle) || (iAngle > maxAngle)) return 0;
	int pwmAngle = toPWM(iAngle);
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
	int curWidth = gpioGetServoPulsewidth(_GPIOidx);
	if (curWidth == PI_BAD_USER_GPIO || curWidth == PI_NOT_SERVO_GPIO) throw "bad configuration";
	if (_GPIOidx) return toAngle(curWidth);
    return 0;
}

//void sg90ctl::_pwmChangedEXT(int gpio, int level, uint32_t tick, void *user)
//{
//	sg90ctl * myself = (sg90ctl *)user;
//	if (myself) myself->
//}


#ifndef __cplusplus
}
#endif //ifndef __cplusplus