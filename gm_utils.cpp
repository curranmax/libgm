
#include "gm_utils.h"
#include "FSO.h"
#include "gm.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

GM* makeGM(){
	return new GM();
}

std::map<int,FSO*> readData(const std::string &fname){
	std::map<int,FSO*> data;
	FSO *cur_fso;
	std::ifstream instream(fname.c_str());
	std::string line;
	while(std::getline(instream,line)){
		if(line == ""){
			continue;
		}
		std::stringstream ss(line);
		std::string v1,v2,v3;
		ss >> v1 >> v2 >> v3;
		if(v1 == "FSO"){
			GM *gm = NULL;
			if(v3 == "GM"){
				gm = makeGM();
			}
			int id_num = atoi(v2.c_str());
			cur_fso = new FSO(id_num,gm);
			data[id_num] = cur_fso;
		} else if(v1 == "Link" && cur_fso != NULL){
			int id_num = atoi(v2.c_str()),gm_val = atoi(v3.c_str());
			cur_fso->newLink(id_num,gm_val);
		} else {
			std::cerr << "Error in input file format" << std::endl;
			exit(0);
		}
	}
	instream.close();
	return data;
}

void writeData(const std::string &fname,std::map<int,FSO*> data){
	std::ofstream outstream(fname.c_str());
	for(std::map<int,FSO*>::iterator i = data.begin(); i != data.end(); i++){
		if(i->second->hasGM()){
			outstream << "FSO " << i->first << " GM" << std::endl;
			i->second->printLinkData(outstream,"\t");
		} else {
			outstream << "FSO " << i->first << std::endl;
		}
		
	}
	outstream.close();
}
