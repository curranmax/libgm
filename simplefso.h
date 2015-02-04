#ifndef _SIMPLE_FSO_H_
#define _SIMPLE_FSO_H_

#include <string>

#include "gm.h"

class SimpleFSO{
public:
	SimpleFSO(const std::string &config_file);
	SimpleFSO(const std::string &config_file,float wait_time);
	~SimpleFSO();

	void switchLink();
	void reset();

	void connectGM();
	void disconnectGM();
private:
	void readData(const std::string &fname);

	GM *gm;

	int val1,val2;
	bool is_val1;

	int micro_wait_time; // Time before and after switching the mirror before doing anything in microseconds
};

#endif
