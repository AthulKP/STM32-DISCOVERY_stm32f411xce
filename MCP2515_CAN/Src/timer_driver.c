/*
 * timer_driver.c
 *
 *  Created on: Apr 27, 2025
 *      Author: athul
 */

#include "timer_hal.h"

volatile TIMx *p_TIMER4 = (TIMx *)TIM4_Base_Address;

void timer_initialize(void)
{
    // Timer 4 configuration with 1ms counting
    RCC_APB1ENR_REGISTER |= RCC_TIMER4_EN;
    p_TIMER4->PSC = PRESCALE_16000;
    p_TIMER4->ARR = ARR_MAX;
    p_TIMER4->CR1 |= ENABLE_TIMER;
}

void timer_delay_ms(uint32_t delay_time){
    p_TIMER4->CNT = 0 ;
    while (p_TIMER4->CNT < delay_time);
}
