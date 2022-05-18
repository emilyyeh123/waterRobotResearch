# Water Robot Research - Communication Between Devices
This repository contains working code for communication between the raspberry Pi and the UAV. This repository is currently on the drone pi. An SSH keygen was created from my (Emily's) github account to be able to push and pull without having to input a password every time. Since the commit on April 26, I have added documentation files and clean-up edits that have not been pulled on the Pi.

The drone's raspberry pi is currently working on very old versions of software because the DJI Matrice 100 Drone code has not been and will no longer be updating (this is since about 2019). Because of this, it's also working on old versions of Python. Anyone who works on this project next should look into saving the current image of the pi somewhere and attempting to reset the pi to be able to use the latest versions of software. If this does not work, document it somewhere and revert to the saved image.

## DJI CPP
For [main.cpp](main.cpp) to compile, must include `dji_linux_environment` and `dji_linux_helpers` in this directory. 
[UserConfig.txt](UserConfig.txt) contains configuration instructions for the Pi to connect to the drone.

Files I wrote:
- [main.cpp](main.cpp)
  - Vehicle gets created here and passed through batteryLevel and position functions
  - writes the battery level or position to output files based on commands received through unix signaling
- [batteryLevel.hpp](batteryLevel.hpp)
- [batteryLevel.cpp](batteryLevel.cpp)
  - `int batteryLevel(Vehicle *vehicle)`
    - output: `BATTERY PERCENTAGE: X%`
  - `void outputBatteryLevel(Vehicle *vehicle)`
    - outputs battery level to [batteryOutput.txt](outputFiles/batteryOutput.txt)
- [position.hpp](position.hpp)
- [position.cpp](position.cpp)
  - must include `flight_control_sample.hpp`
  - `double lat(Vehicle *vehicle)`
    - output: `latitude is: X`
  - `double lon(Vehicle *vehicle)`
    - output: `longitude is: X`
  - `int getHealth(Vehicle *vehicle)`
    - Return gps signal strength on a scale of 1-5. Indoors is likely to be low (1 or 2).
    - output: `Signal Strength (scale from 0-5, >3 is strong): X`
  - `void outputPosition(Vehicle *vehicle)`
    - output to file [positionOutput.txt](outputFiles/positionOutput.txt) `Latitude is: X \n Longitude is: Y`

During communication, Python code will read the output files in [outputFiles](outputFiles) to receive drone updates.

## Unix Signalling
Allows interfacing between Python and C++. The [Multi Agent Bees Repository](https://github.com/jtotran/multi-agent-bees) provides the groundwork for the unix signalling in the [unix_signal_demo](https://github.com/jtotran/multi-agent-bees/tree/main/unix_signal_demo) directory. It has been integrated here to work with the drone's programming.


All files used for unix signalling:
- [cpp_pid](cpp_pid) (updates every time [send_unix_signal.py](send_unix_signal.py) runs)
- [receive_unix_signal.hpp](receive_unix_signal.hpp)
- [receive_unix_signal.cpp](receive_unix_signal.cpp)
- [send_unix_signal.hpp](send_unix_signal.hpp)
- [send_unix_signal.cpp](send_unix_signal.cpp)
- [send_unix_signal.py](send_unix_signal.py) - run this to send commands from the pi
- [echo_unix_signal.py](echo_unix_signal.py) - run this to receive commands

## Xbee Communication (incomplete, but started)
The [Multi Agent Bees Repository](https://github.com/jtotran/multi-agent-bees) provides the groundwork for the Xbee communication protocols in the [xbee_communication](https://github.com/jtotran/multi-agent-bees/tree/main/xbee_communication) directory. An attempt was made to integrate here with drone code, but there was not enough time to test it. The repository's [UAVAgent.py](UAVAgent.py) and [UAVController.py](UAVController.py) are both initial pushes of mostly unedited code. The drone's raspberry pi has edited, but unpushed and untested code for communication. It has some errors, but the idea is that, based on specific commands, it is expected to read the output files to get drone information.

### Xbees
Xbee PRO S1 and S2 are **not compatible** with Xbee PRO S3. [Xbee Compatibility Guide](https://www.sparkfun.com/pages/xbee_guide)

Download [XCTU (Windows) software](https://hub.digi.com/support/products/xctu/?path=/support/asset/drivers-installer-for-windows-xp-vista-7-and-8/) from the DIGI Xbee site to be able to get xbees on the same network. CH, DL, DH should be the same on all devices, but each one should have a unique ID associated with them. There should be 5 xbee PRO S1's in communication with each other with blue painter's tape labeling each one's properties. When I tried working with the xbee PRO S2's, I ran into firmware issues where I could not use them without having to download firmware on them. Additionally, there should be two xbee PRO S3B's in communication with each other.

To better understand how to use XCTU software, refer to [Communication between XBee modules](https://iot4beginners.com/communication-between-xbee-modules/). Communication can be tested using the monitor-looking symbol on the top right and opening the ports. Separate windows must be opened for both devices to test at the same time on the same device.

## Future Plans
May want to test xbees with working ground robots from Dr. Basha's robotics class. Using the pre-programmed microcontrollers, pull the python files from [groundRobotControl](groundRobotControl) onto a pi and follow the instructions from the pdf or comments that are directly in the code. Would also need to add GPS modules to ground robots. Basic code and information for a GPS module can be found in [gpsModule](gpsModule).

## Reference Material
- [DJI Matrice 100](https://www.dji.com/matrice100)
- [DJI OSDK Developer Documentation](https://developer.dji.com/onboard-sdk/documentation/introduction/homepage.html)
- [Bathymetry Research Repository (2019)](https://github.com/eabasha/bathymetryPython) (bathymetry research project, helpful for drone code)
- [Multi Agent Bees Repository](https://github.com/jtotran/multi-agent-bees) (Jason's hive algorithm code and helpful code for communication protocols)
- [Trash Detection Model](https://github.com/Emhernandez808/trash-detection-model/blob/main/classify.py) (Ethan's TensorFlow Trash Detection Model)
