/*
 * mcp_driver.c
 *
 *  Created on: Jun 14, 2025
 *      Author: athul
 */

#include "mcp_hal.h"

SPI_HandleTypeDef *spi_handler = NULL;

void select_mcp(void) {
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
}
void unselect_mcp(void) {
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}
volatile CAN_FRAME* can_message(volatile CAN_FRAME *can_msg,
		uint32_t arbitration_id, uint8_t dlc, uint8_t *data) {

	can_msg->arbitration_id = arbitration_id;
	can_msg->dlc = dlc;
	for (uint8_t i = 0; i < dlc; i++) {
		can_msg->data[i] = data[i];
	}
	return can_msg;
}

uint8_t mcp_reg_read(uint8_t reg_address) {
	volatile uint8_t txdata[2] = { MCP_INSTRUCTION_READ, 0x0, 0x0 };
	volatile uint8_t rxData[2] = { 0, 0, 0 };
	txdata[1] = reg_address;
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_TransmitReceive(spi_handler, txdata, rxData, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
	return rxData[2];
}

void mcp_reg_write(uint8_t reg_address, uint8_t data) {
	volatile uint8_t txdata[2] = { MCP_INSTRUCTION_WRITE, 0x0, 0x0 };
	txdata[1] = reg_address;
	txdata[2] = data;
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}

uint8_t get_mcp_status(void) {
	const uint8_t txdata[3] = { MCP_INSTRUCTION_READ, MCP_REG_CANCTRL, 0x0 };
	volatile uint8_t rxData[3] = { 0, 0, 0 };
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_TransmitReceive(spi_handler, txdata, rxData, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
	return rxData[2];
}

void mcp_initialize(void) {
	mcp_reset();
	for (int i = 0; i < 100000; ++i)
		;
	//HAL_Delay(10); // For stabilizing the MCP
	mcp_set_configuration_mode();
	for (int i = 0; i < 10000; ++i)
		;
	//HAL_Delay(1); // For stabilizing the MCP
	mcp_set_bitrate();
	mcp_enable_msg_reception_and_interrupt();
	mcp_set_normal_mode();
}

void mcp_enable_msg_reception_and_interrupt(void) {
	volatile uint8_t txdata[2] = { MCP_INSTRUCTION_WRITE, MCP_REG_RXB0_CTRL,
			0x60 };
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
	txdata[1] = MCP_REG_RXB1_CTRL;
	txdata[2] = MCP_RX_ALL_MSG;
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
	txdata[1] = MCP_REG_CANINTE;
	txdata[2] = MCP_RX_INT_EN;
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}

void mcp_reset(void) {
	uint8_t txdata[0] = { MCP_INSTRUCTION_RESET };
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 1U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}
void mcp_send_instruction(uint8_t rts_reg) {
	uint8_t instruction[0];
	instruction[0] = rts_reg;
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, instruction, 1U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}

void mcp_set_configuration_mode(void) {
	volatile uint8_t txdata[3] = { MCP_INSTRUCTION_WRITE, MCP_REG_CANCTRL,
			MCP_CONFIGMODE };
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}

void mcp_set_normal_mode(void) {
	volatile uint8_t txdata[3] = { MCP_INSTRUCTION_WRITE, MCP_REG_CANCTRL,
			MCP_NORMALMODE };
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}

void mcp_set_bitrate(void) {
	volatile uint8_t txdata[2] = { MCP_INSTRUCTION_WRITE, MCP_REG_CFG1,
			MCP_16MHz_500kBPS_CFG1 };
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
	txdata[1] = MCP_REG_CFG2;
	txdata[2] = MCP_16MHz_500kBPS_CFG2;
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
	txdata[1] = MCP_REG_CFG3;
	txdata[2] = MCP_16MHz_500kBPS_CFG3;
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 3U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}

void mcp_rx_reg(uint8_t *reg_id, uint8_t *reg_ctrl) {
	do {
		if (!(mcp_reg_read(MCP_REG_TXB0_CTRL) & MCP_TXREQ_EN)) {
			*reg_id = MCP_TRANSMIT_BUFFER_0;
			*reg_ctrl = MCP_REG_TXB0_CTRL;
			break;
		} else if (!(mcp_reg_read(MCP_REG_TXB1_CTRL) & MCP_TXREQ_EN)) {
			*reg_id = MCP_TRANSMIT_BUFFER_1;
			*reg_ctrl = MCP_REG_TXB1_CTRL;
			break;
		} else if (!(mcp_reg_read(MCP_REG_TXB2_CTRL) & MCP_TXREQ_EN)) {
			*reg_id = MCP_TRANSMIT_BUFFER_2;
			*reg_ctrl = MCP_REG_TXB2_CTRL;
			break;
		} else {
			continue;
		}
	} while (1);

}

void load_array(uint8_t *txdata, CAN_FRAME *can_frame) {
	if (can_frame->arbitration_id <= 0x7FF) {
		txdata[1] = ((uint8_t) (can_frame->arbitration_id >> 3));
		txdata[2] = ((uint8_t) ((can_frame->arbitration_id & 0x7) << 5));
		txdata[3] = (0x0);
		txdata[4] = (0x0);
	} else {
		txdata[1] = ((uint8_t) (can_frame->arbitration_id >> 21));
		txdata[2] = ((uint8_t) (((can_frame->arbitration_id >> 13) & 0xE0)
				| 1 << 3 | ((can_frame->arbitration_id >> 16) & 0x3)));
		txdata[3] = ((uint8_t) (can_frame->arbitration_id >> 8));
		txdata[4] = ((uint8_t) (can_frame->arbitration_id));
	}

	txdata[5] = (can_frame->dlc);

	for (int i = 0, j = 6; i < can_frame->dlc; i++, j++) {
		txdata[j] = (can_frame->data[i]);
	}
}

void mcp_send_can(CAN_FRAME *can) {

	volatile uint8_t txdata[13];
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

	txdata[0] = (uint8_t) (MCP_INSTRUCTION_LOAD_TX_BUFFER | buffer_id);
	if (can->arbitration_id <= 0x7FF) {
		txdata[1] = ((uint8_t) (can->arbitration_id >> 3));
		txdata[2] = ((uint8_t) ((can->arbitration_id & 0x7) << 5));
		txdata[3] = (0x0);
		txdata[4] = (0x0);
	} else {
		txdata[1] = ((uint8_t) (can->arbitration_id >> 21));
		txdata[2] = ((uint8_t) (((can->arbitration_id >> 13) & 0xE0) | 1 << 3
				| ((can->arbitration_id >> 16) & 0x3)));
		txdata[3] = ((uint8_t) (can->arbitration_id >> 8));
		txdata[4] = ((uint8_t) (can->arbitration_id));
	}

	txdata[5] = (can->dlc);

	for (int i = 0, j = 6; i < can->dlc; i++, j++) {
		txdata[j] = (can->data[i]);
	}
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 11U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);

	mcp_reg_write(buffer_ctrl_reg, MCP_TXREQ_EN);

	mcp_send_instruction(MCP_INSTRUCTION_REQUEST_TO_SEND | buffer_id);
}

void mcp_recieve_can(volatile CAN_FRAME *can) {
	volatile uint8_t rx_instruction = 0, clr_rx = 0;
	if ((mcp_reg_read(MCP_REG_CANINTF) & MCP_RX0_FULL)) {
		rx_instruction = MCP_INSTRUCTION_READ_RX0_BUFFER;
		clr_rx = MCP_RX0_FULL;
	} else if ((mcp_reg_read(MCP_REG_CANINTF) & MCP_RX1_FULL)) {
		rx_instruction = MCP_INSTRUCTION_READ_RX1_BUFFER;
		clr_rx = MCP_RX1_FULL;
	} else {
		can->arbitration_id = 0;
		can->dlc = 0;
	}

	uint8_t rx_buffer_id[14];
	rx_buffer_id[0] = rx_instruction;
	uint8_t rx_data[14];
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_TransmitReceive(spi_handler, &rx_buffer_id, &rx_data, 14, 1000);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
//	spi_send(rx_instruction); // Read RXB
	uint8_t sidh = rx_data[1];
	uint8_t sidl = rx_data[2];
	uint8_t eid8 = rx_data[3];
	uint8_t eid0 = rx_data[4];
	can->dlc = rx_data[5] & 0x0F; // DLC mask
	for (int i = 0, j = 6; i < (can->dlc); i++, j++) {
		can->data[i] = rx_data[j];
	}
	if (can->dlc < 0x8) {
		for (int i = can->dlc; i < 0x8; i++) {
			can->data[i] = 0x0;
		}
	}
//	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
//	can->data[8] = '\n';
	if (sidl & MCP_RX_EXT_FRAME) {
		can->arbitration_id = sidh << 21 | (sidl >> 5) << 18
				| (sidl & 0b11) << 16 | eid8 << 8 | eid0;
	} else {
		can->arbitration_id = sidh << 3 | sidl >> 5;
	}
	uint8_t txdata[3] = { MCP_INSTRUCTION_BIT_MODIFY, MCP_REG_CANINTF, clr_rx,
			CONST_VAL_0 };
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 4U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}
