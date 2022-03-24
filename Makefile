# File: Makefile
# Created: 2019-06-09
# Author:  Sean Thalken
# Editors:
#
# This is a special makefile that I made to build all of our python modules
# with a single make command. Each module gets compiled into a .so file.
# Place new modules in TARGETS as necessary, and make will build them.
#

# Compiler
CC=g++

# Compiler options
CFLAGS=-c -std=c++11 -O2 -fpic

# Everywhere else
INCLUDES=-I/usr/local/include/djiosdk/
LINKS=-ldjiosdk-core -lpthread

# For Davis's computer
#INCLUDES=-I/usr/include/python3.6m/ -I/usr/local/include/djiosdk/
#LINKS=-ldjiosdk-core -lpthread -lpython3.6m -lboost_python3

# Uncomment to add debugging symbols
#DEBUG=-g

# All of the .hpp header files to use as dependencies
#HEADERS=dji_osdk/dji_vehicle.hpp dji_osdk/dji_linux_environment.hpp dji_osdk/dji_linux_helpers.hpp dji_osdk/dji_status.hpp winchControl.hpp flight_control_sample.hpp gotowaypoint.hpp
#HEADERS=winchControl.hpp flight_control_sample.hpp gotowaypoint.hpp
#HEADERS=cClasses.hpp winchControl.hpp flight_control_sample.hpp gotowaypoint.hpp dji_linux_environment.hpp dji_linux_helpers.hpp
#HEADERS=winchControl.hpp flight_control_sample.hpp gotowaypoint.hpp dji_linux_environment.hpp dji_linux_helpers.hpp
#HEADERS=cClasses.hpp dji_linux_environment.hpp dji_linux_helpers.hpp testXY.hpp

# All of the object files to produce as intermediary work
#OBJECTS=fly2point.o batteryLevel.o dji_osdk/dji_vehicle.o dji_osdk/dji_linux_environment.o dji_osdk/dji_linux_helpers.o dji_osdk/dji_status.o winchControl.o flight_control_sample.o gotowaypoint.o
#OBJECTS=batteryLevel.o dji_osdk/dji_vehicle.o dji_osdk/dji_linux_environment.o dji_osdk/dji_linux_helpers.o winchControl.o flight_control_sample.o gotowaypoint.o
#OBJECTS=batteryLevel.o winchControl.o flight_control_sample.o gotowaypoint.o
#OBJECTS=batteryLevel.o winchControl.o flight_control_sample.o gotowaypoint.o dji_linux_environment.o dji_linux_helpers.o
#OBJECTS=cClasses.o testXY.o batteryLevel.o winchControl.o flight_control_sample.o gotowaypoint.o dji_linux_environment.o dji_linux_helpers.o
#OBJECTS=testXY.o batteryLevel.o winchControl.o flight_control_sample.o gotowaypoint.o dji_linux_environment.o dji_linux_helpers.o
#OBJECTS=cClasses.o dji_linux_environment.o dji_linux_helpers.o testXY.o
#OBJECTS=dji_linux_environment.o dji_linux_helpers.o testXY.o

#OBJECTS=args.o CppVehicle.o dji_linux_environment.o dji_linux_helpers.o flight_control_sample.o batteryLevel.o fly2point.o winchControl.o gotowaypoint.o testXY.o waypointMission.o squareWaypoint.o
#OBJECTS=dji_linux_environment.o dji_linux_helpers.o flight_control_sample.o batteryLevel.o fly2point.o winchControl.o gotowaypoint.o testXY.o waypointMission.o squareWaypoint.o absoluteFlight.o

OBJECTS = dji_linux_environment.o dji_linux_helpers.o batteryLevel.o

# Put shared objects here. These are the files that get imported by python.
#TARGETS=fly2point.so batteryLevel.so
#TARGETS=testXY.so
#TARGETS=testXY.so batteryLevel.so waypointMission.so squareWaypoint.so CppVehicle.so
#TARGETS=testXY.so batteryLevel.so waypointMission.so squareWaypoint.so absoluteFlight.so
TARGETS = battLev

# --------------------------------------------

all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CC) -shared -Wl,-soname,$@ $(OBJECTS) -o $@ $(LINKS)

#%.o: %.cpp $(HEADERS)
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) $(DEBUG) -o $@ $<

clean:
	rm $(TARGETS) $(OBJECTS)
