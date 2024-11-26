#include "task_list.h"

const task_t app_task_table[] = {
    /*************************************************************************/
    /* TASK */
    /* TASK_ID          	task_func       arg     prio     msg_queue_size               stk_size */
    /*************************************************************************/
    {TASK_GUI_ID,   	    task_gui,       NULL,   9,      0,    150},
    {TASK_SCR_ID,   	    task_scr,       NULL,   8,      16,   250},
    //{TASK_OSC_ID,   	    task_scr,       NULL,   1,      0,    600},    
    {TASK_TIMER_ID,   	    task_timer,     NULL,   8,      8,    100},
    {TASK_BTN_ID,   	    task_btn,       NULL,   0,      0,    100},
    {TASK_BUZZER_ID,   	    task_buzzer,    NULL,   1,      8,    100},
};
