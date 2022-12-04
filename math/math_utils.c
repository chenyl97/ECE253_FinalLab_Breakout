/*
 * math_utils.c
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#include "math_utils.h"
#include <math.h>

float length(float x, float y) {
	return sqrt(x * x + y * y);
}

float ABS(float x) {
	return x > 0 ? x : -x;
}
