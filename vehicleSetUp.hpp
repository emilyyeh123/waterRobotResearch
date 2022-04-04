#ifndef VEHICLESETUP_HPP
#define VEHICLESETUP_HPP

#include "batteryLevel.hpp"

#include <iostream>
#include <string>

// DJI OSDK includes
#include <dji_status.hpp>
#include <dji_vehicle.hpp>
#include "dji_linux_helpers.hpp"
using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

Vehicle* initVehicle();

#endif
