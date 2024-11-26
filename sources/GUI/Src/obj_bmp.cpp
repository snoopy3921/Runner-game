#include "obj_bmp.h"
#include "gui_port.h"

static void bmp_init(obj_bmp* p_bmp, int16_t x, int16_t y, int16_t w, int16_t h)
{
  p_bmp->setX(x);
  p_bmp->setY(y);
  p_bmp->setW(w);
  p_bmp->setH(h);
  p_bmp->setType(OBJ_BMP);
  oled_obj::oled_obj_add(p_bmp);
}

obj_bmp::obj_bmp()
{
  this->setAllocType(ALLOC_DYNAMIC);
}

obj_bmp::obj_bmp(int16_t x, int16_t y, int16_t w, int16_t h)
{
  this->setAllocType(ALLOC_DYNAMIC);
  bmp_init(this, x, y, w, h);
}

obj_bmp::~obj_bmp()
{
  deinit();
}

void obj_bmp::init(int16_t x, int16_t y, int16_t w, int16_t h)
{
  this->setFade(0);
  this->clearState(FLAG_FOCUSABLE);
  this->clearState(STATE_DISABLE);
  this->setAllocType(ALLOC_STATIC);
  bmp_init(this, x, y, w, h);
}

void obj_bmp::deinit()
{
  this->setFade(0);
	this->clearState(FLAG_FOCUSABLE);
  this->clearState(STATE_DISABLE);
	this->setType(OBJ_CANVAS);
  oled_obj::oled_obj_delete(dynamic_cast<oled_obj*>(this));
}

void obj_bmp::setBmp(const uint8_t* src)
{
    this->setFeature((void*)src);
}

void obj_bmp::draw()
{

  display_draw_bitmap(this->getX(), this->getY(), (uint8_t *)this->getFeature(), this->getW(), this->getH(), WHITE);
	
}