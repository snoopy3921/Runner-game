#include "task_list.h"
#include "oled_gui.h"
#include "main.h"

void task_gui(void *p_arg)
{
    while(1)
    {
        gui_run();
    }
}