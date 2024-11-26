/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   05/09/2016
 ******************************************************************************
**/
#ifndef __IO_CFG_H__
#define __IO_CFG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"
#include "system_stm32l1xx.h"
#include "core_cm3.h"
#include "core_cmFunc.h"


/******************************************************************************
 *Pin out header
*******************************************************************************/
#define HEADER_A0_IO_PIN				(GPIO_Pin_0)
#define HEADER_A0_IO_PORT				(GPIOA)
#define HEADER_A0_IO_CLOCK			(RCC_AHBPeriph_GPIOA)

#define HEADER_A4_IO_PIN				(GPIO_Pin_4)
#define HEADER_A4_IO_PORT				(GPIOA)
#define HEADER_A4_IO_CLOCK			(RCC_AHBPeriph_GPIOA)

#define HEADER_B15_IO_PIN				(GPIO_Pin_15)
#define HEADER_B15_IO_PORT			(GPIOB)
#define HEADER_B15_IO_CLOCK			(RCC_AHBPeriph_GPIOB)


/*
 * define pin for arduino pinMode/digitalWrite/digitalRead
 * NOTE: define value MUST be deferrent
 */
#define SSD1306_CLK_PIN					(0x03)
#define SSD1306_DATA_PIN				(0x04)
#define SSD1306_RES_PIN					(0x08)

/******************************************************************************
 *Pin map button
*******************************************************************************/
#define BUTTON_DOWN_IO_PIN				(GPIO_Pin_3)
#define BUTTON_DOWN_IO_PORT				(GPIOB)
#define BUTTON_DOWN_IO_CLOCK			(RCC_AHBPeriph_GPIOB)

#define BUTTON_UP_IO_PIN				(GPIO_Pin_13)
#define BUTTON_UP_IO_PORT				(GPIOC)
#define BUTTON_UP_IO_CLOCK				(RCC_AHBPeriph_GPIOC)

#define BUTTON_MODE_IO_PIN				(GPIO_Pin_4)
#define BUTTON_MODE_IO_PORT				(GPIOB)
#define BUTTON_MODE_IO_CLOCK			(RCC_AHBPeriph_GPIOB)

/*****************************************************************************
 *Pin map led life
******************************************************************************/
#define LED_LIFE_IO_PIN					(GPIO_Pin_8)
#define LED_LIFE_IO_PORT				(GPIOB)
#define LED_LIFE_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

/*****************************************************************************
 *Pin map buzzer
******************************************************************************/
#define BUZZER_IO_PIN					(GPIO_Pin_0)
#define BUZZER_IO_PORT					(GPIOB)
#define BUZZER_IO_CLOCK					(RCC_AHBPeriph_GPIOB)

#define BUZZER_IO_AF                    (GPIO_AF_TIM3)
#define BUZZER_IO_SOURCE                (GPIO_PinSource0)

#define BUZZER_TIM                      (TIM3)
#define BUZZER_TIM_PERIPH               (RCC_APB1Periph_TIM3)
#define BUZZER_TIM_IRQ                  (TIM3_IRQn)

/*****************************************************************************
 *Pin map nRF24l01
******************************************************************************/
#define NRF_CE_IO_PIN					(GPIO_Pin_8)
#define NRF_CE_IO_PORT					(GPIOA)
#define NRF_CE_IO_CLOCK					(RCC_AHBPeriph_GPIOA)

#define NRF_CSN_IO_PIN					(GPIO_Pin_9)
#define NRF_CSN_IO_PORT					(GPIOB)
#define NRF_CSN_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

#define NRF_IRQ_IO_PIN					(GPIO_Pin_1)
#define NRF_IRQ_IO_PORT					(GPIOB)
#define NRF_IRQ_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

/*****************************************************************************
 *Pin map Flash W2508
******************************************************************************/
#define FLASH_CE_IO_PIN					(GPIO_Pin_14)
#define FLASH_CE_IO_PORT				(GPIOB)
#define FLASH_CE_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

/****************************************************************************
 *Pin map CT sensor
*****************************************************************************/
#define BAT_ADC_PIN						(GPIO_Pin_0)

#define BAT_ADC_PORT					(GPIOA)
#define BAT_ADC_CLOCK					(RCC_APB2Periph_ADC1)
#define BAT_ADC_IO_CLOCK				(RCC_AHBPeriph_GPIOA)

/****************************************************************************
 *Pin map ssd1306
*****************************************************************************/
#define SSD1306_CLK_IO_PIN				(GPIO_Pin_13)
#define SSD1306_CLK_IO_PORT				(GPIOB)
#define SSD1306_CLK_IO_CLOCK			(RCC_AHBPeriph_GPIOB)

