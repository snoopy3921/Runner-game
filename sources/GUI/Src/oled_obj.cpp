#include "oled_obj.h"
#include <stdint.h>
#include "gui_port.h"
#include "system.h"
using namespace std;


oled_obj *oled_obj::pFirst;
oled_obj *oled_obj::pLast;
uint8_t oled_obj::ucSum;

oled_obj::oled_obj(/* args */)
{
	pPrev = NULL;
	pNext = NULL;
	pFeature = NULL;
	type = OBJ_DEFAULT;
	//alloc_type = ALLOC_NULL;
	fade = x = y = w = h = state = 0;
}

oled_obj::~oled_obj()
{
	
}

void oled_obj::draw()
{
	//Default
}

void oled_obj::deinit(void)
{
	//oled_obj::oled_obj_delete(dynamic_cast<oled_obj*>(this));
}

void oled_obj::drawFade(void)
{
	switch (this->getFade())
	{
	case 1:
	{
		for (int16_t j = this->getY(); j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX(); i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		break;
	}
	case 2:
	{
		for (int16_t j = this->getY(); j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX(); i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		for (int16_t j = this->getY() + 1; j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX(); i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		break;
	}
	case 3:
	{
		for (int16_t j = this->getY(); j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX(); i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		for (int16_t j = this->getY() + 1; j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX(); i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		for (int16_t j = this->getY(); j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX() + 1; i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		break;
	}
	case 4:
	{
		for (int16_t j = this->getY(); j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX(); i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		for (int16_t j = this->getY() + 1; j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX(); i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		for (int16_t j = this->getY(); j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX() + 1; i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		for (int16_t j = this->getY() + 1; j < this->getY() + this->getH(); j += 2)
		{
			for (int16_t i = this->getX() + 1; i < this->getX() + this->getW(); i += 2)
			{
				display_draw_pixel(i, j, this->getState(STATE_FOCUSED) ? WHITE : BLACK);
			}
		}
		break;
	}
	default:
		break;
	}
}


void oled_obj::setAllign(allign_t allign)
{
	switch (allign)
	{
	case ALIGN_TOP:
		this->y = 0;
		break;
	case ALIGN_BOTTOM:
		this->y = DISPLAY_HEIGHT - this->h;
		break;
	case ALIGN_LEFT:
		this->x = 0;
		break;
	case ALIGN_RIGHT:
		this->x = DISPLAY_WIDTH - this->w;
		break;
	case ALIGN_HORIZONMID:
		this->x = (DISPLAY_WIDTH - this->w) / 2;
		break;
	case ALIGN_VERTICALMID:
		this->y = (DISPLAY_HEIGHT - this->h) / 2;
		break;
	case ALIGN_TOPLEFT:
		this->x = 0;
		this->y = 0;
		break;
	case ALIGN_TOPMID:
		this->x = (DISPLAY_WIDTH - this->w) / 2;
		this->y = 0;
		break;
	case ALIGN_TOPRIGHT:
		this->x = DISPLAY_WIDTH - this->w;
		this->y = 0;
		break;
	case ALIGN_BOTTOMLEFT:
		this->x = 0;
		this->y = DISPLAY_HEIGHT - this->h;
		break;
	case ALIGN_BOTTOMMID:
		this->x = (DISPLAY_WIDTH - this->w) / 2;
		this->y = DISPLAY_HEIGHT - this->h;
		break;
	case ALIGN_BOTTOMRIGHT:
		this->x = DISPLAY_WIDTH - this->w;
		this->y = DISPLAY_HEIGHT - this->h;
		break;
	}
}


//////////////////////// Static fields

void oled_obj::oled_obj_init(void)
{
	pFirst = OBJ_NULL;
	pLast = OBJ_NULL;
	ucSum = 0;
}
void oled_obj::oled_obj_add(oled_obj *obj)
{
	if(obj == OBJ_NULL)
	{
		SYS_PRINT("OBJ_NULL\n");
		return;
	}
	if (ucSum == 0)
	{
		obj->setPrev(OBJ_NULL);
		obj->setNext(OBJ_NULL);
		pFirst = obj;
		pLast = obj;
	}
	else
	{
		if (obj->getType() != OBJ_INDICATOR)
		{
			obj->setPrev(pLast);
			obj->setNext(OBJ_NULL);
			pLast->pNext = obj;
			pLast = obj;
		}
		else
		{
			obj->setNext(pFirst);
			obj->setPrev(OBJ_NULL);
			pFirst->pPrev = obj;
			pFirst = obj;
		}
	}
	ucSum++;
}
void oled_obj::oled_obj_delete(oled_obj *obj)
{
	if (obj == OBJ_NULL)
		return;
	if (obj == pFirst)
	{
		if (obj->pNext != OBJ_NULL)
		{
			obj->getNext()->setPrev(OBJ_NULL);
			pFirst = obj->getNext();
		}
		else
		{
			pFirst = OBJ_NULL;
			pLast = OBJ_NULL;
		}
	}
	else if (obj == pLast)
	{
		obj->getPrev()->setNext(OBJ_NULL);
		pLast = obj->getPrev();
	}
	else
	{
		obj->getPrev()->setNext(obj->getNext());
		obj->getNext()->setPrev(obj->getPrev());
	}
	ucSum--;
	//if(obj->getAllocType() == ALLOC_DYNAMIC) delete obj;
	obj = OBJ_NULL;
}
void oled_obj::oled_obj_draw(void)
{
	oled_obj *obj = pFirst;
	display_clear();
	while (obj != OBJ_NULL)
	{
		if (obj->getState(STATE_DISABLE))
			goto next;
		if ((obj->getX() > DISPLAY_WIDTH) || (obj->getX() + obj->getW()) < 0)
			goto next;
		if ((obj->getY() > DISPLAY_HEIGHT) || (obj->getY() + obj->getH()) < 0)
			goto next;
		obj->draw();
		obj->drawFade();
	next:
		obj = obj->getNext();
	}
	display_update();
}
