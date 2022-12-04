/*
 * game.h
 *
 *  Created on: Nov 30, 2022
 *      Author: shang-hsun
 */
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "hardware/bsp.h"
#include "hardware/lcd.h"

#define BRICK_LENGTH 23
#define BRICK_WIDTH 8
#define BRICK_COLOUR_1 Purple
#define BRICK_COLOUR_2 Blue
#define BRICK_COLOUR_3 Cyan
#define BRICK_COLOUR_4 DarkGreen
#define BRICK_COLOUR_5 Green
#define BRICK_COLOUR_6 Yellow
#define BRICK_COLOUR_7 Red

#define PADDLE_Y 5
#define PADDLE_WIDTH 10
#define PADDLE_COLOUR White
#define PADDLE_ANGLE 0.1 //10% of the paddle
#define PADDLE_EASY 60
#define PADDLE_MEDIUM 40
#define PADDLE_HARD 20
#define INCREMENT_BALL_SPEED 1.2
#define DECREMENT_BALL_SPEED 0.8

#define BALL_COLOUR White
#define BALL_DIAMETER 4
#define BALL_MAX_SPEED 2
#define BACKGROUND_COLOUR Black

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#ifndef SRC_GAME_H_
#define SRC_GAME_H_

struct Brick
{
	float brick_x;
	float brick_y;
	bool brick_hit;
	bool brick_drawn;
};

typedef struct PaddleTag {

	float x;
	float legnth;
	u8 direction;
	u32 speed;
}Paddle;



#endif /* SRC_GAME_H_ */
