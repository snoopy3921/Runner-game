#ifndef __OBJ_SWITCH_H__
#define __OBJ_SWITCH_H__

#include "oled_obj.h"

enum SW_SIZE
{	
	SW_SIZE_1 	= 0,
	SW_SIZE_2	    , 
	SW_SIZE_3     ,
};

class obj_switch : public oled_obj
{
private:
    /* data */
    //uint8_t ucSize;
    //uint8_t state;
public:
    obj_switch(/* args */);
    obj_switch(uint8_t ucSize, uint8_t state, int16_t x, int16_t y);

    void init(uint8_t ucSize, uint8_t state, int16_t x, int16_t y);
    virtual void deinit();
    ~obj_switch();
    void toggle();
    virtual void draw();
};

#endif