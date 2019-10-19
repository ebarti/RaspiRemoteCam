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

typedef struct
{
	int xDim;
	int yDim;
	int imFormat;
	int brightness;
	int contrast;
	int saturation;
	int gain;
	int exposure; //-1 = auto
	int whiteBalanceRed; //-1 = auto
	int whiteBalanceBlue; //-1 = auto
	int mode; //0 = auto
} cameraProps;


class FaceTrackingCamera
{
	//Public methods
public:
	//Constructor
	FaceTrackingCamera(string iCascadePath, string iNestedCascadePath, double iScale = 1.0);
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
	int GetCameraCenter(int & oX, int& oY);

	/* Summary of Return Codes
	0 = Succeeded
	1 = Not initialized
	*/
	int GetCameraProperties(cameraProps& oProps);

	/* Summary of Return Codes
	0 = Succeeded
	1 = Not initialized
	*/
	int GetTargetOffset(Point2d & oTargetOffset);

private:
	Point2d GetFeatureCenter(Mat& iImg, Point2d & oPoint, double iScale);
	bool IsFaceAvailable();

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
