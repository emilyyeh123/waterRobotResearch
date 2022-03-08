#include "batteryLevel.hpp"

// DJI OSDK Includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
// Helpers
#include "dji_osdk/dji_linux_helpers.hpp"

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;
using namespace std;
using std::string;

#include <iostream>
#include <string>
#include <sstream>

int batteryLevel(){
  DJI::OSDK::Telemetry::Battery data;

  // initialize variables
  int functionTimeout = 1;
  char* linux_argv[] = {"prog_name"};

  // Setup OSDK
  LinuxSetup linuxEnvironment(1, linux_argv);
  Vehicle* vehicle = linuxEnvironment.getVehicle();
  if (vehicle == NULL){
    cout << "Vehicle not initialized, exiting.\n";
    return -1;
  }
  // Obtain Control Authority
  vehicle -> obtainCtrlAuthority(functionTimeout);

  // giving Mission function time to initialize
  data = vehicle -> broadcast -> getBatteryInfo();
  cout << "battery percentage: " << static_cast<int>(data.percentage) << "% \n";
  vehicle -> releaseCtrlAuthority(functionTimeout);
  return static_cast <int> (data.percentage);
}
