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
	int retSts = 1;
	if (iTiltGPIOidx && iPanGPIOidx)
	{
		tiltCtl = new sg90ctl(iTiltGPIOidx);
		panCtl = new sg90ctl(iPanGPIOidx);
		if (tiltCtl && panCtl)
		{
			retSts = tiltCtl->initialise();
			if (retSts) return retSts;
			retSts = panCtl->initialise();
			retSts = -1 * retSts; // invert the number to signal it is an error with Pan servo
		}
	}
	if (!retSts) _servosInitOK = true;
	return retSts;
}

int ControlSystem::InitializeCamera(std::string iCascadePath, std::string iNestedCascadePath, double iScale)
{
	int retSts = 1;
	if (iCascadePath.length() > 0)
	{
		rpiCam = new FaceTrackingCamera(iCascadePath, iNestedCascadePath, iScale);
		
		if (rpiCam)
			retSts = rpiCam->Initialize();
	}
	if (!retSts) _camInitOK = true;
	return retSts;
}

int ControlSystem::ActivateTrackingMode()
{
	if (_camInitOK && _servosInitOK)
	{
	}
	return 0;
}

int ControlSystem::ActivateUIMode()
{
	if (_camInitOK)
	{
	}
	return 0;
}

#ifndef __cplusplus
}
#endif //ifndef __cplusplus