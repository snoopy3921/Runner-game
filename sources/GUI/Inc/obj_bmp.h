#ifndef __OBJ_BMP_H__
#define __OBJ_BMP_H__

#include "oled_obj.h"

class obj_bmp : public oled_obj
{
private:
    /* data */

public:
    obj_bmp(/* args */);
    obj_bmp(int16_t x, int16_t y, int16_t w, int16_t h);
    ~obj_bmp();

    void init(int16_t x, int16_t y, int16_t w, int16_t h);
    void deinit();

    void setBmp(const uint8_t* src);
    virtual void draw();
};

#endif