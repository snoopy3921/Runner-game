/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   05/09/2016
 ******************************************************************************
**/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "io_cfg.h"
#include "eeprom.h"
//#pragma GCC optimize ("O3")




/******************************************************************************
* Timer Delay
*******************************************************************************/
void timer_delay_init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	
	//Freq = 1MHz / 1000 = 1kHz
	TIM_TimeBaseInitTypeDef TIM_InitStruct; 	
	TIM_InitStruct.TIM_Prescaler = 31 ;								//32/(31+1) = 1 MHz				
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;	
	TIM_InitStruct.TIM_Period = 65535;									//1000 cycsles to reach 1ms		
	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);	
	
	TIM_Cmd(TIM2, ENABLE);	
}


void delay(uint32_t ms)
{
		while(ms > 0)
	{
		TIM_SetCounter(TIM2, 0);
		ms--;
		while(TIM_GetCounter(TIM2) < 1000);
	}
}

/******************************************************************************
* pinout header function
*******************************************************************************/
void pinout_header_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(HEADER_A0_IO_CLOCK, ENABLE);
	RCC_AHBPeriphClockCmd(HEADER_A4_IO_CLOCK, ENABLE);
	RCC_AHBPeriphClockCmd(HEADER_B15_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = HEADER_A0_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(HEADER_A0_IO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = HEADER_A4_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(HEADER_A4_IO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin   = HEADER_B15_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(HEADER_B15_IO_PORT, &GPIO_InitStructure);


	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div1;

	ADC_CommonInit(&ADC_CommonInitStructure);

	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_16Cycles);	//PA0
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_24Cycles);	//PA4
	//ADC_RegularChannelConfig(ADC1, ADC_Channel_21, 3, ADC_SampleTime_24Cycles);	//PB15
	// Covert order PA0 -> PA4 -> PB15

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

	ADC_DMACmd(ADC1, ENABLE);

	ADC_Cmd(ADC1, ENABLE);

	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET);


	ADC_SoftwareStartConv(ADC1);


	
}



/******************************************************************************
* button function
*******************************************************************************/
void io_button_mode_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_MODE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_MODE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_MODE_IO_PORT, &GPIO_InitStructure);
}

void io_button_up_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_UP_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_UP_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_UP_IO_PORT, &GPIO_InitStructure);
}

void io_button_down_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_DOWN_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_DOWN_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_DOWN_IO_PORT, &GPIO_InitStructure);
}

uint8_t io_button_mode_read() {
	return  GPIO_ReadInputDataBit(BUTTON_MODE_IO_PORT,BUTTON_MODE_IO_PIN);
}

uint8_t io_button_up_read() {
	return  GPIO_ReadInputDataBit(BUTTON_UP_IO_PORT,BUTTON_UP_IO_PIN);
}

uint8_t io_button_down_read() {
	return  GPIO_ReadInputDataBit(BUTTON_DOWN_IO_PORT,BUTTON_DOWN_IO_PIN);
}

/******************************************************************************
* led status function
*******************************************************************************/
void led_life_init() {
	GPIO_InitTypeDef        GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(LED_LIFE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_LIFE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_LIFE_IO_PORT, &GPIO_InitStructure);
}

void led_life_on() {
	GPIO_SetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

void led_life_off() {
	GPIO_ResetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

void led_life_toggle()
{
	GPIO_ToggleBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);	
}

/******************************************************************************
* adc function
* + CT sensor
* + themistor sensor
* Note: MUST be enable internal clock for adc module.
*******************************************************************************/
void io_cfg_adc1(void) {
	ADC_InitTypeDef ADC_InitStructure;
	RCC_HSICmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

	/* Enable ADC1 clock */
	RCC_APB2PeriphClockCmd(BAT_ADC_CLOCK , ENABLE);
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode =DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 2;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1, ENABLE);
}

