#include "scr_manager.h"
#include "oled_gui.h"

#include "os_msg.h"
#include "main.h"
#include "game.h"
#include "gui_port.h"


obj_label lb1, lb2, lb3, lb4, lb5 ;
obj_group gr1, gr2;
obj_bmp bmp1, bmp2, bmp3, bmp4;
obj_canvas cv1, cv2, cv3;
oled_anim an1, an2, an3;

static void setup_function(msg_t * msg)
{
	lb1.init(23, 7);
	lb2.init(23, 15);
	lb3.init(23, 25);
	lb4.init(23, 35);
	lb5.init(23, 45);
	
	lb1.print("   __    _  _ ");
	lb2.print("  /__\\  ( )/ )");
	lb3.print(" /(__)\\ (   (");
	lb4.print("(__)(__)(_)\\_)");
	lb5.print("    AK-mOS     ");

	gr2.init();
	gr2.addObj(&lb1, false);
	gr2.addObj(&lb2, false);
	gr2.addObj(&lb3, false);
	gr2.addObj(&lb4, false);
	gr2.addObj(&lb5, false);

	gr2.setFade(4);
	gr2.fading(FADE_IN, 300, ANIM_NULL_CB);

	os_task_delay(350);
}
static void loop_funtion(msg_t * msg)
{
	
	// gr1->setFade(0);
	// gr1->fading(FADE_OUT, 200, ANIM_NULL_CB);
	// os_task_delay(300);
	// gr1->setFade(4);
	// gr1->fading(FADE_IN, 200, ANIM_NULL_CB);
	// os_task_delay(300);
	
}

static void event_function(msg_t * msg)
{
      switch (msg->sig)
      {
      case AC_DISPLAY_BUTTON_MODE_PRESSED:	
			scr_curr_set_stt(SCR_STT_READY); //Set back to ready state to make loop_func stop
			gr2.setFade(0);
			gr2.fading(FADE_OUT, 300, ANIM_NULL_CB);
			os_task_delay(350);
			lb1.deinit();
			lb2.deinit();
			lb3.deinit();
			lb4.deinit();
			lb5.deinit();
			gr2.deinit();
			scr_shift(SCR_MENU_GAME);
            break;
      case AC_DISPLAY_BUTTON_UP_PRESSED:
			//gr1.focusObj(FOCUS_NEXT);
			os_task_delay(350);
            break;   
      default:
            break;
      }
}


void scr_startup_register( void )
{
      scr_reg(SCR_START_UP, nullptr, nullptr, setup_function, loop_funtion, event_function);
}