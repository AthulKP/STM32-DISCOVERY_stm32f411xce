/*
 * gpio_hal.h
 *
 *  Created on: Jan 8, 2025
 *      Author: athul
 */

#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

#include <stdint.h>
#include "CMSIS.h"


#define GPIOC_Base_Address        ((uint32_t) 0x40020800)

#define GPIOC_EN	                ((uint32_t) 0x1<<2)
#define ALTERNATE_FUNCTION_MODE		((uint32_t) 0x2)
#define AF_2                		((uint32_t) 0x2)
#define OS_HIGH			            ((uint32_t) 0x3)


#define WS2812B 	        6 //PC_6
#define AF_HIGH_OFFSET	    8 // GPIO0-7 in AFLR
#define BIT_FIELD_2		    2
#define BIT_FIELD_3		    3
#define BIT_FIELD_4		    4

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
