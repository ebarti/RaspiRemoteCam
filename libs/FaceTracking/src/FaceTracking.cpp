#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus
#include "FaceTracking.h"

using namespace cv;
using namespace std;

// Constructor
FaceTrackingCamera::FaceTrackingCamera(string iCascadePath, string iNestedCascadePath, double iScale)
{
	_Scale = iScale;
	_CascadePath = iCascadePath;
	_NestedCascadePath = iNestedCascadePath;
}
FaceTrackingCamera::~FaceTrackingCamera()
{
	if (_Camera.isOpened()) _Camera.release();
}

int FaceTrackingCamera::Initialize()
{
	//Check if camera is already opened and error out if so
	if (_Camera.isOpened()) return 1;

	//Load the classifiers
	if (!_CascadeClassifier.load(_CascadePath)) return 2;
	if (!_NestedCascadeClassifier.load(_NestedCascadePath)) return 3;

	//Open camera
	if (!_Camera.open()) return 4;
	_isInitialized = true;
	return 0;
}

int FaceTrackingCamera::GetCameraProperties(cameraProps& oProps)
{
	if (!_isInitialized) return 1;
	oProps.brightness = static_cast<int>(_Camera.get(CAP_PROP_BRIGHTNESS));

}


int FaceTrackingCamera::GetTargetOffset(Point2d & oTargetOffset)
{
	if (!_isInitialized) return 1;
	//_Camera.get()
	VideoCaptureProperties spprop;
	return 0;
}

int FaceTrackingCamera::GetCameraCenter(int & oX, int& oY)
{
	if (!_isInitialized) return 1;
	oX = _Camera.get(CAP_PROP_FRAME_HEIGHT);
	oY = _Camera.get(CAP_PROP_FRAME_WIDTH);
	return 0;
}


Point2d FaceTrackingCamera::GetFeatureCenter(Mat& iImg, Point2d & oPoint, double iScale)
{
	
}


#ifndef __cplusplus
}
#endif //ifndef __cplusplus