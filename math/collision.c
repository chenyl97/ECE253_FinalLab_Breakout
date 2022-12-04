/*
 * collision.c
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#include "collision.h"
#include "math_utils.h"
#include <math.h>

u8 intersectLineV(float x, const Ball* ball, float* cy, float* travel_len) {
	float px = ball->pos.x;
	float py = ball->pos.y;
	float r = ball->radius;
	float vx = ball->velocity.x;
	float vy = ball->velocity.y;
	float dxr = ABS(x - px) - r;
	if (dxr < 0) {
		return 1;
	}
	float p = vy * dxr / ABS(vx) + py;
	*cy = p;
	*travel_len = length(dxr, p);
	return 0;
}

u8 intersectLineH(float y, const Ball* ball, float* cx, float* travel_len) {
	float px = ball->pos.x;
	float py = ball->pos.y;
	float r = ball->radius;
	float vx = ball->velocity.x;
	float vy = ball->velocity.y;
	float dyr = ABS(y - py) - r;
	if (dyr < 0) {
		return 1;
	}
	float p = vx * dyr / ABS(vy) + px;
	*cx = p;
	*travel_len = length(dyr, p);
	return 0;
}

/**
 * assume collision point is on the segment
 * return 0: no collision
 * return 1: collide vertical
 * return 2: collide horizontal
 * return 3: hit corner
 * */
u8 intersectLine(Segment segment, const Ball* ball, float max_travel,
		Vector* collision, float* len) {
	float c;
	if (segment.x1 == segment.x2) {
		if (intersectLineV(segment.x1, ball, &c, len))
			return 3;
		if (*len > max_travel)
			return 0;
		if ((segment.y1 < c) && (c < segment.y2)) {
			collision->x = segment.x1;
			collision->y = c;
			return 1;
		}
		return 3;
	} else if (segment.y1 == segment.y2) {
		if (intersectLineH(segment.y1, ball, &c, len))
			return 3;
		if (*len > max_travel)
			return 0;
		if ((segment.x1 < c) && (c < segment.x2)) {
			collision->y = segment.y1;
			collision->x = c;
			return 2;
		}
		return 3;
	}
	return 0;
}

/** if collision point is not on the segment, check end point collision
 * returns travel_len
 * if answer is smaller than 0, it means collision does not happen */
float intersectPoint(float x, float y, const Ball* ball) {
	float r = ball->radius;
	Segment path = createSegment(ball->pos, ball->velocity);
	float h = distance(path, newVector(x, y));
	if (r < h) {
		return -1;
	}
	float l = length(ball->pos.x - x, ball->pos.y - y);
	float p = sqrt(l * l - h * h);
	float q = sqrt(r * r - h * h);
	return p - q;
}

void corner_reflect(Ball* ball, Vector* collision)
{
	float v1x = collision->x - ball->pos.x;
	float v1y = collision->y - ball->pos.y;
	//int x=0;
	//int y=0;
	//float v2x = x - collision->x;
	//float v2y = y - collision->y;
	float v2x = (v1y*v1y)/((v1x*v1x+v1y*v1y));
	float v2y = 1 - v2x*v2x;
	//int x = v2x - collision->x;
	//int y = v2y - collision->y;
	//ball->velocity.x = x-collision->x;
	//ball->velocity.y = y-collision->y;
	float CP = v1x*v2y-v1y*v2x;
	//v2x*v3y-v2y*v3x=;
}

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
		Vector* collision, float* len, Vector* reflect) {
	u8 intersect = intersectLine(segment, ball, max_travel, collision, len);
	if (intersect == 0) {
		return 0;
	} else if (intersect == 1) {//collide vertical
		//TODO reflect velocity
		ball->velocity.x=-ball->velocity.x;

		return 1;
	} else if (intersect == 2) {//collide horizontal
		//TODO reflect velocity
		ball->velocity.y=-ball->velocity.y;

		return 1;
	} else if (intersect == 3) {
		u8 ip_1 = intersectPoint(segment.x1, segment.y1, ball);
		u8 ip_2 = intersectPoint(segment.x2, segment.y2, ball);
		if (ip_1 > max_travel) {
			ip_1 = -1;
		}
		if (ip_2 > max_travel) {
			ip_2 = -1;
		}
		if (ip_1 >= 0 && (ip_2 < 0 || ip_1 < ip_2)) {
			collision->y = segment.y1;
			collision->x = segment.x1;
			*len = ip_1;
			//TODO reflect
			corner_reflect(ball,collision);
			return 1;
		} else if (ip_2 >= 0 && (ip_1 < 0 || ip_2 <= ip_1)) {
			collision->y = segment.y2;
			collision->x = segment.x2;
			*len = ip_2;
			// TODO reflect
			corner_reflect(ball,collision);
			return 1;
		}

	}
	return 0;
}

