
#ifndef _SIMPLE_FSO_H_
#define _SIMPLE_FSO_H_

#include "gm.h"

#include <string>
#include <vector>

class SimpleFSO {
public:
	SimpleFSO() = delete;
	SimpleFSO(const std::string _filename)
			: filename(_filename), file_order(), gm1(nullptr), gm2(nullptr) {
		load();
	}

	SimpleFSO(const SimpleFSO& fso) = delete;
	const SimpleFSO& operator=(const SimpleFSO& fso) = delete;

	~SimpleFSO();

	void load();
	void save();

	bool isGM1Connected() const { return gm1 == nullptr || gm1->isConnected(); }
	bool isGM2Connected() const { return gm2 == nullptr || gm2->isConnected(); }

private:
	int  getGMVal(GM* gm) const;
	void setGMVal(GM* gm, int v) const;

public:
	int getGM1Val() const { return getGMVal(gm1); }
	int getGM2Val() const { return getGMVal(gm2); }

	void setGM1Val(int v) { setGMVal(gm1, v); }
	void setGM2Val(int v) { setGMVal(gm2, v); }

	void incrGM1Val(int v) { setGMVal(gm1, v + getGMVal(gm1)); }
	void incrGM2Val(int v) { setGMVal(gm2, v + getGMVal(gm2)); }

private:
	std::string filename;
	std::vector<std::string> file_order;

	GM* gm1;
	GM* gm2;	
};

#endif
