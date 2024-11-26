#include "obj_indicator.h"
#include "oled_anim.h"
#include "gui_port.h"

static void idctor_init(obj_indicator* p_idctor, oled_obj* target, uint8_t gap, bool isFill)
{
    p_idctor->setTarget(target);
    p_idctor->setGap(gap);
    p_idctor->setIsFill(isFill);
    if(isFill) target->addState(STATE_FOCUSED);   
    p_idctor->setX(target->getX() - gap);
    p_idctor->setY(target->getY() - gap);
    p_idctor->setW(target->getW() + 2*gap);
    p_idctor->setH(target->getH() + 2*gap);     
	p_idctor->setFade(0);
	p_idctor->clearState(FLAG_FOCUSABLE);
    p_idctor->setType(OBJ_INDICATOR);
	oled_obj::oled_obj_add(dynamic_cast<oled_obj*>(p_idctor));
}

obj_indicator::obj_indicator()
{
    this->setAllocType(ALLOC_DYNAMIC);
}

obj_indicator::obj_indicator(oled_obj* target, uint8_t gap, bool isFill)
{
    this->setAllocType(ALLOC_DYNAMIC);
    idctor_init(this, target, gap, isFill);
}

obj_indicator::~obj_indicator()
{
   deinit();
}

void obj_indicator::init(oled_obj* target, uint8_t gap, bool isFill)
{
    this->setAllocType(ALLOC_STATIC);
    idctor_init(this, target, gap, isFill);
}

void obj_indicator::deinit()
{
    oled_obj::oled_obj_delete(dynamic_cast<oled_obj*>(this));
}



void obj_indicator::update()
{
	if(this->getTarget()!=OBJ_NULL)
	{
	  this->setX(target->getX() - gap);
    this->setY(target->getY() - gap);
    this->setW(target->getW() + 2*gap);
    this->setH(target->getH() + 2*gap);
	}
}

void obj_indicator::setTarget(oled_obj* target)
{  
    if(this->getIsFill()) target->addState(STATE_FOCUSED);  
    if(this->getTarget()!=OBJ_NULL) this->getTarget()->clearState(STATE_FOCUSED);    
    this->target = target;
    this->setX(target->getX() - gap);
    this->setY(target->getY() - gap);
    this->setW(target->getW() + 2*gap);
    this->setH(target->getH() + 2*gap);
}


void obj_indicator::draw()
{
    display_draw_round_rect(this->getX(), this->getY(), this->getW(), this->getH(), 3, WHITE);
    if(this->getIsFill()) view_render.fillRoundRect(this->getX(), this->getY(), this->getW(), this->getH(), 3, WHITE);
}