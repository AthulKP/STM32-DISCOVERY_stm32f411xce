/*
 * gpio_hal.h
 *
 *  Created on: Jun 8, 2025
 *      Author: athul
 */

#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

#include <stdint.h>
#include "rcc_hal.h"

#define GPIOD_MODER		(*(volatile uint32_t *)0x40020C00)
#define GPIOD_OSPEED	(*(volatile uint32_t *)0x40020C08)
#define GPIOD_PUPDR		(*(volatile uint32_t *)0x40020C0C)
#define GPIOD_ODR		(*(volatile uint32_t *)0x40020C14)

#define GPIOD_CLOCK_EN		(uint32_t) 1 << 3
#define GPIO_MODE_OUTPUT	(uint8_t) 1
#define GPIO_PULLDOWN		(uint8_t) 2
#define GPIO_HIGH_SPEED		(uint8_t) 3
#define GPIO_2BIT_Pos		(uint8_t) 2
#define GREEN_LED			(uint8_t)12 // PD12
#define ORANGE_LED			(uint8_t)13 // PD13
#define RED_LED				(uint8_t)14 // PD14
#define BLUE_LED			(uint8_t)15 // PD15

void initialize_led(void);
void trun_on_led(uint8_t);
void trun_off_led(uint8_t);

#endif /* GPIO_HAL_H_ */
