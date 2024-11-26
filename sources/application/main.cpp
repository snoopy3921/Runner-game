#include "main.h"
#include "io_cfg.h"
#include "system.h"

#include "oled_gui.h"
#include "gui_port.h"
#include "scr_manager.h"

#include "buzzer.h"

int main()
{
    SysInitConsole();

    led_life_init();

	/* button init */
    button_init(&btn_mode,	10,	BUTTON_MODE_ID,	io_button_mode_init,	io_button_mode_read,	btn_mode_callback);
    button_init(&btn_up,	10,	BUTTON_UP_ID,	io_button_up_init,		io_button_up_read,		btn_up_callback);
	button_init(&btn_down,	10,	BUTTON_DOWN_ID,	io_button_down_init,	io_button_down_read,	btn_down_callback);

	button_enable(&btn_mode);
	button_enable(&btn_up);
	button_enable(&btn_down);

    BUZZER_Init();

    gui_init();
	pinout_header_init();

    os_init();
    os_task_create_list((task_t*)app_task_table, TASK_EOT_ID);
    os_run();



    while(1)
    {	

    }
}