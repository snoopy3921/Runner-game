#include "obj_switch.h"
#include "gui_port.h"


uint8_t const bmp_switch8[][12] = 
{
	{
		0x1C,0x22,0x49,0x5D,0x5D,0x49,0x41,0x41,0x41,0x41,0x22,0x1C			//Off
	},
	{
		0x1C,0x22,0x49,0x5D,0x5D,0x55,0x49,0x5D,0x5D,0x49,0x22,0x1C			//On
	}
};
uint8_t const bmp_switch24x15[][45] =
{
	{
		0xff, 0xff, 0xff, 0x80, 0x00, 0x01, 0xbf, 0x80, 0x01, 0xbf, 0x80, 0x01, 0xbf, 0x80, 0x01, 0xbf, 
		0x80, 0x01, 0xbf, 0x80, 0x01, 0xbf, 0x80, 0x01, 0xbf, 0x80, 0x01, 0xbf, 0x80, 0x01, 0xbf, 0x80, 
		0x01, 0xbf, 0x80, 0x01, 0xbf, 0x80, 0x01, 0x80, 0x00, 0x01, 0xff, 0xff, 0xff
	},
	{	
		0xff, 0xff, 0xff, 0x80, 0x00, 0x01, 0x95, 0x55, 0xfd, 0xaa, 0xa9, 0xfd, 0x95, 0x55, 0xfd, 0xaa, 
		0xa9, 0xfd, 0x95, 0x55, 0xfd, 0xaa, 0xa9, 0xfd, 0x95, 0x55, 0xfd, 0xaa, 0xa9, 0xfd, 0x95, 0x55, 
		0xfd, 0xaa, 0xa9, 0xfd, 0x95, 0x55, 0xfd, 0x80, 0x00, 0x01, 0xff, 0xff, 0xff
	}
};


static void sw_init(obj_switch *p_sw, uint8_t ucSize, uint8_t state, int16_t x, int16_t y)
{
	if(state == STATE_CHECKED) p_sw->addState(STATE_CHECKED);
	else p_sw->clearState(STATE_CHECKED);
	if(ucSize == SW_SIZE_1)
	{
		p_sw->setFeature((void *)bmp_switch8[p_sw->getState(STATE_CHECKED)]);
		p_sw->setW(12);
		p_sw->setH(8);
	}
	if(ucSize == SW_SIZE_2)
	{
		p_sw->setFeature((void *)bmp_switch24x15[p_sw->getState(STATE_CHECKED)]);
		p_sw->setW(24);
		p_sw->setH(15);
	}
	p_sw->setX(x);
	p_sw->setY(y);    
	p_sw->setFade(0);
	p_sw->clearState(FLAG_FOCUSABLE);
	p_sw->setType(OBJ_SWITCH);
	oled_obj::oled_obj_add(dynamic_cast<oled_obj*>(p_sw));
}

obj_switch::obj_switch()
{
	this->setAllocType(ALLOC_DYNAMIC);
}

obj_switch::obj_switch(uint8_t ucSize, uint8_t state, int16_t x, int16_t y)
{
	this->setAllocType(ALLOC_DYNAMIC);
	sw_init(this, ucSize, state, x, y);
}

obj_switch::~obj_switch()
{
	deinit();
}

void obj_switch::init(uint8_t ucSize, uint8_t state, int16_t x, int16_t y)
{
	this->setAllocType(ALLOC_STATIC);
	sw_init(this, ucSize, state, x, y);
}

void obj_switch::deinit()
{
	this->setFade(0);
	this->clearState(FLAG_FOCUSABLE);
	this->setType(OBJ_CANVAS);
	oled_obj::oled_obj_delete(dynamic_cast<oled_obj*>(this));
}

void obj_switch::draw()
{
	if(this->getH() > 8) this->setFeature((void *)bmp_switch24x15[this->getState(STATE_CHECKED)]);
	else this->setFeature((void *)bmp_switch8[this->getState(STATE_CHECKED)]);
	display_draw_bitmap(this->getX(), this->getY(), (uint8_t *)this->getFeature(), this->getW(), this->getH(), this->getState(STATE_FOCUSED)? BLACK : WHITE);
}
void obj_switch::toggle()
{
    if(this->getState(STATE_CHECKED)) this->clearState(STATE_CHECKED);
    else this->addState(STATE_CHECKED);
}