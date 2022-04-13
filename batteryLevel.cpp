// test battery reading

#include "batteryLevel.hpp"
/*
#include <iostream>
#include <string>
using namespace std;

// DJI OSDK includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
#include "dji_linux_helpers.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;
*/
int batteryLevel(Vehicle *vehicle){
  DJI::OSDK::Telemetry::Battery data;

  data = vehicle->broadcast->getBatteryInfo();
  cout << "BATTERY PERCENTAGE: " << static_cast<int>(data.percentage) << "% \n";
  return static_cast<int>(data.percentage);
}
