#include "position.hpp"

#include <iostream>
#include <string>
using namespace std;

// DJI OSDK includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
#include <utility>
#include "dji_linux_helpers.hpp"
#include "flight_control_sample.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

double lat(){
  cout << "SETTING UP VEHICLE\n";

  // Initialize variables
  int functionTimeout = 1;
  char* linux_argv[] = {"prog_name"};

  // Setup OSDK.
  LinuxSetup linuxEnvironment(1, linux_argv);
  Vehicle*   vehicle = linuxEnvironment.getVehicle();
  if (vehicle == NULL)
  {
    cout << "Vehicle not initialized, exiting.\n";
    return -1;
  }
  // Obtain Control Authority
  vehicle->obtainCtrlAuthority(functionTimeout);

  cout << "\nRETRIEVING LATITUDE\n";
  DJI::OSDK::Telemetry::GlobalPosition currentBroadcastGP;
  currentBroadcastGP = vehicle -> broadcast -> getGlobalPosition();
  vehicle -> releaseCtrlAuthority(functionTimeout);

  cout << "Latitude is: " << currentBroadcastGP.latitude;
  return currentBroadcastGP.latitude;
}






