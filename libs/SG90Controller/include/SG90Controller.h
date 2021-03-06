#ifndef SG90Controller_H
#define SG90Controller_H

#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#include "../../SG90/include/SG90.h"
#include "../../FaceTrackingCamera/include/FaceTrackingCamera.h"
#include <future>

class SG90Controller
{
public:
	SG90Controller();
	~SG90Controller();
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

	/*
	Summary of return codes:
	1 = System not initialized
	2 = Canceled before starting
	*/
	int ActivateTrackingMode(std::future<void> exitFutureObj);

	int ActivateUIMode(std::future<void> exitFutureObj);

private:

	void Track();	
	
	bool _camInitOK, _servosInitOK;
	std::shared_ptr<FaceTrackingCamera> _spCamera;
	std::unique_ptr<sg90ctl> _spTiltCtrl;
	std::unique_ptr<sg90ctl> _spPanCtrl;
};


#ifndef __cplusplus
}
#endif //ifndef __cplusplus
#endif //ifndef SG90Controller_H