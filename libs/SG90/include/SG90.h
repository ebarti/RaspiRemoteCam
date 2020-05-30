// Public interface for my custom SG90 control

#ifndef SG90_H
#define SG90_H


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
    sg90ctl(int iGPIOidx, double iMaxDutyCycleFactor, double iMinDutyCycleFactor);
    ~sg90ctl();

    // All return codes are = 0 if succeeded
    int getGPIOIdx() const { return _GPIOidx; };
	int moveToLocation(double iAngle);
    double getCurrentLocation();
	int initialise();
    int move(bool iMovePlus);
    void CleanUp();
private:
	
    int setTargetLocation(double iAngle);
    bool isHardwarePWM() const { return  ((12 == _GPIOidx) || (13 == _GPIOidx) || (18 == _GPIOidx) || (19 == _GPIOidx)) ? true : false; };
    double toAngle(unsigned int iValue) const;
    unsigned int toDutyCycle(double iAngle) const;
	// Data members
	int _GPIOidx;
    double _MaxDutyCycleFactor;
    double _MinDutyCycleFactor;
};

#ifndef __cplusplus
}
#endif //ifndef __cplusplus

#endif // SG90_H