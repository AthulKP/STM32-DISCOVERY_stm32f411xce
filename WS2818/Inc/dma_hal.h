/*
 * dma_hal.h
 *
 *  Created on: Jan 19, 2025
 *      Author: athul
 */

#ifndef DMA_HAL_H_
#define DMA_HAL_H_

#include "CMSIS.h"
#include <stdint.h>

#define DMA2_BASE_ADDRESS	0x40026400
#define DMA1_BASE_ADDRESS	0x40026000

#define ENABLE_DMA1_CLOCK				(uint32_t)0x1<<21
#define ENABLE_DMA2_CLOCK				(uint32_t)0x1<<22
#define ENABLE_STREAM   				(uint32_t)0x1
#define STREAM_CHANNEL_5				(uint32_t)0x5 << 25
#define HIGH_PRIORITY					(uint32_t)0x2 << 16
#define HALF_WORD_MEMORY				(uint32_t)0x1 << 13
#define HALF_WORD_PERIPHERAL			(uint32_t)0x1 << 11
#define ENABLE_MEMORY_POINTER_INCREMENT	(uint32_t)0x1 << 10
#define ENABLE_CIRCULAR_MODE			(uint32_t)0x1 << 8
#define MEMORY_TO_PERIPHERAL_MODE		(uint32_t)0x1 << 6

typedef struct {
	__IO uint32_t LISR ;
	__IO uint32_t HISR ;
	__IO uint32_t LIFCR ;
	__IO uint32_t HIFCR ;
	__IO uint32_t S0CR ;
	__IO uint32_t S0NDTR ;
	__IO uint32_t S0PAR ;
	__IO uint32_t S0M0AR ;
	__IO uint32_t S0M1AR ;
	__IO uint32_t S0FCR ;
	__IO uint32_t S1CR ;
	__IO uint32_t S1NDTR ;
	__IO uint32_t S1PAR ;
	__IO uint32_t S1M0AR ;
	__IO uint32_t S1M1AR ;
	__IO uint32_t S1FCR ;
	__IO uint32_t S2CR ;
	__IO uint32_t S2NDTR ;
	__IO uint32_t S2PAR ;
	__IO uint32_t S2M0AR ;
	__IO uint32_t S2M1AR ;
	__IO uint32_t S2FCR ;
	__IO uint32_t S3CR ;
	__IO uint32_t S3NDTR ;
	__IO uint32_t S3PAR ;
	__IO uint32_t S3M0AR ;
	__IO uint32_t S3M1AR ;
	__IO uint32_t S3FCR ;
	__IO uint32_t S4CR ;
	__IO uint32_t S4NDTR ;
	__IO uint32_t S4PAR ;
	__IO uint32_t S4M0AR ;
	__IO uint32_t S4M1AR ;
	__IO uint32_t S4FCR ;
	__IO uint32_t S5CR ;
	__IO uint32_t S5NDTR ;
	__IO uint32_t S5PAR ;
	__IO uint32_t S5M0AR ;
	__IO uint32_t S5M1AR ;
	__IO uint32_t S5FCR ;
	__IO uint32_t S6CR ;
	__IO uint32_t S6NDTR ;
	__IO uint32_t S6PAR ;
	__IO uint32_t S6M0AR ;
	__IO uint32_t S6M1AR ;
	__IO uint32_t S6FCR ;
	__IO uint32_t S7CR ;
	__IO uint32_t S7NDTR ;
	__IO uint32_t S7PAR ;
	__IO uint32_t S7M0AR ;
	__IO uint32_t S7M1AR ;
	__IO uint32_t S7FCR ;
}DMAx;

#endif /* DMA_HAL_H_ */
