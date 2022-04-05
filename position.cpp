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
  //DJI::OSDK::Telemetry::PositionData currentPos;
  //currentPos = vehicle -> broadcast -> getRelativePosition();

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
  return currentBroadcastGP.longitude;
}

int getHealth(){
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

  cout << "\nRETRIEVING SIGNAL STRENGTH\n";
  DJI::OSDK::Telemetry::GlobalPosition healthSignal;
  //healthSignal = vehicle -> broadcast -> getGlobalPosition();

  cout << "Signal Strength (scale from 0-5, >3 is strong): " << int(healthSignal.health) << endl;
  return int(healthSignal.health);
}

void outputPosition(){
  ofstream myfile;
  myfile.open("outputPosition.txt");
  double latitude = lat();
  double longitude = lon();
  myfile << "Latitude is: " << latitude << endl << "Longitude is: " << longitude << endl;
  myfile.close();
}



