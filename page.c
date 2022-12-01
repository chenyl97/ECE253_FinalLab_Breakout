#include "page.h"
#include "lab2a.h"
#include "lcd.h"
#include "hsm.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

static Text main_text_arr[2];
static Button main_btn_arr[3];
static Text config_text_arr[4];
static Slider config_slider_arr[3];
static Button config_back_btn;

static Text pause_text_arr;
static Button pause_btn_arr[2];
static Text end_text_arr;
static Button end_btn_arr[2];

Page page_main;
Page page_config;
Page page_debug;
Page page_pause;
Page page_end;

// Init structs

void initColor(Color* color, u8 r, u8 g, u8 b) {
	color->r = r;
	color->g = g;
	color->b = b;
}

void initContent(Content* obj, u32 x, u32 y, u32 w, u32 h, u8* font) {
	obj->x = x;
	obj->y = y;
	obj->w = w;
	obj->h = h;
}

void initText(Text* text, char* str, u8* font) {
	text->text = str;
	text->super.font = font;

	u8 len = 0;
	while (str[len] != '\0')
		len++;
	text->length = len - 1;

	u32 text_w = ((u32)len) * ((u32)font[0]);
	u32 text_h = font[1];

	text->text_x = ((text->super.w - text_w) >> 1) + text->super.x;
	text->text_x = ((text->super.h - text_h) >> 1) + text->super.y;

}

void initButton(Button* btn, char* str) {
	btn->text = str;

	u8 len = 0;
	while (str[len] != '\0')
		len++;
	btn->length = len - 1;

	u32 text_w = ((u32)len) * ((u32)font[0]);
	u32 text_h = font[1];

	btn->text_x = ((btn->super.w - text_w) >> 1) + btn->super.x;
	btn->text_y = ((btn->super.h - text_h) >> 1) + btn->super.y;

}

void initSlider(Slider* slider, char* str, u32 low, u32 high){
	slider->text = str;
	slider->low = low;
	slider->high = high;

	u32 text_w = ((u32)len) * ((u32)font[0]);
	u32 text_h = font[1];

	slider->value = (u32) ((high+low) >> 1);
	
	slider->text_x = ((slider->super.w - text_w) >> 1) + slider->super.x;
	slider->text_y = ((slider->super.h - text_h) >> 1) + slider->super.y + 10;
}

void arrange_btns(u8 content_num, u32 w, u32 h, u8* font, Button* BtnArr) {
	u32 margin; 
	margin = (SCREEN_HEIGHT-80-h*content_num)/content_num;
	for (int i=0; i<content_num; i++) {
		BtnArr[i].super.x = ((SCREEN_WIDTH-w) >> 1);
		BtnArr[i].super.y = ((SCREEN_HEIGHT-h) >> 1) + i*(margin+h);
		BtnArr[i].super.w = w;
		BtnArr[i].super.h = h;
		BtnArr[i].super.font = font;
	}
}

void arrange_sliders(u8 content_num, u32 w, u32 h, u8* font, Slider* SliderArr) {
	u32 margin; 

	u32 text_w = ((u32)len) * ((u32)font[0]);
	u32 text_h = font[1];

	margin = (SCREEN_HEIGHT-80-(h+text_h+10)*content_num)/content_num;

	for (int i=0; i<content_num; i++) {
		SliderArr[i].super.x = ((SCREEN_WIDTH-w) >> 1);
		SliderArr[i].super.y = ((SCREEN_HEIGHT-h) >> 1) + i*(margin+h+text_h+10);
		SliderArr[i].super.w = w;
		SliderArr[i].super.h = h;
		SliderArr[i].super.font = font;
	}
}

// Init Pages
	// Text
	// - initContent
	// - initColor: fg
	// - initColor: bg
	// - initText

	// Button
	// - initContent
	// - initColor: fg
	// - initColor: bg
	// - initButton
	// - initColor: focus
	// - initColor: pressed
	// - set target

