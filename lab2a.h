/*****************************************************************************
* lab2a.h for Lab2A of ECE 153a at UCSB
* Date of the Last Update:  October 23,2014
*****************************************************************************/

#ifndef lab2a_h
#define lab2a_h
#include "qpn_port.h"

enum FinalLabSignals {
	ENCODER_UP = Q_USER_SIG,
	ENCODER_DOWN,
	ENCODER_CLICK,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_CENTER,
	TICK
};

typedef struct FinalLabTag {               //Lab2A State machine
	QActive super;
	u32 btn_index;
	unsigned int fequency;
} FinalLab;

/* Setup state machines */
/**********************************************************************/
QState Final_initial(FinalLab *me);
QState Final_on(FinalLab *me);
QState Final_main(FinalLab *me);
QState Final_setting(FinalLab *me);
QState Final_debug(FinalLab *me);
QState Final_game(FinalLab *me);
QState Final_pause(FinalLab *me);
QState Final_end(FinalLab *me);
QState Final_gaming(FinalLab *me);

extern FinalLab AO_final;

void Final_ctor(void);

#endif  
