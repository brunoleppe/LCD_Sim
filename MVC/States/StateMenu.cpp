//
// Created by bleppe on 16/05/23.
//
#include "StateMenu.h"
#include "StateTest.h"
#include "input.h"

Status StateMenu::on_event(StateEvent *evt) {
    Status status;
    switch(evt->signal){
        case EVENT_SIGNAL_ENTER:
            printf("On Enter StateMenu\n");
            status = STATUS_INIT;
            break;
        case EVENT_SIGNAL_EXIT:
            printf("On Exit StateMenu\n");
            status = STATUS_HANDLED;
            break;
        case EVENT_SIGNAL_SELECT:{
            printf("StateMenu On Select: %d\n", evt->value);
            if(evt->value == INPUT_EVENT_CLICKED)
                context->transition(new StateTest());
            status = STATUS_HANDLED;
            break;
        }
        default:
            printf("Ignored Event: %d\n", evt->signal);
            status = State::on_event(evt);
    }
    return status;
}
