/*
 * gpio_hal.h
 *
 *  Created on: Jan 5, 2025
 *      Author: athul
 */

#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

#include <stdint.h>
#include "CMSIS.h"

#define GPIO_Reset_value          ((uint32_t)0x00000000)

#define GPIOA_Base_Address        ((uint32_t)0x40020000)
#define GPIOB_Base_Address        ((uint32_t)0x40020400)
#define GPIOC_Base_Address        ((uint32_t)0x40020800)
#define GPIOD_Base_Address        ((uint32_t)0x40020C00)
#define GPIOE_Base_Address        ((uint32_t)0x40021000)
#define GPIOH_Base_Address        ((uint32_t)0x40021C00)


#define GPIO_AF4 ((uint32_t) 0x1<<3);


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
