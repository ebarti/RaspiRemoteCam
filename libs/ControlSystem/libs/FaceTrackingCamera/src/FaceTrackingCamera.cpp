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
	_TrackedObjectId = -1;
	_TrackingStarted = false;
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
	Ptr<CascadeClassifier> faceCascadePtr = makePtr<CascadeClassifier>(_faceClassifierPath);
	Ptr<CascadeClassifier> nestedFaceCascadePtr = makePtr<CascadeClassifier>(_nestedClassifier);
	if (faceCascadePtr->empty() || nestedFaceCascadePtr->empty()) return 2;

	_spFaceDetector = makePtr<FaceDetectorAdapter>(faceCascadePtr);
	_spTrackingDetector = makePtr<FaceDetectorAdapter>(nestedFaceCascadePtr);
	Size minSize(40,40);
	_spFaceDetector->setMinObjectSize(minSize);
	_spTrackingDetector->setMinObjectSize(minSize);
	DetectionBasedTracker::Parameters params;
	params.minDetectionPeriod = 0;
	
	_spTracker = makePtr<DetectionBasedTracker>(_spFaceDetector, _spTrackingDetector, params);
	//_spTracker = new DetectionBasedTracker(_spFaceDetector, _spTrackingDetector, params);
//	_spTrack = makePtr<DetectionBasedTracker>(faceDetector, trackingDetector, params);
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
int FaceTrackingCamera::GetCameraProperties(VideoCaptureProperties iPropName, double & oPropValue)
{
	if (!_Camera.isOpened()) return 1;	
	oPropValue = _Camera.get(iPropName);
	return 0;
}

///////////////////////////////////
// Implements GetImageAndTarget
///////////////////////////////////
int FaceTrackingCamera::Process(Mat& oImg, Ptr<Point2f> & oTargetOffset)
{
	int rc = GetImage(oImg);
	
	if(0==rc)
		rc = ProcessImage(oImg.clone(), oTargetOffset);

	return rc;
}

///////////////////////////////////
// Implements GetImage
///////////////////////////////////
int FaceTrackingCamera::GetImage(Mat& oImg)
{
	if (!_isInitialized) return 1;
	if (_tstMode)
		oImg = imread("/home/pi/Desktop/download.jpg");
	else if(_Camera.isOpened() && _Camera.grab())
		_Camera.retrieve(oImg);
	return (!oImg.data) ? 2 : 0;
}

///////////////////////////////////
// Implements ProcessImage
///////////////////////////////////
int FaceTrackingCamera::ProcessImage(const Mat& iImg, cv::Ptr<cv::Point2f>& oPoint)
{
	// Convert to Gray Scale 
	Mat grayImg;
	cvtColor(iImg, grayImg, COLOR_BGR2GRAY);
	_spTracker->process(grayImg);
	vector<DetectionBasedTracker::ExtObject> trackedObjects;
	_spTracker->getObjects(trackedObjects);
	if (trackedObjects.size() == 0)
	{
		_TrackedObjectId = -1;
		return 1;
	}

	// Compute the location
	return ComputeLocation(trackedObjects, makePtr<Point2f>(grayImg.rows/2, grayImg.cols/2), oPoint);
}

///////////////////////////////////
// Implements ComputeLocation
///////////////////////////////////
int FaceTrackingCamera::ComputeLocation(const vector<DetectionBasedTracker::ExtObject>& iObjects, Ptr<Point2f> iCenter, Ptr<Point2f>& oPoint)
{
	oPoint = nullptr;
	// Criteria is as follows:
	//	if tracked object id = -1 (we are not tracking anything), then select the closest face to the center of the camera
	int facesPresent = iObjects.size();
	Point2f zero;
	
	double minDistance = cv::norm(*iCenter - zero);
	for (int ii = 0; ii < facesPresent; ii++)
	{
		DetectionBasedTracker::ExtObject itrObj = iObjects[ii];
		Ptr<Point2f> curTrackedObjPoint;
		curTrackedObjPoint->x = itrObj.location.x + itrObj.location.width / 2;
		curTrackedObjPoint->y = itrObj.location.y + itrObj.location.height / 2;
		if (itrObj.id == _TrackedObjectId)
		{
			oPoint = curTrackedObjPoint;
			break;
		}
		else
		{
			// Compound the closest to the center of the image (rows/2 cols/2)
			double distance = cv::norm(*iCenter - *curTrackedObjPoint);
			if (distance < minDistance)
			{
				oPoint = curTrackedObjPoint;
				minDistance = distance;
			}
		}
	}

	return (nullptr != oPoint) ? 0 : 1;
}


#ifndef __cplusplus
}
#endif //ifndef __cplusplus