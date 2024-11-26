#include "task_list.h"
#include "button.h"
#include "main.h"
#include "os_msg.h"
#include "os_task.h"
#include "system.h"
#include "stm32l1xx_tim.h"

button_t btn_mode;
button_t btn_up;
button_t btn_down;

void btn_mode_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
        os_task_post_msg_pure(TASK_SCR_ID, AC_DISPLAY_BUTTON_MODE_PRESSED);
	}
		break;

	case BUTTON_SW_STATE_LONG_PRESSED: {
		os_task_post_msg_pure(TASK_SCR_ID, AC_DISPLAY_BUTTON_MODE_LONG_PRESSED);
	}
		break;

	case BUTTON_SW_STATE_RELEASED: {
		os_task_post_msg_pure(TASK_SCR_ID, AC_DISPLAY_BUTTON_MODE_RELEASED);
	}
		break;

	default:
		break;
	}
}

void btn_up_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
        os_task_post_msg_pure(TASK_SCR_ID, AC_DISPLAY_BUTTON_UP_PRESSED);   
	}
		break;

	case BUTTON_SW_STATE_LONG_PRESSED: {
	}
		break;

	case BUTTON_SW_STATE_RELEASED: {
	}
		break;

	default:
		break;
	}
}

void btn_down_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
		os_task_post_msg_pure(TASK_SCR_ID, AC_DISPLAY_BUTTON_DOWN_PRESSED);
	}
		break;

	case BUTTON_SW_STATE_LONG_PRESSED: {

	}
		break;

	case BUTTON_SW_STATE_RELEASED: {

	}
		break;

	default:
		break;
	}
}


void task_btn(void *p_arg)
{
    while(1)
    {
        button_timer_polling(&btn_mode);
        button_timer_polling(&btn_up);
        button_timer_polling(&btn_down);
        os_task_delay(10);
    }
}