#include "oled_anim.h"
#include "oled_gui.h"
#include "math.h"
#include "system.h"
static uint16_t anim_timestamp = 0;

oled_anim *oled_anim::pFirst;
oled_anim *oled_anim::pLast;
uint8_t oled_anim::uSum;

static float animate_fx(float t) // function for animation
{
	return t*t;
	/*
	if(t <= 0.68584)
		return(3.099775*t*t*t);
	else
	{
		return(-(t-1)*sin(18*(t-1))+1);
	}
	*/
}


static void anim_init(oled_anim *p_anim, oled_obj *target, int16_t x_distance, int16_t y_distance, uint16_t duration)
{
	if (target == OBJ_NULL)
		return;

	p_anim->setTarget(target);
	p_anim->setXDis(x_distance);
	p_anim->setYDis(y_distance);
	p_anim->setDur(duration);
	p_anim->setActTime(0);
	p_anim->setXStart(target->getX());
	p_anim->setYStart(target->getY());
	p_anim->setAnimFadeType(FADE_NULL);

	p_anim->setWStart(-1);
	p_anim->setHStart(-1);

	p_anim->setAnimEndCb(ANIM_NULL_CB);
	oled_anim::oled_anim_add(p_anim);

}
static void anim_init(oled_anim *p_anim, oled_obj *target, int16_t x_distance, int16_t y_distance, int16_t w_distance, int16_t h_distance, uint16_t duration)
{
	if (target == OBJ_NULL)
	return;

	p_anim->setTarget(target);
	p_anim->setXDis(x_distance);
	p_anim->setYDis(y_distance);
	p_anim->setDur(duration);
	p_anim->setActTime(0);
	p_anim->setXStart(target->getX());
	p_anim->setYStart(target->getY());	
	p_anim->setAnimFadeType(FADE_NULL);

	p_anim->setWStart(target->getW());
	p_anim->setHStart(target->getH());
	p_anim->setWDis(w_distance);
	p_anim->setHDis(h_distance);	

	p_anim->setAnimEndCb(ANIM_NULL_CB);
	oled_anim::oled_anim_add(p_anim);
}
static void anim_init(oled_anim *p_anim, oled_obj *target, fade_type fade, uint16_t duration)
{
	if (target == OBJ_NULL)
		return;

	p_anim->setTarget(target);
	p_anim->setXDis(0);
	p_anim->setYDis(0);
	p_anim->setDur(duration);
	p_anim->setActTime(0);

	p_anim->setAnimFadeType(fade);
	p_anim->setFadeStart(target->getFade());

	p_anim->setWStart(-1);
	p_anim->setHStart(-1);

	p_anim->setAnimEndCb(ANIM_NULL_CB);
	oled_anim::oled_anim_add(p_anim);	
}



oled_anim::~oled_anim()
{
	
}

oled_anim::oled_anim()
{
	this->setAllocType(ALLOC_DYNAMIC);
	this->target = OBJ_NULL;
	this->x_distance = 0;
	this->y_distance = 0;

	this->fade_start = -1;
	this->fade = FADE_NULL;

	this->w_start = -1;
	this->h_start = -1;
	this->duration = 0;
	this->act_time = 0;
	this->animEndCb = ANIM_NULL_CB;
}
oled_anim::oled_anim(oled_obj *target, int16_t x_distance, int16_t y_distance, uint16_t duration)
{
	this->setAllocType(ALLOC_DYNAMIC);
	anim_init(this, target, x_distance, y_distance, duration);
}
oled_anim::oled_anim(oled_obj *target, int16_t x_distance, int16_t y_distance, int16_t w_distance, int16_t h_distance, uint16_t duration)
{
	this->setAllocType(ALLOC_DYNAMIC);
	anim_init(this, target, x_distance, y_distance, w_distance, h_distance, duration);
}
oled_anim::oled_anim(oled_obj *target, fade_type fade, uint16_t duration)
{
	this->setAllocType(ALLOC_DYNAMIC);
	anim_init(this, target, fade, duration);
}





