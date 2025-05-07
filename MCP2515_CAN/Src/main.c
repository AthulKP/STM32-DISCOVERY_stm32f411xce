/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Athul K P
 * @brief          : Main program body
 ******************************************************************************

 */

#include <stdint.h>
#include <stdio.h>

#include "utils.h"
#include "spi_hal.h"
#include "gpio_hal.h"
#include "timer_hal.h"
#include "mcp_2525.h"

int main(void)
{
	// GPIO configuration for SPI pins and MCP interrupt pin
	gpio_initilaize();

	// SPI configuration
	spi_initialize();

	// Timer configuration
	timer_initialize();

	// MCP configuration
	mcp_initialize();

	volatile CAN_FRAME can_rx, can_tx;

	mcp_send_can(can_message(&can_tx, 0x1, 1, (uint8_t[]){1}));
	mcp_send_can(can_message(&can_tx, 0x12, 2, (uint8_t[]){1, 2}));
	mcp_send_can(can_message(&can_tx, 0x123, 3, (uint8_t[]){1, 2, 3}));
	mcp_send_can(can_message(&can_tx, 0x1235, 4, (uint8_t[]){1, 2, 3, 5}));
	mcp_send_can(can_message(&can_tx, 0x12358, 5, (uint8_t[]){1, 2, 3, 5, 8}));

	while (1)
	{
		if (gpio_int_triggered())
		{
			mcp_recieve_can(&can_rx);
			printf("ID = 0x%X, DLC = 0x%X, DATA = ", can_rx.arbitration_id, can_rx.dlc);
			for (int i = 0; i < can_rx.dlc; ++i)
			{
				printf("0x%X ", can_rx.data[i]);
			}
			printf("\n");
		}
	}
}
