//
// Created by bleppe on 25/5/2023.
//

#ifndef LCDTEST_QUEUE_H
#define LCDTEST_QUEUE_H

#include "FreeRTOS_defs.h"

class xQueue;
typedef xQueue* QueueHandle_t;

QueueHandle_t xQueueCreate(const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize);

BaseType_t xQueueSend(QueueHandle_t xQueue, const void *pvItemToQueue, const TickType_t xTicksToWait);

BaseType_t xQueueReceive(QueueHandle_t xQueue, void *pvBuffer, const TickType_t xTicksToWait);

void vQueueDelete(QueueHandle_t xQueue);


#endif //LCDTEST_QUEUE_H



