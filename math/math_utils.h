/*
 * math_utils.h
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#ifndef SRC_MATH_MATH_UTILS_H_
#define SRC_MATH_MATH_UTILS_H_

#include "vector.h"
#include "segment.h"

void precompute();
float fast_sin(float radian);
float fast_cos(float radian);

float length(float x, float y);
float ABS(float x);

#endif /* SRC_MATH_MATH_UTILS_H_ */
