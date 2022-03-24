// this code was made just to test the battery reading

#include "batteryLevel.hpp"

#include <math.h>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <ratio>
#include <chrono>

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

/*
int batteryLevel(CppVehicle& cv)
{
   DJI::OSDK::Telemetry::Battery data;
   int functionTimeout = 1;

   cv.my_vehicle->obtainCtrlAuthority(functionTimeout);

   data = cv.my_vehicle->broadcast->getBatteryInfo();
   std::cout << "battery percentage: " << static_cast<int>(data.percentage) << "% \n";
   cv.my_vehicle->releaseCtrlAuthority(functionTimeout);
   return static_cast<int>(data.percentage);
}
*/
