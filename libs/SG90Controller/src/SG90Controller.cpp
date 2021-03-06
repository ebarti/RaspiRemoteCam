#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#include "SG90Controller.h"
#include <pigpio.h>
#include <chrono>
SG90Controller::SG90Controller()
{
	// Init pigpio Library
	_camInitOK = false;
	_servosInitOK = false;
	gpioInitialise();
}
SG90Controller::~SG90Controller()
{
	// Terminate library.
	gpioTerminate();
}

int SG90Controller::InitializeServos(int iTiltGPIOidx, int iPanGPIOidx)
{
	int retSts = 1;
	if (iTiltGPIOidx && iPanGPIOidx)
	{
		_spTiltCtrl = std::make_unique<sg90ctl>(iTiltGPIOidx, 0.04, 0.1);
		_spPanCtrl = std::make_unique<sg90ctl>(iPanGPIOidx, 0.04, 0.1);
		if (nullptr != _spTiltCtrl && nullptr != _spPanCtrl)
		{
			retSts = _spTiltCtrl->initialise();
			if (retSts) return retSts;
			retSts = _spPanCtrl->initialise();
			retSts = -1 * retSts; // invert the number to signal it is an error with Pan servo
		}
	}
	if (!retSts) _servosInitOK = true;
	return retSts;
}

int SG90Controller::InitializeCamera(std::string iCascadePath, std::string iNestedCascadePath, double iScale)
{
	int retSts = 1;
	if (iCascadePath.length() > 0)
	{
		_spCamera = std::make_shared<FaceTrackingCamera>(iCascadePath, iNestedCascadePath, iScale);
		if (_spCamera)
			retSts = _spCamera->Initialize();
	}
	if (!retSts) _camInitOK = true;
	return retSts;
}

int SG90Controller::ActivateTrackingMode(std::future<void> exitFutureObj)
{
	if (!_camInitOK || !_servosInitOK) return 1;
	while (exitFutureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		Track();
	}
	return 0;
}

int SG90Controller::ActivateUIMode(std::future<void> exitFutureObj)
{
	if (!_camInitOK) return 1;
	while (exitFutureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
	{
		// NOP
	}
	return 0;
}

void SG90Controller::Track()
{
	cv::Ptr<cv::Point2f> targetLocation;
	cv::Mat image;
	
	if (0 == _spCamera->Process(image, targetLocation))
	{
		double centerX = image.rows / 2.0;
		double centerY = image.cols / 2.0;
		if (targetLocation)
		{
			if (targetLocation->x != centerX)
				_spPanCtrl->move(targetLocation->x > centerX);
			if (targetLocation->y != centerY)
				_spTiltCtrl->move(targetLocation->y > centerY);
		}
	}
}


#ifndef __cplusplus
}
#endif //ifndef __cplusplus