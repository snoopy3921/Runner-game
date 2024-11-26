#include "obj_group.h"
#include "gui_port.h"


obj_group::obj_group()
{
    memSum = 0;
    member = nullptr;
    focusIndex = -1;
    idctor.init(OBJ_NULL, 2, false);
    this->setAllocType(ALLOC_DYNAMIC);
}
obj_group::~obj_group()
{
    deinit();
}

void obj_group::init()
{
    memSum = 0;
    member = nullptr;
    focusIndex = -1;
    idctor.init(OBJ_NULL, 2, false);
    this->setAllocType(ALLOC_STATIC);
}
void obj_group::deinit()
{
    if(memSum) delete[] member;
    idctor.deinit();

    /*Calling destructor in group causes fail*/
    //anim.deinit(); In group we dont call anim destructor bc they automatically call destrcutor after finishing anim
}

void obj_group::setX(int16_t x)
{
    if(idctor.getTarget() != OBJ_NULL) idctor.setX(idctor.getX()+ (x - this->getX()));
    for(uint8_t i = 0; i < memSum; i++)
    {
        member[i]->setX(member[i]->getX()+ (x - this->getX()));
    }
    oled_obj::setX(x);
}

void obj_group::setY(int16_t y)
{
    if(idctor.getTarget() != OBJ_NULL) idctor.setY(idctor.getY()+ (y - this->getY()));
    for(uint8_t i = 0; i < memSum; i++)
    {
        member[i]->setY(member[i]->getY()+ (y - this->getY()));
    }
    oled_obj::setY(y);
}

void obj_group::setPosOffset(int16_t delta_x, int16_t delta_y)
{
    if(idctor.getTarget() != OBJ_NULL) idctor.setX(idctor.getX()+delta_x);
    if(idctor.getTarget() != OBJ_NULL) idctor.setY(idctor.getY()+delta_y);
    for(uint8_t i = 0; i < memSum; i++)
    {
        member[i]->setX(member[i]->getX()+delta_x);
        member[i]->setY(member[i]->getY()+delta_y);
    }
}

void obj_group::setFade(int8_t fade)
{
	if(idctor.getTarget() != OBJ_NULL) idctor.setFade(fade);
    for(uint8_t i = 0; i < memSum; i++)
    {
        member[i]->setFade(fade);
    }
    oled_obj::setFade(fade);
}

void obj_group::move(int16_t delta_x, int16_t delta_y, uint16_t duration, t_anim_end_cb animEndCb)
{
    anim.init(this, delta_x, delta_y, duration);
}
void obj_group::fading(fade_type fade, uint16_t duration, t_anim_end_cb animEndCb)
{
    anim.init(this, fade, duration);
}

void obj_group::addObj(oled_obj* obj, bool isFocusEn)
{
    if(isFocusEn) 
    {
        obj->addState(FLAG_FOCUSABLE);
        if(focusIndex == -1)
        {            
            idctor.setTarget(obj);
            focusIndex = 0;
        }
    }
    if(memSum)
    {
        if(obj->getX() < this->getX()) this->oled_obj::setX(obj->getX());
        if(obj->getY() < this->getY()) this->oled_obj::setY(obj->getY());
        oled_obj** temp = new oled_obj*[++memSum];
        for(uint8_t i = 0; i < memSum - 1; i++)
        {
            temp[i] = member[i];
        }
        temp[memSum-1] = obj;
        delete[] member;
        member = temp;
    }
    else
    {
        this->oled_obj::setX(obj->getX());
        this->oled_obj::setY(obj->getY());
        memSum++;
        member = new oled_obj*[1];
        member[0] = obj;
    }
}
void obj_group::focusObj(uint8_t direction)
{
    if(memSum == 0 || focusIndex == -1) return;
    int16_t i;
    i = focusIndex;
    switch(direction)
    {
        case FOCUS_NEXT:
						do
						{
							i++;
							if(i == memSum) i = 0;
						}while(!member[i]->getState(FLAG_FOCUSABLE));

						if(member[i]->getState(FLAG_FOCUSABLE))
						{
							anim.init(&idctor, member[i]->getX() - idctor.getGap() - idctor.getX(), member[i]->getY() - idctor.getGap()\
							 - idctor.getY(), member[i]->getW() + 2*(idctor.getGap()) - idctor.getW(),\
							member[i]->getH() + 2*(idctor.getGap()) - idctor.getH(), 150); //This idk to implement callback so anim must be short!!!!
							idctor.setTarget(member[i]);	
						}
            break;
        case FOCUS_PREV:
						do
						{
							i--;
							if(i == -1) i = memSum - 1;
						}while(!member[i]->getState(FLAG_FOCUSABLE));

						if(member[i]->getState(FLAG_FOCUSABLE))
						{
							anim.init(&idctor, member[i]->getX() - idctor.getGap() - idctor.getX(), member[i]->getY() - idctor.getGap()\
							 - idctor.getY(), member[i]->getW() + 2*(idctor.getGap()) - idctor.getW(),\
							member[i]->getH() + 2*(idctor.getGap()) - idctor.getH(), 150); //This idk to implement callback so anim must be short!!!!
							idctor.setTarget(member[i]);
						}			
						break;
		}	


	
	focusIndex = i;
		
	
	int16_t bias_x, bias_y;
	if(idctor.getTarget()->getX() < 0)
		bias_x = -1*idctor.getTarget()->getX();
	else if((idctor.getTarget()->getX() + idctor.getTarget()->getW()) > DISPLAY_WIDTH)
		bias_x = -(idctor.getTarget()->getX() + idctor.getTarget()->getW() - DISPLAY_WIDTH);
	else
		bias_x = 0;
	if(idctor.getTarget()->getY() < 0)
		bias_y = -1*idctor.getTarget()->getY();
	else if((idctor.getTarget()->getY() + idctor.getTarget()->getH()) > DISPLAY_HEIGHT)
		bias_y = -(idctor.getTarget()->getY() + idctor.getTarget()->getH() - DISPLAY_HEIGHT);
	else
		bias_y = 0;
	if(bias_x != 0 || bias_y != 0)
	{
		move(bias_x, bias_y, 100, ANIM_NULL_CB);
	}

    
}

oled_obj* obj_group::getFocusObj()
{
	return member[focusIndex];
}

int8_t obj_group::getFocusIndex()
{
	return focusIndex;
}

void obj_group::setIsFillIndicator(bool isFill)
{
    idctor.setIsFill(isFill);
}
