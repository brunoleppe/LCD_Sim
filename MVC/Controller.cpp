//
// Created by bruno on 09/05/23.
//

#include "Controller.h"
#include <cstdio>
#include <iostream>
#include <SDL2/SDL.h>
#include "Model.h"

void Controller::update(Subject *subject) {
    if(subject->get_type() == SUBJECT_TYPE_INPUT)
        queue.push(((InputSubject*)subject)->get_data());
}

Controller::Controller(GraphicalService* s, MenuView* v)
{
    this->s = s;
    this->v = v;
    running = true;
}

int Controller::controller_task(void *data) {
    auto c = (Controller*)data;
    c->v->set_title(((FramedMessagePacket*)c->s->get_data())->title);
    c->v->draw();
    while(c->running){
        if(!c->queue.empty()){
            c->s->on_event();
            c->v->set_title(((FramedMessagePacket*)c->s->get_data())->title);
            c->v->draw();
            c->queue.pop();
        }
        SDL_Delay(10);
    }
    return 0;
}

void Controller::Stop() {
    running = false;
}
