/*
 * nvic_hal.h
 *
 *  Created on: Jan 11, 2025
 *      Author: athul
 */

#ifndef NVIC_HAL_H_
#define NVIC_HAL_H_

#include "cmsis.h"
#include <stdint.h>

#define NVIC_ISER_Address        ((uint32_t)0xE000E100)
#define NVIC_ICER_Address        ((uint32_t)0xE000E180)

#define INTERRPUT_EN			 ((uint32_t)0x1)
#define TIM4_INTERRPUT_POSITION	 ((uint32_t)0x1E) // 30

#endif /* NVIC_HAL_H_ */
