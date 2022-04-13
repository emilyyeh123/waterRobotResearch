#include "send_unix_signal.hpp" 

void writePID( void ) 
{
	cout << "PID: " << getpid() << endl;

	ofstream cpp_pid ("cpp_pid"); 
	if (cpp_pid.is_open()) 
	{
		cpp_pid << getpid() << endl;
		cpp_pid.close();	
	}
	else
		cout << "Error. Could not write pid to file.\n";

	return; 
}

void getPID( pid_t &pid ) 
{
	string line;
	ifstream python_pid ("python_pid");
	if (python_pid.is_open()) 
	{
		getline(python_pid, line);
		pid = stoi(line);
		cout << "Target PID: " << pid << endl;
	}
	else
		cout << "Error. File does not exist.\n";
	python_pid.close();
	return;
}

void sendUnixSignal( pid_t pid ) 
{
	kill(pid, 34);	
	return; 
}
