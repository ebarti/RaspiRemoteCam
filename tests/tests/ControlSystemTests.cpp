#include "ControlSystem.h"
#include <gtest/gtest.h>
#include <stdlib.h>

class ControlSystemTest : public ::testing::Test
{
protected:
	static void SetUpTestSuite()
	{

		_spController = std::make_shared<ControlSystem>();
	}

	virtual void SetUp()
	{
		ASSERT_EQ(nullptr != _spController, true);
	}
	static std::shared_ptr<ControlSystem> _spController;
};

std::shared_ptr<ControlSystem>ControlSystemTest::_spController = nullptr;

TEST_F(ControlSystemTest, Initialize)
{
	//NoP
}