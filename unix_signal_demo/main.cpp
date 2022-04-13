
#include <stdio.h>
#include <signal.h> 
#include <unistd.h> 
#include <iostream>
#include <string>
#include <fstream>

// include signalling files
#include "send_unix_signal.hpp"
#include "receive_unix_signal.hpp"

// include dji osdk stuff
#include "../batteryLevel.hpp"
#include "../position.hpp"

#include <dji_status.hpp>
#include <dji_vehicle.hpp>
#include "../dji_linux_helpers.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

using namespace std;

uint8_t sig_num = 0;

int main() 
{
	// initialize vehicle
	cout << "INITIALIZING VEHICLE\n";
	// initialize variables
	int functionTimeout = 1;
	char* linux_argv[] = {"prog_name"};
	// setup OSDK
	LinuxSetup linuxEnvironment(1, linux_argv);
	Vehicle* vehicle = linuxEnvironment.getVehicle();
	if (vehicle == NULL){cout << "VEHICLE NOT INITIALIZED, EXITING.\n";}
	// Obtain Control Authority
	vehicle -> obtainCtrlAuthority(functionTimeout);

	signal(34, signalHandler);
	signal(35, signalHandler);
	pid_t pid; 
	writePID();

	while(true) 
	{ 
		if(sig_num == 34) 
		{
			cout << "Signal Received: " << (int)sig_num << endl; 
			sig_num = 0;
			/* Battery Check */ 
		}	
		else if(sig_num == 35) 
		{
			cout << "Signal Received: " << (int)sig_num << endl;
			sig_num = 0;
			outputPosition(vehicle); 
		}
		sleep(1);
	};

	return 0;
}
