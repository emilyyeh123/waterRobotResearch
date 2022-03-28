// test battery reading

#include "batteryLevel.hpp"

#include <iostream>
#include <string>
#include <sstream>

// DJI OSDK includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
// Helpers
#include "dji_linux_helpers.hpp"

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;
using std::string;

int batteryLevel()
{
  std::cout << "Print Statement";
  DJI::OSDK::Telemetry::Battery data;

  // Initialize variables
  int functionTimeout = 1;
  char* linux_argv[] = {"prog_name"};

  // Setup OSDK.
  LinuxSetup linuxEnvironment(1, linux_argv);
  Vehicle*   vehicle = linuxEnvironment.getVehicle();
  if (vehicle == NULL)
  {
    std::cout << "Vehicle not initialized, exiting.\n";
    return -1;
  }
  // Obtain Control Authority
  vehicle->obtainCtrlAuthority(functionTimeout);

  //giving Mission function time to initialize
  data = vehicle->broadcast->getBatteryInfo();
  std::cout << "battery percentage: " << static_cast<int>(data.percentage) << "% \n";
  vehicle->releaseCtrlAuthority(functionTimeout);
  return static_cast<int>(data.percentage);
}

