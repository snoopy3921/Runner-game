#ifndef __OBJ_INDICATOR_H__
#define __OBJ_INDICATOR_H__

#include "oled_obj.h"

class obj_indicator : public oled_obj
{
private:
    /* data */
    oled_obj* target;
    uint8_t gap;
    bool isFill;
public:
    obj_indicator(/* args */);
    obj_indicator(oled_obj* target, uint8_t gap, bool isFill);
    ~obj_indicator();

    void init(oled_obj* target, uint8_t gap, bool isFill);
    virtual void deinit();

    void setGap(uint8_t gap){this->gap = gap;}
    uint8_t getGap(){return this->gap;}
    void setIsFill(bool isFill){this->isFill = isFill;}
    bool getIsFill(){return this->isFill;}
		void update(void);
    void setTarget(oled_obj* target);
    oled_obj* getTarget(){return this->target;}
    virtual void draw();
};

#endif