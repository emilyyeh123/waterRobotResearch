#ifndef SEND_UNIX_SIGNAL_HPP
#define SEND_UNIX_SIGNAL_HPP

#include <iostream>
#include <fstream>
#include <string> 
#include <csignal> 

#include <signal.h> 
#include <unistd.h>

using namespace std;

void writePID(); 
void getPID( pid_t &pid );
void sendUnixSignal( pid_t pid ); 

#endif 
