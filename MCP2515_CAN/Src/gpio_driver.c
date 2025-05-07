/*
 * gpio_driver.c
 *
 *  Created on: Apr 25, 2025
 *      Author: athul
 */

#include "gpio_hal.h"

volatile GPIOx *p_GPIOB = (GPIOx *)GPIOB_BASE_ADDRESS;
volatile GPIOx *p_GPIOD = (GPIOx *)GPIOD_BASE_ADDRESS;

void gpio_initilaize(void)
{
    RCC_AHB1ENR_REGISTER |= (GPIOB_CLK_EN | GPIOD_CLK_EN);
    p_GPIOB->MODER |= ((MODE_AF2 << SPI_SCK * BIT_RES_2) | (MODE_AF2 << SPI_MISO * BIT_RES_2) | (MODE_AF2 << SPI_MOSI * BIT_RES_2));
    p_GPIOD->MODER |= ((MODE_OUTPUT << SPI_CS * BIT_RES_2)|(MODE_INPUT << MCP_INT * BIT_RES_2));

    p_GPIOB->OSPEEDR |= ((HIGH_SPEED << SPI_SCK * BIT_RES_2) | (HIGH_SPEED << SPI_MISO * BIT_RES_2) | (HIGH_SPEED << SPI_MOSI * BIT_RES_2));
    p_GPIOD->OSPEEDR |= (HIGH_SPEED << SPI_CS * BIT_RES_2);

    p_GPIOB->PUPDR |= ((PULL_UP << SPI_SCK * BIT_RES_2) | (NO_PULL << SPI_MISO * BIT_RES_2) | (NO_PULL << SPI_MOSI * BIT_RES_2));
    p_GPIOD->PUPDR |= ((PULL_UP << SPI_CS * BIT_RES_2)|(PULL_UP << MCP_INT * BIT_RES_2));
    p_GPIOD->ODR |= (CONST_VAL_1 << SPI_CS);

    p_GPIOB->AFRH = ((AF5_SPI1 << (SPI_SCK - AFRH_OFFSET) * BIT_RES_4) | (AF5_SPI1 << (SPI_MISO - AFRH_OFFSET) * BIT_RES_4) | (AF5_SPI1 << (SPI_MOSI - AFRH_OFFSET) * BIT_RES_4));
}

void gpio_cs_enable(void) {
    p_GPIOD->ODR &= ~(CONST_VAL_1 << SPI_CS);  // CS low
}

void gpio_cs_disable(void) {
    p_GPIOD->ODR |= (CONST_VAL_1 << SPI_CS);   // CS high
}

uint8_t gpio_int_triggered(void){
    return (uint8_t)(!(p_GPIOD->IDR & (CONST_VAL_1<<MCP_INT)));
}
