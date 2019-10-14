#include <stdio.h>
#include <iostream>
#include <pigpio.h>
#include <SG90.h>

int main()
{
	sg90ctl panServo(21);
	sg90ctl tiltServo(25);
	if (gpioInitialise() >= 0)
	{
		std::cout << "We have initialized pigpio" << std::endl;
		if(panServo.initialise()==0 && tiltServo.initialise() == 0)
			std::cout << "We have initialized servos" << std::endl;
		else return 0;
		for (int i = 1; i <= 100; i++)
		{
			if (i % 2)
			{
				panServo.moveToLocation(-89.0);
				tiltServo.moveToLocation(-40.0);
			}
			else
			{
				panServo.moveToLocation(17.0);
				tiltServo.moveToLocation(40.0);
			}
		}
	}
	
	return 0;
}