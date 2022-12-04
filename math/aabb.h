/*
 * math_utils.h
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#ifndef SRC_MATH_AABB_H_
#define SRC_MATH_AABB_H_

#include "xil_types.h"
#include "vector.h"
#include "segment.h"
#include "aabb.h"
#include <stdbool.h>

#define BRICK_WIDTH 40
#define BRICK_HEIGHT 10
#define BRICK_X_COUNT 6
#define BRICK_Y_COUNT 5

// for bounding box
typedef struct AABBTag {
	float x1;
	float y1;
	float x2;
	float y2;
} AABB;

typedef struct BrickTag {
	float brick_x;
	float brick_y;
	bool brick_hit;
	bool brick_drawn;
} Brick;

typedef struct BallTag {
	Vector pos;
	Vector velocity;
	float speed;
	float radius;
} Ball;

AABB AABBFromBrick(int x, int y);
AABB AABBFromBall(Ball* ball);
u8 intersectAABB(AABB a, AABB b);
u8 intersectSegment(AABB a, Segment b);
u8 segmentOnPath(Segment seg, Ball* ball);

#endif /* SRC_MATH_AABB_H_ */
