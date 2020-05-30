#include <FaceTrackingCamera.h>
#include <gtest/gtest.h>
#include <opencv2/core/utils/logger.hpp>

class CameraTest : public ::testing::Test
{
protected:
	static void SetUpTestSuite()
	{
		cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_VERBOSE);
		setenv("OPENCV_SAMPLES_DATA_PATH", "/home/pi/opencv", 1);
		std::string cascadeFrontalfilename = cv::samples::findFile("data/lbpcascades/lbpcascade_frontalface.xml");
		_spCamera = std::make_shared<FaceTrackingCamera>(cascadeFrontalfilename, cascadeFrontalfilename, true);
	}
	
	virtual void SetUp()
	{
		ASSERT_EQ(nullptr != _spCamera, true);
	}
	//static FaceTrackingCamera * _tstCamera;
	static std::shared_ptr<FaceTrackingCamera> _spCamera;
};

std::shared_ptr<FaceTrackingCamera>CameraTest::_spCamera = nullptr;

TEST_F(CameraTest, Initialize)
{
	EXPECT_EQ(_spCamera->Initialize(), 0);
}


TEST_F(CameraTest, GetCameraProperty)
{
	double dblValue = 0.0;
	EXPECT_EQ(_spCamera->GetCameraProperties(cv::VideoCaptureProperties::CAP_PROP_BRIGHTNESS, dblValue), 0);
	EXPECT_EQ((0.0 != dblValue), true);
}

TEST_F(CameraTest, GetImageAndTarget)
{
	cv::Mat RetrievedImage;
	cv::Ptr<cv::Point2f> pointLocation;
	EXPECT_EQ(_spCamera->Process(RetrievedImage, pointLocation), 1);
	// Test now the output image
	EXPECT_EQ(!RetrievedImage.data, false);
}
