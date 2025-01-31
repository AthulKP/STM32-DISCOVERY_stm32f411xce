/*
 * gpio_hal.h
 *
 *  Created on: Jan 31, 2025
 *      Author: athul
 */

#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

#include <stdint.h>
#include "CMSIS.h"


#define GPIOA_Base_Address        ((uint32_t)0x40020000)
#define GPIOD_Base_Address        ((uint32_t)0x40020C00)

#define GPIOD_EN	    ((uint32_t) 0x1<<3)
#define GPIOA_EN	    ((uint32_t) 0x1)
#define GP_INPUT_Mode	((uint32_t) 0x0)
#define GP_OUTPUT_Mode	((uint32_t) 0x1)
#define Pull_Up 	    ((uint32_t) 0x1)
#define Pull_Down	    ((uint32_t) 0x2)

#define BIT_2Pos	((uint32_t)0x2)

#define Blue_Led	15 //PD_15
#define User_Button	0  //PA_0

#define Led_On	1

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
