
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>

#include "gm.h"
#include "simplefso.h"

SimpleFSO::SimpleFSO(const std::string &config_file){
	micro_wait_time = 0;

	// Read in file and get two values
	is_val1 = true;

	gm = new GM();

	val1 = 0;
	val2 = 0;

	readData(config_file);
}

SimpleFSO::SimpleFSO(const std::string &config_file, float wait_time){
	micro_wait_time = int(wait_time * 1000000);

	// Read in file and get two values
	is_val1 = true;

	gm = new GM();

	val1 = 0;
	val2 = 0;

	readData(config_file);
}

void SimpleFSO::readData(const std::string &fname){
	
	std::ifstream instream(fname.c_str());
	std::string line;

	bool gm_fso = false;
	bool fso1 = false;
	bool fso2 = false;
	while(std::getline(instream,line)){
		if(line == ""){
			continue;
		}
		std::stringstream ss(line);
		std::string v1,v2,v3;
		ss >> v1 >> v2 >> v3;
		if(v1 == "FSO"){
			if(v3 == "GM"){
				if(!gm_fso){
					gm_fso = true;
				} else {
					std::cerr << "Error in config file" << std::endl;
					exit(0);
				}	
			}
		} else if(v1 == "Link"){
			int gm_val = atoi(v3.c_str());
			if(!fso1){
				val1 = gm_val;
				fso1 = true;
			} else if(!fso2){
				val2 = gm_val;
				fso2 = true;
			} else {
				std::cerr << "Error in config file" << std::endl;
				exit(0);
			}
		} else {
			std::cerr << "Error in input file format" << std::endl;
			exit(0);
		}
	}
	instream.close();
}

SimpleFSO::~SimpleFSO(){
	if(gm != NULL){
		gm->disconnectDevice();
		delete gm;
		gm = NULL;
	}
}

void SimpleFSO::switchLink(){
	usleep(micro_wait_time);
	if(is_val1){
		gm->setValue(val2);
	} else {
		gm->setValue(val1);
	}
	is_val1 = !is_val1;
	usleep(micro_wait_time);
}

void SimpleFSO::reset(){
	usleep(micro_wait_time);
	gm->setValue(val1);
	is_val1 = true;
	usleep(micro_wait_time);
}

void SimpleFSO::connectGM(){
	if(gm != NULL){
		gm->connectDevice();
	}
}

void SimpleFSO::disconnectGM(){
	if(gm!= NULL){
		gm->disconnectDevice();
	}
}
