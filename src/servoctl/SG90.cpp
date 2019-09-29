#include "SG90.h"

#ifdef __cplusplus // C++ compatibility
extern "C"{
    #include <pigpio.h>
}
#else // #ifdef __cplusplus -- C compatibility
#include <pigpio.h>
extern "C++"{
#endif //#ifdef __cplusplus

// Constructor
sg90ctl::sg90ctl(int iGPIOidx)
{
    
}

#ifndef __cplusplus
}
#endif //ifndef __cplusplus