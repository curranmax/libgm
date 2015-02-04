
#ifndef _FSO_H_
#define _FSO_H_

#include <map>

#include "gm.h"

class FSO{
public:
	FSO(int _id,GM *_gm): id(_id),active_link(-1),gm(_gm) {}
	~FSO() {
		disconnectGM();
		delete gm;
	}

	bool hasGM() { return gm != NULL; }
	bool hasLink(FSO* fso) { return hasLink(fso->getID()); }
	bool hasLink(int i) { return link_data.find(i) != link_data.end();}

	void setGMVal(int link_id);

	void newLink(int id,int val);
	void setAlignment(int id,int val);
	void setActiveLink(FSO* fso) { setActiveLink(fso->getID()); }
	bool setActiveLink(int al);
	void resetActiveLink() { active_link = -1; }
	void adjustActiveLink(int val);
	void incrementActiveLink(int i_val);

	int getGMVal(int link_id);

	void connectGM();
	void disconnectGM();

	int getID() { return id; }

	void printLinkData(std::ostream &out,const std::string &leading_string,int highlight = -1);

private:
	// ID number, used to reference 
	int id;

	// Current active link
	int active_link;

	// Reference to its mirror, if NULL then it doesn't have a GM
	GM *gm;

	// Key is ID of other FSO
	// Value is value to set GM to in order to create link
	std::map<int,int> link_data;
};

#endif

