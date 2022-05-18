#!/usr/bin/python3

import serial

def main():
	#initialize serial
	gps = serial.Serial("/dev/ttyACM0", baudrate = 9600)

	while True:
		line = gps.readline()			# read serial line
		line = line.decode("utf-8")		# decode byte object to string
		line = line.partition("*")[0]		# remove everything after *
		data = line.split(",")			# split string into list

		# print position or signal strength
		# message structure based on NMEA-0183 protocol
		if data[0] == "$GPGGA":
			print("position: ", data[2], ", ", data[4])
		elif data[0] == "$GPGLL":
			print("position: ", data[1], ", ", data[3])
		elif data[0] == "$GPRMC":
			print("position: ", data[3], ", ", data[5])
		elif data[0] == "$GPGSV":
			print("signal strength: ", data[7])

if __name__ == "__main__":
	main()
