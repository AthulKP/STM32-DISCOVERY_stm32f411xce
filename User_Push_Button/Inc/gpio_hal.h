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


#define GPIOA_Base_Address        ((uint32_t)0x40020000)
#define GPIOD_Base_Address        ((uint32_t)0x40020C00)

#define GPIOA_EN	    ((uint32_t) 0x1)
#define GPIOD_EN	    ((uint32_t) 0x1<<3)
#define GP_Output_Mode	((uint32_t) 0x1)
#define GP_Input_Mode	((uint32_t) 0x0)
#define Pull_Down	    ((uint32_t) 0x2)

#define User_Button	0  //PA_0
#define Green_Led	12 //PD_12
#define Orange_Led	13 //PD_13
#define Red_Led	    14 //PD_14
#define Blue_Led	15 //PD_15

#define Led_On	1
#define Led_Off	0


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
