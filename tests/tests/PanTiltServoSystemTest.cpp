#include <SG90.h>
#include <gtest/gtest.h>
#include <stdlib.h>
#include <pigpio.h>

const int tiltGPIOidx = 12;
const int panGPIOidx = 13;

class PanTiltServoSystemTest : public ::testing::Test
{
protected:
	static void SetUpTestSuite()
	{
		_spTilt = std::make_unique<sg90ctl>(tiltGPIOidx);
		_spPan = std::make_unique<sg90ctl>(panGPIOidx);
	}

	virtual void SetUp()
	{
		ASSERT_EQ(nullptr != _spTilt, true);
		ASSERT_EQ(nullptr != _spPan, true);
	}
	
	//static FaceTrackingCamera * _tstCamera;
	static std::unique_ptr<sg90ctl> _spTilt;
	static std::unique_ptr<sg90ctl> _spPan;
};

std::unique_ptr<sg90ctl>PanTiltServoSystemTest::_spTilt = nullptr;
std::unique_ptr<sg90ctl>PanTiltServoSystemTest::_spPan = nullptr;

TEST_F(PanTiltServoSystemTest, Initialize)
{
	gpioInitialise();
	EXPECT_EQ(_spTilt->getGPIOIdx(), tiltGPIOidx);
	EXPECT_EQ(_spTilt->initialise(), 0);
	EXPECT_EQ(_spPan->getGPIOIdx(), panGPIOidx);
	EXPECT_EQ(_spPan->initialise(), 0);
}

TEST_F(PanTiltServoSystemTest, AngleSweep)
{
	for (int angle = -89; angle < 90; angle++)
	{
		EXPECT_EQ(_spTilt->moveToLocation(angle), 0);
		EXPECT_EQ(_spPan->moveToLocation(angle), 0);
	}
	_spTilt->CleanUp();
	_spPan->CleanUp();
	gpioTerminate();
}


