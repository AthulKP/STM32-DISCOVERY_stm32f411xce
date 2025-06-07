/*
 * rcc_driver.c
 *
 *  Created on: Jun 8, 2025
 *      Author: athul
 */
#include "rcc_hal.h"

void turn_on_hse(void) {
	REG_RCC_CR |= HSEON_EN;
	while (!(REG_RCC_CR & HSERDY_FLG));
}

void set_APB_AHB_prescaler(void) {
	// Set clock dividers
	REG_RCC_CFGR &= ~AHB_PRESCALER_1;
	REG_RCC_CFGR |= (APB1_PRESCALER_2 | APB2_PRESCALER_2 );
}
void change_sysclk(uint32_t clk_frq) {

	REG_RCC_PLLCFGR = clk_frq;

	REG_RCC_CR |= PLLON_EN;
	while (!(REG_RCC_CR & PLLRDY_FLG));

	// Configure FLASH latency
	FLASH_ACR &= ~FLASH_ACR_LATENCY_Msk;
	FLASH_ACR |= FLASH_ACR_LATENCY_3WS;

	// Switch to PLL clock source
	REG_RCC_CFGR &= SYSCLK_CLEAR_SRC;
	REG_RCC_CFGR |= SYSCLK_SRC_PLL;
	while ((REG_RCC_CFGR & SYSCLK_STS_MSK) != SYSCLK_PLL_ENABLED);
}
