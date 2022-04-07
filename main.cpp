#include "batteryLevel.hpp"
#include "position.hpp"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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
  }
  // Obtain Control Authority
  vehicle -> obtainCtrlAuthority(functionTimeout);

  batteryLevel(vehicle);

  //batteryLevel();

  //lat(vehicle);
  //lon();
  outputPosition(vehicle);
  //getHealth();
}
