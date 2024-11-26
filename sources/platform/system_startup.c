#include <stdint.h>
#include "system_startup.h"

#include "system_stm32l1xx.h"
#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"
#include "core_cm3.h"

#include "io_cfg.h"

#include "os_cpu.h"

#include "main.h"


/*****************************************************************************/
/* linker variable                                                           */
/*****************************************************************************/
extern uint32_t _estack;

extern uint32_t _edata;
extern uint32_t _sdata;
extern uint32_t _ldata;
extern uint32_t _ebss;
extern uint32_t _sbss;

extern void (*__preinit_array_start[])();
extern void (*__preinit_array_end[])();
extern void (*__init_array_start[])();
extern void (*__init_array_end[])();

void Reset_Handler(void);

void NMI_Handler(void)           __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)     __attribute__ ((weak));
void MemFault_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));

void SVC_Handler(void)			__attribute__ ((weak));
void DebugMon_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)		__attribute__ ((weak));
void SysTick_Handler(void)		__attribute__ ((weak));

void Default_Handler(void);

void USART1_IRQHandler(void)	__attribute__ ((weak));

void __attribute__((naked))
sys_ctrl_delay(volatile uint32_t count)
{
	(void)count;
	__asm("    subs    r0, #1\n"
	"    bne     sys_ctrl_delay\n"
	"    bx      lr");
}

void sys_cfg_clock() {
	/* Enable the HSI oscillator */
	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	SystemCoreClockUpdate();

	/* NVIC configuration */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}

void _init() {
	/* dummy */
}
void _fini() {
	/* dummy */
}


__attribute__((section(".isr_vector"))) 
void (* const vectors[])() = 
{
    ((void (*)())(uint32_t)&_estack),
    Reset_Handler,             /*     Reset Handler */
    NMI_Handler,                         /* -14 NMI Handler */
    HardFault_Handler,                   /* -13 Hard Fault Handler */
    MemFault_Handler,                   /* -12 MPU Fault Handler */
    BusFault_Handler,                    /* -11 Bus Fault Handler */
    UsageFault_Handler,                  /* -10 Usage Fault Handler */
    0,                                  /*     Reserved */
    0,                                   /*     Reserved */
    0,                                   /*     Reserved */
    0,                                   /*     Reserved */
    SVC_Handler,                         /*  -5 SVCall Handler */
    DebugMon_Handler,                    /*  -4 Debug Monitor Handler */
    0,                                   /*     Reserved */
    PendSV_Handler,                      /*  -2 PendSV Handler */
    SysTick_Handler,                     /*  -1 SysTick Handler */
		//External Interrupts

	Default_Handler,						//	Window Watchdog
	Default_Handler,						//	PVD through EXTI Line detect
	Default_Handler,						//	Tamper and Time Stamp
	Default_Handler,						//	RTC Wakeup
	Default_Handler,						//	FLASH
	Default_Handler,						//	RCC
	Default_Handler,						//	EXTI Line 0
	Default_Handler,							//	EXTI Line 1
	Default_Handler,						//	EXTI Line 2
	Default_Handler,						//	EXTI Line 3
	Default_Handler,						//	EXTI Line 4
	Default_Handler,						//	DMA1 Channel 1
	Default_Handler,						//	DMA1 Channel 2
	Default_Handler,						//	DMA1 Channel 3
	Default_Handler,						//	DMA1 Channel 4
	Default_Handler,						//	DMA1 Channel 5
	Default_Handler,						//	DMA1 Channel 6
	Default_Handler,						//	DMA1 Channel 7
	Default_Handler,						//	ADC1
	Default_Handler,						//	USB High Priority
	Default_Handler,						//	USB Low  Priority
	Default_Handler,						//	DAC
	Default_Handler,						//	COMP through EXTI Line
	Default_Handler,						//	EXTI Line 9..5
	Default_Handler,						//	LCD
	Default_Handler,						//	TIM9
	Default_Handler,						//	TIM10
	Default_Handler,						//	TIM11
	Default_Handler,						//	TIM2
	
	Default_Handler,								//	TIM3
	
	Default_Handler,							//	TIM4


	Default_Handler,						//	I2C1 Event
	Default_Handler,						//	I2C1 Error
	Default_Handler,						//	I2C2 Event
	Default_Handler,						//	I2C2 Error
	Default_Handler,						//	SPI1
	Default_Handler,						//	SPI2

	USART1_IRQHandler,								//	USART1

	Default_Handler,						//	USART2

	Default_Handler,						//	USART3
	Default_Handler,						//	EXTI Line 15..10
	Default_Handler,						//	RTC Alarm through EXTI Line
	Default_Handler,						//	USB FS Wakeup from suspend
	Default_Handler,						//	TIM6
	Default_Handler								//	TIM7
    
};


void HardFault_Handler(void)
{
  while(1)
  {
        for(int i = 0; i < 500000; i++);
        led_life_toggle();
  }
}


void Default_Handler(void)
{
  while(1)
  {
        for(int i = 0; i < 500000; i++);
        led_life_toggle();
  }
}


void Reset_Handler(void)
{
	__disable_irq();

    //copy .data to SRAM
    uint32_t size = &_edata - &_sdata;

    uint32_t * p_des = &_sdata;//Start of .data in virtual mode (SRAM)
    uint32_t * p_src = &_ldata; //Start of .data in load mode

    for(uint32_t i = 0; i < size; i++)
    {
        *p_des++ = *p_src++;
    }

    //copy .bss to SRAM
    size = &_ebss - &_sbss;

    p_des = &_sbss;
    for(uint32_t i = 0; i < size; i++)
    {
        *p_des++ = 0UL; //Init zero
    }


	volatile unsigned i, cnt;
	/* invoke all static constructors */
	cnt = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < cnt; i++)
		__preinit_array_start[i]();

	_init();

	cnt = __init_array_end - __init_array_start;
	for (i = 0; i < cnt; i++)
		__init_array_start[i]();


	SystemInit();    
	sys_cfg_clock(); /* init system clock */
	/* wait configuration stable */
	sys_ctrl_delay(100);  /* wait 300 cycles clock */

    main();
}



