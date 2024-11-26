

#include "system.h"
#include "xprintf.h"
#include "io_cfg.h"

#include "stm32l1xx_usart.h"


static void Sys_Console_Send_Char(uint8_t c)
{
	/* wait last transmission completed */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);

	/* put transnission data */
	USART_SendData(USARTx, (uint8_t)c);

	/* wait transmission completed */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}

void SysInitConsole(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;


	/* Enable GPIO clock */
	RCC_AHBPeriphClockCmd(USARTx_TX_GPIO_CLK | USARTx_RX_GPIO_CLK, ENABLE);

	/* Enable USART clock */
	RCC_APB2PeriphClockCmd(USARTx_CLK, ENABLE);

	/* Connect PXx to USARTx_Tx */
	GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);

	/* Connect PXx to USARTx_Rx */
	GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);

	/* Configure USART Tx and Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
	GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
	GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

	/* USARTx configuration */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTx, &USART_InitStructure);

	/* Enable the USARTx Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearITPendingBit(USARTx, USART_IT_RXNE | USART_IT_TXE);
	USART_ITConfig(USARTx, USART_IT_RXNE, DISABLE);
	USART_ITConfig(USARTx, USART_IT_TXE, DISABLE);

	/* Enable USART */
	USART_Cmd(USARTx, ENABLE);
	
	xfunc_output = (void(*)(int))Sys_Console_Send_Char;
}


void USART1_IRQHandler() {
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		char c = USART_ReceiveData(USART1);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	
}




