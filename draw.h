#ifndef SRC_LCD_DRAW_H_
#define SRC_LCD_DRAW_H_

#include "lab2a.h"

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
} Content;

typedef struct TextTag {
    Content super;
    char* text;
    u8* font;
    u8 length;
    u32 text_x;
    u32 text_y;
} Text;

typedef struct ButtonTag {
    Content super;
    char* text;
    u8* font;
    u8 length;
    u32 text_x;
    u32 text_y;
    Color focus;
    Color press;
    QStateHandler target;
} Button;

typedef struct SliderTag {
	Content super;
	u32 max;
	u32 value;
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


#define MARGIN 1

void initColor(Color* color, u8 r, u8 g, u8 b);
void initContent(Content* obj, u32 x, u32 y, u32 w, u32 h);
void initText(Text* text, char* str, u8* font);
void initButton(Button* btn, char* str, u8* font);

void setColors(Color* fg, Color* bg);
void fillContent(Content* obj);
void drawText(Text* obj);
void drawButton(Button* obj, u32 focused, u32 pressed);
void drawSlider(Slider* obj, u32 focused);
void eraseContent(Content* obj);
void drawPage(Page* obj);
void erasePage(Page* obj);

int triangles(int x, int y);
void plotBackground(void);
void eraseContent(u8 contentNum, Content* contentArr)



#endif
