#ifndef POSITION
#define POSITION

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

double lat(Vehicle *vehicle);
double lon(Vehicle *vehicle);
int getHealth(Vehicle *vehicle);
void outputPosition(Vehicle *vehicle);

#endif
