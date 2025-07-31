/*
 * CAN_Handler.c
 *
 *  Created on: Jul 10, 2025
 *      Author: athul
 */

#include "CAN_Handler.h"

void convert_serial_to_can(uint8_t *ser_data, uint32_t *len)
{
    if (len < 13) return;

    CAN_FRAME* frame = CAN_FramePool_Alloc();
    if (!frame) return;  // Pool full, skip

    frame->arbitration_id   = (ser_data[0] << 24) | (ser_data[1] << 16) | (ser_data[2] << 8) | ser_data[3]; // Big endian to little endian
    frame->dlc         		= ser_data[4];
    if (frame->dlc > 8) frame->dlc = 8;
    memcpy(frame->data, &ser_data[5], frame->dlc);

    xQueueSendFromISR(can_tx_queue, &frame, pdFALSE);
}


void CAN_FramePool_Init(void)
{
    frame_pool_sem = xSemaphoreCreateBinaryStatic(&frame_pool_sem_buffer);

    for (int i = 0; i < CAN_FRAME_POOL_SIZE; ++i){
        frame_usage[i] = 1;
    }
    xSemaphoreGive(frame_pool_sem);
}

CAN_FRAME* CAN_FramePool_Alloc(void)
{
	CAN_FRAME* frame = NULL;
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if (xSemaphoreTakeFromISR(frame_pool_sem, &xHigherPriorityTaskWoken ) == pdTRUE)
    {
        for (int i = 0; i < CAN_FRAME_POOL_SIZE; ++i)
        {
            if (frame_usage[i])
            {
                frame_usage[i] = 0;
                frame = &frame_pool[i];
                break;
            }
        }
        xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(frame_pool_sem,&xHigherPriorityTaskWoken);
    }
    return frame;
}

void CAN_FramePool_Free(CAN_FRAME* frame)
{
    if (!frame) return;

    if (xSemaphoreTake(frame_pool_sem, portMAX_DELAY) == pdTRUE)
    {
        for (int i = 0; i < CAN_FRAME_POOL_SIZE; ++i)
        {
            if (&frame_pool[i] == frame)
            {
                frame_usage[i] = 1;
                break;
            }
        }
        xSemaphoreGive(frame_pool_sem);
    }
}
