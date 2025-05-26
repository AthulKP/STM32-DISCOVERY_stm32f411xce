/*
 * lsm303agr_hal.h
 *
 *  Created on: Jan 2, 2025
 *      Author: athul
 */

#ifndef LSM303AGR_HAL_H_
#define LSM303AGR_HAL_H_

#include <stdint.h>



#define Magnetometer	0x1E
#define Accelerometer	0x19

#define WHO_AM_I_A_Reg	      0x0F
#define TEMP_CFG_REG_A_Reg	  0x1F
#define OUT_TEMP_L_A_Reg      0x0C
#define OUT_TEMP_H_A_Reg      0x0D
#define CTRL_REG4_A_Reg       0x23
#define CTRL_REG1_A_Reg       0x20
#define STATUS_REG_AUX_A_Reg  0x07



#define TEMP_Reg_EN	        ((uint8_t) 0x3<<6)
#define TEMP_OFFSET	        ((int8_t)  0x19)     //25°C
#define BDU_EN	            ((uint8_t) 0x1<<7)
#define ODR_1HZ	            ((uint8_t) 0x1<<4)
#define ODR_10HZ	        ((uint8_t) 0x1<<5)
#define TEMP_DATA_AVAILABLE ((uint8_t) 0x1<<2)
#define	COUNT_TEMP_Regs		2

#endif /* LSM303AGR_HAL_H_ */
