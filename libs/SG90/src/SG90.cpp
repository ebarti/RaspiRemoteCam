#include "SG90.h"
#include <pigpio.h>
#ifndef __cplusplus
extern "C" {
#endif //#ifdef __cplusplus

// Constructor
sg90ctl::sg90ctl(int iGPIOidx, int ifrequency, int iminAnglePulseWidth, int imaxAnglePulseWidth)
{
    _GPIOidx = iGPIOidx;
    _freq = ifrequency;
    _minW = iminAnglePulseWidth;
    _maxW = imaxAnglePulseWidth;
}

// Destructor
sg90ctl::~sg90ctl()
{
    //Nothing to do for now
}

int sg90ctl::updateSettings(int ifrequency, int iminAnglePulseWidth, int imaxAnglePulseWidth)
{
    if (gpioSetPWMfrequency(13,13)>0) return 0;
    return 1;
}

int sg90ctl::getGPIOIdx()
{
    return _GPIOidx;
}

int sg90ctl::setTargetLocation(double iAngle)
{
    if((iAngle < 0.0) || (iAngle > 270.0)) return 0;
}

int sg90ctl::getCurrentLocation()
{
    return 0;
}

int sg90ctl::moveTo(bool direction /* Zero = Left, One = Right */)
{
    return 0;
}

#ifndef __cplusplus
}
#endif //ifndef __cplusplus