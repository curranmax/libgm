
#include "gm.h"

extern "C" {
	GM* GM_new(int ch,const std::string &sn) { return new GM(ch,sn); }

	bool GM_connectDevice(GM* gm) { return gm->connectDevice(); }
	bool GM_disconnectDevice(GM* gm) { return gm->disconnectDevice(); }

	bool GM_setValue(GM* gm,int v) { return gm->setValue(v); }
	int GM_getValue(GM* gm) { return gm->getValue(); }
}
