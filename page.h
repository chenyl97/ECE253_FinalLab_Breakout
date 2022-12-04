/*
 * pages.h
 *      Author: cheny
 */

#ifndef SRC_PAGES_H_
#define SRC_PAGES_H_

#include "xil_types.h"

#include "HSM/lab2a.h"


typedef struct ColorTag {
    u8 r;
    u8 g;
    u8 b;
} Color;

typedef struct ContentTag {
    u32 x;
    u32 y;
    u32 w;
    u32 h;
    Color bg;
    Color fg;
    u8* font;
} Content;

typedef struct TextTag {
    Content super;
    char* text;
    u8 length;
    u32 text_x;
    u32 text_y;
    int margin;
} Text;

typedef struct ButtonTag {
    Content super;
    char* text;
    u8 length;
    u32 text_x;
    u32 text_y;
    Color focus;
    Color press;
    QStateHandler target;
} Button;

typedef struct SliderTag {
	Content super;
    char* text;
    u8 length;
	u32 low;
	u32 high;
	u32 value;
	u32 pre_value;
    u32 text_x;
    u32 text_y;
    u32 total_h;
    Color focus;
    Color bar;
} Slider;

typedef struct PageTag {
    u8 canGoBack;
	u8 textCount;
    u8 buttonCount;
    u8 sliderCount;
    Text* textArr;
    Button* buttonArr;
    Slider* sliderArr;
    // mutable
    u8 index;
} Page;

extern Page page_main;
extern Page page_config;
extern Page page_debug;
extern Page page_pause;
extern Page page_end;

void initAllPages();
QState HSM_template_button(FinalLab *me, Page* page, void* parent);
QState HSM_template_slider(FinalLab *me, Page* page, void* parent);

#endif /* SRC_PAGES_H_ */
