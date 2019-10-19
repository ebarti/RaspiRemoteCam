// Public interface for my custom faceTracking class
#ifndef FaceTracking_H
#define FaceTracking_H
#include <stdint.h>
#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#include "opencv2/opencv.hpp"
#include "raspicam/raspicam_cv.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"

class FaceTrackingCamera
{
	//Public methods
public:
	//Constructor
	FaceTrackingCamera(string iCascadePath, string iNestedCascadePath);
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
	int GetTargetOffset(Point2d & oTargetOffset);

	/* Summary of Return Codes
	0 = Succeeded
	1 = Not initialized
	*/
	int IsFaceAvailable(bool & oFaceAvailable);

	/* Summary of Return Codes
	0 = Succeeded
	1 = Camera opened before init
	2 = No valid Path for Cascade Classifier
	3 = No valid path for Nested Cascade Classifier
	4 = Cannot open raspberry Cam
	*/
	int GetFeatureCenter(Mat& iImg, Point2d & oPoint, double iScale = 1);


private:

	//Data members
	bool _isInitialized;
	double _Scale;
	string _CascadePath;
	string _NestedCascadePath;
	CascadeClassifier _CascadeClassifier;
	CascadeClassifier _NestedCascadeClassifier;
	raspicam::RaspiCam_Cv _Camera;

};


#ifndef __cplusplus
}
#endif //ifndef __cplusplus

#endif
