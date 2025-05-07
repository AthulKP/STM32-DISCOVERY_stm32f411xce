/*
 * gpio_hal.h
 *
 *  Created on: Feb 6, 2025
 *      Author: athul
 */

#ifndef GPIO_HAL_H_
#define GPIO_HAL_H_

#include "utils.h"

#define GPIOB_BASE_ADDRESS      ((uint32_t)0x40020400)
#define GPIOD_BASE_ADDRESS      ((uint32_t)0x40020C00)
#define RCC_AHB1ENR_REGISTER    (*(volatile uint32_t *)0x40023830)

#define GPIOB_CLK_EN	0x1<<1
#define GPIOD_CLK_EN	0x1<<3

#define	MODE_AF2				0x2
#define	MODE_OUTPUT				0x1
#define	MODE_INPUT				0x0
#define	AF5_SPI1				0x5
#define AFRH_OFFSET				0x8
#define BIT_RES_4				0x4
#define BIT_RES_2				0x2


#define	SPI_CS			0x8	//PD8
#define SPI_SCK			0xD //PB13
#define SPI_MISO		0xE //PB14
#define SPI_MOSI		0xF //PB15
#define MCP_INT 		0xA //PB15

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

//Functions
void gpio_initilaize(void);
void gpio_cs_enable(void);
void gpio_cs_disable(void);
uint8_t gpio_int_triggered(void);


#endif /* GPIO_HAL_H_ */
