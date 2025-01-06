/*
 * gpio_hal.h
 *
 *  Created on: Jan 5, 2025
 *      Author: athul
 */

#ifndef RCC_HAL_H_
#define RCC_HAL_H_

#include <stdint.h>
#include "CMSIS.h"

#define RCC_Reset_value        ((uint32_t)0x00000000)

#define RCC_Base_Address      ((uint32_t)0x40023800)

#define GPIOA_EN ((uint32_t) 0x1<<0);
#define GPIOB_EN ((uint32_t) 0x1<<1);
#define GPIOC_EN ((uint32_t) 0x1<<2);
#define GPIOD_EN ((uint32_t) 0x1<<3);
#define GPIOE_EN ((uint32_t) 0x1<<4);
#define GPIOH_EN ((uint32_t) 0x1<<7);
#define I2C1_EN  ((uint32_t) 0x1<<21);

typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t PLLCFGR;
    __IO uint32_t CFGR;
    __IO uint32_t CIR;
    __IO uint32_t AHB1RSTR;
    __IO uint32_t AHB2RSTR;
    __I uint32_t Reserved_1;
    __I uint32_t Reserved_2;
    __IO uint32_t APB1RSTR;
    __IO uint32_t APB2RSTR;
    __I uint32_t Reserved_3;
    __I uint32_t Reserved_4;
    __IO uint32_t AHB1ENR;
    __IO uint32_t AHB2ENR;
    __I uint32_t Reserved_5;
    __I uint32_t Reserved_6;
    __IO uint32_t APB1ENR;
    __IO uint32_t APB2ENR;
    __I uint32_t Reserved_7;
    __I uint32_t Reserved_8;
    __IO uint32_t AHB1LPENR;
    __IO uint32_t AHB2LPENR;
    __I uint32_t Reserved_9;
    __I uint32_t Reserved_10;
    __IO uint32_t APB1LPENR;
    __IO uint32_t APB2LPENR;
    __I uint32_t Reserved_11;
    __I uint32_t Reserved_12;
    __IO uint32_t BDCR;
    __IO uint32_t CSR;
    __I uint32_t Reserved_13;
    __I uint32_t Reserved_14;
    __IO uint32_t SSCGR;
    __IO uint32_t PLLI2SCFGR;
    __I uint32_t Reserved_15;
    __IO uint32_t DCKCFGR;
}RCC;



#endif /* RCC_HAL_H_ */
