#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#include "ControlSystem.h"

ControlSystem::ControlSystem()
{
	_rpiCam = NULL;
	_tiltCtl = NULL;
	_panCtl = NULL;
}
ControlSystem::~ControlSystem()
{
	if(_rpiCam)
		delete _rpiCam;
	_rpiCam = NULL;
	if (_tiltCtl)
		delete _tiltCtl;
	_tiltCtl = NULL;
	if (_panCtl)
		delete _panCtl;
	_panCtl = NULL;
}

int ControlSystem::InitializeServos(int iTiltGPIOidx, int iPanGPIOidx)
{
	int retSts = 1;
	if (iTiltGPIOidx && iPanGPIOidx)
	{
		_tiltCtl = new sg90ctl(iTiltGPIOidx);
		_panCtl = new sg90ctl(iPanGPIOidx);
		if (_tiltCtl && _panCtl)
		{
			retSts = _tiltCtl->initialise();
			if (retSts) return retSts;
			retSts = _panCtl->initialise();
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
		_rpiCam = new FaceTrackingCamera(iCascadePath, iNestedCascadePath, iScale);
		
		if (_rpiCam)
			retSts = _rpiCam->Initialize();
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