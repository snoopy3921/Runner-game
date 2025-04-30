#include "task_list.h"
#include "button.h"
#include "main.h"
#include "os_msg.h"
#include "os_task.h"
#include "system.h"
#include "stm32l1xx_tim.h"
#include "os_cpu.h"


button_t btn_mode;
button_t btn_up;
button_t btn_down;



#if TX_MODE
static uint8_t transmit_payload;
#endif
void btn_mode_callback(void* b) {
	button_t* me_b = (button_t*)b;
	switch (me_b->state) {
	case BUTTON_SW_STATE_PRESSED: {
        os_task_post_msg_pure(TASK_SCR_ID, AC_DISPLAY_BUTTON_MODE_PRESSED);
	#if TX_MODE
		transmit_payload = AC_DISPLAY_BUTTON_MODE_PRESSED;
		nrf24_transmit(&transmit_payload, 1, NO_ACK_MODE);
		while(nrf24_transmit_status() == TRANSMIT_IN_PROGRESS);
	#endif
	}
		break;

	case BUTTON_SW_STATE_LONG_PRESSED: {
		os_task_post_msg_pure(TASK_SCR_ID, AC_DISPLAY_BUTTON_MODE_LONG_PRESSED);
	#if TX_MODE
		transmit_payload = AC_DISPLAY_BUTTON_MODE_LONG_PRESSED;
		nrf24_transmit(&transmit_payload, 1, NO_ACK_MODE);
		while(nrf24_transmit_status() == TRANSMIT_IN_PROGRESS);
	#endif
	}
		break;

	case BUTTON_SW_STATE_RELEASED: {
		os_task_post_msg_pure(TASK_SCR_ID, AC_DISPLAY_BUTTON_MODE_RELEASED);
	#if TX_MODE
		transmit_payload = AC_DISPLAY_BUTTON_MODE_RELEASED;
		nrf24_transmit(&transmit_payload, 1, NO_ACK_MODE);
		while(nrf24_transmit_status() == TRANSMIT_IN_PROGRESS);
	#endif
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
	#if TX_MODE
		transmit_payload = AC_DISPLAY_BUTTON_UP_PRESSED;
		nrf24_transmit(&transmit_payload, 1, NO_ACK_MODE);
		while(nrf24_transmit_status() == TRANSMIT_IN_PROGRESS);
	#endif
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
	#if TX_MODE
		transmit_payload = AC_DISPLAY_BUTTON_DOWN_PRESSED;
		nrf24_transmit(&transmit_payload, 1, NO_ACK_MODE);
		while(nrf24_transmit_status() == TRANSMIT_IN_PROGRESS);
	#endif
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
#if RX_MODE
static uint8_t received_payload;
#ifdef __cplusplus
extern "C"
{
#endif
	void nRF24_Handler()
	{
//		DISABLE_INTERRUPTS

		if (EXTI_GetITStatus(EXTI_Line1) == SET)  {    /* Clear the EXTI line 4 pending bit */    
			EXTI_ClearITPendingBit(EXTI_Line1);
			while(nrf24_receive(&received_payload, 1) == RECEIVE_FIFO_EMPTY);    //poll and receive in one simple function call
			os_task_post_msg_pure(TASK_SCR_ID, received_payload);
			nrf24_clear_interrupt_mask();
		}
//		ENABLE_INTERRUPTS
	}

#ifdef __cplusplus
}
#endif
#endif
void task_btn(void *p_arg)
{
#if TX_MODE
    nrf24_device(TRANSMITTER, RESET);     //initializing nrf24l01+ as a transmitter using one simple function
#else
    nrf24_device(RECEIVER, RESET);      //initializing nrf24l01+ as a receiver device with one simple function call
#endif
    while(1)
    {
        button_timer_polling(&btn_mode);
        button_timer_polling(&btn_up);
        button_timer_polling(&btn_down);
        os_task_delay(10);
    }
}