#include "receive_unix_signal.hpp"

void signalHandler(int sig) {
	/* cout << "Received: 34\n"; */
	sig_num = sig; 
	return;
}
