
#include "simple_fso.h"

#include "gm.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>

SimpleFSO::~SimpleFSO() {
	if(gm1 != nullptr) {
		delete gm1;
	}
	if(gm2 != nullptr) {
		delete gm2;
	}
}

void SimpleFSO::load() {
	// Open file
	std::ifstream ifstr(filename, std::ifstream::in);

	// Read in contents
	std::string line, token;

	std::string gm1_serial_number = "", gm2_serial_number = "";
	int gm1_channel = -1, gm2_channel = -1;
	int gm1_starting_value = -1, gm2_starting_value = -1;

	while(std::getline(ifstr, line)) {
		token = "";
		std::stringstream sstr(line);

		sstr >> token;

		bool match = true;
		if(token == "gm1_serial_number") {
			sstr >> gm1_serial_number;
		} else if(token == "gm2_serial_number") {
			sstr >> gm2_serial_number;
		} else if(token == "gm1_channel") {
			sstr >> gm1_channel;
		} else if(token == "gm2_channel") {
			sstr >> gm2_channel;
		} else if(token == "gm1_starting_value") {
			sstr >> gm1_starting_value;
		} else if(token == "gm2_starting_value") {
			sstr >> gm2_starting_value;
		} else {
			if((gm1_starting_value == -1 || gm2_starting_value == -1) && token == "link") {
				std::string tmp;

				sstr >> tmp >> tmp >> gm1_starting_value >> gm2_starting_value;
			}

			match = false;
		}

		if(match) {
			file_order.push_back(token);
		} else {
			file_order.push_back(line);
		}
	}
	ifstr.close();

	// Make GMs
	gm1 = new GM(gm1_channel, gm1_serial_number);
	gm2 = new GM(gm2_channel, gm2_serial_number);

	gm1->connectDevice();
	gm2->connectDevice();

	setGM1Val(gm1_starting_value);
	setGM2Val(gm2_starting_value);

	std::cout << "FSO loaded from: " << filename << std::endl;
}

void SimpleFSO::save() {
	if(gm1 == nullptr || gm2 == nullptr) {
		std::cerr << "GMs are NULL when trying to save" << std::endl;
		exit(1);
	}

	std::ofstream ofstr(filename, std::ofstream::out);

	bool pso1 = false, pso2 = false;
	for(unsigned int i = 0; i < file_order.size(); ++i) {
		if(file_order[i] == "gm1_serial_number") {
			ofstr << file_order[i] << " " << gm1->getSerialNumber() << std::endl;
		} else if(file_order[i] == "gm2_serial_number") {
			ofstr << file_order[i] << " " << gm2->getSerialNumber() << std::endl;
		} else if(file_order[i] == "gm1_channel") {
			ofstr << file_order[i] << " " << gm1->getChannel() << std::endl;
		} else if(file_order[i] == "gm2_channel") {
			ofstr << file_order[i] << " " << gm2->getChannel() << std::endl;
		} else if(file_order[i] == "gm1_starting_value") {
			ofstr << file_order[i] << " " << getGM1Val() << std::endl;
			pso1 = true;
		} else if(file_order[i] == "gm2_starting_value") {
			ofstr << file_order[i] << " " << getGM2Val() << std::endl;
			pso2 = true;
		} else {
			ofstr << file_order[i];
		}
	}

	if(!pso1) {
		ofstr << "gm1_starting_value " << getGM1Val() << std::endl;
	}
	if(!pso2) {
		ofstr << "gm2_starting_value " << getGM2Val() << std::endl;
	}
	ofstr.close();

	std::cout << "FSO saved to: " << filename << std::endl;
}

int SimpleFSO::getGMVal(GM* gm) const {
	if(gm == nullptr) {
		std::cerr << "gm is NULL" << std::endl;
		exit(1);
	}
	return gm->getValue();
}

void SimpleFSO::setGMVal(GM* gm, int v) const {
	if(gm == nullptr) {
		std::cerr << "gm is NULL" << std::endl;
		exit(1);
	}
	gm->setValue(v);
}
