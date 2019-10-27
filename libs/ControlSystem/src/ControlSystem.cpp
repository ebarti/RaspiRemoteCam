#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#include "ControlSystem.h"

ControlSystem::ControlSystem()
{
	rpiCam = NULL;
	tiltCtl = NULL;
	panCtl = NULL;
}
ControlSystem::~ControlSystem()
{
	if(rpiCam)
		delete rpiCam;
	rpiCam = NULL;
	if (tiltCtl)
		delete tiltCtl;
	tiltCtl = NULL;
	if (panCtl)
		delete panCtl;
	panCtl = NULL;
}

int ControlSystem::InitializeServos(int iTiltGPIOidx, int iPanGPIOidx)
{
	if (iTiltGPIOidx && iPanGPIOidx)
	{
		tiltCtl = new sg90ctl(iTiltGPIOidx);
		panCtl = new sg90ctl(iPanGPIOidx);
		if (tiltCtl && panCtl)
		{
			int initSts = tiltCtl->initialise();
			if (initSts) return initSts;
			initSts = panCtl->initialise();
			return (-1 * initSts); // invert the number to signal it is an error with Pan servo
		}
	}
	return 1;
}

int ControlSystem::InitializeCamera(std::string iCascadePath, std::string iNestedCascadePath, double iScale = 1.0)
{
	if (iCascadePath.length() > 0)
	{
		rpiCam = new FaceTrackingCamera(iCascadePath, iNestedCascadePath, iScale);
		if (rpiCam)
			return rpiCam->Initialize();
	}
	return 1;
}

#ifndef __cplusplus
}
#endif //ifndef __cplusplus