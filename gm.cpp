
#include "gm.h"

#include "usb_handle_registry.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#define MAX_FD 10

GM::GM(const GM &gm){
	handle = nullptr;
	is_connected = false;

	value = gm.value;
	channel = gm.channel;
	serial_number = gm.serial_number;
}

const GM& GM::operator=(const GM& gm){
	handle = nullptr;
	is_connected = false;

	value = gm.value;
	channel = gm.channel;
	serial_number = gm.serial_number;

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
	bool rv = (value == v) && is_connected;
	value = v;
	if(is_connected){
		usbAOut_USB31XX(handle, channel, (uint16_t) value, 0);
	}
	return rv;
}

// Sets up communication to device
bool GM::connectDevice(){
	if(!is_connected) {
		// There maybe problems with calling this multiple times.
		int rv = hid_init();
		if (rv < 0) {
			std::cerr << "hid_init: Failed" <<std::endl;
			return false;
		}

		if(serial_number == "") {
			handle = hid_open(MCC_VID, USB3103_PID, NULL);
		} else {
			std::wstring temp(serial_number.length(), L' ');
			std::copy(serial_number.begin(), serial_number.end(), temp.begin());
			handle = hid_open(MCC_VID, USB3103_PID, temp.c_str());
		}

		if (handle == nullptr) {
			handle = usb_handle::getHidHandle(serial_number);
			if (handle ==nullptr) {
				std::cerr << "Failed to connect to device" << std::endl;
				return false;
			}
		}

		usbDConfigPort_USB31XX(handle, DIO_DIR_OUT);
  		usbDOut_USB31XX(handle, 0);

		if(!updateSerialNumber()) {
			std::cerr << "Problem with serial number of device" << std::endl;
			return false;
		}
		
		usb_handle::addHidHandle(serial_number, handle);
		
		// Configures channel to output between 0 and 10V and also sets output to 0.
		usbAOutConfig_USB31XX(handle, channel, UP_10_00V);

		std::cout << "Connected to GM" << std::endl;
		is_connected = true;
	}
	return is_connected;
}

GM::~GM(){
	disconnectDevice();
}

bool GM::disconnectDevice(){
	if(is_connected) {
		usb_handle::removeHidHandle(serial_number);
		handle = nullptr;
		is_connected = false;
	}
	return !is_connected;
}

bool GM::updateSerialNumber() {
	if(handle != nullptr) {
		wchar_t new_serial_number_c_str[256];
		hid_get_serial_number_string(handle, new_serial_number_c_str, 64);

		if (new_serial_number_c_str == nullptr) {
			return false;
		}

		std::wstring new_serial_number_wstring = new_serial_number_c_str;
		std::string new_serial_number(new_serial_number_wstring.length(), ' ');
		std::copy(new_serial_number_wstring.begin(), new_serial_number_wstring.end(), new_serial_number.begin());
		if (serial_number == "") {
			serial_number = new_serial_number;
		}
		return serial_number == new_serial_number;
	}
	return false;
}
