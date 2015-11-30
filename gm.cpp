
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "gm.h"

GM::GM(const GM &gm){
	channel = gm.channel;
	fd = gm.fd;
	value = gm.value;
}

const GM& GM::operator=(const GM& gm){
	channel = gm.channel;
	fd = gm.fd;
	value = gm.value;
	connected = gm.connected;

	return *this;
}

// Wrapper for driver
// Returns true if value of GM changed and actually moves mirror
bool GM::setValue(int v){
	if(v < MIN_GM_VALUE){
		v = MIN_GM_VALUE;
	}
	if(v > MAX_GM_VALUE){
		v = MAX_GM_VALUE;
	}
	bool rv = (value == v) && connected;
	value = v;
	if(connected){
		usbAOut_USB31XX(fd, channel, value, 0);
	}
	return rv;
}

// Sets up communication to device
void GM::connectDevice(){
	int nInterfaces = PMD_Find(MCC_VID, USB3103_PID, &fd);
	if (nInterfaces <= 0) {
		std::cout << "Could not connect to device" << std::endl;
		std::cout << "Ensure that you have root access when running program" << std::endl;
		exit(0);
	}

	// Set up file descriptor to communicate with device
	usbDConfigPort_USB31XX(fd, DIO_DIR_OUT);
	usbDOut_USB31XX(fd, 0);

	// Configure all analog channels for 0-10V output
	for(int i = 0; i < 8; i++) {
		usbAOutConfig_USB31XX(fd, i, UP_10_00V);
	}

	connected = true;

	setValue(value);
}

GM::~GM(){
	disconnectDevice();
}

void GM::disconnectDevice(){
	close(fd);
	connected = false;
}
