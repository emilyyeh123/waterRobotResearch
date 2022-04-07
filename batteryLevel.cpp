// test battery reading

#include "batteryLevel.hpp"

#include <iostream>
#include <string>
using namespace std;

// DJI OSDK includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
#include "dji_linux_helpers.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

int batteryLevel(Vehicle *vehicle){
/*
int batteryLevel(){
  cout << "INITIALIZING VEHICLE\n";

  // initialize variables
  int functionTimeout = 1;
  char* linux_argv[] = {"prog_name"};

  // Setup OSDK
  LinuxSetup linuxEnvironment(1, linux_argv);
  Vehicle* vehicle = linuxEnvironment.getVehicle();
  if (vehicle == NULL){
    cout << "VEHICLE NOT INITIALIZED, EXITING.\n";
    return -1;
  }
  // Obtain Control Authority
  vehicle -> obtainCtrlAuthority(functionTimeout);
*/

  DJI::OSDK::Telemetry::Battery data;
  //cout << "vehicle address " << &vehicle << endl;

  //giving Mission function time to initialize
  data = vehicle->broadcast->getBatteryInfo();
  cout << "BATTERY PERCENTAGE: " << static_cast<int>(data.percentage) << "% \n";
  //vehicle->releaseCtrlAuthority(functionTimeout);
  return static_cast<int>(data.percentage);
}
