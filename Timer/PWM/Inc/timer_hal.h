/*
 * timer_hal.h
 *
 *  Created on: Jan 8, 2025
 *      Author: athul
 */

#ifndef TIMER_HAL_H_
#define TIMER_HAL_H_

#include <stdint.h>
#include "CMSIS.h"


#define TIM4_Base_Address   ((uint32_t)0x40000800)

#define TIMER4_EN           ((uint32_t)0x1<<2)
#define OC1PE_EN            ((uint32_t)0x1<<3)
#define ARPE_EN    	        ((uint32_t)0x1<<7)
#define CEN_EN    	        ((uint32_t)0x1)
#define UG_REINITIALIZE    	((uint32_t)0x1)
#define PRESCALE_1600       ((uint32_t)1600)
#define ARR_100 	        ((uint32_t)100)
#define PWM_MODE_1	        ((uint32_t)0x6<<4)
#define CC1_OUTPUT	        ((uint32_t)0x1)


typedef struct
{
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SMCR;
    __IO uint32_t DIER;
    __IO uint32_t SR;
    __IO uint32_t EGR;
    __IO uint32_t CCMR1;
    __IO uint32_t CCMR2;
    __IO uint32_t CCER;
    __IO uint32_t CNT;
    __IO uint32_t PSC;
    __IO uint32_t ARR;
    __I  uint32_t RESERVED_1;
    __IO uint32_t CCR1;
    __IO uint32_t CCR2;
    __IO uint32_t CCR3;
    __IO uint32_t CCR4;
    __I  uint32_t RESERVED_2;
    __IO uint32_t DCR;
    __IO uint32_t DMAR;
}TIMx;


#endif /* TIMER_HAL_H_ */
