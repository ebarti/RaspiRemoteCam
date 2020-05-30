#include "SG90Controller.h"
#include <gtest/gtest.h>

class SG90ControllerTest : public ::testing::Test
{
protected:
	static void SetUpTestSuite()
	{

		_spController = std::make_shared<SG90Controller>();
	}

	virtual void SetUp()
	{
		ASSERT_EQ(nullptr != _spController, true);
	}
	static std::shared_ptr<SG90Controller> _spController;
};

std::shared_ptr<SG90Controller>SG90ControllerTest::_spController = nullptr;

TEST_F(SG90ControllerTest, Initialize)
{
	//NoP
}