#ifndef __GUI_PORT_H__
#define __GUI_PORT_H__

#define DISPLAY_SSD1036 (1u)

#include "Adafruit_ssd1306syp.h"

extern Adafruit_ssd1306syp view_render;


#define MAX_GUI_TICK 0xffffffff

#define DISPLAY_HEIGHT ((uint16_t)64u)
#define DISPLAY_WIDTH ((uint16_t)128u)
#define BLACK 0
#define WHITE 1

extern uint32_t get_tick(void);
extern void display_init(void);
extern void display_clear(void);
extern void display_update(void);
extern void display_draw_pixel(int16_t x, int16_t y, uint16_t color);
extern void display_draw_bitmap(int16_t x, int16_t y, const uint8_t *bitmap,
                                int16_t w, int16_t h, uint16_t color);
extern void display_set_cursor(int16_t x, int16_t y);
extern void display_set_text_color(uint16_t color);
extern void display_set_text_size(uint16_t size);
extern void display_print(char* str);

extern void display_draw_round_rect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                                    int16_t radius, uint16_t color);

extern void display_fill_round_rect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                                    int16_t radius, uint16_t color);
extern void display_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
extern void display_draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
extern void display_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
extern void display_draw_circle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
extern void display_fill_circle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
extern void display_draw_circle_helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
extern void display_fill_circle_helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);
extern void display_draw_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
extern void display_fill_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);



#endif