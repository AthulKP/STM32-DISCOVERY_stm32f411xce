/*
 * utils.h
 *
 *  Created on: Apr 27, 2025
 *      Author: athul
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "CMSIS.h"

typedef struct {
	uint32_t arbitration_id;
	uint8_t  dlc;
	uint8_t data[8];
}CAN_FRAME;

#define CONST_VAL_0		0
#define CONST_VAL_1		1
#define CONST_VAL_2		2
#define CONST_VAL_3		3
#define CONST_VAL_4		4
#define CONST_VAL_5		5
#define CONST_VAL_6		6
#define CONST_VAL_7		7
#define CONST_VAL_8		8
#define CONST_VAL_9		9

//Functions
volatile CAN_FRAME* can_message(volatile CAN_FRAME* ,uint32_t ,uint8_t ,uint8_t*);

#endif /* UTILS_H_ */
