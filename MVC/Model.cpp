//
// Created by bruno on 09/05/23.
//

#include "Model.h"
#include <iostream>

void Model::update_state(InputEvent &event) {
    queue.push(&event);
}

int Model::task(void *data) {
    Model *m = (Model*)data;
    while(m->running){
        while(m->queue.empty());
        InputEvent *evt = m->queue.front();
        m->queue.pop();

        std::cout << "Deque event: " << evt->type;

    }
}

void Model::join() {
    SDL_WaitThread(taskThread, nullptr);
}

void Model::stop() {
    running = false;
}

Model::Model() : running(true)
{
    taskThread = SDL_CreateThread(this->task, "EventThread", this);
}

