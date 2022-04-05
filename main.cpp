//#include "vehicleSetUp.hpp"
//#include "batteryLevel.hpp"
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
  //Vehicle* vehicle = initVehicle();

  //batteryLevel(vehicle);
  //batteryLevel();

  //lat();
  //lon();
  //outputPosition();
  getHealth();
}
