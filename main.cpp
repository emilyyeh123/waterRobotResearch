#include <stdio.h>
#include <signal.h> 
#include <unistd.h> 
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// include unix signalling files
#include "send_unix_signal.hpp"
#include "receive_unix_signal.hpp"

// include dji files
#include "batteryLevel.hpp"
#include "position.hpp"

// DJI OSDK includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
#include "dji_linux_helpers.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;


uint8_t sig_num = 0;


int main(){
  cout << "INITIALIZING VEHICLE\n";

  // initialize variables
  int functionTimeout = 1;
  char* linux_argv[] = {"prog_name"};

  // Setup OSDK
  LinuxSetup linuxEnvironment(1, linux_argv);
  Vehicle* vehicle = linuxEnvironment.getVehicle();
  if (vehicle == NULL){
    cout << "VEHICLE NOT INITIALIZED, EXITING.\n";
    return 0;
  }
  // Obtain Control Authority
  vehicle -> obtainCtrlAuthority(functionTimeout);

  signal(34, signalHandler);
  signal(35, signalHandler);
  pid_t pid; 
  writePID();

  while(true){
    if(sig_num == 34){
      // GET BATTERY LEVEL
      cout << "Signal Received: " << (int)sig_num << endl;
      sig_num = 0;
      outputBatteryLevel(vehicle);
    } else if (sig_num == 35) {
      // GET POSITION
      cout << "Signal Received: " << (int)sig_num << endl;
      sig_num = 0;
      outputPosition(vehicle);
    }
    sleep(1);
  }

  return 0;
}
