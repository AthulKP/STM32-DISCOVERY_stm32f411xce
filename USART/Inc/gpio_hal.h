/*
 * gpio_hal.h
 *
 *  Created on: Jan 14, 2025
 *      Author: athul
 */

#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

#include <stdint.h>
#include "cmsis.h"

#define GPIOA_Base_Address          ((uint32_t)0x40020000)
#define RCC_AHB1ENR_Base_Address    ((uint32_t)0x40023830)

#define GPIOA_EN	    ((uint32_t) 0x1)
#define AF_MODE			((uint32_t) 0x2)
#define AF_7			((uint32_t) 0x7)
#define HIGH_SPEED	    ((uint32_t) 0x3)
#define NO_PUPD		    ((uint32_t) 0x0)

#define USART_TX	2 //PA_2
#define USART_RX	3 //PA_3
#define BIT_FIELD_2	2
#define BIT_FIELD_4	4

typedef struct
{
    __IO uint32_t MODER;
    __IO uint32_t OTYPER;
    __IO uint32_t OSPEEDR;
    __IO uint32_t PUPDR;
    __IO uint32_t IDR;
    __IO uint32_t ODR;
    __IO uint32_t BSRR;
    __IO uint32_t LCKR;
    __IO uint32_t AFRL;
    __IO uint32_t AFRH;
}GPIOx;


#endif /* GPIO_HAL_H_ */
