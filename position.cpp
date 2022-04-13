#include "position.hpp"
/*
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
*/
double lat(Vehicle *vehicle){
  cout << "\nRETRIEVING LATITUDE\n";
  DJI::OSDK::Telemetry::GlobalPosition currentBroadcastGP;
  currentBroadcastGP = vehicle -> broadcast -> getGlobalPosition();

  cout << "Latitude is: " << currentBroadcastGP.latitude << endl;
  return currentBroadcastGP.latitude;
}

double lon(Vehicle *vehicle){
  cout << "\nRETRIEVING LONGITUDE\n";
  DJI::OSDK::Telemetry::GlobalPosition currentBroadcastGP;
  currentBroadcastGP = vehicle -> broadcast -> getGlobalPosition();

  cout << "Longitude is: " << currentBroadcastGP.longitude << endl;
  return currentBroadcastGP.longitude;
}

int getHealth(Vehicle *vehicle){
  cout << "\nRETRIEVING SIGNAL STRENGTH\n";
  DJI::OSDK::Telemetry::GlobalPosition healthSignal;

  cout << "Signal Strength (scale from 0-5, >3 is strong): " << int(healthSignal.health) << endl;
  return int(healthSignal.health);
}

void outputPosition(Vehicle *vehicle){
  ofstream myfile;
  myfile.open("outputPosition.txt");
  double latitude = lat(vehicle);
  double longitude = lon(vehicle);
  myfile << "Latitude is: " << latitude << endl << "Longitude is: " << longitude << endl;
  myfile.close();
}



