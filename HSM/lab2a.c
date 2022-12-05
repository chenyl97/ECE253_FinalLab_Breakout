/*****************************************************************************
 * lab2a.c for Lab2A of ECE 153a at UCSB
 * Date of the Last Update:  October 23,2014
 *****************************************************************************/

#define AO_LAB2A
#define AO_FinalProj
#define RIGHT_MAX 100
#define START_POSITION 50
#define DEFAULT_BOARD_V 10
#define DEFAULT_BALL_V 5
#define DEFAULT_DIFFICULTY 3

#include "qpn_port.h"
#include "../hardware/bsp.h"
#include "lab2a.h"
#include "../page.h"
#include <math.h>
#include "../draw/draw.h"
#include "../game.h"



/**********************************************************************/

FinalLab AO_final;



void Final_ctor(void) {
	FinalLab *me = &AO_final;
	QActive_ctor(&me->super, (QStateHandler )&Final_initial);
}

QState Final_initial(FinalLab *me) {
	xil_printf("Initialization\n\r");
	return Q_TRAN(&Final_on);
}

QState Final_on(FinalLab *me) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			return Q_HANDLED();
		}
		case Q_INIT_SIG: {
			return Q_TRAN(&Final_main);
		}
		case ENCODER_UP:
		case ENCODER_DOWN:
		case ENCODER_CLICK:
		case BUTTON_UP:
		case BUTTON_DOWN:
		case BUTTON_LEFT:
		case BUTTON_RIGHT:
		case BUTTON_CENTER:
		case TICK: {
			return Q_HANDLED();
		}
	}
	return Q_SUPER(&QHsm_top);
}

/* Create Lab2A_on state and do any initialization code if needed */
/******************************************************************/

QState Final_main(FinalLab *me) {
	return HSM_template_button(me, &page_main, &Final_on);

}

QState Final_setting(FinalLab *me) {
	return HSM_template_slider(me, &page_config, &Final_on);

}


QState Final_debug(FinalLab *me) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			// game logic initialization
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			return Q_HANDLED();
		}
		case Q_INIT_SIG: {
			return Q_TRAN(&Final_gaming);
		}
		case ENCODER_UP:
		case ENCODER_DOWN:
		case BUTTON_LEFT:
		case TICK:
		case BUTTON_UP:
		case BUTTON_DOWN:
		case ENCODER_CLICK:
		case BUTTON_RIGHT:
		case BUTTON_CENTER: {
			return Q_HANDLED();
		}
	}
	return Q_SUPER(&Final_on);

}
//
QState Final_game(FinalLab *me) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			// game logic initialization
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			return Q_HANDLED();
		}
		case Q_INIT_SIG: {
			init_game();
			paddle_draw(&paddle);
			return Q_TRAN(&Final_gaming);
		}
		case BUTTON_LEFT:
		case BUTTON_UP:
		case BUTTON_DOWN:
		case BUTTON_RIGHT:
		case ENCODER_UP:
		case ENCODER_DOWN:
		case ENCODER_CLICK:
		case BUTTON_CENTER:
		case TICK: {
			return Q_HANDLED();
		}
	}
	return Q_SUPER(&Final_on);

}

QState Final_gaming(FinalLab *me) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			return Q_HANDLED();
		}
		case Q_INIT_SIG: {
			return Q_HANDLED();
		}
		case BUTTON_LEFT:
		case BUTTON_RIGHT:
		case TICK:
		case BUTTON_UP:
		case BUTTON_DOWN:
		case ENCODER_CLICK:{
			return Q_HANDLED();
		}

		case BUTTON_CENTER: {
			return Q_TRAN(&Final_pause);
		}
		case ENCODER_UP: {
			paddle_move(&paddle, 1);
			paddle_draw(&paddle);
			return Q_HANDLED();
		}
		case ENCODER_DOWN: {
			paddle_move(&paddle, -1);
			paddle_draw(&paddle);
			return Q_HANDLED();
		}
	}
	return Q_SUPER(&Final_game);

}

QState Final_pause(FinalLab *me) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			page_pause.index = 0;
			drawPage(&page_pause);
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			erasePage(&page_pause);
			return Q_HANDLED();
		}
		case Q_INIT_SIG: {
			return Q_HANDLED();
		}
		case ENCODER_UP:
		case ENCODER_DOWN:
		case ENCODER_CLICK:
		case BUTTON_RIGHT:
		case BUTTON_LEFT:
		case TICK: {
			return Q_HANDLED();
		}
		case BUTTON_UP: {
			if (page_pause.index > 0) {
				page_pause.index--;
				drawPage(&page_pause);
			}
			return Q_HANDLED();
		}
		case BUTTON_DOWN:{
			if (page_pause.index < page_pause.buttonCount-1) {
				page_pause.index++;
				drawPage(&page_pause);
			}
			return Q_HANDLED();
		}
		case BUTTON_CENTER: {
			erasePage(&page_pause);
			return Q_TRAN(&page_pause.buttonArr[page_pause.index].target);
		}
	}
	return Q_SUPER(&Final_game);

}

QState Final_end(FinalLab *me) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			page_end.index = 0;
			drawPage(&page_end);
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			erasePage(&page_end);
			return Q_HANDLED();
		}
		case Q_INIT_SIG: {
			return Q_HANDLED();
		}
		case ENCODER_UP:
		case ENCODER_DOWN:
		case ENCODER_CLICK:
		case BUTTON_RIGHT:
		case BUTTON_LEFT:
		case TICK: {
			return Q_HANDLED();
		}
		case BUTTON_UP: {
			if (page_end.index > 0) {
				page_end.index--;
				drawPage(&page_end);
			}
			return Q_HANDLED();
		}
		case BUTTON_DOWN:{
			if (page_end.index < page_end.buttonCount-1) {
				page_end.index++;
				drawPage(&page_end);
			}
			return Q_HANDLED();
		}
		case BUTTON_CENTER: {
			erasePage(&page_end);
			return Q_TRAN(&page_end.buttonArr[page_end.index].target);
		}
	}
	return Q_SUPER(&Final_game);

}
