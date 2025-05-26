/*
 * gpio_hal.h
 *
 *  Created on: Feb 6, 2025
 *      Author: athul
 */

#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

#include "cmsis.h"

#define GPIOA_Base_Address   ((uint32_t)0x40020000)
#define GPIOE_Base_Address   ((uint32_t)0x40021000)

#define GPIOA_CLK_EN	0x1
#define GPIOE_CLK_EN	0x1<<4

#define	MODE_AF2				0x2
#define	MODE_OUTPUT				0x1
#define	AF5_SPI1				0x5

#define BIT_RES_4				0x4
#define BIT_RES_2				0x2


#define	SPI_CS			0x3	//PE3
#define SPI_SCK			0x5 //PA5
#define SPI_MISO		0x6 //PA6
#define SPI_MOSI		0x7 //PA7

#define FAST_SPEED		0x2
#define HIGH_SPEED		0x3

#define	PULL_UP			0x1
#define	PULL_DOWN		0x2
#define	NO_PULL			0x0

typedef struct {
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
