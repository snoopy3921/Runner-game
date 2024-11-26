#include "gui_port.h"
#include "os_task.h"

Adafruit_ssd1306syp view_render;


uint32_t get_tick(void)
{
     uint32_t tick = os_task_get_tick();
     return tick;
}
void display_init(void)
{
     view_render.initialize();
}
void display_clear(void)
{
     view_render.clear(false);
}
void display_update(void)
{
     view_render.update();
}
void display_draw_pixel(int16_t x, int16_t y, uint16_t color)
{
     view_render.drawPixel(x, y, color);
}
void display_draw_bitmap(int16_t x, int16_t y, const uint8_t *bitmap,
                         int16_t w, int16_t h, uint16_t color)
{
     view_render.drawBitmap(x, y, bitmap, w, h, color);
}
void display_set_cursor(int16_t x, int16_t y)
{
     view_render.setCursor(x, y);
}
void display_set_text_color(uint16_t color)
{
     view_render.setTextColor(color);
}
void display_print(char* str)
{
     view_render.print(str);
}
void display_draw_round_rect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                             int16_t radius, uint16_t color)
{
     view_render.drawRoundRect(x0, y0, w, h, radius, color);
}

void display_fill_round_rect(int16_t x0, int16_t y0, int16_t w, int16_t h,
                             int16_t radius, uint16_t color)
{
     view_render.fillRoundRect(x0, y0, w, h, radius, color);
}
void display_draw_line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
     view_render.drawLine(x0, y0, x1, y1, color);
}
void display_draw_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
     view_render.drawRect(x, y, w, h, color);
}
void display_fill_rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
     view_render.fillRect(x, y, w, h, color);
}
void display_draw_circle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
     view_render.drawCircle(x0, y0, r, color);
}
void display_fill_circle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
     
}
void display_draw_circle_helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color)
{
}
void display_fill_circle_helper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
}
void display_draw_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
}
void display_fill_triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
}