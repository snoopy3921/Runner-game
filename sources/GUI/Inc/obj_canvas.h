#ifndef __OBJ_CANVAS_H__
#define __OBJ_CANVAS_H__

#include "oled_obj.h"

typedef enum
{
	CANVAS_LINE,
	CANVAS_RECT,
	CANVAS_FILL_RECT,
	CANVAS_ROUND_RECT,
	CANVAS_FILL_ROUND_RECT,
	CANVAS_CIRCLE,
	CANVAS_FILL_CIRCLE,
	CANVAS_CIRCLE_HELPER,
	CANVAS_FILL_CIRCLE_HELPER,
	CANVAS_TRIANGLE,
	CANVAS_FILL_TRIANGLE,
} canvas_type;

class obj_canvas : public oled_obj
{
private:
	/* data */
	canvas_type type;
	uint8_t cornername;
	int16_t delta;
	int16_t radius;

	int16_t x0;
	int16_t y0;
	int16_t x1;
	int16_t y1;
	int16_t x2;
	int16_t y2;

public:
	obj_canvas(/* args */);
	~obj_canvas();

	void init();
	virtual void deinit();

	void canvas_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1);

	void canvas_drawRect(int16_t x, int16_t y, int16_t w, int16_t h);
	void canvas_fillRect(int16_t x, int16_t y, int16_t w, int16_t h);

	void canvas_drawCircle(int16_t x0, int16_t y0, int16_t r);
	void canvas_drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername);

	void canvas_fillCircle(int16_t x0, int16_t y0, int16_t r);
	void canvas_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta);

	void canvas_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);
	void canvas_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2);

	void canvas_drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius);
	void canvas_fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius);

	virtual void draw();
};

#endif