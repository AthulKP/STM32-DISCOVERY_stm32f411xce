/*
 * i3g4250d_hal.h
 *
 *  Created on: Feb 12, 2025
 *      Author: athul
 */

#ifndef I3G4250D_HAL_H_
#define I3G4250D_HAL_H_

#include <stdint.h>
#include "CMSIS.h"

#define WHO_AM_I_REG			0x0F
#define WHO_AM_I				0xD3
#define CTRL_REG1				0x20
#define OUT_TEMP_REG			0x26
#define STATUS_REG				0x27
#define OUT_X_L_REG				0x28
#define OUT_X_H_REG				0x29
#define OUT_Y_L_REG				0x2A
#define OUT_Y_H_REG				0x2B
#define OUT_Z_L_REG				0x2C
#define OUT_Z_H_REG				0x2D
#define OUTPUT_REG_COUNT		0x6


#define Z_EN    				(uint8_t)1<<2
#define Y_EN					(uint8_t)1<<1
#define X_EN					(uint8_t)1<<0
#define BANDWIDTH_12_5_CUTOFF	0b00<<4
#define DATA_RATE_100_HZ		0b00<<6
#define READ_MODE				0x1<<7
#define SINGLE_REG				0x0<<6
#define MULTIPLE_REG			0x1<<6
#define XYZ_DATA_AVAILABLE		0x1<<3

#endif /* I3G4250D_HAL_H_ */
