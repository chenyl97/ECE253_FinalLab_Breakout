#include <stdio.h>
#include <math.h>
#include "bsp.h"
#include "lcd.h"
#include "game.h"
#include <stdbool.h>
#include "qpn_port.h"
#include "lab2a.h"

float paddle_x;
float paddle_length;
float PADDLE_SPEED = 1.5;
bool going_left;
bool going_right;

/*************************Method to draw the paddle on the screen*************************/
void paddle_draw(float x)
{
	//GLCD_DrawRect(PADDLE_Y,x_drawn,PADDLE_WIDTH,length,BACKGROUND_COLOUR);	//cancels the paddle of the previous cycle		
	setColor(0,120,0);
	//drawHLine(x-20, 10, 40);
	fillRect(x,10,40,10,1);
	//GLCD_DrawRect(PADDLE_Y,x,PADDLE_WIDTH,length,PADDLE_COLOUR);		//displays the paddle after its movement
	setColor(0,255,0);
	//drawHLine(x-20, 10, 40);
	fillRect(x,10,40,10,1);
}

/*************************Method to make the paddle move*************************/
void paddle_move(bool direction_left,bool direction_right,int x_ball)
{
	if(x_ball!=-1)
	{//automatic mode
		paddle_x = x_ball;
		if (paddle_x <= 0)
			paddle_x = 0;
		else if (paddle_x+paddle_length > SCREEN_HEIGHT)
			paddle_x = SCREEN_HEIGHT-paddle_length;
	}
	if (direction_left == 1 && direction_right == 0)
	{//means left click
		if (paddle_x <= 0){				//paddle has reached the left side of the screen...do nothing instead of moving the paddle
			going_left = false;
			going_right = false;
			paddle_x = 0;
		}
		else{		
			going_left = true;
			going_right = false;
			paddle_x -= PADDLE_SPEED;//*0.65;		//GPIO read problem, coefficient to fix it
		}
	}
	else if (direction_left == 0 && direction_right == 1)
	{//means right click
		if (paddle_x + paddle_length >= SCREEN_HEIGHT)
		{				//paddle has reached the right side of the screen...do nothing instead of moving the paddle
			going_left = false;//in case both buttons were pressed
			going_right = false;
			paddle_x = SCREEN_HEIGHT-paddle_length;
		}
		else
		{
			going_left = false;
			going_right = true;
			paddle_x += PADDLE_SPEED;
		}
	}
	else
	{//in all other cases, paddle does not move! This to avoid problems
		going_left = false;//in case both buttons were pressed
		going_right = false;
	}
}

void set_difficulty(u8 diff){
	switch(diff){
		case 1: 								//easy level
			paddle_length = PADDLE_EASY;
			paddle_x = (SCREEN_HEIGHT-PADDLE_EASY)/2;
			break;
		case 2: 								//medium
			paddle_length = PADDLE_MEDIUM;
			paddle_x = (SCREEN_HEIGHT-PADDLE_MEDIUM)/2;
			break;
		case 3: 								//hard
			paddle_length = PADDLE_HARD;
			paddle_x = (SCREEN_HEIGHT-PADDLE_HARD)/2;
			break;
		default:								//error
			paddle_length = 0;
			paddle_x = -1;
	}
}

struct Brick brick[30];

/*************************Method to set Bricks after cration*************************/	
void brick_set(struct Brick brick,float x,float y)
{
	brick.brick_x = x;
	brick.brick_y = y;
	brick.brick_hit = false;
	brick.brick_drawn = false;
}

/*************************Method to draw the bricks*************************/
void brick_draw(struct Brick brick)
{
	if (!brick.brick_drawn)
	{						
		if (brick.brick_hit)
		{//GLCD_DrawRect(y,x,10,40,Gray);	//if the ball hits it, it is "deleted" (i.e. coloured by the background colour
			setColor(120,0,0);
			fillRect(brick.brick_x,brick.brick_y,10,40,1);
			//for (int h = 0; h<10; h++)
			//{
				//drawHLine(brick.brick_x, brick.brick_y, 40);
			//}
		}

		else
		{//GLCD_DrawRect(y,x,10,40,colour);			//if not, it is displayed
			setColor(255,0,0);
			fillRect(brick.brick_x,brick.brick_y,10,40,1);
			//for (int h = 0; h<10; h++)
			//{
				//drawHLine(brick.brick_x, brick.brick_y, 40);
			//}
		}
		brick.brick_drawn = true;
	}
}

float ball_x;
float ball_y;
float ball_old_x;
float ball_old_y;
float ball_speed_x;
float ball_speed_y;
float ball_x_drawn;
float ball_y_drawn;
float ball_top;
float ball_bottom;
float ball_right;
float ball_left;

