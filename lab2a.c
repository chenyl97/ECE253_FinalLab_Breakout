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
#include "bsp.h"
#include "lab2a.h"
#include "page.h"
#include <math.h>



int act_position = START_POSITION;//
int board_v = DEFAULT_BOARD_V;//
int ball_v = DEFAULT_BALL_V;//
int difficulty = DEFAULT_DIFFICULTY;//

int stored_value = 0;
int alive = 1;
int Pause = 0;//
int MainVolumeFlag = 0;
int VolumeFlag = 0;
int MainTextFlag = 0;
int TextFlag = 0;


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
	return HSM_template_slider(me, &page_config, &Final_main);

}

QState Final_pause(FinalLab *me){
	return HSM_template_button(me, &page_pause, &Final_game);
}

QState Final_end(FinalLab *me){
	return HSM_template_button(me, &page_end, &Final_game);
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
	case BUTTON_LEFT: {
		return Q_HANDLED();
	}

	case BUTTON_CENTER: {
		return Q_TRAN(&Final_pause);
	}
	case ENCODER_UP:
	case ENCODER_DOWN:
	case BUTTON_RIGHT:
	case TICK:
	case BUTTON_UP:
	case BUTTON_DOWN:
	case ENCODER_CLICK: {
		return Q_HANDLED();
	}

	}
	return Q_SUPER(&Final_on);

}

