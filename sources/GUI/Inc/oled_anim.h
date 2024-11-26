#ifndef __OLED_ANIM_H__
#define __OLED_ANIM_H__

#include "oled_obj.h"

typedef void(*t_anim_end_cb)(void);

#define ANIM_NULL_CB ((t_anim_end_cb)0)
#define ANIM_NULL ((oled_anim*)0)

typedef enum
{
	FADE_NULL = -1,
	FADE_IN,
	FADE_OUT,	
}fade_type;

class oled_anim 
{
private:
    /* data */
    int16_t x_start;
    int16_t y_start;
    int16_t w_start;
    int16_t h_start;
    int16_t w_distance;         //Difference
    int16_t h_distance;
    int16_t x_distance;
    int16_t y_distance;
		int8_t fade_start;
		fade_type fade;
    alloc_t alloc_type;
    
    uint16_t duration;
    uint16_t act_time;      /**< Current time in animation. Set to negative to make delay.*/
    t_anim_end_cb animEndCb;
    oled_anim* pPrev;
    oled_anim* pNext;
    oled_obj* target;

protected:
    static oled_anim* pFirst;
    static oled_anim* pLast;
    static uint8_t uSum;

public:
    oled_anim();
    oled_anim(oled_obj* target, int16_t x_distance, int16_t y_distance, uint16_t duration);
    oled_anim(oled_obj* target, int16_t x_distance, int16_t y_distance, int16_t w_distance, int16_t h_distance, uint16_t duration);
		oled_anim(oled_obj* target, fade_type fade, uint16_t duration);

    ~oled_anim();

    void init(oled_obj* target, int16_t x_distance, int16_t y_distance, uint16_t duration);
    void init(oled_obj* target, int16_t x_distance, int16_t y_distance, int16_t w_distance, int16_t h_distance, uint16_t duration);
    void init(oled_obj* target, fade_type fade, uint16_t duration);
    void deinit();
		
		void setAnimFadeType(fade_type fade){this->fade = fade;}
    void setAnimEndCb(t_anim_end_cb animEndCb){this->animEndCb = animEndCb;}
    void setAnimNext(oled_anim* pNext){this->pNext = pNext;}
    void setAnimPrev(oled_anim* pPrev){this->pPrev = pPrev;}
    oled_anim* getAnimNext(void){return this->pNext;}
    oled_anim* getAnimPrev(void){return this->pPrev;}

    void setAllocType(alloc_t type){ alloc_type = type; }
    alloc_t getAllocType(){ return alloc_type; }
    void setTarget(oled_obj* target){ this->target = target; }
    oled_obj* getTarget(){ return this->target;}

    void setXStart(int16_t val){this->x_start = val;}
    void setYStart(int16_t val){this->y_start = val;}
    void setWStart(int16_t val){this->w_start = val;}
    void setHStart(int16_t val){this->h_start = val;}

    void setFadeStart(int8_t val){this->fade_start = val;}
    void setDur(uint16_t val){this->duration = val;}
    void setActTime(uint16_t val){this->act_time = val;}

    void setXDis(int16_t val){this->x_distance = val;}
    void setYDis(int16_t val){this->y_distance = val;}
    void setWDis(int16_t val){this->w_distance = val;}
    void setHDis(int16_t val){this->h_distance = val;}

    int16_t getXStart(){return this->x_start;}
    int16_t getYStart(){return this->y_start;}
    int16_t getWStart(){return this->w_start;}
    int16_t getHStart(){return this->h_start;}

    int8_t getFadeStart(){return this->fade_start;}
    uint16_t getDur(){return this->duration;}
    uint16_t getActTime(){return this->act_time;}

    int16_t getXDis(){return this->x_distance;}
    int16_t getYDis(){return this->y_distance;}
    int16_t getWDis(){return this->w_distance;}
    int16_t getHDis(){return this->h_distance;}

    static void oled_anim_init(void);
    static void oled_anim_add(oled_anim* pAnim);
    static void oled_anim_delete(oled_anim* pAnim);
    static void oled_anim_run(void);
    
    
};

#define SIZE_OF_ANIM sizeof(oled_anim)

#endif