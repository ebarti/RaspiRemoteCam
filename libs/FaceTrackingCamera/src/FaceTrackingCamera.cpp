#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus
#include "FaceTrackingCamera.h"

//using namespace cv;
using namespace std;
using namespace cv;
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
	oProps.contrast = static_cast<int>(_Camera.get(CAP_PROP_CONTRAST));
	oProps.exposure = static_cast<int>(_Camera.get(CAP_PROP_EXPOSURE));
	oProps.gain = static_cast<int>(_Camera.get(CAP_PROP_GAIN));
	oProps.imFormat = static_cast<int>(_Camera.get(CAP_PROP_FORMAT));
	oProps.mode = static_cast<int>(_Camera.get(CAP_PROP_MODE));
	oProps.saturation = static_cast<int>(_Camera.get(CAP_PROP_SATURATION));
	oProps.whiteBalanceBlue = static_cast<int>(_Camera.get(CAP_PROP_WHITE_BALANCE_BLUE_U));
	oProps.whiteBalanceRed = static_cast<int>(_Camera.get(CAP_PROP_WHITE_BALANCE_RED_V));
	oProps.xDim = static_cast<int>(_Camera.get(CAP_PROP_FRAME_HEIGHT));
	oProps.yDim = static_cast<int>(_Camera.get(CAP_PROP_FRAME_WIDTH));
	return 0;
}


int FaceTrackingCamera::GetImageAndTarget(cv::Mat& oImg, Point & oTargetOffset)
{
	if (!_isInitialized) return 1;
	if (_Camera.isOpened())
	{
		Mat frame, image;
		if (_Camera.grab())
		{
			_Camera.retrieve(frame);
			if (frame.empty()) return 2;
			oImg = frame.clone();
			if (GetFeatureCenter(oImg, oTargetOffset, _Scale)) return 3;
		}
	}
	return 0;
}


int FaceTrackingCamera::GetFeatureCenter(Mat& iImg, Point & oPoint, double iScale)
{
	vector<Rect> faces, faces2;
	Mat gray, smallImg;
	cvtColor(iImg, gray, COLOR_BGR2GRAY); // Convert to Gray Scale 
	double fx = 1 / _Scale;
	// Resize the Grayscale Image  
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);
	// Detect faces of different sizes using cascade classifier  
	_CascadeClassifier.detectMultiScale(smallImg, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
	// Find face previously being tracked, set a tolerance of 5% motion
	bool faceFound = false;
	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Point center;
		center.x = cvRound((r.x + r.width*0.5)*_Scale);
		center.y = cvRound((r.y + r.height*0.5)*_Scale);
		if (IsWithinTolerance(_TrackedFaceLocation, center))
		{
			_TrackedFaceLocation = center;
			oPoint = center;
			Scalar color = Scalar(255, 0, 0); // Color for Drawing tool
			int radius;
			double aspect_ratio = (double)r.width / r.height;
			if (0.75 < aspect_ratio && aspect_ratio < 1.3)
			{
				// Draw a circle around the face, this frame is returned for display
				radius = cvRound((r.width + r.height)*0.25*_Scale);
				circle(iImg, center, radius, color, 3, 8, 0);
			}
			faceFound = true;
			break;
		}	
	}
	return ((faceFound) ? 0 : 1);
}

bool FaceTrackingCamera::IsWithinTolerance(cv::Point iP1, cv::Point iP2)
{
	if (_noPrevFaceFound)
	{
		_noPrevFaceFound = false;
		return true;
	}

	int xDim = static_cast<int>(_Camera.get(CAP_PROP_FRAME_HEIGHT));
	int yDim = static_cast<int>(_Camera.get(CAP_PROP_FRAME_WIDTH));
	//Should later change this to a speed setting, tracking frame rates and compounding an approx speed
	if ((cv::abs((iP1.x - iP2.x) / xDim) > _tol) || (cv::abs((iP1.y - iP2.y) / yDim) > _tol)) return false;
	return true;
}


#ifndef __cplusplus
}
#endif //ifndef __cplusplus