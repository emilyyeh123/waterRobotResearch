#ifndef BATTERYLEVEL_HPP
#define BATTERYLEVEL_HPP

#include <iostream>
#include <string>
using namespace std;

// DJI OSDK includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
#include "dji_linux_helpers.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

int batteryLevel(Vehicle *vehicle);

#endif
