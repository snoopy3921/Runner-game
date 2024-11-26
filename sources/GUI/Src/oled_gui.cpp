#include "oled_gui.h"
#include "main.h"
#include "gui_port.h"
#include "system.h"

static uint16_t gui_tick = 0;

uint16_t oled_getTimestamp(void)
{
    return get_tick();
}
uint16_t oled_tickElaps(uint16_t prev_tick)
{
  if(get_tick() >= prev_tick)
	{
		prev_tick = get_tick() - prev_tick;
  } 
	else
	{
		prev_tick = MAX_GUI_TICK - prev_tick + 1;
    prev_tick += get_tick();
  }
  return prev_tick;
}

void gui_init()
{
	gui_tick = 0;
  oled_obj::oled_obj_init();
  oled_anim::oled_anim_init();	
	display_init();  
  SYS_PRINT("Size of obj: %d\r\n", SIZE_OF_OBJ);
  SYS_PRINT("Size of anim: %d\r\n", SIZE_OF_ANIM);  
}


void gui_run()
{
  oled_obj::oled_obj_draw();      
  oled_anim::oled_anim_run();
}


