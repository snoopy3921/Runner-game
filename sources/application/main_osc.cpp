#include "main.h"
#include "io_cfg.h"
#include "system.h"

#include "oled_gui.h"
#include "gui_port.h"
#include "scr_manager.h"

#include "Adafruit_GFX.h"


#include "stm32l1xx_dma.h"

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint8_t head_signal = 0;

uint8_t signal1[128];
uint8_t signal2[128];
uint8_t signal3[128];

__IO uint16_t signalADC[128];


int yValues[120] = {0};
int w = 120;
int current = 0;

void DMA_setup()
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	DMA_InitTypeDef DMA_StructInit;
	DMA_StructInit.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
	DMA_StructInit.DMA_MemoryBaseAddr = (uint32_t)signalADC;
	DMA_StructInit.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_StructInit.DMA_BufferSize = 128;
	DMA_StructInit.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_StructInit.DMA_MemoryInc	= DMA_MemoryInc_Enable;
	DMA_StructInit.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_StructInit.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_StructInit.DMA_Mode = DMA_Mode_Circular;
	DMA_StructInit.DMA_Priority = DMA_Priority_Medium;
	DMA_StructInit.DMA_M2M = DMA_M2M_Disable;

	DMA_Init(DMA1_Channel1, &DMA_StructInit);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}


// Define Timer Frequency and Period
//#define TIMER_FREQUENCY_HZ ((uint32_t)10000000)  // 10MHz
#define TIMER_FREQUENCY_HZ   1000000
void TIM2_setup()
{
    // 1. Enable the TIM2 peripheral clock
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 2. Timer base configuration
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    // Configure Timer frequency
    uint16_t prescaler = (SystemCoreClock / TIMER_FREQUENCY_HZ) - 1;

    TIM_TimeBaseStructure.TIM_Period = 29 - 1; // 10MHz/10 = 1MHz
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler; // 
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);

    // 4. Start the Timer
    TIM_Cmd(TIM2, ENABLE);
}


void task_osc(void *p_arg)
{

}


int main()
{
    SysInitConsole();

    led_life_init();

	view_render.initialize();
	view_render.display_on();



	DMA_setup();
	TIM2_setup();

	
	pinout_header_init();

	button_init(&btn_mode,	50,	BUTTON_MODE_ID,	io_button_mode_init,	io_button_mode_read,	btn_mode_callback);
	button_init(&btn_up,	50,	BUTTON_UP_ID,	io_button_up_init,		io_button_up_read,		btn_up_callback);
	button_init(&btn_down,	50,	BUTTON_DOWN_ID,	io_button_down_init,	io_button_down_read,	btn_down_callback);

	button_enable(&btn_mode);
	button_enable(&btn_up);
	button_enable(&btn_down);
	

	
	

    int i = 0;
	uint16_t val;
	uint8_t ch = 0;
	int time1, time2;
    while(1)
    {	

        
        //for(int i = 0; i < 100000; i++);
		view_render.clear();

		// view_render.setCursor(0, 0);
		// view_render.print("ADC PA0 value: %f", (signalADC[0] * 3.3) / 4096);

		// view_render.setCursor(0, 15);
		// view_render.print("ADC PA4 value: %f", (signalADC[1] * 3.3) / 4096);

		// view_render.setCursor(0, 30);
		// view_render.print("ADC PB15 value: %f", (signalADC[2] * 3.3) / 4096);

		for(int i = 1; i < 128; i ++)
		{
			int data0 = map(signalADC[i-1], 0, 2500, 64, 0);
			int data1 = map(signalADC[i], 0, 2500, 64, 0);
			view_render.drawLine(i-1, data0, i , data1, WHITE);
			//view_render.drawPixel(i, data, WHITE);
		}



		// for(int i=0;i<128;i++)
		// {
		// 	if(signalADC[i] == 1) {time1=i; break;}
		// }
		// for(int i=time1 + 1;i<128;i++)
		// {
		// 	if(signalADC[i] == 1) {time2=i; break;}
		// }

		//view_render.setCursor(0, 0);
		//view_render.print("T: %d dot; %f Hz", 2*(time2 - time1), (float)100000/(2*(time2 - time1)));
		
		//SYS_PRINT("%f\n", (signalADC[2] * 3.3) / 4096);
		//if(ch > 2) ch = 0;

		view_render.update();
        //led_life_toggle();

		button_timer_polling(&btn_mode);
        button_timer_polling(&btn_up);
        button_timer_polling(&btn_down);

		
    }
}
