#include "task_list.h"
#include "scr_manager.h"
#include "os_msg.h"
#include "oled_gui.h"
#include "button.h"
#include "main.h"

void task_scr(void *p_arg)
{
    msg_t * msg;

    scr_mng_init();

    while(1)
    {
        msg = os_task_wait_for_msg(5);
        scr_mng_run(msg);
        if(msg != NULL) os_msg_free(msg);
    }
}