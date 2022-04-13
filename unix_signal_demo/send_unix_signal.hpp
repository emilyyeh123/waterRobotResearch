#ifndef SEND_UNIX_SIGNAL_HPP
#define SEND_UNIX_SIGNAL_HPP

#include <iostream>
#include <fstream>
#include <string> 
#include <csignal> 
#include <unistd.h>

#include <signal.h> 

using namespace std;

void writePID(); 
void getPID( pid_t &pid );
void sendUnixSignal( pid_t pid ); 

#endif 
