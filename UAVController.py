#!/usr/bin/python3

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

# Camera To Detect Trash
R_CAMERA = 0xDC



# NEED ROOT OR GROUP ACCESS TO PERIPHERAL
def init_serial(): 
    try:
        ser = serial.Serial("/dev/ttyUSB0", 57600, timeout=5) 
    except:
        return #ser = serial.Serial("/dev/ttyUSB1", 57600, timeout=5) 

    return ser

def send_packet(ser, packet):
    for i in range(len(packet)):
        ser.write(packet[i])

    time.sleep(0.5) 

def request_battery(ser): 
    print("transmitting")
    packet = []
    packet.append(struct.pack('B', PACKET_HEADER))
    packet.append(struct.pack('B', R_BATTERY))
    packet.append(struct.pack('B', PACKET_TAIL)) 
    send_packet(ser, packet) 

    print("receiving response")
    data = [] 
    while 1: 
        try:
            resp = ser.read(1) 
            print(resp)
            unpack_resp = struct.unpack('B', resp) 
            unpack_resp = unpack_resp[0] 

            if unpack_resp == PACKET_HEADER:
                while unpack_resp != PACKET_TAIL:
                    resp = ser.read(1)
                    unpack_resp = struct.unpack('B', resp) 
                    unpack_resp = unpack_resp[0] 
                    if unpack_resp != PACKET_TAIL:
                        data.append(unpack_resp) 

                if unpack_resp == PACKET_TAIL:
                    break
        except:
            break
 
    return 0, data

def request_position(ser):
    packet = []
    packet.append(struct.pack('B', PACKET_HEADER))
    packet.append(struct.pack('B', R_POSITION))
    packet.append(struct.pack('B', PACKET_TAIL)) 
    send_packet(ser, packet) 

    data = [] 
    while 1: 
        try:
            resp = ser.read(1) 
            unpack_resp = struct.unpack('B', resp) 
            unpack_resp = unpack_resp[0] 

            if unpack_resp == PACKET_HEADER:
                while unpack_resp != PACKET_TAIL:
                    resp = ser.read(1)
                    unpack_resp = struct.unpack('B', resp) 
                    unpack_resp = unpack_resp[0] 
                    if unpack_resp != PACKET_TAIL:
                        data.append(unpack_resp) 

                if unpack_resp == PACKET_TAIL:
                    break
        except:
            break
 
    return 0, data

def main():
    ser = init_serial()
    print(ser)

    while 1:
        print("UAV Controller Menu") 
        print("[0] Request Battery") 
        print("[1] Request Position") 
        print("[2] Exit") 
        selection = int(input("> "))

        if selection == 0:
            battery = request_battery(ser) 
            print(battery[1]) 
        elif selection == 1:
            pos = request_position(ser) 
            print(''.join(chr(i) for i in pos[1])) 
        elif selection == 2:
            return

if __name__=="__main__":
    main()