void initPageMain() {
	page_main.canGoBack = 0;
	page_main.textCount = 2;
	page_main.buttonCount = 3;
	page_main.index = 0;

	
	initContent(&main_text_arr[0].super, 20, 10, 200, 50);
    initColor(&main_text_arr[0].super.bg, 255, 255, 255);
	initColor(&main_text_arr[0].super.fg, 0, 0, 0);
    initText(&main_text_arr[0].text, "BREAKOUT", BigFont);

    initContent(&main_text_arr[1].super, 20, 50, 200, 30);
    initColor(&main_text_arr[1].super.bg, 255, 255, 255);
	initColor(&main_text_arr[1].super.fg, 0, 0, 0);
    initText(&main_text_arr[1].text, "by Yiliang and Shang-Hsun", SmallFont);
    

    // BTN
    arrange_btns(3, 120, 30, SmallFont ,main_btn_arr);
	initColor(&main_btn_arr[0].super.bg, 255, 255, 255);
	initColor(&main_btn_arr[0].super.fg, 0, 0, 0);
    initButton(&main_btn_arr[0].text, "Start Game");
    initColor(&main_btn_arr[0].focus, 200, 200, 200);
    initColor(&main_btn_arr[0].press, 100, 100, 100);
    main_btn_arr[0].target = (QStateHandler) &Final_game;

    initColor(&main_btn_arr[1].super.bg, 255, 255, 255);
	initColor(&main_btn_arr[1].super.fg, 0, 0, 0);
    initButton(&main_btn_arr[1].text, "Setting");
    initColor(&main_btn_arr[1].focus, 200, 200, 200);
    initColor(&main_btn_arr[1].press, 100, 100, 100);
    main_btn_arr[1].target = (QStateHandler) &Final_setting;

    page_main.textArr = main_text_arr;
	page_main.buttonArr = main_btn_arr;

}

void initPageConfig() {
	page_config.canGoBack = 1;
	page_config.textCount = 1;
	page_config.sliderCount = 3;
	page_config.index = 0;

	initContent(&config_text_arr[0].super, 20, 10, 200, 50);
    initColor(&config_text_arr[0].super.bg, 255, 255, 255);
	initColor(&config_text_arr[0].super.fg, 0, 0, 0);
    initText(&config_text_arr[0].text, "Setting", BigFont);
    
    // slide bar
	arrange_sliders(3, 120, 30, SmallFont, config_slider_arr)
    initColor(&config_slider_arr[0].super.bg, 255, 255, 255);
	initColor(&config_slider_arr[0].super.fg, 0, 0, 0);
    initSlider(&config_slider_arr[0], "Ball Speed", 1, 5);
	initColor(&config_slider_arr[0].focus, 200, 200, 200);

    initColor(&config_slider_arr[1].super.bg, 255, 255, 255);
	initColor(&config_slider_arr[1].super.fg, 0, 0, 0);
    initSlider(&config_slider_arr[1], "Paddle Speed", 1, 5);
	initColor(&config_slider_arr[1].focus, 200, 200, 200);

    initColor(&config_slider_arr[1].super.bg, 255, 255, 255);
	initColor(&config_slider_arr[1].super.fg, 0, 0, 0);
    initSlider(&config_slider_arr[1], "Paddle Lengh", 1, 5);
	initColor(&config_slider_arr[1].focus, 200, 200, 200);

	//back button
	initContent(&config_back_btn.super, 20, 10, 50, 50);
    initColor(&config_back_btn.super.bg, 255, 255, 255);
	initColor(&config_back_btn.super.fg, 0, 0, 0);
    initButton(&config_back_btn.text, "<");
    initColor(&config_back_btn.focus, 200, 200, 200);
    initColor(&config_back_btn.press, 100, 100, 100);
	config_back_btn.super.font = BigFont;

    page_config.textArr = config_text_arr;
	page_config.sliderArr = config_slider_arr;


}

void initPagePause() {
    page_pause.canGoBack = 0;
	page_pause.textCount = 1;
	page_pause.buttonCount = 2;
	page_pause.index = 0;
	
	initContent(&pause_text_arr.super, 20, 10, 200, 50);
    initColor(&pause_text_arr.super.bg, 255, 255, 255);
	initColor(&pause_text_arr.super.fg, 0, 0, 0);
    initText(&pause_text_arr.text, "Pause", BigFont);
    
    // BTN
    arrange_btns(2, 120, 40, SmallFont, pause_btn_arr);
    initColor(&pause_btn_arr[0].super.bg, 255, 255, 255);
	initColor(&pause_btn_arr[0].super.fg, 0, 0, 0);
    initButton(&pause_btn_arr[0].text, "Resume");
    initColor(&pause_btn_arr[0].focus, 200, 200, 200);
    initColor(&pause_btn_arr[0].press, 100, 100, 100);
    pause_btn_arr[0].target = (QStateHandler) &Final_gaming;

    initColor(&pause_btn_arr[1].super.bg, 255, 255, 255);
	initColor(&pause_btn_arr[1].super.fg, 0, 0, 0);
    initButton(&pause_btn_arr[1].text, "Exit");
    initColor(&pause_btn_arr[1].focus, 200, 200, 200);
    initColor(&pause_btn_arr[1].press, 100, 100, 100);
    pause_btn_arr[1].target = (QStateHandler) &Final_main;

    page_pause.textArr = pause_text_arr;
	page_pause.buttonArr = pause_btn_arr;

}

