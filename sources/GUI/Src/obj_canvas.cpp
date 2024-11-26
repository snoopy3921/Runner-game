#include "obj_canvas.h"
#include "gui_port.h"

static float smallest(int x, int y, int z)
{
  return x < y ? (x < z ? x : z) : (y < z ? y : z);
}
static float largest(int x, int y, int z)
{
  return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

static void canvas_init(obj_canvas* p_cv)
{
	p_cv->setFade(0);
	p_cv->clearState(FLAG_FOCUSABLE);
	p_cv->setType(OBJ_CANVAS);
	oled_obj::oled_obj_add(p_cv);
}

obj_canvas::obj_canvas()
{
	this->setAllocType(ALLOC_DYNAMIC);
	canvas_init(this);
}
obj_canvas::~obj_canvas()
{
	deinit();
}

void obj_canvas::init()
{
	this->setAllocType(ALLOC_STATIC);
	canvas_init(this);
}

void obj_canvas::deinit()
{
	this->setFade(0);
	this->clearState(FLAG_FOCUSABLE);
	this->setType(OBJ_CANVAS);
	oled_obj::oled_obj_delete(dynamic_cast<oled_obj*>(this));
}
	
void obj_canvas::canvas_drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
	this->type = CANVAS_LINE;
	this->setX(x0);
	this->setY(y0);
	this->setW(x1 - x0);
	this->setH(y1 - y0);
	this->x1 = x1;
	this->y1 = y1;
}
void obj_canvas::canvas_drawRect(int16_t x, int16_t y, int16_t w, int16_t h)
{
	this->type = CANVAS_RECT;
	this->setX(x);
	this->setY(y);
	this->setW(w);
	this->setH(h);
}
void obj_canvas::canvas_fillRect(int16_t x, int16_t y, int16_t w, int16_t h)
{
	this->type = CANVAS_FILL_RECT;
	this->setX(x);
	this->setY(y);
	this->setW(w);
	this->setH(h);
}

void obj_canvas::canvas_drawCircle(int16_t x0, int16_t y0, int16_t r)
{
	this->type = CANVAS_CIRCLE;
	this->setX(x0 - r);
	this->setY(y0 - r);
	this->setW(x0 + r);
	this->setH(y0 + r);
	this->x0 = x0;
	this->y0 = y0;
	this->radius = r;
}  
void obj_canvas::canvas_drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername)
{
	this->type = CANVAS_CIRCLE_HELPER;
	this->setX(x0);
	this->setY(y0);
	this->setW(x0 + r);
	this->setH(y0 + r);
	this->x0 = x0;
	this->y0 = y0;
	this->cornername = cornername;
}
void obj_canvas::canvas_fillCircle(int16_t x0, int16_t y0, int16_t r)
{
	this->type = CANVAS_FILL_CIRCLE;
	this->setX(x0 - r);
	this->setY(y0 - r);
	this->setW(x0 + r);
	this->setH(y0 + r);
	this->x0 = x0;
	this->y0 = y0;
	this->radius = r;
}
void obj_canvas::canvas_fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta)
{
	this->type = CANVAS_FILL_CIRCLE_HELPER;
	this->setX(x0);
	this->setY(y0);
	this->radius = r;
	this->cornername = cornername;
	this->delta = delta;
}

void obj_canvas::canvas_drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	this->type = CANVAS_TRIANGLE;
	int16_t x_min = smallest(x0, x1, x2);
	int16_t y_min = smallest(y0, y1, y2);
	int16_t x_max = largest(x0, x1, x2);
	int16_t y_max = largest(y0, y1, y2);
	this->setX(x_min);
	this->setY(y_min);
	this->setW(x_max - x_min);
	this->setH(y_max - y_min);
	this->x0 = x0;
	this->x1 = x1;
	this->x2 = x2;
	this->y0 = y0;
	this->y1 = y1;
	this->y2 = y2;
}
void obj_canvas::canvas_fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
	this->type = CANVAS_FILL_TRIANGLE;
	int16_t x_min = smallest(x0, x1, x2);
	int16_t y_min = smallest(y0, y1, y2);
	int16_t x_max = largest(x0, x1, x2);
	int16_t y_max = largest(y0, y1, y2);
	this->setX(x_min);
	this->setY(y_min);
	this->setW(x_max - x_min);
	this->setH(y_max - y_min);
	this->x0 = x0;
	this->x1 = x1;
	this->x2 = x2;
	this->y0 = y0;
	this->y1 = y1;
	this->y2 = y2;
}
void obj_canvas::canvas_drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius)
{
	this->type = CANVAS_ROUND_RECT;
	this->setX(x0);
	this->setY(y0);
	this->setW(w);
	this->setH(h);
	this->radius = radius;
}
void obj_canvas::canvas_fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius)
{
	this->type = CANVAS_FILL_ROUND_RECT;
	this->setX(x0);
	this->setY(y0);
	this->setW(w);
	this->setH(h);
	this->radius = radius;
}
void obj_canvas::draw()
{
	switch(this->type)
	{
		case CANVAS_LINE:
		{
			display_draw_line(this->getX(), this->getY(), this->x1, this->y1, this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;			
		}		
		case CANVAS_RECT:
		{
			display_draw_rect(this->getX(), this->getY(), this->getW(), this->getH(), this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}
		case CANVAS_FILL_RECT:
		{
			display_fill_rect(this->getX(), this->getY(), this->getW(), this->getH(), this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}
		case CANVAS_ROUND_RECT:
		{
			display_draw_round_rect(this->getX(), this->getY(), this->getW(), this->getH(), this->radius, this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}
		case CANVAS_FILL_ROUND_RECT:
		{
			display_fill_round_rect(this->getX(), this->getY(), this->getW(), this->getH(), this->radius, this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}
		case CANVAS_CIRCLE:
		{
			display_draw_circle(this->x0, this->y0, this->radius, this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}
		case CANVAS_FILL_CIRCLE:
		{
			display_fill_circle(this->x0, this->y0, this->radius, this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}
		case CANVAS_CIRCLE_HELPER:
		{
			display_draw_circle_helper(this->x0, this->y0, this->radius, this->cornername, this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}		
		case CANVAS_FILL_CIRCLE_HELPER:
		{
			display_fill_circle_helper(this->x0, this->y0, this->radius, this->cornername, this->delta, this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}
		case CANVAS_TRIANGLE:
		{
			display_draw_triangle(this->x0, this->y0, this->x1, this->y1, this->x2, this->y2, this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}
		case CANVAS_FILL_TRIANGLE:
		{
			display_fill_triangle(this->x0, this->y0, this->x1, this->y1, this->x2, this->y2, this->getState(STATE_FOCUSED)? BLACK : WHITE);
			break;
		}
	}
}