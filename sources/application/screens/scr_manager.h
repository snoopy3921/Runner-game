#ifndef __SCR_MANAGER_H__
#define __SCR_MANAGER_H__

#include <stdint.h>
#include "os_msg.h"


typedef void(*function_ptr)(msg_t * msg);
typedef void(*function_ptr_no_arg)(void);

typedef struct {
	uint8_t *title_ptr;
	uint8_t *icon_ptr;
	uint8_t status;
	function_ptr setup_function;
	function_ptr loop_funtion;
	function_ptr event_function;
}screen_t;

enum SCR_ID{
	SCR_NULL = -1,
	SCR_START_UP,
	SCR_MENU_GAME,
	SCR_MAIN_GAME,
	SCR_SETTING_GAME,
	SCR_CHART_GAME,
	SCR_MAX
};

enum SCR_STT{
	SCR_STT_READY = 0,
	SCR_STT_RUNNING
};

extern screen_t screen_list[SCR_MAX];


extern void scr_mng_init( void );
extern void scr_mng_run( msg_t * msg );


extern void scr_reg(uint8_t scr_id,
					uint8_t *title_ptr,
					uint8_t *icon_ptr,
					function_ptr setup_function,
					function_ptr loop_funtion,
					function_ptr event_function);

extern void scr_shift( uint8_t next_screen );
extern void scr_curr_set_stt(uint8_t status);

extern void scr_startup_register( void );
extern void scr_menu_game_register( void );
extern void scr_main_game_register( void );
extern void scr_setting_game_register( void );
extern void scr_chart_game_register( void );


#endif