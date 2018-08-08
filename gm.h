
#ifndef _GALVO_MIRROR_H_
#define _GALVO_MIRROR_H_

#include "gm_utils.h"

#include <stdlib.h>
#include <asm/types.h>

#include "pmd.h"
#include "usb-3100.h"

#include <iostream>

class GM {
public:
	GM(int ch,const std::string &serial_number_)
		: handle(nullptr), value(0), is_connected(false),
			channel(ch), serial_number(serial_number_) {}

	// Copies parameters, but the copied GM is not connected.
	GM(const GM &gm);
	const GM& operator=(const GM& gm);

	virtual ~GM();

	// Changes analog output (i.e. changes angle of mirror)
	virtual bool setValue(int v);

	// helper function to Connects to device
	virtual bool connectDevice();
	virtual bool disconnectDevice();

	virtual bool isConnected() const { return _getConnected(); }

	virtual bool isNull() const { return false; }

	int getValue() const { return value; }
	int getChannel() const { return channel; }
	std::string getSerialNumber() const { return serial_number; }
protected:
	int _getValue() const { return value; }
	bool _getConnected() const { return is_connected; }
	int _getChannel() const { return channel; }
	std::string _getSerialNumber() const { return serial_number; }

	void _setValue(int x) { value = x; }
	void _setConnected(bool x) { is_connected = x; }
	void _setChannel(int x) { channel = x; }
	void _setSerialNumber(const std::string& x) { serial_number = x; }
private:
	bool updateSerialNumber();
	
	// Has data used to talk to DAQ device
	hid_device *handle;

	// Current analog value device is set to
	int value;

	// Bool saying if connected or not
	bool is_connected;

	int channel;
	std::string serial_number;
};


#endif
