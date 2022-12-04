/*
 * segment.h
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#ifndef SRC_MATH_SEGMENT_H_
#define SRC_MATH_SEGMENT_H_

#include "vector.h"

// for edges
typedef struct SegmentTag {
	float x1;
	float y1;
	float x2;
	float y2;
	float len;
} Segment;

Segment createSegment(Vector pos, Vector velocity);
Segment fromAABBCoord(int x1, int y1, int x2, int y2);
float distance(Segment segment, Vector point);

#endif /* SRC_MATH_SEGMENT_H_ */