void oled_anim::init(oled_obj *target, int16_t x_distance, int16_t y_distance, uint16_t duration)
{
	this->setAllocType(ALLOC_STATIC);
	anim_init(this, target, x_distance, y_distance, duration);
}
void oled_anim::init(oled_obj *target, int16_t x_distance, int16_t y_distance, int16_t w_distance, int16_t h_distance, uint16_t duration)
{
	this->setAllocType(ALLOC_STATIC);
	anim_init(this, target, x_distance, y_distance, w_distance, h_distance, duration);
}
void oled_anim::init(oled_obj *target, fade_type fade, uint16_t duration)
{
	this->setAllocType(ALLOC_STATIC);
	anim_init(this, target, fade, duration);
}

void oled_anim::deinit(void)
{
	oled_anim::oled_anim_delete(this);
}

void oled_anim::oled_anim_init(void)
{
	pFirst = ANIM_NULL;
	pLast = ANIM_NULL;
	uSum = 0;
}
void oled_anim::oled_anim_add(oled_anim *pAnim)
{
	if(pAnim == ANIM_NULL)
	{
		SYS_PRINT("ANIM_NULL\n");
		return;
	}
	if (uSum == 0)
	{
		pAnim->setAnimNext(ANIM_NULL);
		pAnim->setAnimPrev(ANIM_NULL);
		pFirst = pAnim;
		pLast = pAnim;
	}
	else
	{
		pAnim->setAnimPrev(pLast);
		pAnim->setAnimNext(ANIM_NULL);
		pLast->pNext = pAnim;
		pLast = pAnim;
	}
	uSum++;
}
void oled_anim::oled_anim_delete(oled_anim *pAnim)
{
	if (pAnim == pFirst)
	{
		if (pAnim->getAnimNext() != ANIM_NULL)
		{
			pAnim->getAnimNext()->setAnimPrev(ANIM_NULL);
			pFirst = pAnim->getAnimNext();
		}
		else
		{
			pFirst = ANIM_NULL;
			pLast = ANIM_NULL;
		}
	}
	else if (pAnim == pLast)
	{
		pAnim->getAnimPrev()->setAnimNext(ANIM_NULL);
		pLast = pAnim->getAnimPrev();
	}
	else
	{
		pAnim->getAnimPrev()->setAnimNext(pAnim->getAnimNext());
		pAnim->getAnimNext()->setAnimPrev(pAnim->getAnimPrev());
	}
	uSum--;
	if(pAnim->getAllocType() == ALLOC_DYNAMIC) 
	{	
		//delete pAnim;
		pAnim = ANIM_NULL;
	}

}
void oled_anim::oled_anim_run(void)
{
	oled_anim *pAnim = pFirst;
	uint16_t elaps = oled_tickElaps(anim_timestamp);
	anim_timestamp = oled_getTimestamp();

	while (pAnim != NULL)
	{	
		float p;
		pAnim->act_time += elaps;
		if (pAnim->act_time > pAnim->duration)
			pAnim->act_time = pAnim->duration;

		p = animate_fx((float)pAnim->act_time / pAnim->duration);

		if (pAnim->x_distance != 0 || pAnim->y_distance != 0)
		{
			pAnim->target->setX(pAnim->x_start + pAnim->x_distance * p);
			pAnim->target->setY(pAnim->y_start + pAnim->y_distance * p);
		}

		if (pAnim->fade != FADE_NULL)
		{
			switch (pAnim->fade)
			{
			case FADE_IN:
				pAnim->target->setFade(pAnim->fade_start - (int16_t)(p * 4));
				break;
			case FADE_OUT:
				pAnim->target->setFade(pAnim->fade_start + (int16_t)(p * 4));
				break;
			case FADE_NULL:
				break;
			default:
				break;
			}
		}

		if (pAnim->w_start != -1)
		{
			pAnim->target->setW(pAnim->w_start + pAnim->w_distance * p);
			pAnim->target->setH(pAnim->h_start + pAnim->h_distance * p);
		}

		if (pAnim->act_time == pAnim->duration)
		{
			pAnim->setAnimFadeType(FADE_NULL);
			t_anim_end_cb animEndCb = pAnim->animEndCb;
			oled_anim_delete(pAnim);
			if (pAnim->animEndCb != ANIM_NULL_CB)
				animEndCb();
		}
		pAnim = pAnim->getAnimNext();
	}
}