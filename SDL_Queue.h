//
// Created by bleppe on 15/05/23.
//

#ifndef LCDTEST_SDL_QUEUE_H
#define LCDTEST_SDL_QUEUE_H

#include <SDL2/SDL.h>
#include <queue>

template <typename T>
class SDL_Queue {
public:
    // Constructor
    SDL_Queue() {
        mutex = SDL_CreateMutex();
        condition = SDL_CreateCond();
    }

    // Destructor
    ~SDL_Queue() {
        SDL_DestroyMutex(mutex);
        SDL_DestroyCond(condition);
    }

    // Push an item to the queue
    void push(const T& item) {
        SDL_LockMutex(mutex);
        queue.push(item);
        SDL_CondSignal(condition);
        SDL_UnlockMutex(mutex);
    }

    // Pop an item from the queue (blocking)
    T pop() {
        SDL_LockMutex(mutex);
        while (queue.empty()) {
            SDL_CondWait(condition, mutex);
        }
        T item = queue.front();
        queue.pop();
        SDL_UnlockMutex(mutex);
        return item;
    }

private:
    std::queue<T> queue;
    SDL_mutex* mutex;
    SDL_cond* condition;
};


#endif //LCDTEST_SDL_QUEUE_H
