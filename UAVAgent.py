#!/usr/bin/python

import serial
import struct
import time

import enum 



# PACKET STRUCTURE ELEMENTS
PACKET_HEADER = 0xFA
PACKET_TAIL = 0xFB

# CONTROLLER COMMAND PACKET ELEMENTS
# R - Requests
R_BATTERY = 0xEF
R_POSITION = 0xEE

# Camera To Detect Ojects
R_CAMERA = 0xDC



def init_serial():
    try:
        ser = serial.Serial("/dev/ttyUSB1", 57600, timeout=5) 
    except:
        ser = serial.Serial("/dev/ttyUSB0", 57600, timeout=5) 

    return ser

def send_packet(ser, packet):
    for i in range(len(packet)):
        ser.write(packet[i]) 

    time.sleep(0.5) 

def respond_battery(ser):
    battery_reading = 88 # Battery measurement here... 

    packet = []
    packet.append(struct.pack('B', PACKET_HEADER))
    packet.append(struct.pack('B', battery_reading))
    packet.append(struct.pack('B', PACKET_TAIL)) 

    send_packet(ser, packet) 

    return

def respond_position(ser):
    position_string = 'lat: -0.66572, log: -0.68532' # GPS position measurement here... 

    packet = []
    packet.append(struct.pack('B', PACKET_HEADER)) 
    for char in position_string:
        packet.append(struct.pack('c', char.encode('ascii'))) 
    packet.append(struct.pack('B', PACKET_TAIL)) 

    send_packet(ser, packet) 

    return


def main():
    ser = init_serial() 

    data = [] 
    while 1:
        data = [] 
        try:
            resp = ser.read(1) 
            unpack_resp = struct.unpack('B', resp) 
            unpack_resp = unpack_resp[0]
            print("received data")

            if unpack_resp == PACKET_HEADER: 
                while unpack_resp != PACKET_TAIL:
                    resp = ser.read(1) 
                    unpack_resp = struct.unpack('B', resp) 
                    unpack_resp = unpack_resp[0]
                    data.append(unpack_resp) 
        except:
            pass

        if data != []:
            if data[0] == R_BATTERY:
                respond_battery(ser) 
            elif data[0] == R_POSITION:
                respond_position(ser)

    return


if __name__=="__main__":
    main()
