#include "position.hpp"

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
  myfile.open("outputFiles/positionOutput.txt");
  double latitude = lat(vehicle);
  double longitude = lon(vehicle);
  myfile << "Latitude is: " << latitude << endl << "Longitude is: " << longitude << endl;
  myfile.close();
  cout << "Position coordinates printed in outputFiles/positionOutput.txt\n";
}



