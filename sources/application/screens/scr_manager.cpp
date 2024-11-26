#include "scr_manager.h"
#include "os_task.h"
#include "os_msg.h"


screen_t screen_list[SCR_MAX];
static uint8_t curr_screen;
static uint8_t next_screen;

/*
void task_screen(void* p_arg)
{
      msg_t * msg;


      for(;;)
      {
            msg_t * msg = os_task_wait_for_msg(10);
            if(msg!= NULL)
            {
                  screen_list[curr_screen].event_function(msg);
                  os_msg_free(msg);
            }
                                    
            if(screen_list[curr_screen].status == SCR_STT_RUNNING)
            {                  
                  screen_list[curr_screen].loop_funtion(NULL);
            }
						
      }
}
*/


void scr_mng_init( void )
{
      scr_startup_register();
      scr_menu_game_register();
      scr_main_game_register();
      scr_setting_game_register();
      scr_chart_game_register();
      curr_screen = SCR_START_UP;
      next_screen = SCR_START_UP;
      screen_list[curr_screen].setup_function(NULL);
      scr_curr_set_stt(SCR_STT_RUNNING);
}

void scr_mng_run( msg_t * msg )
{
      if(msg != NULL) screen_list[curr_screen].event_function(msg);
                  
      if(screen_list[curr_screen].status == SCR_STT_RUNNING)
      {                  
            screen_list[curr_screen].loop_funtion(NULL);
      }
}

void scr_reg(
      uint8_t scr_id,
	uint8_t *title_ptr,
	uint8_t *icon_ptr,
	function_ptr setup_function,
	function_ptr loop_funtion,
	function_ptr event_function
)
{
      screen_list[scr_id].title_ptr = title_ptr;
      screen_list[scr_id].icon_ptr = icon_ptr;
      screen_list[scr_id].status = SCR_STT_READY;
      screen_list[scr_id].setup_function = setup_function;
      screen_list[scr_id].loop_funtion = loop_funtion;
      screen_list[scr_id].event_function = event_function;
}

void scr_shift( uint8_t next_screen )
{
      if(curr_screen == next_screen) return;
      else
      {
            screen_list[next_screen].setup_function(NULL);
            curr_screen = next_screen;
            scr_curr_set_stt(SCR_STT_RUNNING);
      }
}
void scr_curr_set_stt(uint8_t status)
{
      screen_list[curr_screen].status = status;
}