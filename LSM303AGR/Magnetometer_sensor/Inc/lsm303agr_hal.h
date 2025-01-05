/*
 * lsm303agr_hal.h
 *
 *  Created on: Jan 5, 2025
 *      Author: athul
 */

#ifndef LSM303AGR_HAL_H_
#define LSM303AGR_HAL_H_

#include <stdint.h>



#define Magnetometer	0x1E

#define WHO_AM_I_A_Reg	      0x4F

// Configuration registers
#define CFG_REG_A_M_Reg	          0x60
#define CFG_REG_B_M_Reg	          0x61
#define CFG_REG_C_M_Reg	          0x62

// Status registers
#define STATUS_REG_M_Reg	      0x67

// Data offset registers
#define OFFSET_X_REG_L_M_Reg	  0x45
#define OFFSET_X_REG_H_M_Reg	  0x46
#define OFFSET_Y_REG_L_M_Reg	  0x47
#define OFFSET_Y_REG_H_M_Reg	  0x48
#define OFFSET_Z_REG_L_M_Reg	  0x49
#define OFFSET_Z_REG_H_M_Reg	  0x4A

// Raw data read registers
#define OUTX_L_REG_M_Reg	      0x68
#define OUTX_H_REG_M_Reg	      0x69
#define OUTY_L_REG_M_Reg	      0x6A
#define OUTY_H_REG_M_Reg	      0x6B
#define OUTZ_L_REG_M_Reg	      0x6C
#define OUTZ_H_REG_M_Reg	      0x6D



#define TEMP_Reg_EN	               ((uint8_t) 0x3<<6)

#define COMP_TEMP_EN	           ((uint8_t) 0x1<<7)
#define REBOOT      	           ((uint8_t) 0x1<<6)
#define SOFT_RST	               ((uint8_t) 0x1<<5) // Reset user registers
#define LP_EN                      ((uint8_t) 0x1<<4) // LP enable implies low resolution mode
#define BDU_EN                     ((uint8_t) 0x1<<4) // Prevent incorrect data reading during asynchronous reading
#define XYZ_NEW_DATA_AVAILABLE     ((uint8_t) 0x1<<3) 
#define ODR_10HZ	               ((uint8_t) 0x0<<2)
#define ODR_20HZ	               ((uint8_t) 0x1<<2)
#define ODR_50HZ	               ((uint8_t) 0x2<<2)
#define ODR_100HZ	               ((uint8_t) 0x3<<2)
#define MD_CONTINUOUS_MODE	       ((uint8_t) 0x0)
#define MD_SINGLE_MODE	           ((uint8_t) 0x1)
#define MD_IDLE_MODE	           ((uint8_t) 0x3)

#define OFFSET_REG_COUNT	       ((uint8_t) 0x6)


#endif /* LSM303AGR_HAL_H_ */
