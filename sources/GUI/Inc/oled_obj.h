#ifndef __OLED_OBJ_H__
#define __OLED_OBJ_H__

#ifdef __OLED_OBJ_H__
// #include "obj_switch.h"
#endif

#include <stdint.h>

#define OBJ_NULL ((oled_obj *)0)

typedef enum
{
  	ALLOC_NULL,
	ALLOC_STATIC,  //This anim is statically allocated
	ALLOC_DYNAMIC, //This anim is dynamically allocated
}alloc_t;

typedef enum
{
	ALIGN_TOP,
	ALIGN_BOTTOM,
	ALIGN_LEFT,
	ALIGN_RIGHT,
	ALIGN_HORIZONMID,
	ALIGN_VERTICALMID,
	ALIGN_TOPLEFT,
	ALIGN_TOPMID,
	ALIGN_TOPRIGHT,
	ALIGN_BOTTOMLEFT,
	ALIGN_BOTTOMMID,
	ALIGN_BOTTOMRIGHT,
} allign_t;

enum OBJ_TYPE
{
	OBJ_DEFAULT = 0,
	// OBJ_FOCUS_EN	= 1, //This obj can be focus
	OBJ_SWITCH = 2,
	OBJ_LABEL = 4,
	OBJ_BMP = 8,
	OBJ_CANVAS = 16,
	OBJ_SLIDER = 32,
	OBJ_INDICATOR = 64,
	OBJ_GROUP = 128,
};
enum OBJ_STATE // Consider state and flag using the same var: type
{
	STATE_DEFAULT = 0, // Normal state
	// STATE_INVERTED	= 1,
	STATE_CHECKED = 2,   // being checked -> using for checkbox, switches,...
	STATE_FOCUSED = 4,   // being focused -> a frame will be around that obj
	STATE_PRESSED = 8,   // being pressed -> for button...
	STATE_SCROLLED = 16, // being scrolled -> for animation, scrolling label
	STATE_DISABLE = 32,  // disable state
	// FLAG_INVERTABLE = 64,
	FLAG_CHECKABLE = 128,
	FLAG_FOCUSABLE = 256,
	FLAG_PRESSABLE = 512,
	FLAG_SCROLLABLE = 1024,
};

class oled_obj
{
private:
	alloc_t alloc_type;
	// Fade level
	int8_t fade;
	// Position
	int16_t x;
	int16_t y;
	// Size
	int16_t w;
	int16_t h;
	// Type
	uint16_t type;
	// State
	uint16_t state;
	// Linked list
	oled_obj *pPrev;
	oled_obj *pNext;
	// Feature, using for image array of its obj
	void *pFeature;

protected:
	static uint8_t ucSum;
	static oled_obj *pFirst, *pLast;

public:
	oled_obj(/* args */);
	virtual ~oled_obj();

	virtual void deinit();
	
	virtual void setFade(int8_t fade)
	{
		if (fade > 4)
			this->fade = 4;
		else if (fade < 0)
			this->fade = 0;
		else
			this->fade = fade;
	}

	virtual void setX(int16_t x) { this->x = x; }
	virtual void setY(int16_t y) { this->y = y; }
	void setW(int16_t w) { this->w = w; }
	void setH(int16_t h) { this->h = h; }
	void setFeature(void *pFeature) { this->pFeature = pFeature; }
	void *getFeature(void) { return this->pFeature; }
	int8_t getFade() { return this->fade; }
	int16_t getX(void) { return x; }
	int16_t getY(void) { return y; }
	int16_t getW(void) { return w; }
	int16_t getH(void) { return h; }
	oled_obj *getNext() { return pNext; }
	oled_obj *getPrev() { return pPrev; }
	void setNext(oled_obj *pNext) { this->pNext = pNext; }
	void setPrev(oled_obj *pPrev) { this->pPrev = pPrev; }
	bool getState(uint16_t state) { return (this->state & state) > 0; }
	void addState(uint16_t state)
	{
		uint16_t newState = this->state | state;
		if (newState != this->state)
			this->state = newState;
		if (newState & STATE_DISABLE)
			this->state = STATE_DISABLE;
	}
	void clearState(uint16_t state)
	{
		uint16_t newState = this->state & (~state);
		if (newState != this->state)
			this->state = newState;
	}

	void setAllocType(alloc_t type){ alloc_type = type; }
	alloc_t getAllocType(){	return alloc_type; }

	uint16_t getType() { return type; }
	void setType(uint16_t type) { this->type = type; }

	void setAllign(allign_t allign);

	void drawFade(void);
	virtual void draw();

	// Static fields
	static void oled_obj_init(void);
	static void oled_obj_add(oled_obj *obj);
	static void oled_obj_delete(oled_obj *obj);
	static void oled_obj_draw(void);
};

#define SIZE_OF_OBJ sizeof(oled_obj)

#endif