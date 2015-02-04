
#include <iostream>

#include "FSO.h"

void FSO::newLink(int id,int val){
	link_data[id] = val;
}

void FSO::setAlignment(int id,int val){
	if(hasLink(id)){
		link_data[id] = val;
	}
}

void FSO::setGMVal(int link_id){
	gm->setValue(getGMVal(link_id));
}

bool FSO::setActiveLink(int al){
	if(!hasLink(al)){
		active_link = -1;
		return false;
	}
	active_link = al;
	setGMVal(active_link);
	return true;
}

void FSO::adjustActiveLink(int val){
	setAlignment(active_link,val);
	setGMVal(active_link);
}

void FSO::incrementActiveLink(int i_val){
	setAlignment(active_link,getGMVal(active_link) + i_val);
	setGMVal(active_link);
}

int FSO::getGMVal(int link_id){
	if(hasLink(link_id)){
		return link_data[link_id];
	}
	return -1;
}

void FSO::printLinkData(std::ostream &out,const std::string &leading_string,int highlight){
	for(std::map<int,int>::iterator i = link_data.begin(); i != link_data.end(); i++){
		out << leading_string <<"Link " << i->first << " " << i->second;
		if(i->first == highlight){
			out << " <--";
		}
		out << std::endl;
	}
}

void FSO::connectGM(){
	if(gm != NULL){
		gm->connectDevice();
	}
}
void FSO::disconnectGM(){
	if(gm != NULL){
		gm->disconnectDevice();
	}
}

