/*
 * lsm303agr_hal.h
 *
 *  Created on: Jan 5, 2025
 *      Author: athul
 */

#ifndef LSM303AGR_HAL_H_
#define LSM303AGR_HAL_H_

#include <stdint.h>



#define Accelerometer	0x19

#define WHO_AM_I_A_Reg	      0x1F

// Configuration registers
#define CFG_REG1_A_Reg	          0x20
#define CFG_REG2_A_Reg	          0x21
#define CFG_REG3_A_Reg	          0x22
#define CFG_REG4_A_Reg	          0x23
#define CFG_REG5_A_Reg	          0x24
#define CFG_REG6_A_Reg	          0x25

// FIFO configuration registers
#define FIFO_CTRL_REG_A_Reg       0x2E
#define FIFO_SRC_REG_A_Reg        0x2F

// Status registers
#define STATUS_REG_A_Reg	      0x27

// Raw data read registers
#define OUT_X_L_A_Reg	      0x28
#define OUT_X_H_A_Reg	      0x29
#define OUT_Y_L_A_Reg	      0x2A
#define OUT_Y_H_A_Reg	      0x2B
#define OUT_Z_L_A_Reg	      0x2C
#define OUT_Z_H_A_Reg	      0x2D


#define OUTPUT_DATA_REG_COUNT   6
#define MG_TO_G   1000
#define HR_MODE   4
#define NR_MODE   6
#define LR_MODE   8

#define TEMP_Reg_EN	                    ((uint8_t) 0x3<<6)
#define COMP_TEMP_EN	                ((uint8_t) 0x1<<7)
#define REBOOT      	                ((uint8_t) 0x1<<7) // Reboot accelerometer memory content
#define SOFT_RST	                    ((uint8_t) 0x1<<5) // Reset user registers
#define XYZ_NEW_DATA_AVAILABLE          ((uint8_t) 0x1<<3)

#define ODR_1Hz	        ((uint8_t) 0x1<<4)
#define ODR_10Hz	    ((uint8_t) 0x2<<4)
#define ODR_25Hz	    ((uint8_t) 0x3<<4)
#define ODR_50Hz	    ((uint8_t) 0x4<<4)
#define ODR_100Hz	    ((uint8_t) 0x5<<4)

#define X_EN                            ((uint8_t) 0x1<<0)
#define Y_EN                            ((uint8_t) 0x1<<1)
#define Z_EN                            ((uint8_t) 0x1<<2)
#define HR_EN                           ((uint8_t) 0x1<<3) // High resolution mode
#define LP_EN                           ((uint8_t) 0x1<<3) // LP enable implies low resolution mode
#define LITTLE_EDIAN_EN                 ((uint8_t) 0x1<<6) // Little endian data selection enable
#define BDU_EN                          ((uint8_t) 0x1<<7) // Block data update enable

#define FS_2                            ((uint8_t) 0x0<<4) // Full-scale selection ±2 g
#define FS_4                            ((uint8_t) 0x1<<4) // Full-scale selection ±4 g
#define FS_8                            ((uint8_t) 0x2<<4) // Full-scale selection ±8 g
#define FS_16                           ((uint8_t) 0x3<<4) // Full-scale selection ±16 g

//Linear acceleration sensitivity
#define LA_SO_FS_2_HR            0.98           
#define LA_SO_FS_4_HR            1.95
#define LA_SO_FS_8_HR            3.9
#define LA_SO_FS_16_HR           11.72
#define LA_SO_FS_2_NR            3.9
#define LA_SO_FS_4_NR            7.82
#define LA_SO_FS_8_NR            15.63
#define LA_SO_FS_16_NR           46.9
#define LA_SO_FS_2_LR            15.63
#define LA_SO_FS_4_LR            31.26
#define LA_SO_FS_8_LR            62.52
#define LA_SO_FS_16_LR           187.58


#endif /* LSM303AGR_HAL_H_ */
