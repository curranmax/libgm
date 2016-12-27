
#include "usb_handle_registry.h"

#include <iostream>

namespace usb_handle {

std::map<std::string, libusb_device_handle*> lib_usb_map;
std::map<std::string, hid_device*> hid_map;

void addLibUsbHandle(const std::string& serial_number, libusb_device_handle* new_handle) {
	lib_usb_map[serial_number] = new_handle;
}

libusb_device_handle* getLibUsbHandle(const std::string& serial_number) {
	if (lib_usb_map.size() == 1 && serial_number == "") {
		return lib_usb_map.begin()->second;
	}
	if (lib_usb_map.count(serial_number) == 1) {
		return lib_usb_map[serial_number];
	}
	return nullptr;
}

void addHidHandle(const std::string& serial_number, hid_device* new_handle) {
	hid_map[serial_number] = new_handle;
}

hid_device* getHidHandle(const std::string& serial_number) {
	if (hid_map.size() == 1 && serial_number == "") {
		return hid_map.begin()->second;
	}
	if (hid_map.count(serial_number) == 1) {
		return hid_map[serial_number];
	}
	return nullptr;
}

}		// namepspace usb_handle
