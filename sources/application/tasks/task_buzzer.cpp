#include "task_list.h"
#include "buzzer.h"
#include "main.h"

static void play_track(const Tone_TypeDef * melody)
{   
    int i = 0;
    BUZZER_Disable();
    while((melody)->duration != 0)
    {            
        BUZZER_Enable(melody->frequency, 123);
        os_task_delay((melody->duration)*15);
        melody++;
        i++;
    }  
    BUZZER_Disable();
}

void task_buzzer(void *p_arg)
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
        
        if(sig != OS_CFG_DELAY_MAX) 
        {
            switch (sig)
            {
            case AC_BUZZER_PLAY_TONE_MOVE:
                play_track(tones_USB_dis);
                break;
            case AC_BUZZER_PLAY_TONE_DEATH:
                play_track(tones_startup);
                break;
            default:
                break;
            }
            sig = OS_CFG_DELAY_MAX - 1;
        }
    }
}