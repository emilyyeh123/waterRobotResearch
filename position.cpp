#include "position.hpp"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// DJI OSDK includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
#include <utility>
#include "dji_linux_helpers.hpp"
#include "flight_control_sample.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

// function to set current position
/*void setPosition(){
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

  // bool moveByPositionOffset
  //   (vehicle, xOffsetDesired, yOffsetDesired, zOffsetDesired
  //    yawDesired, posThresholdInM, yawThresholdInDeg)
  //moveByPositionOffset(vehicle, 0, 6, 6, 30);
}*/

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

  cout << "Latitude is: " << currentBroadcastGP.latitude << endl;
  return currentBroadcastGP.latitude;
}

double lon(){
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

  cout << "\nRETRIEVING LONGITUDE\n";
  DJI::OSDK::Telemetry::GlobalPosition currentBroadcastGP;
  currentBroadcastGP = vehicle -> broadcast -> getGlobalPosition();

  cout << "Longitude is: " << currentBroadcastGP.longitude << endl;
  return currentBroadcastGP.latitude;
}

void outputPosition(){
  ofstream myfile;
  myfile.open("positionCoord.txt");
  double latitude = lat();
  double longitude = lon();
  myfile << "Latitude is: " << lat() << endl << "Longitude is: " << lon() << endl;
  myfile.close();
}



