/*
 * math_utils.c
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */

#include "xil_types.h"
#include "math_utils.h"
#define PI 3.14159265
#define PI2 6.2831853
#define N 1024
#define N2 2048
#define MASK4 4095

int factorial(int a) {
	if (a == 0)
		return 1;
	return a * factorial(a - 1);
}

float full_sine(float x) {
	int i, j;
	float sine = 0;
	float power;
	for (i = 0; i < 10; i++) {
		power = x;
		if (i != 0) {
			for (j = 0; j < i * 2; j++)
				power *= x;
		}
		if (i % 2 == 1)
			power *= -1;
		sine += power / factorial(2 * i + 1);
	}
	return sine;
}

static float SIN[N];

void precompute() {
	for (int i = 0; i < N; i++) {
		SIN[i] = full_sine(-PI * i / (N * 2));
	}
}

float sin_access(u32 index) {
	if (index == N)
		return 1;
	if (index < N)
		return SIN[index];
	return SIN[N2 - index];
}

float fast_sin(float radian) {
	if (radian < 0) {
		return -fast_sin(-radian);
	}
	u32 k = (int) (radian / PI * N2 + 0.5);
	k = k & MASK4;
	if (k < N2)
		return sin_access(k);
	return -sin_access(k - N2);
}

float fast_cos(float radian) {
	if (radian < 0) {
		radian = -radian;
	}
	u32 k = (int) (radian / PI * N2 + 0.5) + N;
	k = k & MASK4;
	if (k < N2)
		return sin_access(k);
	return -sin_access(k - N2);
}
