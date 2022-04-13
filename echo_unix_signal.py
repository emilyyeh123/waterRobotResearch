import os 
import signal 
import time

signal_received = False

def signal_handler(signum, frame):
    print('Recieved: ', signum) 

    global signal_received 
    signal_received = True

    return signal_received

def write_pid(): 
    python_pid = open('python_pid', 'w')
    python_pid.write(str(os.getpid()))
    python_pid.close() 

    return

def main(): 
    write_pid() 

    while signal_received != True:
        # Read updated point in file - given trash location 
        # Load manage and send the robots to intercept the trash 
        pass

    print('Successfully received unix signal!') 

    return


if __name__ == '__main__':
    signal.signal(34, signal_handler)

    main() 
