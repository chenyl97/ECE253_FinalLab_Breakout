/*
 * aabb.c
 *
 *  Created on: Dec 1, 2022
 *      Author: shang-hsun
 */

#include "aabb.h"
#include "math_utils.h"
#include <math.h>
#include "collision.h"
#include "vector.h"

#define NO_OVERLAP(a,b,x,y) (a.y<b.x||a.x>b.y)

AABB AABBFromBall(Ball* ball) {
	float px = ball->pos.x;
	float py = ball->pos.y;
	float r = ball->radius;
	float vx = ball->velocity.x;
	float vy = ball->velocity.y;
	AABB aabb;

	aabb.x1 = px - r;
	aabb.x2 = px + r;
	aabb.y1 = py - r;
	aabb.y2 = py + r;

	if (vx > 0) {
		aabb.x2 += vx;
	}
	if (vx < 0) {
		aabb.x1 += vx;
	}
	if (vy > 0) {
		aabb.y2 += vy;
	}
	if (vy < 0) {
		aabb.y1 += vy;
	}
	return aabb;
}

AABB AABBFromBrick(int x, int y) {
	AABB ans;
	ans.x1 = x * BRICK_WIDTH;
	ans.x2 = (x + 1) * BRICK_WIDTH;
	ans.y1 = y * BRICK_HEIGHT;
	ans.y2 = (y + 1) * BRICK_HEIGHT;
	return ans;
}

Segment getSegFromAABB(AABB b, int i) {
	if (i == 0) {
		return fromAABBCoord(b.x1, b.y1, b.x2, b.y1);
	} else if (i == 1) {
		return fromAABBCoord(b.x2, b.y1, b.x2, b.y2);
	} else if (i == 2) {
		return fromAABBCoord(b.x1, b.y2, b.x2, b.y2);
	} else {
		return fromAABBCoord(b.x1, b.y1, b.x1, b.y2);
	}
}

u8 intersectAABB(AABB a, AABB b) {
	return !(NO_OVERLAP(a,b,x1,x2) || NO_OVERLAP(a, b, y1, y2));
}

u8 intersectSegment(AABB a, Segment b) {
	return !(NO_OVERLAP(a,b,x1,x2) || NO_OVERLAP(a, b, y1, y2));
}

u8 segmentOnPath(Segment seg, Ball* ball) {

}

void checkCollision(Brick* bricks, Ball* ball, float max_travel) {
	AABB brick;
	Segment seg;

	AABB aabb = AABBFromBall(ball);
	int coor_x1 = aabb.x1 / BRICK_WIDTH;
	int coor_x2 = aabb.x2 / BRICK_WIDTH + 1;
	int coor_y1 = aabb.y1 / BRICK_HEIGHT;
	int coor_y2 = aabb.y2 / BRICK_HEIGHT + 1;

	float min_dist = max_travel;
	Vector min_cp; // collision point
	Vector min_rf; // reflection angle
	float dist;
	Vector cp;
	Vector rf;

	for (int i = coor_x1; i < coor_x2; i++) {
		for (int j = coor_y1; j < coor_y2; j++) {
			int ind = j * BRICK_X_COUNT + i;
			if (bricks[ind].brick_hit)
				continue;
			brick = AABBFromBrick(i, j);
			if (!intersectAABB(aabb, brick))
				continue;
			for (int m = 0; m < 4; m++) {
				seg = getSegFromAABB(brick, m);
				if (!intersectSegment(aabb, seg))
					continue;
				if (!segmentOnPath(seg, ball))
					continue;
				if (intersectAndReflect(seg, ball, max_travel, &cp, &dist, &rf)) {
					if (dist < min_dist) {
						min_dist = dist;
						min_cp = cp;
						min_rf = rf;
					}
				}
			}
		}
	}
}

