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

class RealCameraTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		std::unique_ptr<FaceTrackingCamera> newCamera(new FaceTrackingCamera(CascadePath, NestedCascadePath, 1.0));
		spCamera = std::move(newCamera);
		ASSERT_EQ(nullptr != spCamera, true) << "CRITICAL ERROR: Ran out of available memory" << std::endl;
	}

	const std::string CascadePath = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml";
	const std::string NestedCascadePath = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml";
	std::unique_ptr<FaceTrackingCamera> spCamera;
};


TEST_F(CameraTest, SimulatedCamera)
{
	EXPECT_EQ(spCamera->Initialize(), 0);
	cv::Mat RetrievedImage;
	cv::Point pointLocation;
	EXPECT_EQ(spCamera->GetImageAndTarget(RetrievedImage, pointLocation), 0);
	// Test now the output image
	EXPECT_EQ(!RetrievedImage.data, false);

}

TEST_F(RealCameraTest, RealCamera)
{
	EXPECT_EQ(spCamera->Initialize(), 0);
}

