/*
 * gpio_driver.c
 *
 *  Created on: Jun 8, 2025
 *      Author: athul
 */

#include "gpio_hal.h"

void initialize_led(void){
	REG_RCC_AHB1ENR |= GPIOD_CLOCK_EN;
	GPIOD_MODER |= ((GPIO_MODE_OUTPUT << GREEN_LED * GPIO_2BIT_Pos) | (GPIO_MODE_OUTPUT << ORANGE_LED * GPIO_2BIT_Pos) | (GPIO_MODE_OUTPUT << RED_LED * GPIO_2BIT_Pos)
			| (GPIO_MODE_OUTPUT << BLUE_LED * GPIO_2BIT_Pos));
	GPIOD_OSPEED |= ((GPIO_HIGH_SPEED << GREEN_LED * GPIO_2BIT_Pos) | (GPIO_HIGH_SPEED << ORANGE_LED * GPIO_2BIT_Pos) | (GPIO_HIGH_SPEED << RED_LED * GPIO_2BIT_Pos)
			| (GPIO_HIGH_SPEED << BLUE_LED * GPIO_2BIT_Pos));
	GPIOD_PUPDR |= ((GPIO_PULLDOWN << GREEN_LED * GPIO_2BIT_Pos) | (GPIO_PULLDOWN << ORANGE_LED * GPIO_2BIT_Pos) | (GPIO_PULLDOWN << RED_LED * GPIO_2BIT_Pos)
			| (GPIO_PULLDOWN << BLUE_LED * GPIO_2BIT_Pos));
}

void trun_on_led(uint8_t led_pin){
	GPIOD_ODR |= (1 << led_pin);
}

void trun_off_led(uint8_t led_pin){
	GPIOD_ODR &= ~(1 << led_pin);
}
