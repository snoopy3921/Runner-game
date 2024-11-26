#include "obj_label.h"
#include <string.h>
#include <stdarg.h>
#include <cstdio>
#include "gui_port.h"



obj_label::obj_label()
{
}
obj_label::~obj_label()
{
	deinit();
}

obj_label::obj_label(int16_t x, int16_t y)
{
	init(x, y);
}

void obj_label::init(int16_t x, int16_t y)
{
	// text_size = 0;
	text_size = 1;
	text[0] = '\0';
	this->setX(x);
	this->setY(y);
	this->setW(0);
	this->setH(0);
	this->label_font = FONT_DEFAULT;
	this->setFade(0);
	this->clearState(FLAG_FOCUSABLE);
	this->setType(OBJ_LABEL);
	oled_obj::oled_obj_add(dynamic_cast<oled_obj*>(this));
}

void obj_label::deinit()
{
	this->setFade(0);
	this->clearState(FLAG_FOCUSABLE);
	this->setType(OBJ_CANVAS);
	oled_obj::oled_obj_delete(dynamic_cast<oled_obj*>(this));
}

void obj_label::printf(const char *str, ...)
{
	char buffer[50];
	va_list args;
	va_start(args, str);
	vsnprintf(buffer, sizeof(buffer), str, args);
	strcpy(text, buffer);
	uint16_t len = strlen(buffer);
	this->setW(len * 6);
	this->setH(8);
}
void obj_label::print(const char *str)
{
	strcpy(text, str);
	uint16_t len = strlen(str);
	this->setW(len * 6);
	this->setH(8);
}
void obj_label::print(unsigned long n) {
    char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
    char *str = &buf[sizeof(buf) - 1];

    *str = '\0';

    // prevent crash if called with base == 1
    int base = 10;

    do {
        unsigned long m = n;
        n /= base;
        char c = m - base * n;
        *--str = c < 10 ? c + '0' : c + 'A' - 10;
    } while(n);

	strcpy(text, str);
	uint16_t len = strlen(str);
	this->setW(len * 6);
	this->setH(8);
}

void obj_label::clear()
{
	this->setW(0);
	this->setH(0);
	text[0] = '\0';
}

void obj_label::setFont(font_t font)
{
	this->label_font = font;
}

void obj_label::setTextSize(uint8_t size)
{
	this->text_size = size;
}

void obj_label::draw()
{	
	display_set_text_color(this->getState(STATE_FOCUSED) ? BLACK : WHITE);
	display_set_cursor(this->getX(), this->getY());
	display_print(text);
}
