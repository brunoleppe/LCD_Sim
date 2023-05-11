//
// Created by bruno on 09/05/23.
//

#include "Controller.h"
#include <SDL2/SDL.h>
#include "ControllerInputEvent.h"
#include "Input/virtual_term.h"

void Controller::update(Subject *subject) {
    if(subject->get_type() == SUBJECT_TYPE_INPUT) {
        queue.push(((InputSubject *) subject)->get_data());
    }
}

Controller::Controller(ModelStateService* s, ViewService* v) : model(s), view(v), running(true)
{}

int Controller::controller_task(void *data) {
    auto c = (Controller*)data;
    c->view->set_message(c->model->get_data());
    c->view->update();
    while(c->running){
        if(!c->queue.empty()){

            auto evt = c->queue.front();
            ControllerInputEvent cEvt = {.event = evt.value};
            int res;
            if((res = is_alpha(evt.code))){
                cEvt.type = INPUT_EVENT_TYPE_ALPHA;
                cEvt.code = res;
            }
            else if((res = is_numeric(evt.code))){
                cEvt.type = INPUT_EVENT_TYPE_NUMERIC;
                cEvt.code = res;
            }
            else if((res = is_control(evt.code))){
                cEvt.type = INPUT_EVENT_TYPE_CONTROL;
                cEvt.code = res;
            }

            c->view->set_event(cEvt);
            c->model->on_event(cEvt);
            c->view->set_message(c->model->get_data());
            c->view->update();
            c->queue.pop();
        }
        SDL_Delay(10);
    }
    return 0;
}

void Controller::Stop() {
    running = false;
}
