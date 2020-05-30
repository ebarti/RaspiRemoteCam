#ifndef FaceDetectorAdapter_H
#define FaceDetectorAdapter_H

#ifndef __cplusplus // C++ compatibility
extern "C++" {
#endif //#ifndef __cplusplus

#ifndef DEBUG
#define DEBUG
#endif

#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/core.hpp>        // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/highgui.hpp>  // OpenCV window I/O
#include <opencv2/features2d.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/objdetect/detection_based_tracker.hpp>
#include <iostream>

class FaceDetectorAdapter : public cv::DetectionBasedTracker::IDetector
{
public:
	FaceDetectorAdapter(cv::Ptr<cv::CascadeClassifier> detector) :
		IDetector(),
		Detector(detector)
	{
		CV_Assert(detector);
	}

	void detect(const cv::Mat &Image, std::vector<cv::Rect> &objects) CV_OVERRIDE
	{
		Detector->detectMultiScale(Image, objects, scaleFactor, minNeighbours, 0, minObjSize, maxObjSize);
	}

	virtual ~FaceDetectorAdapter() CV_OVERRIDE
	{}

private:
	FaceDetectorAdapter();
	cv::Ptr<cv::CascadeClassifier> Detector;
};

#endif