void adc_bat_io_cfg() {
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(BAT_ADC_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = BAT_ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(BAT_ADC_PORT, &GPIO_InitStructure);
}

uint16_t adc_bat_io_read(uint8_t chanel) {
	ADC_RegularChannelConfig(ADC1, chanel, 1, ADC_SampleTime_4Cycles);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET);

	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

/******************************************************************************
* ssd1306 oled IO function
*******************************************************************************/
void ssd1306_clk_input_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SSD1306_CLK_IO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SSD1306_CLK_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(SSD1306_CLK_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_clk_output_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SSD1306_CLK_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = SSD1306_CLK_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SSD1306_CLK_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_clk_digital_write_low() {
	GPIO_ResetBits(SSD1306_CLK_IO_PORT,SSD1306_CLK_IO_PIN);
}

void ssd1306_clk_digital_write_high() {
	GPIO_SetBits(SSD1306_CLK_IO_PORT,SSD1306_CLK_IO_PIN);
}

int ssd1306_clk_digital_read() {
	return (int)(GPIO_ReadInputDataBit(SSD1306_CLK_IO_PORT, SSD1306_CLK_IO_PIN));
}

void ssd1306_data_input_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(SSD1306_DATA_IO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SSD1306_DATA_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(SSD1306_DATA_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_data_output_mode() {
	GPIO_InitTypeDef    GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(SSD1306_DATA_IO_CLOCK, ENABLE);
	GPIO_InitStructure.GPIO_Pin = SSD1306_DATA_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SSD1306_DATA_IO_PORT, &GPIO_InitStructure);
}

void ssd1306_data_digital_write_low() {
	GPIO_ResetBits(SSD1306_DATA_IO_PORT, SSD1306_DATA_IO_PIN);
}

void ssd1306_data_digital_write_high() {
	GPIO_SetBits(SSD1306_DATA_IO_PORT, SSD1306_DATA_IO_PIN);
}

int ssd1306_data_digital_read() {
	return (int)(GPIO_ReadInputDataBit(SSD1306_DATA_IO_PORT, SSD1306_DATA_IO_PIN));
}
/******************************************************************************
* eeprom function
* when using function DATA_EEPROM_ProgramByte,
* must be DATA_EEPROM_unlock- DATA_EEPROM_ProgramByte- DATA_EEPROM_lock
*******************************************************************************/
uint8_t io_eeprom_read(uint32_t address, uint8_t* pbuf, uint32_t len) {
	uint32_t eeprom_address = 0;

	eeprom_address = address + EEPROM_BASE_ADDRESS;

	if ((uint8_t*)pbuf == (uint8_t*)0 || len == 0 ||(address + len)> EEPROM_MAX_SIZE) {
		return EEPROM_DRIVER_NG;
	}

	DATA_EEPROM_Unlock();
	memcpy(pbuf, (const uint8_t*)eeprom_address, len);
	DATA_EEPROM_Lock();

	return EEPROM_DRIVER_OK;
}

uint8_t io_eeprom_write(uint32_t address, uint8_t* pbuf, uint32_t len) {
	uint32_t eeprom_address = 0;
	uint32_t index = 0;
	uint32_t flash_status;

	eeprom_address = address + EEPROM_BASE_ADDRESS;

	if ((uint8_t*)pbuf == (uint8_t*)0 || len == 0 ||(address + len)> EEPROM_MAX_SIZE) {
		return EEPROM_DRIVER_NG;
	}

	DATA_EEPROM_Unlock();

	while (index < len) {
		flash_status = DATA_EEPROM_ProgramByte((eeprom_address + index), (uint32_t)(*(pbuf + index)));

		if(flash_status == FLASH_COMPLETE) {
			index++;
		}
		else {
			FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR
							| FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR);
		}
	}

	DATA_EEPROM_Lock();

	return EEPROM_DRIVER_OK;
}

uint8_t io_eeprom_erase(uint32_t address, uint32_t len) {
	uint32_t eeprom_address = 0;
	uint32_t index = 0;
	uint32_t flash_status;

	eeprom_address = address + EEPROM_BASE_ADDRESS;

	if (len == 0 ||(address + len)> EEPROM_MAX_SIZE) {
		return EEPROM_DRIVER_NG;
	}

	DATA_EEPROM_Unlock();

	while(index < len) {
		sys_ctrl_soft_watchdog_reset();
		sys_ctrl_independent_watchdog_reset();

		flash_status = DATA_EEPROM_ProgramByte(eeprom_address + index, 0x00);

		if(flash_status == FLASH_COMPLETE) {
			index++;
		}
		else {
			FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_WRPERR | FLASH_FLAG_PGAERR
							| FLASH_FLAG_SIZERR | FLASH_FLAG_OPTVERR);
		}
	}

	DATA_EEPROM_Lock();

	return EEPROM_DRIVER_OK;
}