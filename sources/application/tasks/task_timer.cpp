#include "task_list.h"
#include "scr_manager.h"
#include "os_msg.h"
#include "oled_gui.h"
#include "button.h"
#include "main.h"

void task_timer(void *p_arg)
{
    msg_t *msg;
    int32_t sig = OS_CFG_DELAY_MAX - 1;

    while (1)
    {   
        msg = os_task_wait_for_msg(sig);
        if(msg != NULL) 
        {
            sig = msg->sig;
            os_msg_free(msg);
        }
        if(sig != OS_CFG_DELAY_MAX - 1) 
        {
            os_task_post_msg_pure(TASK_SCR_ID, AC_DISPLAY_GAME_UPDATE);
        }
    }
}