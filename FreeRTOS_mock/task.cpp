//
// Created by bleppe on 25/5/2023.
//

#include "task.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>



class xTask{
private:
    SDL_Thread* thread;
    TaskFunction_t taskFunction;
    void *params;
    bool running;
public:
    xTask(const char* name, TaskFunction_t function, void *params) : thread(), taskFunction(function), params(params), running(true) {
        thread = SDL_CreateThread([](void* p)->int{
            auto task = static_cast<xTask*>(p);
            task->taskFunction(task->params);
            task->running = false;
            return 0;
        }, name, this);
    }
    void stop(){
        if(running)
            SDL_WaitThread(thread, nullptr);
    }
};


BaseType_t xTaskCreate(TaskFunction_t pxTaskCode,
                       const char *pcName,
                       const configSTACK_DEPTH_TYPE usStackDepth,
                       void *pvParameters,
                       UBaseType_t uxPriority,
                       TaskHandle_t *pxCreatedTask)
{
    auto task = new xTask(pcName, pxTaskCode, pvParameters);
    if(pxCreatedTask != nullptr){
        *pxCreatedTask = task;
    }
    return 1;
}

void vTaskDelete(TaskHandle_t xTask)
{
    if(xTask == nullptr)
        return;
    xTask->stop();
    delete xTask;
}

void vTaskDelay(const TickType_t xTicksToDelay)
{
    SDL_Delay(xTicksToDelay);
}