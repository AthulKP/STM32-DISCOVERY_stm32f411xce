/*
 * mcp_2525.h
 *
 *  Created on: Mar 5, 2025
 *      Author: athul
 */

#ifndef MCP_2525_H_
#define MCP_2525_H_

#include "cmsis.h"
#include "utils.h"
#include "timer_hal.h"

#define MCP_CONFIGMODE	0x80
#define MCP_NORMALMODE	0x0
#define MCP_TXREQ_EN	0x8
#define MCP_RX0_FULL	0x1
#define MCP_RX1_FULL	0x2
#define MCP_TRANSMIT_BUFFER_0	0x0
#define MCP_TRANSMIT_BUFFER_1	0x2
#define MCP_TRANSMIT_BUFFER_2	0x4
#define MCP_RX_EXT_FRAME		0x8
#define MCP_RX_INT_EN			0x3

#define MCP_REG_CANCTRL		0x0F
#define MCP_REG_CANINTE		0x2B
#define MCP_REG_CANINTF		0x2C
#define MCP_REG_TXB0_CTRL	0x30
#define MCP_REG_TXB1_CTRL	0x40
#define MCP_REG_TXB2_CTRL	0x50
#define MCP_REG_RXB0_CTRL	0x60
#define MCP_REG_RXB1_CTRL	0x70

#define MCP_REG_CFG1	0x2A
#define MCP_REG_CFG2	0x29
#define MCP_REG_CFG3	0x28
#define MCP_RX_ALL_MSG	0x60


#define MCP_16MHz_1000kBPS_CFG1 (0x00)
#define MCP_16MHz_1000kBPS_CFG2 (0xD0)
#define MCP_16MHz_1000kBPS_CFG3 (0x82)

#define MCP_16MHz_500kBPS_CFG1  (0x00)
#define MCP_16MHz_500kBPS_CFG2  (0xF0)
#define MCP_16MHz_500kBPS_CFG3  (0x86)

#define MCP_16MHz_250kBPS_CFG1  (0x41)
#define MCP_16MHz_250kBPS_CFG2  (0xF1)
#define MCP_16MHz_250kBPS_CFG3  (0x85)

#define MCP_16MHz_200kBPS_CFG1  (0x01)
#define MCP_16MHz_200kBPS_CFG2  (0xFA)
#define MCP_16MHz_200kBPS_CFG3  (0x87)

#define MCP_16MHz_125kBPS_CFG1  (0x03)
#define MCP_16MHz_125kBPS_CFG2  (0xF0)
#define MCP_16MHz_125kBPS_CFG3  (0x86)

#define MCP_16MHz_100kBPS_CFG1  (0x03)
#define MCP_16MHz_100kBPS_CFG2  (0xFA)
#define MCP_16MHz_100kBPS_CFG3  (0x87)

#define MCP_16MHz_95kBPS_CFG1   (0x03)
#define MCP_16MHz_95kBPS_CFG2   (0xAD)
#define MCP_16MHz_95kBPS_CFG3   (0x07)

#define MCP_16MHz_83k3BPS_CFG1  (0x03)
#define MCP_16MHz_83k3BPS_CFG2  (0xBE)
#define MCP_16MHz_83k3BPS_CFG3  (0x07)

#define MCP_16MHz_80kBPS_CFG1   (0x03)
#define MCP_16MHz_80kBPS_CFG2   (0xFF)
#define MCP_16MHz_80kBPS_CFG3   (0x87)

#define MCP_16MHz_50kBPS_CFG1   (0x07)
#define MCP_16MHz_50kBPS_CFG2   (0xFA)
#define MCP_16MHz_50kBPS_CFG3   (0x87)

#define MCP_16MHz_40kBPS_CFG1   (0x07)
#define MCP_16MHz_40kBPS_CFG2   (0xFF)
#define MCP_16MHz_40kBPS_CFG3   (0x87)

#define MCP_16MHz_33k3BPS_CFG1  (0x4E)
#define MCP_16MHz_33k3BPS_CFG2  (0xF1)
#define MCP_16MHz_33k3BPS_CFG3  (0x85)

#define MCP_16MHz_20kBPS_CFG1   (0x0F)
#define MCP_16MHz_20kBPS_CFG2   (0xFF)
#define MCP_16MHz_20kBPS_CFG3   (0x87)

#define MCP_16MHz_10kBPS_CFG1   (0x1F)
#define MCP_16MHz_10kBPS_CFG2   (0xFF)
#define MCP_16MHz_10kBPS_CFG3   (0x87)

#define MCP_16MHz_5kBPS_CFG1    (0x3F)
#define MCP_16MHz_5kBPS_CFG2    (0xFF)
#define MCP_16MHz_5kBPS_CFG3    (0x87)

#define MCP_INSTRUCTION_RESET               0xC0
#define MCP_INSTRUCTION_READ                0x03
#define MCP_INSTRUCTION_WRITE               0x02
#define MCP_INSTRUCTION_READ_RX0_BUFFER      0x90
#define MCP_INSTRUCTION_READ_RX1_BUFFER      0x94
#define MCP_INSTRUCTION_LOAD_TX_BUFFER      0x40
#define MCP_INSTRUCTION_REQUEST_TO_SEND     0x80
#define MCP_INSTRUCTION_READ_STATUS         0xA0
#define MCP_INSTRUCTION_RX_STATUS           0xB0
#define MCP_INSTRUCTION_BIT_MODIFY          0x05



//Functions
void mcp_initialize(void);
void mcp_enable_msg_reception(void);
void mcp_reg_write(uint8_t , uint8_t );
uint8_t mcp_reg_read(uint8_t);
void mcp_bit_modify(uint8_t ,uint8_t , uint8_t );
void mcp_reset(void);
void mcp_rts(uint8_t );
void mcp_set_configuration_mode(void);
void mcp_set_normal_mode(void);
void mcp_set_bitrate(void);
void mcp_send_can(CAN_FRAME *);
void mcp_recieve_can(volatile CAN_FRAME *);
void mcp_enable_reception_interrupt(void);

#endif /* MCP_2525_H_ */
