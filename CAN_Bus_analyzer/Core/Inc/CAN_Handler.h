/*
 * CAN_Handler.h
 *
 *  Created on: Jul 10, 2025
 *      Author: athul
 */

#ifndef INC_CAN_HANDLER_H_
#define INC_CAN_HANDLER_H_

#include<stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

#define CAN_FRAME_POOL_SIZE 16  // Adjust as needed

extern QueueHandle_t can_tx_queue;


typedef struct {
	uint32_t arbitration_id;
	uint8_t  dlc;
	uint8_t data[8];
}__attribute__((packed)) CAN_FRAME;

static CAN_FRAME frame_pool[CAN_FRAME_POOL_SIZE];
static SemaphoreHandle_t frame_pool_sem;
static StaticSemaphore_t frame_pool_sem_buffer;

// Tracks which frames are free (1 = free, 0 = used)
static uint8_t frame_usage[CAN_FRAME_POOL_SIZE];

void convert_serial_to_can(uint8_t *Buf, uint32_t *Len);
void CAN_FramePool_Init(void);
CAN_FRAME* CAN_FramePool_Alloc(void);
void CAN_FramePool_Free(CAN_FRAME* frame);

#endif /* INC_CAN_HANDLER_H_ */