#define SSD1306_DATA_IO_PIN				(GPIO_Pin_12)
#define SSD1306_DATA_IO_PORT			(GPIOB)
#define SSD1306_DATA_IO_CLOCK			(RCC_AHBPeriph_GPIOB)

/****************************************************************************
 *Pin map UART2
*****************************************************************************/
#define USART2_TX_PIN					GPIO_Pin_3
#define USART2_TX_GPIO_PORT				GPIOA
#define USART2_TX_GPIO_CLK				RCC_AHBPeriph_GPIOA
#define USART2_TX_SOURCE				GPIO_PinSource3
#define USART2_TX_AF					GPIO_AF_USART1

#define USART2_RX_PIN					GPIO_Pin_2
#define USART2_RX_GPIO_PORT				GPIOA
#define USART2_RX_GPIO_CLK				RCC_AHBPeriph_GPIOA
#define USART2_RX_SOURCE				GPIO_PinSource2
#define USART2_RX_AF					GPIO_AF_USART2

#define USART2_CLK						RCC_APB1Periph_USART2

/****************************************************************************
 *UART RS485 - RS485 dir io config
*****************************************************************************/
#define USART_RS485						(USART2)
#define USART_RS485_CLK					(RCC_APB1Periph_USART2)
#define USART_RS485_IRQn				(USART2_IRQn)

#define USART_RS485_TX_PIN				(GPIO_Pin_3)
#define USART_RS485_TX_GPIO_PORT		(GPIOA)
#define USART_RS485_TX_GPIO_CLK			(RCC_AHBPeriph_GPIOA)
#define USART_RS485_TX_SOURCE			(GPIO_PinSource3)

#define USART_RS485_RX_PIN				(GPIO_Pin_2)
#define USART_RS485_RX_GPIO_PORT		(GPIOA)
#define USART_RS485_RX_GPIO_CLK			(RCC_AHBPeriph_GPIOA)
#define USART_RS485_RX_SOURCE			(GPIO_PinSource2)

#define RS485_TIM						(TIM4)
#define RS485_TIM_PERIPH				(RCC_APB1Periph_TIM4)
#define RS485_TIM_IRQ					(TIM4_IRQn)

/*RS485 dir IO*/
#define RS485_DIR_IO_PIN				(GPIO_Pin_1)
#define RS485_DIR_IO_PORT				(GPIOA)
#define RS485_DIR_IO_CLOCK			(RCC_AHBPeriph_GPIOA)


/******************************************************************************
* pinout header function
*******************************************************************************/
extern void pinout_header_init();

/******************************************************************************
* delay function
*******************************************************************************/
extern void timer_delay_init();
extern void delay(uint32_t ms);

/******************************************************************************
* button function
*******************************************************************************/
extern void io_button_mode_init();
extern void io_button_up_init();
extern void io_button_down_init();

extern uint8_t io_button_mode_read();
extern uint8_t io_button_up_read();
extern uint8_t io_button_down_read();

/******************************************************************************
* led status function
*******************************************************************************/
extern void led_life_init();
extern void led_life_on();
extern void led_life_off();
extern void led_life_toggle();

/******************************************************************************
* adc function
* + themistor sensor
*
* Note: MUST be enable internal clock for adc module.
*******************************************************************************/
/* configure adc peripheral */
extern void io_cfg_adc1(void);

/* adc configure for CT sensor */
extern void adc_bat_io_cfg();
extern uint16_t adc_bat_io_read(uint8_t);

/******************************************************************************
* ssd1306 oled IO function
*******************************************************************************/
extern void ssd1306_clk_input_mode();
extern void ssd1306_clk_output_mode();
extern void ssd1306_clk_digital_write_low();
extern void ssd1306_clk_digital_write_high();
extern int  ssd1306_clk_digital_read();

extern void ssd1306_data_input_mode();
extern void ssd1306_data_output_mode();
extern void ssd1306_data_digital_write_low();
extern void ssd1306_data_digital_write_high();
extern int  ssd1306_data_digital_read();
/******************************************************************************
* eeprom function
*******************************************************************************/
#define EEPROM_BASE_ADDRESS         (0x08080000)
#define EEPROM_MAX_SIZE             (0x1000)

extern uint8_t  io_eeprom_read(uint32_t, uint8_t*, uint32_t);
extern uint8_t  io_eeprom_write(uint32_t, uint8_t*, uint32_t);
extern uint8_t  io_eeprom_erase(uint32_t, uint32_t);


#ifdef __cplusplus
}
#endif

#endif //__IO_CFG_H__