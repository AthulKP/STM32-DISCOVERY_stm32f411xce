/*
 * spi_hal.h
 *
 *  Created on: Feb 6, 2025
 *      Author: athul
 */

#ifndef SPI_HAL_H_
#define SPI_HAL_H_

#include "cmsis.h"

#define SPI1_Base_Address   ((uint32_t)0x40013000)

#define SPI1_CLK_EN	   (uint32_t)0x1<<12
#define SPI_BUSY_FLAG  (uint32_t)(1 << 7)
#define CPHA_1	       (uint16_t)0x1<<0
#define CPOL_1	       (uint16_t)0x1<<1
#define SPI_MODE_3 	   (uint16_t)(CPOL_1|CPHA_1)
#define MSTR_EN	       (uint16_t)0x1<<2
#define CLK_BY_4       (uint16_t)0x1<<3
#define LSB_FIRST      (uint16_t)0x0<<7
#define SSI_EN		   (uint16_t)0x1<<8
#define SSM_EN	       (uint16_t)0x1<<9
#define DFF_8BIT       (uint16_t)0x0<<11
#define BIDIMODE_DIS   (uint16_t)0x0<<15
#define SPI_EN         (uint16_t)0x1<<6
#define RXNE		   (uint16_t)0x1<<0
#define TXE		   	   (uint16_t)0x1<<1

typedef struct{
	__IO uint32_t CR1;
	__IO uint32_t CR2;
	__IO uint32_t SR;
	__IO uint32_t DR;
	__IO uint32_t CRCPR;
	__IO uint32_t RXCRCR;
	__IO uint32_t TXCRCR;
	__IO uint32_t I2SCFGR;
	__IO uint32_t I2SPR;
}SPIx;

#endif /* SPI_HAL_H_ */
