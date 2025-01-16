/*
 * uart_hal.h
 *
 *  Created on: Jan 14, 2025
 *      Author: athul
 */

#ifndef USART_HAL_H_
#define USART_HAL_H_

#include <stdint.h>
#include "cmsis.h"

#define USART2_Base_Address          ((uint32_t)0x40004400)
#define RCC_APB1ENR_Base_Address     ((uint32_t)0x40023840)

#define USART2_EN	 				 ((uint32_t)0x1<<17)
#define ENABLE_USART 				 ((uint16_t)0x1<<13)
#define DISABLE_USART 				 ((uint16_t)~(0x1<<13))
#define EIGHT_DATA_BIT_ONE_START_BIT (uint16_t)~(0x1<<12)
#define ONE_STOP_BIT 				 (uint16_t)~(0x3<<12)
#define DISABLE_OVER_SAMPLING		 (uint16_t)~(0x1<<15)
#define BAUDRATE_9600				 (uint16_t)(0x68<<4 | 0x3)
#define	ENABLE_TE					 (uint16_t)(0x1<<3)
#define	TXE_FLAG					 (uint16_t)(0x1<<7) // Transmit data register empty
#define	TC_FLAG					 	 (uint16_t)(0x1<<6) // Transmission complete

typedef struct {
	__IO uint32_t SR;
	__IO uint32_t DR;
	__IO uint32_t BRR;
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t CR3;
	__IO uint32_t GTPR;

}USARTx;

#endif /* USART_HAL_H_ */
