/*
 * mcp_driver.c
 *
 *  Created on: Apr 25, 2025
 *      Author: athul
 */

#include "mcp_2525.h"
#include "spi_hal.h"
#include "gpio_hal.h"
#include <stdio.h>

void mcp_initialize(void){
	mcp_reset();
	timer_delay_ms(100);
	mcp_set_configuration_mode();
	mcp_set_bitrate();
	mcp_enable_msg_reception();
	mcp_enable_reception_interrupt();
	mcp_set_normal_mode();
}
void mcp_enable_msg_reception(void) {
	mcp_reg_write(MCP_REG_RXB0_CTRL, MCP_RX_ALL_MSG);
	mcp_reg_write(MCP_REG_RXB1_CTRL, MCP_RX_ALL_MSG);
}
void mcp_enable_reception_interrupt(void) {
	mcp_reg_write(MCP_REG_CANINTE, MCP_RX_INT_EN);
}
void mcp_reg_write(uint8_t reg, uint8_t data) {
	gpio_cs_enable();
	spi_send(MCP_INSTRUCTION_WRITE);
	spi_send(reg);
	spi_send(data);
	gpio_cs_disable();
}

void mcp_bit_modify(uint8_t reg,uint8_t bit_pos, uint8_t val){
	gpio_cs_enable();
	spi_send(MCP_INSTRUCTION_BIT_MODIFY);
	spi_send(reg);
	spi_send(bit_pos);
	spi_send(val);
	gpio_cs_disable();
}
uint8_t mcp_reg_read(uint8_t reg) {
	gpio_cs_enable();
	spi_send(MCP_INSTRUCTION_READ);
	spi_send(reg);
	uint8_t data = spi_recevie();
	gpio_cs_disable();
	return data;
}
void mcp_reset(void) {
	gpio_cs_enable();
	spi_send(MCP_INSTRUCTION_RESET);
	gpio_cs_disable();
}
void mcp_rts(uint8_t rts_reg) {
	gpio_cs_enable();
	spi_send(rts_reg);
	gpio_cs_disable();
}

void mcp_set_configuration_mode(void) {
	mcp_reg_write(MCP_REG_CANCTRL, MCP_CONFIGMODE);
}

void mcp_set_normal_mode(void) {
	mcp_reg_write(MCP_REG_CANCTRL, MCP_NORMALMODE);
}

void mcp_set_bitrate(void) {
	mcp_reg_write(MCP_REG_CFG1, MCP_16MHz_500kBPS_CFG1);
	mcp_reg_write(MCP_REG_CFG2, MCP_16MHz_500kBPS_CFG2);
	mcp_reg_write(MCP_REG_CFG3, MCP_16MHz_500kBPS_CFG3);
}

void mcp_send_can(CAN_FRAME *can) {
	volatile uint8_t buffer_id = 0, buffer_ctrl_reg = 0;
	do {
		if (!(mcp_reg_read(MCP_REG_TXB0_CTRL) & MCP_TXREQ_EN)) {
			buffer_id = MCP_TRANSMIT_BUFFER_0;
			buffer_ctrl_reg = MCP_REG_TXB0_CTRL;
			break;
		} else if (!(mcp_reg_read(MCP_REG_TXB1_CTRL) & MCP_TXREQ_EN)) {
			buffer_id = MCP_TRANSMIT_BUFFER_1;
			buffer_ctrl_reg = MCP_REG_TXB1_CTRL;
			break;
		} else if (!(mcp_reg_read(MCP_REG_TXB2_CTRL) & MCP_TXREQ_EN)) {
			buffer_id = MCP_TRANSMIT_BUFFER_2;
			buffer_ctrl_reg = MCP_REG_TXB2_CTRL;
			break;
		} else {
			continue;
		}
	} while (1);

	gpio_cs_enable();
	spi_send(MCP_INSTRUCTION_LOAD_TX_BUFFER | buffer_id);
	if (can->arbitration_id <= 0x7FF) {
		spi_send((uint8_t) (can->arbitration_id >> 3));
		spi_send((uint8_t) ((can->arbitration_id & 0x7) << 5));
		spi_send(0x0);
		spi_send(0x0);
	} else {
		spi_send((uint8_t) (can->arbitration_id >> 21));
		spi_send(
				(uint8_t) (((can->arbitration_id >> 13) & 0xE0) | 1 << 3
						| ((can->arbitration_id >> 16) & 0x3)));
		spi_send((uint8_t) (can->arbitration_id >> 8));
		spi_send((uint8_t) (can->arbitration_id));
	}

	spi_send(can->dlc);

	for (int i = 0; i < can->dlc; i++) {
		spi_send(can->data[i]);
	}
	gpio_cs_disable();

	mcp_reg_write(buffer_ctrl_reg, MCP_TXREQ_EN);

	mcp_rts( MCP_INSTRUCTION_REQUEST_TO_SEND | buffer_id);
}

void mcp_recieve_can(volatile CAN_FRAME *can) {
	volatile uint8_t rx_instruction = 0, clr_rx=0;
	if ((mcp_reg_read(MCP_REG_CANINTF) & MCP_RX0_FULL)) {
		rx_instruction = MCP_INSTRUCTION_READ_RX0_BUFFER;
		clr_rx = MCP_RX0_FULL;
	}else if((mcp_reg_read(MCP_REG_CANINTF) & MCP_RX1_FULL)) {
		rx_instruction = MCP_INSTRUCTION_READ_RX1_BUFFER;
		clr_rx = MCP_RX1_FULL;
	}
	else{
		can->arbitration_id = 0;
		can->dlc = 0;
	}

	gpio_cs_enable();
	spi_send(rx_instruction);  // Read RXB
	uint8_t sidh = spi_recevie();
	uint8_t sidl = spi_recevie();
	uint8_t eid8 = spi_recevie();
	uint8_t eid0 = spi_recevie();
	can->dlc = spi_recevie();
	for (int i = 0; i < (can->dlc & 0x0F); i++) {
		can->data[i] = spi_recevie();
	}
	gpio_cs_disable();

	if (sidl & MCP_RX_EXT_FRAME) {
		can->arbitration_id = sidh << 21 | (sidl >> 5) << 18
				| (sidl & 0b11) << 16 | eid8 << 8 | eid0;
	} else {
		can->arbitration_id = sidh << 3 | sidl >> 5;
	}
	mcp_bit_modify(MCP_REG_CANINTF, clr_rx, CONST_VAL_0);

}

