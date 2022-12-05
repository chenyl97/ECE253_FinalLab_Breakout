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
#include "draw/draw.h"
#include "page.h"

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
#define PADDLE_L_EASY 60
#define PADDLE_L_MEDIUM 40
#define PADDLE_L_HARD 20
#define PADDLE_V_LOW 5
#define PADDLE_V_MEDIUM 10
#define PADDLE_V_HIGH 20
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
	Content super;
	u8 direction;
	u32 speed;
	u32 x_max;
}Paddle;

extern Paddle paddle;

void init_paddle(Paddle* obj);
void paddle_draw(Paddle* paddle);
void paddle_move(Paddle* obj, u8 dir);
void init_game();

#endif /* SRC_GAME_H_ */
