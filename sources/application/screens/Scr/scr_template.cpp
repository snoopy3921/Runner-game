#include "scr_manager.h"
#include "oled_gui.h"

#include "os_msg.h"
#include "main.h"
#include "gui_port.h"



static void setup_function(msg_t * msg)
{


}
static void loop_funtion(msg_t * msg)
{

	
}

static void event_function(msg_t * msg)
{
      switch (msg->sig)
      {
      case AC_DISPLAY_BUTTON_MODE_PRESSED:
            scr_curr_set_stt(SCR_STT_READY); //Set back to ready state to make loop_func stop

            scr_shift(SCR_START_UP);
            break;
      case AC_DISPLAY_BUTTON_UP_PRESSED:

		os_task_delay(350);
            break;    
      default:
            break;
      }
}


void scr_menu_game_register( void )
{
    scr_reg(SCR_MENU_GAME, nullptr, nullptr, setup_function, loop_funtion, event_function);
}