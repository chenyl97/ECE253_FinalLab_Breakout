#include "draw.h"

#include "../page.h"
#include <stdlib.h>
#include "../hardware/lcd.h"
#include "../HSM/lab2a.h"


LCDQ qArr[20];
int ptr = 0;

// Draw

void setColors(Color* fg, Color* bg) {
	setColor(fg->r, fg->g, fg->b);
	setColorBg(bg->r, bg->g, bg->b);
}

void fillContent(Content* obj, int margin) {
	//xil_printf("block: %i, %i, %i, %i\r\n", obj->x, obj->y, obj->w, obj->h);
	fillRect(obj->x, obj->y, obj->w, obj->h, margin);
}

void drawText(Text* obj) {
	setColors(&obj->super.fg, &obj->super.bg);
	fillContent(&obj->super, obj->margin);
	setFont(obj->super.font);
	lcdPrint(obj->text, obj->text_x, obj->text_y);
}

void drawButton(Button* obj, u32 focused, u32 pressed) {
	// text color
	Color* fg = focused ? &obj->focus : &obj->super.fg;
	// button color
	Color* bg = pressed ? &obj->press : &obj->super.bg;

	setColors(bg, fg);
	fillContent(&obj->super, 1);
	setFont(obj->super.font);
	lcdPrint(obj->text, obj->text_x, obj->text_y);
}

void drawSlider(Slider* obj, u32 focused) {

	// slider bg color
	Color* bg = &obj->super.bg;
	// bar color
	Color* br = &obj->bar;

	u32 x = obj->super.x;
	u32 y = obj->super.y;
	u32 w = obj->super.w;
	u32 h = obj->super.h;

	if ((obj->pre_value > obj->value) & focused) {
		// text color
		Color* fg = focused ? &obj->focus : &obj->super.fg;
		setColors(fg, bg);
		fillRect(x + (obj->value*(int)(w / (obj->high - obj->low + 1))), y, (int)(w / (obj->high - obj->low + 1)), h, 0);
		setColors(bg, fg);
		setFont(obj->super.font);
		lcdPrint(obj->text, obj->text_x, obj->text_y);
	}
	else if ((obj->pre_value < obj->value) & focused) {
		// text color
		Color* fg = focused ? &obj->focus : &obj->super.fg;
		setColors(br, br);
		fillRect(x + (obj->pre_value*(int)(w / (obj->high - obj->low + 1))), y, (int)(w / (obj->high - obj->low + 1)), h,
				0);
		setColors(bg, fg);
		setFont(obj->super.font);
		lcdPrint(obj->text, obj->text_x, obj->text_y);
	}
	else {
		// text color
		Color* fg = focused ? &obj->focus : &obj->super.fg;
		setColors(fg, bg);
		fillRect(x, y, w, h, 0);
		setColors(br, br);
		fillRect(x, y, obj->value * (int)(w / (obj->high - obj->low + 1)), h, 0);
		setColors(bg, fg);
		setFont(obj->super.font);
		lcdPrint(obj->text, obj->text_x, obj->text_y);
	}

}

int triangles(int x, int y) {
	x = x % 40;
	y = y % 40;
	x = abs(20 - x);
	return y >= 2 * x ? 1 : 0;
}

void plotBackground(int x, int y, int w, int h) {

	//xil_printf("draw background\r\n");
	setColor(0, 0, 95);
	setColorBg(0, 0, 0);
	drawShape(x, y, w, h, &triangles);

	return;
}

void eraseContent(Content* content) {
	setColor(0, 0, 95);
	setColorBg(0, 0, 0);
	drawShape(content->x, content->y, content->w, content->h, &triangles);
}

void drawPage(Page* obj) {
	//xil_printf("draw page\r\n");
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

void erasePage(Page* obj) {
	u8 i;
	for (i = 0; i < obj->textCount; i++) {
		eraseContent(&obj->textArr[i].super);
	}
	for (i = 0; i < obj->buttonCount; i++) {
		eraseContent(&obj->buttonArr[i].super);
	}
	for (i = 0; i < obj->sliderCount; i++) {
		eraseContent(&obj->sliderArr[i].super);
		setColor(0, 0, 95);
		setColorBg(0, 0, 0);
		drawShape(obj->sliderArr[i].super.x, obj->sliderArr[i].super.y, obj->sliderArr[i].super.w, obj->sliderArr[i].total_h, &triangles);
		obj->sliderArr[i].pre_value = obj->sliderArr[i].value;
	}

}

void addTask(void* func, void* param) {
	qArr[ptr].func = func;
	qArr[ptr].param = param;
	ptr++;
}

void clrAndAddTask(void* func, void* param) {
	qArr[ptr].func = func;
	qArr[ptr].param = param;
	ptr = 1;
}

void clearQ() {
	for (int i = 0; i <= ptr; i++) {
		qArr[ptr].func(qArr[ptr].param);
	}
	ptr = 0;
}
