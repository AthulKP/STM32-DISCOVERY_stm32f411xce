/*
 * RCC_HAL.h
 *
 *  Created on: Jun 8, 2025
 *      Author: athul
 */

#ifndef RCC_HAL_H_
#define RCC_HAL_H_

#include <stdint.h>

#define REG_RCC_CR			(*(volatile uint32_t *)0x40023800)
#define REG_RCC_PLLCFGR		(*(volatile uint32_t *)0x40023804)
#define REG_RCC_CFGR		(*(volatile uint32_t *)0x40023808)

#define FLASH_ACR             	(*((volatile uint32_t *)0x40023C00))
#define FLASH_ACR_LATENCY_Msk  	(0x7UL << 0)
#define FLASH_ACR_LATENCY_3WS  	(3UL << 0)

#define REG_RCC_AHB1ENR		(*(volatile uint32_t *)0x40023830)

#define HSEON_EN		((uint32_t)1<<16)
#define HSERDY_FLG		((uint32_t)1<<17)
#define PLLON_EN		((uint32_t)1<<24)
#define PLLRDY_FLG		((uint32_t)1<<25)

#define PLLQ_7				((uint32_t)7<<24)
#define PLLN_336MHz			((uint32_t)336<<6)
#define PLLM_8				((uint32_t)8<<0)
#define PLLP_2				((uint32_t)8<<16)
#define PLLSRC_HSE			((uint32_t)1<<22)
#define SYSCLK_CLEAR_SRC	~((uint32_t)0x03)
#define SYSCLK_SRC_PLL		((uint32_t)0x02)
#define SYSCLK_PLL_ENABLED	((uint32_t)SYSCLK_SRC_PLL << 2)
#define SYSCLK_STS_MSK		((uint32_t)0x0C)
#define PLL_RESET_VALUE 	((uint32_t)0x24003010)
#define AHB_PRESCALER_1		(0x0F << 4)
#define APB1_PRESCALER_2	(0b100 << 10)
#define APB2_PRESCALER_2	(0b100 << 13)

#define SYSCLK_30MHz	(uint32_t)((6 << 0) | (90 << 6)  |(0b01 << 16) | (1 << 22))
#define SYSCLK_60MHz	(uint32_t)((6 << 0) | (180 << 6) |(0b01 << 16) | (1 << 22))
#define SYSCLK_100MHz	(uint32_t)((6 << 0) | (300 << 6) |(0b01 << 16) | (1 << 22))

void turn_on_hse(void);
void set_APB_AHB_prescaler(void);
void change_sysclk(uint32_t);

#endif /* RCC_HAL_H_ */
