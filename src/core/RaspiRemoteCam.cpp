#include <stdio.h>
#include <iostream>
#include <ControlSystem.h>


int main(int argc, const char* argv[])
{
	std::promise<void> exitSignal;
	std::future<void> exitSignalFutureObj = exitSignal.get_future();
	// Create controlsystem
	ControlSystem* pControl = new ControlSystem();
	if (pControl)
	{
		setenv("OPENCV_SAMPLES_DATA_PATH", "/home/pi/opencv", 1);
		std::string cascadeFrontalfilename = cv::samples::findFile("data/lbpcascades/lbpcascade_frontalface.xml");
		int initCode = pControl->InitializeCamera(cascadeFrontalfilename, cascadeFrontalfilename, 1.0);
		if (0 == initCode) initCode = pControl->InitializeServos(12, 13);

		if (0 == initCode)
		{
			std::thread trackerThread(&ControlSystem::ActivateTrackingMode, pControl, std::move(exitSignalFutureObj));
			std::this_thread::sleep_for(std::chrono::seconds(10));
			exitSignal.set_value();
			trackerThread.join();
		}
	}
	delete pControl;
	pControl = NULL;
	return 0;
}