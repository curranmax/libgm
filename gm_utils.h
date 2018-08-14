
#ifndef _GM_UTILS_H_
#define _GM_UTILS_H_

#define MIN_GM_VALUE 0x0
#define MAX_GM_VALUE 0xffff

int   radianToGMUnit(float theta);
float GMUnitToRadian(int gm_unit);

int   degreeToGMUnit(float theta);
float GMUnitToDegree(int gm_unit);

#endif
