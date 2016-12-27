
#ifndef _DIODE_H_
#define _DIODE_H_

#include <stdlib.h>
#include <asm/types.h>

#include "pmd.h"
#include "usb-1608G.h"

#include <iostream>

#define MIN_DIODE_VALUE 0x0
#define MAX_DIODE_VALUE 0xffff

class Diode {
  public:
	Diode(int channel_, const std::string& serial_number_)
		: is_connected(false), handle(nullptr),
			channel(channel_), serial_number(serial_number_),
			num_samples(1), sampling_rate(1) {}
	Diode(int channel_, const std::string& serial_number_, int num_samples_, int sampling_rate_)
		: is_connected(false), handle(nullptr),
			channel(channel_), serial_number(serial_number_),
			num_samples(num_samples_), sampling_rate(sampling_rate_) {}
	
	// Copies the parameters of the diode, but not the actual connection
	// MAYBE don't allow these
	Diode(const Diode& diode);
	const Diode& operator=(const Diode& diode);

	virtual ~Diode();
	
	// Queries the A to D device for the current voltage.
	// Value returned is unit-less in range [0,2^16-1]
	virtual float getValue();
	float getVoltage(); // Equivalent to convertToVoltage(getValue())

	float convertToVoltage(float value); // static?

	// Returns true if at the end the device is in the appropriate state
	virtual bool connectDevice();
	virtual bool disconnectDevice();

	virtual bool isNull() const { return false; }

	virtual void blinkDaqLed(int num_blinks);

	int getChannel() const { return channel; }
	const std::string& getSerialNumber() const { return serial_number; }
	int getNumSamples() const { return num_samples; }
	int getSamplingRate() const { return sampling_rate; }


  private:
	// Returns true if serial number was "" and now not "" or the serial number was correct
	bool updateSerialNumber();
  	
  	bool is_connected;
	libusb_device_handle* handle;

	int channel;
	std::string serial_number;

	int num_samples;
	int sampling_rate;

	static bool is_lib_usb_init;
};

#endif
