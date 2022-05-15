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

import serial
import string
import struct
import collections
import math

# Command Defines
# Don't use zero! No worky worky
MOVEOBS_ROBOT_COMMAND = 1
MOVEBACK_ROBOT_COMMAND = 2
SENSE_ROBOT_COMMAND = 3
CHANGE_SENSE_THRESHOLD_COMMAND = 4
ROTATE_ROBOT_COMMAND = 5
CHANGE_PWMS_COMMAND = 6
MOVEXY_ROBOT_COMMAND = 7

# Robot Defines
WHEEL_RADIUS = 3 # cm
WHEEL_L = 8 # cm, distance between wheels
TICKS_PER_REV = 128  # number of ticks per 1 revolution of the wheel, both channels of encoder

# Create named tuples for returning values
sensors = collections.namedtuple('Sensors', ['left', 'middle', 'right'])
moved = collections.namedtuple('Movement', ['obsFlag', 'v', 'w', 'time'])
ticks = collections.namedtuple('TicksnTime', ['rightWheelTicks', 'leftWheelTicks', 'time'])
allInfo = collections.namedtuple('AllData', ['distance', 'angle', 'time', 'left', 'middle', 'right'])

#**************************************************************************
# Send Functions
#**************************************************************************

# Move robot to X,Y where X is positive
def moveRobotXY(serialPort, x, y):
    # Write the command to the microcontroller
    serialPort.write(struct.pack('>BBBBB',MOVEXY_ROBOT_COMMAND,(x&0xff),(x>>8)&0xff,(y&0xff),(y>>8)&0xff))

# Move robot until obstacle seen
# Returns a named tuple in the order (distance, angle, time, left, middle, right)
def moveRobotObs(serialPort):
    # Write the command to the microcontroller
    serialPort.write(struct.pack('>B',MOVEOBS_ROBOT_COMMAND))


# Rotate robot by angleToTurn (0 to 2pi)
# Returns a named tuple in the order (distance, angle, time)
def rotateRobot(serialPort,angleToTurn):
    angleToTurnInDegrees = int(angleToTurn*(180/math.pi))

    # Write the command to the microcontroller
    serialPort.write(struct.pack('>BBB',ROTATE_ROBOT_COMMAND,(angleToTurnInDegrees&0xff),(angleToTurnInDegrees>>8)&0xff))


# Move robot backward by X
# Returns a named tuple in the order (distance, angle, time)
def moveRobotBackX(serialPort, x):
    # Write the command to the microcontroller
    serialPort.write(struct.pack('>BBB',MOVEBACK_ROBOT_COMMAND,(x&0xff),(x>>8)&0xff))


# Reads the IR sensors
# Returns a named tuple in the order (left, middle, right)
def getSensors(serialPort):
    # Write the command to the microcontroller
    serialPort.write(struct.pack('>BB',SENSE_ROBOT_COMMAND, 0))


# Change the sensor threshold
# This will impact when the robot decides it has seen an obstacle
def changeSensorThreshold(serialPort, newThreshold):
    # Write the command to the microcontroller
    serialPort.write(struct.pack('>BBB',CHANGE_SENSE_THRESHOLD_COMMAND,newThreshold&0xFF,(newThreshold>>8)&0xff))


# Modify the PWM values used to set the wheel speeds
def changePWMvalues(serialPort, newLeftValue, newRightValue):
    # Write the command to the microcontroller
    serialPort.write(struct.pack('>BBBBB',CHANGE_PWMS_COMMAND,newLeftValue&0xFF,(newLeftValue>>8)&0xff,newRightValue&0xFF,(newRightValue>>8)&0xff))

#**************************************************************************
# Intermediate Functions
#**************************************************************************

# Given right and left wheel ticks plus time in ms
# Compute forward and angular velocity
def motionModel(rightTicks, leftTicks):
    rightWheelDist = (rightTicks)*(2*math.pi*WHEEL_RADIUS/TICKS_PER_REV)
    leftWheelDist = (leftTicks)*(2*math.pi*WHEEL_RADIUS/TICKS_PER_REV)

    return rightWheelDist, leftWheelDist

#**************************************************************************
# Receive Functions
#**************************************************************************

# Read back a response from the TI
# Should read back 1 response per command given except for moveXY since that is really 2
def readResponse(serialPort):
    # Read the response
    msg = serialPort.read(1)
    msgType = struct.unpack_from('<B', msg)

    if msgType[0] == SENSE_ROBOT_COMMAND:
        msg = serialPort.read(15)
        sensors = struct.unpack_from('<HHH', msg)

        return sensors, msgType[0]

    else:
        msg = serialPort.read(15)
        result = struct.unpack_from('<BiiI', msg)

        moved.obsFlag = msgType[0]
        moved.rightWheelDist, moved.leftWheelDist = motionModel(result[1], result[2])
        moved.time = result[3]

        return moved, msgType[0]