/*************************Method to draw the ball*************************/
void ball_draw(float x,float y)
{
    //GLCD_DrawRect(y_drawn,x_drawn,BALL_DIAMETER,BALL_DIAMETER,BACKGROUND_COLOUR);
	//deletes the ball of the previous cycle, before its movement
	setColor(0,0,120);
    drawHLine(x-2,y-7,5);
    drawHLine(x-4,y-6,8);
    drawHLine(x-5,y-5,10);
    drawHLine(x-6,y-4,12);
    drawHLine(x-6,y-3,12);
    drawHLine(x-7,y-2,14);
    drawHLine(x-7,y-1,14);
    drawHLine(x-7,y-0,14);
    drawHLine(x-7,y-1,14);
    drawHLine(x-7,y-2,14);
    drawHLine(x-6,y-3,12);
    drawHLine(x-6,y-4,12);
    drawHLine(x-5,y-5,10);
    drawHLine(x-4,y-6,5);
    drawHLine(x-2,y-7,8);
    //GLCD_DrawRect(y,x,BALL_DIAMETER,BALL_DIAMETER,BALL_COLOUR);
	//displays the ball after its movement
	setColor(0,0,255);
    drawHLine(x-2,y-7,5);
    drawHLine(x-4,y-6,8);
    drawHLine(x-5,y-5,10);
    drawHLine(x-6,y-4,12);
    drawHLine(x-6,y-3,12);
    drawHLine(x-7,y-2,14);
    drawHLine(x-7,y-1,14);
    drawHLine(x-7,y-0,14);
    drawHLine(x-7,y-1,14);
    drawHLine(x-7,y-2,14);
    drawHLine(x-6,y-3,12);
    drawHLine(x-6,y-4,12);
    drawHLine(x-5,y-5,10);
    drawHLine(x-4,y-6,5);
    drawHLine(x-2,y-7,8);

    ball_x_drawn = x;
    ball_y_drawn = y;
}

//uses speed parameters to move the ball inside the screen
void ball_move(float x,float y)
{
	ball_old_x = x;
	ball_old_y = y;
    
    if (ball_speed_y > BALL_MAX_SPEED)
    	ball_speed_y = BALL_MAX_SPEED;//to avoid uncorrect behaviours of the ball

    ball_x += ball_speed_x;
    ball_y += ball_speed_y;

    // set ball borders
    ball_top = y + BALL_DIAMETER;
    ball_bottom = y - BALL_DIAMETER;
    ball_left = x - BALL_DIAMETER;
    ball_right = x + BALL_DIAMETER;

    //check x axis
    if (ball_right >= SCREEN_HEIGHT)
    {//right border of the screen
    	ball_x = SCREEN_HEIGHT - BALL_DIAMETER;
    	ball_speed_x = -ball_speed_x;				//bounces
    }
    else if (ball_left <= 0){ 				//left border of the screen
    	ball_x = 0;
    	ball_speed_x = -ball_speed_x;				//bounces
    }
    
    //check y axis
    if (ball_top >= SCREEN_WIDTH)
    { 			//top border of the screen
        y = SCREEN_WIDTH - BALL_DIAMETER;
        ball_speed_y = -ball_speed_y;				//bounces
    }
    
    //check if hits the paddle
    else if (ball_bottom <= PADDLE_WIDTH+PADDLE_Y	&& ( ball_right>=paddle_x && ball_left<=(paddle_x+paddle_length)))
    {
    	ball_y = PADDLE_WIDTH+PADDLE_Y; 											//put the ball again on top of the paddle
        //computes the angles of the paddle
        float left_angle = paddle_x + paddle_length * PADDLE_ANGLE;
        float right_angle = paddle_x + paddle_length * (1-PADDLE_ANGLE);
        
        //if the paddle goes in the opposite direction of the ball...
        if((going_left==true && ball_speed_x<0) || (going_right==true && ball_speed_x>0))
        	ball_speed_y = -DECREMENT_BALL_SPEED * ball_speed_y;						//decreases the speed
        
        //... or if it goes in the same direction
        else if((going_left==true && ball_speed_x>0) || (going_right==true && ball_speed_x<0))
        	ball_speed_y = -INCREMENT_BALL_SPEED * ball_speed_y;						//increase the speed
        else 
        	ball_speed_y = -ball_speed_y;										//just bounces on the paddle
        
        //check the angles
        if (ball_right <= left_angle ){ 							//forces ball to go to LEFT
            if (ball_speed_x > 0)
            	ball_speed_x = -ball_speed_x;
        }
        else if (ball_left >= right_angle){ 							//force ball to go to RIGHT
            if (ball_speed_x < 0)
            	ball_speed_x = -ball_speed_x;
        }
    }		
}

//checks if (x,y) is inside a brick
bool is_inside(float x,float y,struct Brick brick)
{
	if (x >= brick.brick_x && x <= brick.brick_x+BRICK_LENGTH)
		if (y >= brick.brick_y && y < brick.brick_y+BRICK_WIDTH)
			return true;
	return false;
}


/*************************Method to check the collision between ball and bricks*************************/

