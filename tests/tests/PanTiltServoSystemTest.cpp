#include <SG90.h>
#include <gtest/gtest.h>
#include <pigpio.h>

const int tiltGPIOidx = 12;
const int panGPIOidx = 13;
const double tiltMinDutyCycle = 0.035;
const double tiltMaxDutyCycle = 0.105;
const double panMinDutyCycle = 0.04;
const double panMaxDutyCycle = 0.11;
class PanTiltServoSystemTest : public ::testing::Test
{
protected:
	static void SetUpTestSuite()
	{
		_spTilt = std::make_unique<sg90ctl>(tiltGPIOidx, tiltMinDutyCycle, tiltMaxDutyCycle);
		_spPan = std::make_unique<sg90ctl>(panGPIOidx, panMinDutyCycle, panMaxDutyCycle);
	}

	virtual void SetUp()
	{
		ASSERT_EQ(nullptr != _spTilt, true);
		ASSERT_EQ(nullptr != _spPan, true);
	}
	static std::unique_ptr<sg90ctl> _spTilt;
	static std::unique_ptr<sg90ctl> _spPan;
};

std::unique_ptr<sg90ctl> PanTiltServoSystemTest::_spTilt = nullptr;
std::unique_ptr<sg90ctl> PanTiltServoSystemTest::_spPan = nullptr;

TEST_F(PanTiltServoSystemTest, TiltSweep)
{
	gpioInitialise();
	EXPECT_EQ(_spTilt->getGPIOIdx(), tiltGPIOidx);
	EXPECT_EQ(_spTilt->initialise(), 0);
	for (int angle = -89; angle < 90; angle++)
	{
		EXPECT_EQ(_spTilt->moveToLocation(angle), 0);
	}
	_spTilt->CleanUp();
	gpioTerminate();
}


TEST_F(PanTiltServoSystemTest, PanSweep)
{
	gpioInitialise();
	EXPECT_EQ(_spPan->getGPIOIdx(), panGPIOidx);
	EXPECT_EQ(_spPan->initialise(), 0);
	for (int angle = -89; angle < 90; angle++)
	{
		EXPECT_EQ(_spPan->moveToLocation(angle), 0);
	}
	_spPan->CleanUp();
	gpioTerminate();
}


