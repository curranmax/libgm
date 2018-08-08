
#include "gm_utils.h"

#define FORTY_DEGREES_IN_RADIANS 0.698132

int thetaToGMUnit(float theta) {
	return (MAX_GM_VALUE - MIN_GM_VALUE) / FORTY_DEGREES_IN_RADIANS * theta + MIN_GM_VALUE;
}

float GMUnitToTheta(int gm_unit) {
	return FORTY_DEGREES_IN_RADIANS / (MAX_GM_VALUE - MIN_GM_VALUE) * (gm_unit - MIN_GM_VALUE);
}
