/*
 * utils.c
 *
 *  Created on: Apr 27, 2025
 *      Author: athul
 */

#include "utils.h"

volatile CAN_FRAME* can_message(volatile CAN_FRAME *can_msg, uint32_t arbitration_id,
		uint8_t dlc, uint8_t *data) {

	can_msg->arbitration_id = arbitration_id;
	can_msg->dlc = dlc;
	for (uint8_t i = 0; i < dlc; i++) {
		can_msg->data[i] = data[i];
	}
	return can_msg;
}
