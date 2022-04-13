import os 
import signal
import time 

def get_battery(pid):
    os.kill(pid, 34) 
    time.sleep(2) 

    return 

def get_location(pid):
    os.kill(pid, 35) 
    time.sleep(2) 

    return


def main():
    time.sleep(2) 

    f = open('cpp_pid', 'r') 
    cpp_pid = int(f.readline()) 

    while 1: 
        print("UAV Command Menu") 
        print("[0] Get Battery Level") 
        print("[1] Get Location")
        print("[2] Exit")
        
        command = int(input("> "))

        if (command == 0):
            get_battery(cpp_pid) 
        elif (command == 1):
            get_location(cpp_pid) 
        else:
            return

    return

if __name__=='__main__':
    main() 
