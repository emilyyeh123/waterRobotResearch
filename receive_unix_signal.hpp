#ifndef RECEIVE_UNIX_SIGNAL_HPP
#define RECEIVE_UNIX_SIGNAL_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <csignal> 

#include <signal.h> 

#include <unistd.h> 
#include <cstdint> 

using namespace std;

extern uint8_t sig_num;

void signalHandler(int sig);

#endif 
