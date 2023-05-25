//
// Created by bleppe on 25/5/2023.
//

#include "timer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <list>

class xTimer{
private:
    std::string name;
    const int period;
    bool autoReload;
    void* context;
    TimerCallbackFunction_t callback;

    bool running;
    int count;
public:
    xTimer(const char* name, const int period, const bool autoReload, void* context, TimerCallbackFunction_t callback) :
            name(name), period(period), autoReload(autoReload), context(context), callback(callback), running(false), count(0)
    {

    }
    void start(){
        running = true;
        count = 0;
    }
    void stop(){
        running = false;
    }
    void tick(){
        if(!running)
            return;
        if(++count == period){
            count = 0;
            if(callback != nullptr){
                callback(this);
            }
            if(!autoReload){
                running = false;
            }
        }
    }
    void* get_context(){
        return context;
    }
};

static std::list<xTimer*> timers;
static bool running;
static SDL_Thread* timerThread = nullptr;

static int task(void *data)
{
    (void)data;
    while(running){
        for(auto timer : timers){
            timer->tick();
        }
        SDL_Delay(1);
    }
    return 0;
}


void timer_task()
{
    running = true;
    timerThread = SDL_CreateThread(task, "TimerThread", nullptr);
}

void timer_task_stop()
{
    running = false;
    SDL_WaitThread(timerThread, nullptr);
}


TimerHandle_t xTimerCreate(
        const char * const pcTimerName,
        const TickType_t xTimerPeriod,
        const UBaseType_t uxAutoReload,
        void * const pvTimerID,
        TimerCallbackFunction_t pxCallbackFunction
)
{
    auto timer = new xTimer(pcTimerName, xTimerPeriod, uxAutoReload, pvTimerID, pxCallbackFunction);
    timers.push_back(timer);
    return timer;
}
BaseType_t xTimerDelete(TimerHandle_t xTimer,
                        const TickType_t xBlockTime)
{
    xTimer->stop();
    (void)xBlockTime;
    timers.remove(xTimer);
    delete xTimer;
    return 1;
}

BaseType_t xTimerStart(TimerHandle_t xTimer,
                       const TickType_t xBlockTime)
{
    (void)xBlockTime;
    xTimer->start();
    return 1;
}

BaseType_t xTimerStop(TimerHandle_t xTimer,
                      const TickType_t xBlockTime)
{
    (void)xBlockTime;
    xTimer->stop();
    return 1;
}

BaseType_t xTimerReset(TimerHandle_t xTimer,
                       const TickType_t xBlockTime)
{
    (void)xBlockTime;
    xTimer->start();
    return 1;
}


void *pvTimerGetTimerID(const TimerHandle_t xTimer)
{
    return xTimer->get_context();
}
