#include "page.h"
#include "lab2a.h"
#include "lcd.h"
#include "draw.h"
// Draw

void setColors(Color* fg, Color* bg) {
	setColor(fg->r, fg->g, fg->b);
	setColorBg(bg->r, bg->g, bg->b);
}

void fillContent(Content* obj) {
	fillRect(obj->x, obj->y, obj->w, obj->h, 1);
}

void drawText(Text* obj) {
	setColors(&obj->super.fg, &obj->super.bg);
	fillContent(&obj->super);
	setFont(obj->font);
	lcdPrint(obj->text, obj->text_x, obj->text_y);
}

void drawButton(Button* obj, u32 focused, u32 pressed) {
	// text color
	Color* fg = pressed ? &obj->focus : &obj->super.fg;
	// button color
	Color* bg = pressed ? &obj->press : &obj->super.bg;

	setColors(fg, bg);
	fillContent(&obj->super);
	setFont(obj->font);
	lcdPrint(obj->text, obj->super.x, obj->super.y);
}

void drawSlider(Slider* obj, u32 focused) {
	// text color
	Color* fg = focused ? &obj->focus : &obj->super.fg;
	// button color
	Color* bg = &obj->super.bg;
	// bar color
	Color* br = &obj->bar;

	u32 x = obj->super.x;
	u32 y = obj->super.y;
	u32 w = obj->super.w;
	u32 h = obj->super.h;
	setColors(fg, bg);
	fillRect(x, y, w, h, MARGIN);
	setColors(br, br);
	fillRect(x + MARGIN, y + MARGIN, obj->value, h - (MARGIN << 1), 0);
}

void eraseContent(Content* obj) {
	//TODO
	
}

void drawPage(Page* obj) {
	u8 i;
	for (i = 0; i < obj->textCount; i++) {
		drawText(&obj->textArr[i]);
	}
	for (i = 0; i < obj->buttonCount; i++) {
		drawButton(&obj->buttonArr[i], obj->index == i, 0);
	}
	for (i = 0; i < obj->sliderCount; i++) {
		drawSlider(&obj->sliderArr[i], obj->index == i);
	}

}

void erasePage(Page* obj){
	u8 i;
	for (i = 0; i < obj->textCount; i++) {
		eraseContent(&obj->textArr[i].super);
	}
	for (i = 0; i < obj->buttonCount; i++) {
		eraseContent(&obj->buttonArr[i].super);
	}
	for (i = 0; i < obj->sliderCount; i++) {
		eraseContent(&obj->sliderArr[i].super);
	}
	
}