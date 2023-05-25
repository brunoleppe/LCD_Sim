//
// Created by bleppe on 25/5/2023.
//
#include "queue.h"
#include <SDL2/SDL.h>
#include <queue>

class xQueue{
private:
    std::queue<char*> q;
    int size;
    int count;
public:
    xQueue(int size, int count): size(size), count(count){

    }
    void enqueue(const void* data)
    {
        if((int)q.size() < count) {
            char *buffer = new char[size];
            memcpy(buffer,data,size);
            q.push(buffer);
        }
    }

    void dequeue(void* data){
        char* e = q.front();
        q.pop();
        memcpy(data,e,size);
    }

    bool empty(){
        return q.empty();
    }

    virtual ~xQueue() {
        while(!q.empty()){
            delete[] q.front();
            q.pop();
        }
    }
};

QueueHandle_t xQueueCreate(const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize)
{
    auto queue = new xQueue(uxItemSize, uxQueueLength);
    return queue;
}

BaseType_t xQueueSend(QueueHandle_t xQueue, const void *pvItemToQueue, const TickType_t xTicksToWait)
{
    SDL_Delay(xTicksToWait);
    xQueue->enqueue(pvItemToQueue);
    return 1;
}

BaseType_t xQueueReceive(QueueHandle_t xQueue, void *pvBuffer, const TickType_t xTicksToWait)
{
    SDL_Delay(xTicksToWait);
    if(xQueue->empty())
        return 0;
    xQueue->dequeue(pvBuffer);
    return 1;
}

void vQueueDelete(QueueHandle_t xQueue)
{
    delete xQueue;
}