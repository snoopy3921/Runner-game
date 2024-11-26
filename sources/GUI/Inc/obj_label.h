#ifndef __OBJ_LABEL_H__
#define __OBJ_LABEL_H__

#include "oled_obj.h"


#define MAX_TEXT_LEN 18


typedef enum
{
	FONT_FREE_MONO_9PT_7B,
	FONT_FREE_MONO_BOLD_12PT_7B,
	FONT_FREE_MONO_BOLD_9PT_7B,
	FONT_DEFAULT,
}font_t;



class obj_label : public oled_obj
{
private:
    /* data */
    char text[MAX_TEXT_LEN];
    uint8_t text_size; // 1, 2, 3,...		
		font_t label_font;
public:
    obj_label(/* args */);
    obj_label(int16_t x, int16_t y);
    ~obj_label();

    void init(int16_t x, int16_t y);
    virtual void deinit();

		uint8_t getTextSize(){return text_size;}
    virtual void draw();
    void printf(const char *str, ...);
    void print(const char *str);
    void print(unsigned long n) ;
		void setFont(font_t font);
		void setTextSize(uint8_t size);
		void clear();
};

#endif

