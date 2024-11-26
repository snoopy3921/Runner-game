#ifndef __MAIN_H__
#define __MAIN_H__


#include "os_kernel.h"
#include "os_mem.h"
#include "os_task.h"
#include "os_msg.h"
#include "task_list.h"
#include "button.h"


/*****************************************************************************/
/*  BUTTON task define
 */
/*****************************************************************************/
#define BUTTON_MODE_ID					(1)
#define BUTTON_UP_ID					(2)
#define BUTTON_DOWN_ID					(3)

extern button_t btn_mode;
extern button_t btn_up;
extern button_t btn_down;

extern void btn_mode_callback(void*);
extern void btn_up_callback(void*);
extern void btn_down_callback(void*);

/* define signal */
enum {
	AC_DISPLAY_BUTTON_MODE_PRESSED = 1,						
	AC_DISPLAY_BUTTON_MODE_LONG_PRESSED,					
	AC_DISPLAY_BUTTON_MODE_RELEASED,
	AC_DISPLAY_BUTTON_UP_PRESSED,							
	AC_DISPLAY_BUTTON_UP_LONG_PRESSED,					
	AC_DISPLAY_BUTTON_UP_RELEASED,
	AC_DISPLAY_BUTTON_DOWN_PRESSED,						
	AC_DISPLAY_BUTTON_DOWN_LONG_PRESSED,					
	AC_DISPLAY_BUTTON_DOWN_RELEASED,
	AC_DISPLAY_GAME_UPDATE
};

/* define signal */
enum {
	AC_BUZZER_PLAY_TONE_MOVE = 1,		
	AC_BUZZER_PLAY_TONE_DEATH				
};



extern int main();

#endif //__MAIN_H__
