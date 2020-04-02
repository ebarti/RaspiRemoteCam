// Public interface for my custom faceTracking class
#ifndef FaceTrackingCamera_H
#define FaceTrackingCamera_H
#include <stdint.h>
#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#include "opencv2/opencv.hpp"
#include <raspicam/raspicam_cv.h>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include <string>

class FaceTrackingCamera
{
	//Public methods
public:
	//Constructor
	FaceTrackingCamera(std::string iCascadePath, std::string iNestedCascadePath, double iScale = 1.0);
	~FaceTrackingCamera();

	/* Summary of Return Codes
	0 = Succeeded
	1 = Camera opened before init
	2 = No valid Path for Cascade Classifier
	3 = No valid path for Nested Cascade Classifier
	4 = Cannot open raspberry Cam
	*/
	int Initialize();

	/* Summary of Return Codes
	0 = Succeeded
	1 = Not initialized
	*/
	int GetCameraProperties(cv::VideoCaptureProperties iPropName, double & oPropValue);

	/* Summary of Return Codes
	0 = Succeeded
	1 = Not initialized
	2 = No frame detected, acquisition error
	3 = No faces detected
	*/
	int GetImageAndTarget(cv::Mat& oImg, cv::Point & oTargetOffset);

	
private:
	/* Summary of Return Codes
	0 = Succeeded
	1 = No faces detected
	*/
	int GetFeatureCenter(cv::Mat& iImg, cv::Point & oPoint, double iScale);

	bool IsSameFace(cv::Point iP1, cv::Point iP2);

	bool IsWithinTolerance(cv::Point iP1, cv::Point iP2);

	//Data members
	bool _isInitialized;
	bool _noPrevFaceFound;
	double _Scale;
	std::string _CascadePath;
	std::string _NestedCascadePath;
	cv::CascadeClassifier _CascadeClassifier;
	cv::CascadeClassifier _NestedCascadeClassifier;
	cv::Point _TrackedFaceLocation;
	raspicam::RaspiCam_Cv _Camera;
	double _tol = 0.05;
};


#ifndef __cplusplus
}
#endif //ifndef __cplusplus

#endif
