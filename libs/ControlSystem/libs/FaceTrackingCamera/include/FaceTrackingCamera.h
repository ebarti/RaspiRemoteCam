// Public interface for my custom faceTracking class
#ifndef FaceTrackingCamera_H
#define FaceTrackingCamera_H
#include <stdint.h>
#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#include <raspicam/raspicam_cv.h>
#include "FaceTracker.h"
#include <memory>
#include <string>


class FaceTrackingCamera
{
	//Public methods
public:
	//Constructor
	FaceTrackingCamera(std::string iCascadePath, std::string iNestedCascadePath, bool tstMode = false);
	~FaceTrackingCamera();

	/* Summary of Return Codes
	0 = Succeeded
	1 = Camera opened before init
	2 = No valid Path for Cascade Classifier or Nested Cascade Classifier
	3 = Could not start tracker
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

protected:

	/* Summary of Return Codes
	0 = Succeeded
	1 = Camera not initialized
	2 = Could not get image, acquisition error
	*/
	int GetImage(cv::Mat& oImg);

	/* Summary of Return Codes
	0 = Succeeded
	1 = No faces detected
	*/
	int GetFeatureCenter(const cv::Mat& iImg, cv::Point & oPoint);

	//Data members
	bool _isInitialized;
	std::string _faceClassifierPath;
	std::string _nestedClassifier;
	raspicam::RaspiCam_Cv _Camera;
	bool _tstMode;
	//std::unique_ptr<cv::DetectionBasedTracker> _spTracker;
	cv::Ptr<cv::DetectionBasedTracker> _spTracker;
};


#ifndef __cplusplus
}
#endif //ifndef __cplusplus

#endif
