
#include "diode.h"

#include "pmd.h"
#include "usb-1608G.h"
#include "usb_handle_registry.h"

bool Diode::is_lib_usb_init = false;

Diode::Diode(const Diode& diode) {
	is_connected = false;
	handle = nullptr;

	channel = diode.channel;
	serial_number = diode.serial_number;

	num_samples = diode.num_samples;
	sampling_rate = diode.sampling_rate;
}

const Diode& Diode::operator=(const Diode& diode) {
	is_connected = false;
	handle = nullptr;

	channel = diode.channel;
	serial_number = diode.serial_number;

	num_samples = diode.num_samples;
	sampling_rate = diode.sampling_rate;

	return *this;
}

Diode::~Diode() {
	disconnectDevice();
}

float Diode::getValue() {
	ScanList list[0]; // Used to configure the input

	// TODO make this member values so that it can be easily changed at runtime.
	list[0].mode = DIFFERENTIAL | LAST_CHANNEL; // Gets sign of value
	list[0].range = BP_10V;      				// between +- 10V (using smaller gains gives more accurate results?)
	list[0].channel = channel;

	// Configures the next scan
	usbAInConfig_USB1608G(handle, list);

	// Buffer to hold the read data
	uint16_t data[num_samples];

	// Starts the Scan
	usbAInScanStart_USB1608G(handle, num_samples, 0, sampling_rate, 0x0);
	
	// Gets the data from the scan after it is done. (last parameter )
	int bytes_read = usbAInScanRead_USB1608G(handle, num_samples, /*num_channels*/ 1, data, /*timeout*/ 20000);
	if (bytes_read != 2 * num_samples) {
		std::cerr << "ERROR IN DIODE SCAN!!!!" << std::endl;
		return 0;
	}

	// Average all samples
	// TODO ignore outliers
	int sum_samples = 0;
	for(int i = 0; i < num_samples; ++i) {
		sum_samples += (int)data[i];
	}
	float avg_value = float(sum_samples) / float(num_samples);

	std::cout << sum_samples << " " << num_samples << std::endl;

	return avg_value;
}

float Diode::getVoltage() {
	std::cout << "Diode::getVoltage" << std::endl;
	return convertToVoltage(getValue());
}

float Diode::convertToVoltage(float value) {
	// For BP_10V
	return (value - 32768.0) * 10.0 / 32768.0;
	// see volts_USB1608G for other gains
}

bool Diode::connectDevice() {
	if(!is_connected) {
		if(!is_lib_usb_init) {
			int rv = libusb_init(NULL);
			if (rv < 0) {
				std::cerr << "libusb_init: Failed to initialze libusb" << std::endl;
				return false;
			}
			is_lib_usb_init = true;
		}

		if(serial_number == "") {
			handle = usb_device_find_USB_MCC(USB1608G_V2_PID, nullptr);
		} else {
			handle = usb_device_find_USB_MCC(USB1608G_V2_PID, serial_number.c_str());
		}

		if(handle == nullptr) {
			handle = usb_handle::getLibUsbHandle(serial_number);
			if (handle == nullptr) {
				std::cerr << "Failed to connect to USB-1608G device" << std::endl;
				return false;
			}
		}
		usbInit_1608G(handle, 2);
		if (!updateSerialNumber()) {
			std::cerr << "Problem with device's serial number" << std::endl;
			return false;
		}
		usb_handle::addLibUsbHandle(serial_number, handle);
		std::cout << "Connected to Diode" << std::endl;
		is_connected = true;
	}
	return is_connected;
}

bool Diode::disconnectDevice() {
	if(is_connected) {
		usb_handle::removeLibUsbHandle(serial_number);
		
		handle = nullptr;
		is_connected = false;
	}
	return !is_connected;
}

void Diode::blinkDaqLed(int num_blinks) {
	usbBlink_USB1608G(handle, num_blinks);
}

bool Diode::updateSerialNumber() {
	if (handle != nullptr) {
		char new_serial_number_c_str[256];
		usbGetSerialNumber_USB1608G(handle, new_serial_number_c_str);

		if (new_serial_number_c_str == nullptr) {
			return false;
		}
		std::string new_serial_number = new_serial_number_c_str;
		if (serial_number == "") {
			serial_number = new_serial_number;
		}
		return serial_number == new_serial_number;
	}
	return false;
}

