
#include <stdio.h>
#include <signal.h> 
#include <unistd.h> 

#include "send_unix_signal.hpp"
#include "receive_unix_signal.hpp"

using namespace std;

uint8_t sig_num = 0;

int main() 
{
	signal(34, signalHandler);
	signal(35, signalHandler);
	pid_t pid; 
	writePID();

	while(true) 
	{ 
		if(sig_num == 34) 
		{
			cout << "Signal Received: " << (int)sig_num << endl; 
			sig_num = 0;
			/* Battery Check */ 
		}	
		else if(sig_num == 35) 
		{
			cout << "Signal Received: " << (int)sig_num << endl;
			sig_num = 0;
			/* Get Location */ 
		}
		sleep(1);
	};

	return 0;
}
