
#include "gm_utils.h"

#define FORTY_DEGREES_IN_RADIANS 0.698132

int radianToGMUnit(float theta) {
	return (MAX_GM_VALUE - MIN_GM_VALUE) / FORTY_DEGREES_IN_RADIANS * theta + MIN_GM_VALUE;
}

float GMUnitToRadian(int gm_unit) {
	return FORTY_DEGREES_IN_RADIANS / (MAX_GM_VALUE - MIN_GM_VALUE) * (gm_unit - MIN_GM_VALUE);
}

int degreeToGMUnit(float theta) {
	return (MAX_GM_VALUE - MIN_GM_VALUE) / 40.0 * theta + MIN_GM_VALUE;
}

float GMUnitToDegree(int gm_unit) {
	return 40.0 / (MAX_GM_VALUE - MIN_GM_VALUE) * (gm_unit - MIN_GM_VALUE);
}