bool check_collision(struct Brick brick)
{
    bool is = false;//by default, nobody has hit anything
    if(!brick.brick_hit)
    {
        float ball_center_x = ball_x + BALL_DIAMETER/2.0;
        float ball_center_y = ball_y + BALL_DIAMETER/2.0;
        
        int going_up = 0;
        int going_dw = 0;
        int going_lx = 0;
        int going_rx = 0;
        
        if (is_inside(ball_left,ball_top,brick)){				//LEFT-TOP "sensor"
            going_up++;
            going_lx++;
        }
        if (is_inside(ball_center_x,ball_top,brick)){ 			//CENTER-TOP "sensor"
            going_up++;
        } 
        if (is_inside(ball_right,ball_top,brick)){ 			//RIGHT-TOP "sensor"
            going_up++;
            going_rx++;
        }
        if (is_inside(ball_left,ball_center_y,brick)){ 			//LEFT-CENTER "sensor"
            going_lx++;
        } 
        if (is_inside(ball_right,ball_center_y,brick)){ 		//RIGHT-CENTER "sensor"
            going_rx++;
        }
        if (is_inside(ball_left,ball_bottom,brick)){ 			//LEFT-BOTTOM "sensor"
            going_lx++;
            going_dw++;
        } 
        if (is_inside(ball_center_x,ball_bottom,brick)){ 		//CENTER-BOTTOM "sensor"
            going_dw++;
        } 
        if (is_inside(ball_right,ball_bottom,brick)){ 			//RIGHT-BOTTOM "sensor"
            going_rx++;
            going_dw++;
        }
        
        if (going_up >= 2)
        {//if 2 sensors touch a brick
            // the ball is coming from BOTTOM
        	brick.brick_hit = true;//brick has been hit
            brick.brick_drawn = false;//to make it become black
            ball_speed_y = -ball_speed_y;//bounces
            is = true;
        }
        else if (going_dw >= 2)
        {
            // the ball is coming from TOP
        	brick.brick_hit = true;
        	brick.brick_drawn = false;
            ball_speed_y = -ball_speed_y;
            is = true;
        }
        else if (going_rx >= 2){
            // the ball is coming from LEFT
        	brick.brick_hit = true;
        	brick.brick_drawn = false;
            ball_speed_x = -ball_speed_x;
            is = true;
        }
        else if (going_lx >= 2){
            // the ball is coming from RIGHT
        	brick.brick_hit = true;
        	brick.brick_drawn = false;
            ball_speed_x = -ball_speed_x;
            is = true;
        }
        
        //if (is)
            //play_sound();//play a note if a brick is hit
    }
    return is;
}

int game_points = 0;

void check_points()
{
		for(int i=0; i<30; i++)
		{//every execution of the method, it checks if the ball touches
			if(check_collision(brick[i]))
			{
				game_points++;
			}
		}

		//check win or loss
		if (ball_y <= 0)
		{ 						//bottom of the screen...YOU LOSE
			//GLCD_SetTextColor(Yellow);
			//GLCD_SetBackColor(Black);
			//const char* str = "YOU LOSE!";
			//GLCD_DisplayString(120,50,1,(unsigned char*)str,PIXELS);
			//play_music(LOSS,LOSS_DURATION);			//sad music
			//system_reset();						//reset of the system writing in the appropriate register
			lcdPrint("LOSE", 100, 100);
		}
		else if(game_points == 30)
		{//no more bricks...YOU WIN
			//GLCD_SetTextColor(Blue);
			//GLCD_SetBackColor(Black);
			//const char* str = "YOU WIN!";
			//GLCD_DisplayString(120,60,1,(unsigned char*)str,PIXELS);
			//play_music(WIN,WIN_DURATION);				//happy music
			//if (pad.self)						//if auto mode
			//	GameInitialization();				//restart game
			//else
			//	system_reset();					//reset of the system writing in the appropriate register
			lcdPrint("WIN", 100, 100);
		}
}

void new_game()
{
	ball_draw(120,120);					//displays the ball
	paddle_draw(120);						//displays the paddle
	for(int i=0; i<30; i++)
	{//displays the bricks (if modified)
		int x=0;
		int y=80;
		brick_set(brick[i],x,y);
		brick_draw(brick[i]);
		if(x<240)
		{
			x=x+40;
		}
		else
		{
			x=0;
			if(y<240)
			{
				y=y+40;
			}
			else
			{
				y=0;
			}
		}
	}
}

void game()
{
	new_game();
	while(1)
	{
		check_points();
		if(game_points<30)
		{
			bool dir_left = 0;
			bool dir_right = 0;

			/*
			switch (Q_SIG())
			{
				case ENCODER_UP:
				{
					dir_left = 1; //checks if the paddle goes left
				}

				case ENCODER_DOWN:
				{
					dir_right = 1;//checks if the paddle goes right
				}
			}
			*/

			paddle_move(dir_left,dir_right, ball_x);	//move it
			paddle_draw(paddle_x);						//displays the paddle
			ball_draw(ball_x,ball_y);					//displays the ball
			for(int i=0; i<30; i++)
			{//displays the bricks (if modified)
				int x=0;
				int y=80;
				brick_set(brick[i],x,y);
				brick_draw(brick[i]);
				if(x<240)
				{
					x=x+40;
				}
				else
				{
					x=0;
					if(y<240)
					{
						y=y+40;
					}
					else
					{
						y=0;
					}
				}
			}
		}
	}
}
