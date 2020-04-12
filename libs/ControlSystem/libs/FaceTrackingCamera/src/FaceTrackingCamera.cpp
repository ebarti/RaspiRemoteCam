#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus
#include "FaceTrackingCamera.h"

using namespace std;
using namespace cv;


// Constructor
FaceTrackingCamera::FaceTrackingCamera(string iCascadePath, string iNestedCascadePath, bool tstMode)
{
	_tstMode = tstMode;
	_faceClassifierPath = iCascadePath;
	_nestedClassifier = iNestedCascadePath;
}

// Destructor
FaceTrackingCamera::~FaceTrackingCamera()
{
	if (_Camera.isOpened()) _Camera.release();
	if (nullptr != _spTracker)
		_spTracker->stop();
}

///////////////////////////////////
// Implements Initialize()
///////////////////////////////////
int FaceTrackingCamera::Initialize()
{
	//Check if camera is already opened and error out if so
	if (_Camera.isOpened()) return 1;
	cv::Ptr<cv::CascadeClassifier> faceCascadePtr = makePtr<cv::CascadeClassifier>(_faceClassifierPath);
	cv::Ptr<cv::CascadeClassifier> nestedFaceCascadePtr = makePtr<cv::CascadeClassifier>(_nestedClassifier);
	
	if (faceCascadePtr->empty() || nestedFaceCascadePtr->empty()) return 2;

	cv::Ptr<DetectionBasedTracker::IDetector>  faceDetector = makePtr<FaceDetectorAdapter>(faceCascadePtr);
	cv::Ptr<DetectionBasedTracker::IDetector>  trackingDetector = makePtr<FaceDetectorAdapter>(nestedFaceCascadePtr);
	DetectionBasedTracker::Parameters params;
	_spTracker = makePtr<cv::DetectionBasedTracker>(faceDetector, trackingDetector, params);
//	_spTrack = makePtr<cv::DetectionBasedTracker>(faceDetector, trackingDetector, params);
	if (nullptr == _spTracker) return 3;
	if (!_spTracker->run()) return 4;
	//Open camera
	if (!_Camera.open()) return 5;
	_isInitialized = true;
	return 0;
}

///////////////////////////////////
// Implements GetCameraProperties
///////////////////////////////////
int FaceTrackingCamera::GetCameraProperties(cv::VideoCaptureProperties iPropName, double & oPropValue)
{
	if (!_Camera.isOpened()) return 1;	
	oPropValue = _Camera.get(iPropName);
	return 0;
}

///////////////////////////////////
// Implements GetImageAndTarget
///////////////////////////////////
int FaceTrackingCamera::GetImageAndTarget(cv::Mat& oImg, Point & oTargetOffset)
{
	if (GetImage(oImg)) return 1;
	Mat frame = oImg.clone();
	if (GetFeatureCenter(frame, oTargetOffset)) return 2;
	return 0;
}

///////////////////////////////////
// Implements GetImage
///////////////////////////////////
int FaceTrackingCamera::GetImage(cv::Mat& oImg)
{
	if (!_isInitialized) return 1;
	if (_tstMode)
		oImg = imread("/home/pi/Desktop/TestImage.jpg");
	else if(_Camera.isOpened() && _Camera.grab())
		_Camera.retrieve(oImg);
	return (!oImg.data) ? 1 : 0;
}

///////////////////////////////////
// Implements GetFeatureCenter
///////////////////////////////////
int FaceTrackingCamera::GetFeatureCenter(const Mat& iImg, Point & oPoint)
{
	vector<Rect> faces;
	Mat grayImg;
	cvtColor(iImg, grayImg, COLOR_BGR2GRAY); // Convert to Gray Scale 
	_spTracker->process(grayImg);
	_spTracker->getObjects(faces);

	// Find face previously being tracked, set a tolerance of 5% motion
	bool faceFound = (faces.size());
	for (size_t i = 0; i < faces.size(); i++)
	{
		
	}
	return (faceFound) ? 0 : 1;
}


#ifndef __cplusplus
}
#endif //ifndef __cplusplus