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
	ControlSystem();
	~ControlSystem();
	/*
	@param iTiltGPIOidx:
		The GPIO index of the tilt servo within the RPI board. The servo must be connected to a USER GPIO, range index = 0-31
	@param iPanGPIOidx:
	The GPIO index of the pan servo within the RPI board. The servo must be connected to a USER GPIO, range index = 0-31
	@return:
		0 = Succeeded
		1 = Error initializing (either bad GPIO or bad PulseWidth)
	*/
	int InitializeServos(int iTiltGPIOidx, int iPanGPIOidx);

	/*
	@param iCascadePath:
		Open CV cascade classifier file path (.xml) for feature detection (face detection in our case)
	@param iNestedCascadePath:
		OpenCV nested cascade clasifier file path (.xml) for a nested feature detection
	@param iScale:
		The scale of the images retrieved by the raspberry cam. Typically 1
	@return:
		0 = Succeeded
		1 = Error initializing (either bad GPIO or bad PulseWidth)
	*/
	int InitializeCamera(std::string iCascadePath, std::string iNestedCascadePath, double iScale = 1.0);

	int ActivateTrackingMode();

	int ActivateUIMode();

private:
	
	bool _camInitOK, _servosInitOK;
	FaceTrackingCamera* _rpiCam;
	sg90ctl* _tiltCtl;
	sg90ctl* _panCtl;
};


#ifndef __cplusplus
}
#endif //ifndef __cplusplus
#endif //ifndef ControlSystem_H