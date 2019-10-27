#ifndef ControlSystem_H
#define ControlSystem_H

#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#include <SG90.h>
#include <FaceTrackingCamera.h>

class ControlSystem
{
public:
	ControlSystem(int iTiltGPIOidx, int iPanGPIOidx);
	~ControlSystem();

	int Initialize();

private:

	sg90ctl tiltCtl;
	
};


#ifndef __cplusplus
}
#endif //ifndef __cplusplus
#endif //ifndef ControlSystem_H