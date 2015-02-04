
#ifndef _GM_UTILS_H_
#define _GM_UTILS_H_

#include <map>
#include <string>

class FSO;
class GM;
class DummyGM;

typedef std::map<int,FSO*> fso_map;
typedef std::map<int,FSO*>::iterator fso_map_itr;

// Changes behavior if DEBUG flag given
GM* makeGM();

// IO for alignment files
std::map<int,FSO*> readData(const std::string &fname);
void writeData(const std::string &fname,std::map<int,FSO*> data);

#endif
