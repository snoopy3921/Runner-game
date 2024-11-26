#ifndef __OBJ_GROUP_H__
#define __OBJ_GROUP_H__

#include "oled_obj.h"
#include "oled_anim.h"
#include "obj_indicator.h"

enum FOCUS{
	FOCUS_PREV,
	FOCUS_NEXT
};

class obj_group : public oled_obj
{
private:
    /* data */
    oled_obj** member;
    uint8_t memSum;
    int8_t focusIndex;  
		obj_indicator idctor;
    oled_anim anim;
public:
    obj_group(/* args */);
    ~obj_group();

    void init(/* args */);
    void deinit();

    virtual void setX(int16_t x);
	  virtual void setY(int16_t y);
    virtual void setFade(int8_t fade);


    void addObj(oled_obj* obj, bool isFocusEn);
    void focusObj(uint8_t direction);
    void setPosOffset(int16_t delta_x, int16_t delta_y);
		void fading(fade_type fade, uint16_t duration, t_anim_end_cb animEndCb);
    void move(int16_t delta_x, int16_t delta_y, uint16_t duration, t_anim_end_cb animEndCb);
		oled_obj* getFocusObj();
    int8_t getFocusIndex();
    void setIsFillIndicator(bool isFill);

};

#endif