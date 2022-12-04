/*
 * vector.c
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#include "vector.h"
#include "math_utils.h"
#include <math.h>

Vector newVector(float x, float y) {
	Vector ans;
	ans.x = x;
	ans.y = y;
	return ans;
}

float getLength(Vector vec) {
	return length(vec.x, vec.y);
}

Vector normalize(Vector vec) {
	float factor = 1 / getLength(vec);
	vec.x = vec.x * factor;
	vec.y = vec.y * factor;
	return vec;
}

Vector scale(Vector vec, float scale) {
	vec.x = vec.x * scale;
	vec.y = vec.y * scale;
	return vec;
}

Vector add(Vector a, Vector b) {
	a.x += b.x;
	a.y += b.y;
	return a;
}

Vector subtract(Vector a, Vector b) {
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

float crossProduct(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}

float dotProduct(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}
