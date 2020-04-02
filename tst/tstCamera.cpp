#include <FaceTrackingCamera.h>
#include <gtest/gtest.h>
#include "opencv2/opencv.hpp"
using namespace cv;

TEST(Camera, Initialization)
{
	FaceTrackingCamera * pCamera = new FaceTrackingCamera("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml", "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
	ASSERT_EQ((NULL != pCamera), true);

	EXPECT_EQ(pCamera->Initialize(), 0);
	delete pCamera;
	pCamera = NULL;
}

TEST(Camera, CameraProperties)
{
	FaceTrackingCamera * pCamera = new FaceTrackingCamera("/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml", "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml");
	ASSERT_EQ((NULL != pCamera), true);

	EXPECT_EQ(pCamera->Initialize(), 0);
	double Value = 0.0;

	EXPECT_EQ(pCamera->GetCameraProperties(cv::VideoCaptureProperties::CAP_PROP_GAIN, Value), 0);
	delete pCamera;
	pCamera = NULL;
}