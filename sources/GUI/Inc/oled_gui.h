//For every widget in this GUI, the initial code is put in constructor
//But for specific device like BLE, oled display, ... the init method is reconmended to init device

#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define OLED_USE_ANIM 1
#define OLED_USE_BMP 1
#define OLED_USE_LABEL 1
#define OLED_USE_SW 1
#define OLED_USE_CANVAS 1
#define OLED_USE_SLIDER 0
#define OLED_USE_GROUP 1
#define OLED_USE_INDICATOR 1
#define OLED_USE_CONSOLE 1


#if OLED_USE_ANIM == 1
#define	ANIM_TIME_FAST		150	//ms
#define	ANIM_TIME_NORM		300	//ms
#define	ANIM_TIME_SLOW		600	//ms
/*******?????**********/
#define ANIM_TYPE	2
//0:	ANIM_EASE_IN_EASE_OUT		//??????
//1:	ANIM_EASE_IN						//??	
//2:	ANIM_EASE_OUT						//??
//3:	ANIM_LINEAR							//??
//4:	ANIM_BOUNCE							//??
#endif

#define	OLED_REFRESH_T		10  //ms

#if OLED_USE_GROUP == 1
#include "obj_group.h"
#endif

#if OLED_USE_INDICATOR == 1
#include "obj_indicator.h"
#endif

#if OLED_USE_ANIM == 1
#include "oled_anim.h"
#endif

#if OLED_USE_BMP == 1
#include "obj_bmp.h"
#endif

#if OLED_USE_LABEL == 1
#include "obj_label.h"
#endif


#if OLED_USE_SW == 1
#include "obj_switch.h"
#endif

#if OLED_USE_CANVAS == 1
#include "obj_canvas.h"
#endif

#if OLED_USE_SLIDER == 1
#include "oled_slider.h"
#endif


void gui_timeTick(void);

extern uint16_t oled_getTimestamp(void);

extern uint16_t oled_tickElaps(uint16_t prev_tick);

extern void gui_init();

extern void gui_run();

#ifdef __cplusplus
}
#endif