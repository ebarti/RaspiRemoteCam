#include "SG90.h"
#include <pigpio.h>
#ifndef __cplusplus
extern "C++" {
#endif //#ifdef __cplusplus

const double minAngle = -90.0;
const double maxAngle = 90.0;
const double angleRange = 180; // Degrees the servo is able to move
const int operatingFreq = 50;
const int minDuty = 500000;
const int maxDuty = 1000000;
const int dutyRange = maxDuty - minDuty;
// Constructor
sg90ctl::sg90ctl(int iGPIOidx/*, sg90ctlCB_t callback*/)
{
	_GPIOidx = iGPIOidx;
}
// Destructor
sg90ctl::~sg90ctl()
{
	
}

void sg90ctl::CleanUp()
{
	gpioPWM(_GPIOidx, 0);
}

int sg90ctl::initialise()
{
	int retSts = gpioSetPWMfrequency(getGPIOIdx(), operatingFreq);
	if (0 == retSts)
		retSts = gpioSetPWMrange(getGPIOIdx(), maxDuty);
	if (0 == retSts)
		retSts = gpioPWM(_GPIOidx, toDutyCycle(0));
	return retSts;
}

int sg90ctl::setTargetLocation(double iAngle)
{
	return gpioPWM(_GPIOidx, toDutyCycle(iAngle));
}
int sg90ctl::moveToLocation(double iAngle)
{
	if ((iAngle < minAngle) || (iAngle > maxAngle)) return 1;
	return setTargetLocation(iAngle);
}

double sg90ctl::getCurrentLocation()
{
	if (!_GPIOidx) return 0;
	int curWidth = gpioGetPWMdutycycle(_GPIOidx);
		
	if (curWidth == PI_BAD_USER_GPIO || curWidth == PI_NOT_SERVO_GPIO) throw "bad configuration";
	return toAngle(curWidth);
}

int sg90ctl::move(bool iMovePlus) //Increment one degree
{
	double deltaAngle = (iMovePlus) ? 1.0 : -1.0;
	return moveToLocation(deltaAngle + getCurrentLocation());
}

double sg90ctl::toAngle(unsigned int iValue)
{
	double wrkValue = iValue;
	return (wrkValue - minDuty) * angleRange / dutyRange + minAngle;
}

unsigned int sg90ctl::toDutyCycle(double iAngle)
{
	return (minDuty + (iAngle - minAngle) * dutyRange / angleRange);
}



//void sg90ctl::_pwmChangedEXT(int gpio, int level, uint32_t tick, void *user)
//{
//	sg90ctl * myself = (sg90ctl *)user;
//	if (myself) myself->
//}


#ifndef __cplusplus
}
#endif //ifndef __cplusplus