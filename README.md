# Water Robot Research - Communication Between Devices
This repository contains working code for communication between the raspberry Pi and the UAV.

## DJI CPP
For [main](main.cpp) to compile, must include `dji_linux_environment` and `dji_linux_helpers` in this directory. 
[UserConfig.txt](UserConfig.txt) contains configuration instructions for the Pi to connect to the drone.

Files I wrote:
- [main.cpp](main.cpp)
  - runs batteryLevel and position code based on unix signalling commands (must run in conjunction with [send_unix_signal.py](send_unix_signal.py))
- [batteryLevel.hpp](batteryLevel.hpp)
- [batteryLevel.cpp](batteryLevel.cpp)
- [position.hpp](position.hpp)
- [position.cpp](position.cpp)

## Unix Signalling
All files used for unix signalling:
- [cpp_pid](cpp_pid) (updates every time [send_unix_signal.py](send_unix_signal.py) runs)
- [receive_unix_signal.hpp](receive_unix_signal.hpp)
- [receive_unix_signal.cpp](receive_unix_signal.cpp)
- [send_unix_signal.hpp](send_unix_signal.hpp)
- [send_unix_signal.cpp](send_unix_signal.cpp)
- [send_unix_signal.py](send_unix_signal.py) - run this to send commands from the pi
- [echo_unix_signal.py](echo_unix_signal.py)

## Next Steps
- Integrate xbee Communication from Jason's [Multi Agent Bees Repository](https://github.com/jtotran/multi-agent-bees)
- Test Ethan's [Trash Detection Model](https://github.com/Emhernandez808/trash-detection-model/blob/main/classify.py) on TensorFlow

## Reference Material
- [DJI Matrice 100](https://www.dji.com/matrice100)
- [DJI OSDK Developer Documentation](https://developer.dji.com/onboard-sdk/documentation/introduction/homepage.html)
- [Bathymetry Research Repository (2019)](https://github.com/eabasha/bathymetryPython)

## Additional References
- [Multi Agent Bees Repository](https://github.com/jtotran/multi-agent-bees)
- [Trash Detection Model](https://github.com/Emhernandez808/trash-detection-model/blob/main/classify.py)
