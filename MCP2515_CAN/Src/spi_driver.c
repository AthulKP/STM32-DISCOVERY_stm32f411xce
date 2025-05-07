/*
 * spi_driver.c
 *
 *  Created on: Apr 25, 2025
 *      Author: athul
 */

#include "spi_hal.h"
#include "gpio_hal.h"
#include "mcp_2525.h"

volatile SPIx *p_spi2 = (SPIx *)SPI2_BASE_ADDRESS;
volatile GPIOx *p_cs_gpio = (GPIOx *)GPIOD_BASE_ADDRESS;

void spi_initialize(void){
    RCC_APB1ENR_REGISTER |= SPI2_CLK_EN;
    p_spi2->CR1 = (uint16_t)(BIDIMODE_DIS | DFF_8BIT | SSM_EN | SSI_EN | LSB_FIRST | CLK_BY_4 | MSTR_EN | SPI_MODE_0);
	while (p_spi2->SR & SPI_BUSY_FLAG); // wait until the SPI is not busy
	p_spi2->CR1 |= SPI_EN;
	while (!(p_spi2->CR1 & SPI_EN)); // wait until the SPI is enabled
}

uint8_t spi_read(uint8_t reg)
{

	p_cs_gpio->ODR &= ~(1 << SPI_CS); // CS LOW
	p_spi2->DR = reg; // Send dummy byte to make the clock continue
	while (!(p_spi2->SR & TXE))
		;			// Wait for TXE (Transmit buffer empty)
	p_spi2->DR = 0x00; // Send dummy byte to make the clock continue
	while (!(p_spi2->SR & RXNE))
		;		   // Wait for RXNE (Receive buffer full)
	(void)p_spi2->DR; // Clear the buffer and reset RXNE flag
	while (!(p_spi2->SR & RXNE))
		; // Wait for RXNE (Receive buffer full)

	p_cs_gpio->ODR |= (1 << SPI_CS); // CS HIGH

	return p_spi2->DR;
}

void spi_write(uint8_t reg, uint8_t data)
{

	p_cs_gpio->ODR &= ~(1 << SPI_CS); // CS LOW
	p_spi2->DR = reg; // Send dummy byte to make the clock continue
	while (!(p_spi2->SR & TXE))
		;			// Wait for TXE (Transmit buffer empty)
	p_spi2->DR = data; // Send dummy byte to make the clock continue
	while (!(p_spi2->SR & TXE))
		; // Wait for TXE (Transmit buffer empty)
	while (!(p_spi2->SR & RXNE))
		;		   // Wait for RXNE (Receive buffer full)
	(void)p_spi2->DR; // Wait for RXNE (Receive buffer full)

	p_cs_gpio->ODR |= (1 << SPI_CS); // CS HIGH
}

void spi_send(uint8_t instruction)
{
	while (!(p_spi2->SR & TXE));	// Wait for TXE (Transmit buffer empty)
	p_spi2->DR = instruction;	 	// Send dummy byte to make the clock continue
	while (!(p_spi2->SR & TXE));    // Wait for TXE (Transmit buffer empty)
}

uint8_t spi_recevie(void){
	while (!(p_spi2->SR & TXE));		   // Wait for RXNE (Receive buffer full)
	p_spi2->DR = CONST_VAL_0; // Send dummy byte to make the clock continue
	(void)p_spi2->DR; // Clear the buffer and reset RXNE flag
	while (!(p_spi2->SR & RXNE)); // Wait for RXNE (Receive buffer full)
	return p_spi2->DR;
}
