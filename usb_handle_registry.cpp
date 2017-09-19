
#include "usb_handle_registry.h"

#include "usb-1608G.h"

#include <iostream>

namespace usb_handle {

std::map<std::string, libusb_device_handle*> lib_usb_map;
std::map<std::string, int> lib_usb_count;

std::map<std::string, hid_device*> hid_map;
std::map<std::string, int> hid_count;

void addLibUsbHandle(const std::string& serial_number, libusb_device_handle* new_handle) {
	lib_usb_map[serial_number] = new_handle;
	lib_usb_count[serial_number] += 1;
}

void removeLibUsbHandle(const std::string& serial_number) {
	lib_usb_count[serial_number] -= 1;
	if(lib_usb_count[serial_number] <= 0) {
		// Delete this libusb_device_handle, and delete entries in maps
		usbDLatchW_USB1608G(lib_usb_map[serial_number], 0x0);
		cleanup_USB1608G(lib_usb_map[serial_number]);

		lib_usb_map[serial_number] = nullptr;
	}
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
	hid_count[serial_number] += 1;
}

void removeHidHandle(const std::string& serial_number) {
	hid_count[serial_number] -= 1;
	if(hid_count[serial_number] <= 0) {
		// Delete associated hid_device*
		hid_close(hid_map[serial_number]);
		hid_exit(); // Maybe only be called once all hid devices are closed, or at the end of the program

		hid_map[serial_number] = nullptr;
	}
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
