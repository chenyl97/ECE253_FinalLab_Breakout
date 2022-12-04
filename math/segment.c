/*
 * segment.c
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#include "segment.h"
#include "math_utils.h"
#include <math.h>

Segment createSegment(Vector pos, Vector velocity) {
	Segment ans;
	ans.x1 = pos.x;
	ans.y1 = pos.y;
	ans.x2 = pos.x + velocity.x;
	ans.y2 = pos.y + velocity.y;
	ans.len = getLength(velocity);
	return ans;
}

Segment fromAABBCoord(int x1, int y1, int x2, int y2) {
	Segment ans;
	ans.x1 = x1;
	ans.y1 = y1;
	ans.x2 = x2;
	ans.y2 = y2;
	ans.len = ABS(x2 - x1) + ABS(y2 - y1);
	return ans;
}

float distance(Segment segment, Vector point) {
	float x1 = segment.x1;
	float y1 = segment.y1;
	float x2 = segment.x2;
	float y2 = segment.y2;
	float x0 = point.x;
	float y0 = point.y;
	return (x2 - x1) * (y1 - y0) - (x1 - x0) * (y2 - y1) / segment.len;
}
