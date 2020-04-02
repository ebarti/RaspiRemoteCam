// I will use this file to define any test fixtures that I might aid myself with.
// Starting with a camera test fixture

#include <FaceTrackingCamera.h>
#include <gtest/gtest.h>
#include <string>

class CameraTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		pCamera(new FaceTrackingCamera(CascadePath, NestedCascadePath));
		ASSERT_EQ(!!spCamera, true) << "CRITICAL ERROR: Ran out of available memory" << endl;
	}

	void TearDown() override
	{
		// Nothing to do
	}
	const std::string CascadePath = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml";
	const std::string NestedCascadePath = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml";
	std::shared_ptr<FaceTrackingCamera> spCamera;
};