//
// Created by bleppe on 25/5/2023.
//

#ifndef LCDTEST_TIMER_H
#define LCDTEST_TIMER_H

#include <string>
#include "FreeRTOS_defs.h"

class xTimer;
typedef xTimer* TimerHandle_t;
typedef void (*TimerCallbackFunction_t)(TimerHandle_t);


void timer_task();
void timer_task_stop();

TimerHandle_t xTimerCreate(
        const char * const pcTimerName,
        const TickType_t xTimerPeriod,
        const UBaseType_t uxAutoReload,
        void * const pvTimerID,
        TimerCallbackFunction_t pxCallbackFunction
);
BaseType_t xTimerDelete(TimerHandle_t xTimer,
                        const TickType_t xBlockTime);

BaseType_t xTimerStart(TimerHandle_t xTimer,
                       const TickType_t xBlockTime);

BaseType_t xTimerStop(TimerHandle_t xTimer,
                      const TickType_t xBlockTime);

BaseType_t xTimerChangePeriod(TimerHandle_t xTimer,
                              const TickType_t xNewPeriod,
                              const TickType_t xBlockTime);

BaseType_t xTimerReset(TimerHandle_t xTimer,
                       const TickType_t xBlockTime);

void *pvTimerGetTimerID(const TimerHandle_t xTimer);

#endif //LCDTEST_TIMER_H
