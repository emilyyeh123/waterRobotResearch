#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// include dji files
#include "batteryLevel.hpp"
#include "position.hpp"

// DJI OSDK includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
#include "dji_linux_helpers.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;


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

  outputBatteryLevel(vehicle);
  outputPosition(vehicle);
}
