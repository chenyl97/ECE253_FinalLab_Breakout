/*
 * math_structs.h
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#ifndef SRC_MATH_VECTOR_H_
#define SRC_MATH_VECTOR_H_

// for position and velocity
typedef struct VectorTag {
	float x;
	float y;
} Vector;

Vector newVector(float x, float y);
float getLength(Vector vec);
Vector normalize(Vector vec);
Vector scale(Vector vec, float scale);
Vector add(Vector a, Vector b);
Vector subtract(Vector a, Vector b);
float crossProduct(Vector a, Vector b);
float dotProduct(Vector a, Vector b);

#endif /* SRC_MATH_VECTOR_H_ */
