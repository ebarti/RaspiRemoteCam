// Public interface for my custom SG90 control

#ifndef SG90_H
#define SG90_H

#include <stdint.h>

#ifndef __cplusplus // C++ compatibility
extern "C++"{
#endif //#ifndef __cplusplus

#define operatingFreq = 50.0
#define minPulse = 1000.0
#define maxPulse = 2000.0
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
    int updateSettings(int frequency, int minAnglePulseWidth, int maxAnglePulseWidth);
    int getGPIOIdx();
    int setTargetLocation(int iAngle);
    int getCurrentLocation();
    int moveTo(bool direction /* Zero = Left, One = Right */);

    // Data members
private:
    int GPIOidx, freq, minW, maxW;

    sg90ctlCB_t theCallback;


}

#ifndef __cplusplus
}
#endif //ifndef __cplusplus

#endif // SG90_H