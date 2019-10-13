// Public interface for my custom SG90 control

#ifndef SG90_H
#define SG90_H

#include <stdint.h>

#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#define minAngle -90.0
#define maxAngle 90.0
#define angleRange (maxAngle - minAngle) // Degrees the servo is able to move
#define operatingFreq 50.0
#define minPulse 1000.0
#define maxPulse 2000.0
#define pulseRange (maxPulse-minPulse)

#define toAngle(pwm) ((pwm-minPulse)*angleRange/pulseRange + minAngle)
#define toPWM(iAngle) (minPulse + (iAngle - minAngle)*pulseRange/angleRange)
// for future callback implementation
typedef void (*sg90ctlCB_t)(int);

class sg90ctl
{
    //Public methods:
public:
    //Constructor
    sg90ctl(int iGPIOidx);
    ~sg90ctl();

    // All return codes are = 1 if succeeded
    int getGPIOIdx();
    int setTargetLocation(double iAngle);
    int getCurrentLocation();
 
    // Data members
private:
	int _GPIOidx;
	double _targetAngle;

    sg90ctlCB_t theCallback;


};

#ifndef __cplusplus
}
#endif //ifndef __cplusplus

#endif // SG90_H