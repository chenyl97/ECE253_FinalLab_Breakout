/*
 * collision_check.h
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#ifndef SRC_MATH_COLLISION_H_
#define SRC_MATH_COLLISION_H_

#include "vector.h"
#include "segment.h"
#include "aabb.h"

#define EPS 1e-8

/**
 * Parameters:
 * - segment 		- segment for collision
 * - ball			- ball data
 * - max_travel		- remaining travel time
 * Results:
 * - collision		- collision point
 * - travel_time	- time traveled
 * Return: if collision happens (true) or not (false)
 * */
u8 intersectAndReflect(Segment segment, Ball* ball, float max_travel,
		Vector* collision, float* travel_len, Vector* reflect);

#endif /* SRC_MATH_COLLISION_H_ */
