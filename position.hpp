#ifndef POSITION
#define POSITION

#include<dji_vehicle.hpp>

double lat(Vehicle *vehicle);
double lon(Vehicle *vehicle);
int getHealth(Vehicle *vehicle);
void outputPosition(Vehicle *vehicle);

#endif
