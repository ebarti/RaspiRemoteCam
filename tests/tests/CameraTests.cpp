#include <FaceTrackingCamera.h>
#include <gtest/gtest.h>
#include <string>
#include "opencv2/opencv.hpp"
using namespace cv;

class CameraTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		std::unique_ptr<FaceTrackingCamera> newCamera(new FaceTrackingCamera(CascadePath, NestedCascadePath, 1.0, true));
		spCamera = std::move(newCamera);
		ASSERT_EQ(nullptr != spCamera, true) << "CRITICAL ERROR: Ran out of available memory" << std::endl;
	}

	const std::string CascadePath = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml";
	const std::string NestedCascadePath = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml";
	std::unique_ptr<FaceTrackingCamera> spCamera;
};


TEST_F(CameraTest, Initialization)
{
	EXPECT_EQ(spCamera->Initialize(), 0);
}

TEST_F(CameraTest, CameraProperties)
{
	EXPECT_EQ(spCamera->Initialize(), 0);
	double Value = 0.0;
	EXPECT_EQ(spCamera->GetCameraProperties(cv::VideoCaptureProperties::CAP_PROP_GAIN, Value), 0);
}