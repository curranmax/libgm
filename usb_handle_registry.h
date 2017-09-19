
#ifndef _USB_HANDLE_REGISTRY_H_
#define _USB_HANDLE_REGISTRY_H_

#include "pmd.h"

#include <stdlib.h>
#include <asm/types.h>
#include <map>

namespace usb_handle {
// TODO this should keep track of how many people have these handles, and then close then appropriately when that reaches zero

void addLibUsbHandle(const std::string& serial_number, libusb_device_handle* new_handle);
void removeLibUsbHandle(const std::string& serial_number);
libusb_device_handle* getLibUsbHandle(const std::string& serial_number);

void addHidHandle(const std::string& serial_number, hid_device* new_handle);
void removeHidHandle(const std::string& serial_number);
hid_device* getHidHandle(const std::string& serial_number);
}		// namepspace usb_handle

#endif
