/*
 * SYSCFG_hal.h
 *
 *  Created on: Jan 31, 2025
 *      Author: athul
 */

#ifndef SYSCFG_HAL_H_
#define SYSCFG_HAL_H_

#include <stdint.h>
#include "CMSIS.h"

#define SYSCFG_BASE_ADDRESS 	((uint32_t)0x40013800)
#define SYSCFG_EN 				((uint32_t)0x1 << 14)
#define SYSCFG_EXTICR1_OFFSET	((uint32_t)0x08)

#define EXTI_PIN_PA0			(uint32_t)~(0xf)

typedef struct {
	__I  uint32_t MEMRMP;
	__I  uint32_t PMC;
	__IO uint32_t EXTICR1;
	__IO uint32_t EXTICR2;
	__IO uint32_t EXTICR3;
	__IO uint32_t EXTICR4;
	__IO uint32_t CMPCR;
}SYSCFG;

#endif /* SYSCFG_HAL_H_ */
