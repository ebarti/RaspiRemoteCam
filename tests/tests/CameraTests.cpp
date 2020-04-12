#include <FaceTrackingCamera.h>
#include <gtest/gtest.h>
#include <stdlib.h>
#include <opencv2/core/utils/logger.hpp>
using namespace cv;

class CameraTest : public ::testing::Test
{
protected:
	static void SetUpTestSuite()
	{
		cv::utils::logging::setLogLevel(utils::logging::LOG_LEVEL_VERBOSE);
		setenv("OPENCV_SAMPLES_DATA_PATH", "/home/pi/opencv", 1);
		std::string cascadeFrontalfilename = samples::findFile("data/lbpcascades/lbpcascade_frontalface.xml");
		_tstCamera = new FaceTrackingCamera(cascadeFrontalfilename, cascadeFrontalfilename, true);
	}
	
	static void TearDownTestSuite()
	{
		delete _tstCamera;
		_tstCamera = NULL;
	}

	virtual void SetUp()
	{
		ASSERT_EQ(NULL != _tstCamera, true);
	}
	static FaceTrackingCamera * _tstCamera;
};

FaceTrackingCamera * CameraTest::_tstCamera = NULL;

TEST_F(CameraTest, Initialize)
{
	EXPECT_EQ(_tstCamera->Initialize(), 0);
}


TEST_F(CameraTest, GetCameraProperty)
{
	double dblValue = 0.0;
	EXPECT_EQ(_tstCamera->GetCameraProperties(cv::VideoCaptureProperties::CAP_PROP_BRIGHTNESS, dblValue), 0);
	EXPECT_EQ((0.0 != dblValue), true);
}

TEST_F(CameraTest, GetImageAndTarget)
{
	cv::Mat RetrievedImage;
	cv::Point pointLocation;
	EXPECT_EQ(_tstCamera->GetImageAndTarget(RetrievedImage, pointLocation), 0);
	// Test now the output image
	EXPECT_EQ(!RetrievedImage.data, false);
}
