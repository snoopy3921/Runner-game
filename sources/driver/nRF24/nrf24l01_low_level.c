#include "nrf24l01.h"
#include "os_task.h"
#include "io_cfg.h"
/*start of low level functions, specific to the mcu and compiler*/

/*delay in miliseconds*/
void delay_function(uint32_t duration_ms)
{
    os_task_delay(duration_ms);
}

/*contains all SPI configuations, such as pins and control registers*/
/*SPI control: master, interrupts disabled, clock polarity low when idle, clock phase falling edge, clock up tp 1 MHz*/
void SPI_Initializer()
{
    nrf24l01_spi_init();
}

/*contains all CSN and CE pins gpio configurations, including setting them as gpio outputs and turning SPI off and CE '1'*/
void pinout_Initializer()
{
    nrf24l01_io_ctrl_init();
}

/*CSN pin manipulation to high or low (SPI on or off)*/
void nrf24_SPI(uint8_t input)
{
    if(input == SPI_ON) nrf24l01_csn_low();
    else nrf24l01_csn_high();
}

/*1 byte SPI shift register send and receive routine*/
uint8_t SPI_send_command(uint8_t command)
{
    // Wait until TX buffer is empty
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	// Send byte to SPI (TXE cleared)
	SPI_I2S_SendData(SPI1, (uint8_t)command);
	//if(data != nRF24_CMD_NOP) return 0;
	// Wait while receive buffer is empty
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	// Return received byte
	return (uint8_t)SPI_I2S_ReceiveData(SPI1);
}

/*CE pin maniplation to high or low*/
void nrf24_CE(uint8_t input)
{
    if(input == CE_OFF) nrf24l01_ce_low();
    else nrf24l01_ce_high();
}