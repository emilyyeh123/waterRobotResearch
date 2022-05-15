#******************************************************
 # Robotics Interface code
 # 
 # Connects the raspberry pi to a microcontroller via
 # the serial port.  Defines a set of functions for
 # controlling the robot movement, measuring sensors,
 # and configuring parameters
 #
 # Author: Elizabeth Basha
 # Date: Fall 2018
 #*****************************************************
#! /usr/bin/env python

import math
import robotControl
import serial
import time

print("Starting")

# Open Serial Port
ser = serial.Serial("/dev/serial0",115200)

# ------------------------------------------------------------
# MOVEMENT FUNCTIONS

# Move robot to X,Y where X is positive
#robotControl.moveRobotXY(ser,10,0)

# Move robot until obstacle seen
#robotControl.moveRobotObs(ser)

# Rotate robot by angleToTurn (0 to 2pi)
#result = robotControl.rotateRobot(ser,math.pi)

# Move robot backward by X
#result = robotControl.moveRobotBackX(ser, 12)

# Read result
# Returns named tuple in the order (obsFlag, v, w, time)
#result, msgType = robotControl.readResponse(ser)
#time.sleep(.5)
#print(result.obsFlag, result.rightWheelDist, result.leftWheelDist, result.time)

# ------------------------------------------------------------
# Change PWM values and see movement impact
time.sleep(2)
robotControl.changePWMvalues(ser, 50, 50)

robotControl.moveRobotXY(ser,10,0)
result, msgType = robotControl.readResponse(ser)
time.sleep(.5)
print(result.obsFlag, result.rightWheelDist, result.leftWheelDist, result.time)

time.sleep(2)
robotControl.changePWMvalues(ser, 150, 150)
robotControl.moveRobotXY(ser,10,0)
result, msgType = robotControl.readResponse(ser)
time.sleep(.5)
print(result.obsFlag, result.rightWheelDist, result.leftWheelDist, result.time)

# ------------------------------------------------------------
# SENSOR FUNCTIONS
# Send and read one ir command so that msgType has a value
#robotControl.getSensors(ser)
#result, msgType = robotControl.readResponse(ser)
#time.sleep(.5)
#print(result)
  
# Close Serial Port
ser.close()

print("Done")
