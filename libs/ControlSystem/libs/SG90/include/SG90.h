// Public interface for my custom SG90 control

#ifndef SG90_H
#define SG90_H

#include <stdint.h>

#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

// for future callback implementation
typedef void (*sg90ctlCB_t)(int);

class sg90ctl
{
    //Public methods:
public:
    //Constructor
    // For a raspberry pi 4, the hardware PWM capable pins are 12, 13, 18, 19
    sg90ctl(int iGPIOidx);
    ~sg90ctl();

    // All return codes are = 0 if succeeded
    int getGPIOIdx();
    int setTargetLocation(double iAngle);
	int moveToLocation(double iAngle);
    int getCurrentLocation();
	int initialise();
    
private:
	
    bool isHardwarePWM() { return  ((12 == _GPIOidx) || (13 == _GPIOidx) || (18 == _GPIOidx) || (19 == _GPIOidx)) ? 1 : 0; };
    double toAngle(double iValue);
    double toPWM(double iAngle);
    double toDutyCycle(double iAngle);
	// Data members
	int _GPIOidx;
	double _targetAngle;
    
};

#ifndef __cplusplus
}
#endif //ifndef __cplusplus

#endif // SG90_H