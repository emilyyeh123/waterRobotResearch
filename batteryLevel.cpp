// test battery reading

#include "batteryLevel.hpp"

int batteryLevel(Vehicle *vehicle){
  DJI::OSDK::Telemetry::Battery data;

  data = vehicle->broadcast->getBatteryInfo();
  cout << "BATTERY PERCENTAGE: " << static_cast<int>(data.percentage) << "% \n";
  return static_cast<int>(data.percentage);
}

void outputBatteryLevel(Vehicle* vehicle){
  ofstream myfile;
  myfile.open("outputFiles/batteryOutput.txt");
  int battLev = batteryLevel(vehicle);
  myfile << "Battery Percentage: " << battLev << endl;
  myfile.close();
  cout << "Battery Level sent to outputFiles/batteryOutput.txt" << endl;
}
