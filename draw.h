#ifndef SRC_LCD_DRAW_H_
#define SRC_LCD_DRAW_H_

#include "lab2a.h"
#include "page.h"

#define MARGIN 1

void setColors(Color* fg, Color* bg);
void fillContent(Content* obj, int margin);
void drawText(Text* obj);
void drawButton(Button* obj, u32 focused, u32 pressed);
void drawSlider(Slider* obj, u32 focused);
void eraseContent(Content* obj);
void drawPage(Page* obj);
void erasePage(Page* obj);

int triangles(int x, int y);
void plotBackground(int x, int y, int w, int h);

void addTask(void* func, void* param);
void clrAndAddTask (void* func, void* param);
void clearQ();

typedef struct LCDQTag {
	void (*func) (void* p);
	void* param;
}LCDQ;



#endif
