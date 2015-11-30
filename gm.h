
#ifndef _GALVO_MIRROR_H_
#define _GALVO_MIRROR_H_

#include <stdlib.h>
#include <asm/types.h>

#include "pmd.h"
#include "usb-3100.h"

#include <iostream>

#define MIN_GM_VALUE 0x0
#define MAX_GM_VALUE 0xffff

class GM {
public:
	GM() : channel(0),fd(-1),value(0),connected(false) {}
	GM(int ch) : channel(ch),fd(-1),value(0),connected(false) {}

	GM(const GM &gm);

	const GM& operator=(const GM& gm);

	virtual ~GM();

	// Changes analog output (i.e. changes angle of mirror)
	virtual bool setValue(int v);

	// helper function to Connects to device
	virtual void connectDevice();
	virtual void disconnectDevice();

	int getValue() const { return value; }

protected:
	void _setFD(int _fd) { fd = _fd;}
	void _setChannel(int _channel) { channel = _channel; }
	void _setValue(int _value) { value = _value; }
	void _setConnected(bool _connected) { connected = _connected; }

	int _getFD() const { return fd; }
	int _getChannel() const { return channel; }
	int _getValue() const { return value;}  // Just for symmetry
	bool _getConnected() const { return connected; }
	
private:
	// Parameters needed to talk to device
	int channel;
	int fd;

	// Current analgo value device is set to
	int value;

	// Bool saying if connected or not
	bool connected;
};

#endif
