/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   05/09/2016
 ******************************************************************************
**/
#include <stdint.h>
#include <stdbool.h>

#include "system_copy.h"


#include "system_stm32l1xx.h"
#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"
#include "core_cm3.h"


//#pragma GCC optimize ("O3")

/*****************************************************************************/
/* linker variable                                                           */
/*****************************************************************************/
extern uint32_t _ldata;
extern uint32_t _data;
extern uint32_t _edata;
extern uint32_t _bss;
extern uint32_t _ebss;
extern uint32_t _sstack;
extern uint32_t _estack;

extern void (*__preinit_array_start[])();
extern void (*__preinit_array_end[])();
extern void (*__init_array_start[])();
extern void (*__init_array_end[])();
extern void _init();
extern void _fini();

/*****************************************************************************/
/* static function prototype                                                 */
/*****************************************************************************/
/*****************************/
/* system interrupt function */
/*****************************/
void default_handler();
void Reset_Handler();

/*****************************/
/* user interrupt function   */
/*****************************/
void exti_line1_irq();
void exti_line15_irq();
void timer6_irq();
void timer4_irq();
void timer7_irq();
void uart1_irq();
void uart2_irq();
void buzzer_irq( void );


/* cortex-M processor fault exceptions */
void nmi_handler()          __attribute__ ((weak));
void hard_fault_handler()   __attribute__ ((weak));
void mem_manage_handler()   __attribute__ ((weak));
void bus_fault_handler()    __attribute__ ((weak));
void usage_fault_handler()  __attribute__ ((weak));

/* cortex-M processor non-fault exceptions */
void dg_monitor_handler()   __attribute__ ((weak, alias("default_handler")));
void PendSV_Handler()		__attribute__ ((weak));
void SVC_Handler()			__attribute__ ((weak));
void SysTick_Handler()		__attribute__ ((weak));

/* external interrupts */
void svc_exe(uint32_t* svc_args);

/*****************************************************************************/
/* system variable                                                           */
/*****************************************************************************/
system_info_t system_info;

/*****************************************************************************/
/* interrupt vector table                                                    */
/*****************************************************************************/
__attribute__((section(".isr_vector")))
void (* const isr_vector[])() = {
		((void (*)())(uint32_t)&_estack),		//	The initial stack pointer
		Reset_Handler,							//	The reset handler
		nmi_handler,							//	The NMI handler
		hard_fault_handler,						//	The hard fault handler
		mem_manage_handler,						//	The MPU fault handler
		bus_fault_handler,						//	The bus fault handler
		usage_fault_handler,					//	The usage fault handler
		0,										//	Reserved
		0,										//	Reserved
		0,										//	Reserved
		0,										//	Reserved
		SVC_Handler,							//	SVCall handler
		dg_monitor_handler,						//	Debug monitor handler
		0,										//	Reserved
		PendSV_Handler,							//	The PendSV handler
		SysTick_Handler,						//	The SysTick handler

		//External Interrupts
		default_handler,						//	Window Watchdog
		default_handler,						//	PVD through EXTI Line detect
		default_handler,						//	Tamper and Time Stamp
		default_handler,						//	RTC Wakeup
		default_handler,						//	FLASH
		default_handler,						//	RCC
		default_handler,						//	EXTI Line 0
		exti_line1_irq,							//	EXTI Line 1
		default_handler,						//	EXTI Line 2
		default_handler,						//	EXTI Line 3
		default_handler,						//	EXTI Line 4
		default_handler,						//	DMA1 Channel 1
		default_handler,						//	DMA1 Channel 2
		default_handler,						//	DMA1 Channel 3
		default_handler,						//	DMA1 Channel 4
		default_handler,						//	DMA1 Channel 5
		default_handler,						//	DMA1 Channel 6
		default_handler,						//	DMA1 Channel 7
		default_handler,						//	ADC1
		default_handler,						//	USB High Priority
		default_handler,						//	USB Low  Priority
		default_handler,						//	DAC
		default_handler,						//	COMP through EXTI Line
		default_handler,						//	EXTI Line 9..5
		default_handler,						//	LCD
		default_handler,						//	TIM9
		default_handler,						//	TIM10
		default_handler,						//	TIM11
		default_handler,						//	TIM2
		
		buzzer_irq,								//	TIM3
		

		default_handler,						//	TIM4


		default_handler,						//	I2C1 Event
		default_handler,						//	I2C1 Error
		default_handler,						//	I2C2 Event
		default_handler,						//	I2C2 Error
		default_handler,						//	SPI1
		default_handler,						//	SPI2
		uart1_irq,								//	USART1


		default_handler,						//	USART2


		default_handler,						//	USART3
		default_handler,						//	EXTI Line 15..10
		default_handler,						//	RTC Alarm through EXTI Line
		default_handler,						//	USB FS Wakeup from suspend
		default_handler,						//	TIM6
		timer7_irq,								//	TIM7
		};

void __attribute__((naked))
sys_ctrl_delay(volatile uint32_t count)
{
	(void)count;
	__asm("    subs    r0, #1\n"
	"    bne     sys_ctrl_delay\n"
	"    bx      lr");
}

void _init() {
	/* dummy */
}

void _fini() {
	/* dummy */
}

/*****************************************************************************/
/* static function defination                                                */
/*****************************************************************************/
void default_handler() {
	
}

void Reset_Handler() {
	/* MUST BE disable interrupt */
	__disable_irq();

	volatile uint32_t *pSrc = &_ldata;
	volatile uint32_t *pDest = &_data;
	volatile unsigned i, cnt;

	/* init system */
	SystemInit();

	/* copy init data from FLASH to SRAM */
	while(pDest < &_edata) {
		*pDest++ = *pSrc++;
	}

	/* zero bss */
	for (pDest = &_bss; pDest < &_ebss; pDest++) {
		*pDest = 0UL;
	}




	/* invoke all static constructors */
	cnt = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < cnt; i++)
		__preinit_array_start[i]();

	_init();

	cnt = __init_array_end - __init_array_start;
	for (i = 0; i < cnt; i++)
		__init_array_start[i]();

	/* wait configuration stable */
	sys_ctrl_delay(100);  /* wait 300 cycles clock */


	/* entry app function */
	main();
}

void nmi_handler() {

}

void hard_fault_handler() {
  while(1)
  {
        for(int i = 0; i < 500000; i++);
        led_life_toggle();
  }
}

void mem_manage_handler() {

}

void bus_fault_handler() {

}

void usage_fault_handler() {

}



void svc_exe(uint32_t* svc_args) {

}

/************************/
/* external interrupts  */
/************************/
void uart1_irq() {

}

void uart2_irq() {

}

void exti_line1_irq() {

}

void exti_line15_irq() {

}

void timer6_irq() {

}

void timer7_irq() {

}

void timer4_irq() {

}
