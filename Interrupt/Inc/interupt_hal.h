/*
 * interupt_hal.h
 *
 *  Created on: Jan 31, 2025
 *      Author: athul
 */

#ifndef INTERUPT_HAL_H_
#define INTERUPT_HAL_H_

#include <stdint.h>
#include "CMSIS.h"

#define EXTI_BASE_ADDRESS	0x40013C00
#define EXTI0_EN			(0x1 << 6)
#define MASK_PA0			(0x1)
#define TRIGGER_RISING_EDGE	(0x1)

typedef struct {
	__IO uint32_t EXTI_IMR;
	__IO uint32_t EXTI_EMR;
	__IO uint32_t EXTI_RTSR;
	__IO uint32_t EXTI_FTSR;
	__IO uint32_t EXTI_SWIER;
	__IO uint32_t EXTI_PR;
}External_interrupt_x;

#endif /* INTERUPT_HAL_H_ */
