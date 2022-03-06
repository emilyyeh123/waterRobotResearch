/*! @file missions/main.cpp
 *  @version 3.3
 *  @date Jun 05 2017
 *
 *  @brief
 *  main for GPS Missions API usage in a Linux environment.
 *  Shows example usage of the Waypoint Missions and Hotpoint Missions through
 *  the
 *  Mission Manager API.
 *
 *  @Copyright (c) 2017 DJI
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "flight_control_sample.hpp"
#include "gotowaypoint.hpp"
#include "winchControl.hpp"
#include <math.h>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <ratio>
#include <chrono>
#include <random>

#include <boost/python.hpp>

using namespace DJI::OSDK;
using namespace DJI::OSDK::Telemetry;

//Defs to make code Neater
#define REAL 5
#define HEIGHT_DEFAULT 3
// NickThePowerful "Peer" Review
//need to put info about params right here
// if we only have 4 parameters then we perform winch functions...
// 5 parameters seem to skip winch functions. which seems backwards. May have been a weird test implementation
// all calls to chrono and cout with std namespace are used as logging
//MAIN CONCEPT
// This code was made to be called every time we want to reach a point and perform whihch operations
// Curtis must have wanted to make this into an executable to be called from a higher function, Python Module?

// example call main.c target_lat target_lon height num_tests
// main.c -s target_lat target_lon height
// main.c -sh target_lat target_lon

int random_num(int min, int max){
	std::random_device r;
	std::default_random_engine goRun(r());
	std::uniform_int_distribution<int> dist(min,max);
	return dist(goRun);
}


// number of tests are unneeded when you are not using winch
double
fly2point(bool noWinch, int num_tests, int height, double target_lat, double target_lon)
{

  int    responseTimeout = 1; // used for runWaypointMission for time out increment values, need to determine units
  int functionTimeout = 1;
  char* linux_argv[] = {"prog_name"};


  // He wanted to log both the input degrees and conversion created
  //Radian conversion
  std::cout << "Target: " << target_lat << ", " << target_lon << std::endl;
  target_lat = target_lat / 180.0 * M_PI;
  target_lon = target_lon / 180.0 * M_PI;
  std::cout << "Target: " << target_lat << ", " << target_lon << std::endl;
  // Setup OSDK.
  LinuxSetup linuxEnvironment(1, linux_argv);
  Vehicle*   vehicle = linuxEnvironment.getVehicle();
  if (vehicle == NULL)
  {
    std::cout << "Vehicle not initialized, exiting.\n";
    return -1;

  }
  // Obtain Control Authority
  vehicle->obtainCtrlAuthority(functionTimeout);
 //add battery code
 //running the mission - NONBLOCKING CODE
  bool rc = runWaypointMission(vehicle, target_lat, target_lon, 20, height, responseTimeout); // bool is only used for error check
  if (!rc) {
    std::cout << "Couldn't start waypoint mission, exiting...\n";
    return -1;
  }
  //giving Mission function time to initialize
  sleep(5);
//Calc the difference in units between current position and target position based on target param values
//Keeps running the runWayPoint code until we reach the end
  Telemetry::GlobalPosition currentBroadcastGP;
  double deltaX, deltaY, deltaZ; // delta repersent the difference between our position and desired position
  // While mission is running we check if we reached our target position
  do {
      currentBroadcastGP = vehicle->broadcast->getGlobalPosition();
      deltaY = abs((target_lon - currentBroadcastGP.longitude) * C_EARTH);
      deltaX = abs((target_lat - currentBroadcastGP.latitude) * C_EARTH * cos(target_lat));
      deltaZ = abs(height - currentBroadcastGP.height);
      std::cout << deltaX << ", " << deltaY << ", " << deltaZ << std::endl;
      sleep(1);
  } while (deltaX > 2 || deltaY > 2 || deltaZ > 3);

  std::cout << "Target reached." << std::endl;
//Once we reach waypoint you terminate
//Just go determines whether or not we perform winch shit? So returning a 0, is the default for no value
  if (noWinch) {
    return random_num(0,100);
  }
// If we are not suppose to "Just Go" We run the whinch code

//;)
//START WINCH SHIT
// Time setting up, chrono by default uses auto typing
// Datatype below is std::chrono::time_point<std::chrono::high_resolution_clock>
  auto test_start_t = std::chrono::high_resolution_clock::now();
  auto winch_down_start_t = test_start_t;
  auto winch_down_end_t = test_start_t;
  auto lowering_start_t = test_start_t;
  auto lowering_end_t = test_start_t;
  auto sensing_start_t = test_start_t;
  auto sensing_end_t = test_start_t;
  auto winch_up_start_t = test_start_t;
  auto winch_up_end_t = test_start_t;
  auto test_end_t = test_start_t;

  sleep(1);
  int lidar = getLidarDist();

  std::cout << "Lidar: " << lidar << std::endl;
  if (lidar > 1500) {
    moveByPositionOffset(vehicle, 0, 0, -5, 0);
  } else if (lidar > 800) {
    moveByPositionOffset(vehicle, 0, 0, -3, 0);
  }

  char filename[100];
  time_t rawtime = time(NULL);
  strftime(filename, 100, "sensor-%j-%H-%M-%S.txt", gmtime(&rawtime));
  std::ofstream datafile(filename);

  //datafile << "gps: (" << argv[1] << ", " << argv[2] << ")" << std::endl;

  winch_down_start_t = std::chrono::high_resolution_clock::now();
  winchDown();
  std::cout << "Shit is Going down" << std::flush;
  while (getWinchStatus() != '0') {
    sleep(1);
    std::cout << "." << std::flush;
  }
  winch_down_end_t = std::chrono::high_resolution_clock::now();

  int result = 0;

  lowering_start_t = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < num_tests; i++) {
    std::cout << "Test: " << i << std::endl;
    datafile << "Test: " << i << std::endl;
    // this code lowkey sucks
    for (int j = 0; j < 25; j++) {
      std::cout << "Sensor: ";
      char x = (char)getSensor();
      std::cout << x << std::endl;
      if (x != '0') {
        lowering_end_t = std::chrono::high_resolution_clock::now();
        sensing_start_t = std::chrono::high_resolution_clock::now();
        //Trying to eliminate noise with sensors  i guess fuck wtf  - ;)
	for (int k = 0; k < 25; k++) {
            int val = getSensorVal();
            x = getSensor();

            if (x == '1') {
              datafile << "water (" << val << ")" << std::endl;
              result = 1;
            } else if (x == '2') {
              datafile << "land (" << val << ")" << std::endl;
              if (result != 1) {
                result = 2;
              }
            }
        }
        sensing_end_t = std::chrono::high_resolution_clock::now();
        break;
      }
      moveByPositionOffset(vehicle, 0, 0, -1, 0);
    }
    moveByPositionOffset(vehicle, 0, 0, 5, 0);

    sleep(1);
  }

  winch_up_start_t = std::chrono::high_resolution_clock::now();
  winchUp();
  std::cout << "Going up" << std::flush;
  while (getWinchStatus() != '0') {
    sleep(1);
    std::cout << "." << std::flush;
  }
  winch_up_end_t = std::chrono::high_resolution_clock::now();
  test_end_t = std::chrono::high_resolution_clock::now();

  /* Total, Winch Down, Lowering UAV, Sensing, Winch Up */
  std::cout << std::endl << std::chrono::duration_cast<std::chrono::milliseconds>(test_end_t - test_start_t).count() << "ms, "
    << std::chrono::duration_cast<std::chrono::milliseconds>(winch_down_end_t - winch_down_start_t).count() << "ms, "
    << std::chrono::duration_cast<std::chrono::milliseconds>(lowering_end_t - lowering_start_t).count() << "ms, "
    << std::chrono::duration_cast<std::chrono::microseconds>(sensing_end_t - sensing_start_t).count() << "us, "
    << std::chrono::duration_cast<std::chrono::milliseconds>(winch_up_end_t - winch_up_start_t).count() << "ms, "
    << std::endl;

  datafile << std::chrono::duration_cast<std::chrono::milliseconds>(test_end_t - test_start_t).count() << "ms, "
    << std::chrono::duration_cast<std::chrono::milliseconds>(winch_down_end_t - winch_down_start_t).count() << "ms, "
    << std::chrono::duration_cast<std::chrono::milliseconds>(lowering_end_t - lowering_start_t).count() << "ms, "
    << std::chrono::duration_cast<std::chrono::microseconds>(sensing_end_t - sensing_start_t).count() << "us, "
    << std::chrono::duration_cast<std::chrono::milliseconds>(winch_up_end_t - winch_up_start_t).count() << "ms, "
    << std::endl;

  datafile.close();

  std::cout << "Result: " << result << std::endl;
 // END SENSOR LOGIC
  return result; //----why would you care about returing the result in a int main function? Kinda weird
}

BOOST_PYTHON_MODULE(fly2point)
{
   using namespace boost::python;

   def("fly2point", fly2point);
}
