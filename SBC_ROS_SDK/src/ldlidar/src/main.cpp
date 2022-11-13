#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
//#include <wiringPi.h>
//#include <softPwm.h>
#include "cmd_interface_linux.h"
#include "lipkg.h"
#include "tofbf.h"
#include "signal.h"
#include "pid.h"
#include "unistd.h"

int main(int argc, char **argv)
{
	//int32_t pwm_out = 0;
	//PIDObjTyp LidarMotorPID(500, 50, 200, 0, 100, 0);
	//wiringPiSetup();
	//set pwm out frequency 24kHz
	//pinMode(LIDAR_PWM, PWM_OUTPUT);
	//pwmSetClock(8);
	//pwmSetMode(PWM_MODE_MS);
	//pwmSetRange(100);
	//pwmWrite(LIDAR_PWM, 70);

	lo_address osc_target;
	osc_target = lo_address_new("Pia.local", "6578");

	LiPkg * lidar = new LiPkg;

	CmdInterfaceLinux cmd_port;
	std::string port_name("/dev/ttyS0");
	cmd_port.SetReadCallback([&lidar, &osc_target](const char *byte, size_t len) {
		if (lidar->Parse((uint8_t*)byte, len))
		{
			lidar->AssemblePacket(osc_target);
		}
		});
	
	if(cmd_port.Open(port_name))
			std::cout<<"LiDAR_LD19 started successfully "  <<std::endl;
	
	while (true)
	{
		sleep(10);
	}
	return 0;
}
