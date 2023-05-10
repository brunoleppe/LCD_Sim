//
// Created by bruno on 09/05/23.
//

#ifndef LCDTEST_MODEL_H
#define LCDTEST_MODEL_H

#include "Controller.h"
#include <queue>
#include <SDL.h>
#include <SDL_thread.h>


class Model {
public:
    void update_state(InputEvent &event);
    void join();
    void stop();
    Model();

private:
    bool running;
    static int task(void *data);
    SDL_Thread *taskThread;
    std::queue<InputEvent*> queue;
};


#endif //LCDTEST_MODEL_H