void initPageEnd() {
	page_end.canGoBack = 0;
	page_end.textCount = 1;
	page_end.buttonCount = 2;
	page_end.index = 0;    
	
	initContent(&end_text_arr.super, 20, 10, 200, 50);
    initColor(&end_text_arr.super.bg, 255, 255, 255);
	initColor(&end_text_arr.super.fg, 0, 0, 0);
    initText(&end_text_arr.text, "Pause", BigFont);
    
    // BTN
    arrange_btns(2, 120, 40, SmallFont, end_btn_arr);
    initColor(&end_btn_arr[0].super.bg, 255, 255, 255);
	initColor(&end_btn_arr[0].super.fg, 0, 0, 0);
    initButton(&end_btn_arr[0].text, "Restart", SmallFont);
    initColor(&end_btn_arr[0].focus, 200, 200, 200);
    initColor(&end_btn_arr[0].press, 100, 100, 100);
    end_btn_arr[0].target = (QStateHandler) &Final_gaming;

    initColor(&end_btn_arr[1].super.bg, 255, 255, 255);
	initColor(&end_btn_arr[1].super.fg, 0, 0, 0);
    initButton(&end_btn_arr[1].text, "Exit", SmallFont);
    initColor(&end_btn_arr[1].focus, 200, 200, 200);
    initColor(&end_btn_arr[1].press, 100, 100, 100);
    end_btn_arr[1].target = (QStateHandler) &Final_main;

    page_end.textArr = pause_text_arr;
	page_end.buttonArr = pause_btn_arr;


}

void initPageDebug() {

}

void initAllPages() {
	initPageMain();
	initPageConfig();
	initPagePause();
	//initPageDebug();
	initPageEnd();
}

QState HSM_template_BTN(FinalLab *me, Page* page, void* parent) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			page->index = 0;
			drawPage(page);
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			erasePage(page);
			return Q_HANDLED();
		}
		case Q_INIT_SIG: {
			return Q_HANDLED();
		}
		case ENCODER_UP:
		case ENCODER_DOWN:
		case ENCODER_CLICK:
		case BUTTON_RIGHT:
		case TICK: {
			return Q_HANDLED();
		}
		case BUTTON_UP: {
			if (page->index > 0)
				page->index--;
			drawPage(page);
			return Q_HANDLED();
		}
		case BUTTON_DOWN: {
			if (page->index < page->buttonCount - 1)
				page->index++;
			drawPage(page);
			return Q_HANDLED();
		}
		case BUTTON_CENTER: {
			return Q_TRAN(page->buttonArr[page->index].target);
		}

		case BUTTON_LEFT: {
			return Q_TRAN(&Final_main);
		}
	}
	return Q_SUPER(parent);

}

QState HSM_template_slider(FinalLab *me, Page* page, void* parent) {
	switch (Q_SIG(me)) {
		case Q_ENTRY_SIG: {
			page->index = 0;
			drawPage(page);
			return Q_HANDLED();
		}
		case Q_EXIT_SIG: {
			erasePage(page);
			return Q_HANDLED();
		}
		case Q_INIT_SIG: {
			return Q_HANDLED();
		}
		case ENCODER_CLICK:
		case BUTTON_RIGHT:
		case BUTTON_CENTER:
		case TICK: {
			return Q_HANDLED();
		}
		case BUTTON_UP: {
			if (page->index > 0)
				page->index--;
			drawPage(page);
			return Q_HANDLED();
		}
		case BUTTON_DOWN: {
			if (page->index < page->sliderCount - 1)
				page->index++;
			drawPage(page);
			return Q_HANDLED();
		}
		case BUTTON_LEFT: {
			return Q_TRAN(&Final_main);
		}

		case ENCODER_UP:{
			if (page->sliderArr[page->index] < page->sliderArr[page->index].high)
				page->sliderArr[page->index]++;
			return Q_HANDLED();
		}
		case ENCODER_DOWN:{
			if (page->sliderArr[page->index] > page->sliderArr[page->index].low)
				page->sliderArr[page->index]--;
			return Q_HANDLED();
		}
	}
	return Q_SUPER(parent);

}
