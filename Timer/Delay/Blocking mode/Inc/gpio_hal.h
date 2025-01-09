/*
 * gpio_hal.h
 *
 *  Created on: Jan 10, 2025
 *      Author: athul
 */

#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

#include "cmsis.h"
#include <stdint.h>

#define GPIOD_Base_Address        ((uint32_t) 0x40020C00)

#define GPIOD_EN	    ((uint32_t) 0x1<<3)
#define GP_OUTPUT_MODE	((uint32_t) 0x1)
#define PULL_DWON		((uint32_t) 0x2)


#define Green_Led	        12 //PD_12
#define LED_ON  	        1
#define BIT_FIELD_2		    2


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
