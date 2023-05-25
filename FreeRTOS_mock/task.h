//
// Created by bleppe on 25/5/2023.
//

#ifndef LCDTEST_TASK_H
#define LCDTEST_TASK_H

#include "FreeRTOS_defs.h"

class xTask;
typedef xTask* TaskHandle_t;
typedef void (*TaskFunction_t)(void *pvParameters);


BaseType_t xTaskCreate(TaskFunction_t pxTaskCode,
                       const char *pcName,
                       const configSTACK_DEPTH_TYPE usStackDepth,
                       void *pvParameters,
                       UBaseType_t uxPriority,
                       TaskHandle_t *pxCreatedTask);

void vTaskDelete(TaskHandle_t xTask);

void vTaskDelay(const TickType_t xTicksToDelay);

#endif //LCDTEST_TASK_H
